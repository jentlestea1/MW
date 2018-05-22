<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2004 P&P Software GmbH                                                                                  -->
<!--================================================================-->

<!--===================================================================
This rule writes out the configuration code for a control action.
===================================================================-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
      <xsl:strip-space elements="*"/>
      <xsl:output omit-xml-declaration="yes" method="text"/>

      <xsl:template match="ControlAction">

            <!--Construct the name of the control action component -->
           <xsl:variable name="contAct" select="@name"/>
           
           <!--Construct the name of the control block attached to the control action -->
           <xsl:variable name="contBlk" select="./ControlBlock//*[(@kind='component') and (@name)]/@name"/>    
           <xsl:variable name="type" select="./ControlBlock//*[(@kind='component') and (@name) and (@type)]/@type"/>
           <xsl:variable name="classType" select="substring-after($type,'/')"/>
         // ---- Configure the control  action "<xsl:value-of select="$contAct"/>" ----
<xsl:text/>
           <!-- Set the initial enable status -->
           <xsl:if test="InitialEnableStatus">
                 <xsl:choose>
                       <xsl:when test="@value='ENABLED'">
                           <xsl:text>   </xsl:text><xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$contAct"/>)->setInitialEnabledStatus(true);
<xsl:text/>
                       </xsl:when>
                       <xsl:when test="@value='DISABLED'">
                           <xsl:text>   </xsl:text><xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$contAct"/>)->setInitialEnabledStatus(false);
<xsl:text/>
                       </xsl:when>
                       <xsl:otherwise>
                       -- FSM Configuration Error: illegal value for the initial enabled status of a control action
                       </xsl:otherwise>
                 </xsl:choose>
           </xsl:if>

            <!-- Load the control block in the control action -->
            <xsl:text>   </xsl:text><xsl:value-of select="$contAct"/>->setTargetControlBlock(<xsl:value-of select="$contBlk"/>);
<xsl:text/>            
      </xsl:template>            
      
</xsl:stylesheet>
