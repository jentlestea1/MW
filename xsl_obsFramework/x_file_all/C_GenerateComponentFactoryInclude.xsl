<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2003 P&P Software GmbH                                                                                  -->
<!--================================================================-->

<!--===================================================================
This is the code generator for an "#include" file that defines the numerical identifiers
for the components created by the application component factory and for their types.

This XSL program processes the XML-based application model. 
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
<xsl:include href="TypeNameFromPath.xsl"/>
<!--
      Top-level rule 
-->
<xsl:template match="/ObsApplication">

<!--
      Define general purpose variables
-->
<xsl:variable name="FileName" select="'CC_ComponentFactory'"/>
<xsl:variable name="CompFactoryClassName" select="'CC_ComponentFactory'"/>
<!--
      Start Code Generation      
-->  
<xsl:variable name="TargetFile" select="'/home/wangshaobo/obs_xml_xsl/projects_c/componentFactory/CC_ComponentFactory'"/>
<xsl:document href="{$TargetFile}_inc.h" omit-xml-declaration="yes" method="text">
//
// Copyright 2004 P&amp;P Software GmbH - All Rights Reserved
//
// <xsl:value-of select="$FileName"/>_inc.h
//
// This an automatically generated file

/**
 * @file <xsl:value-of select="$FileName"/>.h 
 * This file defines symbolic names for the components created by the &lt;li&gt;application component factory&lt;li&gt;.
 * For each component created by the application component factory, a symbolic name is provided. 
 * The symbolic name takes the form of an integer constant. This name should be used as an argument
 * in the getter methods of the application component factory (instance of class &lt;code&gt;<xsl:value-of select="$CompFactoryClassName"/>&lt;/code&gt;).
 * The names of the components are read from the &lt;i&gt;application model&lt;/i&gt;. Their symbolic
 * names are constructed as follows: CI_XXX where "XXX" is the component name read from the application
 * model file.
 * &lt;p&gt;
 * This file also defines the symbolic names for the types of the components returned by the application
 * component factory. The symbolic names of the types take the form of an integer constant. 
 * The symbolic name of the type is formed as follows. If the name of the type is TYPE, then its
 * symbolic name is constructed as follows: TN_TYPE. The symbolic names of the types of the
 * application components should not normally be used by an application. They are provided here for future
 * extensions.
 * &lt;p&gt;
 * Finally, this file defines the forward declarations for all the classes from which application components
 * are instantiated.
 * &lt;p&gt;
 * This file was generated automatically by an XSL program that processes the 
 * XML-based application model.
 * @see <xsl:value-of select="$CompFactoryClassName"/>
 * @author Automatically Generated File
 */

#ifndef <xsl:value-of select="$FileName"/>_inc_H
#define <xsl:value-of select="$FileName"/>_inc_H 
<xsl:for-each select="//*[(@kind='component') and (@name)]">  
      <xsl:variable name="ClassName">
            <xsl:call-template name="ClassNameFromPath">
                  <xsl:with-param name="path" select="@type"/>
            </xsl:call-template>
      </xsl:variable>    
      
  /**  
<xsl:call-template name="WriteCommentBody">
         <xsl:with-param name="text" select="normalize-space(Description)"/>
         <xsl:with-param name="indent" select="'   '"/>
</xsl:call-template>   
   * This component is instantiated from class &lt;code&gt;<xsl:value-of select="$ClassName"/>&lt;/code&gt;.
   * @see <xsl:value-of select="$ClassName"/> 
   */
  const int CI_<xsl:value-of  select="@name"/> = <xsl:value-of  select="position()"/>;
</xsl:for-each>

   // Now define the symbolic names for the types  <xsl:text/>
<!-- 
      Create a temporary variable that holds a sequence of elements named "type" with one element
      for each component type. The name of the type is the value of the element. 
-->
<xsl:variable name="temp">
<xsl:for-each select="//*[(@kind='component') and (@name)]">  
   <xsl:element name="type"><xsl:value-of select="@type"/></xsl:element>
</xsl:for-each>
</xsl:variable>

<xsl:variable name="sortedTemp">
<xsl:for-each select="exslt:node-set($temp)/type">
    <xsl:sort/>
   <xsl:element name="type"><xsl:value-of select="."/></xsl:element>
</xsl:for-each>
</xsl:variable>

<xsl:for-each select="exslt:node-set($sortedTemp)/type">
      <xsl:variable name="value" select="."/>
      <xsl:variable name="count" select="position()"/>
      <xsl:variable name="previousValue" select="../type[position()=number($count)-1]"/>
      <xsl:if test="not($value=$previousValue)">
       <xsl:variable name="TypeName">
            <xsl:call-template name="TypeNameFromPath">
                <xsl:with-param name="path" select="$value"/>
            </xsl:call-template>
       </xsl:variable>
   const int <xsl:value-of select="$TypeName"/> = <xsl:value-of select="position()"/>;  <xsl:text/>
      </xsl:if>
</xsl:for-each>

   // Now define the forward declarations for the types   <xsl:text/>
<xsl:for-each select="exslt:node-set($sortedTemp)/type">
      <xsl:variable name="value" select="."/>
      <xsl:variable name="count" select="position()"/>
      <xsl:variable name="previousValue" select="../type[position()=number($count)-1]"/>
      <xsl:if test="not($value=$previousValue)">
       <xsl:variable name="ClassName">
            <xsl:call-template name="ClassNameFromPath">
                <xsl:with-param name="path" select="$value"/>
            </xsl:call-template>
       </xsl:variable>
   class <xsl:value-of select="$ClassName"/>;  <xsl:text/>
      </xsl:if>
</xsl:for-each>



#endif
</xsl:document>
</xsl:template>


</xsl:stylesheet>
