<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2003 P&P Software GmbH                               -->
<!--================================================================-->

<!--===================================================================
This rule extracts the truncated class name from the class path.
The truncated class name is the class name without the initial "DC_" or "CC_" prefix.
The class path is assumed to be specified as follows: "XXX/Classname" where"XXX" is
the directory path and "ClassName" is the desired class name.
===================================================================-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
      <xsl:strip-space elements="*"/>
      <xsl:output omit-xml-declaration="yes" method="text"/>
      <xsl:template name="TruncatedClassNameFromPath">
            <xsl:param name="path"/>
            <xsl:variable name="temp" select="substring-after($path,'/')"/>
            <xsl:choose>
                  <xsl:when test="contains($temp,'/')">
                        <xsl:call-template name="ClassNameFromPath">
                              <xsl:with-param name="path" select="$temp"/>
                        </xsl:call-template>
                  </xsl:when>
                  <xsl:otherwise>
                       <xsl:variable name="len" select="string-length($temp)"/><xsl:value-of select="substring($temp,4,number($len)-3)"/>
                  </xsl:otherwise>
            </xsl:choose>
      </xsl:template>
</xsl:stylesheet>
