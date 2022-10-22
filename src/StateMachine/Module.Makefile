#### Module State Machine
MODULE_STATEMACHINE=$(SRC_DIR)/StateMachine

##### SubModules State Machine
SUBMODOBJ_STATEMACHINE_TRANSITION=$(TST_DIR)/transition.o
SUBMODOBJ_STATEMACHINE_TRANSITION_LIST=$(SUBMODOBJ_STATEMACHINE_TRANSITION:.o=List.o)
MODOBJ_STATEMACHINE_TRANSITION=$(SUBMODOBJ_STATEMACHINE_TRANSITION) $(SUBMODOBJ_STATEMACHINE_TRANSITION_LIST)

SUBMODOBJ_STATEMACHINE_CONDITION=$(TST_DIR)/stateCondition.o
SUBMODOBJ_STATEMACHINE_CONDITION_LIST=$(SUBMODOBJ_STATEMACHINE_CONDITION:.o=List.o)
MODOBJ_STATEMACHINE_CONDITION=$(SUBMODOBJ_STATEMACHINE_CONDITION) $(SUBMODOBJ_STATEMACHINE_CONDITION_LIST)

SUBMODOBJ_STATEMACHINE_STATE=$(TST_DIR)/state.o
SUBMODOBJ_STATEMACHINE_STATE_LIST=$(SUBMODOBJ_STATEMACHINE_STATE:.o=List.o)
MODOBJ_STATEMACHINE_STATE=$(SUBMODOBJ_STATEMACHINE_STATE) $(SUBMODOBJ_STATEMACHINE_STATE_LIST)

SUBMODOBJ_STATEMACHINE_BODY=$(TST_DIR)/stateMachine.o
SUBMODOBJ_STATEMACHINE_BODY_LIST=$(SUBMODOBJ_STATEMACHINE_BODY:.o=List.o)
MODOBJ_STATEMACHINE_BODY=$(SUBMODOBJ_STATEMACHINE_BODY) $(SUBMODOBJ_STATEMACHINE_BODY_LIST)

MODOBJ_STATEMACHINE=$(MODOBJ_STATEMACHINE_TRANSITION) $(MODOBJ_STATEMACHINE_CONDITION) $(MODOBJ_STATEMACHINE_STATE) $(MODOBJ_STATEMACHINE_BODY)

$(MODOBJ_STATEMACHINE): $(shell find $(MODULE_STATEMACHINE) $(FNDARGS))
	$(SAFE)  $(MKC) $(MODULE_STATEMACHINE) full_mod

