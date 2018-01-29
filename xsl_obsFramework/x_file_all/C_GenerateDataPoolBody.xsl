<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2003 P&P Software GmbH                               -->
<!--================================================================-->

<!--===================================================================
Generator meta-component for a data pool class for the OBS Framework.

This XSLT program generates the body file of the data pool class.

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
 <xsl:include href="ClassIdFromClassName.xsl"/>
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

  <xsl:variable name="maxParId">
    <xsl:call-template name="computeMaxParId">
       <xsl:with-param name="currentMax" select="0"/>
       <xsl:with-param name="currentPos" select="1"/>
    </xsl:call-template>
  </xsl:variable>
  <xsl:variable name="TargetFile" select="concat('/home/wangshaobo/obs_xml_xsl/projects_c/',@type)"/>     
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
// <xsl:value-of select="$ClassName"/>.c
//
// Automatically generated file

#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/CompilerSwitches.h"
#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/DebugSupport.h"
#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/BasicTypes.h"
#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/ClassId.h"
#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/Constants.h"
#include "<xsl:value-of select="$CodeDir"/>Base/CC_RootObject.h"
#include "<xsl:value-of select="$CodeDir"/>System/ObsClock.h"
#include "<xsl:value-of select="$CodeDir"/>Data/DC_SettableDataItem.h"
#include "<xsl:value-of select="$ClassName"/>.h"

static unsigned int const TD_FloatCode = 1;
static unsigned int const TD_IntegerCode = 2;

<!--=======================================================================================-->
///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

<xsl:if test="TimeStamp">
void <xsl:value-of select="$ClassName"/>_setObsClock(<xsl:value-of select="$ClassName"/> *this, ObsClock* pObsClock)
{
    assert( pObsClock != pNULL );               
    this->pObsClock = pObsClock;
}

ObsClock* <xsl:value-of select="$ClassName"/>_getObsClock(const <xsl:value-of select="$ClassName"/> *this)
{
    return this->pObsClock;
}

</xsl:if>



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////





