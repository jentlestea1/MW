<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2003 P&P Software GmbH                               -->
<!--================================================================-->

<!--===================================================================
This rule constructs the class identifier from the class name.
The class name is assumed to have the form: "yy_xxx". The class identifier is constructed 
as: "ID_XXX". The part of the class name after the underscore is capitalized.
===================================================================-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
      <xsl:strip-space elements="*"/>
      <xsl:output omit-xml-declaration="yes" method="text"/>
      <xsl:template name="ClassIdFromClassName">
            <xsl:param name="className"/>
            <xsl:variable name="temp_1" select="substring-after($className,'_')"/>
            <xsl:variable name="temp_2" select="translate($temp_1,'abcdefghijklmnopqrstuvzyxw','ABCDEFGHIJKLMNOPQRSTUVZYXW')"/>
            <xsl:value-of select="concat('ID_',$temp_2)"/>
      </xsl:template>
</xsl:stylesheet>
