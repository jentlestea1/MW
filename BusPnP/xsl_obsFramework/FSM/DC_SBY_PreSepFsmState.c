  
//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_SBY_PreSepFsmState.c
//
// This file was automatically generated by an XSL program

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"
#include "../FSM/FsmState.h"
#include "../FSM/DC_SBY_PreSepFsmState.h"

/////////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
/////////////////////////////////////////////////////////////////////////////////


    
static void doInit(void *obj) {
      return FSMSTATE_GET_CLASS(obj)->doInit((void*)(obj));
      // remove previous statement and insert application-specific code here
}
    
static void doContinue(void *obj) {
      return;
}
          
static bool isFinished(void *obj) {
      return DC_SBY_PRESEPFSMSTATE_GET_CLASS(obj)->isFinished((void*)(obj));
      // remove previous statement and insert application-specific code here
}
    


///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

// the following may be useful if you don't need it, just delete.
// DC_SBY_PreSepFsmState *this = DC_SBY_PRESEPFSMSTATE(obj)
static void instance_init(Object *obj)
{
      // insert application-specific code here
}

DC_SBY_PreSepFsmState* DC_SBY_PreSepFsmState_new(void)
{
        return (DC_SBY_PreSepFsmState*)object_new(TYPE_DC_SBY_PRESEPFSMSTATE);

}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
DC_SBY_PreSepFsmStateClass *dc_p_class = DC_SBY_PRESEPFSMSTATE_CLASS(oc);

    
        dc_p_class->doInit=doInit;
    
        dc_p_class->doContinue=doContinue;
          
        dc_p_class->isFinished=isFinished;
    

}

static const TypeInfo type_info = {
        .name = TYPE_DC_SBY_PRESEPFSMSTATE,
        .parent = TYPE_FSMSTATE,
        .instance_size = sizeof(DC_SBY_PreSepFsmState),
        .abstract = false,
        .class_size = sizeof(DC_SBY_PreSepFsmStateClass),
        .instance_init = instance_init,
        .class_init = class_init,

};

void DC_SBY_PreSepFsmState_register(void)
{
        type_register_static(&type_info);

}
            