<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2004 P&P Software GmbH                                                                                  -->
<!--================================================================-->

<!--===================================================================
This rule writes out the configuration code for a control block. This rule is only partially
implemented. Only the case of control blocks with data pool link is covered.
The rule links the inputs and outputs of the control block and it initializes the parameter
values with values read from the parameter database.
===================================================================-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
      <xsl:strip-space elements="*"/>
      <xsl:output omit-xml-declaration="yes" method="text"/>

      <xsl:include href="MakeFirstLetterCap.xsl"/>

      <xsl:template match="ControlBlock">

           <xsl:variable name="contBlk" select="*[(@kind='component') and (@name)]/@name"/>
           <xsl:variable name="type" select="*[(@kind='component') and (@name) and (@type)]/@type"/>
           <xsl:variable name="classType" select="substring-after($type,'/')"/>
<xsl:text>
   </xsl:text>// ---- Configure the control block "<xsl:value-of select="$contBlk"/>" ----
<xsl:text/>

            <!--NB: no configuration needs to be done for control blocks that use copy link -->
            <xsl:choose>
                  <xsl:when test="DataPoolLink">
                        <xsl:call-template name="dataPoolLink"/>
                  </xsl:when>
                  <xsl:when test="DataItemLink">
                        <xsl:call-template name="dataItemLink"/>
                  </xsl:when>
                  <xsl:when test="PointerLink">
                        <xsl:call-template name="pointerLink"/>
                  </xsl:when>
            </xsl:choose>
            
            <xsl:for-each select="Parameter">
                  <xsl:variable name="parName" select="DatabaseName/@value"/>
                  <!-- determine the type of the database parameter -->
                  <xsl:variable name="parType" select="/ObsApplication/ParameterDatabase//Parameter[Name/@value=substring-after($parName,'_')]/Type/@value"/>
                   <xsl:variable name="normalizedType">
                        <xsl:call-template name="MakeFirstLetterCap">
                          <xsl:with-param name="before" select="''"/>
                          <xsl:with-param name="after" select="$parType"/>
                        </xsl:call-template>
                    </xsl:variable>
               <xsl:text>   </xsl:text> <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$contBlk"/>)->setParameter(<xsl:value-of 
                   select="Number/@value"/>,<xsl:value-of select="'PARAMETERDATABASE'"/>_GET_CLASS(CC_RootObject_getParameterDatabase())->getParameter<xsl:value-of select="$normalizedType"/>(<xsl:value-of select="DatabaseName/@value"/>));
<xsl:text/>
            </xsl:for-each>
            
      </xsl:template>

      <!-- ====================================================================== -->

      <xsl:template name="dataPoolLink">
           <!-- The control block to be configured -->
           <xsl:variable name="contBlk" select="*[(@kind='component') and (@name)]/@name"/>
           <xsl:variable name="type" select="*[(@kind='component') and (@name) and (@type)]/@type"/>
           <xsl:variable name="classType" select="substring-after($type,'/')"/>

           <xsl:for-each select="Input">
               <xsl:text>   </xsl:text>
               <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$contBlk"/>)->setInputLink(<xsl:value-of select="Number/@value"/>,<xsl:value-of select="DatapoolName/@value"/>);
<xsl:text/>     
           </xsl:for-each>
           <xsl:for-each select="Output">
               <xsl:text>   </xsl:text>
               <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/> _GET_CLASS(<xsl:value-of select="$contBlk"/>)->setOutputLink(<xsl:value-of select="Number/@value"/>,<xsl:value-of select="DatapoolName/@value"/>);
<xsl:text/>
           </xsl:for-each>
      </xsl:template>            

      <!-- ====================================================================== -->

      <xsl:template name="dataItemLink">
           <!-- The control block to be configured -->
           <xsl:variable name="contBlk" select="*[(@kind='component') and (@name)]/@name"/>

            -- ERROR: configuration of control blocks with data item link is not currently covered by this XSL rule
      </xsl:template>            

      <!-- ====================================================================== -->

      <xsl:template name="pointerLink">
           <!-- The control block to be configured -->
           <xsl:variable name="contBlk" select="*[(@kind='component') and (@name)]/@name"/>

            -- ERROR: configuration of control blocks with pointer link is not currently covered by this XSL rule
      </xsl:template>            

</xsl:stylesheet>
