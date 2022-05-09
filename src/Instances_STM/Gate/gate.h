#ifndef GATE_H
#define GATE_H

#include <stdio.h>
#include <time.h>

#include "../../consts.h"
#include "../../StateMachine/transition.h"
#include "../../StateMachine/stateCondition.h"
#include "../../StateMachine/state.h"
#include "../../StateMachine/stateMachine.h"

#define MAX_CLOSED_TIME 300.0
#define OPEN_WARNNING_INTERVAL 30.0

#define CHECK_LOCK_TOLERANCE 300.0
#define CHECK_UNLOCK_TOLERANCE 30.0
#define CHECK_OPEN_TOLERANCE 60.0

typedef struct data_smc_gate {
//Monitor warnnings
  time_t last_open_warnning;

//Monitor auto triggers
  time_t auto_lock_time;
  time_t auto_unlock_time;
  time_t auto_open_time;

//Overwrite auto triggers
  boolean ignoreAutoTriggers;
} data_smc_gate;

/*
 *
 * STATE CONDITION DECLARATIONS
 *
 */

//Constants
#define SECS_IN_DAY (60*60*24)
#define MILIS_IN_DAY (1000*SECS_IN_DAY)
//Functions for checking condition transitions
boolean timeOutCheck(time_t triggerTime, float tolerance);
boolean timeOutCheckOnlyTime(time_t triggerTime, float tolerance);
//StateCondition factories
StateConditionList *conditions_stt_locked_create(StateNode *sttLock);
StateConditionList *conditions_stt_closed_create(StateNode *sttLock, StateNode *sttOpening);
StateConditionList *conditions_stt_unlock_create(StateNode *sttClosed);

/*
 *
 * STATE DECLARATIONS
 *
 */

StateList *GateStateList_createAll();
void State_Enter_base(char* , void*);
void State_Open_enter( void *data);


#endif
