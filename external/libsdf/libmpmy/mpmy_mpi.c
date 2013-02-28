#ifdef _SWAMPI
#include <swampi.h>
#else
#include <mpi.h>
#endif
#include "mpmy_abnormal.h"

#include "Malloc.h"

#include "chn.h"
#include "mpmy.h"
#include "Assert.h"
#include "timers.h"
#include "Msgs.h"
#include "error.h"
#include "memfile.h"

struct comm_s {
    MPI_Request hndl;
    int inout;
};

static Chn commchn;
#define NCOMM 2048
#define IN 1
#define OUT 2

int MPMY_Isend(const void *buf, int cnt, int dest, int tag,
	       MPMY_Comm_request *reqp) {
    struct comm_s *comm = ChnAlloc(&commchn);

    Msgf(("Isend: buf=%p, cnt=%d, dest=%d, tag=%d\n",
	  buf, cnt, dest, tag));
    if (MPI_Isend((void *)buf, cnt, MPI_BYTE, dest, tag, MPI_COMM_WORLD,
		  &comm->hndl) != MPI_SUCCESS)
	Error("MPMY_Isend MPI_Isend failed\n");
    comm->inout = OUT;
    Msgf(("Isend: hndl=%ld\n", (long) comm->hndl));
    *reqp = comm;
    return MPMY_SUCCESS;
}

#if 0
#define HAVE_MPMY_IRSEND
int MPMY_Irsend(const void *buf, int cnt, int dest, int tag,
	       MPMY_Comm_request *reqp) {
    struct comm_s *comm = ChnAlloc(&commchn);

    Msgf(("Irsend: buf=%p, dest=%d, tag=%d\n",
	  buf, dest, tag));
    if (MPI_Irsend(buf, cnt, MPI_BYTE, dest, tag, MPI_COMM_WORLD,
		   &comm->hndl) != MPI_SUCCESS)
	Error("MPMY_Isend MPI_Irsend failed\n");
    comm->inout = OUT;
    Msgf(("Irsend: hndl=%d\n", (int) comm->hndl));
    *reqp = comm;
    return MPMY_SUCCESS;
}
#endif /* 0 */

int MPMY_Irecv(void *buf, int cnt, int src, int tag, MPMY_Comm_request *reqp) {
    struct comm_s *comm = ChnAlloc(&commchn);

    if (tag == MPMY_TAG_ANY) tag = MPI_ANY_TAG;
    if (src == MPMY_SOURCE_ANY) {
	src = MPI_ANY_SOURCE;
    } else if (src < 0 || src >= MPMY_Nproc()) {
	Error("Bad src (%d) in Irecv\n", src);
    }
    Msgf(("Irecv: buf=%p, src=%d, tag=%d\n",
	  buf, src, tag));
    if (MPI_Irecv(buf, cnt, MPI_BYTE, src, tag, MPI_COMM_WORLD,
		  &comm->hndl) != MPI_SUCCESS)
	Error("MPMY_Irecv MPI_Irecv failed\n");
    comm->inout = IN;
    Msgf(("Irecv: hndl=%ld\n", (long) comm->hndl));
    *reqp = comm;
    return MPMY_SUCCESS;
}

int MPMY_Test(MPMY_Comm_request req, int *flag, MPMY_Status *stat) {
    struct comm_s *comm = req;
    MPI_Status status;
    int cnt;
    int ret = 0;

    Msgf(("MPMY_Test hndl=%ld at %p\n",  (long) comm->hndl, &comm->hndl));
    if ((ret = MPI_Test(&comm->hndl, flag, &status)) != MPI_SUCCESS) {
      Error("MPMY_Test MPI_Test failed (%d), MPI_ERROR %d, hndl=%ld at %p, flag=%p, status=%p\n", 
	    ret, status.MPI_ERROR, (long)comm->hndl, &comm->hndl, flag, &status);
    }
    Msgf(("Tested (%s), %d\n", 
	  (comm->inout==IN)?"in":"out", *flag));
    if (*flag) {
	if(comm->inout == IN) {
	    MPI_Get_count(&status, MPI_BYTE, &cnt);
	    Msgf(("Recvd(T) from %d, tag %d, count: %d\n",
		  status.MPI_SOURCE, status.MPI_TAG, cnt));
	    if (stat) {
		stat->src = status.MPI_SOURCE;
		stat->tag = status.MPI_TAG;
		stat->count = cnt;
	    }
	}
	ChnFree(&commchn, comm);
    }
    return MPMY_SUCCESS;
}

