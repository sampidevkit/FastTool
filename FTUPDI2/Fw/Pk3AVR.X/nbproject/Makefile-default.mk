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
FINAL_IMAGE=${DISTDIR}/Pk3AVR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Pk3AVR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=apps/VCP.c apps/VCP_ATC.c apps/VCP_Debug.c apps/AppMain.c apps/PID_Controller.c cfg/Debug_Cfg.c cfg/SystemTick_Cfg.c cfg/Indicator_Cfg.c clib/buttons/Buttons.c clib/common/Utils.c clib/common/RingBuffer.c clib/common/Debug.c clib/indicator/Indicator.c clib/system/TickTimer.c clib/system/TaskManager.c mcc_generated_files/usb/usb_descriptors.c mcc_generated_files/usb/usb_device_events.c mcc_generated_files/usb/usb_device.c mcc_generated_files/usb/usb_hal_16bit.c mcc_generated_files/usb/usb_device_cdc.c mcc_generated_files/interrupt_manager.c mcc_generated_files/traps.c mcc_generated_files/where_was_i.s mcc_generated_files/mcc.c mcc_generated_files/system.c mcc_generated_files/clock.c mcc_generated_files/tmr1.c mcc_generated_files/tmr2.c mcc_generated_files/pin_manager.c mcc_generated_files/oc1.c mcc_generated_files/adc1.c mcc_generated_files/uart1.c mcc_generated_files/tmr4.c main.c apps/UPDI.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/apps/VCP.o ${OBJECTDIR}/apps/VCP_ATC.o ${OBJECTDIR}/apps/VCP_Debug.o ${OBJECTDIR}/apps/AppMain.o ${OBJECTDIR}/apps/PID_Controller.o ${OBJECTDIR}/cfg/Debug_Cfg.o ${OBJECTDIR}/cfg/SystemTick_Cfg.o ${OBJECTDIR}/cfg/Indicator_Cfg.o ${OBJECTDIR}/clib/buttons/Buttons.o ${OBJECTDIR}/clib/common/Utils.o ${OBJECTDIR}/clib/common/RingBuffer.o ${OBJECTDIR}/clib/common/Debug.o ${OBJECTDIR}/clib/indicator/Indicator.o ${OBJECTDIR}/clib/system/TickTimer.o ${OBJECTDIR}/clib/system/TaskManager.o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/traps.o ${OBJECTDIR}/mcc_generated_files/where_was_i.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/mcc_generated_files/tmr2.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/oc1.o ${OBJECTDIR}/mcc_generated_files/adc1.o ${OBJECTDIR}/mcc_generated_files/uart1.o ${OBJECTDIR}/mcc_generated_files/tmr4.o ${OBJECTDIR}/main.o ${OBJECTDIR}/apps/UPDI.o
POSSIBLE_DEPFILES=${OBJECTDIR}/apps/VCP.o.d ${OBJECTDIR}/apps/VCP_ATC.o.d ${OBJECTDIR}/apps/VCP_Debug.o.d ${OBJECTDIR}/apps/AppMain.o.d ${OBJECTDIR}/apps/PID_Controller.o.d ${OBJECTDIR}/cfg/Debug_Cfg.o.d ${OBJECTDIR}/cfg/SystemTick_Cfg.o.d ${OBJECTDIR}/cfg/Indicator_Cfg.o.d ${OBJECTDIR}/clib/buttons/Buttons.o.d ${OBJECTDIR}/clib/common/Utils.o.d ${OBJECTDIR}/clib/common/RingBuffer.o.d ${OBJECTDIR}/clib/common/Debug.o.d ${OBJECTDIR}/clib/indicator/Indicator.o.d ${OBJECTDIR}/clib/system/TickTimer.o.d ${OBJECTDIR}/clib/system/TaskManager.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/mcc_generated_files/traps.o.d ${OBJECTDIR}/mcc_generated_files/where_was_i.o.d ${OBJECTDIR}/mcc_generated_files/mcc.o.d ${OBJECTDIR}/mcc_generated_files/system.o.d ${OBJECTDIR}/mcc_generated_files/clock.o.d ${OBJECTDIR}/mcc_generated_files/tmr1.o.d ${OBJECTDIR}/mcc_generated_files/tmr2.o.d ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/mcc_generated_files/oc1.o.d ${OBJECTDIR}/mcc_generated_files/adc1.o.d ${OBJECTDIR}/mcc_generated_files/uart1.o.d ${OBJECTDIR}/mcc_generated_files/tmr4.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/apps/UPDI.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/apps/VCP.o ${OBJECTDIR}/apps/VCP_ATC.o ${OBJECTDIR}/apps/VCP_Debug.o ${OBJECTDIR}/apps/AppMain.o ${OBJECTDIR}/apps/PID_Controller.o ${OBJECTDIR}/cfg/Debug_Cfg.o ${OBJECTDIR}/cfg/SystemTick_Cfg.o ${OBJECTDIR}/cfg/Indicator_Cfg.o ${OBJECTDIR}/clib/buttons/Buttons.o ${OBJECTDIR}/clib/common/Utils.o ${OBJECTDIR}/clib/common/RingBuffer.o ${OBJECTDIR}/clib/common/Debug.o ${OBJECTDIR}/clib/indicator/Indicator.o ${OBJECTDIR}/clib/system/TickTimer.o ${OBJECTDIR}/clib/system/TaskManager.o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/traps.o ${OBJECTDIR}/mcc_generated_files/where_was_i.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/mcc_generated_files/tmr2.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/oc1.o ${OBJECTDIR}/mcc_generated_files/adc1.o ${OBJECTDIR}/mcc_generated_files/uart1.o ${OBJECTDIR}/mcc_generated_files/tmr4.o ${OBJECTDIR}/main.o ${OBJECTDIR}/apps/UPDI.o

