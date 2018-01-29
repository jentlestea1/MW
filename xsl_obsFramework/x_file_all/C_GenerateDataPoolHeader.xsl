<?xml version="1.0" encoding="UTF-8"?>
<!--================================================================-->
<!-- Copyright 2003 P&P Software GmbH                               -->
<!--================================================================-->

<!--===================================================================
Generator meta-component for the header file of a datapool class 
for the OBS Framework. The data pool is implemented as a subclass of
class DataPool. This class defines the attributes of the
items contained in the data pool and the services to be provided
by a data pool class and it provides dummy default implementations
for most attributes and for all the services.

This code generator reads as input an XML-based "data pool descriptor
file" that defines how the attributes and services of the target data
pool class should be implemented and uses this information to construct
the header file of the target data pool class.

The attributes of the data pool class are implemented as follows:

- timeStamp: if this attribute is present then the values of the
  data pool items are time stamped every time they are updated. If this
  attribute is absent, then the default implementation of the
  time stamp attribute is used.
- robustnessLevel: this attribute defines the robustness level of the
  data pool implementation. It can have a value in the range [0..3] as
  explained below.
- validityStatus: if this attribute is present then a "validity
  status" is associated to each data pool item. If this attribute is absent, 
  then the default implementation of the validity status attribute is used.
- backUpValue: if this attribute is present then a "back-up
  value service" is implemented as described below. If this attribute is
  absent, then no "back-up value service" is implemented.
- DataItem: if this attribute is present, then the data item getter
  method is implemented. If this attribute is absent, then the default
  implementation of the data item getter method is used.
- typeChecking: if this attribute is present, then the type checking
  service is implemented. If this attribute is absent, then the default
  implementation of the type checking service is used.
- monitoringProfile: if this attribute is present, then a monitorig
  profile component is associated to each data pool item. If this attribute
  is absent, then the default implementation of the getter and setter 
  methods for the monitoring profile is used.
- recoveryAction: if this attribute is present, then a recovery
  action component is associated to each data pool item. If this attribute
  is absent, then the default implementation of the getter and setter 
  methods for the recovery action is used.

The robustness level defines the level of checking that is done on the
legality of the identifier that is used as a parameter to data pool method
calls. The following robustness levels are defined:
Level 1 = The legality of the identifier value is verified only in
          'assert' clauses
Level 2 = The legality of the identifier value is verified in 'assert'
          clauses and additional run-time checks are performed on
          accesses that imply a modification of an internal data structure
          (but no such checks are performed when performing read accessed)
Level 3 = The legality of the identifier value is verified in 'assert'
          clauses and in additional run-time checks.

The "back-up value service" is implemented as follows. To each data pool item,
a "back-up value" is associated. When the validity status of the data pool item
is equal to "valid", then the back-up value is kept identical to the primary value.
When the validity status of the data pool item
changes from "valid" to "not valid", then the primary value is no longer updated and
the getter method and getDataItem method for the data pool item will return the back-up
value.

NB: This program writes its output to documents that are 
opened using the "xsl:document" instruction. The directory where these files
are written must apparently be specified through an absolute path names (this
seems to be in contrast with the documentation of xsl:document and may be a
bug in the XSLT processor). This directory is hardcoded in variable
$TargetFile.
===================================================================-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    version="1.1"
    xmlns:lxslt="http://xml.apache.org/xslt"
    xmlns:redirect="org.apache.xalan.lib.Redirect"
    extension-element-prefixes="redirect">

<xsl:strip-space elements="*"/>
<xsl:output omit-xml-declaration="yes" method="text"/>

<!--===================================================================
       Include general utility rules
===================================================================-->
<xsl:include href="ClassNameFromPath.xsl"/>

 <!--===================================================================
      Top-level rule 
===================================================================-->
<xsl:template match="/ObsApplication/DataPool/IndexedDataPool">
<!--===================================================================
      Define general-purpose variables
 ===================================================================-->  
  <xsl:variable name="ClassName">
        <xsl:call-template name="ClassNameFromPath">
              <xsl:with-param name="path" select="@type"/>
        </xsl:call-template>
  </xsl:variable>
  <xsl:variable name="CodeDir" select="'../'"/>
  <xsl:variable name="TargetFile" select="concat('/home/wangshaobo/obs_xml_xsl/projects_c/',@type)"/>     
  <xsl:variable name="LowerCase" select="'abcdefghijklmnopqrstuvwxyz'"/>         
  <xsl:variable name="UpperCase" select="'ABCDEFGHIJKLMNOPQRSTUVWXYZ'"/>         
  Generating code for class <xsl:value-of select="$ClassName"/> in files <xsl:value-of select="$TargetFile"/>.h

  <!-- Check whether writing to an output file is possible -->
  <xsl:if test="not(element-available('xsl:document'))">
        FATAL ERROR: the xsl:document element is not supported. Header files cannot be written! This element
        is normally supported only in version 1.1 of XSL.
  </xsl:if>
            
  <!-- ===================================================================================
         Create the output file  
          ===================================================================================-->
  <xsl:document href="{$TargetFile}.h" omit-xml-declaration="yes" method="text">  
//
// Copyright 2004 P&amp;P Software GmbH - All Rights Reserved
//
// <xsl:value-of select="$ClassName"/>.h
//
// The code in this file was automatically generated 

#ifndef <xsl:value-of select="$ClassName"/>_H
#define <xsl:value-of select="$ClassName"/>_H

