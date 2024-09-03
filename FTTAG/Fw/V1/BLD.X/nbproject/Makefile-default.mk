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
FINAL_IMAGE=${DISTDIR}/BLD.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/BLD.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=app/libcomp.c app/AppMain.c cfg/user_usb_device_descriptors.c ../Library/Bootloader/BLD_FileIO.c ../Library/Bootloader/BLD_Nvm_PIC32.c ../Library/Bootloader/Bootloader.c ../Library/Bootloader/asm.S ../Library/Common/UserFunctions.c ../Library/FileIO/files_lite.c ../Library/Kit/kit.c ../Library/Kit/kit_usb_device.c ../Library/Kit/kit_usb_device_msd.c ../Library/Programmer/HexParsing.c ../Library/System/TaskManager.c ../Library/System/TickTimer.c ../Library/System/Wdt.c ../Library/USB/usb_device_msd.c ../Library/USB/user_usb_device_events.c mcc_generated_files/memory/flash.c mcc_generated_files/usb/usb_device.c mcc_generated_files/coretimer.c mcc_generated_files/mcc.c mcc_generated_files/pin_manager.c mcc_generated_files/interrupt_manager.c mcc_generated_files/clock.c mcc_generated_files/system.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/app/libcomp.o ${OBJECTDIR}/app/AppMain.o ${OBJECTDIR}/cfg/user_usb_device_descriptors.o ${OBJECTDIR}/_ext/1037833288/BLD_FileIO.o ${OBJECTDIR}/_ext/1037833288/BLD_Nvm_PIC32.o ${OBJECTDIR}/_ext/1037833288/Bootloader.o ${OBJECTDIR}/_ext/1037833288/asm.o ${OBJECTDIR}/_ext/2045302226/UserFunctions.o ${OBJECTDIR}/_ext/1964994587/files_lite.o ${OBJECTDIR}/_ext/436485491/kit.o ${OBJECTDIR}/_ext/436485491/kit_usb_device.o ${OBJECTDIR}/_ext/436485491/kit_usb_device_msd.o ${OBJECTDIR}/_ext/1334186087/HexParsing.o ${OBJECTDIR}/_ext/1577815438/TaskManager.o ${OBJECTDIR}/_ext/1577815438/TickTimer.o ${OBJECTDIR}/_ext/1577815438/Wdt.o ${OBJECTDIR}/_ext/436494369/usb_device_msd.o ${OBJECTDIR}/_ext/436494369/user_usb_device_events.o ${OBJECTDIR}/mcc_generated_files/memory/flash.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o ${OBJECTDIR}/mcc_generated_files/coretimer.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/app/libcomp.o.d ${OBJECTDIR}/app/AppMain.o.d ${OBJECTDIR}/cfg/user_usb_device_descriptors.o.d ${OBJECTDIR}/_ext/1037833288/BLD_FileIO.o.d ${OBJECTDIR}/_ext/1037833288/BLD_Nvm_PIC32.o.d ${OBJECTDIR}/_ext/1037833288/Bootloader.o.d ${OBJECTDIR}/_ext/1037833288/asm.o.d ${OBJECTDIR}/_ext/2045302226/UserFunctions.o.d ${OBJECTDIR}/_ext/1964994587/files_lite.o.d ${OBJECTDIR}/_ext/436485491/kit.o.d ${OBJECTDIR}/_ext/436485491/kit_usb_device.o.d ${OBJECTDIR}/_ext/436485491/kit_usb_device_msd.o.d ${OBJECTDIR}/_ext/1334186087/HexParsing.o.d ${OBJECTDIR}/_ext/1577815438/TaskManager.o.d ${OBJECTDIR}/_ext/1577815438/TickTimer.o.d ${OBJECTDIR}/_ext/1577815438/Wdt.o.d ${OBJECTDIR}/_ext/436494369/usb_device_msd.o.d ${OBJECTDIR}/_ext/436494369/user_usb_device_events.o.d ${OBJECTDIR}/mcc_generated_files/memory/flash.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d ${OBJECTDIR}/mcc_generated_files/coretimer.o.d ${OBJECTDIR}/mcc_generated_files/mcc.o.d ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/mcc_generated_files/clock.o.d ${OBJECTDIR}/mcc_generated_files/system.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/app/libcomp.o ${OBJECTDIR}/app/AppMain.o ${OBJECTDIR}/cfg/user_usb_device_descriptors.o ${OBJECTDIR}/_ext/1037833288/BLD_FileIO.o ${OBJECTDIR}/_ext/1037833288/BLD_Nvm_PIC32.o ${OBJECTDIR}/_ext/1037833288/Bootloader.o ${OBJECTDIR}/_ext/1037833288/asm.o ${OBJECTDIR}/_ext/2045302226/UserFunctions.o ${OBJECTDIR}/_ext/1964994587/files_lite.o ${OBJECTDIR}/_ext/436485491/kit.o ${OBJECTDIR}/_ext/436485491/kit_usb_device.o ${OBJECTDIR}/_ext/436485491/kit_usb_device_msd.o ${OBJECTDIR}/_ext/1334186087/HexParsing.o ${OBJECTDIR}/_ext/1577815438/TaskManager.o ${OBJECTDIR}/_ext/1577815438/TickTimer.o ${OBJECTDIR}/_ext/1577815438/Wdt.o ${OBJECTDIR}/_ext/436494369/usb_device_msd.o ${OBJECTDIR}/_ext/436494369/user_usb_device_events.o ${OBJECTDIR}/mcc_generated_files/memory/flash.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o ${OBJECTDIR}/mcc_generated_files/coretimer.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=app/libcomp.c app/AppMain.c cfg/user_usb_device_descriptors.c ../Library/Bootloader/BLD_FileIO.c ../Library/Bootloader/BLD_Nvm_PIC32.c ../Library/Bootloader/Bootloader.c ../Library/Bootloader/asm.S ../Library/Common/UserFunctions.c ../Library/FileIO/files_lite.c ../Library/Kit/kit.c ../Library/Kit/kit_usb_device.c ../Library/Kit/kit_usb_device_msd.c ../Library/Programmer/HexParsing.c ../Library/System/TaskManager.c ../Library/System/TickTimer.c ../Library/System/Wdt.c ../Library/USB/usb_device_msd.c ../Library/USB/user_usb_device_events.c mcc_generated_files/memory/flash.c mcc_generated_files/usb/usb_device.c mcc_generated_files/coretimer.c mcc_generated_files/mcc.c mcc_generated_files/pin_manager.c mcc_generated_files/interrupt_manager.c mcc_generated_files/clock.c mcc_generated_files/system.c main.c



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
ProjectDir="C:\Working\Business\FT\FTTAG\Fw\V1\BLD.X"
ProjectName=BLD
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\BLD.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="BLD.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/BLD.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: [copy ${ImagePath} ".\fttag64_bld.${OUTPUT_SUFFIX}"]"
	@copy ${ImagePath} ".\fttag64_bld.${OUTPUT_SUFFIX}"
	@echo "--------------------------------------"

