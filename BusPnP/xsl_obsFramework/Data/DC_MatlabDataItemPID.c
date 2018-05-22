  
//
// Copyright 2003 P&P Software GmbH - All Rights Reserved
//
// DC_MatlabDataItemPID.c
//
// This is an automatically generated file

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_DataItem.h"
#include "../Data/DataPool.h"
#include "DC_MatlabDataItemPID.h"

///////////////////////////////////////////////////////////////////////////////
//
//                            class data
//
///////////////////////////////////////////////////////////////////////////////

static unsigned int numberOfInstances=0;



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////



static void propagateState(void *obj) {
#ifdef HAVE_SIMULINK
    for (unsigned int i=0; i<DC_MATLABDATAITEMPID(obj)->numberOfParameters; i++)
    *DC_MATLABDATAITEMPID(obj)->modelParameters[i]=(real_T)CONTROLBLOCK(obj)->p[i];

    for (unsigned int i=0; i<DC_MATLABDATAITEMPID(obj)->numberOfInputs; i++)
        *DC_MATLABDATAITEMPID(obj)->modelInputs[i]=(real_T)DC_DATAITEM_GET_CLASS(DATAITEMCONTROLBLOCK(obj)->pDIU[i])->getFloatValue();
#endif
}

static void updateOutput(void *obj) {
#ifdef HAVE_SIMULINK
    modelStep();

    for (unsigned int i=0;i<DC_MATLABDATAITEMPID(obj)->numberOfOutputs;i++)
        DC_DATAITEM_GET_CLASS(DATAITEMCONTROLBLOCK(obj)->pDIY[i])->setFloatValue((TD_Float)*modelOutputs[i]);
#endif
}

static void reset(void *obj) {
#ifdef HAVE_SIMULINK
        DC_MATLABDATAITEMPID_GET_CLASS(obj)->modelInitialize(1);
#endif
}


///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////
// the following may be useful if you don't need it, just delete.
//  *this = DC_MATLABDATAITEMPID(obj)
    /**
     * Configure the PID control block. The control block is configured to have one
     * input, one outputs, three parameters. The three parameters represent
     * the proportional, integral and derivative gain. The number of states is
     * set to zero because the state is maintained internally to the
     * Simulink-generated code. The Simulink model is initialized by calling
     * the reset method.
     * The class identifier is set.
     * A pseudo-code implementation of this method therefore is:
     *    . . . // set up internal data structures to link to matlab code
     *    . . . // set class identifier
     *    setNumberOfStates(0);
     *    setNumberOfInputs(1);
     *    setNumberOfOutputs(1);
     *    setNumberOfParameters(3);
     *    reset(); 
     * Note that the number of states is set to zero because the matlab
     * code already provides a data structure to save the propagation state.
     * 
     * This class should only be instantiated once.
     */
static void instance_init(object* obj) {
    // The Simulink model is NOT reentrant, thus we
    // can only have one instance of this object
    assert(numberOfInstances==0);
    numberOfInstances++;

    DC_MATLABDATAITEMPID(obj)->numberOfInputs=1;
    DC_MATLABDATAITEMPID(obj)->numberOfOutputs=1;
    DC_MATLABDATAITEMPID(obj)->numberOfParameters=3;
#ifdef HAVE_SIMULINK
   DC_MATLABDATAITEMPID(obj)->modelStep =PID_step;
   DC_MATLABDATAITEMPID(obj)->modelInitialize =PID_init;

   DC_MATLABDATAITEMPID(obj)->modelInputs =(new real_T*)malloc(DC_MATLABDATAITEMPID(obj)->numberOfInputs);
    DC_MATLABDATAITEMPID(obj)->modelOutputs =(new real_T*)malloc(DC_MATLABDATAITEMPID(obj)->numberOfOutputs);
    DC_MATLABDATAITEMPID(obj)->modelParameters =(real_T*)malloc(DC_MATLABDATAITEMPID(obj)->numberOfParameters);

    DC_MATLABDATAITEMPID(obj)->modelInputs[0] =&Input;//这里的Input好像是pid.h里面的
    DC_MATLABDATAITEMPID(obj)->modelOutputs[0]   =&Output;DC_MATLABDATAITEMPID(obj)->modelParameters[1-1]=&;DC_MATLABDATAITEMPID(obj)->modelParameters[2-1]=&;DC_MATLABDATAITEMPID(obj)->modelParameters[3-1]=&;
#endif
    CONTROLBLOCK_GET_CLASS(obj)->setNumberOfStates(0);
    CONTROLBLOCK_GET_CLASS(obj)->setNumberOfInputs(DC_MATLABDATAITEMPID(obj)->numberOfInputs);
    CONTROLBLOCK_GET_CLASS(obj)->setNumberOfOutputs(DC_MATLABDATAITEMPID(obj)->numberOfOutputs);
    CONTROLBLOCK_GET_CLASS(obj)->setNumberOfParameters(DC_MATLABDATAITEMPID(obj)->numberOfParameters);

    CC_ROOTOBJECT_GET_CLASS(obj)->setClassId(ID_MATLABDATAITEMPID);

    // Initialize the Simulink model
    reset();
}
DC_MatlabDataItemPID* DC_MatlabDataItemPID_new(void)
{
    return (DC_MatlabDataItemPID*)object_new(TYPE_DC_MATLABDATAITEMPID);
}


///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    DC_MatlabDataItemPIDClass *dc_p_class = DC_MATLABDATAITEMPID_CLASS(oc);

    dc_p_class->propagateState=propagateState;
    dc_p_class->updateOutput=updateOutput;
    dc_p_class->reset=reset;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_MATLABDATAITEMPID,
    .parent =
 DataItemControlBlockClass,
    .instance_size = sizeof(DC_MatlabDataItemPID),
    .abstract = false,
    .class_size = sizeof(DC_MatlabDataItemPIDClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_MatlabDataItemPID_register(void)
{
    type_register_static(&type_info);
}
