<?xml version="1.0" encoding="UTF-8"?>
<!--
    Copyright 2004 P&P Software GmbH                                                                                 
-->
<!--
Count the number of components in the sample application model.
 -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"  version="1.1"  xmlns:lxslt="http://xml.apache.org/xslt">

<xsl:strip-space elements="*"/>
<xsl:output omit-xml-declaration="yes" method="text"/>

<!--
    Global Variables                                                                                                                      
-->
<xsl:template match="/ObsApplication">
      Number of components:      <xsl:value-of select="count(//*[@kind='component'][@name])"/>

</xsl:template>

</xsl:stylesheet>
