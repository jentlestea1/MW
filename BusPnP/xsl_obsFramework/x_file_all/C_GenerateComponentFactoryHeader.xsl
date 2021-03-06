<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2004 P&P Software GmbH                                                                                  -->
<!--================================================================-->

<!--===================================================================
This is the code generator for the header file of the application component factory for the 
OBS Framework.

This XSL program process the XML-based application model.
===================================================================-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    version="1.1"  xmlns:lxslt="http://xml.apache.org/xslt"
    xmlns:exslt="http://exslt.org/common">

<xsl:strip-space elements="*"/>
<xsl:output omit-xml-declaration="yes" method="text"/>
<!--
    Global Variables                                                                                                                      
-->
<xsl:variable name="codeDir" select="'../'"/>
<xsl:variable name="className" select="'CC_ComponentFactory'"/>
<xsl:variable name="numberOfComponents" select="count(//*[(@kind='component') and (@name)])"/>
<xsl:variable name="LowerCase" select="'abcdefghijklmnopqrstuvwxyz'"/>
<xsl:variable name="UpperCase" select="'ABCDEFGHIJKLMNOPQRSTUVWXYZ'"/>
<!--
       Include general utility rules
-->
<xsl:include href="WriteCommentBody.xsl"/>
<xsl:include href="ClassNameFromPath.xsl"/>
<xsl:include href="TruncatedClassNameFromPath.xsl"/>
<xsl:include href="TypeNameFromPath.xsl"/>
<!--
    Top-Level Rule                                                 
-->
<xsl:template match="/ObsApplication">
<xsl:variable name="TargetFile" select="'/home/wangshaobo/obs_xml_xsl/projects_c/componentFactory/CC_ComponentFactory'"/>
<xsl:document href="{$TargetFile}.h" omit-xml-declaration="yes" method="text">
// Copyright 2004 P&amp;P Software GmbH - All Rights Reserved
//
// <xsl:value-of select="$className"/>.h
//
// This file was automatically generated by an XSL program

#ifndef <xsl:value-of select="$className"/>_H
#define <xsl:value-of select="$className"/>_H

#include "<xsl:value-of select="$codeDir"/>GeneralInclude/ForwardDeclarations.h"
#include "<xsl:value-of select="$codeDir"/>GeneralInclude/BasicTypes.h"
#include "<xsl:value-of select="$className"/>_inc.h"
#include "<xsl:value-of select="$codeDir"/>Base/CC_RootObject.h"   
#include &lt;assert.h&gt;
#include "../Qom/object.h"
/**
 * Application component factory.
 * This class creates and configures all the components required by the target application and makes
 * them available through getter methods. 
 * The components are created in the constructor and are then stored in an array.
 * A configuration method is provided that will configure all the created components.
 * The components can be accessed by clients exclusively through their pointers.
 * The pointers are returned by getter methods. There is one getter method for each
 * type of components managed by the component factory. The name of the getter
 * methods is of the form: &lt;code&gt;getXXX&lt;/code&gt; where "XXX" is the type name
 * stripped of the initial prefix "DC_" or "CC_". The argument of the getter name is an
 * integer that represents the symbolic identifier of the component (it is an integer that, 
 * from the point of view of external components, acts 
 * as the component name). The symbolic identifiers of the components are stored in
 * the include file &lt;code&gt;<xsl:value-of select="$className"/>_inc.h&lt;/code&gt;. 
 * The getter methods return typed instances of the components. An assertion is used 
 * to verify that the getter method is consistent with the actual type of the component that
 * is being retrieved (i.e. to verify that a component of type "XXX" is retrieved with a call
 * to method &lt;code&gt;getXXX&lt;/code&gt;). There are no other run-time checks
 * on the consistency of usage of the getter methods. This approach is justified because
 * the component factory should normally be used only during the application instantiation
 * phase and the type and order of the calls to the getter methods should be fixed. This
 * allows their correctness to be verified once and for all with assertions enabled.
 * &lt;p&gt;
 * This is a singleton class. Its only instance is accessed through its method 
 * &lt;code&gt;getInstance&lt;/code&gt;.
 * &lt;p&gt;
 * This class is automatically generated by an XSL program that processes the XML-based
 * model of the target application.
 * &lt;p&gt;
 * This class manages a total of <xsl:value-of select="$numberOfComponents"/> components.
 * &lt;p&gt;
 * For reasons of efficiency, all getter methods are declared to be inline. 
 * &lt;p&gt;
 * Implementation note: this class maintains the component references in two distinct location.
 * For each component, a dedicated variable is delcared that holds the pointer to the component.
 * Additionally, an array &lt;code&gt;list&lt;/code&gt; of pointers to the top-level type &lt;code&gt;CC_RootObject&lt;/code&gt;
 * is declared that holds all the pointers to the components. The getter methods retrieve the components
 * from this array. The configuration methods instead use directly the component variables. 
 * Finally, an array of integers is provided that holds the values of the type identifiers for each
 * created component. 
 * @see <xsl:value-of select="$className"/>_inc.h
 * @author Automatically Generated Class
 * @version 1.0
 */
 
 #define TYPE_<xsl:value-of select="$className"/> "<xsl:value-of select="translate($className,$UpperCase,$LowerCase)"/>"
 <!--
