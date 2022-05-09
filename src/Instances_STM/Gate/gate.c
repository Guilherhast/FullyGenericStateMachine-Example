#include "gate.h"

// Receive gate smc
void SmcGate_SwitchToState(StateMachine *gate_smc, State *stt) {
  if (stt == NULL) {
    return;
  }
  // Watch out for the state not being in state list
  data_smc_gate *smc_data = (data_smc_gate *)gate_smc->data;
  smc_data->triggeredInternally = true;
  gate_smc->stateTo = stt;
}
void SmcGate_SwitchToStateByName(StateMachine *gate_smc, char *sttName) {
  SmcGate_SwitchToState(gate_smc,
                        State_searchByName(gate_smc->possibleStates, sttName));
}

StateMachine *SmcGate_create() {
  // Creating linked list of states

  // Initialize auto lock and auto unlock time
  // Also auto open

  // When the state machine make a test
  // If it is true ( put the internally triggered flag)
  return NULL;
}
