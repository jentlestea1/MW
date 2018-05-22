<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2003 P&P Software GmbH                               -->
<!--================================================================-->

<!--===================================================================
This is the code generator for a dynamic factory class for the OBS Framework.

This XSL program generates the header file of the dynamic factory class.

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
<xsl:variable name="LowerCase" select="'abcdefghijklmnopqrstuvwxyz'"/>
<xsl:variable name="UpperCase" select="'ABCDEFGHIJKLMNOPQRSTUVWXYZ'"/>
<!--
      Top-level rule 
-->
<xsl:template match="/ObsApplication">
    <!-- Extract the information reelvant to the generation of the manoeuvre dynamic factory and store it in a tree variable -->
    <xsl:if test="//Manoeuvre">
        <!--
            -->
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
            Generating code for class CC_ManoeuvreFactory in file <xsl:value-of select="$TargetFile"/>.h
            <xsl:document href="{$TargetFile}.h" omit-xml-declaration="yes" method="text">
               <xsl:call-template name="GenerateCode">
                  <xsl:with-param name="ClassName" select="'CC_ManoeuvreFactory'"/>
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
            Generating code for class CC_TelecommandFactory in file <xsl:value-of select="$TargetFile"/>.h
            <xsl:document href="{$TargetFile}.h" omit-xml-declaration="yes" method="text">  
               <xsl:call-template name="GenerateCode">
                  <xsl:with-param name="ClassName" select="'CC_TelecommandFactory'"/>
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
            Generating code for class CC_TelemetryPacketFactory in file <xsl:value-of select="$TargetFile"/>.h
            <xsl:document href="{$TargetFile}.h" omit-xml-declaration="yes" method="text">  
               <xsl:call-template name="GenerateCode">
                  <xsl:with-param name="ClassName" select="'CC_TelemetryPacketFactory'"/>
                  <xsl:with-param name="containedType" select="'TelemetryPacket'"/>
                  <xsl:with-param name="nodes" select="exslt:node-set($sortedTelemetryPackets)/TelemetryPacket"/>
               </xsl:call-template>
            </xsl:document>
      </xsl:if>
</xsl:template>
<xsl:template name="GenerateCode">
  <xsl:param name="ClassName"/>
  <xsl:param name="containedType"/>
  <xsl:param name="nodes"/>
//
// Copyright 2004 P&amp;P Software GmbH - All Rights Reserved
//
// <xsl:value-of select="$ClassName"/>.h
//
// This file was automatically generated by an XSL program
//

#ifndef <xsl:value-of select="$ClassName"/>_H
#define <xsl:value-of select="$ClassName"/>_H

#include "<xsl:value-of select="$codeDir"/>GeneralInclude/ForwardDeclarations.h"
#include "<xsl:value-of select="$codeDir"/>GeneralInclude/BasicTypes.h"
#include "<xsl:value-of select="$codeDir"/>Base/CC_RootObject.h"   <xsl:text/>
<xsl:for-each select="exslt:node-set($nodes)">
   <xsl:variable name="clsName" select="@type"/>
   <xsl:variable name="pos" select="position()"/>
   <xsl:if test="($pos=1) or (exslt:node-set($nodes)[position()=(($pos)-1)]/@type!=$clsName)">
#include "<xsl:value-of select="$codeDir"/><xsl:value-of select="$clsName"/>.h"  <xsl:text/>
    </xsl:if>
</xsl:for-each>
#include "../Qom/object.h"

