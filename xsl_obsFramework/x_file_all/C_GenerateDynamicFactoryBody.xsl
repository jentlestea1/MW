<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2003 P&P Software GmbH                               -->
<!--================================================================-->

<!--===================================================================
Generator meta-component for a dynamic factory class for the OBS Framework.

This XSL program generates the body file of the dynamic factory class.

This XSL program process the XML-based application model.

NB: This program writes its outputs to documents that are 
opened using the "xsl:document" instruction. The directory where these files
are written must apparently be specified through an absolute path names (this
seems to be in contrast with the documentation of xsl:document and may be a
bug in the XSLT provessor). This directory is hardcoded in variable
$TargetFile. One output document is opened for each dynamic factory covered by
this XSL program.
===================================================================-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    version="1.1"  xmlns:lxslt="http://xml.apache.org/xslt"
    xmlns:exslt="http://exslt.org/common">

<xsl:strip-space elements="*"/>
<xsl:output omit-xml-declaration="yes" method="text"/>

<!--
       Include general utility rules
-->
<xsl:include href="WriteCommentBody.xsl"/>
<xsl:include href="ClassNameFromPath.xsl"/>
<xsl:include href="TruncatedClassNameFromPath.xsl"/>
<xsl:include href="TypeNameFromPath.xsl"/>
<!--
      Define global variables
-->
<xsl:variable name="codeDir" select="'../'"/>
<!--
      Top-level rule 
