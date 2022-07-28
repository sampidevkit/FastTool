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
FINAL_IMAGE=${DISTDIR}/USB_CDC_UART.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/USB_CDC_UART.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=app/libcomp.c app/Application.c ../../Library/Bootloader/Bootloader.c ../../Library/Common/Button.c ../../Library/Timer/SystemTick.c ../../Library/USB/USB_CDC_UART.c mcc_generated_files/usb/usb_descriptors.c mcc_generated_files/usb/usb_device_events.c mcc_generated_files/usb/usb_device.c mcc_generated_files/usb/usb_device_cdc.c mcc_generated_files/exceptions.c mcc_generated_files/clock.c mcc_generated_files/pin_manager.c mcc_generated_files/mcc.c mcc_generated_files/system.c mcc_generated_files/interrupt_manager.c mcc_generated_files/coretimer.c mcc_generated_files/uart2.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/app/libcomp.o ${OBJECTDIR}/app/Application.o ${OBJECTDIR}/_ext/1919251143/Bootloader.o ${OBJECTDIR}/_ext/814859167/Button.o ${OBJECTDIR}/_ext/1066572015/SystemTick.o ${OBJECTDIR}/_ext/1610046384/USB_CDC_UART.o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o ${OBJECTDIR}/mcc_generated_files/exceptions.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/coretimer.o ${OBJECTDIR}/mcc_generated_files/uart2.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/app/libcomp.o.d ${OBJECTDIR}/app/Application.o.d ${OBJECTDIR}/_ext/1919251143/Bootloader.o.d ${OBJECTDIR}/_ext/814859167/Button.o.d ${OBJECTDIR}/_ext/1066572015/SystemTick.o.d ${OBJECTDIR}/_ext/1610046384/USB_CDC_UART.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d ${OBJECTDIR}/mcc_generated_files/exceptions.o.d ${OBJECTDIR}/mcc_generated_files/clock.o.d ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/mcc_generated_files/mcc.o.d ${OBJECTDIR}/mcc_generated_files/system.o.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/mcc_generated_files/coretimer.o.d ${OBJECTDIR}/mcc_generated_files/uart2.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/app/libcomp.o ${OBJECTDIR}/app/Application.o ${OBJECTDIR}/_ext/1919251143/Bootloader.o ${OBJECTDIR}/_ext/814859167/Button.o ${OBJECTDIR}/_ext/1066572015/SystemTick.o ${OBJECTDIR}/_ext/1610046384/USB_CDC_UART.o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o ${OBJECTDIR}/mcc_generated_files/exceptions.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/coretimer.o ${OBJECTDIR}/mcc_generated_files/uart2.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=app/libcomp.c app/Application.c ../../Library/Bootloader/Bootloader.c ../../Library/Common/Button.c ../../Library/Timer/SystemTick.c ../../Library/USB/USB_CDC_UART.c mcc_generated_files/usb/usb_descriptors.c mcc_generated_files/usb/usb_device_events.c mcc_generated_files/usb/usb_device.c mcc_generated_files/usb/usb_device_cdc.c mcc_generated_files/exceptions.c mcc_generated_files/clock.c mcc_generated_files/pin_manager.c mcc_generated_files/mcc.c mcc_generated_files/system.c mcc_generated_files/interrupt_manager.c mcc_generated_files/coretimer.c mcc_generated_files/uart2.c main.c



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
ProjectDir="F:\Git\SAMPI\FastTool\TAG\FTTAG64\USB_CDC_UART.X"
ProjectName=USB_CDC_UART
ConfName=default
ImagePath="${DISTDIR}\USB_CDC_UART.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="${DISTDIR}"
ImageName="USB_CDC_UART.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/USB_CDC_UART.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: [copy ${ImagePath} ".\lastbuild.${OUTPUT_SUFFIX}"]"
	@copy ${ImagePath} ".\lastbuild.${OUTPUT_SUFFIX}"
	@echo "--------------------------------------"

