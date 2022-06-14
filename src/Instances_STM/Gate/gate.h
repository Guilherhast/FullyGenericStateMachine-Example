#ifndef GATE_H
#define GATE_H

#define NAME_LOCKED "Locked"
#define NAME_CLOSED "Closed"
#define NAME_CLOSING "Closing"
#define NAME_FORCEDCLOSING "ForcedClosing"
#define NAME_INTERRUPTEDCLOSING "InterruptedClosing"
#define NAME_OPENNING "Openning"
#define NAME_FORCEDOPENNING "ForcedOpenning"
#define NAME_INTERRUPTEDOPENNING "InterruptedOpenning"
#define NAME_OPEN "Open"

#include <stdio.h>
#include <time.h>

#include "../../StateMachine/state.h"
#include "../../StateMachine/stateCondition.h"
#include "../../StateMachine/stateMachine.h"
#include "../../StateMachine/transition.h"
#include "../../consts.h"

#define MAX_CLOSED_TIME 300.0
#define OPEN_WARNNING_INTERVAL 30.0

#define CHECK_LOCK_TOLERANCE 300.0
#define CHECK_UNLOCK_TOLERANCE 30.0
#define CHECK_OPEN_TOLERANCE 60.0

typedef struct data_smc_gate {
  // Monitor warnnings
  time_t last_open_warnning;

  // Monitor auto triggers
  time_t auto_lock_time;
  time_t auto_unlock_time;
  time_t auto_open_time;

  // Overwrite auto triggers
  boolean ignoreAutoTriggers;
} data_smc_gate;

/*
 *
 * STATE CONDITION DECLARATIONS
 *
 */

// Constants
#define SECS_IN_DAY (60 * 60 * 24)
#define MIL 1000
#define MILIS_IN_DAY (MIL * SECS_IN_DAY)
// Functions for checking condition transitions
boolean timeOutCheck(time_t triggerTime, float tolerance);
boolean timeOutCheckOnlyTime(time_t triggerTime, float tolerance);
// StateCondition factories
StateConditionList *conditions_stt_locked_create(State *sttLock);
StateConditionList *conditions_stt_closed_create(State *sttLock,
                                                 State *sttOpening);
StateConditionList *conditions_stt_unlock_create(State *sttClosed);

/*
 *
 * TRANSITIONS
 *
 */
void GateTransitions_addTransitionsFromList(StateList *sttList, char *sttName,
                                            USint n, void **names,
                                            boolean isTrigger);

#define GateTransitions_addTransitionsFromListReal(sl, sn, n, nm)              \
  GateTransitions_addTransitionsFromList(sl, sn, n, nm, false)

#define GateTransitions_addTransitionsFromListTrigger(sl, sn, n, nm)           \
  GateTransitions_addTransitionsFromList(sl, sn, n, nm, true)

void GateTransitions_initTmp();
void GateTransitions_cleanTmp();

/*
 *
 * CONDITIONS
 *
 */
void GateConditions_addAll(StateList *sttList);

/*
 *
 * STATE DECLARATIONS
 *
 */

StateList *GateStateList_createAll();
void State_Enter_base(char *, void *);
void State_Open_enter(void *data);

/*
 *
 * BODY DECLARATIONS
 *
 */
data_smc_gate *gateData_allocAndInit(boolean ignoreAutoTriggers,
                                     time_t lock_time, time_t unlock_time,
                                     time_t open_time);

#define gateData_allocAndInitIG(l, u, o) gateData_allocAndInit(true, l, u, o)
#define gateData_allocAndInitNOIG(l, u, o) gateData_allocAndInit(false, l, u, o)

StateMachineList *GateSMC_create(SMCID id, data_smc_gate *data);
StateMachineList *GateSMCS_createList(USint n, SMCID *IDS,
                                      data_smc_gate **data);

/*
 * Gate Declarations
 */
StateMachineList *GateStateMachine_create();
#endif