MP_PROCESSOR_OPTION=32MM0064GPM028
MP_LINKER_FILE_OPTION=,--script="..\Library\Bootloader\Linker\p32MM0064GPM028\Bld.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1037833288/asm.o: ../Library/Bootloader/asm.S  .generated_files/flags/default/c58b246e3c7e9d9b2b5e7e4b1a305c74ebc4dd0c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1037833288" 
	@${RM} ${OBJECTDIR}/_ext/1037833288/asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1037833288/asm.o 
	@${RM} ${OBJECTDIR}/_ext/1037833288/asm.o.ok ${OBJECTDIR}/_ext/1037833288/asm.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1037833288/asm.o.d"  -o ${OBJECTDIR}/_ext/1037833288/asm.o ../Library/Bootloader/asm.S  -DXPRJ_default=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1037833288/asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD4=1,-I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1037833288/asm.o.d" "${OBJECTDIR}/_ext/1037833288/asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1037833288/asm.o: ../Library/Bootloader/asm.S  .generated_files/flags/default/96dfa2e4a3936d23611b8f09af79968dcf669b7f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1037833288" 
	@${RM} ${OBJECTDIR}/_ext/1037833288/asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1037833288/asm.o 
	@${RM} ${OBJECTDIR}/_ext/1037833288/asm.o.ok ${OBJECTDIR}/_ext/1037833288/asm.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1037833288/asm.o.d"  -o ${OBJECTDIR}/_ext/1037833288/asm.o ../Library/Bootloader/asm.S  -DXPRJ_default=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1037833288/asm.o.asm.d",--gdwarf-2,-I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1037833288/asm.o.d" "${OBJECTDIR}/_ext/1037833288/asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/app/libcomp.o: app/libcomp.c  .generated_files/flags/default/af9c8ce705db13a22fe1dc876acee8cd4623fbfd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/libcomp.o.d 
	@${RM} ${OBJECTDIR}/app/libcomp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/app/libcomp.o.d" -o ${OBJECTDIR}/app/libcomp.o app/libcomp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/app/AppMain.o: app/AppMain.c  .generated_files/flags/default/70616a2602f1e2cf90d0890a5e85dad22477d0ac .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/AppMain.o.d 
	@${RM} ${OBJECTDIR}/app/AppMain.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/app/AppMain.o.d" -o ${OBJECTDIR}/app/AppMain.o app/AppMain.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/cfg/user_usb_device_descriptors.o: cfg/user_usb_device_descriptors.c  .generated_files/flags/default/de3f619fabe1eff57cdd1a75f5909490b11e138c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/cfg" 
	@${RM} ${OBJECTDIR}/cfg/user_usb_device_descriptors.o.d 
	@${RM} ${OBJECTDIR}/cfg/user_usb_device_descriptors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/cfg/user_usb_device_descriptors.o.d" -o ${OBJECTDIR}/cfg/user_usb_device_descriptors.o cfg/user_usb_device_descriptors.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1037833288/BLD_FileIO.o: ../Library/Bootloader/BLD_FileIO.c  .generated_files/flags/default/4ff1b63517e39b5db53a789a221b384e584133c6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1037833288" 
	@${RM} ${OBJECTDIR}/_ext/1037833288/BLD_FileIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1037833288/BLD_FileIO.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/1037833288/BLD_FileIO.o.d" -o ${OBJECTDIR}/_ext/1037833288/BLD_FileIO.o ../Library/Bootloader/BLD_FileIO.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1037833288/BLD_Nvm_PIC32.o: ../Library/Bootloader/BLD_Nvm_PIC32.c  .generated_files/flags/default/c944dcab0c14f95b56b2b5118b551adcd9ab288f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1037833288" 
	@${RM} ${OBJECTDIR}/_ext/1037833288/BLD_Nvm_PIC32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1037833288/BLD_Nvm_PIC32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/1037833288/BLD_Nvm_PIC32.o.d" -o ${OBJECTDIR}/_ext/1037833288/BLD_Nvm_PIC32.o ../Library/Bootloader/BLD_Nvm_PIC32.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1037833288/Bootloader.o: ../Library/Bootloader/Bootloader.c  .generated_files/flags/default/434d8439808fa502185fb6f50e23ed50a6b28fc4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1037833288" 
	@${RM} ${OBJECTDIR}/_ext/1037833288/Bootloader.o.d 
	@${RM} ${OBJECTDIR}/_ext/1037833288/Bootloader.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/1037833288/Bootloader.o.d" -o ${OBJECTDIR}/_ext/1037833288/Bootloader.o ../Library/Bootloader/Bootloader.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2045302226/UserFunctions.o: ../Library/Common/UserFunctions.c  .generated_files/flags/default/3e48dbf67abe8cf44a883c8e97ff3d0839075c14 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2045302226" 
	@${RM} ${OBJECTDIR}/_ext/2045302226/UserFunctions.o.d 
	@${RM} ${OBJECTDIR}/_ext/2045302226/UserFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/2045302226/UserFunctions.o.d" -o ${OBJECTDIR}/_ext/2045302226/UserFunctions.o ../Library/Common/UserFunctions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1964994587/files_lite.o: ../Library/FileIO/files_lite.c  .generated_files/flags/default/7a14ac4f9a67fa6cf26d181f85e503ac3f57e64 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1964994587" 
	@${RM} ${OBJECTDIR}/_ext/1964994587/files_lite.o.d 
	@${RM} ${OBJECTDIR}/_ext/1964994587/files_lite.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/1964994587/files_lite.o.d" -o ${OBJECTDIR}/_ext/1964994587/files_lite.o ../Library/FileIO/files_lite.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/436485491/kit.o: ../Library/Kit/kit.c  .generated_files/flags/default/bb00128bb39bacad687391f1410bc6f79ea56880 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/436485491" 
	@${RM} ${OBJECTDIR}/_ext/436485491/kit.o.d 
	@${RM} ${OBJECTDIR}/_ext/436485491/kit.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/436485491/kit.o.d" -o ${OBJECTDIR}/_ext/436485491/kit.o ../Library/Kit/kit.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/436485491/kit_usb_device.o: ../Library/Kit/kit_usb_device.c  .generated_files/flags/default/bb42f22b8c5bbbd3703c28453339d11681dfbad0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/436485491" 
	@${RM} ${OBJECTDIR}/_ext/436485491/kit_usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/436485491/kit_usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/436485491/kit_usb_device.o.d" -o ${OBJECTDIR}/_ext/436485491/kit_usb_device.o ../Library/Kit/kit_usb_device.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/436485491/kit_usb_device_msd.o: ../Library/Kit/kit_usb_device_msd.c  .generated_files/flags/default/ca28d2786bb4923482944d8a6107f5b7fd82dfdf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/436485491" 
	@${RM} ${OBJECTDIR}/_ext/436485491/kit_usb_device_msd.o.d 
	@${RM} ${OBJECTDIR}/_ext/436485491/kit_usb_device_msd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/436485491/kit_usb_device_msd.o.d" -o ${OBJECTDIR}/_ext/436485491/kit_usb_device_msd.o ../Library/Kit/kit_usb_device_msd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1334186087/HexParsing.o: ../Library/Programmer/HexParsing.c  .generated_files/flags/default/f433ba47dec0bd7fdc00c9d12bd607c418fa3951 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1334186087" 
	@${RM} ${OBJECTDIR}/_ext/1334186087/HexParsing.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334186087/HexParsing.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/1334186087/HexParsing.o.d" -o ${OBJECTDIR}/_ext/1334186087/HexParsing.o ../Library/Programmer/HexParsing.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1577815438/TaskManager.o: ../Library/System/TaskManager.c  .generated_files/flags/default/8040a79ee95168dfc45be4c6d29977070eb157e1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1577815438" 
	@${RM} ${OBJECTDIR}/_ext/1577815438/TaskManager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1577815438/TaskManager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/1577815438/TaskManager.o.d" -o ${OBJECTDIR}/_ext/1577815438/TaskManager.o ../Library/System/TaskManager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1577815438/TickTimer.o: ../Library/System/TickTimer.c  .generated_files/flags/default/5fd64d95264bad13a340a7ea356c777e88e81d9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1577815438" 
	@${RM} ${OBJECTDIR}/_ext/1577815438/TickTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1577815438/TickTimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/1577815438/TickTimer.o.d" -o ${OBJECTDIR}/_ext/1577815438/TickTimer.o ../Library/System/TickTimer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1577815438/Wdt.o: ../Library/System/Wdt.c  .generated_files/flags/default/c30640173e4c6c6335af0fb866aca6f0578224b5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1577815438" 
	@${RM} ${OBJECTDIR}/_ext/1577815438/Wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1577815438/Wdt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/1577815438/Wdt.o.d" -o ${OBJECTDIR}/_ext/1577815438/Wdt.o ../Library/System/Wdt.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/436494369/usb_device_msd.o: ../Library/USB/usb_device_msd.c  .generated_files/flags/default/a1f6cb7eb6a592b3d0c204141fe7b36a4b4258e2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/436494369" 
	@${RM} ${OBJECTDIR}/_ext/436494369/usb_device_msd.o.d 
	@${RM} ${OBJECTDIR}/_ext/436494369/usb_device_msd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/436494369/usb_device_msd.o.d" -o ${OBJECTDIR}/_ext/436494369/usb_device_msd.o ../Library/USB/usb_device_msd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/436494369/user_usb_device_events.o: ../Library/USB/user_usb_device_events.c  .generated_files/flags/default/aa55234bc54fc94955693f0721c4c4ad2db195f1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/436494369" 
	@${RM} ${OBJECTDIR}/_ext/436494369/user_usb_device_events.o.d 
	@${RM} ${OBJECTDIR}/_ext/436494369/user_usb_device_events.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/436494369/user_usb_device_events.o.d" -o ${OBJECTDIR}/_ext/436494369/user_usb_device_events.o ../Library/USB/user_usb_device_events.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/mcc_generated_files/memory/flash.o: mcc_generated_files/memory/flash.c  .generated_files/flags/default/5628f1e176eff029e29a7f2694b44867db3ddb4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/memory" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/memory/flash.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/memory/flash.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/memory/flash.o.d" -o ${OBJECTDIR}/mcc_generated_files/memory/flash.o mcc_generated_files/memory/flash.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device.o: mcc_generated_files/usb/usb_device.c  .generated_files/flags/default/54172469feb970c21ed4ef251c714681a987da98 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d" -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o mcc_generated_files/usb/usb_device.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/mcc_generated_files/coretimer.o: mcc_generated_files/coretimer.c  .generated_files/flags/default/438a8c93c8e4719ce1d9c326bc74702cd1ccd70 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/coretimer.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/coretimer.o.d" -o ${OBJECTDIR}/mcc_generated_files/coretimer.o mcc_generated_files/coretimer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/flags/default/fedfb483270dd3e08bb0f70a628e5f964bda281b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d" -o ${OBJECTDIR}/mcc_generated_files/mcc.o mcc_generated_files/mcc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/flags/default/37b301fd646a11c9d6757cbef2c7bfead5afcd50 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o mcc_generated_files/pin_manager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/abdfa899781ea743d5cd41132a36312349b9a6b7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o mcc_generated_files/interrupt_manager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/flags/default/2452659c7d2344879aacd291790fa49958d0d14e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d" -o ${OBJECTDIR}/mcc_generated_files/clock.o mcc_generated_files/clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/flags/default/3452d813dab83aee88b62a1954eae3f45c5dbc62 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d" -o ${OBJECTDIR}/mcc_generated_files/system.o mcc_generated_files/system.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/c3364556420d922aef545bcf869dd60211852e60 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
