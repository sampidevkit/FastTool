#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/QWIIC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/QWIIC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=app/libcomp.c app/Application.c ../../Library/Bootloader/Bootloader.c ../../Library/Common/Button.c ../../Library/Common/Util.c ../../Library/Tasks/TaskManager.c ../../Library/Timer/SystemTick.c ../../Library/Timer/Wdt.c ../../Library/USB/USB_CDC_Debug.c mcc_generated_files/drivers/i2c_simple_master.c mcc_generated_files/drivers/i2c_master.c mcc_generated_files/drivers/i2c_types.c mcc_generated_files/usb/usb_descriptors.c mcc_generated_files/usb/usb_device_events.c mcc_generated_files/usb/usb_device.c mcc_generated_files/usb/usb_device_cdc.c mcc_generated_files/exceptions.c mcc_generated_files/clock.c mcc_generated_files/pin_manager.c mcc_generated_files/mcc.c mcc_generated_files/system.c mcc_generated_files/interrupt_manager.c mcc_generated_files/coretimer.c mcc_generated_files/i2c2_driver.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/app/libcomp.o ${OBJECTDIR}/app/Application.o ${OBJECTDIR}/_ext/1919251143/Bootloader.o ${OBJECTDIR}/_ext/814859167/Button.o ${OBJECTDIR}/_ext/814859167/Util.o ${OBJECTDIR}/_ext/1066804390/TaskManager.o ${OBJECTDIR}/_ext/1066572015/SystemTick.o ${OBJECTDIR}/_ext/1066572015/Wdt.o ${OBJECTDIR}/_ext/1610046384/USB_CDC_Debug.o ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.o ${OBJECTDIR}/mcc_generated_files/drivers/i2c_master.o ${OBJECTDIR}/mcc_generated_files/drivers/i2c_types.o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o ${OBJECTDIR}/mcc_generated_files/exceptions.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/coretimer.o ${OBJECTDIR}/mcc_generated_files/i2c2_driver.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/app/libcomp.o.d ${OBJECTDIR}/app/Application.o.d ${OBJECTDIR}/_ext/1919251143/Bootloader.o.d ${OBJECTDIR}/_ext/814859167/Button.o.d ${OBJECTDIR}/_ext/814859167/Util.o.d ${OBJECTDIR}/_ext/1066804390/TaskManager.o.d ${OBJECTDIR}/_ext/1066572015/SystemTick.o.d ${OBJECTDIR}/_ext/1066572015/Wdt.o.d ${OBJECTDIR}/_ext/1610046384/USB_CDC_Debug.o.d ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.o.d ${OBJECTDIR}/mcc_generated_files/drivers/i2c_master.o.d ${OBJECTDIR}/mcc_generated_files/drivers/i2c_types.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d ${OBJECTDIR}/mcc_generated_files/exceptions.o.d ${OBJECTDIR}/mcc_generated_files/clock.o.d ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/mcc_generated_files/mcc.o.d ${OBJECTDIR}/mcc_generated_files/system.o.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/mcc_generated_files/coretimer.o.d ${OBJECTDIR}/mcc_generated_files/i2c2_driver.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/app/libcomp.o ${OBJECTDIR}/app/Application.o ${OBJECTDIR}/_ext/1919251143/Bootloader.o ${OBJECTDIR}/_ext/814859167/Button.o ${OBJECTDIR}/_ext/814859167/Util.o ${OBJECTDIR}/_ext/1066804390/TaskManager.o ${OBJECTDIR}/_ext/1066572015/SystemTick.o ${OBJECTDIR}/_ext/1066572015/Wdt.o ${OBJECTDIR}/_ext/1610046384/USB_CDC_Debug.o ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.o ${OBJECTDIR}/mcc_generated_files/drivers/i2c_master.o ${OBJECTDIR}/mcc_generated_files/drivers/i2c_types.o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o ${OBJECTDIR}/mcc_generated_files/exceptions.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/coretimer.o ${OBJECTDIR}/mcc_generated_files/i2c2_driver.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=app/libcomp.c app/Application.c ../../Library/Bootloader/Bootloader.c ../../Library/Common/Button.c ../../Library/Common/Util.c ../../Library/Tasks/TaskManager.c ../../Library/Timer/SystemTick.c ../../Library/Timer/Wdt.c ../../Library/USB/USB_CDC_Debug.c mcc_generated_files/drivers/i2c_simple_master.c mcc_generated_files/drivers/i2c_master.c mcc_generated_files/drivers/i2c_types.c mcc_generated_files/usb/usb_descriptors.c mcc_generated_files/usb/usb_device_events.c mcc_generated_files/usb/usb_device.c mcc_generated_files/usb/usb_device_cdc.c mcc_generated_files/exceptions.c mcc_generated_files/clock.c mcc_generated_files/pin_manager.c mcc_generated_files/mcc.c mcc_generated_files/system.c mcc_generated_files/interrupt_manager.c mcc_generated_files/coretimer.c mcc_generated_files/i2c2_driver.c main.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

