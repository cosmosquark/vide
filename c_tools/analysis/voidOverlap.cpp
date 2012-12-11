// =============================================================================
//
//   Program: voidOverlap
//
//   Description: Takes two void catalogs and reports the "overlap" between
//                them.
//
// ============================================================================


#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include <stdio.h>
#include <math.h>
#include "voidOverlap_conf.h"
#include <vector>
#include <netcdfcpp.h>

typedef struct partStruct {
  float x, y, z, volume;
  float ra, dec, redshift;
  long uniqueID;
} PART;

typedef struct zoneStruct {
  int numPart;
  int *partIDs;
} ZONE2PART;

typedef struct voidZoneStruct {
  int numZones;
  int *zoneIDs;
} VOID2ZONE;

typedef struct voidStruct {
  float vol, coreDens, zoneVol, densCon, voidProb, radius;
  int voidID, numPart, numZones, coreParticle, zoneNumPart;
  float maxRadius, nearestMock, centralDen, redshift, redshiftInMpc;
  float nearestEdge;
  float center[3], barycenter[3];
  std::vector<int> matches;
} VOID;

typedef struct catalog {
  int numVoids, numPartTot, numZonesTot;
  float boxLen[3];
  std::vector<PART> part;
  std::vector<ZONE2PART> zones2Parts;
  std::vector<VOID2ZONE> void2Zones;
  std::vector<VOID> voids;
} CATALOG;

void loadCatalog(const char *partFile, const char *volFile, 
                 const char *voidFile, const char *zoneFile,
                 const char *infoFile,
                 const char *zonePartFile, CATALOG& catalog);

int main(int argc, char **argv) {

  // initialize arguments
  voidOverlap_info args;
  voidOverlap_conf_params params;

  voidOverlap_conf_init(&args);
  voidOverlap_conf_params_init(&params);

  params.check_required = 0;
  if (voidOverlap_conf_ext (argc, argv, &args, &params))
    return 1;

  if (!args.configFile_given) {
    if (voidOverlap_conf_required (&args, VOIDOVERLAP_CONF_PACKAGE))
      return 1;
  } else {
    params.check_required = 1;
    params.initialize = 0;
    if (voidOverlap_conf_config_file (args.configFile_arg, &args, &params))
    return 1;
  }

  char outVoid[200];
  int p1, p2, iZ1, iZ2, iVoid1, iVoid2, iVoid, zoneID1, zoneID2;
  int voidStartIndex, numVoids, numVoidsOut, targetVoidID, voidID1, voidID2;
  FILE *fp;
  float *temp, junk, voidVol;
  long *temp2;
  int junkInt, voidID, numPart, numZones, zoneID, partID;
  char line[500], junkStr[10];
  bool periodicX=false, periodicY=false, periodicZ=false, match;
  float dist[3], rdist, r1, r2;

  CATALOG catalog1, catalog2;

  loadCatalog(args.partFile1_arg, args.volFile1_arg, args.voidFile1_arg,
              args.zoneFile1_arg, args.infoFile1_arg,
              args.zonePartFile1_arg, catalog1);

  loadCatalog(args.partFile2_arg, args.volFile2_arg, args.voidFile2_arg,
              args.zoneFile2_arg, args.infoFile2_arg,
              args.zonePartFile2_arg, catalog2);

  // check for periodic box
    if ( strchr(args.periodic_arg, 'x') != NULL) {
      periodicX = true;
      printf("Will assume x-direction is periodic.\n");
    }
    if ( strchr(args.periodic_arg, 'y') != NULL) {
      periodicY = true;
      printf("Will assume y-direction is periodic.\n");
    }
    if ( strchr(args.periodic_arg, 'z') != NULL) {
      periodicZ = true;
      printf("Will assume z-direction is periodic.\n");
    }

  printf(" Determining overlap...\n");
  for (iVoid1 = 0; iVoid1 < catalog1.numVoids; iVoid1++) {
    printf("  Working on void %d of %d...\n", iVoid1, catalog1.numVoids); 
    voidID1 = catalog1.voids[iVoid1].voidID;
    for (iZ1 = 0; iZ1 < catalog1.void2Zones[voidID1].numZones; iZ1++) {
      zoneID1 = catalog1.void2Zones[voidID1].zoneIDs[iZ1];
      for (p1 = 0; p1 < catalog1.zones2Parts[zoneID1].numPart; p1++) {
        
        for (iVoid2 = 0; iVoid2 < catalog2.numVoids; iVoid2++) {
          voidID2 = catalog2.voids[iVoid2].voidID;
          for (iZ2 = 0; iZ2 < catalog2.void2Zones[voidID2].numZones; iZ2++) {
            zoneID2 = catalog2.void2Zones[voidID2].zoneIDs[iZ2];
            for (p2 = 0; p2 < catalog2.zones2Parts[zoneID2].numPart; p2++) {
        
              match = false;

              if (args.useID_flag) {
                if (catalog1.part[p1].uniqueID == 
                    catalog2.part[p2].uniqueID) match = true;
              } else {
                dist[0] = catalog1.part[p1].x - catalog2.part[p2].x;
                dist[1] = catalog1.part[p1].y - catalog2.part[p2].y;
                dist[2] = catalog1.part[p1].z - catalog2.part[p2].z;

                if (periodicX) dist[0] = fmin(dist[0], 
                                              abs(catalog1.boxLen[0]-dist[0]));
                if (periodicY) dist[1] = fmin(dist[1], 
                                              abs(catalog1.boxLen[1]-dist[1]));
                if (periodicZ) dist[2] = fmin(dist[2], 
                                              abs(catalog1.boxLen[2]-dist[2]));

                rdist = sqrt(dist[0]*dist[0] + dist[1]*dist[1] + 
                             dist[2]*dist[2]);

                r1 = pow(3./4./M_PI*catalog1.part[p1].volume, 1./3.);
                r2 = pow(3./4./M_PI*catalog2.part[p2].volume, 1./3.);
                if (rdist <=  r1 + r2) match = true;
             }
       
              if (match) {
                catalog1.voids[iVoid1].matches.push_back(iVoid2);
                break;
              } 

            } // end p2
            if (match) break;
          } // end iZ1
        } // end iVoid2

      } // end p1
    } // end iZ1
  } // end iVoid1


  printf("HELLO: ");
  for (iVoid = 0; iVoid < catalog1.voids[0].matches.size(); iVoid++) {
    printf("%d ", catalog2.voids[iVoid].voidID);
  }
  printf("\n Well, bye.\n");
  return 0;
} // end main