#define HAVE_MPMY_WAIT
int MPMY_Wait(MPMY_Comm_request req, MPMY_Status *stat) {
    struct comm_s *comm = req;
    MPI_Status status;
    int cnt;

    Msgf(("Wait for %ld\n", (long) comm->hndl));
    if (MPI_Wait(&comm->hndl, &status) != MPI_SUCCESS)
      Error("MPMY_Wait MPI_Wait failed\n");
    Msgf(("Waited for (%s), deallocated\n", 
	  (comm->inout==IN)?"in":"out"));
    if(comm->inout == IN) {
	MPI_Get_count(&status, MPI_BYTE, &cnt);
	Msgf(("Recvd(W) from %d, tag %d, count: %d\n", 
	      status.MPI_SOURCE, status.MPI_TAG, cnt));
	if (stat) {
	    stat->src = status.MPI_SOURCE;
	    stat->tag = status.MPI_TAG;
	    stat->count = cnt;
	}
    }
    ChnFree(&commchn, comm);
    return MPMY_SUCCESS;
}

#define HAVE_MPMY_SHIFT
#define SHIFT_TAG 0x1492
int MPMY_Shift(int proc, void *recvbuf, int recvcnt, 
	       const void *sendbuf, int sendcnt, MPMY_Status *stat) {
    MPI_Status status;
    int count;

    Msgf(("Starting MPMY_Shift(proc=%d, recvcnt=%d, sendcnt=%d, recvbuf=%p, sendbuf=%p\n",
	  proc, recvcnt, sendcnt, recvbuf, sendbuf));

    if (MPI_Sendrecv((void *)sendbuf, sendcnt, MPI_BYTE, proc, SHIFT_TAG,
		     recvbuf, recvcnt, MPI_BYTE, proc, SHIFT_TAG,
		     MPI_COMM_WORLD, &status) != MPI_SUCCESS)
	Error("MPMY_Shift MPI_Sendrecv failed\n");
    MPI_Get_count(&status, MPI_BYTE, &count);
    Msgf(("MPMY_Shift done, received=%d\n", count));
    if (stat) {
	stat->count = count;
	stat->src = status.MPI_SOURCE;
	stat->tag = status.MPI_TAG;
    }
    return MPMY_SUCCESS;
}

int
Native_MPMY_Alltoall(void *sendbuf, int sendcount, MPMY_Datatype sendtype, 
	      void *recvbuf, int recvcount, MPMY_Datatype recvtype)
{
    MPI_Datatype st, rt;

    switch (sendtype){
    case MPMY_FLOAT:
	st = MPI_FLOAT;
	break;
    case MPMY_DOUBLE:
	st = MPI_DOUBLE;
	break;
    case MPMY_INT:
	st = MPI_INT;
	break;
    case MPMY_CHAR:
	st = MPI_CHAR;
	break;
    default:
	Error("No type match in alltoall\n");
    }
    switch (recvtype){
    case MPMY_FLOAT:
	rt = MPI_FLOAT;
	break;
    case MPMY_DOUBLE:
	rt = MPI_DOUBLE;
	break;
    case MPMY_INT:
	rt = MPI_INT;
	break;
    case MPMY_CHAR:
	rt = MPI_CHAR;
	break;
    default:
	Error("No type match in alltoall\n");
    }
    MPI_Alltoall(sendbuf, sendcount, st, 
		 recvbuf, recvcount, rt, MPI_COMM_WORLD);
    return MPMY_SUCCESS;
}

int
Native_MPMY_Alltoallv(void *sendbuf, int *sendcounts, int *sendoffsets, MPMY_Datatype sendtype, 
		      void *recvbuf, int *recvcounts, int *recvoffsets, MPMY_Datatype recvtype)
{
    MPI_Datatype st, rt;

    switch (sendtype){
    case MPMY_FLOAT:
	st = MPI_FLOAT;
	break;
    case MPMY_DOUBLE:
	st = MPI_DOUBLE;
	break;
    case MPMY_INT:
	st = MPI_INT;
	break;
    case MPMY_CHAR:
	st = MPI_CHAR;
	break;
    case MPMY_SHORT:
	st = MPI_SHORT;
	break;
    case MPMY_LONG:
	st = MPI_LONG;
	break;
    default:
	Error("No type match in alltoallv\n");
    }
    switch (recvtype){
    case MPMY_FLOAT:
	rt = MPI_FLOAT;
	break;
    case MPMY_DOUBLE:
	rt = MPI_DOUBLE;
	break;
    case MPMY_INT:
	rt = MPI_INT;
	break;
    case MPMY_CHAR:
	rt = MPI_CHAR;
	break;
    case MPMY_SHORT:
	rt = MPI_SHORT;
	break;
    case MPMY_LONG:
	rt = MPI_LONG;
	break;
    default:
	Error("No type match in alltoallv\n");
    }
    MPI_Alltoallv(sendbuf, sendcounts, sendoffsets, st, 
		  recvbuf, recvcounts, recvoffsets, rt, MPI_COMM_WORLD);
    return MPMY_SUCCESS;
}

