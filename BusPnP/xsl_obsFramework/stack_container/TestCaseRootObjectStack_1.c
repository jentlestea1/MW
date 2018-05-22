

//
// Copyright 2003 P&P Software GmbH - All Rights Reserved
//
// TestCaseRootObjectStack_1.c
//
// Version	1.0
// Date		10.09.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../System/CC_RootObjectStack.h"
#include "TestCaseRootObjectStack_1.h"
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
   CC_RootObjectStack* pStack = new CC_RootObjectStack();
   unsigned int size = 2;
   unsigned int nEvt = getNumberOfEvents();
   CC_RootObject* pItem1 = new CC_RootObject();
     
   // Check the value of the class identifier
   if ( pStack->getClassId() != ID_ROOTOBJECTSTACK )
   {    setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
   }

   // Check configuration status
   if ( pStack->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Set the stack size
   pStack->setStackSize(size);
   if ( pStack->getStackSize() != size)
   {    setTestResult(TEST_FAILURE, "Wrong stack size value");
        return;
   }

   // Check configuration status
   if ( !pStack->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Push one item on stack and check correctness
   pStack->push(pItem1);
   if ( pStack->getNumberOfItems() != 1 )
   {    setTestResult(TEST_FAILURE, "Wrong number of items on stack");
        return;
   }
   
   if ( pStack->pop() != pItem1 )
   {    setTestResult(TEST_FAILURE, "Wrong item on stack");
        return;
   } 

   // Check that a pop operation returns pNULL and generates correct event
   if ( pStack->pop() != pNULL )
   {    setTestResult(TEST_FAILURE, "Wrong item on stack");
        return;
   }
   if ( !verifyLatestEvent(nEvt+1,EVT_STACK_EMPTY) )
   {    setTestResult(TEST_FAILURE, "Wrong event");
        return;
   }

   // Perform three push operations and verify event generation
   pStack->push(pItem1);
   pStack->push(pItem1);
   if ( !pStack->isFull() )
   {    setTestResult(TEST_FAILURE, "Stack should be full");
        return;
   }
   pStack->push(pItem1);
   if ( !verifyLatestEvent(nEvt+2,EVT_STACK_FULL) )
   {    setTestResult(TEST_FAILURE, "Wrong event");
        return;
   }

   // Check that there are only two items on the stack
   if ( pStack->getNumberOfItems()!=2 )
   {    setTestResult(TEST_FAILURE, "wrong number of items in stack");
        return;
   }

   // Perform a stack reset and check success
   pStack->reset();
   if ( pStack->getNumberOfItems() != 0 )
   {    setTestResult(TEST_FAILURE, "Reset operation failed");
        return;
   }
   if ( !pStack->isEmpty() )
   {    setTestResult(TEST_FAILURE, "Reset operation failed");
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
// TestCaseRootObjectStack_1 *this = TESTCASEROOTOBJECTSTACK_1(obj)

/**
 * Set the identifier and the name of the test case to: 
 * ID_ROOTOBJECTSTACK*10+1 and "TestCaseRootObjectStack_1".
 */
static void instance_init(Object *obj)
{
    (TestCase*)(obj)->testId=ID_ROOTOBJECTSTACK*10+1;
    (TestCase*)(obj)->testName=TestCaseRootObjectStack_1;
    return;
}

TestCaseRootObjectStack_1* TestCaseRootObjectStack_1_new(void)
{
        return (TestCaseRootObjectStack_1*)object_new(TYPE_TESTCASEROOTOBJECTSTACK_1);

}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
TestCaseRootObjectStack_1Class *t_p_class = TESTCASEROOTOBJECTSTACK_1_CLASS(oc);

        t_p_class->runTestCase = runTestCase;

}

static const TypeInfo type_info = {
        .name = TYPE_TESTCASEROOTOBJECTSTACK_1,
        .parent = TYPE_TESTCASEWITHWITHEVTCHECK,
        .instance_size = sizeof(TestCaseRootObjectStack_1),
        .abstract = false,
        .class_size = sizeof(TestCaseRootObjectStack_1Class),
        .instance_init = instance_init,
        .class_init = class_init,

};

void TestCaseRootObjectStack_1_register(void)
{
        type_register_static(&type_info);

}

