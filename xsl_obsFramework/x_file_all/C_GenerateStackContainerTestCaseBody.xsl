<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2003 P&P Software GmbH                               -->
<!--================================================================-->

<!--===================================================================
Generator meta-component for the test case for a stack container class
of the OBS Framework.

This XSLT program generates the body file of the stack container
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
<!-- Code generation                                                -->
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
<xsl:variable name="TargetFile" select="concat('/home/wangshaobo/obs_xml_xsl/projects_c/stack_container/',$TestCaseClassName)"/>
<xsl:document href="{$TargetFile}.c" omit-xml-declaration="yes" method="text">

//
// Copyright 2003 P&amp;P Software GmbH - All Rights Reserved
//
// <xsl:value-of select="$TestCaseClassName"/>.c
//
// Version	1.0
// Date		10.09.03 (Version 1.0)
// Author	A. Pasetti (P&amp;P Software)
//

#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/CompilerSwitches.h"
#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/ClassId.h"
#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/Constants.h"
#include "<xsl:value-of select="$CodeDir"/>System/<xsl:value-of select="$ClassName"/>.h"
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
   <xsl:value-of select="$ClassName"/>* pStack = new <xsl:value-of select="$ClassName"/>();
   unsigned int size = 2;
   unsigned int nEvt = getNumberOfEvents();
   <xsl:choose>
     <xsl:when test="contains(Type,'*')">
       <xsl:value-of select="Type"/> pItem1 = new <xsl:value-of select="substring-before(Type,'*')"/>();
     </xsl:when>
     <xsl:otherwise>
       <xsl:value-of select="Type"/> pItem1 = (<xsl:value-of select="Type"/>)1;
     </xsl:otherwise>
   </xsl:choose>
   // Check the value of the class identifier
   if ( pStack->getClassId() != <xsl:value-of select="$ClassId"/> )
   {    setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
   }

   // Check configuration status
   if ( pStack->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Set the stack size
   pStack->setStackSize(size);
   if ( pStack->getStackSize() != size)
   {    setTestResult(TEST_FAILURE, "Wrong stack size value");
        return;
   }

   // Check configuration status
   if ( !pStack->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Push one item on stack and check correctness
   pStack->push(pItem1);
   if ( pStack->getNumberOfItems() != 1 )
   {    setTestResult(TEST_FAILURE, "Wrong number of items on stack");
        return;
   }
   <xsl:choose>
     <xsl:when test="contains(Type,'*')">
   if ( pStack->pop() != pItem1 )
   {    setTestResult(TEST_FAILURE, "Wrong item on stack");
        return;
   } </xsl:when>
     <xsl:otherwise>
   if ( fabs((float)(pStack->pop()-pItem1))>FLT_EPSILON )
   {    setTestResult(TEST_FAILURE, "Wrong item on stack");
        return;
   } </xsl:otherwise>
   </xsl:choose>

   // Check that a pop operation returns pNULL and generates correct event
   if ( pStack->pop() != pNULL )
   {    setTestResult(TEST_FAILURE, "Wrong item on stack");
        return;
   }
   if ( !verifyLatestEvent(nEvt+1,EVT_STACK_EMPTY) )
   {    setTestResult(TEST_FAILURE, "Wrong event");
        return;
   }

   // Perform three push operations and verify event generation
   pStack->push(pItem1);
   pStack->push(pItem1);
   if ( !pStack->isFull() )
   {    setTestResult(TEST_FAILURE, "Stack should be full");
        return;
   }
   pStack->push(pItem1);
   if ( !verifyLatestEvent(nEvt+2,EVT_STACK_FULL) )
   {    setTestResult(TEST_FAILURE, "Wrong event");
        return;
   }

   // Check that there are only two items on the stack
   if ( pStack->getNumberOfItems()!=2 )
   {    setTestResult(TEST_FAILURE, "wrong number of items in stack");
        return;
   }

   // Perform a stack reset and check success
   pStack->reset();
   if ( pStack->getNumberOfItems() != 0 )
   {    setTestResult(TEST_FAILURE, "Reset operation failed");
        return;
   }
   if ( !pStack->isEmpty() )
   {    setTestResult(TEST_FAILURE, "Reset operation failed");
        return;
   }

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
   <xsl:value-of select="$ClassName"/>* pStack = new <xsl:value-of select="$ClassName"/>();
   unsigned int size = 2;
   unsigned int nEvt = getNumberOfEvents();
   <xsl:choose>
     <xsl:when test="contains(Type,'*')">
       <xsl:value-of select="Type"/> pItem1 = new <xsl:value-of select="substring-before(Type,'*')"/>();
     </xsl:when>
     <xsl:otherwise>
       <xsl:value-of select="Type"/> pItem1 = (<xsl:value-of select="Type"/>)1;
     </xsl:otherwise>
   </xsl:choose>
   // Check the value of the class identifier
   if ( pStack->getClassId() != <xsl:value-of select="$ClassId"/> )
   {    setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
   }

   // Check configuration status
   if ( pStack->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Set the stack size
   pStack->setStackSize(size);
   if ( pStack->getStackSize() != size)
   {    setTestResult(TEST_FAILURE, "Wrong stack size value");
        return;
   }

   // Check configuration status
   if ( !pStack->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Push one item on stack and check correctness
   pStack->push(pItem1);
   if ( pStack->getNumberOfItems() != 1 )
   {    setTestResult(TEST_FAILURE, "Wrong number of items on stack");
        return;
   }
   <xsl:choose>
     <xsl:when test="contains(Type,'*')">
   if ( pStack->pop() != pItem1 )
   {    setTestResult(TEST_FAILURE, "Wrong item on stack");
        return;
   } </xsl:when>
     <xsl:otherwise>
   if ( fabs((float)(pStack->pop()-pItem1))>FLT_EPSILON )
   {    setTestResult(TEST_FAILURE, "Wrong item on stack");
        return;
   } </xsl:otherwise>
   </xsl:choose>

   // Check that a pop operation returns pNULL and generates correct event
   if ( pStack->pop() != pNULL )
   {    setTestResult(TEST_FAILURE, "Wrong item on stack");
        return;
   }
   if ( !verifyLatestEvent(nEvt+1,EVT_STACK_EMPTY) )
   {    setTestResult(TEST_FAILURE, "Wrong event");
        return;
   }

   // Perform three push operations and verify event generation
   pStack->push(pItem1);
   pStack->push(pItem1);
   if ( !pStack->isFull() )
   {    setTestResult(TEST_FAILURE, "Stack should be full");
        return;
   }
   pStack->push(pItem1);
   if ( !verifyLatestEvent(nEvt+2,EVT_STACK_FULL) )
   {    setTestResult(TEST_FAILURE, "Wrong event");
        return;
   }

   // Check that there are only two items on the stack
   if ( pStack->getNumberOfItems()!=2 )
   {    setTestResult(TEST_FAILURE, "wrong number of items in stack");
        return;
   }

   // Perform a stack reset and check success
   pStack->reset();
   if ( pStack->getNumberOfItems() != 0 )
   {    setTestResult(TEST_FAILURE, "Reset operation failed");
        return;
   }
   if ( !pStack->isEmpty() )
   {    setTestResult(TEST_FAILURE, "Reset operation failed");
        return;
   }

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



</xsl:stylesheet>
