<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2004 P&P Software GmbH                                                                                  -->
<!--================================================================-->

<!--===================================================================
This rule writes out the string passed as the "text" parameter as the body of a comment
that follows the JavaDoc convention.
The text string is assumed to consist of a normalized sequence of words (this is normally
achieved by passing the argument "text" through function normalize-space). 
Each comment line starts with the string "indent" (usually, a sequence of spaces), is 
followed by an asterisk and by up to ten words from the text string.
Individual comment lines are written by the template rule "WriteCommentLine".
===================================================================-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
      <xsl:strip-space elements="*"/>
      <xsl:output omit-xml-declaration="yes" method="text"/>
      <xsl:template name="WriteCommentBody">
            <xsl:param name="text"/>
            <xsl:param name="indent"/>
            <xsl:value-of select="$indent"/>* <xsl:call-template name="WriteCommentLine">
                  <xsl:with-param name="text" select="$text"/>
                  <xsl:with-param name="count" select="10"/>
                  <xsl:with-param name="indent" select="$indent"/>
            </xsl:call-template>
      </xsl:template>

      <xsl:template name="WriteCommentLine">
            <xsl:param name="text"/>
            <xsl:param name="count"/>
            <xsl:param name="indent"/>
            <xsl:choose>
                  <xsl:when test="contains($text,' ')">
                        <xsl:variable name="word" select="substring-before($text,' ')"/>
                        <xsl:value-of select="concat($word,' ')"/>
                        <xsl:text/>
                        <xsl:choose>
                              <xsl:when test="($count>0)">
                                    <xsl:call-template name="WriteCommentLine">
                                          <xsl:with-param name="text" select="substring-after($text,' ')"/>
                                          <xsl:with-param name="count" select="number($count)-1"/>
                                          <xsl:with-param name="indent" select="$indent"/>
                                    </xsl:call-template>
                              </xsl:when>
                              <xsl:when test="($count=0)"><xsl:text>
</xsl:text>
                                    <xsl:call-template name="WriteCommentBody">
                                          <xsl:with-param name="text" select="substring-after($text,' ')"/>
                                          <xsl:with-param name="indent" select="$indent"/>
                                    </xsl:call-template>
                              </xsl:when>
                        </xsl:choose>
                  </xsl:when>
                  <xsl:otherwise>
                        <xsl:variable name="word" select="$text"/>
                        <xsl:value-of select="$word"/>
                        <xsl:text/>
                  </xsl:otherwise>
            </xsl:choose>
      </xsl:template>
</xsl:stylesheet>