-->
<xsl:template match="/ObsApplication">

      <!-- Extract the information reelvant to the generation of the manoeuvre dynamic factory and store it in a tree variable -->
      <xsl:if test="//Manoeuvre">
            <xsl:variable name="temp">
               <xsl:for-each select="//ManoeuvreManagement/Manoeuvre">
                  <xsl:element name="Manoeuvre">
                        <xsl:attribute name="type">
                              <xsl:value-of select=".//*[(@kind='component') and (@type)]/@type"/>
                        </xsl:attribute>
                        <xsl:for-each select=".//*[(@kind='property') and (@type='int') and (@name)]">  
                               <xsl:element name="Property"><xsl:value-of select="@name"/></xsl:element>
                        </xsl:for-each>
                  </xsl:element>
               </xsl:for-each>
            </xsl:variable>
            
            <xsl:variable name="sortedManoeuvres">
                  <xsl:for-each select="exslt:node-set($temp)/Manoeuvre">
                        <xsl:sort select="@type"/>
                        <xsl:copy-of select="."/>
                  </xsl:for-each>
            </xsl:variable>
            
            The following manoeuvre types with their configuration parameters are processed:
            <xsl:for-each select="exslt:node-set($sortedManoeuvres)/Manoeuvre">
                  TC Type: <xsl:value-of select="@type"/>
                     Config. Properties: <xsl:for-each select="Property"><xsl:value-of select="."/><xsl:text>  </xsl:text></xsl:for-each>
            </xsl:for-each>

            <xsl:variable name="TargetFile" select="'/home/wangshaobo/obs_xml_xsl/projects_c/Manoeuvre/CC_ManoeuvreFactory'"/>     
            Generating code for class CC_ManoeuvreFactory in file <xsl:value-of select="$TargetFile"/>.c
            <xsl:document href="{$TargetFile}.c" omit-xml-declaration="yes" method="text">  
               <xsl:call-template name="GenerateCode">
                  <xsl:with-param name="ClassName" select="'CC_ManoeuvreFactory'"/>
                  <xsl:with-param name="classId" select="'ID_MANOEUVREFACTORY'"/>
                  <xsl:with-param name="containedType" select="'Manoeuvre'"/>
                  <xsl:with-param name="nodes" select="exslt:node-set($sortedManoeuvres)/Manoeuvre"/>
               </xsl:call-template>
            </xsl:document>
      </xsl:if>

      <!-- Extract the information relevant to the generation of the telecommand dynamic factory and store it in a tree variable -->
      <xsl:if test="(//Telecommand) or (//PUSTelecommand)">
            <xsl:variable name="temp">
               <xsl:for-each select="//*[(@kind='interface') and ((@type='Telecommand/Telecommand') or (@type='Telecommand/PUSTelecommand'))]">
                  <xsl:element name="Telecommand">
                        <xsl:attribute name="type">
                              <xsl:value-of select=".//*[(@kind='component') and (@type)]/@type"/>
                        </xsl:attribute>
                        <xsl:for-each select=".//*[(@kind='property') and (@type='int') and (@name)]">  
                               <xsl:element name="Property"><xsl:value-of select="@name"/></xsl:element>
                        </xsl:for-each>
                  </xsl:element>
               </xsl:for-each>
            </xsl:variable>
            
            <xsl:variable name="sortedTelecommands">
                  <xsl:for-each select="exslt:node-set($temp)/Telecommand">
                        <xsl:sort select="@type"/>
                        <xsl:copy-of select="."/>
                  </xsl:for-each>
            </xsl:variable>
            
            The following telecommand types with their configuration parameters are processed:
            <xsl:for-each select="exslt:node-set($sortedTelecommands)/Telecommand">
                  TC Type: <xsl:value-of select="@type"/>
                     Config. Properties: <xsl:for-each select="Property"><xsl:value-of select="."/><xsl:text>  </xsl:text></xsl:for-each>
            </xsl:for-each>

            <xsl:variable name="TargetFile" select="'/home/wangshaobo/obs_xml_xsl/projects_c/Telecommand/CC_TelecommandFactory'"/>     
            Generating code for class CC_TelecommandFactory in file <xsl:value-of select="$TargetFile"/>.c
            <xsl:document href="{$TargetFile}.c" omit-xml-declaration="yes" method="text">  
               <xsl:call-template name="GenerateCode">
                  <xsl:with-param name="ClassName" select="'CC_TelecommandFactory'"/>
                  <xsl:with-param name="classId" select="'ID_TELECOMMANDFACTORY'"/>
                  <xsl:with-param name="containedType" select="'Telecommand'"/>
                  <xsl:with-param name="nodes" select="exslt:node-set($sortedTelecommands)/Telecommand"/>
               </xsl:call-template>
            </xsl:document>
      </xsl:if>

       <!-- Extract the information relevant to the generation of the telemetry packet dynamic factory and store it in a tree variable -->
      <xsl:if test="(//StandardTelemetryPacket) or (//PUSTelemetryPacket)">
            <xsl:variable name="temp">
               <xsl:for-each select="//*[(@kind='interface') and ((@type='Telemetry/StandardTelemetryPacket') or (@type='Telemetry/PUSTelemetryPacket'))]">
                  <xsl:element name="TelemetryPacket">
                        <xsl:attribute name="type">
                              <xsl:value-of select=".//*[(@kind='component') and (@type)]/@type"/>
                        </xsl:attribute>
                        <xsl:for-each select=".//*[(@kind='property') and (@type='int') and (@name)]">  
                               <xsl:element name="Property"><xsl:value-of select="@name"/></xsl:element>
                        </xsl:for-each>
                  </xsl:element>
               </xsl:for-each>
            </xsl:variable>
            
            <xsl:variable name="sortedTelemetryPackets">
                  <xsl:for-each select="exslt:node-set($temp)/TelemetryPacket">
                        <xsl:sort select="@type"/>
                        <xsl:copy-of select="."/>
                  </xsl:for-each>
            </xsl:variable>
            
            The following telemetry packet types with their configuration parameters are processed:
            <xsl:for-each select="exslt:node-set($sortedTelemetryPackets)/TelemetryPacket">
                  TC Type: <xsl:value-of select="@type"/>
                     Config. Properties: <xsl:for-each select="Property"><xsl:value-of select="."/><xsl:text>  </xsl:text></xsl:for-each>
            </xsl:for-each>
            
            <xsl:variable name="TargetFile" select="'/home/wangshaobo/obs_xml_xsl/projects_c/Telemetry/CC_TelemetryPacketFactory'"/>     
            Generating code for class CC_TelemetryPacketFactory in file <xsl:value-of select="$TargetFile"/>.c
            <xsl:document href="{$TargetFile}.c" omit-xml-declaration="yes" method="text">  
               <xsl:call-template name="GenerateCode">
                  <xsl:with-param name="ClassName" select="'CC_TelemetryPacketFactory'"/>
                  <xsl:with-param name="classId" select="'ID_TELECOMMANDFACTORY'"/>
                  <xsl:with-param name="containedType" select="'TelemetryPacket'"/>
                  <xsl:with-param name="nodes" select="exslt:node-set($sortedTelemetryPackets)/TelemetryPacket"/>
               </xsl:call-template>
            </xsl:document>
      </xsl:if>