int
Native_MPMY_Allgather(void *sendbuf, int sendcount, MPMY_Datatype type, void *recvbuf)
{
    MPI_Datatype st, rt;
    int recvcount = sendcount;

    switch (type){
    case MPMY_FLOAT:
	st = MPI_FLOAT;
	break;
    case MPMY_DOUBLE:
	st = MPI_DOUBLE;
	break;
    case MPMY_INT:
	st = MPI_INT;
	break;
    case MPMY_CHAR:
	st = MPI_CHAR;
	break;
    case MPMY_SHORT:
	st = MPI_SHORT;
	break;
    case MPMY_LONG:
	st = MPI_LONG;
	break;
    default:
	Error("No type match in allgather\n");
    }
    rt = st;
    MPI_Allgather(sendbuf, sendcount, st, 
		  recvbuf, recvcount, rt, MPI_COMM_WORLD);
    return MPMY_SUCCESS;
}

int
Native_MPMY_Allgatherv(void *sendbuf, int sendcount, MPMY_Datatype type, void *recvbuf,
		       int *rcounts, int *roffsets)
{
    MPI_Datatype st, rt;

    switch (type){
    case MPMY_FLOAT:
	st = MPI_FLOAT;
	break;
    case MPMY_DOUBLE:
	st = MPI_DOUBLE;
	break;
    case MPMY_INT:
	st = MPI_INT;
	break;
    case MPMY_CHAR:
	st = MPI_CHAR;
	break;
    case MPMY_SHORT:
	st = MPI_SHORT;
	break;
    case MPMY_LONG:
	st = MPI_LONG;
	break;
    default:
	Error("No type match in allgather\n");
    }
    rt = st;
    MPI_Allgatherv(sendbuf, sendcount, st, 
		   recvbuf, rcounts, roffsets, rt, MPI_COMM_WORLD);
    return MPMY_SUCCESS;
}


#define HAVE_MPMY_SYNC
int MPMY_Sync(void) {
    MPI_Barrier(MPI_COMM_WORLD);
    return MPMY_SUCCESS;
}

int MPMY_Init(int *argcp, char ***argvp) {
    ChnInit(&commchn, sizeof(struct comm_s), NCOMM, Realloc_f);
    ChnMoreMem(&commchn);	/* alloc now to prevent heap fragmentation later */
    if (MPI_Init(argcp, argvp) != MPI_SUCCESS)
	Error("MPMY_Init MPI_Init failed\n");
    if (MPI_Comm_size(MPI_COMM_WORLD, &_MPMY_nproc_) != MPI_SUCCESS)
	Error("MPMY_Init MPI_Comm_size failed\n");
    if (MPI_Comm_rank(MPI_COMM_WORLD, &_MPMY_procnum_) != MPI_SUCCESS)
	Error("MPMY_Init MPI_Comm_rank failed\n");
#ifdef PROCS_PER_NODE
    _MPMY_procs_per_node_ = PROCS_PER_NODE;
#else
    _MPMY_procs_per_node_ = 1;
#endif
    _MPMY_setup_absigs();
    MPMY_OnAbnormal(MPMY_SystemAbort);
    MPMY_OnAbnormal(MPMY_Abannounce);
    MPMY_OnAbnormal(PrintMemfile);
    _MPMY_initialized_ = 1;
    return MPMY_SUCCESS;
}

#define HAVE_MPMY_FINALIZE
int MPMY_Finalize(void){
  return (MPI_Finalize() == MPI_SUCCESS) ? MPMY_SUCCESS : MPMY_FAILED ;
}

#define HAVE_MPMY_FLICK
int MPMY_Flick(void){
    return MPMY_SUCCESS;
}

#define HAVE_MPMY_JOBREMAINING
int
MPMY_JobRemaining(void)
{
    /* returns -1 for failure, or if not a slurm job */
    return -1;
}


#ifdef USE_HWCLOCK
#include "timers_hwclock.c"
#endif

#ifdef USE_GETTIME
#include "timers_gettime.c"
#endif

#if !defined(USE_HWCLOCK) && !defined(USE_GETTIME)
#define HAVE_MPMY_TIMERS
#include "timers_mpi.c"
#endif

#if defined(__CM5__) || defined(_AIX) || defined(__AP1000__)
#define CANT_USE_ALARM
#endif
#if defined(__CM5__) || defined(__INTEL_SSD__)
#include "mpmy_pario.c"
#else
#if defined(USE_MPIIO)
#include "mpmy_mpiio.c"
#else
#include "mpmy_io.c"
#endif
#endif
#include "mpmy_abnormal.c"
#include "mpmy_generic.c"
