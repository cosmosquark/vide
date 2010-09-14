/** @file zobovConf.h
 *  @brief The header file for the command line option parser
 *  generated by GNU Gengetopt version 2.22
 *  http://www.gnu.org/software/gengetopt.
 *  DO NOT modify this file, since it can be overwritten
 *  @author GNU Gengetopt by Lorenzo Bettini */

#ifndef ZOBOVCONF_H
#define ZOBOVCONF_H

/* If we use autoconf.  */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h> /* for FILE */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef ZOBOVCONF_PACKAGE
/** @brief the program name */
#define ZOBOVCONF_PACKAGE "showZobov"
#endif

#ifndef ZOBOVCONF_VERSION
/** @brief the program version */
#define ZOBOVCONF_VERSION "0"
#endif

/** @brief Where the command line options are stored */
struct zobovConf_info
{
  const char *help_help; /**< @brief Print help and exit help description.  */
  const char *version_help; /**< @brief Print version and exit help description.  */
  char * desc_arg;	/**< @brief The description file name for the voids.  */
  char * desc_orig;	/**< @brief The description file name for the voids original value given at command line.  */
  const char *desc_help; /**< @brief The description file name for the voids help description.  */
  char * adj_arg;	/**< @brief Adjacent file name.  */
  char * adj_orig;	/**< @brief Adjacent file name original value given at command line.  */
  const char *adj_help; /**< @brief Adjacent file name help description.  */
  char * void_arg;	/**< @brief Void/zone bind filename.  */
  char * void_orig;	/**< @brief Void/zone bind filename original value given at command line.  */
  const char *void_help; /**< @brief Void/zone bind filename help description.  */
  int id_arg;	/**< @brief Void id to extract.  */
  char * id_orig;	/**< @brief Void id to extract original value given at command line.  */
  const char *id_help; /**< @brief Void id to extract help description.  */
  int sProba_flag;	/**< @brief Sort against probability (default=off).  */
  const char *sProba_help; /**< @brief Sort against probability help description.  */
  int sVol_flag;	/**< @brief Sort against volume (default=on).  */
  const char *sVol_help; /**< @brief Sort against volume help description.  */
  double mProba_arg;	/**< @brief Minimal probability to accept (default='0.0').  */
  char * mProba_orig;	/**< @brief Minimal probability to accept original value given at command line.  */
  const char *mProba_help; /**< @brief Minimal probability to accept help description.  */
  char * ramsesDir_arg;	/**< @brief Ramses base output directory.  */
  char * ramsesDir_orig;	/**< @brief Ramses base output directory original value given at command line.  */
  const char *ramsesDir_help; /**< @brief Ramses base output directory help description.  */
  int ramsesId_arg;	/**< @brief Ramses output id.  */
  char * ramsesId_orig;	/**< @brief Ramses output id original value given at command line.  */
  const char *ramsesId_help; /**< @brief Ramses output id help description.  */
  char * configFile_arg;	/**< @brief Configuration file.  */
  char * configFile_orig;	/**< @brief Configuration file original value given at command line.  */
  const char *configFile_help; /**< @brief Configuration file help description.  */
  int quiet_flag;	/**< @brief Quiet mode (default=off).  */
  const char *quiet_help; /**< @brief Quiet mode help description.  */
  char * move_arg;	/**< @brief Move the center by (x,y,z) (default='(0,0,0)').  */
  char * move_orig;	/**< @brief Move the center by (x,y,z) original value given at command line.  */
  const char *move_help; /**< @brief Move the center by (x,y,z) help description.  */
  int galax_flag;	/**< @brief Output is galax particles (default=off).  */
  const char *galax_help; /**< @brief Output is galax particles help description.  */
  char * output_arg;	/**< @brief Output file (default='voidDesc').  */
  char * output_orig;	/**< @brief Output file original value given at command line.  */
  const char *output_help; /**< @brief Output file help description.  */
  int interactive_flag;	/**< @brief Go in interactive mode (default=off).  */
  const char *interactive_help; /**< @brief Go in interactive mode help description.  */
  
  unsigned int help_given ;	/**< @brief Whether help was given.  */
  unsigned int version_given ;	/**< @brief Whether version was given.  */
  unsigned int desc_given ;	/**< @brief Whether desc was given.  */
  unsigned int adj_given ;	/**< @brief Whether adj was given.  */
  unsigned int void_given ;	/**< @brief Whether void was given.  */
  unsigned int id_given ;	/**< @brief Whether id was given.  */
  unsigned int sProba_given ;	/**< @brief Whether sProba was given.  */
  unsigned int sVol_given ;	/**< @brief Whether sVol was given.  */
  unsigned int mProba_given ;	/**< @brief Whether mProba was given.  */
  unsigned int ramsesDir_given ;	/**< @brief Whether ramsesDir was given.  */
  unsigned int ramsesId_given ;	/**< @brief Whether ramsesId was given.  */
  unsigned int configFile_given ;	/**< @brief Whether configFile was given.  */
  unsigned int quiet_given ;	/**< @brief Whether quiet was given.  */
  unsigned int move_given ;	/**< @brief Whether move was given.  */
  unsigned int galax_given ;	/**< @brief Whether galax was given.  */
  unsigned int output_given ;	/**< @brief Whether output was given.  */
  unsigned int interactive_given ;	/**< @brief Whether interactive was given.  */

} ;

