<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2003 P&P Software GmbH                               -->
<!--================================================================-->

<!--===================================================================
Generator meta-component for the test case for a data pool class
of the OBS Framework.

This XSL program generates the body file of the data pool
test case class.

This XSL program process an XML file that describes the data pool
class. The structure of the XML file is described in the XSLT
program that generates the header file of the data pool class
(see file GenerateDataPoolHeader.h).
===================================================================-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    version="1.1"
    xmlns:lxslt="http://xml.apache.org/xslt">

<xsl:strip-space elements="*"/>
<xsl:output omit-xml-declaration="yes" method="text"/>

<!--===================================================================
       Include general utility rules
===================================================================-->
<xsl:include href="ClassIdFromClassName.xsl"/> 
<!-- <xsl:include href="GenerateDataPoolBody.xsl"/>  -->
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
  <xsl:variable name="ClassId">
        <xsl:call-template name="ClassIdFromClassName">
              <xsl:with-param name="className" select="$ClassName"/>
        </xsl:call-template>
  </xsl:variable>
  <xsl:variable name="CodeDir" select="'../'"/>
  <xsl:variable name="TestCaseClassName" select="concat('TestCase',substring($ClassName,4,string-length($ClassName)),'_1')"/>

  <!-- compute and store the maximum parameter ID value (the rule comes from GenerateDataPoolBody.xsl     -->
  <xsl:variable name="maxParId">
    <xsl:call-template name="computeMaxParId">
       <xsl:with-param name="currentMax" select="0"/>
       <xsl:with-param name="currentPos" select="1"/>
    </xsl:call-template>
  </xsl:variable>

  <!-- compute and store the lowest illegal parameter id          -->
  <xsl:variable name="lowestIllegalParId">
    <xsl:call-template name="computeLowestIllegalParId">
       <xsl:with-param name="current" select="1"/>
    </xsl:call-template>
  </xsl:variable>

  <!-- compute and store the total number of parameters           -->
  <xsl:variable name="numberOfPar" select="count(DataPoolItem)"/>

  <xsl:variable name="TargetFile" select="concat('/home/wangshaobo/obs_xml_xsl/projects_c/RegressionTest/',$TestCaseClassName)"/>     
  <xsl:variable name="LowerCase" select="'abcdefghijklmnopqrstuvwxyz'"/>
  <xsl:variable name="UpperCase" select="'ABCDEFGHIJKLMNOPQRSTUVWXYZ'"/>
  Generating code for class <xsl:value-of select="$ClassName"/> in files <xsl:value-of select="$TargetFile"/>.c

  <!-- Check whether writing to an output file is possible -->
  <xsl:if test="not(element-available('xsl:document'))">
        FATAL ERROR: the xsl:document element is not supported. Header files cannot be written! This element
        is normally supported only in version 1.1 of XSL.
  </xsl:if>
            
 <!-- ===================================================================================
         Create the output file  
  ===================================================================================-->
  <xsl:document href="{$TargetFile}.c" omit-xml-declaration="yes" method="text">  
//
// Copyright 2003 P&amp;P Software GmbH - All Rights Reserved
//
// <xsl:value-of select="$TestCaseClassName"/>.h
//
// Version	1.0
// Date		10.09.03 (Version 1.0)
// Author	A. Pasetti (P&amp;P Software)
//

#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/CompilerSwitches.h"
#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/ClassId.h"
#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/Constants.h"
#include "<xsl:value-of select="$CodeDir"/>Data/<xsl:value-of select="$ClassName"/>.h"
#include "<xsl:value-of select="$CodeDir"/>Data/DC_DataItem.h"
#include "<xsl:value-of select="$CodeDir"/>System/DC_DummyObsClock.h"
#include "<xsl:value-of select="$CodeDir"/>FDIR/DC_NullProfile.h"
#include "<xsl:value-of select="$CodeDir"/>FDIR/DC_NullRecoveryAction.h"
#include "<xsl:value-of select="$TestCaseClassName"/>.h"
#include "<xsl:value-of select="$CodeDir"/>Utilities/TestCaseWithEvtCheck.h"

#include &lt;math.h&gt;
#include &lt;float.h&gt;<xsl:text>

</xsl:text>
<!--
<xsl:value-of select="$TestCaseClassName"/>::<xsl:value-of select="$TestCaseClassName"/>():
      TestCaseWithEvtCheck(<xsl:value-of select="$ClassId"/>*10+1,"<xsl:value-of select="$TestCaseClassName"/>") {
            return;
}

void <xsl:value-of select="$TestCaseClassName"/>::runTestCase() {

    // Variable to hold the number of events
    unsigned int nEvt;
    nEvt = getNumberOfEvents();

    // Variable to hold number of parameters in the data pool
    TD_DataPoolId numberOfPar = <xsl:value-of select="$numberOfPar"/>;
<xsl:if test="(not(RobustnessLevel/Low)) or (TypeChecking)">
    // Variable to hold first identifier of a real-value parameter
    TD_DataPoolId firstRealId = <xsl:value-of 
            select="DataPoolItem[Type/@value='TD_Float'][position()=1]/Id/@value"/>;

    // Variable to hold first identifier of an integer-valued parameter
    TD_DataPoolId firstIntegerId = <xsl:value-of 
            select="DataPoolItem[Type/@value='TD_Integer'][position()=1]/Id/@value"/>;
</xsl:if>
    // Instantiate datapool
    <xsl:value-of select="$ClassName"/>* pDP = new <xsl:value-of select="$ClassName"/>();

    // Variable to hold maximum parameter identifier
    TD_DataPoolId maxParId;
    maxParId = <xsl:value-of select="$maxParId"/>;

    // Auxiliary variable to hold a data pool item identifier
    TD_DataPoolId id;
    id = 0;

    // Variable to hold the lowest illegal parameter id
    TD_DataPoolId lowestIllegalParId;
    lowestIllegalParId = (TD_DataPoolId)<xsl:value-of select="$lowestIllegalParId"/>;

    // Verify correctness of class ID
    if (pDP->getClassId() != <xsl:value-of select="$ClassId"/>)
    {      setTestResult(TEST_FAILURE, "Wrong class ID");
            return;
    }
<xsl:if test="(ValidityStatus)">
    // Check default value of validity status.
    <xsl:text/>
    <xsl:for-each select="DataPoolItem">
    if ( !pDP->isValid(<xsl:value-of select="Id/@value"/>) )
    {      setTestResult(TEST_FAILURE, "Wrong default validity status on data item <xsl:value-of select="Id/@value"/>");
            return;
    }
    </xsl:for-each>
</xsl:if>
<xsl:if test="(TimeStamp)">
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
</xsl:if>
<xsl:if test="(MonitoringProfile) or (RecoveryAction)">
    // Check that the data pool is not yet configured
    if ( pDP->isObjectConfigured() != NOT_CONFIGURED )
    {      setTestResult(TEST_FAILURE, "Incorrect configuration status at creation");
            return;
    }
</xsl:if>
<xsl:if test="MonitoringProfile">
    // Load monitoring profiles and check correctness of load operations
    DC_NullProfile* pNP = new DC_NullProfile();  <xsl:text/>
    <xsl:for-each select="DataPoolItem">
    pDP->setMonitoringProfile(<xsl:value-of select="Id/@value"/>,pNP);
    if (pDP->getMonitoringProfile(<xsl:value-of select="Id/@value"/>)!=pNP)
    {	setTestResult(TEST_FAILURE, "Failure to read back monitoring profile");
        return;
    }
    </xsl:for-each>
</xsl:if>
<xsl:if test="RecoveryAction">
    // Load recovery actions and check correctness of load operations
    DC_NullRecoveryAction* pRA = new DC_NullRecoveryAction();  <xsl:text/>
    <xsl:for-each select="DataPoolItem">
    pDP->setRecoveryAction(<xsl:value-of select="Id/@value"/>,pRA);
    if (pDP->getRecoveryAction(<xsl:value-of select="Id/@value"/>)!=pRA)
    {	setTestResult(TEST_FAILURE, "Failure to read back recovery action");
        return;
    }
    </xsl:for-each>
</xsl:if>
<xsl:if test="(MonitoringProfile) or (RecoveryAction) or (TimeStamp)">
    // Check that the data pool is configured
    if ( pDP->isObjectConfigured() != CONFIGURED )
     {      setTestResult(TEST_FAILURE, "Incorrect configuration status");
            return;
      }
</xsl:if>
    // Check data setting and getting services for the data pool item values
    // Do it for the real-value items first and then for the interger-valued items
<xsl:for-each select="DataPoolItem[Type/@value='TD_Float']">
    id = <xsl:value-of select="Id/@value"/>;
    pDP->setValue(id,(TD_Float)id);
    if ( fabs((float)(pDP->getFloatValue(id)-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    if ( fabs((float)((*pDP->getPointerFloatValue(id))-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }<xsl:if test="DataItem">
    if ( fabs((float)(pDP->getDataItem(id)->getFloat()-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }</xsl:if>
</xsl:for-each>
<xsl:for-each select="DataPoolItem[Type/@value='TD_Integer']">
    id = <xsl:value-of select="Id/@value"/>;
    pDP->setValue(id,(TD_Integer)id);
    if ( pDP->getIntegerValue(id)!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    if ( (*pDP->getPointerIntegerValue(id))!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }<xsl:if test="DataItem">
    if ( pDP->getDataItem(id)->getInt()!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }</xsl:if>
</xsl:for-each>
<xsl:if test="TimeStamp">
    // Check the time stamp of a data pool item
    if ( pDP->getTimeStamp(<xsl:value-of select="DataPoolItem[position()=1]/Id/@value"/>)!=time )
    {	setTestResult(TEST_FAILURE, "Wrong time stamp");
        return;
    }
</xsl:if>
<xsl:if test="ValidityStatus">
    // Check the setting/getting of the validity status
    id = <xsl:value-of select="DataPoolItem[position()=1]/Id/@value"/>;
    pDP->setValidityStatus(id,false);
    if ( pDP->isValid(id) )
    {      setTestResult(TEST_FAILURE, "Wrong validity status");
           return;
    }

    // Check illegal attempt to set the validity status
    if (isNonNominalCheckAllowed()) {
        pDP->setValidityStatus(<xsl:value-of select="$maxParId"/>+1,false);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt = nEvt+1;
    }

    // Reset the data pool and check that all items are valid
    id = <xsl:value-of select="DataPoolItem[position()=1]/Id/@value"/>;
    pDP->setValidityStatus(id,false);
    pDP->reset();
    if ( !pDP->isValid(id) )
    {      setTestResult(TEST_FAILURE, "Reset failure");
           return;
    }

</xsl:if>
<xsl:if test="BackUpValue">
    // Check the back-up value mechanism  (for an integer-valued data pool item)
    id = <xsl:value-of select="DataPoolItem[Type/@value='TD_Integer'][position()=1]/Id/@value"/>;
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
    id = <xsl:value-of  select="DataPoolItem[Type/@value='TD_Float'][position()=1]/Id/@value"/>;
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
</xsl:if>
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
<xsl:if test="TypeChecking">
    if ( !pDP->isFloat(firstRealId) || pDP->isInteger(firstRealId) )
    {   setTestResult(TEST_FAILURE, "Error in type checking service");
        return;
    }
    if ( !pDP->isInteger(firstIntegerId) || pDP->isFloat(firstIntegerId) )
    {   setTestResult(TEST_FAILURE, "Error in type checking service");
        return;
    }
</xsl:if>
<xsl:if test="RobustnessLevel/@value!=1">
    if (isNonNominalCheckAllowed()) {
        // Check use of illegal parameter identifier in a setter method
        pDP->setValue(maxParId+1,(TD_Float)0);
        pDP->setValue(maxParId+1,(TD_Integer)0);
        if ( !verifyLatestEvent(nEvt+2,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt = nEvt+2;

        // Check use of illegal type in a setter method
        pDP->setValue(firstIntegerId,(TD_Float)0);
        pDP->setValue(firstRealId,(TD_Integer)0);
        if ( !verifyLatestEvent(nEvt+2,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt = nEvt+2;

        // Check use of illegal parameter identifier in a pointer getter method
        char* dummy_1;
        dummy_1 = (char*)pDP->getPointerFloatValue(maxParId+1);
        dummy_1 = (char*)pDP->getPointerIntegerValue(maxParId+1);
        if ( !verifyLatestEvent(nEvt+2,EVT_ILLEGAL_DP_ACCESS) )
           return;
        nEvt = nEvt+2;

        // Check use of illegal type in a pointer getter method
        dummy_1 = (char*)pDP->getPointerFloatValue(firstIntegerId);
        dummy_1 = (char*)pDP->getPointerIntegerValue(firstRealId);
        if ( !verifyLatestEvent(nEvt+2,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt = nEvt+2;
        <xsl:if test="MonitoringProfile">
        // Check use of out-of-range parameter identifier in a monitoring profile setter method
        pDP->setMonitoringProfile(maxParId+1,pNP);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;

        // Check use of illegal parameter identifier in a monitoring profile setter method
        pDP->setMonitoringProfile(lowestIllegalParId,pNP);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;
        </xsl:if>
        <xsl:if test="RecoveryAction">
        // Check use of out-of-range parameter identifier in a recovery action setter method
        pDP->setRecoveryAction(maxParId+1,pRA);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;

        // Check use of illegal parameter identifier in a recovery action setter method
        pDP->setRecoveryAction(lowestIllegalParId,pRA);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;
        </xsl:if>
    }
</xsl:if>
<xsl:if test="RobustnessLevel/@value=3">
    if (isNonNominalCheckAllowed()) {
        // Check use of out-of-range parameter identifier in a type checking method
        bool b = pDP->isFloat(maxParId+1);
        b = pDP->isInteger(maxParId+1);
        if ( !verifyLatestEvent(nEvt+2,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt = nEvt+2;

        // Check use of invalid parameter identifier in a type checking method
        b = pDP->isFloat(lowestIllegalParId);
        b = pDP->isInteger(lowestIllegalParId);
        if ( !verifyLatestEvent(nEvt+2,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt = nEvt+2;

        // Check use of illegal parameter identifier in a getter method
        TD_Float dummy_f;
        TD_Integer dummy_i;
        dummy_f = pDP->getFloatValue(maxParId+1);
        dummy_i = pDP->getIntegerValue(maxParId+1);
        if ( !verifyLatestEvent(nEvt+2,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt = nEvt+2;

        // Check use of illegal type in a getter method
        dummy_f = pDP->getFloatValue(firstIntegerId);
        dummy_i = pDP->getIntegerValue(firstRealId);
        if ( !verifyLatestEvent(nEvt+2,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt = nEvt+2;
        <xsl:if test="DataItem">
        // Check use of out-of-range parameter identifier in a data item getter method
        DC_DataItem* pDI;
        pDI = pDP->getDataItem(maxParId+1);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;

        // Check use of illegal parameter identifier in a data item getter method
        pDI = pDP->getDataItem(lowestIllegalParId);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;
        </xsl:if>
        <xsl:if test="MonitoringProfile">
        // Check use of out-of-range parameter identifier in a monitoring profile getter method
        MonitoringProfile* pMP = pDP->getMonitoringProfile(maxParId+1);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;

        // Check use of illegal parameter identifier in a monitoring profile getter method
        pMP = pDP->getMonitoringProfile(lowestIllegalParId);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;
        </xsl:if>
        <xsl:if test="RecoveryAction">
        // Check use of out-of-range parameter identifier in a recovery action getter method
        RecoveryAction* pRec = pDP->getRecoveryAction(maxParId+1);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;

        // Check use of illegal parameter identifier in a recovery action getter method
        pRec = pDP->getRecoveryAction(lowestIllegalParId);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;
        </xsl:if>
        <xsl:if test="TimeStamp">
        // Check use of out-of-range parameter identifier in a time stamp getter method
        TD_ObsTime t = pDP->getTimeStamp(maxParId+1);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;

        // Check use of illegal parameter identifier in a time stamp getter method
        t = pDP->getTimeStamp(lowestIllegalParId);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;
        </xsl:if>
        <xsl:if test="ValidityStatus">
        // Check use of out-of-range parameter identifier in a validity status getter method
        bool vs = pDP->isValid(maxParId+1);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;

        // Check use of illegal parameter identifier in a validity status getter method
        vs = pDP->isValid(lowestIllegalParId);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;
        </xsl:if>
    }
</xsl:if>
   setTestResult(TEST_SUCCESS,"Test Successful");
   return;
   }
-->
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
    TD_DataPoolId numberOfPar = <xsl:value-of select="$numberOfPar"/>;
<xsl:if test="(not(RobustnessLevel/Low)) or (TypeChecking)">
    // Variable to hold first identifier of a real-value parameter
    TD_DataPoolId firstRealId = <xsl:value-of 
            select="DataPoolItem[Type/@value='TD_Float'][position()=1]/Id/@value"/>;

    // Variable to hold first identifier of an integer-valued parameter
    TD_DataPoolId firstIntegerId = <xsl:value-of 
            select="DataPoolItem[Type/@value='TD_Integer'][position()=1]/Id/@value"/>;
</xsl:if>
    // Instantiate datapool
    <xsl:value-of select="$ClassName"/>* pDP = new <xsl:value-of select="$ClassName"/>();

    // Variable to hold maximum parameter identifier
    TD_DataPoolId maxParId;
    maxParId = <xsl:value-of select="$maxParId"/>;

    // Auxiliary variable to hold a data pool item identifier
    TD_DataPoolId id;
    id = 0;

    // Variable to hold the lowest illegal parameter id
    TD_DataPoolId lowestIllegalParId;
    lowestIllegalParId = (TD_DataPoolId)<xsl:value-of select="$lowestIllegalParId"/>;

    // Verify correctness of class ID
    if (pDP->getClassId() != <xsl:value-of select="$ClassId"/>)
    {      setTestResult(TEST_FAILURE, "Wrong class ID");
            return;
    }
<xsl:if test="(ValidityStatus)">
    // Check default value of validity status.
    <xsl:text/>
    <xsl:for-each select="DataPoolItem">
    if ( !pDP->isValid(<xsl:value-of select="Id/@value"/>) )
    {      setTestResult(TEST_FAILURE, "Wrong default validity status on data item <xsl:value-of select="Id/@value"/>");
            return;
    }
    </xsl:for-each>
</xsl:if>
<xsl:if test="(TimeStamp)">
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
</xsl:if>
<xsl:if test="(MonitoringProfile) or (RecoveryAction)">
    // Check that the data pool is not yet configured
    if ( pDP->isObjectConfigured() != NOT_CONFIGURED )
    {      setTestResult(TEST_FAILURE, "Incorrect configuration status at creation");
            return;
    }
</xsl:if>
<xsl:if test="MonitoringProfile">
    // Load monitoring profiles and check correctness of load operations
    DC_NullProfile* pNP = new DC_NullProfile();  <xsl:text/>
    <xsl:for-each select="DataPoolItem">
    pDP->setMonitoringProfile(<xsl:value-of select="Id/@value"/>,pNP);
    if (pDP->getMonitoringProfile(<xsl:value-of select="Id/@value"/>)!=pNP)
    {	setTestResult(TEST_FAILURE, "Failure to read back monitoring profile");
        return;
    }
    </xsl:for-each>
</xsl:if>
<xsl:if test="RecoveryAction">
    // Load recovery actions and check correctness of load operations
    DC_NullRecoveryAction* pRA = new DC_NullRecoveryAction();  <xsl:text/>
    <xsl:for-each select="DataPoolItem">
    pDP->setRecoveryAction(<xsl:value-of select="Id/@value"/>,pRA);
    if (pDP->getRecoveryAction(<xsl:value-of select="Id/@value"/>)!=pRA)
    {	setTestResult(TEST_FAILURE, "Failure to read back recovery action");
        return;
    }
    </xsl:for-each>
</xsl:if>
<xsl:if test="(MonitoringProfile) or (RecoveryAction) or (TimeStamp)">
    // Check that the data pool is configured
    if ( pDP->isObjectConfigured() != CONFIGURED )
     {      setTestResult(TEST_FAILURE, "Incorrect configuration status");
            return;
      }
</xsl:if>
    // Check data setting and getting services for the data pool item values
    // Do it for the real-value items first and then for the interger-valued items
<xsl:for-each select="DataPoolItem[Type/@value='TD_Float']">
    id = <xsl:value-of select="Id/@value"/>;
    pDP->setValue(id,(TD_Float)id);
    if ( fabs((float)(pDP->getFloatValue(id)-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    if ( fabs((float)((*pDP->getPointerFloatValue(id))-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }<xsl:if test="DataItem">
    if ( fabs((float)(pDP->getDataItem(id)->getFloat()-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }</xsl:if>
</xsl:for-each>
<xsl:for-each select="DataPoolItem[Type/@value='TD_Integer']">
    id = <xsl:value-of select="Id/@value"/>;
    pDP->setValue(id,(TD_Integer)id);
    if ( pDP->getIntegerValue(id)!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    if ( (*pDP->getPointerIntegerValue(id))!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }<xsl:if test="DataItem">
    if ( pDP->getDataItem(id)->getInt()!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }</xsl:if>
</xsl:for-each>
<xsl:if test="TimeStamp">
    // Check the time stamp of a data pool item
    if ( pDP->getTimeStamp(<xsl:value-of select="DataPoolItem[position()=1]/Id/@value"/>)!=time )
    {	setTestResult(TEST_FAILURE, "Wrong time stamp");
        return;
    }
</xsl:if>
<xsl:if test="ValidityStatus">
    // Check the setting/getting of the validity status
    id = <xsl:value-of select="DataPoolItem[position()=1]/Id/@value"/>;
    pDP->setValidityStatus(id,false);
    if ( pDP->isValid(id) )
    {      setTestResult(TEST_FAILURE, "Wrong validity status");
           return;
    }

    // Check illegal attempt to set the validity status
    if (isNonNominalCheckAllowed()) {
        pDP->setValidityStatus(<xsl:value-of select="$maxParId"/>+1,false);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt = nEvt+1;
    }

    // Reset the data pool and check that all items are valid
    id = <xsl:value-of select="DataPoolItem[position()=1]/Id/@value"/>;
    pDP->setValidityStatus(id,false);
    pDP->reset();
    if ( !pDP->isValid(id) )
    {      setTestResult(TEST_FAILURE, "Reset failure");
           return;
    }

</xsl:if>
<xsl:if test="BackUpValue">
    // Check the back-up value mechanism  (for an integer-valued data pool item)
    id = <xsl:value-of select="DataPoolItem[Type/@value='TD_Integer'][position()=1]/Id/@value"/>;
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
    id = <xsl:value-of  select="DataPoolItem[Type/@value='TD_Float'][position()=1]/Id/@value"/>;
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
</xsl:if>
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
<xsl:if test="TypeChecking">
    if ( !pDP->isFloat(firstRealId) || pDP->isInteger(firstRealId) )
    {   setTestResult(TEST_FAILURE, "Error in type checking service");
        return;
    }
    if ( !pDP->isInteger(firstIntegerId) || pDP->isFloat(firstIntegerId) )
    {   setTestResult(TEST_FAILURE, "Error in type checking service");
        return;
    }
</xsl:if>
<xsl:if test="RobustnessLevel/@value!=1">
    if (isNonNominalCheckAllowed()) {
        // Check use of illegal parameter identifier in a setter method
        pDP->setValue(maxParId+1,(TD_Float)0);
        pDP->setValue(maxParId+1,(TD_Integer)0);
        if ( !verifyLatestEvent(nEvt+2,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt = nEvt+2;

        // Check use of illegal type in a setter method
        pDP->setValue(firstIntegerId,(TD_Float)0);
        pDP->setValue(firstRealId,(TD_Integer)0);
        if ( !verifyLatestEvent(nEvt+2,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt = nEvt+2;

        // Check use of illegal parameter identifier in a pointer getter method
        char* dummy_1;
        dummy_1 = (char*)pDP->getPointerFloatValue(maxParId+1);
        dummy_1 = (char*)pDP->getPointerIntegerValue(maxParId+1);
        if ( !verifyLatestEvent(nEvt+2,EVT_ILLEGAL_DP_ACCESS) )
           return;
        nEvt = nEvt+2;

        // Check use of illegal type in a pointer getter method
        dummy_1 = (char*)pDP->getPointerFloatValue(firstIntegerId);
        dummy_1 = (char*)pDP->getPointerIntegerValue(firstRealId);
        if ( !verifyLatestEvent(nEvt+2,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt = nEvt+2;
        <xsl:if test="MonitoringProfile">
        // Check use of out-of-range parameter identifier in a monitoring profile setter method
        pDP->setMonitoringProfile(maxParId+1,pNP);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;

        // Check use of illegal parameter identifier in a monitoring profile setter method
        pDP->setMonitoringProfile(lowestIllegalParId,pNP);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;
        </xsl:if>
        <xsl:if test="RecoveryAction">
        // Check use of out-of-range parameter identifier in a recovery action setter method
        pDP->setRecoveryAction(maxParId+1,pRA);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;

        // Check use of illegal parameter identifier in a recovery action setter method
        pDP->setRecoveryAction(lowestIllegalParId,pRA);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;
        </xsl:if>
    }
</xsl:if>
<xsl:if test="RobustnessLevel/@value=3">
    if (isNonNominalCheckAllowed()) {
        // Check use of out-of-range parameter identifier in a type checking method
        bool b = pDP->isFloat(maxParId+1);
        b = pDP->isInteger(maxParId+1);
        if ( !verifyLatestEvent(nEvt+2,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt = nEvt+2;

        // Check use of invalid parameter identifier in a type checking method
        b = pDP->isFloat(lowestIllegalParId);
        b = pDP->isInteger(lowestIllegalParId);
        if ( !verifyLatestEvent(nEvt+2,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt = nEvt+2;

        // Check use of illegal parameter identifier in a getter method
        TD_Float dummy_f;
        TD_Integer dummy_i;
        dummy_f = pDP->getFloatValue(maxParId+1);
        dummy_i = pDP->getIntegerValue(maxParId+1);
        if ( !verifyLatestEvent(nEvt+2,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt = nEvt+2;

        // Check use of illegal type in a getter method
        dummy_f = pDP->getFloatValue(firstIntegerId);
        dummy_i = pDP->getIntegerValue(firstRealId);
        if ( !verifyLatestEvent(nEvt+2,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt = nEvt+2;
        <xsl:if test="DataItem">
        // Check use of out-of-range parameter identifier in a data item getter method
        DC_DataItem* pDI;
        pDI = pDP->getDataItem(maxParId+1);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;

        // Check use of illegal parameter identifier in a data item getter method
        pDI = pDP->getDataItem(lowestIllegalParId);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;
        </xsl:if>
        <xsl:if test="MonitoringProfile">
        // Check use of out-of-range parameter identifier in a monitoring profile getter method
        MonitoringProfile* pMP = pDP->getMonitoringProfile(maxParId+1);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;

        // Check use of illegal parameter identifier in a monitoring profile getter method
        pMP = pDP->getMonitoringProfile(lowestIllegalParId);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;
        </xsl:if>
        <xsl:if test="RecoveryAction">
        // Check use of out-of-range parameter identifier in a recovery action getter method
        RecoveryAction* pRec = pDP->getRecoveryAction(maxParId+1);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;

        // Check use of illegal parameter identifier in a recovery action getter method
        pRec = pDP->getRecoveryAction(lowestIllegalParId);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;
        </xsl:if>
        <xsl:if test="TimeStamp">
        // Check use of out-of-range parameter identifier in a time stamp getter method
        TD_ObsTime t = pDP->getTimeStamp(maxParId+1);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;

        // Check use of illegal parameter identifier in a time stamp getter method
        t = pDP->getTimeStamp(lowestIllegalParId);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;
        </xsl:if>
        <xsl:if test="ValidityStatus">
        // Check use of out-of-range parameter identifier in a validity status getter method
        bool vs = pDP->isValid(maxParId+1);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;

        // Check use of illegal parameter identifier in a validity status getter method
        vs = pDP->isValid(lowestIllegalParId);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt++;
        </xsl:if>
    }
</xsl:if>
   setTestResult(TEST_SUCCESS,"Test Successful");
   return;
}
   

///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

// the following may be useful if you don't need it, just delete.
// <xsl:value-of select="$TestCaseClassName"/> *this = <xsl:value-of select="translate($TestCaseClassName,$LowerCase,$UpperCase)"/>(obj)


/**
 * Set the identifier and the name of the test case to: 
 * <xsl:value-of select="$ClassId"/>*10+1 and "<xsl:value-of select="$TestCaseClassName"/>".
 */
static void instance_init(Object *obj)
{
    (TestCase*)(obj)->testId=<xsl:value-of select="$ClassId"/>*10+1;
    (TestCase*)(obj)->testName=<xsl:value-of select="$TestCaseClassName"/>;
    return;
}

<xsl:value-of select="$TestCaseClassName"/>* <xsl:value-of select="$TestCaseClassName"/>_new(void)
{
        return (<xsl:value-of select="$TestCaseClassName"/>*)object_new(TYPE_<xsl:value-of select="translate($TestCaseClassName,$LowerCase,$UpperCase)"/>);

}

///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////
static void class_init(ObjectClass *oc, void *data)
{
<xsl:value-of select="$TestCaseClassName"/>Class *t_p_class = <xsl:value-of select="translate($TestCaseClassName,$LowerCase,$UpperCase)"/>_CLASS(oc);

        t_p_class->runTestCase = runTestCase;

}

static const TypeInfo type_info = {
        .name = TYPE_<xsl:value-of select="translate($TestCaseClassName,$LowerCase,$UpperCase)"/>,
        .parent = TYPE_TESTCASEWITHWITHEVTCHECK,
        .instance_size = sizeof(<xsl:value-of select="$TestCaseClassName"/>),
        .abstract = false,
        .class_size = sizeof(<xsl:value-of select="$TestCaseClassName"/>Class),
        .instance_init = instance_init,
        .class_init = class_init,

};

void <xsl:value-of select="$TestCaseClassName"/>_register(void)
{
        type_register_static(&amp;type_info);

}
</xsl:document>
</xsl:template>

<!--================================================================-->
<!-- Utility to process a string made up of several words           -->
<!-- separated by a space and returning the same string with the    -->
<!-- same words with the first letter of each word capitalized.     -->
<!--================================================================-->

<xsl:template name="makeFirstLetterCap">
  <xsl:param name="before"/>
  <xsl:param name="after"/>
  <xsl:variable name="firstInitial" select="substring($after,1,1)"/>
  <xsl:variable name="restOfString" select="substring($after,2,string-length($after))"/>
  <xsl:variable name="firstLetterCap" select="translate(
          $firstInitial,'abcdefghijlmnopqrstuvywz','ABCDEFGHIJLMNOPQRSTUVYWZ')"/>
  <xsl:variable name="afterWithFirstCap" select="concat($firstLetterCap,$restOfString)"/>
  <xsl:choose>
    <xsl:when test="contains($afterWithFirstCap,' ')">
      <xsl:variable name="after_1" select="substring-before($afterWithFirstCap,' ')"/>
      <xsl:variable name="after_2" select="substring-after($afterWithFirstCap,' ')"/>
      <xsl:variable name="newBefore" select="concat($before,$after_1)"/>
      <xsl:call-template name="makeFirstLetterCap">
        <xsl:with-param name="before" select="$newBefore"/>
        <xsl:with-param name="after" select="$after_2"/>
      </xsl:call-template>
    </xsl:when>
    <xsl:otherwise>
      <xsl:value-of select="concat($before,$afterWithFirstCap)"/>
    </xsl:otherwise>
  </xsl:choose>

</xsl:template>

<!--================================================================-->
<!-- Utility to compute the lowest parId to which no data pool      -->
<!-- parameter is associated.                                       -->
<!-- If there are no gaps in the parameter identifiers, this        -->
<!-- template rule will return the value of the maximum parameter   -->
<!-- identifier + 1.                                                -->
<!-- When it is called the first time, the parameter 'current'      -->
<!-- should be set to one.                                          -->
<!--================================================================-->

<xsl:template name="computeLowestIllegalParId">
  <xsl:param name="current"/>
  <xsl:choose>
    <xsl:when test="//DataPoolItem/Id[@value=$current]">
      <xsl:call-template name="computeLowestIllegalParId">
        <xsl:with-param name="current" select="$current+1"/>
      </xsl:call-template>
    </xsl:when>
    <xsl:otherwise>
      <xsl:value-of select="$current"/>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

<!--================================================================-->
<!-- Utility to compute the maximum value of the Id/@value field on -->
<!-- all the Attribute elements.                                    -->
<!-- When it is called the first time, the parameter 'currentMax'   -->
<!-- should be set to zero and the parameter 'currentPos' should be -->
<!-- set to 1.                                                      -->
<!--================================================================-->

<xsl:template name="computeMaxParId">
  <xsl:param name="currentMax"/>
  <xsl:param name="currentPos"/>
  <xsl:choose>
    <xsl:when test="$currentPos=count(//DataPoolItem/Id)">
      <xsl:value-of select="$currentMax"/>
    </xsl:when>
    <xsl:otherwise>
      <xsl:variable name="valOfNextParId" select="//DataPoolItem[$currentPos+1]/Id/@value"/>
      <xsl:choose>
        <xsl:when test="$currentMax &lt; $valOfNextParId">
          <xsl:call-template name="computeMaxParId">
            <xsl:with-param name="currentMax" select="$valOfNextParId"/>
            <xsl:with-param name="currentPos" select="$currentPos+1"/>
          </xsl:call-template>
        </xsl:when>
        <xsl:otherwise>
          <xsl:call-template name="computeMaxParId">
            <xsl:with-param name="currentMax" select="$currentMax"/>
            <xsl:with-param name="currentPos" select="$currentPos+1"/>
          </xsl:call-template>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

</xsl:stylesheet>