# Source Files
SOURCEFILES=apps/VCP.c apps/VCP_ATC.c apps/VCP_Debug.c apps/AppMain.c apps/PID_Controller.c cfg/Debug_Cfg.c cfg/SystemTick_Cfg.c cfg/Indicator_Cfg.c clib/buttons/Buttons.c clib/common/Utils.c clib/common/RingBuffer.c clib/common/Debug.c clib/indicator/Indicator.c clib/system/TickTimer.c clib/system/TaskManager.c mcc_generated_files/usb/usb_descriptors.c mcc_generated_files/usb/usb_device_events.c mcc_generated_files/usb/usb_device.c mcc_generated_files/usb/usb_hal_16bit.c mcc_generated_files/usb/usb_device_cdc.c mcc_generated_files/interrupt_manager.c mcc_generated_files/traps.c mcc_generated_files/where_was_i.s mcc_generated_files/mcc.c mcc_generated_files/system.c mcc_generated_files/clock.c mcc_generated_files/tmr1.c mcc_generated_files/tmr2.c mcc_generated_files/pin_manager.c mcc_generated_files/oc1.c mcc_generated_files/adc1.c mcc_generated_files/uart1.c mcc_generated_files/tmr4.c main.c apps/UPDI.c



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
Device=PIC24FJ256GB106
ProjectDir="E:\Github\FastTool\UpdiV2\FTUPDI2\Fw\Pk3AVR.X"
ProjectName=Pk3AVR
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\Pk3AVR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="Pk3AVR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif
MDFUHostPath="D:\Resource\Program Files\microchip\MPLABX\v6.25\mplab_platform\mplab-pymdfu\bin\windows\pymdfu-bin.exe"
PYFWImageBuilderPath="D:\Resource\Program Files\microchip\MPLABX\v6.25\mplab_platform\mplab-pymdfu\bin\windows\pyfwimagebuilder-bin.exe"

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Pk3AVR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: [copy ${ImagePath} ".\App.${OUTPUT_SUFFIX}"]"
	@copy ${ImagePath} ".\App.${OUTPUT_SUFFIX}"
	@echo "--------------------------------------"

