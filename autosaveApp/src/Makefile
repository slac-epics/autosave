TOP=../..

include $(TOP)/configure/CONFIG
#============================================
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#============================================

PROD_HOST += asVerify
asVerify_SRCS   += asVerify.c verify.c
asVerify_LIBS   += ca
asVerify_LIBS   += Com

#==================================================
# xxxRecord.h will be created from xxxRecord.dbd

#DBDINC += xxxRecord

# Trial version that uses dbLoadRecordsHookRegister.
#USR_CFLAGS += -DDBLOADRECORDSHOOKREGISTER

# ===================================================
# <name>.dbd will be created from <name>Include.dbd
# autosave.dbd is used for the test IOC application
# uncomment when building PROD_IOC = autosaveTest
#DBD += autosave.dbd
# ===================================================

# This is exported for use by external IOC applications
DBD += autosaveSupport.dbd

#include files
INC += osdNfs.h

#===================================================
# create library for linking will install in <lib>
#===================================================
LIBRARY_IOC += autosave

#os independent code
autosave_SRCS += dbrestore.c save_restore.c
autosave_SRCS += initHooks.c fGetDateStr.c
autosave_SRCS += configMenuSub.c verify.c

#os dependent code
autosave_SRCS += osdNfs.c

autosave_LIBS += $(EPICS_BASE_IOC_LIBS)

#=================================================================
# create munch file for dynamic loading will install in <bin>
#=================================================================
PROD_IOC = autosaveLib

# The PROD_IOC must include the registry routines for dynamic loading.
# <name>_registerRecordDeviceDriver.cpp will be created from <name>.dbd
autosaveLib_SRCS_DEFAULT += autosave_registerRecordDeviceDriver.cpp
autosaveLib_SRCS_DEFAULT += autosaveMain.cpp
autosaveLib_SRCS_vxWorks += -nil-

#The following adds support from base/src/vxWorks
autosaveLib_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

autosaveLib_LIBS += autosave
autosaveLib_LIBS += $(EPICS_BASE_IOC_LIBS)
#====================================================================

#=================================================================
# Create an IOC Application for testing within this module
# Please don't build the following IOC application PROD_IOC
# for production deployment
#=================================================================

#PROD_IOC = autosaveTest
# ======================================================================
# <name>_registerRecordDeviceDriver.cpp will be created from <name>.dbd
# =======================================================================

#autosaveTest_SRCS_DEFAULT += autosave_registerRecordDeviceDriver.cpp
#autosaveTest_SRCS_DEFAULT += autosaveMain.cpp
#autosaveTest_SRCS_vxWorks += -nil-

#The following adds support from base/src/vxWorks
#autosaveTest_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

#autosaveTest_LIBS += autosave
#autosaveTest_LIBS += $(EPICS_BASE_IOC_LIBS)
# ========================================================================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