class <xsl:value-of select="$className"/> {

  private:
    static <xsl:value-of select="$className"/>* pInstance;     
<xsl:for-each select="//*[(@kind='component') and (@name)]">  
       <xsl:variable name="ClassName">
            <xsl:call-template name="ClassNameFromPath">
                <xsl:with-param name="path" select="@type"/>
            </xsl:call-template>
       </xsl:variable>
    <xsl:text>    </xsl:text><xsl:value-of select="$ClassName"/>* <xsl:value-of select="@name"/>;
</xsl:for-each>    
    CC_RootObject* list[<xsl:value-of select="$numberOfComponents"/>];
    int type[<xsl:value-of select="$numberOfComponents"/>+1];

  protected:
    /**
     * Instantiate the factory component. The components are created and their
     * pointers are stored in an internal array. A second array is initialized that holds
     * the type identifier of each component.
     * This constructor is defined to be protected because this is a singleton
     * class.
     */
    <xsl:value-of select="$className"/>(void);

   /**
     * Configure the static part of the base class &lt;code&gt;CC_RootObject&lt;/code&gt;. This method is called by method 
     * &lt;code&gt;configureApplication&lt;/code&gt;
     */
     void configureRootObject(void);
   
    <xsl:if test="ObsClock">
    /**
     * Configure the component implementing the OBS Clock. This method is called by method 
     * &lt;code&gt;configureApplication&lt;/code&gt;
     */
     void configureObsClock(void);
    </xsl:if>

    <xsl:if test="EventRepository">
    /**
     * Configure the component implementing the event repository. This method is called by method 
     * &lt;code&gt;configureApplication&lt;/code&gt;
     */
     void configureEventRepository (void);
    </xsl:if>

    <xsl:if test="FSM">
    /**
     * Configure the components implementing the applications FSMs. This method configures the
     * FSM, their FsmStates and their FsmEvents. This method is called by method 
     * &lt;code&gt;configureApplication&lt;/code&gt;
     */
     void configureFSM(void);
    </xsl:if>

    <xsl:if test="ControllerManagement">
    /**
     * Configure the components implementing the control actions and control blocks. This method is called by method 
     * &lt;code&gt;configureApplication&lt;/code&gt;
     */
     void configureControllers(void);
    </xsl:if>

    <xsl:if test="DataPool">
    /**
     * Configure the components implementing the application data pool. This method is called by method 
     * &lt;code&gt;configureApplication&lt;/code&gt;
     */
     void configureDataPool(void);
    </xsl:if>

    <xsl:if test="ParameterDatabase">
    /**
     * Configure the components implementing the parameter database. This method is called by method 
     * &lt;code&gt;configureApplication&lt;/code&gt;
     */
     void configureParameterDatabase(void);
    </xsl:if>

    /**
     * Configure the functionality managers. This method is called by method 
     * &lt;code&gt;configureApplication&lt;/code&gt;
     */
     void configureFunctionalityManagers(void);

  public:

    /**
     * Get the single instance of this singleton class. If the instance does not
     * yet exist, it is created.
     */
    static <xsl:value-of select="$className"/>* getInstance(void);

