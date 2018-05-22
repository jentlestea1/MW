  
//
// Copyright 2003 P&P Software GmbH - All Rights Reserved
//
// TestCaseSampleFullDataPool_1.h
//
// Version	1.0
// Date		10.09.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_SampleFullDataPool.h"
#include "../Data/DC_DataItem.h"
#include "../System/DC_DummyObsClock.h"
#include "../FDIR/DC_NullProfile.h"
#include "../FDIR/DC_NullRecoveryAction.h"
#include "TestCaseSampleFullDataPool_1.h"
#include "../Utilities/TestCaseWithEvtCheck.h"

#include <math.h>
#include <float.h>


/////////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
/////////////////////////////////////////////////////////////////////////////////


static void runTestCase(void *obj,TD_Integer value)
{

    // Variable to hold the number of events
    unsigned int nEvt;
    nEvt = getNumberOfEvents();

    // Variable to hold number of parameters in the data pool
    TD_DataPoolId numberOfPar = 8;

    // Variable to hold first identifier of a real-value parameter
    TD_DataPoolId firstRealId = 2;

    // Variable to hold first identifier of an integer-valued parameter
    TD_DataPoolId firstIntegerId = 1;

    // Instantiate datapool
    DC_SampleFullDataPool* pDP = new DC_SampleFullDataPool();

    // Variable to hold maximum parameter identifier
    TD_DataPoolId maxParId;
    maxParId = 11;

    // Auxiliary variable to hold a data pool item identifier
    TD_DataPoolId id;
    id = 0;

    // Variable to hold the lowest illegal parameter id
    TD_DataPoolId lowestIllegalParId;
    lowestIllegalParId = (TD_DataPoolId)3;

    // Verify correctness of class ID
    if (pDP->getClassId() != ID_SAMPLEFULLDATAPOOL)
    {      setTestResult(TEST_FAILURE, "Wrong class ID");
            return;
    }

    // Check default value of validity status.
    
    if ( !pDP->isValid(1) )
    {      setTestResult(TEST_FAILURE, "Wrong default validity status on data item 1");
            return;
    }
    
    if ( !pDP->isValid(2) )
    {      setTestResult(TEST_FAILURE, "Wrong default validity status on data item 2");
            return;
    }
    
    if ( !pDP->isValid(4) )
    {      setTestResult(TEST_FAILURE, "Wrong default validity status on data item 4");
            return;
    }
    
    if ( !pDP->isValid(5) )
    {      setTestResult(TEST_FAILURE, "Wrong default validity status on data item 5");
            return;
    }
    
    if ( !pDP->isValid(7) )
    {      setTestResult(TEST_FAILURE, "Wrong default validity status on data item 7");
            return;
    }
    
    if ( !pDP->isValid(8) )
    {      setTestResult(TEST_FAILURE, "Wrong default validity status on data item 8");
            return;
    }
    
    if ( !pDP->isValid(10) )
    {      setTestResult(TEST_FAILURE, "Wrong default validity status on data item 10");
            return;
    }
    
    if ( !pDP->isValid(11) )
    {      setTestResult(TEST_FAILURE, "Wrong default validity status on data item 11");
            return;
    }
    
    // Check that the data pool is not yet configured
    if ( pDP->isObjectConfigured() != NOT_CONFIGURED )
    {    setTestResult(TEST_FAILURE, "Incorrect configuration status at creation");
          return;
    }

    // Create and load dummy clock
    DC_DummyObsClock* pClk = new DC_DummyObsClock();
    TD_ObsTime time = (TD_ObsTime)10;
    pClk->setTime(time);
    pClk->setCycle(0);
    pDP->setObsClock(pClk);
    if ( pDP->getObsClock() != pClk )
    {      setTestResult(TEST_FAILURE, "Incorrect OBS Clock");
            return;
    }

    // Check that the data pool is not yet configured
    if ( pDP->isObjectConfigured() != NOT_CONFIGURED )
    {      setTestResult(TEST_FAILURE, "Incorrect configuration status at creation");
            return;
    }

    // Load monitoring profiles and check correctness of load operations
    DC_NullProfile* pNP = new DC_NullProfile();  
    pDP->setMonitoringProfile(1,pNP);
    if (pDP->getMonitoringProfile(1)!=pNP)
    {	setTestResult(TEST_FAILURE, "Failure to read back monitoring profile");
        return;
    }
    
    pDP->setMonitoringProfile(2,pNP);
    if (pDP->getMonitoringProfile(2)!=pNP)
    {	setTestResult(TEST_FAILURE, "Failure to read back monitoring profile");
        return;
    }
    
    pDP->setMonitoringProfile(4,pNP);
    if (pDP->getMonitoringProfile(4)!=pNP)
    {	setTestResult(TEST_FAILURE, "Failure to read back monitoring profile");
        return;
    }
    
    pDP->setMonitoringProfile(5,pNP);
    if (pDP->getMonitoringProfile(5)!=pNP)
    {	setTestResult(TEST_FAILURE, "Failure to read back monitoring profile");
        return;
    }
    
    pDP->setMonitoringProfile(7,pNP);
    if (pDP->getMonitoringProfile(7)!=pNP)
    {	setTestResult(TEST_FAILURE, "Failure to read back monitoring profile");
        return;
    }
    
    pDP->setMonitoringProfile(8,pNP);
    if (pDP->getMonitoringProfile(8)!=pNP)
    {	setTestResult(TEST_FAILURE, "Failure to read back monitoring profile");
        return;
    }
    
    pDP->setMonitoringProfile(10,pNP);
    if (pDP->getMonitoringProfile(10)!=pNP)
    {	setTestResult(TEST_FAILURE, "Failure to read back monitoring profile");
        return;
    }
    
    pDP->setMonitoringProfile(11,pNP);
    if (pDP->getMonitoringProfile(11)!=pNP)
    {	setTestResult(TEST_FAILURE, "Failure to read back monitoring profile");
        return;
    }
    
    // Load recovery actions and check correctness of load operations
    DC_NullRecoveryAction* pRA = new DC_NullRecoveryAction();  
    pDP->setRecoveryAction(1,pRA);
    if (pDP->getRecoveryAction(1)!=pRA)
    {	setTestResult(TEST_FAILURE, "Failure to read back recovery action");
        return;
    }
    
    pDP->setRecoveryAction(2,pRA);
    if (pDP->getRecoveryAction(2)!=pRA)
    {	setTestResult(TEST_FAILURE, "Failure to read back recovery action");
        return;
    }
    
    pDP->setRecoveryAction(4,pRA);
    if (pDP->getRecoveryAction(4)!=pRA)
    {	setTestResult(TEST_FAILURE, "Failure to read back recovery action");
        return;
    }
    
    pDP->setRecoveryAction(5,pRA);
    if (pDP->getRecoveryAction(5)!=pRA)
    {	setTestResult(TEST_FAILURE, "Failure to read back recovery action");
        return;
    }
    
    pDP->setRecoveryAction(7,pRA);
    if (pDP->getRecoveryAction(7)!=pRA)
    {	setTestResult(TEST_FAILURE, "Failure to read back recovery action");
        return;
    }
    
    pDP->setRecoveryAction(8,pRA);
    if (pDP->getRecoveryAction(8)!=pRA)
    {	setTestResult(TEST_FAILURE, "Failure to read back recovery action");
        return;
    }
    
    pDP->setRecoveryAction(10,pRA);
    if (pDP->getRecoveryAction(10)!=pRA)
    {	setTestResult(TEST_FAILURE, "Failure to read back recovery action");
        return;
    }
    
    pDP->setRecoveryAction(11,pRA);
    if (pDP->getRecoveryAction(11)!=pRA)
    {	setTestResult(TEST_FAILURE, "Failure to read back recovery action");
        return;
    }
    
    // Check that the data pool is configured
    if ( pDP->isObjectConfigured() != CONFIGURED )
     {      setTestResult(TEST_FAILURE, "Incorrect configuration status");
            return;
      }

    // Check data setting and getting services for the data pool item values
    // Do it for the real-value items first and then for the interger-valued items

    id = 2;
    pDP->setValue(id,(TD_Float)id);
    if ( fabs((float)(pDP->getFloatValue(id)-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    if ( fabs((float)((*pDP->getPointerFloatValue(id))-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    id = 5;
    pDP->setValue(id,(TD_Float)id);
    if ( fabs((float)(pDP->getFloatValue(id)-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    if ( fabs((float)((*pDP->getPointerFloatValue(id))-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    id = 8;
    pDP->setValue(id,(TD_Float)id);
    if ( fabs((float)(pDP->getFloatValue(id)-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    if ( fabs((float)((*pDP->getPointerFloatValue(id))-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    id = 11;
    pDP->setValue(id,(TD_Float)id);
    if ( fabs((float)(pDP->getFloatValue(id)-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    if ( fabs((float)((*pDP->getPointerFloatValue(id))-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    id = 1;
    pDP->setValue(id,(TD_Integer)id);
    if ( pDP->getIntegerValue(id)!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    if ( (*pDP->getPointerIntegerValue(id))!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    id = 4;
    pDP->setValue(id,(TD_Integer)id);
    if ( pDP->getIntegerValue(id)!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    if ( (*pDP->getPointerIntegerValue(id))!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    id = 7;
    pDP->setValue(id,(TD_Integer)id);
    if ( pDP->getIntegerValue(id)!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    if ( (*pDP->getPointerIntegerValue(id))!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    id = 10;
    pDP->setValue(id,(TD_Integer)id);
    if ( pDP->getIntegerValue(id)!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    if ( (*pDP->getPointerIntegerValue(id))!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    // Check the time stamp of a data pool item
    if ( pDP->getTimeStamp(1)!=time )
    {	setTestResult(TEST_FAILURE, "Wrong time stamp");
        return;
    }

    // Check the setting/getting of the validity status
    id = 1;
    pDP->setValidityStatus(id,false);
    if ( pDP->isValid(id) )
    {      setTestResult(TEST_FAILURE, "Wrong validity status");
           return;
    }

    // Check illegal attempt to set the validity status
    if (isNonNominalCheckAllowed()) {
        pDP->setValidityStatus(11+1,false);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt = nEvt+1;
    }

    // Reset the data pool and check that all items are valid
    id = 1;
    pDP->setValidityStatus(id,false);
    pDP->reset();
    if ( !pDP->isValid(id) )
    {      setTestResult(TEST_FAILURE, "Reset failure");
           return;
    }


    // Check the back-up value mechanism  (for an integer-valued data pool item)
    id = 1;
    TD_Integer oldValue = pDP->getIntegerValue(id);
    pDP->setValidityStatus(id,false);
    pDP->setValue(id,(TD_Integer)(oldValue+1));
    if ( pDP->getIntegerValue(id)!=oldValue )
    {      setTestResult(TEST_FAILURE, "Back-up value failure");
            return;
    }
    if ( pDP->getDataItem(id)->getIntegerValue()!=oldValue )
    {	setTestResult(TEST_FAILURE, "Back-up value failure");
        return;
    }
    pDP->setValidityStatus(id,true);
    pDP->setValue(id,(TD_Integer)(oldValue+1));
    if ( pDP->getIntegerValue(id)!=(oldValue+1) )
    {      setTestResult(TEST_FAILURE, "Back-up value failure");
           return;
    }
    if ( pDP->getDataItem(id)->getIntegerValue()!=(oldValue+1) )
    {      setTestResult(TEST_FAILURE, "Back-up value failure");
           return;
    }

    // Check the back-up value mechanism  (for a real-valued data pool item)
    id = 2;
    TD_Float fOldValue = pDP->getFloatValue(id);
    pDP->setValidityStatus(id,false);
    pDP->setValue(id,(TD_Float)(fOldValue+1.0));
    if ( fabs( (float)(pDP->getFloatValue(id)-fOldValue) )>FLT_EPSILON )
    {      setTestResult(TEST_FAILURE, "Back-up value failure");
           return;
    }
    pDP->setValidityStatus(id,true);
    pDP->setValue(id,(TD_Float)(fOldValue+1.0));
    if ( fabs( (float)(pDP->getFloatValue(id)-(fOldValue+1.0)) )>FLT_EPSILON )
    {      setTestResult(TEST_FAILURE, "Back-up value failure");
           return;
    }

    // Check the iteration service
    TD_DataPoolId counter = 0;
    for (TD_DataPoolId i=pDP->firstIdentifier(); !pDP->isLastIdentifier(); i=pDP->nextIdentifier()) {
        counter++;
        pDP->setValidityStatus(i,false);        // dummy call  just to exercise data pool access
    }
    if ( counter!=numberOfPar )
    {   setTestResult(TEST_FAILURE, "Error in data pool iteration");
        return;
    }

    if ( !pDP->isFloat(firstRealId) || pDP->isInteger(firstRealId) )
    {   setTestResult(TEST_FAILURE, "Error in type checking service");
        return;
    }
    if ( !pDP->isInteger(firstIntegerId) || pDP->isFloat(firstIntegerId) )
    {   setTestResult(TEST_FAILURE, "Error in type checking service");
        return;
    }

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;
}
   

///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

// the following may be useful if you don't need it, just delete.
// TestCaseSampleFullDataPool_1 *this = TESTCASESAMPLEFULLDATAPOOL_1(obj)


/**
 * Set the identifier and the name of the test case to: 
 * ID_SAMPLEFULLDATAPOOL*10+1 and "TestCaseSampleFullDataPool_1".
 */
static void instance_init(Object *obj)
{
    (TestCase*)(obj)->testId=ID_SAMPLEFULLDATAPOOL*10+1;
    (TestCase*)(obj)->testName=TestCaseSampleFullDataPool_1;
    return;
}

TestCaseSampleFullDataPool_1* TestCaseSampleFullDataPool_1_new(void)
{
        return (TestCaseSampleFullDataPool_1*)object_new(TYPE_TESTCASESAMPLEFULLDATAPOOL_1);

}

///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////
static void class_init(ObjectClass *oc, void *data)
{
TestCaseSampleFullDataPool_1Class *t_p_class = TESTCASESAMPLEFULLDATAPOOL_1_CLASS(oc);

        t_p_class->runTestCase = runTestCase;

}

static const TypeInfo type_info = {
        .name = TYPE_TESTCASESAMPLEFULLDATAPOOL_1,
        .parent = TYPE_TESTCASEWITHWITHEVTCHECK,
        .instance_size = sizeof(TestCaseSampleFullDataPool_1),
        .abstract = false,
        .class_size = sizeof(TestCaseSampleFullDataPool_1Class),
        .instance_init = instance_init,
        .class_init = class_init,

};

void TestCaseSampleFullDataPool_1_register(void)
{
        type_register_static(&type_info);

}