#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/ForwardDeclarations.h"
#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/BasicTypes.h"
#include "<xsl:value-of select="$CodeDir"/>Data/DataPool.h"
#include "<xsl:value-of select="$CodeDir"/>Data/<xsl:value-of select="$ClassName"/>_inc.h"
#include "../Qom/object.h"

/**
 * <xsl:value-of select="Description"/>.
 * The code for this class was automatically generated by an XSL program
 * using as input an XML-based description of the data pool. This class
 * fully defines the structure of the data pool: its constructor allocates memory
 * for all internal data structures and it initializes them to reflect the
 * data pool layout defined in the XML-based data pool descriptor file.
 * &lt;p&gt;
 * This data pool has the following characteristics: &lt;ul&gt;
<xsl:choose>
 <xsl:when test="TimeStamp"> * &lt;li&gt;Time stamp attached to each data pool item. 
 * Its value is updated to 
 * the current time every time the setter method for the data pool item is called.
 * The current time is read from a plug-in &lt;code&gt;ObsClock&lt;/code&gt; component&lt;/li&gt;</xsl:when>
 <xsl:otherwise> * &lt;li&gt;Default implementation of time stamp attribute
 * as inherited from base class. &lt;/li&gt;</xsl:otherwise>
</xsl:choose><xsl:text>
</xsl:text>
<xsl:choose>
  <xsl:when test="RobustnessLevel/NoChecks"> * &lt;li&gt;No checks on the legality of the identifier values
 * used as method argument&lt;/li&gt;</xsl:when>
  <xsl:when test="RobustnessLevel/Low"> * &lt;li&gt;Low level of robustness to use of illegal
 * identifier values in method calls: legality of the identifier value
 * is only checked in assertions&lt;/li&gt;</xsl:when>
  <xsl:when test="RobustnessLevel/Medium"> * &lt;li&gt;Medium level of robustness to use of illegal
 * identifier values in method calls: legality of the identifier value
 * is always checked in assertions and it is checked at run time
 * whenever use of an illegal value could corrupt the internal data structures. Detection
 * of an illegal value results in the generation of an event report of type 
 * EVT_ILLEGAL_DP_ACCESS&lt;/li&gt;. </xsl:when>
  <xsl:otherwise> * &lt;li&gt;High level of robustness to use of illegal
 * identifier values in method calls: legality of the identifier value
 * is always checked in assertions and in run-time checks. Detection
 * of an illegal value results in the generation of an event report of type 
 * EVT_ILLEGAL_DP_ACCESS&lt;/li&gt;. </xsl:otherwise>
</xsl:choose><xsl:text>
</xsl:text>
<xsl:choose>
  <xsl:when test="ValidityStatus"> * &lt;li&gt;Validity status flag attached to 
 * each data pool item. &lt;/li&gt;</xsl:when>
  <xsl:otherwise> * &lt;li&gt;Default implementation of validity status attribute
 * as inherited from base class. &lt;/li&gt;</xsl:otherwise>
</xsl:choose><xsl:text>
</xsl:text>
<xsl:if test="BackUpValue"> * &lt;li&gt;Back-up value attached to each data pool item.
 * When the validity status of the data pool item
 * is equal to "valid", then the back-up value is kept identical to the primary value.
 * When the validity status of the data pool item
 * changes from "valid" to "not valid", then the primary value is no longer updated and
 * the getter method and getDataItem method for the data pool item will return the back-up
 * value. Note that the back-up mechanism is only effective for clients that link to the
 * data pool items through the &lt;i&gt;copy link&lt;/i&gt; or the &lt;i&gt;data item link&lt;/i&gt;
 * mechanism. It is not
 * effective for clients that use the &lt;i&gt;pointer link&lt;/i&gt; mechanism.&lt;/li&gt; <xsl:text/>
</xsl:if><xsl:text>
</xsl:text>
<xsl:choose>
  <xsl:when test="DataItem"> * &lt;li&gt;Data item (instance of class &lt;code&gt;DC_DataItem&lt;/code&gt;) attached to each
 * data pool item. &lt;/li&gt;</xsl:when>
  <xsl:otherwise> * &lt;li&gt;Default implementation of data item attribute
 * as inherited from base class. &lt;/li&gt;</xsl:otherwise>
</xsl:choose><xsl:text>
</xsl:text>
<xsl:choose>
  <xsl:when test="MonitoringProfile"> * &lt;li&gt;Monitoring profile
 * (instance of class &lt;code&gt;MonitoringProfile&lt;/code&gt;) attached to each data pool
 * item. &lt;/li&gt;</xsl:when>
  <xsl:otherwise> * &lt;li&gt;Default implementation of monitoring profile
 * attribute as inherited from base class. &lt;/li&gt;</xsl:otherwise>
</xsl:choose><xsl:text>
</xsl:text>
<xsl:choose>
  <xsl:when test="RecoveryAction"> * &lt;li&gt;Recovery action
 * (instance of class &lt;code&gt;RecoveryAction&lt;/code&gt;) attached to each data pool
 * item. &lt;/li&gt;</xsl:when>
  <xsl:otherwise> * &lt;li&gt;Default implementation of recovery action
 * attribute as inherited from base class. &lt;/li&gt;</xsl:otherwise>
</xsl:choose><xsl:text>
</xsl:text>
<xsl:choose>
  <xsl:when test="TypeChecking"> * &lt;li&gt;Type checking service fully implemented. &lt;/li&gt;</xsl:when>
  <xsl:otherwise> * &lt;li&gt;Default implementation of type checking service
 * as inherited from base class. &lt;/li&gt;</xsl:otherwise>
</xsl:choose>
 * &lt;/ul&gt;
 * Note that an include file (&lt;code&gt;<xsl:value-of select="$ClassName"/>_inc.h&lt;/code&gt;) 
 * is also automatically generated that defines symbolic names to access the items in the data pool. 
 * @author Automatically Generated
 * @version 1.0
 */

