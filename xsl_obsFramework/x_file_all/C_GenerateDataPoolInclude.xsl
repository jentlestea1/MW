<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2003 P&P Software GmbH                               -->
<!--================================================================-->

<!--===================================================================
This is the code generator for an "#include" file that defines the 
identifiers for the items in a data pool. The include file generated 
by this code generator should be included by all classes that wish to 
have access to the items in the data pool by using symbolic names for 
the identifier.

This XSL program process an XML file that describes the data pool. 

NB: This program writes its output to documents that are 
opened using the "xsl:document" instruction. The directory where these files
are written must apparently be specified through an absolute path names (this
seems to be in contrast with the documentation of xsl:document and may be a
bug in the XSLT processor). This directory is hardcoded in variable
$TargetFile.
===================================================================-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    version="1.1"  xmlns:lxslt="http://xml.apache.org/xslt">

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
            
  Generating code for class <xsl:value-of select="$ClassName"/> in files <xsl:value-of select="$TargetFile"/>_inc.h

  <!-- Check whether writing to an output file is possible -->
  <xsl:if test="not(element-available('xsl:document'))">
        FATAL ERROR: the xsl:document element is not supported. Header files cannot be written! This element
        is normally supported only in version 1.1 of XSL.
  </xsl:if>
            
  <!-- ===================================================================================
         Create the output file  
          ===================================================================================-->
  <xsl:document href="{$TargetFile}_inc.h" omit-xml-declaration="yes" method="text">  
<!--===================================================================
      Start Code Generation      
==================================================================-->  
//
// Copyright 2003 P&amp;P Software GmbH - All Rights Reserved
//
// <xsl:value-of select="$ClassName"/>_inc.h
//
// This an automatically generated file
//

/**
 * @file <xsl:value-of select="$ClassName"/>_inc.h 
 * This file defines symbolic names for the identifiers of the items in the
 * data pool defined in class &lt;code&gt;<xsl:value-of select="$ClassName"/>&lt;/code&gt;.
 * The symbolic names are obtained by capitalizing the name of the data pool items
 * as given in the XML data pool descriptor file and adding the prefix
 * "DP_" to it.
 * Classes that wish to use symbolic names to access the items in the data pool
 * should include this file. 
 * This file was generated automatically by an XSLT program that processes the 
 * XML data pool descriptor file.
 * @see <xsl:value-of select="$ClassName"/>
 */

#ifndef <xsl:value-of select="$ClassName"/>_inc_H
#define <xsl:value-of select="$ClassName"/>_inc_H

#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/BasicTypes.h"

<xsl:for-each select="DataPoolItem">
  <xsl:variable name="CapName" select="translate(
          Name/@value,'abcdefghijlmnopqrstuvywz','ABCDEFGHIJLMNOPQRSTUVYWZ')"/>
const TD_DatabaseId DP_<xsl:value-of select="$CapName"/> = <xsl:value-of 
          select="Id/@value"/>;<xsl:text/>
</xsl:for-each>

#endif
</xsl:document>
</xsl:template>


</xsl:stylesheet>
