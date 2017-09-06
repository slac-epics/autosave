TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

#----------------------------------------------------
#  Optimization of db files using dbst (DEFAULT: NO)
#DB_OPT = YES

#----------------------------------------------------
# Create and install (or just install) into <top>/db
# databases, templates, substitutions like this

#DB += xxx.db
DB += save_restoreStatus.db
DB += configMenu.db
DB += SR_test.db

#----------------------------------------------------
# Create and install (or just install)
# Archive request files, templates, substitutions like this
ARCHIVE += archive_SR.sub-arch
ARCHIVE += archive_SR.tpl-arch

#----------------------------------------------------
# If <anyname>.db template is not named <anyname>*.template add
# <anyname>_template = <templatename>

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