<!--
class <xsl:value-of select="$ClassName"/> : public DataPool {

  private:
      TD_Float* pDefaultFloat;
      TD_Integer* pDefaultInt;
      unsigned char* value;
      unsigned char** pValue;
      TD_DataPoolId size;
      TD_DataPoolId maxParId;
      TD_DataPoolId iterationCounter; <xsl:text/>
 <xsl:if test="BackUpValue">
      unsigned char** pBackUpValue;      <xsl:text/>
      unsigned char* backUpValue;
 </xsl:if>
 <xsl:if test="TimeStamp">
      ObsClock* pObsClock;
      TD_ObsTime* timeStamp;        <xsl:text/>
 </xsl:if>
 <xsl:if test="ValidityStatus">
      bool* valid;   <xsl:text/>
 </xsl:if>
 <xsl:if test="DataItem">
      DC_SettableDataItem** pDataItem;    <xsl:text/>
 </xsl:if>
 <xsl:if test="MonitoringProfile">
      MonitoringProfile** pMonitoringProfile;       <xsl:text/>
 </xsl:if>
 <xsl:if test="RecoveryAction">
      RecoveryAction** pRecoveryAction;       <xsl:text/>
 </xsl:if>
 <xsl:if test="TypeChecking">
      char* type;                 <xsl:text/>
 </xsl:if>

  public:
    /**
     * Instantiate a data pool component. The class identifier is set.
     * All internal data structures are allocated and initialized.
     * The data pool is internally implemented as a linear array. In order
     * to avoid alignment problems, this array is forced to be aligned with
     * an 8-byte word boundary (more specifically, it is aligned with a 
     * location that can store a value of type &lt;code&gt;double&lt;/code&gt;).<xsl:text/>
 <xsl:if test="TimeStamp">
     * The time stamp of all data pool items is initialized to zero.<xsl:text/>
 </xsl:if>
 <xsl:if test="ValidityStatus">
     * The validity status of all data pool items is initialized to "valid". <xsl:text/>
 </xsl:if>
 <xsl:if test="TimeStamp">
     * The plug-in OBS Clock component is initialized to an illegal value to signify that the
     * data pool component is not yet configured.   <xsl:text/>
 </xsl:if>
     */
    <xsl:value-of select="$ClassName"/>(void);
 
 <xsl:if test="TimeStamp">
    /**
     * Load the OBS Clock component. The data pool needs access to
     * this component in order to time-stamp new values of data pool items.
     * @param pObsClock the OBS Clock component.
     */
    void setObsClock(ObsClock* pObsClock);

    /**
     * Return the OBS Clock component.
     * @see #setObsClock
     * @return the OBS Clock component.
     */
    ObsClock* getObsClock(void) const;
 </xsl:if>
 
    /**
     * Setter method for the value of a real-typed data pool item. <xsl:text/>
 <xsl:if test="TimeStamp">
     * When this method is called on a data pool item, its time stamp is
     * automatically updated.       <xsl:text/>
 </xsl:if>
 <xsl:if test="BackUpValue">
     * If the validity status of the data pool item is "valid", then its
     * back up value is also updated.<xsl:text/>
 </xsl:if>
 <xsl:if test="not(RobustnessLevel/Low)">
     * If the data pool item identifier has an illegal value, then no action is taken other
     * than generating an event of type EVT_ILLEGAL_DP_ACCESS.  <xsl:text/>
 </xsl:if>
     * @param id the data identifier of the data pool item to be set
     * @param newValue the new value to be set
     */
    virtual void setValue(TD_DataPoolId id, TD_Float newValue);
    
    /**
     * Setter method for the value of an integer-typed data pool item.  <xsl:text/>
 <xsl:if test="TimeStamp">
     * When this method is called on a data pool item, its time stamp is
     * automatically updated.       <xsl:text/>
 </xsl:if>
 <xsl:if test="BackUpValue">
     * If the validity status of the data pool item is "valid", then its
     * back up value is also updated.<xsl:text/>
 </xsl:if>
 <xsl:if test="not(RobustnessLevel/Low)">
     * If the data pool item identifier has an illegal value, then no action is taken other
     * than generating an event of type EVT_ILLEGAL_DP_ACCESS.  <xsl:text/>
 </xsl:if>
     * @param id the data identifier of the data pool item to be set
     * @param newValue the new value to be set
     */
    virtual void setValue(TD_DataPoolId id, TD_Integer newValue);
    
    /**
     * Getter method for the value of a real-typed data pool item.
     * This method implements the &lt;i&gt;copy link&lt;/i&gt;
     * mechanism for real-valued data. <xsl:text/>
 <xsl:if test="BackUpValue">
     * If the validity status of the data pool item is "not valid", then the
     * back up value of the data pool item is returned.<xsl:text/>
 </xsl:if>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then the default value of
     * zero is returned.  <xsl:text/>
 </xsl:if>
     * @param id the data identifier of the data pool item to be read
     * @return the value of the data with identifier id
     */
    virtual TD_Float getFloatValue(TD_DataPoolId id);
    
