  
//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_SampleRecoveryAction.h
//
// This file was automatically generated by an XSL program

#ifndef DC_SampleRecoveryAction_H
#define DC_SampleRecoveryAction_H

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../FDIR/RecoveryAction.h"
#include "../Qom/object.h"

/**
 * Sample application-specific recovery action.
 * <p>
 * This is a stub class. It provides dummy implementations for some of the virtual
 * methods of its superclass. 
 * This class was automatically generated by an XSL program that processes the
 * XML-based <i>target application model</i>. The XSL program searches 
 * the  searches the application model for all "RecoveryAction" elements
 * which have a "Custom" subelement that indicates that a custom recovery action
 * class must be created. For each such element a class header file is created.
 * The base class of the generated class is assumed to be the class in the
 * "type" attribute of the RecoveryAction element. 
 * The information in the application model is used to decide which virtual methods
 * should be overridden.
 * @todo Modify the generator meta-component generateRecoveryAction to generate the code
 * that sets the class identifier and to treat the default attributes in the custom recovery action description.
 * @author Automatically Generated Class
 * @version 1.0
 */
 
#define TYPE_DC_SAMPLERECOVERYACTION "dc_samplerecoveryaction"
void DC_SampleRecoveryAction_register(void);


/////////////////////////////////////////////////////////////////////////////////
//
//                              class and struct
//
/////////////////////////////////////////////////////////////////////////////////

struct DC_SampleRecoveryAction {
    RecoveryAction parent;
};


struct DC_SampleRecoveryActionClass {
    RecoveryActionClass parent_class;
    /**
     * This is a stub method that must be completed by the application developer.
     * This stub provides a default implementation that returns ACTION_SUCCESS but does not
     * otherwise take any action.
     * @return true if the continuation action of this state has terminated, false otherwise
     */
    TD_ActionOutcome (*doRecoveryAction)(void *obj);

};


#define DC_SAMPLERECOVERYACTION_GET_CLASS(obj) \
         OBJECT_GET_CLASS(DC_SampleRecoveryActionClass, obj, TYPE_DC_SAMPLERECOVERYACTION)


#define DC_SAMPLERECOVERYACTION_CLASS(klass) \
         OBJECT_CLASS_CHECK(DC_SampleRecoveryActionClass, klass, TYPE_DC_SAMPLERECOVERYACTION)


#define DC_SAMPLERECOVERYACTION(obj) \
         OBJECT_CHECK(DC_SampleRecoveryAction, obj, TYPE_DC_SAMPLERECOVERYACTION)


DC_SampleRecoveryAction* DC_SampleRecoveryAction_new(void);


#endif
             