// ----------------------------------------------------------------------------
void loadCatalog(const char *partFile, const char *volFile, 
                 const char *voidFile, const char *zoneFile,
                 const char *infoFile,
                 const char *zonePartFile, CATALOG& catalog) {

  int i, p, numPartTot, numZonesTot, dummy, iVoid, iZ, numVolTot;
  FILE *fp;
  float *temp, junk, voidVol, coreParticle, coreDens, zoneVol, zoneNumPart;
  float densCon, voidProb, volNorm;
  long *temp2;
  int junkInt, voidID, numPart, numZones, zoneID, partID;
  char line[500], junkStr[10];
  float ranges[3][2];

  printf("\n Loading info...\n");
  NcFile f_info(infoFile);
  ranges[0][0] = f_info.get_att("range_x_min")->as_double(0);
  ranges[0][1] = f_info.get_att("range_x_max")->as_double(0);
  ranges[1][0] = f_info.get_att("range_y_min")->as_double(0);
  ranges[1][1] = f_info.get_att("range_y_max")->as_double(0);
  ranges[2][0] = f_info.get_att("range_z_min")->as_double(0);
  ranges[2][1] = f_info.get_att("range_z_max")->as_double(0);

  catalog.boxLen[0] = ranges[0][1] - ranges[0][0];
  catalog.boxLen[1] = ranges[1][1] - ranges[1][0];
  catalog.boxLen[2] = ranges[2][1] - ranges[2][0];
  f_info.close();
  
  // read in all particle positions
  printf("\n Loading particles...\n");
  fp = fopen(partFile, "r");
  fread(&dummy, 1, 4, fp); 
  fread(&catalog.numPartTot, 1, 4, fp);
  fread(&dummy, 1, 4, fp);

  catalog.part.resize(numPartTot);

  temp = (float *) malloc(numPartTot * sizeof(float));
  temp2 = (long *) malloc(numPartTot * sizeof(long));

  fread(&dummy, 1, 4, fp);
  fread(temp, numPartTot, 4, fp);
  for (p = 0; p < numPartTot; p++) 
    catalog.part[p].x = temp[p];
  fread(&dummy, 1, 4, fp);
  fread(&dummy, 1, 4, fp);
  fread(temp, numPartTot, 4, fp);
  for (p = 0; p < numPartTot; p++) 
    catalog.part[p].y = temp[p];
  fread(&dummy, 1, 4, fp);
  fread(&dummy, 1, 4, fp);
  fread(temp, numPartTot, 4, fp);
  for (p = 0; p < numPartTot; p++) 
    catalog.part[p].z = temp[p];
  fread(&dummy, 1, 4, fp);
  fread(&dummy, 1, 4, fp);
  fread(temp, numPartTot, 4, fp);
  for (p = 0; p < numPartTot; p++) 
    catalog.part[p].ra = temp[p];
  fread(&dummy, 1, 4, fp);
  fread(&dummy, 1, 4, fp);
  fread(temp, numPartTot, 4, fp);
  for (p = 0; p < numPartTot; p++) 
    catalog.part[p].dec = temp[p];
  fread(&dummy, 1, 4, fp);
  fread(&dummy, 1, 4, fp);
  fread(temp, numPartTot, 4, fp);
  for (p = 0; p < numPartTot; p++) 
    catalog.part[p].redshift = temp[p];
  fread(&dummy, 1, 4, fp);
  fread(&dummy, 1, 4, fp);
  fread(temp2, numPartTot, 8, fp);
  for (p = 0; p < numPartTot; p++) 
    catalog.part[p].uniqueID = temp2[p];
 
  free(temp2);
  fclose(fp); 

  printf(" Read %d particles...\n", catalog.numPartTot);

  // read in all particle volumes
  printf(" Loading volumes...\n");
  fp = fopen(volFile, "r");
  fread(&numVolTot, 1, 4, fp);
  fread(temp, numPartTot, 4, fp);
  for (p = 0; p < numPartTot; p++) 
    catalog.part[p].volume = temp[p];
  fclose(fp); 
  free(temp);

  // read in desired voids
  printf(" Loading voids...\n");
  fp = fopen(voidFile ,"r");
  fgets(line, sizeof(line), fp);
  sscanf(line, "%d %s %d %s", &junkInt, junkStr, &catalog.numVoids, junkStr);
  fgets(line, sizeof(line), fp);

  catalog.voids.resize(catalog.numVoids);
  iVoid = 0;
  while (fgets(line, sizeof(line), fp) != NULL) {
   scanf(line, "%d %d %d %f %f %d %d %f %d %f %f\n", &iVoid, &voidID,
           &coreParticle, &coreDens, &zoneVol, &zoneNumPart, &numZones,
           &voidVol, &numPart, &densCon, &voidProb);

    catalog.voids[iVoid].coreParticle = coreParticle;
    catalog.voids[iVoid].zoneNumPart = zoneNumPart;
    catalog.voids[iVoid].coreDens = coreDens;
    catalog.voids[iVoid].zoneVol = zoneVol;
    catalog.voids[iVoid].voidID = voidID;
    catalog.voids[iVoid].vol = voidVol;
    catalog.voids[iVoid].numPart = numPart;
    catalog.voids[iVoid].numZones = numZones;
    catalog.voids[iVoid].densCon = densCon;
    catalog.voids[iVoid].voidProb = voidProb;

    catalog.voids[iVoid].radius = pow(voidVol/volNorm*3./4./M_PI, 1./3.);
    iVoid++;
  }
  fclose(fp);

  // load up the zone membership for each void
  printf(" Loading zone-void membership info...\n");
  fp = fopen(zoneFile, "r");
  fread(&catalog.numZonesTot, 1, 4, fp);

  catalog.void2Zones.resize(catalog.numZonesTot);

  for (iZ = 0; iZ < numZonesTot; iZ++) {
    fread(&numZones, 1, 4, fp);

    catalog.void2Zones[iZ].numZones = numZones;
    catalog.void2Zones[iZ].zoneIDs = (int *) malloc(numZones * sizeof(int));

    for (p = 0; p < numZones; p++) {
      fread(&catalog.void2Zones[iZ].zoneIDs[p], 1, 4, fp);
    }
  }
  fclose(fp);

  // now the zone membership
  printf(" Loading particle-zone membership info...\n");
  fp = fopen(zonePartFile, "r");
  fread(&dummy, 1, 4, fp);
  fread(&numZonesTot, 1, 4, fp);

  catalog.zones2Parts.resize(numZonesTot); 
  for (iZ = 0; iZ < numZonesTot; iZ++) {
    fread(&numPart, 1, 4, fp);
    
    catalog.zones2Parts[iZ].numPart = numPart;
    catalog.zones2Parts[iZ].partIDs = (int *) malloc(numPart * sizeof(int));

    for (p = 0; p < numPart; p++) {
      fread(&catalog.zones2Parts[iZ].partIDs[p], 1, 4, fp);
    }
  }

  fclose(fp);

} // end loadCatalog