MP_PROCESSOR_OPTION=32MM0064GPM028
MP_LINKER_FILE_OPTION=,--script="..\..\Library\Bootloader\fttag64_app.ld"
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
${OBJECTDIR}/app/libcomp.o: app/libcomp.c  .generated_files/flags/default/c981661f0c0373ef5e132eb772831010e80184f2 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/libcomp.o.d 
	@${RM} ${OBJECTDIR}/app/libcomp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/app/libcomp.o.d" -o ${OBJECTDIR}/app/libcomp.o app/libcomp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/app/Application.o: app/Application.c  .generated_files/flags/default/b00a992b17d68335fe1953ef0cb313e867369086 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/Application.o.d 
	@${RM} ${OBJECTDIR}/app/Application.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/app/Application.o.d" -o ${OBJECTDIR}/app/Application.o app/Application.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1919251143/Bootloader.o: ../../Library/Bootloader/Bootloader.c  .generated_files/flags/default/427a71c431ff5fb19e19fc025c4c82c593dd769c .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/1919251143" 
	@${RM} ${OBJECTDIR}/_ext/1919251143/Bootloader.o.d 
	@${RM} ${OBJECTDIR}/_ext/1919251143/Bootloader.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/1919251143/Bootloader.o.d" -o ${OBJECTDIR}/_ext/1919251143/Bootloader.o ../../Library/Bootloader/Bootloader.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/814859167/Button.o: ../../Library/Common/Button.c  .generated_files/flags/default/828ccf8c077d512ddf5b740caa825751cd538628 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/814859167" 
	@${RM} ${OBJECTDIR}/_ext/814859167/Button.o.d 
	@${RM} ${OBJECTDIR}/_ext/814859167/Button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/814859167/Button.o.d" -o ${OBJECTDIR}/_ext/814859167/Button.o ../../Library/Common/Button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1066572015/SystemTick.o: ../../Library/Timer/SystemTick.c  .generated_files/flags/default/244d986842ca34efacd0a2a34380756631b6fa35 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/1066572015" 
	@${RM} ${OBJECTDIR}/_ext/1066572015/SystemTick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1066572015/SystemTick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/1066572015/SystemTick.o.d" -o ${OBJECTDIR}/_ext/1066572015/SystemTick.o ../../Library/Timer/SystemTick.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1610046384/USB_CDC_UART.o: ../../Library/USB/USB_CDC_UART.c  .generated_files/flags/default/9fc9930e566c25e7733e4db21fc336c3c696c871 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/1610046384" 
	@${RM} ${OBJECTDIR}/_ext/1610046384/USB_CDC_UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1610046384/USB_CDC_UART.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/1610046384/USB_CDC_UART.o.d" -o ${OBJECTDIR}/_ext/1610046384/USB_CDC_UART.o ../../Library/USB/USB_CDC_UART.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o: mcc_generated_files/usb/usb_descriptors.c  .generated_files/flags/default/bf80b74922b3fa47b592c350d5613beaecc58205 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d" -o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o mcc_generated_files/usb/usb_descriptors.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o: mcc_generated_files/usb/usb_device_events.c  .generated_files/flags/default/a31cb55f84128ff333644609efff84cd8ddabb20 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d" -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o mcc_generated_files/usb/usb_device_events.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device.o: mcc_generated_files/usb/usb_device.c  .generated_files/flags/default/1ae8472ec315e3953fa477009f5147ab4a1bd6c .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d" -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o mcc_generated_files/usb/usb_device.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o: mcc_generated_files/usb/usb_device_cdc.c  .generated_files/flags/default/1ac679aa3b2753971acbc79d2892ab67702ddbf7 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d" -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o mcc_generated_files/usb/usb_device_cdc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/exceptions.o: mcc_generated_files/exceptions.c  .generated_files/flags/default/c88fa2ee5361c34cc005dce4ce7ef3ae8987988f .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/exceptions.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/exceptions.o.d" -o ${OBJECTDIR}/mcc_generated_files/exceptions.o mcc_generated_files/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/flags/default/beb6c2a18d7ee214c550007098314fe4956c024c .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d" -o ${OBJECTDIR}/mcc_generated_files/clock.o mcc_generated_files/clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/flags/default/f388cbafc07b46c6d6803cefc9342f916d3abfd3 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o mcc_generated_files/pin_manager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/flags/default/c5e574e27f5056b0a49eed20bf06b68a9f59db52 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d" -o ${OBJECTDIR}/mcc_generated_files/mcc.o mcc_generated_files/mcc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/flags/default/5a503d065d3603d6881fa2569ee65c841118a9f3 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d" -o ${OBJECTDIR}/mcc_generated_files/system.o mcc_generated_files/system.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/e1b3eb85032f6ba9b7e8763596f4af8be847ae37 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o mcc_generated_files/interrupt_manager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/coretimer.o: mcc_generated_files/coretimer.c  .generated_files/flags/default/d72a62288904192fdceaf0ac3428dd9743007441 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/coretimer.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/coretimer.o.d" -o ${OBJECTDIR}/mcc_generated_files/coretimer.o mcc_generated_files/coretimer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart2.o: mcc_generated_files/uart2.c  .generated_files/flags/default/5196ed5168ef0333915fcff045e2737bfa99103a .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart2.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart2.o mcc_generated_files/uart2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/154a34eff6b56956621236cdd75160930be63b4a .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/app/libcomp.o: app/libcomp.c  .generated_files/flags/default/2597ed24a167ff7a462d69ad7f235305025ee143 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/libcomp.o.d 
	@${RM} ${OBJECTDIR}/app/libcomp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/app/libcomp.o.d" -o ${OBJECTDIR}/app/libcomp.o app/libcomp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/app/Application.o: app/Application.c  .generated_files/flags/default/ec06c6e71249b9e7db5090c504cdd1e346696709 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/Application.o.d 
	@${RM} ${OBJECTDIR}/app/Application.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/app/Application.o.d" -o ${OBJECTDIR}/app/Application.o app/Application.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1919251143/Bootloader.o: ../../Library/Bootloader/Bootloader.c  .generated_files/flags/default/7599c0db81eb4313c1bd6460ee00f694f561134 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/1919251143" 
	@${RM} ${OBJECTDIR}/_ext/1919251143/Bootloader.o.d 
	@${RM} ${OBJECTDIR}/_ext/1919251143/Bootloader.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/1919251143/Bootloader.o.d" -o ${OBJECTDIR}/_ext/1919251143/Bootloader.o ../../Library/Bootloader/Bootloader.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/814859167/Button.o: ../../Library/Common/Button.c  .generated_files/flags/default/7836ff6a9e8e8dde693883c5ea022eba2df46f70 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/814859167" 
	@${RM} ${OBJECTDIR}/_ext/814859167/Button.o.d 
	@${RM} ${OBJECTDIR}/_ext/814859167/Button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/814859167/Button.o.d" -o ${OBJECTDIR}/_ext/814859167/Button.o ../../Library/Common/Button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1066572015/SystemTick.o: ../../Library/Timer/SystemTick.c  .generated_files/flags/default/1baa006e6fde9d80a0ae65b73e9030e677c61411 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/1066572015" 
	@${RM} ${OBJECTDIR}/_ext/1066572015/SystemTick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1066572015/SystemTick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/1066572015/SystemTick.o.d" -o ${OBJECTDIR}/_ext/1066572015/SystemTick.o ../../Library/Timer/SystemTick.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1610046384/USB_CDC_UART.o: ../../Library/USB/USB_CDC_UART.c  .generated_files/flags/default/1937c907f03cccb17a559d928e036b8105b219ff .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/1610046384" 
	@${RM} ${OBJECTDIR}/_ext/1610046384/USB_CDC_UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1610046384/USB_CDC_UART.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/1610046384/USB_CDC_UART.o.d" -o ${OBJECTDIR}/_ext/1610046384/USB_CDC_UART.o ../../Library/USB/USB_CDC_UART.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o: mcc_generated_files/usb/usb_descriptors.c  .generated_files/flags/default/50fa3d6e6ef86cade4f4600a533ade08c6be7329 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d" -o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o mcc_generated_files/usb/usb_descriptors.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o: mcc_generated_files/usb/usb_device_events.c  .generated_files/flags/default/75b814d49311ad400079872f99c7a677b2a476c1 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d" -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o mcc_generated_files/usb/usb_device_events.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device.o: mcc_generated_files/usb/usb_device.c  .generated_files/flags/default/ac6239d4c86104ce73c218388bbe57c023496fe6 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d" -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o mcc_generated_files/usb/usb_device.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o: mcc_generated_files/usb/usb_device_cdc.c  .generated_files/flags/default/dfa616fc88568ca64777184c22bd0a5c5d1adf9a .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d" -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o mcc_generated_files/usb/usb_device_cdc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/exceptions.o: mcc_generated_files/exceptions.c  .generated_files/flags/default/cfc801a02c7141396fb4c0da78725cc73182fcf7 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/exceptions.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/exceptions.o.d" -o ${OBJECTDIR}/mcc_generated_files/exceptions.o mcc_generated_files/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/flags/default/5454333435f01d48ce851e1ff68a692f0f3c5c8c .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d" -o ${OBJECTDIR}/mcc_generated_files/clock.o mcc_generated_files/clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/flags/default/b444a99debac6e4b042bfd930ec8162980bac79c .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o mcc_generated_files/pin_manager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/flags/default/fd746b1c6cf22f5ef437a585ffabd728721c681c .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d" -o ${OBJECTDIR}/mcc_generated_files/mcc.o mcc_generated_files/mcc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/flags/default/6fb441f16737472ffbf1225fd0cee90b8c9f37f6 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d" -o ${OBJECTDIR}/mcc_generated_files/system.o mcc_generated_files/system.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/391208894bc8cb22baf8c85e5ffdb775f465c17e .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o mcc_generated_files/interrupt_manager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/coretimer.o: mcc_generated_files/coretimer.c  .generated_files/flags/default/7a643b3fcc04d9ac0492199ad7c078bca6b6433 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/coretimer.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/coretimer.o.d" -o ${OBJECTDIR}/mcc_generated_files/coretimer.o mcc_generated_files/coretimer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/uart2.o: mcc_generated_files/uart2.c  .generated_files/flags/default/158ec0f5421861941c695e72f3ed5fcb94eb817 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart2.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart2.o mcc_generated_files/uart2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/4927146f88ec64bf1a820f62d7238c159cb08241 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -ffunction-sections -fdata-sections -O2 -fno-common -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/USB_CDC_UART.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../../Library/Bootloader/fttag64_app.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -o ${DISTDIR}/USB_CDC_UART.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=4096,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--cref,--warn-section-align,--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/USB_CDC_UART.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../Library/Bootloader/fttag64_app.ld ../../Library/Bootloader/fttag64_bld.hex
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -o ${DISTDIR}/USB_CDC_UART.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=4096,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--cref,--warn-section-align,--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/USB_CDC_UART.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
	@echo Normalizing hex file
	@"C:/Program Files/Microchip/MPLABX/v6.00/mplab_platform/platform/../mplab_ide/modules/../../bin/hexmate" --edf="C:/Program Files/Microchip/MPLABX/v6.00/mplab_platform/platform/../mplab_ide/modules/../../dat/en_msgs.txt" ${DISTDIR}/USB_CDC_UART.X.${IMAGE_TYPE}.hex -o${DISTDIR}/USB_CDC_UART.X.${IMAGE_TYPE}.hex

	@echo "Creating unified hex file"
	@"C:/Program Files/Microchip/MPLABX/v6.00/mplab_platform/platform/../mplab_ide/modules/../../bin/hexmate" --edf="C:/Program Files/Microchip/MPLABX/v6.00/mplab_platform/platform/../mplab_ide/modules/../../dat/en_msgs.txt" ${DISTDIR}/USB_CDC_UART.X.${IMAGE_TYPE}.hex ../../Library/Bootloader/fttag64_bld.hex -odist/${CND_CONF}/production/USB_CDC_UART.X.production.unified.hex

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