MP_PROCESSOR_OPTION=24FJ256GB106
MP_LINKER_FILE_OPTION=,--script=p24FJ256GB106.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/apps/VCP.o: apps/VCP.c  .generated_files/flags/default/bfd2c133553d90e023f64e5440d15928a06e0747 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/apps" 
	@${RM} ${OBJECTDIR}/apps/VCP.o.d 
	@${RM} ${OBJECTDIR}/apps/VCP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  apps/VCP.c  -o ${OBJECTDIR}/apps/VCP.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/apps/VCP.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/apps/VCP_ATC.o: apps/VCP_ATC.c  .generated_files/flags/default/8d0a82b026b50892fe12c98f137ac476fc08905d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/apps" 
	@${RM} ${OBJECTDIR}/apps/VCP_ATC.o.d 
	@${RM} ${OBJECTDIR}/apps/VCP_ATC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  apps/VCP_ATC.c  -o ${OBJECTDIR}/apps/VCP_ATC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/apps/VCP_ATC.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/apps/VCP_Debug.o: apps/VCP_Debug.c  .generated_files/flags/default/532add6e2607514111261374f5e0ffaf07f24752 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/apps" 
	@${RM} ${OBJECTDIR}/apps/VCP_Debug.o.d 
	@${RM} ${OBJECTDIR}/apps/VCP_Debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  apps/VCP_Debug.c  -o ${OBJECTDIR}/apps/VCP_Debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/apps/VCP_Debug.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/apps/AppMain.o: apps/AppMain.c  .generated_files/flags/default/54ee769fbb8be6d02c5a4b8e0e7c9d3145fd72d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/apps" 
	@${RM} ${OBJECTDIR}/apps/AppMain.o.d 
	@${RM} ${OBJECTDIR}/apps/AppMain.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  apps/AppMain.c  -o ${OBJECTDIR}/apps/AppMain.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/apps/AppMain.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/apps/PID_Controller.o: apps/PID_Controller.c  .generated_files/flags/default/416e3818a9098b7b6d9fd473db428b666623c814 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/apps" 
	@${RM} ${OBJECTDIR}/apps/PID_Controller.o.d 
	@${RM} ${OBJECTDIR}/apps/PID_Controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  apps/PID_Controller.c  -o ${OBJECTDIR}/apps/PID_Controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/apps/PID_Controller.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/cfg/Debug_Cfg.o: cfg/Debug_Cfg.c  .generated_files/flags/default/df0d95277bc35139948918c5cd63831bb345a3bf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/cfg" 
	@${RM} ${OBJECTDIR}/cfg/Debug_Cfg.o.d 
	@${RM} ${OBJECTDIR}/cfg/Debug_Cfg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  cfg/Debug_Cfg.c  -o ${OBJECTDIR}/cfg/Debug_Cfg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/cfg/Debug_Cfg.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/cfg/SystemTick_Cfg.o: cfg/SystemTick_Cfg.c  .generated_files/flags/default/150428ff0e32dc4ad70d8dc2ec11841e41396646 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/cfg" 
	@${RM} ${OBJECTDIR}/cfg/SystemTick_Cfg.o.d 
	@${RM} ${OBJECTDIR}/cfg/SystemTick_Cfg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  cfg/SystemTick_Cfg.c  -o ${OBJECTDIR}/cfg/SystemTick_Cfg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/cfg/SystemTick_Cfg.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/cfg/Indicator_Cfg.o: cfg/Indicator_Cfg.c  .generated_files/flags/default/11f2485e5a76074ed45d0b5c983d6822bc21be80 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/cfg" 
	@${RM} ${OBJECTDIR}/cfg/Indicator_Cfg.o.d 
	@${RM} ${OBJECTDIR}/cfg/Indicator_Cfg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  cfg/Indicator_Cfg.c  -o ${OBJECTDIR}/cfg/Indicator_Cfg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/cfg/Indicator_Cfg.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/clib/buttons/Buttons.o: clib/buttons/Buttons.c  .generated_files/flags/default/7773b369ef1acce4e81465fe365d30a1e151c65a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/clib/buttons" 
	@${RM} ${OBJECTDIR}/clib/buttons/Buttons.o.d 
	@${RM} ${OBJECTDIR}/clib/buttons/Buttons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  clib/buttons/Buttons.c  -o ${OBJECTDIR}/clib/buttons/Buttons.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/clib/buttons/Buttons.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/clib/common/Utils.o: clib/common/Utils.c  .generated_files/flags/default/97fa02925856d902c11ab1528580346491ec4071 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/clib/common" 
	@${RM} ${OBJECTDIR}/clib/common/Utils.o.d 
	@${RM} ${OBJECTDIR}/clib/common/Utils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  clib/common/Utils.c  -o ${OBJECTDIR}/clib/common/Utils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/clib/common/Utils.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/clib/common/RingBuffer.o: clib/common/RingBuffer.c  .generated_files/flags/default/40a7008cd377ba010e60cca9003510c841e4561e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/clib/common" 
	@${RM} ${OBJECTDIR}/clib/common/RingBuffer.o.d 
	@${RM} ${OBJECTDIR}/clib/common/RingBuffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  clib/common/RingBuffer.c  -o ${OBJECTDIR}/clib/common/RingBuffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/clib/common/RingBuffer.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/clib/common/Debug.o: clib/common/Debug.c  .generated_files/flags/default/5c6363b02756963c38e3dc971b0877594bb318fc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/clib/common" 
	@${RM} ${OBJECTDIR}/clib/common/Debug.o.d 
	@${RM} ${OBJECTDIR}/clib/common/Debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  clib/common/Debug.c  -o ${OBJECTDIR}/clib/common/Debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/clib/common/Debug.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/clib/indicator/Indicator.o: clib/indicator/Indicator.c  .generated_files/flags/default/38a1ef6e6ecdded35aa41b963d26aec336b9799d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/clib/indicator" 
	@${RM} ${OBJECTDIR}/clib/indicator/Indicator.o.d 
	@${RM} ${OBJECTDIR}/clib/indicator/Indicator.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  clib/indicator/Indicator.c  -o ${OBJECTDIR}/clib/indicator/Indicator.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/clib/indicator/Indicator.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/clib/system/TickTimer.o: clib/system/TickTimer.c  .generated_files/flags/default/d973383258d56031b9945e188cdb95e0b2800d73 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/clib/system" 
	@${RM} ${OBJECTDIR}/clib/system/TickTimer.o.d 
	@${RM} ${OBJECTDIR}/clib/system/TickTimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  clib/system/TickTimer.c  -o ${OBJECTDIR}/clib/system/TickTimer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/clib/system/TickTimer.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/clib/system/TaskManager.o: clib/system/TaskManager.c  .generated_files/flags/default/25a1e5cd236e9756fa7c7916e2bb134c022d389a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/clib/system" 
	@${RM} ${OBJECTDIR}/clib/system/TaskManager.o.d 
	@${RM} ${OBJECTDIR}/clib/system/TaskManager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  clib/system/TaskManager.c  -o ${OBJECTDIR}/clib/system/TaskManager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/clib/system/TaskManager.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o: mcc_generated_files/usb/usb_descriptors.c  .generated_files/flags/default/38238f80fd9405aea1d4322c94bbdee6de97985c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_descriptors.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o: mcc_generated_files/usb/usb_device_events.c  .generated_files/flags/default/5b043e71b14a605bb2a1c63d714830b402b2c31c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device_events.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device.o: mcc_generated_files/usb/usb_device.c  .generated_files/flags/default/573ddb21d2777b161711ea98562aa75d9b3fd508 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o: mcc_generated_files/usb/usb_hal_16bit.c  .generated_files/flags/default/8f133334639990b53f7938b4c52c39c2cd52638a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_hal_16bit.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o: mcc_generated_files/usb/usb_device_cdc.c  .generated_files/flags/default/6654cd22d0e8220cd40e5c136c0aa9767c7b7357 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device_cdc.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/ed05c1efe24e599caebf3cdff9a661bf3574a58d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/traps.o: mcc_generated_files/traps.c  .generated_files/flags/default/5e8bded1801afabd81ff103f2b086a66cfd46240 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/traps.c  -o ${OBJECTDIR}/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/traps.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/flags/default/2e0cf93ea790a4388bc23e4a900e394e96d210c3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/mcc.c  -o ${OBJECTDIR}/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/flags/default/bc1b7069c14aae7706003197e66852cd6d4d4c34 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system.c  -o ${OBJECTDIR}/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/flags/default/f4e0687734f64a2572560f4a549b72863c6c5dc5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clock.c  -o ${OBJECTDIR}/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  .generated_files/flags/default/f2a59e1dde478997f16b2339485e7cd3fb9f0541 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr2.o: mcc_generated_files/tmr2.c  .generated_files/flags/default/2cca0ade18885ab62c02b4b2da92c9dd1fde58cc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/mcc_generated_files/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr2.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/flags/default/422598dc9730d7454afb9a0d461feacc08342b4b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/oc1.o: mcc_generated_files/oc1.c  .generated_files/flags/default/956c588bc6ba8c860a4cd383dae8336eb74f5022 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/oc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/oc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/oc1.c  -o ${OBJECTDIR}/mcc_generated_files/oc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/oc1.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/adc1.o: mcc_generated_files/adc1.c  .generated_files/flags/default/72a3a28282b8a583e63aeed8d8e2e8ce91e13eb1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/adc1.c  -o ${OBJECTDIR}/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/adc1.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/uart1.o: mcc_generated_files/uart1.c  .generated_files/flags/default/d56e1118faa3e39f4d744cce1c50dc9a3f64da3f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/uart1.c  -o ${OBJECTDIR}/mcc_generated_files/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart1.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr4.o: mcc_generated_files/tmr4.c  .generated_files/flags/default/75b257bfa4262c61f8533388a9cdcefcf127a50b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr4.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr4.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr4.c  -o ${OBJECTDIR}/mcc_generated_files/tmr4.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr4.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/711154a73d7a3b1c88dece8cdbfcc97bd0b7770f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/apps/UPDI.o: apps/UPDI.c  .generated_files/flags/default/35489f8c443983da068912c6bbdc1a4d389d3c8b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/apps" 
	@${RM} ${OBJECTDIR}/apps/UPDI.o.d 
	@${RM} ${OBJECTDIR}/apps/UPDI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  apps/UPDI.c  -o ${OBJECTDIR}/apps/UPDI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/apps/UPDI.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/apps/VCP.o: apps/VCP.c  .generated_files/flags/default/42618a6aed76d9878204d9f443eea35fdf6d0cb2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/apps" 
	@${RM} ${OBJECTDIR}/apps/VCP.o.d 
	@${RM} ${OBJECTDIR}/apps/VCP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  apps/VCP.c  -o ${OBJECTDIR}/apps/VCP.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/apps/VCP.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/apps/VCP_ATC.o: apps/VCP_ATC.c  .generated_files/flags/default/3e215c4b103581c7d883e25040368fe7fb6eeeef .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/apps" 
	@${RM} ${OBJECTDIR}/apps/VCP_ATC.o.d 
	@${RM} ${OBJECTDIR}/apps/VCP_ATC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  apps/VCP_ATC.c  -o ${OBJECTDIR}/apps/VCP_ATC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/apps/VCP_ATC.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/apps/VCP_Debug.o: apps/VCP_Debug.c  .generated_files/flags/default/3766e5cc4c79ba2e20b1eda9aa686dea7aa6bd6c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/apps" 
	@${RM} ${OBJECTDIR}/apps/VCP_Debug.o.d 
	@${RM} ${OBJECTDIR}/apps/VCP_Debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  apps/VCP_Debug.c  -o ${OBJECTDIR}/apps/VCP_Debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/apps/VCP_Debug.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/apps/AppMain.o: apps/AppMain.c  .generated_files/flags/default/eecde0420b791f69038482ba4e66a291ff3224ed .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/apps" 
	@${RM} ${OBJECTDIR}/apps/AppMain.o.d 
	@${RM} ${OBJECTDIR}/apps/AppMain.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  apps/AppMain.c  -o ${OBJECTDIR}/apps/AppMain.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/apps/AppMain.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/apps/PID_Controller.o: apps/PID_Controller.c  .generated_files/flags/default/d1c3bcfeb1ca0ba0c2a98a9e84449f3758a2cdad .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/apps" 
	@${RM} ${OBJECTDIR}/apps/PID_Controller.o.d 
	@${RM} ${OBJECTDIR}/apps/PID_Controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  apps/PID_Controller.c  -o ${OBJECTDIR}/apps/PID_Controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/apps/PID_Controller.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/cfg/Debug_Cfg.o: cfg/Debug_Cfg.c  .generated_files/flags/default/ebd52811fbe81990543d24bccd29b81c217aa263 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/cfg" 
	@${RM} ${OBJECTDIR}/cfg/Debug_Cfg.o.d 
	@${RM} ${OBJECTDIR}/cfg/Debug_Cfg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  cfg/Debug_Cfg.c  -o ${OBJECTDIR}/cfg/Debug_Cfg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/cfg/Debug_Cfg.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/cfg/SystemTick_Cfg.o: cfg/SystemTick_Cfg.c  .generated_files/flags/default/b2f145d18b923fae52293134bc88eb3e33950cc8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/cfg" 
	@${RM} ${OBJECTDIR}/cfg/SystemTick_Cfg.o.d 
	@${RM} ${OBJECTDIR}/cfg/SystemTick_Cfg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  cfg/SystemTick_Cfg.c  -o ${OBJECTDIR}/cfg/SystemTick_Cfg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/cfg/SystemTick_Cfg.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/cfg/Indicator_Cfg.o: cfg/Indicator_Cfg.c  .generated_files/flags/default/c3ec1da19eb1782028f42655b7b8eb72baf8edb7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/cfg" 
	@${RM} ${OBJECTDIR}/cfg/Indicator_Cfg.o.d 
	@${RM} ${OBJECTDIR}/cfg/Indicator_Cfg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  cfg/Indicator_Cfg.c  -o ${OBJECTDIR}/cfg/Indicator_Cfg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/cfg/Indicator_Cfg.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/clib/buttons/Buttons.o: clib/buttons/Buttons.c  .generated_files/flags/default/18a19244c4fc0b4bbb60329b64414ffb037fd87b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/clib/buttons" 
	@${RM} ${OBJECTDIR}/clib/buttons/Buttons.o.d 
	@${RM} ${OBJECTDIR}/clib/buttons/Buttons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  clib/buttons/Buttons.c  -o ${OBJECTDIR}/clib/buttons/Buttons.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/clib/buttons/Buttons.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/clib/common/Utils.o: clib/common/Utils.c  .generated_files/flags/default/cb84ea5cb04169071600d524df3fc46b0f26aeec .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/clib/common" 
	@${RM} ${OBJECTDIR}/clib/common/Utils.o.d 
	@${RM} ${OBJECTDIR}/clib/common/Utils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  clib/common/Utils.c  -o ${OBJECTDIR}/clib/common/Utils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/clib/common/Utils.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/clib/common/RingBuffer.o: clib/common/RingBuffer.c  .generated_files/flags/default/89163a0e1c842dec59b092dd810e53a3c4ab4381 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/clib/common" 
	@${RM} ${OBJECTDIR}/clib/common/RingBuffer.o.d 
	@${RM} ${OBJECTDIR}/clib/common/RingBuffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  clib/common/RingBuffer.c  -o ${OBJECTDIR}/clib/common/RingBuffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/clib/common/RingBuffer.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/clib/common/Debug.o: clib/common/Debug.c  .generated_files/flags/default/6ec010679998077b21921f06f83ca5e91607d420 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/clib/common" 
	@${RM} ${OBJECTDIR}/clib/common/Debug.o.d 
	@${RM} ${OBJECTDIR}/clib/common/Debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  clib/common/Debug.c  -o ${OBJECTDIR}/clib/common/Debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/clib/common/Debug.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/clib/indicator/Indicator.o: clib/indicator/Indicator.c  .generated_files/flags/default/1b3f7b052cd80c33c2a7c30e3cba1c75a4076580 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/clib/indicator" 
	@${RM} ${OBJECTDIR}/clib/indicator/Indicator.o.d 
	@${RM} ${OBJECTDIR}/clib/indicator/Indicator.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  clib/indicator/Indicator.c  -o ${OBJECTDIR}/clib/indicator/Indicator.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/clib/indicator/Indicator.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/clib/system/TickTimer.o: clib/system/TickTimer.c  .generated_files/flags/default/dac54c65df2aa6e65caf499e543318bcf18fbfca .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/clib/system" 
	@${RM} ${OBJECTDIR}/clib/system/TickTimer.o.d 
	@${RM} ${OBJECTDIR}/clib/system/TickTimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  clib/system/TickTimer.c  -o ${OBJECTDIR}/clib/system/TickTimer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/clib/system/TickTimer.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/clib/system/TaskManager.o: clib/system/TaskManager.c  .generated_files/flags/default/341f6996abc85d3802fa0bb623e5cc49b9bb635d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/clib/system" 
	@${RM} ${OBJECTDIR}/clib/system/TaskManager.o.d 
	@${RM} ${OBJECTDIR}/clib/system/TaskManager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  clib/system/TaskManager.c  -o ${OBJECTDIR}/clib/system/TaskManager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/clib/system/TaskManager.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o: mcc_generated_files/usb/usb_descriptors.c  .generated_files/flags/default/e51e484df10f7e85b041982c0451a2792fec28dc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_descriptors.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o: mcc_generated_files/usb/usb_device_events.c  .generated_files/flags/default/93005de8d7b3a06ff41506037dfe7fc68da2486d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device_events.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device.o: mcc_generated_files/usb/usb_device.c  .generated_files/flags/default/d8e6a925794dca787b26d1c8418e9acde5ff802c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o: mcc_generated_files/usb/usb_hal_16bit.c  .generated_files/flags/default/c8de61e0ce823ae149ada8ecf8768c292fc8dc94 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_hal_16bit.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o: mcc_generated_files/usb/usb_device_cdc.c  .generated_files/flags/default/2803713473e9bb47c19a0b2f38be21ff71636cde .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device_cdc.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/a24a47ec0a82b35ca4ba8d45f52b236ff55df822 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/traps.o: mcc_generated_files/traps.c  .generated_files/flags/default/19a30bb92f3c1d2cf5969f09e787b36516699aaf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/traps.c  -o ${OBJECTDIR}/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/traps.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/flags/default/8a22cfe7ccd9a98ad185204ba4572dba85ef8f3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/mcc.c  -o ${OBJECTDIR}/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/flags/default/93ec02374083e1ccef104772ada039b17ed84751 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system.c  -o ${OBJECTDIR}/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/flags/default/97608a492abb0f155ad70c4c7b0822c54c05cf7f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clock.c  -o ${OBJECTDIR}/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  .generated_files/flags/default/36e9052b3c421b70104d35ea724a58c1e0473879 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr2.o: mcc_generated_files/tmr2.c  .generated_files/flags/default/c4bcb720c4aa077ed76a51f33af85ae9f7878c10 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/mcc_generated_files/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr2.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/flags/default/7441b8a1a149039729737d512c52361efff4b9cd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/oc1.o: mcc_generated_files/oc1.c  .generated_files/flags/default/4dff0f8162f0a64683a2bd66d49b642ecc17cc3c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/oc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/oc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/oc1.c  -o ${OBJECTDIR}/mcc_generated_files/oc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/oc1.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/adc1.o: mcc_generated_files/adc1.c  .generated_files/flags/default/c1bd705dae7bad23de30324bd01bad0364a8abe6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/adc1.c  -o ${OBJECTDIR}/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/adc1.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/uart1.o: mcc_generated_files/uart1.c  .generated_files/flags/default/8e4927fec0c2e4fb7b05625fefaccc1535a327ab .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/uart1.c  -o ${OBJECTDIR}/mcc_generated_files/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart1.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr4.o: mcc_generated_files/tmr4.c  .generated_files/flags/default/3905428c9612d4662c5dc366caaaa25834fa4fa9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr4.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr4.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr4.c  -o ${OBJECTDIR}/mcc_generated_files/tmr4.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr4.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/352ab5e90282c4234302157e5b93a2e216e75ef6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/apps/UPDI.o: apps/UPDI.c  .generated_files/flags/default/a6252490fbf6f12ace0afb54e5dba7c619b1389a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/apps" 
	@${RM} ${OBJECTDIR}/apps/UPDI.o.d 
	@${RM} ${OBJECTDIR}/apps/UPDI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  apps/UPDI.c  -o ${OBJECTDIR}/apps/UPDI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/apps/UPDI.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -ffunction-sections -fdata-sections -O2 -mcci -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/mcc_generated_files/where_was_i.o: mcc_generated_files/where_was_i.s  .generated_files/flags/default/8c006d8fbd1f142542998b902c1db9a44a7f81ff .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/where_was_i.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/where_was_i.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/where_was_i.s  -o ${OBJECTDIR}/mcc_generated_files/where_was_i.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)    -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/where_was_i.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/mcc_generated_files/where_was_i.o: mcc_generated_files/where_was_i.s  .generated_files/flags/default/e8d1172649cc694fbd22df8eab11b4657f97ab8c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/where_was_i.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/where_was_i.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/where_was_i.s  -o ${OBJECTDIR}/mcc_generated_files/where_was_i.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)    -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/where_was_i.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Pk3AVR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/Pk3AVR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files"  -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--heap=1024,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/Pk3AVR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/Pk3AVR.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"apps" -I"cfg" -I"clib" -I"mcc_generated_files" -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=1024,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/Pk3AVR.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
	@echo Normalizing hex file
	@"D:/Resource/Program Files/microchip/MPLABX/v6.25/mplab_platform/platform/../mplab_ide/modules/../../bin/hexmate" --edf="D:/Resource/Program Files/microchip/MPLABX/v6.25/mplab_platform/platform/../mplab_ide/modules/../../dat/en_msgs.txt" ${DISTDIR}/Pk3AVR.X.${IMAGE_TYPE}.hex -o${DISTDIR}/Pk3AVR.X.${IMAGE_TYPE}.hex

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

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