/**
 * Dynamic factory for components of type: &lt;code&gt;<xsl:value-of select="$containedType"/>&lt;/code&gt;.
 * A &lt;i&gt;dynamic factory&lt;/i&gt; is a component that manages a pool of instances of
 * components of a certain type. Clients of the factory can require one of these
 * instances at run-time. After the factory hands over a component instance to its
 * client, the instance is marked as "in use" and cannot be given to any other
 * clients. When the requesting client has finished using the instance, it should release
 * it by marking it as "no longer in use". This will allow the factory to make it
 * available to other clients that request it. The "in use" status of the component
 * instances is controlled through method &lt;code&gt;setInUse&lt;/code&gt; declared on
 * the component instances.
 * &lt;p&gt;
 * A dynamic factory is configured in two steps. The first step is performed
 * by the factory constructor when the internal data structures to hold the component
 * instances are created. The second step is performed during application initialization
 * when the component instances are loaded in the factory. Reconfiguration at run time
 * during normal application operation is not allowed.
 * &lt;p&gt;
 * Dynamic factories are implemented as singletons. They can exist in one single instance
 * that can be accessed through the &lt;code&gt;getInstance&lt;/code&gt; method.
 * The one single instance of the class is created the first time that method
 * <code>getInstance</code> is called. In order to avoid possible disruptions of
 * real-time behaviour, applications should ensure that this method has been called
 * at least once before the application enters its operational phase.
 * &lt;p&gt;
 * This factory manages the following component instances:&lt;ul&gt;  <xsl:text/>
<xsl:for-each select="exslt:node-set($nodes)">
   <xsl:variable name="clsName" select="@type"/>
   <xsl:variable name="pos" select="position()"/>
   <xsl:if test="($pos=1) or (exslt:node-set($nodes)[position()=(($pos)-1)]/@type!=$clsName)">
      <xsl:variable name="uClsName">
         <xsl:call-template name="ClassNameFromPath">
               <xsl:with-param name="path" select="$clsName"/>
         </xsl:call-template>
      </xsl:variable>
 * &lt;li&gt;Number of instances of type &lt;code&gt;<xsl:value-of select="$uClsName"/>&lt;/code&gt;: <xsl:text/>
      <xsl:value-of select="count(exslt:node-set($nodes)[@type=$clsName])"/>&lt;/li&gt;    <xsl:text/>
   </xsl:if>
</xsl:for-each>
 * &lt;/ul&gt;
 * The code for this class was automatically generated by an XSL program processing
 * the XML-based application model.    
 * @ingroup <xsl:value-of select="$containedType"/>
 * @see <xsl:value-of select="$containedType"/>
 * @author Automatically Generated Class
 * @version 1.0
 */
<!--
class <xsl:value-of select="$ClassName"/> : public CC_RootObject {

  private:
    static <xsl:value-of select="$ClassName"/>* pInstance;     <xsl:text/>
    <xsl:for-each select="exslt:node-set($nodes)">
      <xsl:variable name="clsName" select="@type"/>
      <xsl:variable name="tClassName">
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
    unsigned int size<xsl:value-of select="$tClassName"/>;
    <xsl:value-of select="$uClsName"/>** pool<xsl:value-of select="$tClassName"/>;
      </xsl:if>
    </xsl:for-each>

  protected:
    /**
     * Instantiate the factory component. The class identifier is set and
     * the internal data structures to hold the component instances managed
     * by the factory are created.
     * This constructor is defined to be protected because this is a singleton
     * class.
     */
    <xsl:value-of select="$ClassName"/>(void);

  public:

    /**
     * Get the single instance of this singleton class. If the instance does not
     * yet exist, it is created.
     */
    static <xsl:value-of select="$ClassName"/>* getInstance(void);

    /**
     * Check that all component instances required by the factory have been loaded.
     * @return true if the component is configured, false otherwise
     */
    virtual bool isObjectConfigured();

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
    /**
     * Load one instance of type &lt;code&gt;<xsl:value-of select="$uClsName"/>&lt;/code&gt; in the
     * factory. The component instances managed by the factory are internally stored in an
     * array. This method loads the i-th element of the array. The argument i should lie
     * in the interval [0,N-1] where N is the number of component instances of type
     * &lt;code&gt;<xsl:value-of select="$uClsName"/>&lt;/code&gt;. The value of N is defined by
     * the class constructor.
     * &lt;p&gt;
     * The "in use" status of a newly loaded component is initialized
     * to: "component is not in use".
     * &lt;p&gt;
     * This is an initialization method that should only be called during the application
     * configuration phase.
     * @param i the index in the internal array
     * @param pItem the component instance
     */
    void set<xsl:value-of select="$containedType"/>(unsigned int i, <xsl:value-of select="$uClsName"/>* pItem);

    /**
     * Return the number of component instances of type &lt;code&gt;<xsl:value-of select="$uClsName"/>&lt;/code&gt;
     * that are currently allocated. A component instance is allocated if its "in use" status is
     * equal to: "component is in use".
     * @return the number of allocated component instances
     */
    unsigned int getNumber<xsl:value-of select="$tClsName"/>(void);