</xsl:template>

<xsl:template name="GenerateCode">
  <xsl:param name="ClassName"/>
  <xsl:param name="classId"/>
  <xsl:param name="containedType"/>
  <xsl:param name="nodes"/>
  <xsl:variable name="LowerCase" select="'abcdefghijklmnopqrstuvwxyz'"/>
  <xsl:variable name="UpperCase" select="'ABCDEFGHIJKLMNOPQRSTUVWXYZ'"/>
//
// Copyright 2003 P&amp;P Software GmbH - All Rights Reserved
//
// <xsl:value-of select="$ClassName"/>.c
//
// This file was automatically generated by an XSL program
//

#include "<xsl:value-of select="$codeDir"/>GeneralInclude/CompilerSwitches.h"
#include "<xsl:value-of select="$codeDir"/>GeneralInclude/DebugSupport.h"
#include "<xsl:value-of select="$codeDir"/>GeneralInclude/BasicTypes.h"
#include "<xsl:value-of select="$codeDir"/>GeneralInclude/ClassId.h"
#include "<xsl:value-of select="$codeDir"/>GeneralInclude/Constants.h"  <xsl:text/>
<xsl:for-each select="exslt:node-set($nodes)">
   <xsl:variable name="clsName" select="@type"/>
   <xsl:variable name="pos" select="position()"/>
   <xsl:if test="($pos=1) or (exslt:node-set($nodes)[position()=(($pos)-1)]/@type!=$clsName)">
#include "<xsl:value-of select="$codeDir"/><xsl:value-of select="$clsName"/>.h"  <xsl:text/>
    </xsl:if>
</xsl:for-each>
#include "<xsl:value-of select="$codeDir"/>Base/CC_RootObject.h"
#include "<xsl:value-of select="$ClassName"/>.h"

<!--
<xsl:value-of select="$ClassName"/>* <xsl:value-of select="$ClassName"/>::pInstance = pNULL;

<xsl:value-of select="$ClassName"/>::<xsl:value-of select="$ClassName"/>(void) {
    setClassId(<xsl:value-of select="$classId"/>);

  <xsl:for-each select="exslt:node-set($nodes)">
      <xsl:variable name="clsName" select="@type"/>
      <xsl:variable name="tClsName">
            <xsl:call-template name="TruncatedClassNameFromPath">
                  <xsl:with-param  name="path" select="$clsName"/>
            </xsl:call-template>
      </xsl:variable>
      <xsl:variable name="uClsName">
         <xsl:call-template name="ClassNameFromPath">
               <xsl:with-param name="path" select="$clsName"/>
         </xsl:call-template>
      </xsl:variable>
       <xsl:variable name="pos" select="position()"/>
      <xsl:if test="($pos=1) or (exslt:node-set($nodes)[position()=(($pos)-1)]/@type!=$clsName)">
    size<xsl:value-of select="$tClsName"/> = <xsl:value-of select="count(exslt:node-set($nodes)[@type=$clsName])"/>;
    pool<xsl:value-of select="$tClsName"/> = new <xsl:value-of
        select="$uClsName"/>*[size<xsl:value-of select="$tClsName"/>];
    for (unsigned int i=0; i&lt;size<xsl:value-of select="$tClsName"/>; i++)
        pool<xsl:value-of select="$tClsName"/>[i] = pNULL;
      </xsl:if>
  </xsl:for-each>
}