/** @brief The additional parameters to pass to parser functions */
struct zobovConf_params
{
  int override; /**< @brief whether to override possibly already present options (default 0) */
  int initialize; /**< @brief whether to initialize the option structure zobovConf_info (default 1) */
  int check_required; /**< @brief whether to check that all required options were provided (default 1) */
  int check_ambiguity; /**< @brief whether to check for options already specified in the option structure zobovConf_info (default 0) */
  int print_errors; /**< @brief whether getopt_long should print an error message for a bad option (default 1) */
} ;

/** @brief the purpose string of the program */
extern const char *zobovConf_info_purpose;
/** @brief the usage string of the program */
extern const char *zobovConf_info_usage;
/** @brief all the lines making the help output */
extern const char *zobovConf_info_help[];

/**
 * The command line parser
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int zobovConf (int argc, char * const *argv,
  struct zobovConf_info *args_info);

/**
 * The command line parser (version with additional parameters - deprecated)
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @param override whether to override possibly already present options
 * @param initialize whether to initialize the option structure my_args_info
 * @param check_required whether to check that all required options were provided
 * @return 0 if everything went fine, NON 0 if an error took place
 * @deprecated use zobovConf_ext() instead
 */
int zobovConf2 (int argc, char * const *argv,
  struct zobovConf_info *args_info,
  int override, int initialize, int check_required);

/**
 * The command line parser (version with additional parameters)
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @param params additional parameters for the parser
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int zobovConf_ext (int argc, char * const *argv,
  struct zobovConf_info *args_info,
  struct zobovConf_params *params);

/**
 * Save the contents of the option struct into an already open FILE stream.
 * @param outfile the stream where to dump options
 * @param args_info the option struct to dump
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int zobovConf_dump(FILE *outfile,
  struct zobovConf_info *args_info);

/**
 * Save the contents of the option struct into a (text) file.
 * This file can be read by the config file parser (if generated by gengetopt)
 * @param filename the file where to save
 * @param args_info the option struct to save
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int zobovConf_file_save(const char *filename,
  struct zobovConf_info *args_info);

/**
 * Print the help
 */
void zobovConf_print_help(void);
/**
 * Print the version
 */
void zobovConf_print_version(void);

/**
 * Initializes all the fields a zobovConf_params structure 
 * to their default values
 * @param params the structure to initialize
 */
void zobovConf_params_init(struct zobovConf_params *params);

/**
 * Allocates dynamically a zobovConf_params structure and initializes
 * all its fields to their default values
 * @return the created and initialized zobovConf_params structure
 */
struct zobovConf_params *zobovConf_params_create(void);

/**
 * Initializes the passed zobovConf_info structure's fields
 * (also set default values for options that have a default)
 * @param args_info the structure to initialize
 */
void zobovConf_init (struct zobovConf_info *args_info);
/**
 * Deallocates the string fields of the zobovConf_info structure
 * (but does not deallocate the structure itself)
 * @param args_info the structure to deallocate
 */
void zobovConf_free (struct zobovConf_info *args_info);

/**
 * The config file parser (deprecated version)
 * @param filename the name of the config file
 * @param args_info the structure where option information will be stored
 * @param override whether to override possibly already present options
 * @param initialize whether to initialize the option structure my_args_info
 * @param check_required whether to check that all required options were provided
 * @return 0 if everything went fine, NON 0 if an error took place
 * @deprecated use zobovConf_config_file() instead
 */
int zobovConf_configfile (char * const filename,
  struct zobovConf_info *args_info,
  int override, int initialize, int check_required);

/**
 * The config file parser
 * @param filename the name of the config file
 * @param args_info the structure where option information will be stored
 * @param params additional parameters for the parser
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int zobovConf_config_file (char * const filename,
  struct zobovConf_info *args_info,
  struct zobovConf_params *params);

/**
 * Checks that all the required options were specified
 * @param args_info the structure to check
 * @param prog_name the name of the program that will be used to print
 *   possible errors
 * @return
 */
int zobovConf_required (struct zobovConf_info *args_info,
  const char *prog_name);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* ZOBOVCONF_H */
