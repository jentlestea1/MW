
//
// Copyright 2003 P&P Software GmbH - All Rights Reserved
//
// CC_RootObjectStack.c
//
// Version	1.0
// Date		30.08.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Base/CC_RootObject.h"
#include "CC_RootObjectStack.h"
;
       
///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////


void CC_RootObjectStack_setStackSize(CC_RootObjectStack *this, unsigned int size) {
   assert( this->size == 0);      // should not be called more than once
   assert( size > 0);             // stack size must be greater than zero

   this->pStack = (CC_RootObject**)malloc(size*sizeof(CC_RootObject*));
   assert( this->pStack!= pNULL );
   this->size = size;
   this->stackPointer = 0;
}

unsigned int CC_RootObjectStack_getStackSize(CC_RootObjectStack *this) {
   return this->size;
}

unsigned int CC_RootObjectStack_getNumberOfItems(CC_RootObjectStack *this) {
   return this->stackPointer;
}


void CC_RootObjectStack_push(CC_RootObjectStack *this, CC_RootObject* newItem) {
   assert( (this->pStack != pNULL) );

   if ( CC_RootObjectStack_isFull(this) )
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_STACK_FULL);
   else {
       this->pStack[this->stackPointer]=newItem;
       this->stackPointer++;
   }
   assert( this->stackPointer <= this->size );
}

CC_RootObject* CC_RootObjectStack_pop(CC_RootObjectStack *this) {
   assert( (this->pStack != pNULL) );

   if ( this->isEmpty() ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_STACK_EMPTY);
       return pNULL;
   } else {
       this->stackPointer--;
       return this->pStack[this->stackPointer];
   }
}

bool CC_RootObjectStack_isFull(CC_RootObjectStack *this) {
   assert( (this->pStack != pNULL) );
   return (this->stackPointer==this->size);
}

bool CC_RootObjectStack_isEmpty(CC_RootObjectStack *this) {
   assert( (this->pStack != pNULL) );
   return (this->stackPointer==0);
}

void CC_RootObjectStack_reset(CC_RootObjectStack *this) {
   assert( (this->pStack != pNULL) );
   this->stackPointer = 0;
}

/////////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
/////////////////////////////////////////////////////////////////////////////////


static bool isObjectConfigured(void* obj) {

   // Check configuration of super object
   if ( !CC_ROOTOBJECT(obj)->isObjectConfigured() )
       return NOT_CONFIGURED;

   if ( (CC_ROOTOBJECTSTACK(obj)->pStack == pNULL) )
       return NOT_CONFIGURED;
   return CONFIGURED;
}

///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

// the following may be useful if you don't need it, just delete.
// CC_RootObjectStack *this = CC_ROOTOBJECTSTACK(obj)
static void instance_init(Object *obj)
{

    CC_ROOTOBJECTSTACK(obj)->size = 0;
    CC_ROOTOBJECTSTACK(obj)->stackPointer = 0;
    CC_ROOTOBJECTSTACK(obj)->pStack = pNULL;
	CC_RootObject_setClassId(ID_ROOTOBJECTSTACK);

}

CC_RootObjectStack* CC_RootObjectStack_new(void)
{
        return (CC_RootObjectStack*)object_new(TYPE_CC_ROOTOBJECTSTACK);

}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
CC_RootObjectStackClass *dc_p_class = CC_ROOTOBJECTSTACK_CLASS(oc);

        dc_p_class->isObjectConfigured = isObjectConfigured;

}

static const TypeInfo type_info = {
        .name = TYPE_CC_ROOTOBJECTSTACK,
        .parent = TYPE_CC_ROOTOBJECT,
        .instance_size = sizeof(CC_RootObjectStack),
        .abstract = false,
        .class_size = sizeof(CC_RootObjectStackClass),
        .instance_init = instance_init,
        .class_init = class_init,

};

void CC_RootObjectStack_register(void)
{
        type_register_static(&type_info);

}
