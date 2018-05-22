<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2004 P&P Software GmbH                                                                                  -->
<!--================================================================-->

<!--===================================================================
This rule writes out the configuration code for the static part of the CC_RootObject class
(excluding the setting of the size of the system list).
===================================================================-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
      <xsl:strip-space elements="*"/>
      <xsl:output omit-xml-declaration="yes" method="text"/>

      <xsl:template name="configureRootObject">

           <xsl:variable name="evtRep" select="//EventRepository/*[@kind='component'][@name]/@name"/>
           <xsl:variable name="parDB" select="//ParameterDatabase/*[@kind='component'][@name]/@name"/>
           <xsl:variable name="DP" select="//DataPool/*[@kind='component'][@name]/@name"/>
           <xsl:variable name="tracer" select="//Tracer/*[@kind='component'][@name]/@name"/>

   // Load the event repository
   CC_RootObject_setEventRepository(<xsl:value-of select="$evtRep"/>);

   // Load the parameter database
   CC_RootObject_setParameterDatabase(<xsl:value-of select="$parDB"/>);
           
   // Load the datapool
   CC_RootObject_setDataPool(<xsl:value-of select="$DP"/>);

   // Load the tracer
   CC_RootObject_setTracer(<xsl:value-of select="$tracer"/>);

      </xsl:template>            
      
</xsl:stylesheet>