    /**
     * Return the number of component instances of type &lt;code&gt;<xsl:value-of select="$uClsName"/>&lt;/code&gt;
     * that are in the factory. The value returned is the maximum number of component instances of
     * type &lt;code&gt;<xsl:value-of select="$uClsName"/>&lt;/code&gt; that can be allocated.
     * @return the total number of component instances in the factory of
     * type &lt;code&gt;<xsl:value-of select="$uClsName"/>&lt;/code&gt;
     */
    unsigned int getCapacity<xsl:value-of select="$tClsName"/>(void);

    /**
     * Allocate one instance of type &lt;code&gt;<xsl:value-of select="$uClsName"/>&lt;/code&gt;.
     * This method scans all the entries in the factory of type &lt;code&gt;<xsl:value-of select="$uClsName"/>&lt;/code&gt;
     * and returns the first one which is not in use. <xsl:text/>
     <xsl:if test="Property">
     * In addition to verifyin that the returned component is not in use, this method also performs a check
     * on the value of the component configuration parameters. The folloging configuration parameters 
     * are checked: <xsl:for-each select="Property"><xsl:if test="not(position()=last())"><xsl:value-of select="."/>, </xsl:if>
     <xsl:if test="position()=last()"><xsl:value-of select="."/>.</xsl:if></xsl:for-each>
     * This method has a parameter matching each component configuration parameter. A component instance is
     * returned only if the value of the component configuration parameter is greater than or equal to the method
     * parameter. <xsl:text/>
     </xsl:if>
     * Before being returned to the caller,
     * the status of the component instance is changed to: "in use". A client that receives
     * a component instance through a call to this method, should release the instance when it
     * no longer needs it. This can be done by calling
     * method &lt;code&gt;setInUse(false)&lt;/code&gt; on the component itself.
     * &lt;p&gt;
     * If no free component instances are found, then the method returns null. Note that no
     * event report is generated to record the failure to allocate a component instance. Event
     * reporting is the responsibility of the caller. <xsl:text/>
      <xsl:for-each select="Property">
     * @param <xsl:value-of select="."/> minimum value for a component configuration parameter <xsl:text/>
      </xsl:for-each>     
     * @return the allocated component instance or null if no free instances were found
     */
    <xsl:value-of select="$uClsName"/>* allocate<xsl:value-of select="$tClsName"/>(<xsl:for-each select="Property">unsigned int <xsl:if test="not(position()=last())">
          <xsl:value-of select="."/>, </xsl:if><xsl:if test="position()=last()"><xsl:value-of select="."/></xsl:if></xsl:for-each>);

    /**
     * Check whether a non-allocated component instance of type &lt;code&gt;<xsl:value-of select="$uClsName"/>&lt;/code&gt;
     * is available within the factory. If this method return true, then the corresponding
     * &lt;code&gt;allocate&lt;/code&gt; method is guaranteed to return a non-null value.
     * The method parameters are used as in the corresponding &lt;code&gt;allocate&lt;/code&gt; method.
     * @see #allocate<xsl:value-of select="$uClsName"/> 
      <xsl:for-each select="Property">
     * @param <xsl:value-of select="."/> minimum value for a component configuration parameter <xsl:text/>
      </xsl:for-each>     
     * @return true if free instances of type <xsl:value-of select="$uClsName"/> are available,
     * false otherwise
     */
    bool isFree<xsl:value-of select="$tClsName"/>(<xsl:for-each select="Property">unsigned int <xsl:if test="not(position()=last())">
          <xsl:value-of select="."/>, </xsl:if><xsl:if test="position()=last()"><xsl:value-of select="."/></xsl:if></xsl:for-each>);

            <xsl:if test="$uClsName='DC_PUSDataReportingPacket'">
    /**
     * Return the PUS data reporting packet that is currently allocated and whose SID is
     * equal to the value of the argument &lt;code&gt;sid&lt;/code&gt;.
     * This method scans all the instances of type <xsl:value-of select="$uClsName"/> in the
     * factory and, if it finds one which is allocated (its status is "in use") and with the SID
     * equal to &lt;code&gt;sid&lt;/code&gt;, it returns it. Otherwise, a null pointer is returned.
     * @param sid the structure identifier (SID) of the PUS data reporting packet
     * @return the sought PUS data reporting packet or null if no allocated data reporting packet
     * with SID equal to &lt;code&gt;sid&lt;/code&gt; is found
     */
    <xsl:value-of select="$uClsName"/>* get<xsl:value-of select="$tClsName"/>(TD_SID sid);
            </xsl:if>