bool <xsl:value-of select="$className"/>::isObjectConfigured(void) {

    if ( !CC_RootObject::isObjectConfigured() )
        return false;
  <xsl:for-each select="exslt:node-set($nodes)">
      <xsl:variable name="clsName" select="@type"/>
      <xsl:variable name="tClsName">
            <xsl:call-template name="TruncatedClassNameFromPath">
                  <xsl:with-param  name="path" select="$clsName"/>
            </xsl:call-template>
      </xsl:variable>
      <xsl:variable name="uClsName">
         <xsl:call-template name="ClassNameFromPath">
               <xsl:with-param name="path" select="$clsName"/>
         </xsl:call-template>
      </xsl:variable>
      <xsl:variable name="pos" select="position()"/>
      <xsl:if test="($pos=1) or (exslt:node-set($nodes)[position()=(($pos)-1)]/@type!=$clsName)">
    if ( pool<xsl:value-of select="$tClsName"/>==pNULL )
        return false;

    for (unsigned int i=0; i&lt;size<xsl:value-of select="$tClsName"/>; i++)
        if ( pool<xsl:value-of select="$tClsName"/>[i]==pNULL )
            return false;
     </xsl:if>
  </xsl:for-each>

   return true;
}

<xsl:value-of select="$className"/>* <xsl:value-of select="$className"/>::getInstance(void) {
    if (pInstance==pNULL)
        pInstance = new <xsl:value-of select="$className"/>();
    return pInstance;
}

  <xsl:for-each select="exslt:node-set($nodes)">
      <xsl:variable name="clsName" select="@type"/>
      <xsl:variable name="tClsName">
            <xsl:call-template name="TruncatedClassNameFromPath">
                  <xsl:with-param  name="path" select="$clsName"/>
            </xsl:call-template>
      </xsl:variable>
      <xsl:variable name="uClsName">
         <xsl:call-template name="ClassNameFromPath">
               <xsl:with-param name="path" select="$clsName"/>
         </xsl:call-template>
      </xsl:variable>
    <xsl:variable name="pos" select="position()"/>
    <xsl:if test="($pos=1) or (exslt:node-set($nodes)[position()=(($pos)-1)]/@type!=$clsName)">
void <xsl:value-of select="$className"/>::set<xsl:value-of
                    select="$containedType"/>(unsigned int i, <xsl:value-of select="$uClsName"/>* pItem) {
    assert(i&lt;size<xsl:value-of select="$tClsName"/>);
    assert(pItem!=pNULL);
    pool<xsl:value-of select="$tClsName"/>[i] = pItem;
    pool<xsl:value-of select="$tClsName"/>[i]->setInUse(false);
}

unsigned int <xsl:value-of select="$className"/>::getNumber<xsl:value-of select="$tClsName"/>(void) {
    unsigned int counter = 0;
    for (unsigned int i=0; i&lt;size<xsl:value-of select="$tClsName"/>; i++)
        if ( pool<xsl:value-of select="$tClsName"/>[i]->isInUse() )
            counter++;
    return counter;
}

unsigned int <xsl:value-of select="$className"/>::getCapacity<xsl:value-of select="$tClsName"/>(void) {
    return size<xsl:value-of select="$tClsName"/>;
}


<xsl:value-of select="$uClsName"/>* <xsl:value-of
                        select="$className"/>::allocate<xsl:value-of select="$tClsName"/>(<xsl:for-each select="Property">unsigned int <xsl:if test="not(position()=last())">
          <xsl:value-of select="."/>, </xsl:if><xsl:if test="position()=last()"><xsl:value-of select="."/></xsl:if></xsl:for-each>) {
    assert( isObjectConfigured() );
    for (unsigned int i=0; i&lt;size<xsl:value-of select="$tClsName"/>; i++)
        if (<xsl:for-each select="Property">pool<xsl:value-of select="$tClsName"/>[i]->get<xsl:value-of select="."/>()>=<xsl:value-of select="."/> &amp;&amp;
             </xsl:for-each>!pool<xsl:value-of select="$tClsName"/>[i]->isInUse() ) {
           pool<xsl:value-of select="$tClsName"/>[i]->setInUse(true);
           return pool<xsl:value-of select="$tClsName"/>[i];
        }
    return pNULL;
}