<!--=======================================================================================-->
static void setValueFloat(void *obj,TD_DataPoolId id, TD_Float newValue) {
    assert( id &lt;= <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId );               <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] == TD_FloatCode );
 </xsl:if>
 <xsl:if test="not(RobustnessLevel/Low)">
    if ( id > <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return;
    }<xsl:if test="TypeChecking">
    if ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] != TD_FloatCode ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return;
    }</xsl:if>
 </xsl:if>
    (*(TD_Float*)<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue[id]) = newValue;        <xsl:text/>
 <xsl:if test="TimeStamp">
    <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->timeStamp[id] = <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pObsClock->getTime();        <xsl:text/>
 </xsl:if>
 <xsl:if test="(BackUpValue) and (ValidityStatus)">
    if ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->valid[id] )
        (*(TD_Float*)<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pBackUpValue[id]) = newValue;          <xsl:text/>
 </xsl:if>
}
<!--=======================================================================================-->
static void setValueInt(void *obj, TD_DataPoolId id, TD_Integer newValue) {
    assert( id &lt;= <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId );           <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] == TD_IntegerCode );
 </xsl:if>
 <xsl:if test="not(RobustnessLevel/Low)">
    if ( id > <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return;
    }<xsl:if test="TypeChecking">
    if ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] != TD_IntegerCode ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return;
    }</xsl:if>
 </xsl:if>
    (*(TD_Integer*)<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue[id]) = newValue;      <xsl:text/>
 <xsl:if test="TimeStamp">
    <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->timeStamp[id] = <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pObsClock->getTime();        <xsl:text/>
 </xsl:if>
 <xsl:if test="(BackUpValue) and (ValidityStatus)">
    if ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->valid[id] )
        (*(TD_Integer*)<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pBackUpValue[id]) = newValue;        <xsl:text/>
 </xsl:if>
}
<!--=======================================================================================-->
static TD_Float getFloatValue(void *obj, TD_DataPoolId id) {
    assert( id &lt;= <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId );           <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] == TD_FloatCode );
 </xsl:if>
 <xsl:if test="RobustnessLevel/High">
    if ( id > <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return (TD_Float)0;
    }<xsl:if test="TypeChecking">
    if ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] != TD_FloatCode ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return (TD_Float)0;
    }</xsl:if>
 </xsl:if>
 <xsl:choose>
   <xsl:when test="(BackUpValue) and (ValidityStatus)">
    if ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->valid[id] )
        return (*(TD_Float*)<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue[id]);
    else
        return (*(TD_Float*)<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pBackUpValue[id]);
   </xsl:when>
   <xsl:otherwise>
    return (*(TD_Float*)<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue[id]);         <xsl:text/>
   </xsl:otherwise>
 </xsl:choose>
}
<!--=======================================================================================-->
static TD_Integer getIntegerValue(void *obj, TD_DataPoolId id) {
    assert( id &lt;= <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId );           <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] == TD_IntegerCode );
 </xsl:if>
 <xsl:if test="RobustnessLevel/High">
    if ( id > <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return (TD_Integer)0;
    }<xsl:if test="TypeChecking">
    if ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] != TD_IntegerCode ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return (TD_Integer)0;
    }</xsl:if>
 </xsl:if>
 <xsl:choose>
   <xsl:when test="(BackUpValue) and (ValidityStatus)">
    if ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->valid[id] )
        return (*(TD_Integer*)<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue[id]);
    else
        return (*(TD_Integer*)<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pBackUpValue[id]);
   </xsl:when>
   <xsl:otherwise>
    return (*(TD_Integer*)<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue[id]);           <xsl:text/>
   </xsl:otherwise>
 </xsl:choose>
}
<!--=======================================================================================-->
static TD_Float* getPointerFloatValue(void *obj, TD_DataPoolId id) {
    assert( id &lt;= <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId );           <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] == TD_FloatCode );
 </xsl:if>
 <xsl:if test="not(RobustnessLevel/Low)">
    if ( id > <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pDefaultFloat;
    }<xsl:if test="TypeChecking">
    if ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] != TD_FloatCode ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pDefaultFloat;
     }</xsl:if>
 </xsl:if>
    return ((TD_Float*)<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue[id]);
}
<!--=======================================================================================-->
static TD_Integer* getPointerIntegerValue(void *obj, TD_DataPoolId id) {
    assert( id &lt;= <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId );           <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] == TD_IntegerCode );
 </xsl:if>
 <xsl:if test="not(RobustnessLevel/Low)">
    if ( id > <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pDefaultInt;
    }<xsl:if test="TypeChecking">
    if ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] != TD_IntegerCode ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pDefaultInt;
    }</xsl:if>
 </xsl:if>
    return ((TD_Integer*)<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue[id]);
}
<!--=======================================================================================-->
 <xsl:if test="DataItem">
static DC_DataItem* getDataItem(void *obj, TD_DataPoolId id) {
    assert( id &lt;= <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId );           <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] != -1 );
 </xsl:if>
 <xsl:if test="not(RobustnessLevel/Low)">
    if ( id > <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
       <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
       return <xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->getDataItem(id);
    }<xsl:if test="TypeChecking">
    if ( type[id] == -1 ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
       return <xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->getDataItem(id);
    }</xsl:if>
 </xsl:if>
 return <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pDataItem[id];
}

 </xsl:if>
<!--=======================================================================================-->
 <xsl:if test="TimeStamp">
static TD_ObsTime getTimeStamp(void *obj,TD_DataPoolId id) {
    assert( id &lt;= <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId );           <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] != -1 );
 </xsl:if>
 <xsl:if test="RobustnessLevel/High">
    if ( id > <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
       return <xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->getTimeStamp(id);
    }<xsl:if test="TypeChecking">
    if ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] == -1 ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
       return <xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->getTimeStamp(id);
    }</xsl:if>
 </xsl:if>
    return <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->timeStamp[id];
}
 </xsl:if>
<!--=======================================================================================-->
<xsl:if test="ValidityStatus">
static bool isValid(void *obj, TD_DataPoolId id) {
    assert( id &lt;= <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId );               <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] != -1 );
 </xsl:if>
 <xsl:if test="RobustnessLevel/High">
    if ( id > <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return <xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->isValid(id);
    }<xsl:if test="TypeChecking">
    if ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] == -1 ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return <xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->isValid(id);
    }</xsl:if>
 </xsl:if>
    return <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->valid[id];
}

