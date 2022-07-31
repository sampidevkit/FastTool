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
FINAL_IMAGE=${DISTDIR}/RTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/RTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=app/libcomp.c app/Application.c ../../Library/Bootloader/Bootloader.c ../../Library/Common/Button.c ../../Library/Timer/SystemTick.c mcc_generated_files/exceptions.c mcc_generated_files/clock.c mcc_generated_files/pin_manager.c mcc_generated_files/mcc.c mcc_generated_files/system.c mcc_generated_files/interrupt_manager.c ../../RTOS/Core/heap_4.c ../../RTOS/Core/list.c ../../RTOS/Core/queue.c ../../RTOS/Core/tasks.c ../../RTOS/Core/timers.c ../../RTOS/PIC32MM/port.c ../../RTOS/PIC32MM/port_asm.S main.c mcc_generated_files/tmr2.c mcc_generated_files/tmr3.c mcc_generated_files/tmr2_isr.S mcc_generated_files/tmr3_isr.S

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/app/libcomp.o ${OBJECTDIR}/app/Application.o ${OBJECTDIR}/_ext/1919251143/Bootloader.o ${OBJECTDIR}/_ext/814859167/Button.o ${OBJECTDIR}/_ext/1066572015/SystemTick.o ${OBJECTDIR}/mcc_generated_files/exceptions.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/_ext/116891928/heap_4.o ${OBJECTDIR}/_ext/116891928/list.o ${OBJECTDIR}/_ext/116891928/queue.o ${OBJECTDIR}/_ext/116891928/tasks.o ${OBJECTDIR}/_ext/116891928/timers.o ${OBJECTDIR}/_ext/1589056288/port.o ${OBJECTDIR}/_ext/1589056288/port_asm.o ${OBJECTDIR}/main.o ${OBJECTDIR}/mcc_generated_files/tmr2.o ${OBJECTDIR}/mcc_generated_files/tmr3.o ${OBJECTDIR}/mcc_generated_files/tmr2_isr.o ${OBJECTDIR}/mcc_generated_files/tmr3_isr.o
POSSIBLE_DEPFILES=${OBJECTDIR}/app/libcomp.o.d ${OBJECTDIR}/app/Application.o.d ${OBJECTDIR}/_ext/1919251143/Bootloader.o.d ${OBJECTDIR}/_ext/814859167/Button.o.d ${OBJECTDIR}/_ext/1066572015/SystemTick.o.d ${OBJECTDIR}/mcc_generated_files/exceptions.o.d ${OBJECTDIR}/mcc_generated_files/clock.o.d ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/mcc_generated_files/mcc.o.d ${OBJECTDIR}/mcc_generated_files/system.o.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/_ext/116891928/heap_4.o.d ${OBJECTDIR}/_ext/116891928/list.o.d ${OBJECTDIR}/_ext/116891928/queue.o.d ${OBJECTDIR}/_ext/116891928/tasks.o.d ${OBJECTDIR}/_ext/116891928/timers.o.d ${OBJECTDIR}/_ext/1589056288/port.o.d ${OBJECTDIR}/_ext/1589056288/port_asm.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/mcc_generated_files/tmr2.o.d ${OBJECTDIR}/mcc_generated_files/tmr3.o.d ${OBJECTDIR}/mcc_generated_files/tmr2_isr.o.d ${OBJECTDIR}/mcc_generated_files/tmr3_isr.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/app/libcomp.o ${OBJECTDIR}/app/Application.o ${OBJECTDIR}/_ext/1919251143/Bootloader.o ${OBJECTDIR}/_ext/814859167/Button.o ${OBJECTDIR}/_ext/1066572015/SystemTick.o ${OBJECTDIR}/mcc_generated_files/exceptions.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/_ext/116891928/heap_4.o ${OBJECTDIR}/_ext/116891928/list.o ${OBJECTDIR}/_ext/116891928/queue.o ${OBJECTDIR}/_ext/116891928/tasks.o ${OBJECTDIR}/_ext/116891928/timers.o ${OBJECTDIR}/_ext/1589056288/port.o ${OBJECTDIR}/_ext/1589056288/port_asm.o ${OBJECTDIR}/main.o ${OBJECTDIR}/mcc_generated_files/tmr2.o ${OBJECTDIR}/mcc_generated_files/tmr3.o ${OBJECTDIR}/mcc_generated_files/tmr2_isr.o ${OBJECTDIR}/mcc_generated_files/tmr3_isr.o