    /**
     * Getter method for the value of an integer-typed data pool item.
     * This method implements the &lt;i&gt;copy link&lt;/i&gt;
     * mechanism for integer-valued data.   <xsl:text/>
 <xsl:if test="BackUpValue">
     * If the validity status of the data pool item is "not valid", then the
     * back up value of the data pool item is returned.<xsl:text/>
 </xsl:if>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then the default value of
     * zero is returned.  <xsl:text/>
 </xsl:if>
     * @param id the data identifier of the data pool item to be read
     * @return the value of the data with identifier id
     */
    virtual TD_Integer getIntegerValue(TD_DataPoolId id);
    
    /**
     * Getter method for the pointer to a real-typed data pool item.
     * This method implements the &lt;i&gt;pointer link&lt;/i&gt;
     * mechanism for real-typed data. <xsl:text/>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then a pointer to a variable
     * with fixed value zero is returned.  <xsl:text/>
 </xsl:if>
     * @param id the data identifier of the data pool item to be read
     * @return the pointer to the data with identifier id
     */
    virtual TD_Float* getPointerFloatValue(TD_DataPoolId id);
    
    /**
     * Getter method for the pointer to an integer-typed data pool item.
     * This method implements the &lt;i&gt;pointer link&lt;/i&gt;
     * mechanism for integer-typed data.<xsl:text/>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then a pointer to a variable
     * with fixed value zero is returned.  <xsl:text/>
 </xsl:if>
     * @param id the data identifier of the data pool item to be read
     * @return the pointer to the data with identifier id
     */
    virtual TD_Integer* getPointerIntegerValue(TD_DataPoolId id);
    
<xsl:if test="DataItem">
    /**
     * Getter method for a &lt;i&gt;data item&lt;/i&gt; that encapsulates a
     * data pool item. This method implements the &lt;i&gt;data item link&lt;/i&gt;
     * mechanism.<xsl:text/>
 <xsl:if test="BackUpValue">
     * If the validity status of the data pool item is "not valid", then the
     * data item returned by this method is dynamically reconfigured to point to
     * back up value of the data pool item.<xsl:text/>
 </xsl:if>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then the value returned by the
     * implementation of this method in the base class is returned.  <xsl:text/>
 </xsl:if>
     * @see DC_DataItem
     * @param id the data identifier of the data pool item to be read
     * @return the &lt;code&gt;DC_DataItem&lt;/code&gt; item encapsulating the data
     * pool item with identifier id
     */
    virtual DC_DataItem* getDataItem(TD_DataPoolId id);
</xsl:if>

<xsl:if test="TimeStamp">
    /**
     * Return the time stamp of a data pool item.
     * The time stamp of a data pool item is set by the setter
     * method when the item value is updated. Note that it the data pool item is
     * accessed using its pointer or its data item, then the time stamp is not
     * updated.<xsl:text/>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then the value returned by the
     * implementation of this method in the base class is returned.  <xsl:text/>
 </xsl:if>
     * @param id the data identifier of the data whose time stamp is sought
     * @return the time stamp of the data with identifier id
     */
    virtual TD_ObsTime getTimeStamp(TD_DataPoolId id);
</xsl:if>

<xsl:if test="ValidityStatus">
    /**
     * Return the validity status of a data pool item.
     * The value that is returned is the value that is set with method
     * &lt;code&gt;setValidityStatus&lt;/code&gt;. <xsl:text/>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then the value returned by the
     * implementation of this method in the base class is returned.  <xsl:text/>
 </xsl:if>
     * @see #setValidityStatus
     * @param id the data identifier of the data pool item
     * @return true if the data pool item is valid, false otherwise
     */
    virtual bool isValid(TD_DataPoolId id);

    /**
     * Set the validity status of a data pool item.<xsl:text/>
     * If the data pool item identifier has an out-of-range value, then no action is taken other
     * than generating an event of type EVT_ILLEGAL_DP_ACCESS. 
     * @param id the data identifier of the data pool item
     * @param newValidityStatus the new validity status
     */
    virtual void setValidityStatus(TD_DataPoolId id, bool newValidityStatus);
</xsl:if>

<xsl:if test="MonitoringProfile">
    /**
     * Get the monitoring profile for a data pool item.
     * The component that is returned by this method is the component that is set loaded
     * with method &lt;code&gt;setMonitoringProfile&lt;/code&gt;.<xsl:text/>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then the value returned by the
     * implementation of this method in the base class is returned.  <xsl:text/>
 </xsl:if>
     * @see #setMonitoringProfile
     * @param id the identifier of the data pool item
     * @return the monitoring profile
     */
    virtual MonitoringProfile* getMonitoringProfile(TD_DataPoolId id);

    /**
     * Set the monitoring profile for a data pool item.<xsl:text/>
 <xsl:if test="not(RobustnessLevel/Low)">
     * If the data pool item identifier has an illegal value, then no action is taken other
     * than generating an event of type EVT_ILLEGAL_DP_ACCESS.  <xsl:text/>
 </xsl:if>
     * @see #getMonitoringProfile
     * @param id the identifier of the data pool item
     * @param pMonitoringProfile the monitoring profile
     */
    virtual void setMonitoringProfile(TD_DataPoolId id, MonitoringProfile* pMonitoringProfile);
</xsl:if>

<xsl:if test="RecoveryAction">
    /**
     * Get the recovery action for a data pool item.
     * The component that is returned by this method is the component that is set loaded
     * with method &lt;code&gt;setRecoveryAction&lt;/code&gt;.<xsl:text/>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then the value returned by the
     * implementation of this method in the base class is returned.  <xsl:text/>
 </xsl:if>
     * @see #setRecoveryAction
     * @param id the identifier of the data pool item
     * @return the monitoring profile
     */
    virtual RecoveryAction* getRecoveryAction(TD_DataPoolId id);