static void setValidityStatus(void *obj,TD_DataPoolId id, bool newValidityStatus) {
    assert( id &lt;= <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId );       <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] != -1 );
 </xsl:if>
    if ( id > <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return;
        }

 <xsl:if test="(BackUpValue) and (DataItem)">
    if ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->valid[id] &amp;&amp; !newValidityStatus)       // change from valid to not valid
    <xsl:value-of select="'DC_SETTABLEDATAITEM'"/>_GET_CLASS(<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pDataItem[id])->setVariable((TD_Integer*) <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pBackUpValue[id]);   // make the data item point to the backup value
    if ( ! <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->valid[id] &amp;&amp; newValidityStatus)       // change from not valid to valid
    <xsl:value-of select="'DC_SETTABLEDATAITEM'"/>_GET_CLASS(<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pDataItem[id])->setVariable((TD_Integer*) <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue[id]);   // make the data item point to the primary value
 </xsl:if>   
   <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->valid[id] = newValidityStatus;
}
</xsl:if>
<!--=======================================================================================-->
<xsl:if test="MonitoringProfile">
static MonitoringProfile* getMonitoringProfile(void *obj,TD_DataPoolId id) {
    assert( id &lt;= <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId );       <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] != -1 );
 </xsl:if>
 <xsl:if test="RobustnessLevel/High">
    if ( id > <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return <xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->getMonitoringProfile(id);
    }<xsl:if test="TypeChecking">
        if ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] == -1 ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return <xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->getMonitoringProfile(id);
    }</xsl:if>
 </xsl:if>
    return <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pMonitoringProfile[id];
}

static void setMonitoringProfile(void *obj,TD_DataPoolId id, MonitoringProfile* pMonProf) {
    assert( pMonProf != pNULL );
    assert( id &lt;= <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId );           <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] != -1 );
 </xsl:if>
 <xsl:if test="not(RobustnessLevel/Low)">
    if ( id > <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return;
    }<xsl:if test="TypeChecking">
    if ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] == -1 ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return;
    }</xsl:if>
 </xsl:if>
    <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pMonitoringProfile[id] = pMonProf;
}
</xsl:if>
<!--=======================================================================================-->
<xsl:if test="RecoveryAction">
static RecoveryAction* getRecoveryAction(void *obj, TD_DataPoolId id) {
    assert( id &lt;= <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId );           <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] != -1 );
 </xsl:if>
 <xsl:if test="RobustnessLevel/High">
    if ( id > <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return <xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->getRecoveryAction(id);
    }<xsl:if test="TypeChecking">
    if ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] == -1 ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return <xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->getRecoveryAction(id);
    }</xsl:if>
 </xsl:if>
    return <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pRecoveryAction[id];
}

static void setRecoveryAction(void *obj, TD_DataPoolId id, RecoveryAction* pRecAct) {
    assert( pRecAct != pNULL );
    assert( id &lt;= <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId );               <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] != -1 );
 </xsl:if>
 <xsl:if test="not(RobustnessLevel/Low)">
    if ( id > <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return;
    }<xsl:if test="TypeChecking">
    if ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] == -1 ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return;
    }</xsl:if>
 </xsl:if>
    <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pRecoveryAction[id] = pRecAct;
}
</xsl:if>
<!--=======================================================================================-->
static TD_DataPoolId firstIdentifier(void *obj) {
    assert( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue != pNULL );
    <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->iterationCounter = 0;
    while ( (<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue[<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->iterationCounter]==pNULL) &amp;&amp; (<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->iterationCounter&lt;<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId) )
        <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->iterationCounter++;
    return <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->iterationCounter;
}

static TD_DataPoolId nextIdentifier(void *obj) {
    assert( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue != pNULL );
    <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->iterationCounter++;
    while ( (<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue[<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->iterationCounter]==pNULL) &amp;&amp; (<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->iterationCounter&lt;<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId) )
        <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->iterationCounter++;
    return <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->iterationCounter;
}

static bool isLastIdentifier(void *obj) {
    assert( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue != pNULL );
    return ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->iterationCounter &gt; <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId );
}
<!--=======================================================================================-->
<xsl:if test="TypeChecking">
static bool isFloat(void *obj, TD_DataPoolId id) {
    assert( id &lt;= <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId );           <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] != -1 );
 </xsl:if>
 <xsl:if test="RobustnessLevel/High">
    if ( id > <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return <xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->isFloat(id);
    }<xsl:if test="TypeChecking">
    if ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] == -1 ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return <xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->isFloat(id);
    }</xsl:if>
 </xsl:if>
    return ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] == TD_FloatCode );
}

