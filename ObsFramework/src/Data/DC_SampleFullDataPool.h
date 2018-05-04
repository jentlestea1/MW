//
//
// DC_SampleFullDataPool.h
//
// The code in this file was automatically generated 


#ifndef DC_SAMPLEFULLDATAPOOL_H
#define DC_SAMPLEFULLDATAPOOL_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Data/DataPool.h"
#include "../Qom/object.h"


/*
 * Sample data pool with full functionality..
 * The code for this class was automatically generated by an XSL program
 * using as input an XML-based description of the data pool. This class
 * fully defines the structure of the data pool: its constructor allocates memory
 * for all internal data structures and it initializes them to reflect the
 * data pool layout defined in the XML-based data pool descriptor file.
 * <p>
 * This data pool has the following characteristics: <ul>
 * <li>Time stamp attached to each data pool item. 
 * Its value is updated to 
 * the current time every time the setter method for the data pool item is called.
 * The current time is read from a plug-in <code>ObsClock</code> component</li>
 * <li>High level of robustness to use of illegal
 * identifier values in method calls: legality of the identifier value
 * is always checked in assertions and in run-time checks. Detection
 * of an illegal value results in the generation of an event report of type 
 * EVT_ILLEGAL_DP_ACCESS</li>. 
 * <li>Validity status flag attached to 
 * each data pool item. </li>
 * <li>Back-up value attached to each data pool item.
 * When the validity status of the data pool item
 * is equal to "valid", then the back-up value is kept identical to the primary value.
 * When the validity status of the data pool item
 * changes from "valid" to "not valid", then the primary value is no longer updated and
 * the getter method and getDataItem method for the data pool item will return the back-up
 * value. Note that the back-up mechanism is only effective for clients that link to the
 * data pool items through the <i>copy link</i> or the <i>data item link</i>
 * mechanism. It is not
 * effective for clients that use the <i>pointer link</i> mechanism.</li> 
 * <li>Data item(instance of class <code>DC_DataItem</code>) attached to each
 * data pool item. </li>
 * <li>Monitoring profile
 * (instance of class <code>MonitoringProfile</code>) attached to each data pool
 * item. </li>
 * <li>Recovery action
 * (instance of class <code>RecoveryAction</code>) attached to each data pool
 * item. </li>
 * <li>Type checking service fully implemented. </li>
 * </ul>
 * Note that an include file(<code>DC_SampleFullDataPool_inc.h</code>) 
 * is also automatically generated that defines symbolic names to access the items in the data pool. 
 * @author Automatically Generated
 * @version 1.0
 */
#define TYPE_DC_SAMPLEFULLDATAPOOL "dc_samplefulldatapool"

void DC_SampleFullDataPool_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_SampleFullDataPool {
    DataPool parent;

    TD_Float *pDefaultFloat;
    TD_Integer *pDefaultInt;
    unsigned char *value;
    unsigned char **pValue;
    TD_DataPoolId size;
    TD_DataPoolId maxParId;
    TD_DataPoolId iterationCounter; 
    unsigned char **pBackUpValue;      
    unsigned char *backUpValue;

    ObsClock *pObsClock;
    TD_ObsTime *timeStamp;        
    bool *valid;   
    DC_SettableDataItem **pDataItem;    
    MonitoringProfile **pMonitoringProfile;       
    RecoveryAction **pRecoveryAction;       
    char *type;                 
};


struct DC_SampleFullDataPoolClass {
    DataPoolClass parent_class;
 
    void (*setRecoveryAction)(void*, TD_DataPoolId, RecoveryAction*);
    void (*setMonitoringProfile)(void*, TD_DataPoolId, MonitoringProfile*);
};


#define DC_SAMPLEFULLDATAPOOL_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_SampleFullDataPoolClass, obj, TYPE_DC_SAMPLEFULLDATAPOOL)

#define DC_SAMPLEFULLDATAPOOL_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_SampleFullDataPoolClass, klass, TYPE_DC_SAMPLEFULLDATAPOOL)

#define DC_SAMPLEFULLDATAPOOL(obj) \
        OBJECT_CHECK(DC_SampleFullDataPool, obj, TYPE_DC_SAMPLEFULLDATAPOOL)


DC_SampleFullDataPool* DC_SampleFullDataPool_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Load the OBS Clock component. The data pool needs access to
 * this component in order to time-stamp new values of data pool items.
 * @param pObsClock the OBS Clock component.
 */
void DC_SampleFullDataPool_setObsClock(DC_SampleFullDataPool *This, ObsClock *pObsClock);

/**
 * Return the OBS Clock component.
 * @see #setObsClock
 * @return the OBS Clock component.
 */
ObsClock* DC_SampleFullDataPool_getObsClock(const DC_SampleFullDataPool *This);


#endif
