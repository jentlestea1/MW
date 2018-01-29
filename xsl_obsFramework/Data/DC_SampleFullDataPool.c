  
//
// Copyright 2003 P&P Software GmbH - All Rights Reserved
//
// DC_SampleFullDataPool.c
//
// Automatically generated file

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../System/ObsClock.h"
#include "../Data/DC_SettableDataItem.h"
#include "DC_SampleFullDataPool.h"

static unsigned int const TD_FloatCode = 1;
static unsigned int const TD_IntegerCode = 2;


///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////


void DC_SampleFullDataPool_setObsClock(DC_SampleFullDataPool *this, ObsClock* pObsClock)
{
    assert( pObsClock != pNULL );               
    this->pObsClock = pObsClock;
}

ObsClock* DC_SampleFullDataPool_getObsClock(const DC_SampleFullDataPool *this)
{
    return this->pObsClock;
}





///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////






static void setValueFloat(void *obj,TD_DataPoolId id, TD_Float newValue) {
    assert( id <= DC_SAMPLEFULLDATAPOOL(obj)->maxParId );               
    assert( DC_SAMPLEFULLDATAPOOL(obj)->type[id] == TD_FloatCode );
 
    if ( id > DC_SAMPLEFULLDATAPOOL(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return;
    }
    if ( DC_SAMPLEFULLDATAPOOL(obj)->type[id] != TD_FloatCode ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return;
    }
    (*(TD_Float*)DC_SAMPLEFULLDATAPOOL(obj)->pValue[id]) = newValue;        DC_SAMPLEFULLDATAPOOL(obj)->timeStamp[id] = DC_SAMPLEFULLDATAPOOL(obj)->pObsClock->getTime();        
    if ( DC_SAMPLEFULLDATAPOOL(obj)->valid[id] )
        (*(TD_Float*)DC_SAMPLEFULLDATAPOOL(obj)->pBackUpValue[id]) = newValue;          
}

static void setValueInt(void *obj, TD_DataPoolId id, TD_Integer newValue) {
    assert( id <= DC_SAMPLEFULLDATAPOOL(obj)->maxParId );           
    assert( DC_SAMPLEFULLDATAPOOL(obj)->type[id] == TD_IntegerCode );
 
    if ( id > DC_SAMPLEFULLDATAPOOL(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return;
    }
    if ( DC_SAMPLEFULLDATAPOOL(obj)->type[id] != TD_IntegerCode ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return;
    }
    (*(TD_Integer*)DC_SAMPLEFULLDATAPOOL(obj)->pValue[id]) = newValue;      DC_SAMPLEFULLDATAPOOL(obj)->timeStamp[id] = DC_SAMPLEFULLDATAPOOL(obj)->pObsClock->getTime();        
    if ( DC_SAMPLEFULLDATAPOOL(obj)->valid[id] )
        (*(TD_Integer*)DC_SAMPLEFULLDATAPOOL(obj)->pBackUpValue[id]) = newValue;        
}

static TD_Float getFloatValue(void *obj, TD_DataPoolId id) {
    assert( id <= DC_SAMPLEFULLDATAPOOL(obj)->maxParId );           
    assert( DC_SAMPLEFULLDATAPOOL(obj)->type[id] == TD_FloatCode );
 
    if ( id > DC_SAMPLEFULLDATAPOOL(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return (TD_Float)0;
    }
    if ( DC_SAMPLEFULLDATAPOOL(obj)->type[id] != TD_FloatCode ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return (TD_Float)0;
    }
    if ( DC_SAMPLEFULLDATAPOOL(obj)->valid[id] )
        return (*(TD_Float*)DC_SAMPLEFULLDATAPOOL(obj)->pValue[id]);
    else
        return (*(TD_Float*)DC_SAMPLEFULLDATAPOOL(obj)->pBackUpValue[id]);
   
}

static TD_Integer getIntegerValue(void *obj, TD_DataPoolId id) {
    assert( id <= DC_SAMPLEFULLDATAPOOL(obj)->maxParId );           
    assert( DC_SAMPLEFULLDATAPOOL(obj)->type[id] == TD_IntegerCode );
 
    if ( id > DC_SAMPLEFULLDATAPOOL(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return (TD_Integer)0;
    }
    if ( DC_SAMPLEFULLDATAPOOL(obj)->type[id] != TD_IntegerCode ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return (TD_Integer)0;
    }
    if ( DC_SAMPLEFULLDATAPOOL(obj)->valid[id] )
        return (*(TD_Integer*)DC_SAMPLEFULLDATAPOOL(obj)->pValue[id]);
    else
        return (*(TD_Integer*)DC_SAMPLEFULLDATAPOOL(obj)->pBackUpValue[id]);
   
}

static TD_Float* getPointerFloatValue(void *obj, TD_DataPoolId id) {
    assert( id <= DC_SAMPLEFULLDATAPOOL(obj)->maxParId );           
    assert( DC_SAMPLEFULLDATAPOOL(obj)->type[id] == TD_FloatCode );
 
    if ( id > DC_SAMPLEFULLDATAPOOL(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return DC_SAMPLEFULLDATAPOOL(obj)->pDefaultFloat;
    }
    if ( DC_SAMPLEFULLDATAPOOL(obj)->type[id] != TD_FloatCode ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return DC_SAMPLEFULLDATAPOOL(obj)->pDefaultFloat;
     }
    return ((TD_Float*)DC_SAMPLEFULLDATAPOOL(obj)->pValue[id]);
}

static TD_Integer* getPointerIntegerValue(void *obj, TD_DataPoolId id) {
    assert( id <= DC_SAMPLEFULLDATAPOOL(obj)->maxParId );           
    assert( DC_SAMPLEFULLDATAPOOL(obj)->type[id] == TD_IntegerCode );
 
    if ( id > DC_SAMPLEFULLDATAPOOL(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return DC_SAMPLEFULLDATAPOOL(obj)->pDefaultInt;
    }
    if ( DC_SAMPLEFULLDATAPOOL(obj)->type[id] != TD_IntegerCode ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return DC_SAMPLEFULLDATAPOOL(obj)->pDefaultInt;
    }
    return ((TD_Integer*)DC_SAMPLEFULLDATAPOOL(obj)->pValue[id]);
}

static DC_DataItem* getDataItem(void *obj, TD_DataPoolId id) {
    assert( id <= DC_SAMPLEFULLDATAPOOL(obj)->maxParId );           
    assert( DC_SAMPLEFULLDATAPOOL(obj)->type[id] != -1 );
 
    if ( id > DC_SAMPLEFULLDATAPOOL(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
       DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
       return DATAPOOL_GET_CLASS(obj)->getDataItem(id);
    }
    if ( type[id] == -1 ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
       return DATAPOOL_GET_CLASS(obj)->getDataItem(id);
    }
 return DC_SAMPLEFULLDATAPOOL(obj)->pDataItem[id];
}

 
static TD_ObsTime getTimeStamp(void *obj,TD_DataPoolId id) {
    assert( id <= DC_SAMPLEFULLDATAPOOL(obj)->maxParId );           
    assert( DC_SAMPLEFULLDATAPOOL(obj)->type[id] != -1 );
 
    if ( id > DC_SAMPLEFULLDATAPOOL(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
       return DATAPOOL_GET_CLASS(obj)->getTimeStamp(id);
    }
    if ( DC_SAMPLEFULLDATAPOOL(obj)->type[id] == -1 ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
       return DATAPOOL_GET_CLASS(obj)->getTimeStamp(id);
    }
    return DC_SAMPLEFULLDATAPOOL(obj)->timeStamp[id];
}
 
static bool isValid(void *obj, TD_DataPoolId id) {
    assert( id <= DC_SAMPLEFULLDATAPOOL(obj)->maxParId );               
    assert( DC_SAMPLEFULLDATAPOOL(obj)->type[id] != -1 );
 
    if ( id > DC_SAMPLEFULLDATAPOOL(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return DATAPOOL_GET_CLASS(obj)->isValid(id);
    }
    if ( DC_SAMPLEFULLDATAPOOL(obj)->type[id] == -1 ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return DATAPOOL_GET_CLASS(obj)->isValid(id);
    }
    return DC_SAMPLEFULLDATAPOOL(obj)->valid[id];
}

static void setValidityStatus(void *obj,TD_DataPoolId id, bool newValidityStatus) {
    assert( id <= DC_SAMPLEFULLDATAPOOL(obj)->maxParId );       
    assert( DC_SAMPLEFULLDATAPOOL(obj)->type[id] != -1 );
 
    if ( id > DC_SAMPLEFULLDATAPOOL(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return;
        }

 
    if ( DC_SAMPLEFULLDATAPOOL(obj)->valid[id] && !newValidityStatus)       // change from valid to not valid
    DC_SETTABLEDATAITEM_GET_CLASS(DC_SAMPLEFULLDATAPOOL(obj)->pDataItem[id])->setVariable((TD_Integer*) DC_SAMPLEFULLDATAPOOL(obj)->pBackUpValue[id]);   // make the data item point to the backup value
    if ( ! DC_SAMPLEFULLDATAPOOL(obj)->valid[id] && newValidityStatus)       // change from not valid to valid
    DC_SETTABLEDATAITEM_GET_CLASS(DC_SAMPLEFULLDATAPOOL(obj)->pDataItem[id])->setVariable((TD_Integer*) DC_SAMPLEFULLDATAPOOL(obj)->pValue[id]);   // make the data item point to the primary value
 DC_SAMPLEFULLDATAPOOL(obj)->valid[id] = newValidityStatus;
}

static MonitoringProfile* getMonitoringProfile(void *obj,TD_DataPoolId id) {
    assert( id <= DC_SAMPLEFULLDATAPOOL(obj)->maxParId );       
    assert( DC_SAMPLEFULLDATAPOOL(obj)->type[id] != -1 );
 
    if ( id > DC_SAMPLEFULLDATAPOOL(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return DATAPOOL_GET_CLASS(obj)->getMonitoringProfile(id);
    }
        if ( DC_SAMPLEFULLDATAPOOL(obj)->type[id] == -1 ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return DATAPOOL_GET_CLASS(obj)->getMonitoringProfile(id);
    }
    return DC_SAMPLEFULLDATAPOOL(obj)->pMonitoringProfile[id];
}

static void setMonitoringProfile(void *obj,TD_DataPoolId id, MonitoringProfile* pMonProf) {
    assert( pMonProf != pNULL );
    assert( id <= DC_SAMPLEFULLDATAPOOL(obj)->maxParId );           
    assert( DC_SAMPLEFULLDATAPOOL(obj)->type[id] != -1 );
 
    if ( id > DC_SAMPLEFULLDATAPOOL(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return;
    }
    if ( DC_SAMPLEFULLDATAPOOL(obj)->type[id] == -1 ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return;
    }DC_SAMPLEFULLDATAPOOL(obj)->pMonitoringProfile[id] = pMonProf;
}

static RecoveryAction* getRecoveryAction(void *obj, TD_DataPoolId id) {
    assert( id <= DC_SAMPLEFULLDATAPOOL(obj)->maxParId );           
    assert( DC_SAMPLEFULLDATAPOOL(obj)->type[id] != -1 );
 
    if ( id > DC_SAMPLEFULLDATAPOOL(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return DATAPOOL_GET_CLASS(obj)->getRecoveryAction(id);
    }
    if ( DC_SAMPLEFULLDATAPOOL(obj)->type[id] == -1 ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return DATAPOOL_GET_CLASS(obj)->getRecoveryAction(id);
    }
    return DC_SAMPLEFULLDATAPOOL(obj)->pRecoveryAction[id];
}

static void setRecoveryAction(void *obj, TD_DataPoolId id, RecoveryAction* pRecAct) {
    assert( pRecAct != pNULL );
    assert( id <= DC_SAMPLEFULLDATAPOOL(obj)->maxParId );               
    assert( DC_SAMPLEFULLDATAPOOL(obj)->type[id] != -1 );
 
    if ( id > DC_SAMPLEFULLDATAPOOL(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return;
    }
    if ( DC_SAMPLEFULLDATAPOOL(obj)->type[id] == -1 ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return;
    }DC_SAMPLEFULLDATAPOOL(obj)->pRecoveryAction[id] = pRecAct;
}

static TD_DataPoolId firstIdentifier(void *obj) {
    assert( DC_SAMPLEFULLDATAPOOL(obj)->pValue != pNULL );
    DC_SAMPLEFULLDATAPOOL(obj)->iterationCounter = 0;
    while ( (DC_SAMPLEFULLDATAPOOL(obj)->pValue[DC_SAMPLEFULLDATAPOOL(obj)->iterationCounter]==pNULL) && (DC_SAMPLEFULLDATAPOOL(obj)->iterationCounter<DC_SAMPLEFULLDATAPOOL(obj)->maxParId) )
        DC_SAMPLEFULLDATAPOOL(obj)->iterationCounter++;
    return DC_SAMPLEFULLDATAPOOL(obj)->iterationCounter;
}

static TD_DataPoolId nextIdentifier(void *obj) {
    assert( DC_SAMPLEFULLDATAPOOL(obj)->pValue != pNULL );
    DC_SAMPLEFULLDATAPOOL(obj)->iterationCounter++;
    while ( (DC_SAMPLEFULLDATAPOOL(obj)->pValue[DC_SAMPLEFULLDATAPOOL(obj)->iterationCounter]==pNULL) && (DC_SAMPLEFULLDATAPOOL(obj)->iterationCounter<DC_SAMPLEFULLDATAPOOL(obj)->maxParId) )
        DC_SAMPLEFULLDATAPOOL(obj)->iterationCounter++;
    return DC_SAMPLEFULLDATAPOOL(obj)->iterationCounter;
}

static bool isLastIdentifier(void *obj) {
    assert( DC_SAMPLEFULLDATAPOOL(obj)->pValue != pNULL );
    return ( DC_SAMPLEFULLDATAPOOL(obj)->iterationCounter > DC_SAMPLEFULLDATAPOOL(obj)->maxParId );
}

static bool isFloat(void *obj, TD_DataPoolId id) {
    assert( id <= DC_SAMPLEFULLDATAPOOL(obj)->maxParId );           
    assert( DC_SAMPLEFULLDATAPOOL(obj)->type[id] != -1 );
 
    if ( id > DC_SAMPLEFULLDATAPOOL(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return DATAPOOL_GET_CLASS(obj)->isFloat(id);
    }
    if ( DC_SAMPLEFULLDATAPOOL(obj)->type[id] == -1 ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return DATAPOOL_GET_CLASS(obj)->isFloat(id);
    }
    return ( DC_SAMPLEFULLDATAPOOL(obj)->type[id] == TD_FloatCode );
}

static bool isInteger(void *obj,TD_DataPoolId id) {
    assert( id <= DC_SAMPLEFULLDATAPOOL(obj)->maxParId );       
    assert( DC_SAMPLEFULLDATAPOOL(obj)->type[id] != -1 );
 
    if ( id > DC_SAMPLEFULLDATAPOOL(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return DATAPOOL_GET_CLASS(obj)->isInteger(id);
    }
    if ( DC_SAMPLEFULLDATAPOOL(obj)->type[id] == -1 ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      DC_EVENTREPOSITORY_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return DATAPOOL_GET_CLASS(obj)->isInteger(id);
    }
    return ( DC_SAMPLEFULLDATAPOOL(obj)->type[id] == TD_IntegerCode );
}

static bool isObjectConfigured(void *obj) {

   // Check configuration of super object
   if (!DATAPOOL_GET_CLASS(obj)->isObjectConfigured(id)||(DC_SAMPLEFULLDATAPOOL(obj)->pObsClock==pNULL))
       return NOT_CONFIGURED;
   for (TD_DataPoolId i=DATAPOOL_GET_CLASS(obj)->firstIdentifier(); !DATAPOOL_GET_CLASS(obj)->isLastIdentifier(); i=DATAPOOL_GET_CLASS(obj)->nextIdentifier())
       if ( (DATAPOOL_GET_CLASS(obj)->getMonitoringProfile(i)==pNULL) || (DATAPOOL_GET_CLASS(obj)->getRecoveryAction(i)==pNULL) )
            return false;
   return true;
}

static void reset(void *obj) {
   for (TD_DataPoolId i=DATAPOOL_GET_CLASS(obj)->firstIdentifier(); !DATAPOOL_GET_CLASS(obj)->isLastIdentifier(); i=DATAPOOL_GET_CLASS(obj)->nextIdentifier())
        DATAPOOL_GET_CLASS(obj)->setValidityStatus(i, true);
}






///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

// the following may be useful if you don't need it, just delete.
//  *this = DC_SAMPLEFULLDATAPOOL(obj)


/**
 * Instantiate a data pool component. The class identifier is set.
 * All internal data structures are allocated and initialized.
 * The data pool is internally implemented as a linear array. In order
 * to avoid alignment problems, this array is forced to be aligned with
 * an 8-byte word boundary (more specifically, it is aligned with a 
 * location that can store a value of type <code>double</code>).
 * The time stamp of all data pool items is initialized to zero.
 * The validity status of all data pool items is initialized to "valid". 
 * The plug-in OBS Clock component is initialized to an illegal value to signify that the
 * data pool component is not yet configured.   
 */

static void instance_init(object* obj) {
  
   CC_ROOTOBJECT_GET_CLASS(obj)->setClassId(ID_SAMPLEFULLDATAPOOL);
   
   DC_SAMPLEFULLDATAPOOL(obj)->pDefaultFloat = (TD_Float*)malloc(sizeof(TD_Float));
   *(DC_SAMPLEFULLDATAPOOL(obj)->pDefaultFloat) = (TD_Float)0;
   DC_SAMPLEFULLDATAPOOL(obj)->pDefaultInt = (TD_Integer*)malloc(sizeof(TD_Integer)*sizeof(TD_Integer));
   *(DC_SAMPLEFULLDATAPOOL(obj)->pDefaultInt) = (TD_Integer)0;
  
   DC_SAMPLEFULLDATAPOOL(obj)->iterationCounter = 0;
   unsigned int const numberOfRealPar = 4;
   unsigned int const numberOfIntPar = 4;
   DC_SAMPLEFULLDATAPOOL(obj)->size = numberOfRealPar*sizeof(TD_Float)+numberOfIntPar*sizeof(TD_Integer);
   DC_SAMPLEFULLDATAPOOL(obj)->maxParId = 11;
   DC_SAMPLEFULLDATAPOOL(obj)->value = (unsigned char*)malloc((size/sizeof(double))+1);
   DC_SAMPLEFULLDATAPOOL(obj)->pValue = (unsigned char**)malloc((DC_SAMPLEFULLDATAPOOL(obj)->maxParId+1)*sizeof(unsigned char*));       
   DC_SAMPLEFULLDATAPOOL(obj)->backUpValue = (unsigned char*)malloc(DC_SAMPLEFULLDATAPOOL(obj)->size);
   DC_SAMPLEFULLDATAPOOL(obj)->pBackUpValue = (unsigned char**)malloc((DC_SAMPLEFULLDATAPOOL(obj)->maxParId+1)*sizeof(char*));
   DC_SAMPLEFULLDATAPOOL(obj)->pObsClock = pNULL;
   DC_SAMPLEFULLDATAPOOL(obj)->timeStamp = (TD_ObsTime*)malloc((DC_SAMPLEFULLDATAPOOL(obj)->maxParId+1)*sizeof(TD_ObsTime));
   DC_SAMPLEFULLDATAPOOL(obj)->valid = (bool*)malloc((DC_SAMPLEFULLDATAPOOL(obj)->maxParId+1)*sizeof(bool));
   DC_SAMPLEFULLDATAPOOL(obj)->pDataItem = (DC_SettableDataItem**)malloc((DC_SAMPLEFULLDATAPOOL(obj)->maxParId+1)*sizeof(DC_SettableDataItem*));
   DC_SAMPLEFULLDATAPOOL(obj)->pMonitoringProfile = (MonitoringProfile**)malloc((maxParId+1)*sizeof(MonitoringProfile*));
   DC_SAMPLEFULLDATAPOOL(obj)->pRecoveryAction = (RecoveryAction**)malloc((maxParId+1)*sizeof(RecoveryAction*));  
   DC_SAMPLEFULLDATAPOOL(obj)->type = (char*)malloc(maxParId+1);
 

   for (TD_DataPoolId i=0; i< DC_SAMPLEFULLDATAPOOL(obj)->size; i++)  {
         DC_SAMPLEFULLDATAPOOL(obj)->value[i] = 0;
         DC_SAMPLEFULLDATAPOOL(obj)->backUpValue[i] = 0;
 
   }

   for (TD_DataPoolId i=0; i<= DC_SAMPLEFULLDATAPOOL(obj)->maxParId; i++)  {
         DC_SAMPLEFULLDATAPOOL(obj)->pValue[i] = pNULL;
         DC_SAMPLEFULLDATAPOOL(obj)->pBackUpValue[i] = pNULL;          
         DC_SAMPLEFULLDATAPOOL(obj)->timeStamp[i] = 0;               
         DC_SAMPLEFULLDATAPOOL(obj)->valid[i] = true;                
         DC_SAMPLEFULLDATAPOOL(obj)->pDataItem[i] = pNULL;
         DC_SAMPLEFULLDATAPOOL(obj)->pMonitoringProfile[i] = pNULL;   
         DC_SAMPLEFULLDATAPOOL(obj)->pRecoveryAction[i] = pNULL;  
         DC_SAMPLEFULLDATAPOOL(obj)->type[i] = -1;        
 
   }

 unsigned int offset = 0;       
DC_SAMPLEFULLDATAPOOL(obj)->type[1] = TD_IntegerCode;
         DC_SAMPLEFULLDATAPOOL(obj)->type[2] = TD_FloatCode; 
         DC_SAMPLEFULLDATAPOOL(obj)->type[4] = TD_IntegerCode;
         DC_SAMPLEFULLDATAPOOL(obj)->type[5] = TD_FloatCode; 
         DC_SAMPLEFULLDATAPOOL(obj)->type[7] = TD_IntegerCode;
         DC_SAMPLEFULLDATAPOOL(obj)->type[8] = TD_FloatCode; 
         DC_SAMPLEFULLDATAPOOL(obj)->type[10] = TD_IntegerCode;
         DC_SAMPLEFULLDATAPOOL(obj)->type[11] = TD_FloatCode; 
         
 // Store the TD_Float values in the first part of the array
 for (TD_DatabaseId i=0; i<= DC_SAMPLEFULLDATAPOOL(obj)->maxParId; i++)  {
     if ( DC_SAMPLEFULLDATAPOOL(obj)->type[i]==TD_FloatCode) {
        DC_SAMPLEFULLDATAPOOL(obj)->pValue[i] =  DC_SAMPLEFULLDATAPOOL(obj)->value + offset;            
         DC_SAMPLEFULLDATAPOOL(obj)->pBackUpValue[i] =  DC_SAMPLEFULLDATAPOOL(obj)->backUpValue + offset;         
         DC_SAMPLEFULLDATAPOOL(obj)->pDataItem[i] = DC_SettableDataItem_new((TD_Float*) DC_SAMPLEFULLDATAPOOL(obj)->pValue[i]);     
       
        offset = offset + sizeof(TD_Float);                     
     } 
 }

 // Now ensure that offset is aligned with a TD_Integer
 unsigned int temp = (offset/sizeof(TD_Integer));
 if (temp*sizeof(TD_Integer)<offset)
    offset = (temp+1)*sizeof(TD_Integer);

 // Store the TD_Integer values in the second part of the array
 for (TD_DatabaseId i=0; i<= DC_SAMPLEFULLDATAPOOL(obj)->maxParId; i++)  {
     if (type[i]==TD_IntegerCode) {
         DC_SAMPLEFULLDATAPOOL(obj)->pValue[i] =  DC_SAMPLEFULLDATAPOOL(obj)->value + offset;            
       DC_SAMPLEFULLDATAPOOL(obj)->pBackUpValue[i] =  DC_SAMPLEFULLDATAPOOL(obj)->backUpValue + offset;         
       DC_SAMPLEFULLDATAPOOL(obj)->pDataItem[i] = DC_SettableDataItem_new((TD_Integer*) DC_SAMPLEFULLDATAPOOL(obj)->pValue[i]);     
       
        offset = offset + sizeof(TD_Integer);                     
     } 
 }
       

}


DC_SampleFullDataPool* DC_SampleFullDataPool_new(void)
{
    return (DC_SampleFullDataPool*)object_new(TYPE_DC_SAMPLEFULLDATAPOOL);
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    DC_SampleFullDataPoolClass *dc_p_class = DC_SAMPLEFULLDATAPOOL_CLASS(oc);

    dc_p_class->setValueFloat = setValueFloat;
    dc_p_class->setValueInt = setValueInt;
    dc_p_class->getFloatValue = getFloatValue;
    dc_p_class->getIntegerValue = getIntegerValue;
    dc_p_class->getPointerFloatValue = getPointerFloatValue;
    dc_p_class->getPointerIntegerValue = getPointerIntegerValue;
    dc_p_class->getDataItem = getDataItem;
    dc_p_class->getTimeStamp = getTimeStamp;
    dc_p_class->isValid = isValid;
    dc_p_class->setValidityStatus = setValidityStatus;
    dc_p_class->getMonitoringProfile = getMonitoringProfile;
    dc_p_class->setMonitoringProfile = setMonitoringProfile;
    dc_p_class->getRecoveryAction = getRecoveryAction;
    dc_p_class->setRecoveryAction = setRecoveryAction;
    dc_p_class->firstIdentifier = firstIdentifier;
    dc_p_class->nextIdentifier = nextIdentifier;
    dc_p_class->isLastIdentifier = isLastIdentifier;
    dc_p_class->isFloat = isFloat;
    dc_p_class->isInteger = isInteger;
    dc_p_class->reset = reset;
    dc_p_class->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_SAMPLEFULLDATAPOOL,
    .parent = TYPE_DATAPOOL,
    .instance_size = sizeof(DC_SampleFullDataPool),
    .abstract = false,
    .class_size = sizeof(DC_SampleFullDataPoolClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_SampleFullDataPool_register(void)
{
    type_register_static(&type_info);
}