static bool isInteger(void *obj,TD_DataPoolId id) {
    assert( id &lt;= <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId );       <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] != -1 );
 </xsl:if>
 <xsl:if test="RobustnessLevel/High">
    if ( id > <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return <xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->isInteger(id);
    }<xsl:if test="TypeChecking">
    if ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] == -1 ) {
       DC_EventRepository* dc_e_r=CC_RootObject_getEventRepository();
      <xsl:value-of select="translate('DC_EventRepository',$LowerCase,$UpperCase)"/>_GET_CLASS(dc_e_r)->create(obj,EVT_ILLEGAL_DB_ACCESS);
        return <xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->isInteger(id);
    }</xsl:if>
 </xsl:if>
    return ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[id] == TD_IntegerCode );
}
</xsl:if>
<!--=======================================================================================-->
<xsl:if test="(MonitoringProfile) or (RecoveryAction) or (TimeStamp)">
static bool isObjectConfigured(void *obj) {

   // Check configuration of super object
   if (!<xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->isObjectConfigured(id)<xsl:if test="TimeStamp">||(<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pObsClock==pNULL)</xsl:if>)
       return NOT_CONFIGURED;
   for (TD_DataPoolId i=<xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->firstIdentifier(); !<xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->isLastIdentifier(); i=<xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->nextIdentifier())
       if ( (<xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->getMonitoringProfile(i)==pNULL) || (<xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->getRecoveryAction(i)==pNULL) )
            return false;
   return true;
}
</xsl:if>
<!--=======================================================================================-->
<xsl:if test="ValidityStatus">
static void reset(void *obj) {
   for (TD_DataPoolId i=<xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->firstIdentifier(); !<xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->isLastIdentifier(); i=<xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->nextIdentifier())
        <xsl:value-of select="'DATAPOOL'"/>_GET_CLASS(obj)->setValidityStatus(i, true);
}
</xsl:if>





///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

// the following may be useful if you don't need it, just delete.
// <xsl:value-of select="ClassName"/> *this = <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)


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