    /**
     * Set the recovery action for a data pool item.<xsl:text/>
 <xsl:if test="not(RobustnessLevel/Low)">
     * If the data pool item identifier has an illegal value, then no action is taken other
     * than generating an event of type EVT_ILLEGAL_DP_ACCESS.  <xsl:text/>
 </xsl:if>
     * @see #getRecoveryAction
     * @param id the identifier of the data pool item
     * @param pRcoveryAction the recovery action
     */
    virtual void setRecoveryAction(TD_DataPoolId id, RecoveryAction* pRcoveryAction);
</xsl:if>

    /**
     * Iteration method that resets the iteration and returns the lowest
     * indentifier of the items in the data pool.
     * @see DataPool#firstIdentifier
     * @return the identifier of the first data pool item in the iteration
     */
    virtual TD_DataPoolId firstIdentifier(void);

    /**
     * Iteration method that returns the next identifier in an iteration.
     * @see DataPool#firstIdentifier
     * @return the identifier of the next data pool item in the iteration
     */
    virtual TD_DataPoolId nextIdentifier(void);

    /**
     * Iteration method that returns the next identifier in an iteration.
     * @see DataPool#firstIdentifier
     * @return true if the iteration has completed, false otherwise
     */
    virtual bool isLastIdentifier(void);
    
<xsl:if test="TypeChecking">
    /**
     * Method implementing the type checking service to check whether a
     * data pool item is real-typed.<xsl:text/>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then the value returned by the
     * implementation of this method in the base class is returned.  <xsl:text/>
 </xsl:if>
     * @see DataPool#isFloat
     * @see id the identifier of the data pool item
     * @return true if the id is the identifier of a real-valued data item,
     * false otherwise
     */
    virtual bool isFloat(TD_DataPoolId id);

    /**
     * Method implementing the type checking service to check whether a
     * data pool item is integer-typed.<xsl:text/>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then the value returned by the
     * implementation of this method in the base class is returned.  <xsl:text/>
 </xsl:if>
     * @see DataPool#isInteger
     * @see id the identifier of the data pool item
     * @return true if the id is the identifier of a real-valued data item,
     * false otherwise
     */
    virtual bool isInteger(TD_DataPoolId id);
</xsl:if>

<xsl:if test="ValidityStatus">
    /**
     * Implement the data pool reset service.
     * The validity status of all data pool item is reset to the value it
     * had at the time the data pool component was created.
     * @see #isValid
     */
    virtual void reset(void);
</xsl:if>

<xsl:if test="(MonitoringProfile) or (RecoveryAction) or (TimeStamp)">
    /**
     * Perform a class-specific configuration check. The following checks are performed: &lt;ul&gt;<xsl:text/>
  <xsl:if test="(MonitoringProfile)">
     * &lt;li&gt;All monitoring profiles have been loaded&lt;/li&gt;<xsl:text/>
  </xsl:if>
  <xsl:if test="(RecoveryAction)">
     * &lt;li&gt;All recovery actions have been loaded&lt;/li&gt;<xsl:text/>
  </xsl:if>
  <xsl:if test="(TimeStamp)">
     * &lt;li&gt;The OBS Clock plug-in component has been loaded&lt;/li&gt;<xsl:text/>
  </xsl:if>
     * &lt;/ul&gt;
     * @return true if the data pool object is configured, false otherwise
     */
    virtual bool isObjectConfigured(void);
</xsl:if>


};
-->

#define TYPE_<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/> "<xsl:value-of select="translate($ClassName,$UpperCase,$LowerCase)"/>"

void <xsl:value-of select="$ClassName"/>_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct <xsl:value-of select="$ClassName"/> {
    DataPool parent;

    TD_Float *pDefaultFloat;
    TD_Integer *pDefaultInt;
    unsigned char *value;
    unsigned char **pValue;
    TD_DataPoolId size;
    TD_DataPoolId maxParId;
    TD_DataPoolId iterationCounter;    <xsl:text/>
 <xsl:if test="BackUpValue">
    unsigned char** pBackUpValue;      <xsl:text/>
    unsigned char* backUpValue;
 </xsl:if>
 <xsl:if test="TimeStamp">
    ObsClock* pObsClock;
    TD_ObsTime* timeStamp;        <xsl:text/>
 </xsl:if>
 <xsl:if test="ValidityStatus">
    bool* valid;   <xsl:text/>
 </xsl:if>
 <xsl:if test="DataItem">
    DC_SettableDataItem** pDataItem;    <xsl:text/>
 </xsl:if>
 <xsl:if test="MonitoringProfile">
    MonitoringProfile** pMonitoringProfile;       <xsl:text/>
 </xsl:if>
 <xsl:if test="RecoveryAction">
    RecoveryAction** pRecoveryAction;       <xsl:text/>
 </xsl:if>
 <xsl:if test="TypeChecking">
    char* type;                 <xsl:text/>
 </xsl:if>
};


struct <xsl:value-of select="$ClassName"/>Class {
    DataPoolClass parent_class;
 