       </xsl:if>
    </xsl:for-each>
};
-->
#define TYPE_<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/> "<xsl:value-of select="translate($ClassName,$UpperCase,$LowerCase)"/>"

static <xsl:value-of select="$ClassName"/>* pInstance;     <xsl:text/>

void <xsl:value-of select="$ClassName"/>_register(void);


/////////////////////////////////////////////////////////////////////////////////
//
//                              class and struct
//
/////////////////////////////////////////////////////////////////////////////////

struct <xsl:value-of select="$ClassName"/> {
    CC_RootObject parent;
    <xsl:for-each select="exslt:node-set($nodes)">
      <xsl:variable name="clsName" select="@type"/>
      <xsl:variable name="tClassName">
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
    unsigned int size<xsl:value-of select="$tClassName"/>;
    <xsl:value-of select="$uClsName"/>** pool<xsl:value-of select="$tClassName"/>;
      </xsl:if>
    </xsl:for-each>
};


struct <xsl:value-of select="$ClassName"/>Class {
    CC_RootObjectClass parent_class;

    /**
     * Check that all component instances required by the factory have been loaded.
     * @return true if the component is configured, false otherwise
     */
    bool (*isObjectConfigured)(void *obj);


};


#define <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>_GET_CLASS(obj) \
             OBJECT_GET_CLASS(<xsl:value-of select="$ClassName"/>Class, obj, TYPE_<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>)


#define <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>_CLASS(klass) \
             OBJECT_CLASS_CHECK(<xsl:value-of select="$ClassName"/>Class, klass, TYPE_<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>)


#define <xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>(obj) \
             OBJECT_CHECK(<xsl:value-of select="$ClassName"/>, obj, TYPE_<xsl:value-of select="translate($ClassName,$LowerCase,$UpperCase)"/>)


<xsl:value-of select="$ClassName"/>* <xsl:value-of select="$ClassName"/>_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Get the single instance of this singleton class. If the instance does not
 * yet exist, it is created.
 */