static void instance_init(object* obj) {
  
   <xsl:value-of select="translate('CC_RootObject',$LowerCase,$UpperCase)"/>_GET_CLASS(obj)->setClassId(<xsl:value-of select="$ClassId"/>);
   
   <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pDefaultFloat = (TD_Float*)malloc(sizeof(TD_Float));
   *(<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pDefaultFloat) = (TD_Float)0;
   <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pDefaultInt = (TD_Integer*)malloc(sizeof(TD_Integer)*sizeof(TD_Integer));
   *(<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pDefaultInt) = (TD_Integer)0;
  
   <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->iterationCounter = 0;
   unsigned int const numberOfRealPar = <xsl:value-of select="count(//Type[@value='TD_Float'])"/>;
   unsigned int const numberOfIntPar = <xsl:value-of select="count(//Type[@value='TD_Integer'])"/>;
   <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->size = numberOfRealPar*sizeof(TD_Float)+numberOfIntPar*sizeof(TD_Integer);
   <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId = <xsl:value-of select="$maxParId"/>;
   <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->value = (unsigned char*)malloc((size/sizeof(double))+1);
   <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue = (unsigned char**)malloc((<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId+1)*sizeof(unsigned char*));       
   <xsl:if test="BackUpValue">
       <xsl:text/>
   <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->backUpValue = (unsigned char*)malloc(<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->size);
   <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pBackUpValue = (unsigned char**)malloc((<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId+1)*sizeof(char*));
 </xsl:if>
 <xsl:if test="TimeStamp">
<xsl:text>  </xsl:text><xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pObsClock = pNULL;
   <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->timeStamp = (TD_ObsTime*)malloc((<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId+1)*sizeof(TD_ObsTime));
 </xsl:if>
 <xsl:if test="ValidityStatus">
   <xsl:text>  </xsl:text><xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->valid = (bool*)malloc((<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId+1)*sizeof(bool));
 </xsl:if>
 <xsl:if test="DataItem">
   <xsl:text>  </xsl:text><xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pDataItem = (DC_SettableDataItem**)malloc((<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId+1)*sizeof(DC_SettableDataItem*));
 </xsl:if>
 <xsl:if test="MonitoringProfile">
   <xsl:text>  </xsl:text><xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pMonitoringProfile = (MonitoringProfile**)malloc((maxParId+1)*sizeof(MonitoringProfile*));
 </xsl:if>
 <xsl:if test="RecoveryAction">
    <xsl:text>  </xsl:text><xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pRecoveryAction = (RecoveryAction**)malloc((maxParId+1)*sizeof(RecoveryAction*));  
</xsl:if>
 <xsl:if test="TypeChecking">
    <xsl:text>   </xsl:text><xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type = (char*)malloc(maxParId+1);
 </xsl:if>

   for (TD_DataPoolId i=0; i&lt; <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->size; i++)  {
         <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->value[i] = 0;
 <xsl:if test="BackUpValue"><xsl:text/>
         <xsl:text>        </xsl:text><xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->backUpValue[i] = 0;
 </xsl:if>
   }

   for (TD_DataPoolId i=0; i&lt;= <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId; i++)  {
         <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue[i] = pNULL;
 <xsl:if test="BackUpValue"><xsl:text/>
         <xsl:text>        </xsl:text><xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pBackUpValue[i] = pNULL;          
 </xsl:if>
 <xsl:if test="TimeStamp">
         <xsl:text>        </xsl:text><xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->timeStamp[i] = 0;               
 </xsl:if>
 <xsl:if test="ValidityStatus">
         <xsl:text>        </xsl:text><xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->valid[i] = true;                
 </xsl:if>
 <xsl:if test="DataItem">
         <xsl:text>        </xsl:text><xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pDataItem[i] = pNULL;
 </xsl:if>
 <xsl:if test="MonitoringProfile">
         <xsl:text>        </xsl:text><xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pMonitoringProfile[i] = pNULL;   
 </xsl:if>
 <xsl:if test="RecoveryAction">
         <xsl:text>        </xsl:text><xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pRecoveryAction[i] = pNULL;  
 </xsl:if>
 <xsl:if test="TypeChecking">
         <xsl:text>        </xsl:text><xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[i] = -1;        
 </xsl:if>
   }

 unsigned int offset = 0;       
<xsl:choose>
  <xsl:when test="//TypeChecking">
    <xsl:for-each select="DataPoolItem">
       <xsl:sort select="Id/@value" data-type="number"/>
       <xsl:choose>
         <xsl:when test="Type/@value='TD_Float'">
  <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[<xsl:value-of select="Id/@value"/>] = TD_FloatCode; 
         </xsl:when>
         <xsl:when test="Type/@value='TD_Integer'">
<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[<xsl:value-of select="Id/@value"/>] = TD_IntegerCode;
         </xsl:when>
       </xsl:choose>
    </xsl:for-each>
 // Store the TD_Float values in the first part of the array
 for (TD_DatabaseId i=0; i&lt;= <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId; i++)  {
     if ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->type[i]==TD_FloatCode) {
     <xsl:text>   </xsl:text>
         <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue[i] =  <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->value + offset;            
       <xsl:if test="//BackUpValue">                      
     <xsl:text>  </xsl:text>
         <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pBackUpValue[i] =  <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->backUpValue + offset;         
       </xsl:if> 
      <xsl:if test="//DataItem">
     <xsl:text>  </xsl:text>
         <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pDataItem[i] = DC_SettableDataItem_new((TD_Float*) <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue[i]);     
       </xsl:if>
        offset = offset + sizeof(TD_Float);                     
     } 
 }

 // Now ensure that offset is aligned with a TD_Integer
 unsigned int temp = (offset/sizeof(TD_Integer));
 if (temp*sizeof(TD_Integer)&lt;offset)
    offset = (temp+1)*sizeof(TD_Integer);

 // Store the TD_Integer values in the second part of the array
 for (TD_DatabaseId i=0; i&lt;= <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->maxParId; i++)  {
     if (type[i]==TD_IntegerCode) {
         <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue[i] =  <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->value + offset;            
       <xsl:if test="//BackUpValue">                      
         <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pBackUpValue[i] =  <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->backUpValue + offset;         
       </xsl:if> 
       <xsl:if test="//DataItem">
         <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pDataItem[i] = DC_SettableDataItem_new((TD_Integer*) <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue[i]);     
       </xsl:if>
        offset = offset + sizeof(TD_Integer);                     
     } 
 }
       </xsl:when>
   <xsl:otherwise>
 // Store the TD_Float values in the first part of the array
     <xsl:for-each select="DataPoolItem[Type/@value='TD_Float']">
        <xsl:sort select="Id/@value" data-type="number"/>
        <xsl:text>   </xsl:text><xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue[<xsl:value-of select="Id/@value"/>] =  <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->value + offset;               
        <xsl:if test="//BackUpValue">
  <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pBackUpValue[<xsl:value-of select="Id/@value"/>] =  <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->backUpValue + offset; 
        </xsl:if>
 offset = offset + sizeof(TD_Float);              <xsl:text/>
        <xsl:if test="//DataItem">
  <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pDataItem[<xsl:value-of select="Id/@value"/>] = DC_SettableDataItem_new((TD_Float*) <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue[<xsl:value-of select="Id/@value"/>]); 
        </xsl:if>
     </xsl:for-each>
 // Now ensure that offset is aligned with a TD_Integer
 unsigned int temp = (offset/sizeof(TD_Integer));
 if (temp*sizeof(TD_Integer)&lt;offset)
    offset = (temp+1)*sizeof(TD_Integer);

 // Store the TD_Integer values in the second part of the array
     <xsl:for-each select="DataPoolItem[Type/@value='TD_Integer']">
        <xsl:sort select="Id/@value" data-type="number"/>
  <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue[<xsl:value-of select="Id/@value"/>] =  <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->value + offset;            
        <xsl:if test="//BackUpValue">
  <xsl:text>      </xsl:text><xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pBackUpValue[<xsl:value-of select="Id/@value"/>] =  <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->backUpValue + offset;   
        </xsl:if>
 offset = offset + sizeof(TD_Integer);          
        <xsl:if test="//DataItem">
  <xsl:text>      </xsl:text><xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pDataItem[<xsl:value-of select="Id/@value"/>] = DC_SettableDataItem_new((TD_Integer*) <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pValue[<xsl:value-of select="Id/@value"/>]); 
        </xsl:if>
     </xsl:for-each>
   </xsl:otherwise>