    /**
     * Configure the application. All the components created in the constructor are configured
     * and linked together. The configuration code implements the configuration actions specified
     * in the application model. The application configuration process is broken up into a sequence
     * of steps. To each step a protected method in this class is associated. This method only
     * calls the step methods in sequence. The names of the step methods are formed as
     * follows: &lt;code&gt;configureXXX&lt;/code&gt; where "XXX" is the name of a feature in
     * the application whose configuration is covered by the method.
     */
    void configureApplication(void);


<xsl:variable name="temp">
<xsl:for-each select="//*[(@kind='component') and (@name)]">  
   <xsl:element name="type"><xsl:value-of select="@type"/></xsl:element>
</xsl:for-each>
</xsl:variable>

<xsl:variable name="sortedTemp">
<xsl:for-each select="$temp/type">
    <xsl:sort/>
   <xsl:element name="type"><xsl:value-of select="."/></xsl:element>
</xsl:for-each>
</xsl:variable>

<xsl:for-each select="$sortedTemp/type">
      <xsl:variable name="value" select="."/>
      <xsl:variable name="count" select="position()"/>
      <xsl:variable name="previousValue" select="../type[position()=number($count)-1]"/>
      <xsl:if test="not($value=$previousValue)">
       <xsl:variable name="ClassName">
            <xsl:call-template name="ClassNameFromPath">
                <xsl:with-param name="path" select="$value"/>
            </xsl:call-template>
       </xsl:variable>
       <xsl:variable name="TypeName">
            <xsl:call-template name="TypeNameFromPath">
                <xsl:with-param name="path" select="$value"/>
            </xsl:call-template>
       </xsl:variable>
       <xsl:variable name="TruncatedClassName">
            <xsl:call-template name="TruncatedClassNameFromPath">
                <xsl:with-param name="path" select="$value"/>
            </xsl:call-template>
       </xsl:variable>
   /**
    * Getter method for components of type &lt;code&gt;<xsl:value-of select="$ClassName"/>&lt;/code&gt;.
    * An assertion exception is raised if the component that is sought with this method is not of type
    * &lt;code&gt;<xsl:value-of select="$ClassName"/>&lt;/code&gt;. An assertion exception is likewise raised 
    * if the value of the integer representing the component name is out of range (namely if it is negative
    * or greater than N where N is the total number of components managed by the component factory).
    * @param compName the name of the component as given by its numerical identifier
    * @return the pointer to the component
    */
   inline <xsl:value-of select="$ClassName"/>* get<xsl:value-of select="$TruncatedClassName"/>(int compName) {
       assert( (compName&gt;=1) &amp;&amp; (compName&lt;=<xsl:value-of select="$numberOfComponents"/>) );
       assert( type[compName]==<xsl:value-of select="$TypeName"/>);
       return (<xsl:value-of select="$ClassName"/>*)list[compName];
   }
      </xsl:if>
</xsl:for-each>
};
-->
void <xsl:value-of select="$className"/>_register(void);


/////////////////////////////////////////////////////////////////////////////////
//
//                              class and struct
//
/////////////////////////////////////////////////////////////////////////////////
struct <xsl:value-of select="$className"/> {
    Object parent;
<xsl:for-each select="//*[(@kind='component') and (@name)]">  
       <xsl:variable name="className">
            <xsl:call-template name="ClassNameFromPath">
                <xsl:with-param name="path" select="@type"/>
            </xsl:call-template>
       </xsl:variable>
    <xsl:text>    </xsl:text><xsl:value-of select="$className"/>* <xsl:value-of select="@name"/>;
</xsl:for-each>    
    CC_RootObject* list[<xsl:value-of select="$numberOfComponents"/>];
    int type[<xsl:value-of select="$numberOfComponents"/>+1];
};


struct <xsl:value-of select="$className"/>Class {
    ObjectClass parent_class;
    
};


#define <xsl:value-of select="translate($className,$LowerCase,$UpperCase)"/>_GET_CLASS(obj) \
         OBJECT_GET_CLASS(<xsl:value-of select="$className"/>Class, obj, TYPE_<xsl:value-of select="translate($className,$LowerCase,$UpperCase)"/>)


#define <xsl:value-of select="translate($className,$LowerCase,$UpperCase)"/>_CLASS(klass) \
         OBJECT_CLASS_CHECK(<xsl:value-of select="$className"/>Class, klass, TYPE_<xsl:value-of select="translate($className,$LowerCase,$UpperCase)"/>)


#define <xsl:value-of select="translate($className,$LowerCase,$UpperCase)"/>(obj) \
         OBJECT_CHECK(<xsl:value-of select="$className"/>, obj, TYPE_<xsl:value-of select="translate($className,$LowerCase,$UpperCase)"/>)


<xsl:value-of select="$className"/>* <xsl:value-of select="$className"/>_new(void);
    
///////////////////////////////////////////////////////////////////////////////
//
//                            class method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////


/**
 * Get the single instance of this singleton class. If the instance does not
 * yet exist, it is created.
 */
static <xsl:value-of select="$className"/>* <xsl:value-of select="$className"/>getInstance(void);

