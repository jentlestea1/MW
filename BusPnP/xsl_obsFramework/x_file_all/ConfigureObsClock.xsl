<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2004 P&P Software GmbH                                                                                  -->
<!--================================================================-->

<!--===================================================================
This rule writes out the configuration code for the OBS Clock component.
The configuration of the OBS Clock is assumed to consist only of setting property values.
The handling of the default attributes for the custom OBS Clock component is not covered.
===================================================================-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
      <xsl:strip-space elements="*"/>
      <xsl:output omit-xml-declaration="yes" method="text"/>

      <xsl:template match="ObsClock">

            <!-- Construct the name of the ObsClock component -->
            <xsl:variable name="obsClock" select="*[@kind='component']/@name"/>
            <xsl:variable name="type" select="*[(@kind='component') and (@name) and (@type)]/@type"/>
            <xsl:variable name="classType" select="substring-after($type,'/')"/>

<xsl:text>
   </xsl:text>// ---- Configure the OBS Clock "<xsl:value-of select="$obsClock"/>" ----
<xsl:text/>
            <!-- Set the property values  -->
            <xsl:for-each select=".//*[@kind='property'][@name]">
                <xsl:text>   </xsl:text> <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$obsClock"/>)->set<xsl:value-of select="@name"/>(<xsl:value-of select="@value"/>);
<xsl:text/>
            </xsl:for-each>

      </xsl:template>            
      
</xsl:stylesheet>