    <!--void (*setValueFloat)(void *obj, TD_DataPoolId id, TD_Float newValue);
    -void (*setValueInt)(void *obj, TD_DataPoolId id, TD_Integer newValue);
    -TD_Float (*getFloatValue)(void *obj, TD_DataPoolId id);
    -TD_Integer (*getIntegerValue)(void *obj, TD_DataPoolId id);
    -TD_Float* (*getPointerFloatValue)(void *obj, TD_DataPoolId id);
    -TD_Integer* (*getPointerIntegerValue)(void *obj, TD_DataPoolId id);
    -DC_DataItem* (*getDataItem)(void *obj, TD_DataPoolId id);
    -TD_ObsTime (*getTimeStamp)(void *obj, TD_DataPoolId id);
    -abool (*isValid)(void *obj, TD_DataPoolId id);
    -void (*setValidityStatus)(void *obj, TD_DataPoolId id, bool newValidityStatus);
    -MonitoringProfile* (*getMonitoringProfile)(void *obj, TD_DataPoolId id);
    -void (*setMonitoringProfile)(void *obj, TD_DataPoolId id, MonitoringProfile* pMonitoringProfile);
    -RecoveryAction* (*getRecoveryAction)(void *obj, TD_DataPoolId id);
    -void (*setRecoveryAction)(void *obj, TD_DataPoolId id, RecoveryAction* pRcoveryAction);
    TD_DataPoolId (*firstIdentifier)(void *obj);
    TD_DataPoolId (*nextIdentifier)(void *obj);
    bool (*isLastIdentifier)(void *obj);
    bool (*isFloat)(void *obj, TD_DataPoolId id);
    bool (*isInteger)(void *obj, TD_DataPoolId id);
    void (*reset)(void *obj);
    bool (*isObjectConfigured)(void *obj);
    -->
 
    /**
     * Setter method for the value of a real-typed data pool item. <xsl:text/>
 <xsl:if test="TimeStamp">
     * When this method is called on a data pool item, its time stamp is
     * automatically updated.       <xsl:text/>
 </xsl:if>
 <xsl:if test="BackUpValue">
     * If the validity status of the data pool item is "valid", then its
     * back up value is also updated.<xsl:text/>
 </xsl:if>
 <xsl:if test="not(RobustnessLevel/Low)">
     * If the data pool item identifier has an illegal value, then no action is taken other
     * than generating an event of type EVT_ILLEGAL_DP_ACCESS.  <xsl:text/>
 </xsl:if>
     * @param id the data identifier of the data pool item to be set
     * @param newValue the new value to be set
     */
     <!--virtual void setValue(TD_DataPoolId id, TD_Float newValue);-->
    void (*setValueFloat)(void *obj, TD_DataPoolId id, TD_Float newValue);
    
    /**
     * Setter method for the value of an integer-typed data pool item.  <xsl:text/>
 <xsl:if test="TimeStamp">
     * When this method is called on a data pool item, its time stamp is
     * automatically updated.       <xsl:text/>
 </xsl:if>
 <xsl:if test="BackUpValue">
     * If the validity status of the data pool item is "valid", then its
     * back up value is also updated.<xsl:text/>
 </xsl:if>
 <xsl:if test="not(RobustnessLevel/Low)">
     * If the data pool item identifier has an illegal value, then no action is taken other
     * than generating an event of type EVT_ILLEGAL_DP_ACCESS.  <xsl:text/>
 </xsl:if>
     * @param id the data identifier of the data pool item to be set
     * @param newValue the new value to be set
     */
     <!--virtual void setValue(TD_DataPoolId id, TD_Integer newValue);-->
    void (*setValueInt)(void *obj, TD_DataPoolId id, TD_Integer newValue);
    
    /**
     * Getter method for the value of a real-typed data pool item.
     * This method implements the &lt;i&gt;copy link&lt;/i&gt;
     * mechanism for real-valued data. <xsl:text/>
 <xsl:if test="BackUpValue">
     * If the validity status of the data pool item is "not valid", then the
     * back up value of the data pool item is returned.<xsl:text/>
 </xsl:if>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then the default value of
     * zero is returned.  <xsl:text/>
 </xsl:if>
     * @param id the data identifier of the data pool item to be read
     * @return the value of the data with identifier id
     */
     <!--virtual TD_Float getFloatValue(TD_DataPoolId id);-->
    TD_Float (*getFloatValue)(void *obj, TD_DataPoolId id);
    
    /**
     * Getter method for the value of an integer-typed data pool item.
     * This method implements the &lt;i&gt;copy link&lt;/i&gt;
     * mechanism for integer-valued data.   <xsl:text/>
 <xsl:if test="BackUpValue">
     * If the validity status of the data pool item is "not valid", then the
     * back up value of the data pool item is returned.<xsl:text/>
 </xsl:if>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then the default value of
     * zero is returned.  <xsl:text/>
 </xsl:if>
     * @param id the data identifier of the data pool item to be read
     * @return the value of the data with identifier id
     */
    <!--virtual TD_Integer getIntegerValue(TD_DataPoolId id);-->
    TD_Integer (*getIntegerValue)(void *obj, TD_DataPoolId id);
    
    /**
     * Getter method for the pointer to a real-typed data pool item.
     * This method implements the &lt;i&gt;pointer link&lt;/i&gt;
     * mechanism for real-typed data. <xsl:text/>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then a pointer to a variable
     * with fixed value zero is returned.  <xsl:text/>
 </xsl:if>
     * @param id the data identifier of the data pool item to be read
     * @return the pointer to the data with identifier id
     */
     <!--virtual TD_Float* getPointerFloatValue(TD_DataPoolId id);-->
    TD_Float* (*getPointerFloatValue)(void *obj, TD_DataPoolId id);
    