///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

   /**
     * Configure the static part of the base class &lt;code&gt;CC_RootObject&lt;/code&gt;. This method is called by method 
     * &lt;code&gt;configureApplication&lt;/code&gt;
     */
    
     
     void <xsl:value-of select="$className"/>_configureRootObject(<xsl:value-of select="$className"/> *this);
   
    <xsl:if test="ObsClock">
    /**
     * Configure the component implementing the OBS Clock. This method is called by method 
     * &lt;code&gt;configureApplication&lt;/code&gt;
     */
     void <xsl:value-of select="$className"/>_configureObsClock(<xsl:value-of select="$className"/> *this);
    </xsl:if>

    <xsl:if test="EventRepository">
    /**
     * Configure the component implementing the event repository. This method is called by method 
     * &lt;code&gt;configureApplication&lt;/code&gt;
     */
     void  <xsl:value-of select="$className"/>_configureEventRepository (<xsl:value-of select="$className"/> *this);
    </xsl:if>

    <xsl:if test="FSM">
    /**
     * Configure the components implementing the applications FSMs. This method configures the
     * FSM, their FsmStates and their FsmEvents. This method is called by method 
     * &lt;code&gt;configureApplication&lt;/code&gt;
     */
     void <xsl:value-of select="$className"/>_configureFSM(<xsl:value-of select="$className"/> *this);
    </xsl:if>

    <xsl:if test="ControllerManagement">
    /**
     * Configure the components implementing the control actions and control blocks. This method is called by method 
     * &lt;code&gt;configureApplication&lt;/code&gt;
     */
     void <xsl:value-of select="$className"/>_configureControllers(<xsl:value-of select="$className"/> *this);
    </xsl:if>

    <xsl:if test="DataPool">
    /**
     * Configure the components implementing the application data pool. This method is called by method 
     * &lt;code&gt;configureApplication&lt;/code&gt;
     */
     void <xsl:value-of select="$className"/>_configureDataPool(<xsl:value-of select="$className"/> *this);
    </xsl:if>

    <xsl:if test="ParameterDatabase">
    /**
     * Configure the components implementing the parameter database. This method is called by method 
     * &lt;code&gt;configureApplication&lt;/code&gt;
     */
     void <xsl:value-of select="$className"/>_configureParameterDatabase(<xsl:value-of select="$className"/> *this);
    </xsl:if>

    /**
     * Configure the functionality managers. This method is called by method 
     * &lt;code&gt;configureApplication&lt;/code&gt;
     */
     void <xsl:value-of select="$className"/>_configureFunctionalityManagers(<xsl:value-of select="$className"/> *this);


    /**
     * Configure the application. All the components created in the constructor are configured
     * and linked together. The configuration code implements the configuration actions specified
     * in the application model. The application configuration process is broken up into a sequence
     * of steps. To each step a protected method in this class is associated. This method only
     * calls the step methods in sequence. The names of the step methods are formed as
     * follows: &lt;code&gt;configureXXX&lt;/code&gt; where "XXX" is the name of a feature in
     * the application whose configuration is covered by the method.
     */
    void <xsl:value-of select="$className"/>_configureApplication(<xsl:value-of select="$className"/> *this);

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
       <xsl:variable name="ClassName">
            <xsl:call-template name="ClassNameFromPath">
                <xsl:with-param name="path" select="$value"/>
            </xsl:call-template>
       </xsl:variable>
       <xsl:variable name="TypeName">
            <xsl:call-template name="TypeNameFromPath">
                <xsl:with-param name="path" select="$value"/>
            </xsl:call-template>
       </xsl:variable>
       <xsl:variable name="TruncatedClassName">
            <xsl:call-template name="TruncatedClassNameFromPath">
                <xsl:with-param name="path" select="$value"/>
            </xsl:call-template>
       </xsl:variable>
   /**
    * Getter method for components of type &lt;code&gt;<xsl:value-of select="$ClassName"/>&lt;/code&gt;.
    * An assertion exception is raised if the component that is sought with this method is not of type
    * &lt;code&gt;<xsl:value-of select="$ClassName"/>&lt;/code&gt;. An assertion exception is likewise raised 
    * if the value of the integer representing the component name is out of range (namely if it is negative
    * or greater than N where N is the total number of components managed by the component factory).
    * @param compName the name of the component as given by its numerical identifier
    * @return the pointer to the component
    */
    inline <xsl:value-of select="$ClassName"/>* <xsl:value-of select="$className"/>_get<xsl:value-of select="$TruncatedClassName"/>(<xsl:value-of select="$className"/> *this, int compName) {
       assert( (compName&gt;=1) &amp;&amp; (compName&lt;=<xsl:value-of select="$numberOfComponents"/>) );
       assert( type[compName]==<xsl:value-of select="$TypeName"/>);
       return (<xsl:value-of select="$ClassName"/>*)list[compName];
   }
      </xsl:if>
  </xsl:for-each>

#endif
</xsl:document>
</xsl:template>




</xsl:stylesheet>
