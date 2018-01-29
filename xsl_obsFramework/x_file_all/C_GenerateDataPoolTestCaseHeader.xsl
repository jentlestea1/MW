<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2003 P&P Software GmbH                               -->
<!--================================================================-->

<!--===================================================================
Generator meta-component for the test case for a data pool class
of the OBS Framework. 
          
This XSL program generates the header file of the data pool
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

  <xsl:variable name="TestCaseClassName" select="concat('TestCase',substring($ClassName,4,string-length($ClassName)),'_1')"/>

  <xsl:variable name="TargetFile" select="concat('/home/wangshaobo/obs_xml_xsl/projects_c/RegressionTest/',$TestCaseClassName)"/>     
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
<!--===================================================================
      Start Code Generation      
==================================================================-->  
//
// Copyright 2003 P&amp;P Software GmbH - All Rights Reserved
//
// <xsl:value-of select="$TestCaseClassName"/>.h
//
// This is an automatically generated file

#ifndef <xsl:value-of select="$TestCaseClassName"/>_H
#define <xsl:value-of select="$TestCaseClassName"/>_H

#include "<xsl:value-of select="$CodeDir"/>Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"

/**
 * Check the functionalities implemented by the
 * &lt;code&gt;<xsl:value-of select="$ClassName"/>&lt;/code&gt; component.
 * An instance of the component is created and the following
 * specific checks are performed upon it: &lt;ol&gt;
 * &lt;li&gt;It is verified that the class ID of the component has the correct value.&lt;/li&gt; <xsl:text/>
<xsl:if test="(MonitoringProfile) or (RecoveryAction) or (TimeStamp)">
 * &lt;li&gt;It is verified that, after instantiation, the configuration service
 * of the component reports "not configured".&lt;/li&gt;
 * &lt;li&gt;The data pool is configured and it is verified that the configuration service
 * reports "configured".&lt;/li&gt; <xsl:text/>
</xsl:if>
<xsl:if test="(ValidityStatus)">
 * &lt;li&gt;It is verified that the default value of the validity status is "valid".&lt;/li&gt;<xsl:text/>
</xsl:if>
 * &lt;li&gt;A float value is set and then read and it is verified that the value that is read
 * back is the same as the value that was written.&lt;/li&gt;
 * &lt;li&gt;An integer value is set and then read and it is verified that the value that is read
 * back is the same as the value that was written.&lt;/li&gt;
 * &lt;li&gt;A float value is set and then its pointer is read and it is verified that the value that
 * was written can be correctly read from the pointer.&lt;/li&gt;
 * &lt;li&gt;An integer value is set and then its pointer is read and it is verified that the value that
 * was written can be correctly read from the pointer.&lt;/li&gt; <xsl:text/>
<xsl:if test="(TimeStamp)">
 * &lt;li&gt;An OBS Clock is loaded into the data pool and the correctness of the load operation
 * is checked.&lt;/li&gt; <xsl:text/>
 * &lt;li&gt;The time stamp of a newly set data pool item is checked.&lt;/li&gt; <xsl:text/>
</xsl:if>
<xsl:if test="(ValidityStatus)">
 * &lt;li&gt;The validity status of a data pool item is changed and it is checked that this
 * change is reflected in the validity status read back from the data pool.&lt;/li&gt; 
 * &lt;li&gt;Non-nominal behaviour check: an attempt is made to set the validity status of a 
 * non-existent data pool item and it is checked that the correct event is generated.&lt;/li&gt; 
 * &lt;li&gt;A call to method &lt;code&gt;reset&lt;/code&gt; is performed and it is verified that 
 * a validity status previously set to "not valid" is reset to "valid".&lt;/li&gt; <xsl:text/>
</xsl:if>
<xsl:if test="(BackUpValue)">
 * &lt;li&gt;The validity status of a data pool item is switched to "not valid", its value is set and
 * then read back and it is verified that the value that is read back is the "back up value" (i.e. the
 * value of the data pool item before its validity status was changed. <xsl:text/>
 <xsl:if test="(DataItem)">
 * The data pool item value is read back both through the value getter method and through the
 * data item associated to the data pool item. &lt;/li&gt; <xsl:text/>
 </xsl:if>
 * &lt;li&gt;The validity status of the data pool item is switched back to "valid", its value is set and
 * then read back and it is verified that the value that is read back is the "primary value" (i.e. the
 * last value of the data pool item to be set with the setter method.&lt;/li&gt; <xsl:text/>
 <xsl:if test="(DataItem)">
 * The data pool item value is read back both through the value getter method and through the
 * data item associated to the data pool item. &lt;/li&gt; <xsl:text/>
 </xsl:if>
</xsl:if>
<xsl:if test="(TypeChecking)">
 * &lt;li&gt;The type checking service is checked both for real-valued and for integer-valued
 * data pool items.&lt;/li&gt; <xsl:text/>
</xsl:if>
<xsl:if test="(MonitoringProfile)">
 * &lt;li&gt;A monitoring profile attribute is set and then read back and it is checked that the read-back
 * value is correct.&lt;/li&gt; <xsl:text/>
</xsl:if>
<xsl:if test="(RecoveryAction)">
 * &lt;li&gt;A recovery action attribute is set and then read back and it is checked that the read-back
 * value is correct.&lt;/li&gt; <xsl:text/>
</xsl:if>
<xsl:if test="not(RobustnessLevel/Low)">
 * &lt;li&gt;Non-nominal behaviour check: it is checked that a call to a setter method with an illegal
 * data pool item identifier results in the generation of an "illegal datapool access" event 
 * report. &lt;/li&gt;
 * &lt;li&gt;Non-nominal behaviour check: it is checked that a call to a setter method with an illegal
 * data pool item type results in the generation of an "illegal datapool access" event 
 * report. &lt;/li&gt;
 * &lt;li&gt;Non-nominal behaviour check: it is checked that a call to a pointer getter method with an illegal
 * parameter identifier results in the generation of an "illegal data pool access" event 
 * report. &lt;/li&gt;
 * &lt;li&gt;Non-nominal behaviour check: it is checked that a call to a pointer getter method with an illegal
 * parameter type results in the generation of an "illegal data pool access" event 
 * report. &lt;/li&gt;<xsl:text/>
 <xsl:if test="MonitoringProfile">
 * &lt;li&gt;Non-nominal behaviour check: it is checked that a call to a setter method for a
 * monitoring profile with an illegal parameter identifier results in the generation of an 
 * "illegal data pool access" event report. &lt;/li&gt;<xsl:text/>
 </xsl:if>
 <xsl:if test="RecoveryAction">
 * &lt;li&gt;Non-nominal behaviour check: it is checked that a call to a setter method for a
 * recovery action with an illegal parameter identifier results in the generation of an 
 * "illegal data pool access" event report. &lt;/li&gt;<xsl:text/>
 </xsl:if>
</xsl:if>
<xsl:if test="RobustnessLevel/High">
 * &lt;li&gt;Non-nominal behaviour check: it is checked that a call to a type checking method with an illegal
 * parameter identifier results in the generation of "illegal data pool access" event 
 * report. &lt;/li&gt;<xsl:text/>
 * &lt;li&gt;Non-nominal behaviour check: it is checked that a call to a getter method with an illegal
 * parameter identifier results in the generation of "illegal data pool access" event 
 * report. &lt;/li&gt;<xsl:text/>
 <xsl:if test="DataItem">
 * &lt;li&gt;Non-nominal behaviour check: it is checked that a call to a data item getter method with an 
 * illegal parameter identifier results in the generation of an "illegal data pool access" event 
 * report. &lt;/li&gt;<xsl:text/>
 </xsl:if>
 <xsl:if test="TimeStamp">
 * &lt;li&gt;Non-nominal behaviour check: it is checked that a call to a time stamp getter method with an 
 * illegal parameter identifier results in the generation of an "illegal data pool access" event 
 * report. &lt;/li&gt;<xsl:text/>
 </xsl:if>
 <xsl:if test="ValidityStatus">
 * &lt;li&gt;Non-nominal behaviour check: it is checked that a call to a validity status getter method with an 
 * illegal parameter identifier results in the generation of an "illegal data pool access" event 
 * report. &lt;/li&gt;<xsl:text/>
 </xsl:if>
</xsl:if>
 * &lt;/ol&gt;
 * The code for this test class - like the code for the component it checks -
 * is automatically generated by an XSLT program. The XSLT program takes as an input an
 * XML file (the 'Data Pool Descriptor File') that describes the structure
 * of the data pool in the component being tested.
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


#endif
</xsl:document>
</xsl:template>

</xsl:stylesheet>