else
${OBJECTDIR}/app/libcomp.o: app/libcomp.c  .generated_files/flags/default/3424728047c61d2ee6c007ba0dd51e2b1e84a7fa .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/libcomp.o.d 
	@${RM} ${OBJECTDIR}/app/libcomp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/app/libcomp.o.d" -o ${OBJECTDIR}/app/libcomp.o app/libcomp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/app/AppMain.o: app/AppMain.c  .generated_files/flags/default/5ae269f8fad3c258c9fd62e397c06c630a54d0b8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/AppMain.o.d 
	@${RM} ${OBJECTDIR}/app/AppMain.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/app/AppMain.o.d" -o ${OBJECTDIR}/app/AppMain.o app/AppMain.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/cfg/user_usb_device_descriptors.o: cfg/user_usb_device_descriptors.c  .generated_files/flags/default/ab07d582e98c925b3968a49aedcffb009f04ca7d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/cfg" 
	@${RM} ${OBJECTDIR}/cfg/user_usb_device_descriptors.o.d 
	@${RM} ${OBJECTDIR}/cfg/user_usb_device_descriptors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/cfg/user_usb_device_descriptors.o.d" -o ${OBJECTDIR}/cfg/user_usb_device_descriptors.o cfg/user_usb_device_descriptors.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1037833288/BLD_FileIO.o: ../Library/Bootloader/BLD_FileIO.c  .generated_files/flags/default/16f616da2c087dd0490117fd90334ae7c0137c3b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1037833288" 
	@${RM} ${OBJECTDIR}/_ext/1037833288/BLD_FileIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1037833288/BLD_FileIO.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/1037833288/BLD_FileIO.o.d" -o ${OBJECTDIR}/_ext/1037833288/BLD_FileIO.o ../Library/Bootloader/BLD_FileIO.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1037833288/BLD_Nvm_PIC32.o: ../Library/Bootloader/BLD_Nvm_PIC32.c  .generated_files/flags/default/3f0b1b6e1d3432d897beca9c0cb3e4ee800eb73b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1037833288" 
	@${RM} ${OBJECTDIR}/_ext/1037833288/BLD_Nvm_PIC32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1037833288/BLD_Nvm_PIC32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/1037833288/BLD_Nvm_PIC32.o.d" -o ${OBJECTDIR}/_ext/1037833288/BLD_Nvm_PIC32.o ../Library/Bootloader/BLD_Nvm_PIC32.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1037833288/Bootloader.o: ../Library/Bootloader/Bootloader.c  .generated_files/flags/default/d101534736e7216ac2d81cf803b96f7c47a17c4a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1037833288" 
	@${RM} ${OBJECTDIR}/_ext/1037833288/Bootloader.o.d 
	@${RM} ${OBJECTDIR}/_ext/1037833288/Bootloader.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/1037833288/Bootloader.o.d" -o ${OBJECTDIR}/_ext/1037833288/Bootloader.o ../Library/Bootloader/Bootloader.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2045302226/UserFunctions.o: ../Library/Common/UserFunctions.c  .generated_files/flags/default/22ca1febfffc7c5a8a2c5d71fd06ad8b0d740913 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2045302226" 
	@${RM} ${OBJECTDIR}/_ext/2045302226/UserFunctions.o.d 
	@${RM} ${OBJECTDIR}/_ext/2045302226/UserFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/2045302226/UserFunctions.o.d" -o ${OBJECTDIR}/_ext/2045302226/UserFunctions.o ../Library/Common/UserFunctions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1964994587/files_lite.o: ../Library/FileIO/files_lite.c  .generated_files/flags/default/c54d960c3e33586666291222ace5a51d8d3631e9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1964994587" 
	@${RM} ${OBJECTDIR}/_ext/1964994587/files_lite.o.d 
	@${RM} ${OBJECTDIR}/_ext/1964994587/files_lite.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/1964994587/files_lite.o.d" -o ${OBJECTDIR}/_ext/1964994587/files_lite.o ../Library/FileIO/files_lite.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/436485491/kit.o: ../Library/Kit/kit.c  .generated_files/flags/default/ece47209e7777567e7188779162e390623e75a97 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/436485491" 
	@${RM} ${OBJECTDIR}/_ext/436485491/kit.o.d 
	@${RM} ${OBJECTDIR}/_ext/436485491/kit.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/436485491/kit.o.d" -o ${OBJECTDIR}/_ext/436485491/kit.o ../Library/Kit/kit.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/436485491/kit_usb_device.o: ../Library/Kit/kit_usb_device.c  .generated_files/flags/default/976e36a497609b254ff4fff3598ad9c8ddcbdb3f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/436485491" 
	@${RM} ${OBJECTDIR}/_ext/436485491/kit_usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/436485491/kit_usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/436485491/kit_usb_device.o.d" -o ${OBJECTDIR}/_ext/436485491/kit_usb_device.o ../Library/Kit/kit_usb_device.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/436485491/kit_usb_device_msd.o: ../Library/Kit/kit_usb_device_msd.c  .generated_files/flags/default/11b14e543948df6a0a81d3b39f0cb38a7e0376c5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/436485491" 
	@${RM} ${OBJECTDIR}/_ext/436485491/kit_usb_device_msd.o.d 
	@${RM} ${OBJECTDIR}/_ext/436485491/kit_usb_device_msd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/436485491/kit_usb_device_msd.o.d" -o ${OBJECTDIR}/_ext/436485491/kit_usb_device_msd.o ../Library/Kit/kit_usb_device_msd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1334186087/HexParsing.o: ../Library/Programmer/HexParsing.c  .generated_files/flags/default/a5a55ac428a3f9107535517e7a9d9f06b831a6bd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1334186087" 
	@${RM} ${OBJECTDIR}/_ext/1334186087/HexParsing.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334186087/HexParsing.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/1334186087/HexParsing.o.d" -o ${OBJECTDIR}/_ext/1334186087/HexParsing.o ../Library/Programmer/HexParsing.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1577815438/TaskManager.o: ../Library/System/TaskManager.c  .generated_files/flags/default/665e5ef41e9fc33457d7f4615f19b6ecf1ee22ce .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1577815438" 
	@${RM} ${OBJECTDIR}/_ext/1577815438/TaskManager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1577815438/TaskManager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/1577815438/TaskManager.o.d" -o ${OBJECTDIR}/_ext/1577815438/TaskManager.o ../Library/System/TaskManager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1577815438/TickTimer.o: ../Library/System/TickTimer.c  .generated_files/flags/default/914177aaf14469a70ab11d78fbf98dc49814bcc0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1577815438" 
	@${RM} ${OBJECTDIR}/_ext/1577815438/TickTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1577815438/TickTimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/1577815438/TickTimer.o.d" -o ${OBJECTDIR}/_ext/1577815438/TickTimer.o ../Library/System/TickTimer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1577815438/Wdt.o: ../Library/System/Wdt.c  .generated_files/flags/default/2088fbc98d219df4714b04cff87a57090346f8f5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1577815438" 
	@${RM} ${OBJECTDIR}/_ext/1577815438/Wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1577815438/Wdt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/1577815438/Wdt.o.d" -o ${OBJECTDIR}/_ext/1577815438/Wdt.o ../Library/System/Wdt.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/436494369/usb_device_msd.o: ../Library/USB/usb_device_msd.c  .generated_files/flags/default/66c37d22b2a7f04e23830b4972fb7c53597f2850 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/436494369" 
	@${RM} ${OBJECTDIR}/_ext/436494369/usb_device_msd.o.d 
	@${RM} ${OBJECTDIR}/_ext/436494369/usb_device_msd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/436494369/usb_device_msd.o.d" -o ${OBJECTDIR}/_ext/436494369/usb_device_msd.o ../Library/USB/usb_device_msd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/436494369/user_usb_device_events.o: ../Library/USB/user_usb_device_events.c  .generated_files/flags/default/a4f94a7d1869a43e1f35759e7b65d5c12f7e5469 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/436494369" 
	@${RM} ${OBJECTDIR}/_ext/436494369/user_usb_device_events.o.d 
	@${RM} ${OBJECTDIR}/_ext/436494369/user_usb_device_events.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/_ext/436494369/user_usb_device_events.o.d" -o ${OBJECTDIR}/_ext/436494369/user_usb_device_events.o ../Library/USB/user_usb_device_events.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/mcc_generated_files/memory/flash.o: mcc_generated_files/memory/flash.c  .generated_files/flags/default/5ebc2a4a818d39d1e52dab8d3b8091afd03802c7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/memory" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/memory/flash.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/memory/flash.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/memory/flash.o.d" -o ${OBJECTDIR}/mcc_generated_files/memory/flash.o mcc_generated_files/memory/flash.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device.o: mcc_generated_files/usb/usb_device.c  .generated_files/flags/default/f382634ef125115fb91de115ab54a8f6e80a1dfc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d" -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o mcc_generated_files/usb/usb_device.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/mcc_generated_files/coretimer.o: mcc_generated_files/coretimer.c  .generated_files/flags/default/fe48f04410e90ce58bdd6823547227d23687653c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/coretimer.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/coretimer.o.d" -o ${OBJECTDIR}/mcc_generated_files/coretimer.o mcc_generated_files/coretimer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/flags/default/29d2d381a4c2f725a28143642c37621dc451c842 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d" -o ${OBJECTDIR}/mcc_generated_files/mcc.o mcc_generated_files/mcc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/flags/default/5580b9631156bc9ee142dcb738e9f71be4e530b7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o mcc_generated_files/pin_manager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/7c3e68b2c83f0db9760f7869685bc50405f96699 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o mcc_generated_files/interrupt_manager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/flags/default/68b078fff54a242bc26fa7b6ff6ea47efc62158 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d" -o ${OBJECTDIR}/mcc_generated_files/clock.o mcc_generated_files/clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/flags/default/f816abd8e7c09db15f7b858cf77aca72f17a2f29 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d" -o ${OBJECTDIR}/mcc_generated_files/system.o mcc_generated_files/system.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/f07568943079ac93b14ba3c789c7df90fd95afbb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"mcc_generated_files/usb" -I"../Library" -I"../Library/USB" -ffunction-sections -fdata-sections -O2 -fno-common -D__USB_DESCRIPTORS_C -DCOMMON_LIB_CFG -DUSBCFG_H -DUSBGEN_H -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/BLD.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../Library/Bootloader/Linker/p32MM0064GPM028/Bld.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_ICD4=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/BLD.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC016FF -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_ICD4=1,--defsym=_min_heap_size=4096,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml 
	
else
${DISTDIR}/BLD.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../Library/Bootloader/Linker/p32MM0064GPM028/Bld.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/BLD.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=4096,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml 
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/BLD.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
	@echo Normalizing hex file
	@"C:/Program Files/Microchip/MPLABX/v6.05/mplab_platform/platform/../mplab_ide/modules/../../bin/hexmate" --edf="C:/Program Files/Microchip/MPLABX/v6.05/mplab_platform/platform/../mplab_ide/modules/../../dat/en_msgs.txt" ${DISTDIR}/BLD.X.${IMAGE_TYPE}.hex -o${DISTDIR}/BLD.X.${IMAGE_TYPE}.hex

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
