<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2003 P&P Software GmbH                               -->
<!--================================================================-->

<!--===================================================================
Generator meta-component for the test case for a stack container class
of the OBS Framework. 
          
This XSLT program generates the header file of the stack container
test case class.

This XSLT program process an XML file that describes the stack container
class. The structure of the XML file is described in the XSLT 
program that generates the header file of the stack container class
(see file GenerateStackContainerHeader.h).
===================================================================-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    version="1.0"
    xmlns:lxslt="http://xml.apache.org/xslt"
    xmlns:redirect="org.apache.xalan.lib.Redirect"
    extension-element-prefixes="redirect">

<xsl:strip-space elements="*"/>
<xsl:output omit-xml-declaration="yes" method="text"/>

<!--================================================================-->
<!-- Top-level rule                                                 -->
<!--================================================================-->

<xsl:template match="/StackContainerDescriptor">
  <xsl:call-template name="GenerateCode"/>
</xsl:template>

<!--================================================================-->
<!-- Code generationg                                               -->
<!--================================================================-->

<xsl:template name="GenerateCode">

  <!-- extract useful variables from XML file                       -->
  <xsl:variable name="ClassName" select="@name"/>
  <xsl:variable name="ClassId" select="@classId"/>
  <xsl:variable name="Level" select="@robustnessLevel"/>
  <xsl:variable name="CodeDir" select="ObsFrameworkCodeDirPath"/>
  <xsl:variable name="LowerCase" select="'abcdefghijklmnopqrstuvwxyz'"/>
  <xsl:variable name="UpperCase" select="'ABCDEFGHIJKLMNOPQRSTUVWXYZ'"/>

  <!-- construct the name of the test case class                   -->
  <xsl:variable name="TestCaseClassName" select="
    concat('TestCase',substring($ClassName,4,string-length($ClassName)),'_1')"/>

  <!-- store the empty string string in variable $emptyString     -->
  <xsl:variable name="emptyString"></xsl:variable>

  <!-- start code generation                                       -->
<xsl:variable name="TargetFile" select="concat('/home/wangshaobo/obs_xml_xsl/projects_c/stack_container/',$TestCaseClassName)"/>
<xsl:document href="{$TargetFile}.h" omit-xml-declaration="yes" method="text">
//
// Copyright 2003 P&amp;P Software GmbH - All Rights Reserved
//
// <xsl:value-of select="$TestCaseClassName"/>.h
//
// Version	1.0
// Date		10.10.03 (Version 1.0)
// Author	A. Pasetti (P&amp;P Software)
//

#ifndef <xsl:value-of select="$TestCaseClassName"/>_H
#define <xsl:value-of select="$TestCaseClassName"/>_H

#include "<xsl:value-of select="$CodeDir"/>Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"

/**
 * Check the functionality of the container class for items of type
 * <xsl:if test="contains(Type,'*')">pointer to </xsl:if>&lt;code&gt;<xsl:value-of select="Type"/>&lt;/code&gt;.
 * One instance of the container class is created and
 * the following specific checks are performed upon it : <ol>
 * <li>The correctness of the class identifier is checked.</li>
 * <li>It is checked that the configuration check service
 * initially reports "not configured".</li>
 * <li>The stack size is set to 2 and it is checked that the set value
 * is correctly reported.</li>
 * <li>It is checked that the configuration check service reports
 * "configured".</li>
 * <li>An item is pushed onto the stack and it is checked that the
 * stack reports "number of items on the stack equals 1".</li>
 * <li>An item is popped from the stack and it is checked that the
 * correct element is returned.</li>
 * <li>A pop operation is performed and it is verified that pNULL
 * is returned and the correct event report is generated.</li>
 * <li>Three items are pushed on the stack and it is verified that
 * only 2 are actually placed on the stack and that the correct event
 * report is generated.</li>
 * <li>It is verified that the stack is full after the second push operation.</li>
 * <li>A reset operation is performed and it is verified that
 * the number of items on the stack is zero and that the stack is
 * empty.</li>
 * </ol>
 * This class was generated automatically by an XSLT program.
 * @see <xsl:value-of select="$ClassName"/>
 * @author Alessandro Pasetti (P&amp;P Software GmbH)
 * @version 1.0
 */
<!-- 
class <xsl:value-of select="$TestCaseClassName"/> : public TestCaseWithEvtCheck {

public :

     /**
      * Set the identifier and the name of the test case to: 
      * <xsl:value-of select="$ClassId"/>*10+1 and "<xsl:value-of select="$TestCaseClassName"/>".
      */
     <xsl:value-of select="$TestCaseClassName"/>();

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase();
};
-->

void <xsl:value-of select="$TestCaseClassName"/>_register(void);


/////////////////////////////////////////////////////////////////////////////////
//
//                              class and struct
//
/////////////////////////////////////////////////////////////////////////////////

struct <xsl:value-of select="$TestCaseClassName"/> {
    TestCaseWithEvtCheck parent;
};


struct <xsl:value-of select="$TestCaseClassName"/>Class {
    TestCaseWithEvtCheckClass parent_class;
    /**
     * Execute the test case. See class comment for details.
     */
    void (*runTestCase)(void* obj);
};


#define <xsl:value-of select="translate($TestCaseClassName,$LowerCase,$UpperCase)"/>_GET_CLASS(obj) \
           OBJECT_GET_CLASS(<xsl:value-of select="$ClassName"/>Class, obj, TYPE_<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>)


#define <xsl:value-of select="translate($TestCaseClassName,$LowerCase,$UpperCase)"/>_CLASS(klass) \
           OBJECT_CLASS_CHECK(<xsl:value-of select="$TestCaseClassName"/>Class, klass, TYPE_<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>)


#define <xsl:value-of select="translate($TestCaseClassName,$LowerCase,$UpperCase)"/>(obj) \
           OBJECT_CHECK(<xsl:value-of select="$TestCaseClassName"/>, obj, TYPE_<xsl:value-of select="translate($TestCaseClassName,$LowerCase,$UpperCase)"/>)


<xsl:value-of select="$TestCaseClassName"/>* <xsl:value-of select="$TestCaseClassName"/>_new(void);
#endif
</xsl:document>
</xsl:template>

</xsl:stylesheet>
