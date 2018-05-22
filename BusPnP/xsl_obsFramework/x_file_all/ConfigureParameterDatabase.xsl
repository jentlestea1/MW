<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2004 P&P Software GmbH                                                                                  -->
<!--================================================================-->

<!--===================================================================
This rule writes out the configuration code for the parameter database. This
consists in code to set property values and to reset the parameter database.
===================================================================-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
      <xsl:strip-space elements="*"/>
      <xsl:output omit-xml-declaration="yes" method="text"/>

      <xsl:template match="ParameterDatabase">

           <xsl:variable name="parDB" select="*[(@kind='component') and (@name)]/@name"/>
           <xsl:variable name="type" select="*[(@kind='component') and (@name) and (@type)]/@type"/>
           <xsl:variable name="classType" select="substring-after($type,'/')"/>
            <!-- Set the property values  -->
            <xsl:for-each select=".//*[@kind='property'][@name]">
                <xsl:text>   </xsl:text>
                 <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$parDB"/>)->set<xsl:value-of select="@name"/>(<xsl:value-of select="@value"/>);
<xsl:text/>
            </xsl:for-each>

            <!-- Reset the parameter database -->
            <xsl:text>   </xsl:text><xsl:value-of select="$parDB"/>->reset();
<xsl:text/>

      </xsl:template>            

</xsl:stylesheet>