# The following macros may be used in the pre and post step lines
_/_=\\
ShExtension=.bat
Device=PIC32MM0064GPM028
ProjectDir="C:\Users\liemp\Downloads\FastTool\FTTAG64\QWIIC.X"
ProjectName=QWIIC
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\QWIIC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="QWIIC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/QWIIC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: [copy ${ImagePath} ".\lastbuild.${OUTPUT_SUFFIX}"]"
	@copy ${ImagePath} ".\lastbuild.${OUTPUT_SUFFIX}"
	@echo "--------------------------------------"

MP_PROCESSOR_OPTION=32MM0064GPM028
MP_LINKER_FILE_OPTION=,--script="..\..\Loadables\fttag64_app.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/app/libcomp.o: app/libcomp.c  .generated_files/flags/default/8080bbc46c516a62efaf4d89917982dd1e9559dc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/libcomp.o.d 
	@${RM} ${OBJECTDIR}/app/libcomp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/app/libcomp.o.d" -o ${OBJECTDIR}/app/libcomp.o app/libcomp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/app/Application.o: app/Application.c  .generated_files/flags/default/5badc67c7d182ce1d3e7b9c443ec065d32e2840c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/Application.o.d 
	@${RM} ${OBJECTDIR}/app/Application.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/app/Application.o.d" -o ${OBJECTDIR}/app/Application.o app/Application.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1919251143/Bootloader.o: ../../Library/Bootloader/Bootloader.c  .generated_files/flags/default/e892fba558d1b80ee64b57cb77c24963533c4642 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1919251143" 
	@${RM} ${OBJECTDIR}/_ext/1919251143/Bootloader.o.d 
	@${RM} ${OBJECTDIR}/_ext/1919251143/Bootloader.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/1919251143/Bootloader.o.d" -o ${OBJECTDIR}/_ext/1919251143/Bootloader.o ../../Library/Bootloader/Bootloader.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/814859167/Button.o: ../../Library/Common/Button.c  .generated_files/flags/default/53f511e949004aacdd7cc8edbb4de6baaaa32d74 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/814859167" 
	@${RM} ${OBJECTDIR}/_ext/814859167/Button.o.d 
	@${RM} ${OBJECTDIR}/_ext/814859167/Button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/814859167/Button.o.d" -o ${OBJECTDIR}/_ext/814859167/Button.o ../../Library/Common/Button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/814859167/Util.o: ../../Library/Common/Util.c  .generated_files/flags/default/a73d7fb4881c5d5b52206848136e8ea16a8ef8a7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/814859167" 
	@${RM} ${OBJECTDIR}/_ext/814859167/Util.o.d 
	@${RM} ${OBJECTDIR}/_ext/814859167/Util.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/814859167/Util.o.d" -o ${OBJECTDIR}/_ext/814859167/Util.o ../../Library/Common/Util.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1066804390/TaskManager.o: ../../Library/Tasks/TaskManager.c  .generated_files/flags/default/807dde4e60395cff9dc3682779a586a43858db83 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1066804390" 
	@${RM} ${OBJECTDIR}/_ext/1066804390/TaskManager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1066804390/TaskManager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/1066804390/TaskManager.o.d" -o ${OBJECTDIR}/_ext/1066804390/TaskManager.o ../../Library/Tasks/TaskManager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1066572015/SystemTick.o: ../../Library/Timer/SystemTick.c  .generated_files/flags/default/ac225f3c295339d73cc041cf69faed9b58ecc402 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1066572015" 
	@${RM} ${OBJECTDIR}/_ext/1066572015/SystemTick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1066572015/SystemTick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/1066572015/SystemTick.o.d" -o ${OBJECTDIR}/_ext/1066572015/SystemTick.o ../../Library/Timer/SystemTick.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1066572015/Wdt.o: ../../Library/Timer/Wdt.c  .generated_files/flags/default/2ef144a595779b1931718bb6f3ae64973549755 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1066572015" 
	@${RM} ${OBJECTDIR}/_ext/1066572015/Wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1066572015/Wdt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/1066572015/Wdt.o.d" -o ${OBJECTDIR}/_ext/1066572015/Wdt.o ../../Library/Timer/Wdt.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1610046384/USB_CDC_Debug.o: ../../Library/USB/USB_CDC_Debug.c  .generated_files/flags/default/e68e3bbda521373105be797878c2984b833633de .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1610046384" 
	@${RM} ${OBJECTDIR}/_ext/1610046384/USB_CDC_Debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1610046384/USB_CDC_Debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/1610046384/USB_CDC_Debug.o.d" -o ${OBJECTDIR}/_ext/1610046384/USB_CDC_Debug.o ../../Library/USB/USB_CDC_Debug.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.o: mcc_generated_files/drivers/i2c_simple_master.c  .generated_files/flags/default/d3a2c2070c14a59bddf64f39526f670e8fc17751 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/drivers" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.o.d" -o ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.o mcc_generated_files/drivers/i2c_simple_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/drivers/i2c_master.o: mcc_generated_files/drivers/i2c_master.c  .generated_files/flags/default/4e93d513a58e8df8a2bba4fc9198445d68723765 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/drivers" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/drivers/i2c_master.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/drivers/i2c_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/drivers/i2c_master.o.d" -o ${OBJECTDIR}/mcc_generated_files/drivers/i2c_master.o mcc_generated_files/drivers/i2c_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/drivers/i2c_types.o: mcc_generated_files/drivers/i2c_types.c  .generated_files/flags/default/6de3ccd286beee85319e7935717a077514635f7b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/drivers" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/drivers/i2c_types.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/drivers/i2c_types.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/drivers/i2c_types.o.d" -o ${OBJECTDIR}/mcc_generated_files/drivers/i2c_types.o mcc_generated_files/drivers/i2c_types.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o: mcc_generated_files/usb/usb_descriptors.c  .generated_files/flags/default/aa36cf59dc975d714d25fe0a929a1b7dcf775e26 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d" -o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o mcc_generated_files/usb/usb_descriptors.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o: mcc_generated_files/usb/usb_device_events.c  .generated_files/flags/default/e897d7d291584ef3a2a0583c2177c03ccadef1a1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d" -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o mcc_generated_files/usb/usb_device_events.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device.o: mcc_generated_files/usb/usb_device.c  .generated_files/flags/default/3e6176f2a9efeb82d56a3cc7376f5ec5b6902d5a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d" -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o mcc_generated_files/usb/usb_device.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o: mcc_generated_files/usb/usb_device_cdc.c  .generated_files/flags/default/3f6c4c3128b30c42f1cae183d54b8322ea100efc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d" -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o mcc_generated_files/usb/usb_device_cdc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/exceptions.o: mcc_generated_files/exceptions.c  .generated_files/flags/default/afb2b3aee8cae25961b18eaa28f8ddbe0670b92b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/exceptions.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/exceptions.o.d" -o ${OBJECTDIR}/mcc_generated_files/exceptions.o mcc_generated_files/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/flags/default/14e0b9705141490b65cac1eb77ddceb395caaf5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d" -o ${OBJECTDIR}/mcc_generated_files/clock.o mcc_generated_files/clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/flags/default/a2be52a948648bd4d2aa447f0a6f17ab5229746e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o mcc_generated_files/pin_manager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/flags/default/f67f75c8244f31fed1534d841f7ff42830f8a20a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d" -o ${OBJECTDIR}/mcc_generated_files/mcc.o mcc_generated_files/mcc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/flags/default/86a1e951f110eab6119cd100779fc31f8dee2f9e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d" -o ${OBJECTDIR}/mcc_generated_files/system.o mcc_generated_files/system.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/435ba8ee0237ab9ae890920bf2540905e4326c6a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o mcc_generated_files/interrupt_manager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/coretimer.o: mcc_generated_files/coretimer.c  .generated_files/flags/default/d8a0a2ee2bc0a8cb1613281995f6171c7eff657f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/coretimer.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/coretimer.o.d" -o ${OBJECTDIR}/mcc_generated_files/coretimer.o mcc_generated_files/coretimer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/i2c2_driver.o: mcc_generated_files/i2c2_driver.c  .generated_files/flags/default/a86654f37307ad4efea1489de86a4794f51aaa89 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c2_driver.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c2_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/i2c2_driver.o.d" -o ${OBJECTDIR}/mcc_generated_files/i2c2_driver.o mcc_generated_files/i2c2_driver.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/e9a7bccb9cb8b2f7cacbb42775cf2f6b675c054c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/app/libcomp.o: app/libcomp.c  .generated_files/flags/default/f41ae09ce93f43501275413e4c84e92db95a4f6f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/libcomp.o.d 
	@${RM} ${OBJECTDIR}/app/libcomp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/app/libcomp.o.d" -o ${OBJECTDIR}/app/libcomp.o app/libcomp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/app/Application.o: app/Application.c  .generated_files/flags/default/5c39f95488c9d087bb6183f4b9735d2d6d787bde .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/Application.o.d 
	@${RM} ${OBJECTDIR}/app/Application.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/app/Application.o.d" -o ${OBJECTDIR}/app/Application.o app/Application.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1919251143/Bootloader.o: ../../Library/Bootloader/Bootloader.c  .generated_files/flags/default/908e04f905e1f45bd879b485e49c14e6c6ce11e7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1919251143" 
	@${RM} ${OBJECTDIR}/_ext/1919251143/Bootloader.o.d 
	@${RM} ${OBJECTDIR}/_ext/1919251143/Bootloader.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/1919251143/Bootloader.o.d" -o ${OBJECTDIR}/_ext/1919251143/Bootloader.o ../../Library/Bootloader/Bootloader.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/814859167/Button.o: ../../Library/Common/Button.c  .generated_files/flags/default/d54b9b1d759871713e52379110729d7c5ac3450 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/814859167" 
	@${RM} ${OBJECTDIR}/_ext/814859167/Button.o.d 
	@${RM} ${OBJECTDIR}/_ext/814859167/Button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/814859167/Button.o.d" -o ${OBJECTDIR}/_ext/814859167/Button.o ../../Library/Common/Button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/814859167/Util.o: ../../Library/Common/Util.c  .generated_files/flags/default/ce0d67b76a9be349d3743d08a620c5d31b706546 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/814859167" 
	@${RM} ${OBJECTDIR}/_ext/814859167/Util.o.d 
	@${RM} ${OBJECTDIR}/_ext/814859167/Util.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/814859167/Util.o.d" -o ${OBJECTDIR}/_ext/814859167/Util.o ../../Library/Common/Util.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1066804390/TaskManager.o: ../../Library/Tasks/TaskManager.c  .generated_files/flags/default/a04b0fcd54e9921014cbef7cff5fe15fa846b491 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1066804390" 
	@${RM} ${OBJECTDIR}/_ext/1066804390/TaskManager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1066804390/TaskManager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/1066804390/TaskManager.o.d" -o ${OBJECTDIR}/_ext/1066804390/TaskManager.o ../../Library/Tasks/TaskManager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1066572015/SystemTick.o: ../../Library/Timer/SystemTick.c  .generated_files/flags/default/eb81677c5f1e72976e766d715e8199bb7fc2e605 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1066572015" 
	@${RM} ${OBJECTDIR}/_ext/1066572015/SystemTick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1066572015/SystemTick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/1066572015/SystemTick.o.d" -o ${OBJECTDIR}/_ext/1066572015/SystemTick.o ../../Library/Timer/SystemTick.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1066572015/Wdt.o: ../../Library/Timer/Wdt.c  .generated_files/flags/default/4987752f6078a4a12a45f0a6a4f64ddacc31b13e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1066572015" 
	@${RM} ${OBJECTDIR}/_ext/1066572015/Wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1066572015/Wdt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/1066572015/Wdt.o.d" -o ${OBJECTDIR}/_ext/1066572015/Wdt.o ../../Library/Timer/Wdt.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1610046384/USB_CDC_Debug.o: ../../Library/USB/USB_CDC_Debug.c  .generated_files/flags/default/cce50e90ca46b582884bb56d62e77c5d49557eb6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1610046384" 
	@${RM} ${OBJECTDIR}/_ext/1610046384/USB_CDC_Debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1610046384/USB_CDC_Debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/_ext/1610046384/USB_CDC_Debug.o.d" -o ${OBJECTDIR}/_ext/1610046384/USB_CDC_Debug.o ../../Library/USB/USB_CDC_Debug.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.o: mcc_generated_files/drivers/i2c_simple_master.c  .generated_files/flags/default/b48cbfb3e920dcc444be84fa4714a3dba7809a69 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/drivers" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.o.d" -o ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.o mcc_generated_files/drivers/i2c_simple_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/drivers/i2c_master.o: mcc_generated_files/drivers/i2c_master.c  .generated_files/flags/default/ce1b986c42b542aeedc60f4455925d6055245758 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/drivers" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/drivers/i2c_master.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/drivers/i2c_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/drivers/i2c_master.o.d" -o ${OBJECTDIR}/mcc_generated_files/drivers/i2c_master.o mcc_generated_files/drivers/i2c_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/drivers/i2c_types.o: mcc_generated_files/drivers/i2c_types.c  .generated_files/flags/default/eca65d8a35c0704543daee3e480e6ef4cac763bf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/drivers" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/drivers/i2c_types.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/drivers/i2c_types.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/drivers/i2c_types.o.d" -o ${OBJECTDIR}/mcc_generated_files/drivers/i2c_types.o mcc_generated_files/drivers/i2c_types.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o: mcc_generated_files/usb/usb_descriptors.c  .generated_files/flags/default/89435e61996e1b02b73dd6e1f51c583b0ddea066 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d" -o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o mcc_generated_files/usb/usb_descriptors.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o: mcc_generated_files/usb/usb_device_events.c  .generated_files/flags/default/eacd070516acb76f7fd09c8d6b976a941e0874ac .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d" -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o mcc_generated_files/usb/usb_device_events.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device.o: mcc_generated_files/usb/usb_device.c  .generated_files/flags/default/2db16698e97adb88f57790f1249d2a4bb5485de6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d" -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o mcc_generated_files/usb/usb_device.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o: mcc_generated_files/usb/usb_device_cdc.c  .generated_files/flags/default/f6768728c37ff6d7a553e26d49c2d7500dd7d325 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d" -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o mcc_generated_files/usb/usb_device_cdc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/exceptions.o: mcc_generated_files/exceptions.c  .generated_files/flags/default/99aca9c5c250ff43d744d8706d0ca2cb7ceccad3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/exceptions.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/exceptions.o.d" -o ${OBJECTDIR}/mcc_generated_files/exceptions.o mcc_generated_files/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/flags/default/9d4b7676be70410b044376db8fac2c9440ab585c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d" -o ${OBJECTDIR}/mcc_generated_files/clock.o mcc_generated_files/clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/flags/default/1a9fff721b406af826e0191871aaab2281b1fc67 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o mcc_generated_files/pin_manager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/flags/default/b7b644dd3fb232285c2e462c33233e20cd4fc61f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d" -o ${OBJECTDIR}/mcc_generated_files/mcc.o mcc_generated_files/mcc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/flags/default/f0e5217b56e7ad11e807ff430e0caa9f848df78d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d" -o ${OBJECTDIR}/mcc_generated_files/system.o mcc_generated_files/system.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/5d9983199ab885955f324ffcefef0aed0139a7fb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o mcc_generated_files/interrupt_manager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/coretimer.o: mcc_generated_files/coretimer.c  .generated_files/flags/default/4d19e7d003d930bb18147afd0cb7b36cc8fdabb8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/coretimer.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/coretimer.o.d" -o ${OBJECTDIR}/mcc_generated_files/coretimer.o mcc_generated_files/coretimer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/i2c2_driver.o: mcc_generated_files/i2c2_driver.c  .generated_files/flags/default/8b504d329f40750079f950f5b823a5532f10e5d3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c2_driver.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c2_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/i2c2_driver.o.d" -o ${OBJECTDIR}/mcc_generated_files/i2c2_driver.o mcc_generated_files/i2c2_driver.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/b07cb5b13b6ebcd4b0da42510cce24e03c5926e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -DUSB_CDC_DISABLE_LED -DDISABLE_LIBRARY_WARNING -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/QWIIC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../../Loadables/fttag64_app.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -o ${DISTDIR}/QWIIC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=4096,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--cref,--warn-section-align,--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/QWIIC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../Loadables/fttag64_app.ld ../../Loadables/fttag64_bld.hex
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -o ${DISTDIR}/QWIIC.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=4096,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--cref,--warn-section-align,--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/QWIIC.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
	@echo Normalizing hex file
	@"C:/Program Files/Microchip/MPLABX/v6.05/mplab_platform/platform/../mplab_ide/modules/../../bin/hexmate" --edf="C:/Program Files/Microchip/MPLABX/v6.05/mplab_platform/platform/../mplab_ide/modules/../../dat/en_msgs.txt" ${DISTDIR}/QWIIC.X.${IMAGE_TYPE}.hex -o${DISTDIR}/QWIIC.X.${IMAGE_TYPE}.hex

	@echo "Creating unified hex file"
	@"C:/Program Files/Microchip/MPLABX/v6.05/mplab_platform/platform/../mplab_ide/modules/../../bin/hexmate" --edf="C:/Program Files/Microchip/MPLABX/v6.05/mplab_platform/platform/../mplab_ide/modules/../../dat/en_msgs.txt" ${DISTDIR}/QWIIC.X.${IMAGE_TYPE}.hex ../../Loadables/fttag64_bld.hex -odist/${CND_CONF}/production/QWIIC.X.production.unified.hex

endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