# Source Files
SOURCEFILES=app/libcomp.c app/Application.c ../../Library/Bootloader/Bootloader.c ../../Library/Common/Button.c ../../Library/Timer/SystemTick.c mcc_generated_files/exceptions.c mcc_generated_files/clock.c mcc_generated_files/pin_manager.c mcc_generated_files/mcc.c mcc_generated_files/system.c mcc_generated_files/interrupt_manager.c ../../RTOS/Core/heap_4.c ../../RTOS/Core/list.c ../../RTOS/Core/queue.c ../../RTOS/Core/tasks.c ../../RTOS/Core/timers.c ../../RTOS/PIC32MM/port.c ../../RTOS/PIC32MM/port_asm.S main.c mcc_generated_files/tmr2.c mcc_generated_files/tmr3.c mcc_generated_files/tmr2_isr.S mcc_generated_files/tmr3_isr.S



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
ProjectDir="F:\Git\SAMPI\FastTool\TAG\FTTAG64\RTOS.X"
ProjectName=RTOS
ConfName=default
ImagePath="${DISTDIR}\RTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="${DISTDIR}"
ImageName="RTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/RTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
${OBJECTDIR}/_ext/1589056288/port_asm.o: ../../RTOS/PIC32MM/port_asm.S  .generated_files/flags/default/1ae6299267d999dcc1836e8fcbcc735d3f8a470e .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/1589056288" 
	@${RM} ${OBJECTDIR}/_ext/1589056288/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1589056288/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1589056288/port_asm.o.ok ${OBJECTDIR}/_ext/1589056288/port_asm.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1589056288/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1589056288/port_asm.o ../../RTOS/PIC32MM/port_asm.S  -DXPRJ_default=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1589056288/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,-I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1589056288/port_asm.o.d" "${OBJECTDIR}/_ext/1589056288/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mcc_generated_files/tmr2_isr.o: mcc_generated_files/tmr2_isr.S  .generated_files/flags/default/c2e1fa5ecbaf2b1df0f83b1cef6875af7597cd94 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2_isr.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2_isr.o 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2_isr.o.ok ${OBJECTDIR}/mcc_generated_files/tmr2_isr.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr2_isr.o.d"  -o ${OBJECTDIR}/mcc_generated_files/tmr2_isr.o mcc_generated_files/tmr2_isr.S  -DXPRJ_default=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/mcc_generated_files/tmr2_isr.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,-I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/tmr2_isr.o.d" "${OBJECTDIR}/mcc_generated_files/tmr2_isr.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mcc_generated_files/tmr3_isr.o: mcc_generated_files/tmr3_isr.S  .generated_files/flags/default/c10fd4c528ecdb2a33af2771223dce7ddf1b4ce6 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr3_isr.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr3_isr.o 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr3_isr.o.ok ${OBJECTDIR}/mcc_generated_files/tmr3_isr.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr3_isr.o.d"  -o ${OBJECTDIR}/mcc_generated_files/tmr3_isr.o mcc_generated_files/tmr3_isr.S  -DXPRJ_default=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/mcc_generated_files/tmr3_isr.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,-I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/tmr3_isr.o.d" "${OBJECTDIR}/mcc_generated_files/tmr3_isr.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1589056288/port_asm.o: ../../RTOS/PIC32MM/port_asm.S  .generated_files/flags/default/5467cafa96be2949377bddbce61a3fe910a9ac9a .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/1589056288" 
	@${RM} ${OBJECTDIR}/_ext/1589056288/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1589056288/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1589056288/port_asm.o.ok ${OBJECTDIR}/_ext/1589056288/port_asm.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1589056288/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1589056288/port_asm.o ../../RTOS/PIC32MM/port_asm.S  -DXPRJ_default=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1589056288/port_asm.o.asm.d",--gdwarf-2,-I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1589056288/port_asm.o.d" "${OBJECTDIR}/_ext/1589056288/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mcc_generated_files/tmr2_isr.o: mcc_generated_files/tmr2_isr.S  .generated_files/flags/default/ca8c3e0eb139bfd4d84098a80a74ede99bfe7e6f .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2_isr.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2_isr.o 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2_isr.o.ok ${OBJECTDIR}/mcc_generated_files/tmr2_isr.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr2_isr.o.d"  -o ${OBJECTDIR}/mcc_generated_files/tmr2_isr.o mcc_generated_files/tmr2_isr.S  -DXPRJ_default=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/mcc_generated_files/tmr2_isr.o.asm.d",--gdwarf-2,-I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/tmr2_isr.o.d" "${OBJECTDIR}/mcc_generated_files/tmr2_isr.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mcc_generated_files/tmr3_isr.o: mcc_generated_files/tmr3_isr.S  .generated_files/flags/default/1638f1179e98ce6764e9116a98b727c7be17da36 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr3_isr.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr3_isr.o 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr3_isr.o.ok ${OBJECTDIR}/mcc_generated_files/tmr3_isr.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr3_isr.o.d"  -o ${OBJECTDIR}/mcc_generated_files/tmr3_isr.o mcc_generated_files/tmr3_isr.S  -DXPRJ_default=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/mcc_generated_files/tmr3_isr.o.asm.d",--gdwarf-2,-I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/tmr3_isr.o.d" "${OBJECTDIR}/mcc_generated_files/tmr3_isr.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/app/libcomp.o: app/libcomp.c  .generated_files/flags/default/9889fd45c226dcca38febe86ea7713ccc9b041f8 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/libcomp.o.d 
	@${RM} ${OBJECTDIR}/app/libcomp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/app/libcomp.o.d" -o ${OBJECTDIR}/app/libcomp.o app/libcomp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/app/Application.o: app/Application.c  .generated_files/flags/default/76438eff74b97d64f254b5de34aec5da8a393dfa .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/Application.o.d 
	@${RM} ${OBJECTDIR}/app/Application.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/app/Application.o.d" -o ${OBJECTDIR}/app/Application.o app/Application.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1919251143/Bootloader.o: ../../Library/Bootloader/Bootloader.c  .generated_files/flags/default/888c60664fb96310b3a965a880a504c3cf7bea08 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/1919251143" 
	@${RM} ${OBJECTDIR}/_ext/1919251143/Bootloader.o.d 
	@${RM} ${OBJECTDIR}/_ext/1919251143/Bootloader.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/_ext/1919251143/Bootloader.o.d" -o ${OBJECTDIR}/_ext/1919251143/Bootloader.o ../../Library/Bootloader/Bootloader.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/814859167/Button.o: ../../Library/Common/Button.c  .generated_files/flags/default/9287349daebfd7e94240fef84001553dadba7ea9 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/814859167" 
	@${RM} ${OBJECTDIR}/_ext/814859167/Button.o.d 
	@${RM} ${OBJECTDIR}/_ext/814859167/Button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/_ext/814859167/Button.o.d" -o ${OBJECTDIR}/_ext/814859167/Button.o ../../Library/Common/Button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1066572015/SystemTick.o: ../../Library/Timer/SystemTick.c  .generated_files/flags/default/fbe9738054a9ec407b0bee204c0f7b5d0f84b4a3 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/1066572015" 
	@${RM} ${OBJECTDIR}/_ext/1066572015/SystemTick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1066572015/SystemTick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/_ext/1066572015/SystemTick.o.d" -o ${OBJECTDIR}/_ext/1066572015/SystemTick.o ../../Library/Timer/SystemTick.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/exceptions.o: mcc_generated_files/exceptions.c  .generated_files/flags/default/f3057e045f50b4aaaf3a902474b23b3a0cd1461e .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/exceptions.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/exceptions.o.d" -o ${OBJECTDIR}/mcc_generated_files/exceptions.o mcc_generated_files/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/flags/default/84565cf0ea676c64a47ed630320d6ebfc28b25fe .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d" -o ${OBJECTDIR}/mcc_generated_files/clock.o mcc_generated_files/clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/flags/default/cdb638a42688499f3294c616ee24da2cfafc1007 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o mcc_generated_files/pin_manager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/flags/default/b476a46d5cf129b1e6ec45aa4733c775f6a27e98 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d" -o ${OBJECTDIR}/mcc_generated_files/mcc.o mcc_generated_files/mcc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/flags/default/f963977f7ba3652766dd3c7fc655a708c561213a .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d" -o ${OBJECTDIR}/mcc_generated_files/system.o mcc_generated_files/system.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/c45e6ae9de69dbec870e44917176ac1fa94cf6cd .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o mcc_generated_files/interrupt_manager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/116891928/heap_4.o: ../../RTOS/Core/heap_4.c  .generated_files/flags/default/7a22ffaf50a8042db6ec7776f26cd38cc00387ab .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/116891928" 
	@${RM} ${OBJECTDIR}/_ext/116891928/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/116891928/heap_4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/_ext/116891928/heap_4.o.d" -o ${OBJECTDIR}/_ext/116891928/heap_4.o ../../RTOS/Core/heap_4.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/116891928/list.o: ../../RTOS/Core/list.c  .generated_files/flags/default/25c54bc70535e191740de9f11a60d9a279f61095 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/116891928" 
	@${RM} ${OBJECTDIR}/_ext/116891928/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/116891928/list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/_ext/116891928/list.o.d" -o ${OBJECTDIR}/_ext/116891928/list.o ../../RTOS/Core/list.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/116891928/queue.o: ../../RTOS/Core/queue.c  .generated_files/flags/default/33cc3bee3e0f851b373fcfaa8007e7db4507786f .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/116891928" 
	@${RM} ${OBJECTDIR}/_ext/116891928/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/116891928/queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/_ext/116891928/queue.o.d" -o ${OBJECTDIR}/_ext/116891928/queue.o ../../RTOS/Core/queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/116891928/tasks.o: ../../RTOS/Core/tasks.c  .generated_files/flags/default/e6692fc6747d8411968b5086b22f79977c025c1b .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/116891928" 
	@${RM} ${OBJECTDIR}/_ext/116891928/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/116891928/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/_ext/116891928/tasks.o.d" -o ${OBJECTDIR}/_ext/116891928/tasks.o ../../RTOS/Core/tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/116891928/timers.o: ../../RTOS/Core/timers.c  .generated_files/flags/default/85a0a22a30400274d3a33944969968bef92e5bcf .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/116891928" 
	@${RM} ${OBJECTDIR}/_ext/116891928/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/116891928/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/_ext/116891928/timers.o.d" -o ${OBJECTDIR}/_ext/116891928/timers.o ../../RTOS/Core/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1589056288/port.o: ../../RTOS/PIC32MM/port.c  .generated_files/flags/default/d96c3fcf45a964cf1cab4a93af655e8f2cd1edbd .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/1589056288" 
	@${RM} ${OBJECTDIR}/_ext/1589056288/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1589056288/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/_ext/1589056288/port.o.d" -o ${OBJECTDIR}/_ext/1589056288/port.o ../../RTOS/PIC32MM/port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/544c07c43fd3d1fff5819bddeed70f3b59e22e28 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/tmr2.o: mcc_generated_files/tmr2.c  .generated_files/flags/default/b9f89e9eaedcaf02fc0b35d20229951abc15253c .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr2.o.d" -o ${OBJECTDIR}/mcc_generated_files/tmr2.o mcc_generated_files/tmr2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/tmr3.o: mcc_generated_files/tmr3.c  .generated_files/flags/default/73b60e419376a76eaeddbe92b6d8123f98550042 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr3.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr3.o.d" -o ${OBJECTDIR}/mcc_generated_files/tmr3.o mcc_generated_files/tmr3.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/app/libcomp.o: app/libcomp.c  .generated_files/flags/default/88cf004d163ac1c1f8fb53f7c4479f2a62378ae6 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/libcomp.o.d 
	@${RM} ${OBJECTDIR}/app/libcomp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/app/libcomp.o.d" -o ${OBJECTDIR}/app/libcomp.o app/libcomp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/app/Application.o: app/Application.c  .generated_files/flags/default/83613569c636bf7a3902d2dbec736004ae2dbd6a .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/Application.o.d 
	@${RM} ${OBJECTDIR}/app/Application.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/app/Application.o.d" -o ${OBJECTDIR}/app/Application.o app/Application.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1919251143/Bootloader.o: ../../Library/Bootloader/Bootloader.c  .generated_files/flags/default/23ea9c70111f658dd6f0c9ad120f34659a635dad .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/1919251143" 
	@${RM} ${OBJECTDIR}/_ext/1919251143/Bootloader.o.d 
	@${RM} ${OBJECTDIR}/_ext/1919251143/Bootloader.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/_ext/1919251143/Bootloader.o.d" -o ${OBJECTDIR}/_ext/1919251143/Bootloader.o ../../Library/Bootloader/Bootloader.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/814859167/Button.o: ../../Library/Common/Button.c  .generated_files/flags/default/d8f8ffa719b19fcad752d8b0c29eab93fe4a4288 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/814859167" 
	@${RM} ${OBJECTDIR}/_ext/814859167/Button.o.d 
	@${RM} ${OBJECTDIR}/_ext/814859167/Button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/_ext/814859167/Button.o.d" -o ${OBJECTDIR}/_ext/814859167/Button.o ../../Library/Common/Button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1066572015/SystemTick.o: ../../Library/Timer/SystemTick.c  .generated_files/flags/default/2214a30cfaee9ed5e59cec0ae98b4b4c5f802e0d .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/1066572015" 
	@${RM} ${OBJECTDIR}/_ext/1066572015/SystemTick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1066572015/SystemTick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/_ext/1066572015/SystemTick.o.d" -o ${OBJECTDIR}/_ext/1066572015/SystemTick.o ../../Library/Timer/SystemTick.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/exceptions.o: mcc_generated_files/exceptions.c  .generated_files/flags/default/de261f7d19d339201ecc7fa0f4b881ada6704268 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/exceptions.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/exceptions.o.d" -o ${OBJECTDIR}/mcc_generated_files/exceptions.o mcc_generated_files/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/flags/default/5d11fd75e125d940673aef7b5e65a8b21aadfbeb .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d" -o ${OBJECTDIR}/mcc_generated_files/clock.o mcc_generated_files/clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/flags/default/9179063b3052e1cc550065ee634e5a152c98205 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o mcc_generated_files/pin_manager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/flags/default/d2673725ae4eb5c1b4112506f71a9ca7bbb1737d .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d" -o ${OBJECTDIR}/mcc_generated_files/mcc.o mcc_generated_files/mcc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/flags/default/3d735e4fdd89a387fa2024f97fcfd7a6260cc055 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d" -o ${OBJECTDIR}/mcc_generated_files/system.o mcc_generated_files/system.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/766bd6b2a744a3b7f9e8028218509a3a2bfbcb87 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o mcc_generated_files/interrupt_manager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/116891928/heap_4.o: ../../RTOS/Core/heap_4.c  .generated_files/flags/default/2c2690c43d44d16705fe26d6dfa2799cad92b4c4 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/116891928" 
	@${RM} ${OBJECTDIR}/_ext/116891928/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/116891928/heap_4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/_ext/116891928/heap_4.o.d" -o ${OBJECTDIR}/_ext/116891928/heap_4.o ../../RTOS/Core/heap_4.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/116891928/list.o: ../../RTOS/Core/list.c  .generated_files/flags/default/489f13f87e328b127c28031a092cf457397ebc6d .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/116891928" 
	@${RM} ${OBJECTDIR}/_ext/116891928/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/116891928/list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/_ext/116891928/list.o.d" -o ${OBJECTDIR}/_ext/116891928/list.o ../../RTOS/Core/list.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/116891928/queue.o: ../../RTOS/Core/queue.c  .generated_files/flags/default/7a8ea1f8e4fdb555f4fc74dba328e9264c6a3d0d .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/116891928" 
	@${RM} ${OBJECTDIR}/_ext/116891928/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/116891928/queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/_ext/116891928/queue.o.d" -o ${OBJECTDIR}/_ext/116891928/queue.o ../../RTOS/Core/queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/116891928/tasks.o: ../../RTOS/Core/tasks.c  .generated_files/flags/default/d6e7cb947e89c4657bf1ad9ef8c6787a5bc853a6 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/116891928" 
	@${RM} ${OBJECTDIR}/_ext/116891928/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/116891928/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/_ext/116891928/tasks.o.d" -o ${OBJECTDIR}/_ext/116891928/tasks.o ../../RTOS/Core/tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/116891928/timers.o: ../../RTOS/Core/timers.c  .generated_files/flags/default/a3a98ded924243a7dab09f3a5ab833c19d4eaf3d .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/116891928" 
	@${RM} ${OBJECTDIR}/_ext/116891928/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/116891928/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/_ext/116891928/timers.o.d" -o ${OBJECTDIR}/_ext/116891928/timers.o ../../RTOS/Core/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1589056288/port.o: ../../RTOS/PIC32MM/port.c  .generated_files/flags/default/65fecd0804ac590fad4672953855c4e0ecbf247f .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/_ext/1589056288" 
	@${RM} ${OBJECTDIR}/_ext/1589056288/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1589056288/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/_ext/1589056288/port.o.d" -o ${OBJECTDIR}/_ext/1589056288/port.o ../../RTOS/PIC32MM/port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/ff12af271dd170e6b9a92777e3a61071f2b24d76 .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/tmr2.o: mcc_generated_files/tmr2.c  .generated_files/flags/default/c7682b1ef783a32401d5f2f4632d3f5d260259c .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr2.o.d" -o ${OBJECTDIR}/mcc_generated_files/tmr2.o mcc_generated_files/tmr2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mcc_generated_files/tmr3.o: mcc_generated_files/tmr3.c  .generated_files/flags/default/e7a53fe9131f8794e6d73e29ad44a7e825fdde8b .generated_files/flags/default/88d83c7a69442caf92c0f7f6fbd64c23df277cf
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr3.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"app" -I"cfg" -I"mcc_generated_files" -I"../../Library" -I"../../RTOS/Core" -I"../../RTOS/PIC32MM" -ffunction-sections -fdata-sections -O2 -fno-common -DUSE_RTOS -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr3.o.d" -o ${OBJECTDIR}/mcc_generated_files/tmr3.o mcc_generated_files/tmr3.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/RTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../../Library/Bootloader/fttag64_app.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -o ${DISTDIR}/RTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=1024,--defsym=_min_stack_size=64,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--cref,--warn-section-align,--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/RTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../Library/Bootloader/fttag64_app.ld ../../Library/Bootloader/fttag64_bld.hex
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -o ${DISTDIR}/RTOS.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=1024,--defsym=_min_stack_size=64,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--cref,--warn-section-align,--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/RTOS.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
	@echo Normalizing hex file
	@"C:/Program Files/Microchip/MPLABX/v6.00/mplab_platform/platform/../mplab_ide/modules/../../bin/hexmate" --edf="C:/Program Files/Microchip/MPLABX/v6.00/mplab_platform/platform/../mplab_ide/modules/../../dat/en_msgs.txt" ${DISTDIR}/RTOS.X.${IMAGE_TYPE}.hex -o${DISTDIR}/RTOS.X.${IMAGE_TYPE}.hex

	@echo "Creating unified hex file"
	@"C:/Program Files/Microchip/MPLABX/v6.00/mplab_platform/platform/../mplab_ide/modules/../../bin/hexmate" --edf="C:/Program Files/Microchip/MPLABX/v6.00/mplab_platform/platform/../mplab_ide/modules/../../dat/en_msgs.txt" ${DISTDIR}/RTOS.X.${IMAGE_TYPE}.hex ../../Library/Bootloader/fttag64_bld.hex -odist/${CND_CONF}/production/RTOS.X.production.unified.hex

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
