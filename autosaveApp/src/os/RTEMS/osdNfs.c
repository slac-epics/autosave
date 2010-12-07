/***********************************************
 * osdNfs.c
 * 
 * Realize the RTEMS specified routines for NFS operation
 *
 * Created by: Zheqiao Geng, gengzq@slac.stanford.edu
 * Created on: Aug. 13, 2010
 * Description: Realize the basic function for NFS mount and dismount
 *
 * Modified by: Zheqiao Geng
 * Modified on: Dec 02, 2010
 * Description:
 *    1. set the initial value of save_restoreNFSOK to 0
 *    2. realize the checkHost routine to copy the IP address to the hostName string
 *       if the hostName string is empty
 * Note:
 *    a). If the user does not call the routine save_restoreSet_NFSHost(char *hostname, char *address)
 *        at his startup script, the NFS mounting functionalities will be disabled, and the NFS should
 *        be managed outside autosave
 *    b). If the user used it, all NFS functionalities including the remounting will be enabled 
 ***********************************************/
#include "osdNfs.h"

/**
 * Global variables
 */
int save_restoreNFSOK    = 0;  /* assume the NFS is not mounted at first, this will enable the program to try to mount
                                  the NFS at first. For some applications, NFS is not managed by autosave, this flag will be
				  automatically set to 1 if the file saving is successfull, because from that we know that the
				  NFS must be OK, similarly, the save_restoreIoErrors will be clean to zero at the same time  */
int save_restoreIoErrors = 0;  /* to accumulate the IO error numbers, when the number larger than threshold, remount NFS */

/**
 * copy the IP address to the host name if the host name is not set (for RTEMS)
 */
void checkHost(char *hostName, char *hostAddress)
{
    /* check the input parameters */
    /*if(!hostName || !hostName[0] || !hostAddress || !hostAddress[0]) return;*/
    
    /* host checking */
    /*if (gethostbyname(hostName) != NFS_SUCCESS) {
        (void)hostAdd(hostName, hostAddress);
    }*/
    /* Note: it seems that the routine of hostAdd is not supported by RTEMS. And because the nfsMount routine
             of RTEMS can accept both host name and IP address, so here we copy the address into the host name.
	     But be careful, in this case, the input of char*hostName and char*hostAddress must be a buffer pointer,
	     but not a constant string, the buffer size should be same in principle. So the routine of 
	     save_restoreSet_NFSHost(char *hostname, char *address) can be used in both ways:
	             save_restoreSet_NFSHost("myname", "192.168.2.1");
		     save_restoreSet_NFSHost("", "192.168.2.1");                                                
		     
             Further more, if the user want to use the hostName, the host name must be already registered! */
	     
    if(hostName && hostAddress[0])
        strcpy(hostName, hostAddress);	     	     
}

/**
 * Mount the NFS
 *
 * Pre conditions:
 *    Initialization has been done: rpcUdpInit() and nfsInit(smallPoolDepth, bigPoolDepth)
 *    Please note that when using CEXP to load the RTEMS modules, the initialization will be 
 *    done automatically
 *
 * Input:
 *    uidhost  - string. The NFS server and uid/gid, [<uid>'.'<gid>'@']<host>. Note better to use IP address
 *               with 'dot' notation for <host>
 *    path     - string. Absolute path on the NFS server
 *    mntpoint - string. Local path. Please note that if "mntpoint" does not exist, it will be created
 *
 * Output:
 *    See the definition of NFS operation error codes
 */
int mountFileSystem(char *uidhost, char *path, char *mntpoint)
{
    /* check the input parameters */
    if (!uidhost || !uidhost[0])   return NFS_INVALID_HOST;
    if (!path || !path[0])         return NFS_INVALID_PATH;
    if (!mntpoint || !mntpoint[0]) return NFS_INVALID_MNTPOINT;

    /* mount the file system */
    if (nfsMount(uidhost, path, mntpoint) == OK) {     /* 0 - succeed; -1 - failed */
        save_restoreNFSOK    = 1;
        save_restoreIoErrors = 0;                      /* clean the counter */
        return NFS_SUCCESS;
    } else {
        save_restoreNFSOK = 0;
        return NFS_FAILURE;
    }
}

/**
 * unmount the NFS
 *
 * Input:
 *    mntpoint - string. Local path. 
 *
 * Output:
 *    See the definition of NFS operation error codes
 */ 
int dismountFileSystem(char *mntpoint)
{
    /* check the input parameters */
    if (!mntpoint || !mntpoint[0]) return NFS_INVALID_MNTPOINT;

    /* unmount the file system */
    if (unmount(mntpoint) == OK) {                     /* 0 - succeed; -1 - failed */
        save_restoreNFSOK    = 0;
        return NFS_SUCCESS;
    } else {
        return NFS_FAILURE;
    }
}