static <xsl:value-of select="$ClassName"/>* <xsl:value-of select="$ClassName"/>_getInstance(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
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
    /**
     * Load one instance of type &lt;code&gt;<xsl:value-of select="$uClsName"/>&lt;/code&gt; in the
     * factory. The component instances managed by the factory are internally stored in an
     * array. This method loads the i-th element of the array. The argument i should lie
     * in the interval [0,N-1] where N is the number of component instances of type
     * &lt;code&gt;<xsl:value-of select="$uClsName"/>&lt;/code&gt;. The value of N is defined by
     * the class constructor.
     * &lt;p&gt;
     * The "in use" status of a newly loaded component is initialized
     * to: "component is not in use".
     * &lt;p&gt;
     * This is an initialization method that should only be called during the application
     * configuration phase.
     * @param i the index in the internal array
     * @param pItem the component instance
     */
     void <xsl:value-of select="$ClassName"/>_set<xsl:value-of select="$containedType"/>(<xsl:value-of select="$ClassName"/> *this, unsigned int i, <xsl:value-of select="$uClsName"/>* pItem);

    /**
     * Return the number of component instances of type &lt;code&gt;<xsl:value-of select="$uClsName"/>&lt;/code&gt;
     * that are currently allocated. A component instance is allocated if its "in use" status is
     * equal to: "component is in use".
     * @return the number of allocated component instances
     */
     unsigned int <xsl:value-of select="$ClassName"/>_getNumber<xsl:value-of select="$tClsName"/>(<xsl:value-of select="$ClassName"/> *this);

    /**
     * Return the number of component instances of type &lt;code&gt;<xsl:value-of select="$uClsName"/>&lt;/code&gt;
     * that are in the factory. The value returned is the maximum number of component instances of
     * type &lt;code&gt;<xsl:value-of select="$uClsName"/>&lt;/code&gt; that can be allocated.
     * @return the total number of component instances in the factory of
     * type &lt;code&gt;<xsl:value-of select="$uClsName"/>&lt;/code&gt;
     */
    unsigned int  <xsl:value-of select="$ClassName"/>_getCapacity<xsl:value-of select="$tClsName"/>( <xsl:value-of select="$ClassName"/> *this);

    /**
     * Allocate one instance of type &lt;code&gt;<xsl:value-of select="$uClsName"/>&lt;/code&gt;.
     * This method scans all the entries in the factory of type &lt;code&gt;<xsl:value-of select="$uClsName"/>&lt;/code&gt;
     * and returns the first one which is not in use. <xsl:text/>
     <xsl:if test="Property">
     * In addition to verifyin that the returned component is not in use, this method also performs a check
     * on the value of the component configuration parameters. The folloging configuration parameters 
     * are checked: <xsl:for-each select="Property"><xsl:if test="not(position()=last())"><xsl:value-of select="."/>, </xsl:if>
     <xsl:if test="position()=last()"><xsl:value-of select="."/>.</xsl:if></xsl:for-each>
     * This method has a parameter matching each component configuration parameter. A component instance is
     * returned only if the value of the component configuration parameter is greater than or equal to the method
     * parameter. <xsl:text/>
     </xsl:if>
     * Before being returned to the caller,
     * the status of the component instance is changed to: "in use". A client that receives
     * a component instance through a call to this method, should release the instance when it
     * no longer needs it. This can be done by calling
     * method &lt;code&gt;setInUse(false)&lt;/code&gt; on the component itself.
     * &lt;p&gt;
     * If no free component instances are found, then the method returns null. Note that no
     * event report is generated to record the failure to allocate a component instance. Event
     * reporting is the responsibility of the caller. <xsl:text/>
      <xsl:for-each select="Property">
     * @param <xsl:value-of select="."/> minimum value for a component configuration parameter <xsl:text/>
      </xsl:for-each>     
     * @return the allocated component instance or null if no free instances were found
     */
    <xsl:value-of select="$uClsName"/>*  <xsl:value-of select="$ClassName"/>_allocate<xsl:value-of select="$tClsName"/>(<xsl:value-of select="$ClassName"/> *this,<xsl:for-each select="Property">unsigned int <xsl:if test="not(position()=last())">
          <xsl:value-of select="."/>, </xsl:if><xsl:if test="position()=last()"><xsl:value-of select="."/></xsl:if></xsl:for-each>);

    /**
     * Check whether a non-allocated component instance of type &lt;code&gt;<xsl:value-of select="$uClsName"/>&lt;/code&gt;
     * is available within the factory. If this method return true, then the corresponding
     * &lt;code&gt;allocate&lt;/code&gt; method is guaranteed to return a non-null value.
     * The method parameters are used as in the corresponding &lt;code&gt;allocate&lt;/code&gt; method.
     * @see #allocate<xsl:value-of select="$uClsName"/> 
      <xsl:for-each select="Property">
     * @param <xsl:value-of select="."/> minimum value for a component configuration parameter <xsl:text/>
      </xsl:for-each>     
     * @return true if free instances of type <xsl:value-of select="$uClsName"/> are available,
     * false otherwise
     */
    bool  <xsl:value-of select="$ClassName"/>_isFree<xsl:value-of select="$tClsName"/>( <xsl:value-of select="$ClassName"/> *this,<xsl:for-each select="Property">unsigned int <xsl:if test="not(position()=last())">
          <xsl:value-of select="."/>, </xsl:if><xsl:if test="position()=last()"><xsl:value-of select="."/></xsl:if></xsl:for-each>);

            <xsl:if test="$uClsName='DC_PUSDataReportingPacket'">
    /**
     * Return the PUS data reporting packet that is currently allocated and whose SID is
     * equal to the value of the argument &lt;code&gt;sid&lt;/code&gt;.
     * This method scans all the instances of type <xsl:value-of select="$uClsName"/> in the
     * factory and, if it finds one which is allocated (its status is "in use") and with the SID
     * equal to &lt;code&gt;sid&lt;/code&gt;, it returns it. Otherwise, a null pointer is returned.
     * @param sid the structure identifier (SID) of the PUS data reporting packet
     * @return the sought PUS data reporting packet or null if no allocated data reporting packet
     * with SID equal to &lt;code&gt;sid&lt;/code&gt; is found
     */
    <xsl:value-of select="$uClsName"/>*  <xsl:value-of select="$ClassName"/>_get<xsl:value-of select="$tClsName"/>(<xsl:value-of select="$ClassName"/>* this,TD_SID sid);
            </xsl:if>

       </xsl:if>
    </xsl:for-each>

#endif

</xsl:template>




</xsl:stylesheet>
