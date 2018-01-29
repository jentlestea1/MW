<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2004 P&P Software GmbH                                                                                  -->
<!--================================================================-->

<!--===================================================================
This rule writes out the configuration code for the event repository component.
This rule only covers the setting of the repository property values. The handling of
 event reporting inhibition status and the handling of the default attributes for the
 custom event repository component are not covered.
===================================================================-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
      <xsl:strip-space elements="*"/>
      <xsl:output omit-xml-declaration="yes" method="text"/>

      <xsl:template match="EventRepository">

            <!-- Construct the name of the event repository component -->
            <xsl:variable name="evtRep" select="*[@kind='component']/@name"/>
            <xsl:variable name="type" select="*[(@kind='component') and (@name) and (@type)]/@type"/>
            <xsl:variable name="classType" select="substring-after($type,'/')"/>

<xsl:text>
   </xsl:text>// ---- Configure the event repository "<xsl:value-of select="$evtRep"/>" ----
<xsl:text/>
            <!-- Set the property values  -->
            <xsl:for-each select=".//*[@kind='property'][@name]">
                <xsl:text>   </xsl:text><xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$evtRep"/>)->set<xsl:value-of select="@name"/>(<xsl:value-of select="@value"/>);
<xsl:text/>
            </xsl:for-each>

      </xsl:template>            
      
</xsl:stylesheet>