</xsl:choose>

}


<xsl:value-of select="$ClassName"/>* <xsl:value-of select="$ClassName"/>_new(void)
{
    return (<xsl:value-of select="$ClassName"/>*)object_new(TYPE_<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>);
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    <xsl:value-of select="$ClassName"/>Class *dc_p_class = <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>_CLASS(oc);

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
    .name = TYPE_<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>,
    .parent = TYPE_DATAPOOL,
    .instance_size = sizeof(<xsl:value-of select="$ClassName"/>),
    .abstract = false,
    .class_size = sizeof(<xsl:value-of select="$ClassName"/>Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void <xsl:value-of select="$ClassName"/>_register(void)
{
    type_register_static(&amp;type_info);
}

</xsl:document>
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

<!--================================================================-->
<!-- Utility to compute the position of the first element among     -->
<!-- all //DataPoolItem/Type elements to have a "value" attribute   -->
<!-- equal to "$mask". If this value never occurs, then a value     -->
<!-- of zero is returned.                                           -->
<!-- The first time this template is called, the parameter          -->
<!-- "$currentPos" should have value one.                           -->
<!--================================================================-->

<xsl:template name="computeFirst">
  <xsl:param name="mask"/>
  <xsl:param name="currentPos"/>
  <xsl:choose>
    <xsl:when test="$currentPos=count(//DataPoolItem/Type)+1">
      <xsl:value-of select="'0'"/>
    </xsl:when>
    <xsl:otherwise>
      <xsl:variable name="val" select="//DataPoolItem[$currentPos]/Type/@value"/>
      <xsl:choose>
        <xsl:when test="$val = $mask">
          <xsl:value-of select="$currentPos"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:call-template name="computeFirst">
            <xsl:with-param name="mask" select="$mask"/>
            <xsl:with-param name="currentPos" select="$currentPos+1"/>
          </xsl:call-template>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>



</xsl:stylesheet>