bool <xsl:value-of select="$className"/>::isFree<xsl:value-of select="$tClsName"/>(<xsl:for-each select="Property">unsigned int <xsl:if test="not(position()=last())">
          <xsl:value-of select="."/>, </xsl:if><xsl:if test="position()=last()"><xsl:value-of select="."/></xsl:if></xsl:for-each>) {
    for (unsigned int i=0; i&lt;size<xsl:value-of select="$tClsName"/>; i++)
        if ( <xsl:for-each select="Property">pool<xsl:value-of select="$tClsName"/>[i]->get<xsl:value-of select="."/>()>=<xsl:value-of select="."/> &amp;&amp;
             </xsl:for-each>!pool<xsl:value-of select="$tClsName"/>[i]->isInUse() )
           return true;

    return false;
}

            <xsl:if test="$uClsName='DC_PUSDataReportingPacket'">
<xsl:value-of select="$uClsName"/>* <xsl:value-of select="$className"/>::get<xsl:value-of
                                                                select="$tClsName"/>(TD_SID sid) {
    assert( isObjectConfigured() );
    assert( sid>0 );

    for (unsigned int i=0; i&lt;size<xsl:value-of select="$tClsName"/>; i++)
        if ( ( pool<xsl:value-of select="$tClsName"/>[i]->getSID() == sid ) &amp;&amp;
             ( pool<xsl:value-of select="$tClsName"/>[i]->isInUse() ) ) {
            return pool<xsl:value-of select="$tClsName"/>[i];
         }
    return pNULL;
}
            </xsl:if>

     </xsl:if>
   </xsl:for-each>
-->
///////////////////////////////////////////////////////////////////////////////
//
//                            class data
//
///////////////////////////////////////////////////////////////////////////////


static <xsl:value-of select="$ClassName"/>* pInstance=pNULL;     


///////////////////////////////////////////////////////////////////////////////
//
//                            class  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////


<xsl:value-of select="$ClassName"/>* <xsl:value-of select="$ClassName"/>_getInstance(void) {
    if (pInstance==pNULL)
        pInstance = <xsl:value-of select="$ClassName"/>_new();
    return pInstance;
}

///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////


  <xsl:for-each select="exslt:node-set($nodes)">
      <xsl:variable name="clsName" select="@type"/>
      <xsl:variable name="tClsName">
            <xsl:call-template name="TruncatedClassNameFromPath">
                  <xsl:with-param  name="path" select="$clsName"/>
            </xsl:call-template>
      </xsl:variable>
      <xsl:variable name="uClsName">
         <xsl:call-template name="ClassNameFromPath">
               <xsl:with-param name="path" select="$clsName"/>
         </xsl:call-template>
      </xsl:variable>
    <xsl:variable name="pos" select="position()"/>
    <xsl:if test="($pos=1) or (exslt:node-set($nodes)[position()=(($pos)-1)]/@type!=$clsName)">
void <xsl:value-of select="$ClassName"/>_set<xsl:value-of
    select="$containedType"/>(<xsl:value-of select="$ClassName"/> *this,unsigned int i, <xsl:value-of select="$uClsName"/>* pItem) {
    assert(i&lt;this->size<xsl:value-of select="$tClsName"/>);
    assert(pItem!=pNULL);
    
    this->pool<xsl:value-of select="$tClsName"/>[i] = pItem;
    <xsl:value-of select="translate(concat('DC_',$tClsName),$LowerCase,$UpperCase)"/>_GET_CLASS(this->pool<xsl:value-of select="$tClsName"/>[i])->setInUse(false);
}

