<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2004 P&P Software GmbH                               -->
<!--================================================================-->

<!--================================================================-->
<!-- Utility to process a string made up of several words           -->
<!-- separated by a space and returning the same string with the    -->
<!-- same words with the first letter of each word capitalized.     -->
<!-- The utilitiy should be first called with the parameter         -->
<!-- 'before' set equal to the empty string and the parameter       -->
<!-- 'after' set equal to the string to be processed.               -->
<!--================================================================-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
      <xsl:strip-space elements="*"/>
      <xsl:output omit-xml-declaration="yes" method="text"/>
      <xsl:template name="MakeFirstLetterCap">
            <xsl:param name="before"/>
            <xsl:param name="after"/>
            <xsl:variable name="firstInitial" select="substring($after,1,1)"/>
            <xsl:variable name="restOfString" select="substring($after,2,string-length($after))"/>
            <xsl:variable name="firstLetterCap" select="translate($firstInitial,'abcdefghijlmnopqrstuvywz','ABCDEFGHIJLMNOPQRSTUVYWZ')"/>
            <xsl:variable name="afterWithFirstCap" select="concat($firstLetterCap,$restOfString)"/>
            <xsl:choose>
                  <xsl:when test="contains($afterWithFirstCap,' ')">
                        <xsl:variable name="after_1" select="substring-before($afterWithFirstCap,' ')"/>
                        <xsl:variable name="after_2" select="substring-after($afterWithFirstCap,' ')"/>
                        <xsl:variable name="newBefore" select="concat($before,$after_1)"/>
                        <xsl:call-template name="MakeFirstLetterCap">
                              <xsl:with-param name="before" select="$newBefore"/>
                              <xsl:with-param name="after" select="$after_2"/>
                        </xsl:call-template>
                  </xsl:when>
                  <xsl:otherwise>
                        <xsl:value-of select="concat($before,$afterWithFirstCap)"/>
                  </xsl:otherwise>
            </xsl:choose>
      </xsl:template>
</xsl:stylesheet>
