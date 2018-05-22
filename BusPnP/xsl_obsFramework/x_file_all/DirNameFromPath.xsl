<?xml version="1.0" encoding="UTF-8"?>

<!--
      Copyright 2003 P&P Software GmbH                               
-->

<!--===================================================================
This rule extracts the directory path from the class path.
The class path is assumed to be specified as follows: "XXX/Classname" where"XXX" is
the directory path and "ClassName" is the class name. 
The rule returns the string "/XXX" (note that the "XXX" string may be made up of substrings 
separated by slashes but it should not start with a slash).
===================================================================-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
      <xsl:strip-space elements="*"/>
      <xsl:output omit-xml-declaration="yes" method="text"/>
      <xsl:template name="DirNameFromPath">
            <xsl:param name="path"/>
            <xsl:call-template name="DirNameFromPath_2">
                  <xsl:with-param name="firstPart" select="''"/>
                  <xsl:with-param name="secondPart" select="$path"/>
            </xsl:call-template>
      </xsl:template>

      <xsl:template name="DirNameFromPath_2">
            <xsl:param name="firstPart"/>
            <xsl:param name="secondPart"/>
            <xsl:variable name="temp_1" select="substring-before($secondPart,'/')"/>
            <xsl:variable name="temp_2" select="substring-after($secondPart,'/')"/>
            <xsl:choose>
                  <xsl:when test="contains($temp_2,'/')">
                        <xsl:call-template name="DirNameFromPath_2">
                              <xsl:with-param name="firstPart" select="concat(firstPart,'/',$temp_1)"/>
                              <xsl:with-param name="secondPart" select="$temp_2"/>
                        </xsl:call-template>
                  </xsl:when>
                  <xsl:otherwise>
                        <xsl:value-of select="$temp_1"/>
                  </xsl:otherwise>
            </xsl:choose>
      </xsl:template>

</xsl:stylesheet>