unsigned int <xsl:value-of select="$ClassName"/>_getNumber<xsl:value-of select="$tClsName"/>(<xsl:value-of select="$ClassName"/> *this) {
    unsigned int counter = 0;
    for (unsigned int i=0; i&lt;size<xsl:value-of select="$tClsName"/>; i++)
        if ( <xsl:value-of select="translate(concat('DC_',$tClsName),$LowerCase,$UpperCase)"/>_GET_CLASS(this->pool<xsl:value-of select="$tClsName"/>[i])->isInUse() )
            counter++;
    return counter;
}

unsigned int <xsl:value-of select="$ClassName"/>_getCapacity<xsl:value-of select="$tClsName"/>(<xsl:value-of select="$ClassName"/> *this) {
    return this->size<xsl:value-of select="$tClsName"/>;
}
<xsl:value-of select="$uClsName"/>* <xsl:value-of
    select="$ClassName"/>_allocate<xsl:value-of select="$tClsName"/>(<xsl:value-of select="$ClassName"/> *this, <xsl:for-each select="Property">unsigned int <xsl:if test="not(position()=last())">
          <xsl:value-of select="."/>, </xsl:if><xsl:if test="position()=last()"><xsl:value-of select="."/></xsl:if></xsl:for-each>) {
    assert( this->isObjectConfigured() );
    for (unsigned int i=0; i&lt;this->size<xsl:value-of select="$tClsName"/>; i++)
    if (<xsl:for-each select="Property"><xsl:value-of select="translate(concat('DC_',$tClsName),$LowerCase,$UpperCase)"/>_GET_CLASS((this->pool<xsl:value-of select="$tClsName"/>[i]))->get<xsl:value-of select="."/>()>=<xsl:value-of select="."/> &amp;&amp;
    </xsl:for-each>!<xsl:value-of select="translate(concat('DC_',$tClsName),$LowerCase,$UpperCase)"/>_GET_CLASS(this->pool<xsl:value-of select="$tClsName"/>[i])->isInUse() ) { //这里C_GenerateDynamicFactoryBody.xsl是不是存在问题
        <xsl:value-of select="translate(concat('DC_',$tClsName),$LowerCase,$UpperCase)"/>_GET_CLASS(this->pool<xsl:value-of select="$tClsName"/>[i])->setInUse(true);
           return this->pool<xsl:value-of select="$tClsName"/>[i];
        }
    return pNULL;
}

bool <xsl:value-of select="$ClassName"/>_isFree<xsl:value-of select="$tClsName"/>(<xsl:value-of select="ClassName"/> *this, <xsl:for-each select="Property">unsigned int <xsl:if test="not(position()=last())">
          <xsl:value-of select="."/>, </xsl:if><xsl:if test="position()=last()"><xsl:value-of select="."/></xsl:if></xsl:for-each>) {
    for (unsigned int i=0; i&lt;size<xsl:value-of select="$tClsName"/>; i++)
        if ( <xsl:for-each select="Property"><xsl:value-of select="translate(concat('DC_',$tClsName),$LowerCase,$UpperCase)"/>_GET_CLASS(this->pool<xsl:value-of select="$tClsName"/>[i])->get<xsl:value-of select="."/>()>=<xsl:value-of select="."/> &amp;&amp;
             </xsl:for-each>!<xsl:value-of select="translate(concat('DC_',$tClsName),$LowerCase,$UpperCase)"/>_GET_CLASS(this->pool<xsl:value-of select="$tClsName"/>[i])->isInUse() )
           return true;

    return false;
}

            <xsl:if test="$uClsName='DC_PUSDataReportingPacket'">