    /**
     * Getter method for the pointer to an integer-typed data pool item.
     * This method implements the &lt;i&gt;pointer link&lt;/i&gt;
     * mechanism for integer-typed data.<xsl:text/>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then a pointer to a variable
     * with fixed value zero is returned.  <xsl:text/>
 </xsl:if>
     * @param id the data identifier of the data pool item to be read
     * @return the pointer to the data with identifier id
     */
     <!--virtual TD_Integer* getPointerIntegerValue(TD_DataPoolId id);-->
    TD_Integer* (*getPointerIntegerValue)(void *obj, TD_DataPoolId id);
    
<xsl:if test="DataItem">
    /**
     * Getter method for a &lt;i&gt;data item&lt;/i&gt; that encapsulates a
     * data pool item. This method implements the &lt;i&gt;data item link&lt;/i&gt;
     * mechanism.<xsl:text/>
 <xsl:if test="BackUpValue">
     * If the validity status of the data pool item is "not valid", then the
     * data item returned by this method is dynamically reconfigured to point to
     * back up value of the data pool item.<xsl:text/>
 </xsl:if>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then the value returned by the
     * implementation of this method in the base class is returned.  <xsl:text/>
 </xsl:if>
     * @see DC_DataItem
     * @param id the data identifier of the data pool item to be read
     * @return the &lt;code&gt;DC_DataItem&lt;/code&gt; item encapsulating the data
     * pool item with identifier id
     */
     <!--virtual DC_DataItem* getDataItem(TD_DataPoolId id);-->
    DC_DataItem* (*getDataItem)(void *obj, TD_DataPoolId id);
</xsl:if>

<xsl:if test="TimeStamp">
    /**
     * Return the time stamp of a data pool item.
     * The time stamp of a data pool item is set by the setter
     * method when the item value is updated. Note that it the data pool item is
     * accessed using its pointer or its data item, then the time stamp is not
     * updated.<xsl:text/>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then the value returned by the
     * implementation of this method in the base class is returned.  <xsl:text/>
 </xsl:if>
     * @param id the data identifier of the data whose time stamp is sought
     * @return the time stamp of the data with identifier id
     */
     <!--virtual TD_ObsTime getTimeStamp(TD_DataPoolId id);-->
    TD_ObsTime (*getTimeStamp)(void *obj, TD_DataPoolId id);
</xsl:if>

<xsl:if test="ValidityStatus">
    /**
     * Return the validity status of a data pool item.
     * The value that is returned is the value that is set with method
     * &lt;code&gt;setValidityStatus&lt;/code&gt;. <xsl:text/>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then the value returned by the
     * implementation of this method in the base class is returned.  <xsl:text/>
 </xsl:if>
     * @see #setValidityStatus
     * @param id the data identifier of the data pool item
     * @return true if the data pool item is valid, false otherwise
     */
     <!--virtual bool isValid(TD_DataPoolId id);-->
    bool (*isValid)(void *obj, TD_DataPoolId id);

    /**
     * Set the validity status of a data pool item.<xsl:text/>
     * If the data pool item identifier has an out-of-range value, then no action is taken other
     * than generating an event of type EVT_ILLEGAL_DP_ACCESS. 
     * @param id the data identifier of the data pool item
     * @param newValidityStatus the new validity status
     */
     <!--virtual void setValidityStatus(TD_DataPoolId id, bool newValidityStatus);-->
    void (*setValidityStatus)(void *obj, TD_DataPoolId id, bool newValidityStatus);
</xsl:if>

<xsl:if test="MonitoringProfile">
    /**
     * Get the monitoring profile for a data pool item.
     * The component that is returned by this method is the component that is set loaded
     * with method &lt;code&gt;setMonitoringProfile&lt;/code&gt;.<xsl:text/>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then the value returned by the
     * implementation of this method in the base class is returned.  <xsl:text/>
 </xsl:if>
     * @see #setMonitoringProfile
     * @param id the identifier of the data pool item
     * @return the monitoring profile
     */
     <!--virtual MonitoringProfile* getMonitoringProfile(TD_DataPoolId id);-->
    MonitoringProfile* (*getMonitoringProfile)(void *obj, TD_DataPoolId id);

    /**
     * Set the monitoring profile for a data pool item.<xsl:text/>
 <xsl:if test="not(RobustnessLevel/Low)">
     * If the data pool item identifier has an illegal value, then no action is taken other
     * than generating an event of type EVT_ILLEGAL_DP_ACCESS.  <xsl:text/>
 </xsl:if>
     * @see #getMonitoringProfile
     * @param id the identifier of the data pool item
     * @param pMonitoringProfile the monitoring profile
     */
     <!--virtual void setMonitoringProfile(TD_DataPoolId id, MonitoringProfile* pMonitoringProfile);-->
    void (*setMonitoringProfile)(void *obj, TD_DataPoolId id, MonitoringProfile* pMonitoringProfile);
</xsl:if>

<xsl:if test="RecoveryAction">
    /**
     * Get the recovery action for a data pool item.
     * The component that is returned by this method is the component that is set loaded
     * with method &lt;code&gt;setRecoveryAction&lt;/code&gt;.<xsl:text/>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then the value returned by the
     * implementation of this method in the base class is returned.  <xsl:text/>
 </xsl:if>
     * @see #setRecoveryAction
     * @param id the identifier of the data pool item
     * @return the monitoring profile
     */
     <!--virtual RecoveryAction* getRecoveryAction(TD_DataPoolId id);-->
    RecoveryAction* (*getRecoveryAction)(void *obj, TD_DataPoolId id);

