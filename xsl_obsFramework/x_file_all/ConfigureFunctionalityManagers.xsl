<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2004 P&P Software GmbH                                                                                  -->
<!--================================================================-->

<!--===================================================================
This files contains the rules to write out the configuration code for the four functionality managers.
Most of these rules are incomplete and would need to be extended to cover all cases foreseen
by the framework.
===================================================================-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
      <xsl:strip-space elements="*"/>
      <xsl:output omit-xml-declaration="yes" method="text"/>

      <xsl:template match="ManoeuvreManager">
            <!--Construct the name of the manager component -->
           <xsl:variable name="man" select="@name"/>
           <xsl:variable name="type" select="@type"/>
           <xsl:variable name="classType" select="substring-after($type,'/')"/>
           
            <!-- Set the property values  -->
<xsl:text>
   </xsl:text>// ---- Configure the manoeuvre manager
<xsl:text/>
            <xsl:for-each select=".//*[@kind='property'][@name]">
                <xsl:text>   </xsl:text>
                    <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$man"/>)->set<xsl:value-of select="@name"/>(<xsl:value-of select="@value"/>);
<xsl:text/>
            </xsl:for-each>

      </xsl:template>            

<!--===================================================================-->

      <xsl:template match="TelecommandManager">
            <!--Construct the name of the manager component -->
           <xsl:variable name="man" select="@name"/>
           <xsl:variable name="type" select="@type"/>
           <xsl:variable name="classType" select="substring-after($type,'/')"/>
           
            <!-- Set the property values  -->
<xsl:text>
   </xsl:text>// ---- Configure the telecommand manager
<xsl:text/>
            <xsl:for-each select="./*[@kind='property'][@name]">
                <xsl:text>   </xsl:text><xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$man"/>)->set<xsl:value-of select="@name"/>(<xsl:value-of select="@value"/>);
<xsl:text/>
            </xsl:for-each>

            <!-- Load the telecommand loader -->
            <xsl:variable name="tcLoader" select="TelecommandLoader//*[@kind='component']/@name"/>
            <xsl:text>   </xsl:text> <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$man"/>)->setTelecommandLoader(<xsl:value-of select="$tcLoader"/>);

            <!-- Configure the telecommand loader -->
            <xsl:apply-templates select="TelecommandLoader" mode="TcManagerConfig">
                  <xsl:with-param name="TcMan" select="$man"/>
            </xsl:apply-templates>


      </xsl:template>            
      
<!--===================================================================-->

      <!-- Incomplete implementation that will only work in the case of the basic PUS TC loader -->
      <xsl:template match="TelecommandLoader" mode="TcManagerConfig">
            <xsl:param name="TcMan"/>
            
            <xsl:variable name="tcLoader" select=".//*[@kind='component']/@name"/>
            <xsl:variable name="type" select=".//*[@kind='component']/@type"/>
            <xsl:variable name="classType" select="substring-after($type,'/')"/>
            
            <!-- Set the property values  -->
<xsl:text>
   </xsl:text>// ---- Configure the telecommand loader
<xsl:text/>
            <xsl:for-each select=".//*[@kind='property'][@name]">
                <xsl:text>   </xsl:text> <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$tcLoader"/>)->set<xsl:value-of select="@name"/>(<xsl:value-of select="@value"/>);
<xsl:text/>
            </xsl:for-each>
            
            <!-- Load the telemetry manager -->
            <xsl:text>   </xsl:text>
             <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$tcLoader"/>)->setTelecommandManager(<xsl:value-of select="$TcMan"/>);
                  
       </xsl:template>

<!--===================================================================-->

      <xsl:template match="TelemetryManager">
            <!--Construct the name of the manager component -->
           <xsl:variable name="man" select="@name"/>
           <xsl:variable name="type" select="@type"/>
           <xsl:variable name="classType" select="substring-after($type,'/')"/>
           
            <!-- Set the property values  -->
<xsl:text>
   </xsl:text>// ---- Configure the telemetry manager
<xsl:text/>
            <xsl:for-each select="./*[@kind='property'][@name]">
                <xsl:text>   </xsl:text>
               <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$man"/>)->set<xsl:value-of select="@name"/>(<xsl:value-of select="@value"/>);
<xsl:text/>
            </xsl:for-each>

            <!-- Load the telemetry stream -->
            <xsl:variable name="tmStream" select="TelemetryStream//*[@kind='component']/@name"/>
            <xsl:text>   </xsl:text>
            <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$man"/>)->setTelemetryStream(<xsl:value-of select="$tmStream"/>);
<xsl:text/>
            <!-- Load the telemetry mode manager (this rule assumes that the PUS mode manager is used -->
            <xsl:variable name="tmModMan" select="//PUSTelemetryModeManager[@kind='component']/@name"/>
            <xsl:text>   </xsl:text>
            <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$man"/>)->setTelemetryModeManager(<xsl:value-of select="$tmModMan"/>);
<xsl:text/>
            <!-- Configure the telemetry stream -->
            <xsl:apply-templates select="TelemetryStream" mode="TmManagerConfig"/>

            <!-- Configure the telemetry mode manager -->
            <xsl:apply-templates select="//TelemetryManagement/PUSTelemetryPackets/PUSTelemetryModeManager" mode="TmManagerConfig"/>

      </xsl:template>            
      
<!--===================================================================-->

      <!-- Incomplete implementation that will only work in the case of the basic PUS TM stream -->
      <xsl:template match="TelemetryStream" mode="TmManagerConfig">
            
            <xsl:variable name="tmStream" select=".//*[@kind='component']/@name"/>
            <xsl:variable name="type" select=".//*[@kind='component']/@type"/>
            <xsl:variable name="classType" select="substring-after($type,'/')"/>
            
            <!-- Set the property values  -->
<xsl:text>
   </xsl:text>// ---- Configure the telemetry stream
<xsl:text/>
            <xsl:for-each select=".//*[@kind='property'][@name]">
                <xsl:text>   </xsl:text>
                <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$tmStream"/>)->set<xsl:value-of select="@name"/>(<xsl:value-of select="@value"/>);
<xsl:text/>
            </xsl:for-each>
            
       </xsl:template>
                  
<!--===================================================================-->

      <!-- Incomplete implementation that will only work in the case of the PUS TM mode manager -->
      <xsl:template match="PUSTelemetryModeManager" mode="TmManagerConfig">
            
            <xsl:variable name="tmModMan" select="//PUSTelemetryModeManager[@kind='component']/@name"/>
            <xsl:variable name="type" select="//PUSTelemetryModeManager[@kind='component']/@type"/>
            <xsl:variable name="classType" select="substring-after($type,'/')"/>
            
            <!-- Set the property values  -->
<xsl:text>
   </xsl:text>// ---- Configure the telemetry mode manager
<xsl:text/>
            <xsl:for-each select="//PUSTelemetryModeManager/*[@kind='property'][@name]">
                <xsl:text>   </xsl:text>
                <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$tmModMan"/>)->set<xsl:value-of select="@name"/>(<xsl:value-of select="@value"/>);
<xsl:text/>
            </xsl:for-each>
            
       </xsl:template>
                  
                  
</xsl:stylesheet>