<xsl:value-of select="$uClsName"/>* <xsl:value-of select="$ClassName"/>_get<xsl:value-of
    select="$tClsName"/>(<xsl:value-of select="$ClassName"/> *this, TD_SID sid) {
    assert(this->isObjectConfigured() );
    assert( sid>0 );

    for (unsigned int i=0; i&lt;size<xsl:value-of select="$tClsName"/>; i++)
         if ( ( <xsl:value-of select="translate(concat('DC_',$tClsName),$LowerCase,$UpperCase)"/>_GET_CLASS(this->pool<xsl:value-of select="$tClsName"/>[i])->getSID() == sid ) &amp;&amp;
             (  <xsl:value-of select="translate(concat('DC_',$tClsName),$LowerCase,$UpperCase)"/>_GET_CLASS(this->pool<xsl:value-of select="$tClsName"/>[i])->isInUse() ) ) {
             return this->pool<xsl:value-of select="$tClsName"/>[i];
         }
    return pNULL;
}
        </xsl:if>
     </xsl:if>
   </xsl:for-each>
/////////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
/////////////////////////////////////////////////////////////////////////////////

static bool isObjectConfigured(void* obj) {

  if ( !<xsl:value-of select="translate('CC_RootObject',$LowerCase,$UpperCase)"/>(obj)->isObjectConfigured() )
        return false;
  <xsl:for-each select="exslt:node-set($nodes)">
      <xsl:variable name="clsName" select="@type"/>
      <xsl:variable name="tClsName">
            <xsl:call-template name="TruncatedClassNameFromPath">
                  <xsl:with-param  name="path" select="$clsName"/>
            </xsl:call-template>
      </xsl:variable>
      <xsl:variable name="uClsName">
         <xsl:call-template name="ClassNameFromPath">
               <xsl:with-param name="path" select="$clsName"/>
         </xsl:call-template>
      </xsl:variable>
      <xsl:variable name="pos" select="position()"/>
      <xsl:if test="($pos=1) or (exslt:node-set($nodes)[position()=(($pos)-1)]/@type!=$clsName)">
    if ( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pool<xsl:value-of select="$tClsName"/>==pNULL )
        return false;

    for (unsigned int i=0; i&lt; <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->size<xsl:value-of select="$tClsName"/>; i++)
        if (  <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pool<xsl:value-of select="$tClsName"/>[i]==pNULL )
            return false;
     </xsl:if>
  </xsl:for-each>

   return true;
}
///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////
// the following may be useful if you don't need it, just delete.
// <xsl:value-of select="$ClassName"/> *this = <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)
static void instance_init(Object *obj)
{
   CC_RootObject_setClassId(<xsl:value-of select="$classId"/>);

  <xsl:for-each select="exslt:node-set($nodes)">
      <xsl:variable name="clsName" select="@type"/>
      <xsl:variable name="tClsName">
            <xsl:call-template name="TruncatedClassNameFromPath">
                  <xsl:with-param  name="path" select="$clsName"/>
            </xsl:call-template>
      </xsl:variable>
      <xsl:variable name="uClsName">
         <xsl:call-template name="ClassNameFromPath">
               <xsl:with-param name="path" select="$clsName"/>
         </xsl:call-template>
      </xsl:variable>
       <xsl:variable name="pos" select="position()"/>
      <xsl:if test="($pos=1) or (exslt:node-set($nodes)[position()=(($pos)-1)]/@type!=$clsName)">
     <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->size<xsl:value-of select="$tClsName"/> = <xsl:value-of select="count(exslt:node-set($nodes)[@type=$clsName])"/>;
     <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pool<xsl:value-of select="$tClsName"/> = (<xsl:value-of select="$uClsName"/>**)malloc( <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->size<xsl:value-of select="$tClsName"/>*sizeof(<xsl:value-of select="$uClsName"/>*));
    for (unsigned int i=0; i&lt; <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->size<xsl:value-of select="$tClsName"/>; i++)
        <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj)->pool<xsl:value-of select="$tClsName"/>[i] = pNULL;
      </xsl:if>
  </xsl:for-each>

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

        dc_p_class->isObjectConfigured = isObjectConfigured;

}

static const TypeInfo type_info = {
        .name = TYPE_<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>,
        .parent = TYPE_CC_ROOTOBJECT,
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

</xsl:template>

</xsl:stylesheet>
