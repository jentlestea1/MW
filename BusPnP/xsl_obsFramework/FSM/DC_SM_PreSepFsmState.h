  
//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_SM_PreSepFsmState.h
//
// This file was automatically generated by an XSL program

#ifndef DC_SM_PreSepFsmState_H
#define DC_SM_PreSepFsmState_H

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../FSM/FsmState.h"
#include "../Qom/object.h"

/**
 * Sample FsmState application class. FsmState component for the survival mode pre-separation 
 * submode.
 * <p>
 * This is a stub class. It provides dummy implementations for some of the virtual
 * methods of its superclass. 
 * This class was automatically generated by an XSL program that processes the
 * XML-based <i>target application model</i>. The XSL program  
 * searches the application model for all "FsmState" elements
 * which have a "Custom" subelement that indicates that a custom FsmState
 * class must be created. For each such element a class header file is created.
 * The base class of the generated class is assumed to be the class in the
 * "type" attribute of the FsmState element. 
 * The information in the application model is used to decide which virtual methods
 * should be overridden.
 * @todo Modify the generator meta-component generateRecoveryAction to generate the code
 * that sets the class identifier and to treat the default attributes in the custom recovery action description.
 * @author Automatically Generated Class
 * @version 1.0
 */

void DC_SM_PreSepFsmState_register(void);


/////////////////////////////////////////////////////////////////////////////////
//
//                              class and struct
//
/////////////////////////////////////////////////////////////////////////////////

struct DC_SM_PreSepFsmState {
    FsmState parent;
};


struct DC_SM_PreSepFsmStateClass {
    FsmStateClass parent_class;
    
    /**
     * Reset the telemetry manager, reset the telecommand manager.
     * <p>
     * This is a stub method that must be completed by the application developer.
     * This stub provides a default implementation that calls the <code>doInit</code> 
     * method of the superclass.
     */
    void (*doInit)(void *obj);
    
    /**
     * Dummy implementation that returns without taking any action. There is no continuation
     * action associated to this class.
     */
    void (*doContinue)(void *obj);
          
    /**
     * Terminate when the separation is detected.
     * <p>
     * This is a stub method that must be completed by the application developer.
     * This stub provides a default implementation that calls the <code>isFinished</code> 
     * method of the superclass.
     * @return true if the continuation action of this state has terminated, false otherwise
     */
    bool (*isFinished)(void *obj);
    
};


#define DC_SM_PRESEPFSMSTATE_GET_CLASS(obj) \
             OBJECT_GET_CLASS(DC_SM_PreSepFsmStateClass, obj, TYPE_DC_SM_PRESEPFSMSTATE)


#define DC_SM_PRESEPFSMSTATE_CLASS(klass) \
             OBJECT_CLASS_CHECK(DC_SM_PreSepFsmStateClass, klass, TYPE_DC_SM_PRESEPFSMSTATE)


#define DC_SM_PRESEPFSMSTATE(obj) \
             OBJECT_CHECK(DC_SM_PreSepFsmState, obj, TYPE_DC_SM_PRESEPFSMSTATE)


DC_SM_PreSepFsmState* DC_SM_PreSepFsmState_new(void);



#endif
             