    /**
     * Set the recovery action for a data pool item.<xsl:text/>
 <xsl:if test="not(RobustnessLevel/Low)">
     * If the data pool item identifier has an illegal value, then no action is taken other
     * than generating an event of type EVT_ILLEGAL_DP_ACCESS.  <xsl:text/>
 </xsl:if>
     * @see #getRecoveryAction
     * @param id the identifier of the data pool item
     * @param pRcoveryAction the recovery action
     */
    <!--virtual void setRecoveryAction(TD_DataPoolId id, RecoveryAction* pRcoveryAction);-->
    void (*setRecoveryAction)(void *obj, TD_DataPoolId id, RecoveryAction* pRcoveryAction);
</xsl:if>

    /**
     * Iteration method that resets the iteration and returns the lowest
     * indentifier of the items in the data pool.
     * @see DataPool#firstIdentifier
     * @return the identifier of the first data pool item in the iteration
     */
    <!--virtual TD_DataPoolId firstIdentifier(void);-->
    TD_DataPoolId (*firstIdentifier)(void *obj);

    /**
     * Iteration method that returns the next identifier in an iteration.
     * @see DataPool#firstIdentifier
     * @return the identifier of the next data pool item in the iteration
     */
    <!--virtual TD_DataPoolId nextIdentifier(void);-->
    TD_DataPoolId (*nextIdentifier)(void *obj);

    /**
     * Iteration method that returns the next identifier in an iteration.
     * @see DataPool#firstIdentifier
     * @return true if the iteration has completed, false otherwise
     */
    <!--virtual bool isLastIdentifier(void);-->
    bool (*isLastIdentifier)(void *obj);
    
<xsl:if test="TypeChecking">
    /**
     * Method implementing the type checking service to check whether a
     * data pool item is real-typed.<xsl:text/>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then the value returned by the
     * implementation of this method in the base class is returned.  <xsl:text/>
 </xsl:if>
     * @see DataPool#isFloat
     * @see id the identifier of the data pool item
     * @return true if the id is the identifier of a real-valued data item,
     * false otherwise
     */
    <!--virtual bool isFloat(TD_DataPoolId id);-->
    bool (*isFloat)(void *obj, TD_DataPoolId id);

    /**
     * Method implementing the type checking service to check whether a
     * data pool item is integer-typed.<xsl:text/>
 <xsl:if test="RobustnessLevel/Medium">
     * If the data pool item identifier has an illegal value, then the value returned by the
     * implementation of this method in the base class is returned.  <xsl:text/>
 </xsl:if>
     * @see DataPool#isInteger
     * @see id the identifier of the data pool item
     * @return true if the id is the identifier of a real-valued data item,
     * false otherwise
     */
    <!--virtual bool isInteger(TD_DataPoolId id);-->
    bool (*isInteger)(void *obj, TD_DataPoolId id);
</xsl:if>

<xsl:if test="ValidityStatus">
    /**
     * Implement the data pool reset service.
     * The validity status of all data pool item is reset to the value it
     * had at the time the data pool component was created.
     * @see #isValid
     */
    <!--virtual void reset(void);-->
    void (*reset)(void *obj);
</xsl:if>

<xsl:if test="(MonitoringProfile) or (RecoveryAction) or (TimeStamp)">
    /**
     * Perform a class-specific configuration check. The following checks are performed: &lt;ul&gt;<xsl:text/>
  <xsl:if test="(MonitoringProfile)">
     * &lt;li&gt;All monitoring profiles have been loaded&lt;/li&gt;<xsl:text/>
  </xsl:if>
  <xsl:if test="(RecoveryAction)">
     * &lt;li&gt;All recovery actions have been loaded&lt;/li&gt;<xsl:text/>
  </xsl:if>
  <xsl:if test="(TimeStamp)">
     * &lt;li&gt;The OBS Clock plug-in component has been loaded&lt;/li&gt;<xsl:text/>
  </xsl:if>
     * &lt;/ul&gt;
     * @return true if the data pool object is configured, false otherwise
     */
    bool isObjectConfigured(void *obj);
    <!--bool (*isObjectConfigured)(void *obj);-->
</xsl:if>
};


#define <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>_GET_CLASS(obj) \
    OBJECT_GET_CLASS(<xsl:value-of select="$ClassName"/>Class, obj, TYPE_<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>)

#define <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>_CLASS(klass) \
    OBJECT_CLASS_CHECK(<xsl:value-of select="$ClassName"/>Class, klass, TYPE_<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>)

#define  <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj) \
    OBJECT_CHECK(<xsl:value-of select="$ClassName"/>, obj, TYPE_<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>)


<xsl:value-of select="$ClassName"/>* <xsl:value-of select="$ClassName"/>_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

 <xsl:if test="TimeStamp">
/**
 * Load the OBS Clock component. The data pool needs access to
 * this component in order to time-stamp new values of data pool items.
 * @param pObsClock the OBS Clock component.
 */
void <xsl:value-of select="$ClassName"/>_setObsClock(<xsl:value-of select="$ClassName"/> *this, ObsClock* pObsClock);
/**
 * Return the OBS Clock component.
 * @see #setObsClock
 * @return the OBS Clock component.
 */
ObsClock* <xsl:value-of select="$ClassName"/>_getObsClock(<xsl:value-of select="$ClassName"/> *this);
 </xsl:if>


#endif

    </xsl:document>
</xsl:template>





</xsl:stylesheet>
