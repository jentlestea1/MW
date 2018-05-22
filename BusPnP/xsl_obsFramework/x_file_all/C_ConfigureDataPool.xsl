<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2004 P&P Software GmbH                                                                                  -->
<!--================================================================-->

<!--===================================================================
This rule writes out the configuration code for a DataPool component of  an application model.
===================================================================-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
      <xsl:strip-space elements="*"/>
      <xsl:output omit-xml-declaration="yes" method="text"/>

      <xsl:template match="DataPool">

          <!-- Configure the Monitoring Profiles attached to this data pool (assuming that
                  the only configuration action is setting property values) -->
           <xsl:for-each select=".//MonitoringProfile">
                 <xsl:variable name="monProf" select="*[(@kind='component') and (@name)]/@name"/>
                 <xsl:for-each select=".//*[@kind='property'][@name]"><xsl:text>
   </xsl:text><xsl:value-of select="$monProf"/>->set<xsl:value-of select="@name"/>(<xsl:value-of select="@value"/>);<xsl:text/>
                  </xsl:for-each>
           </xsl:for-each>
          
          <!-- Configure the Recvery Actions attached to this data pool (assuming that
                  the only configuration action is setting property values) -->
           <xsl:for-each select=".//RecoveryAction"><xsl:text>
                 </xsl:text>
                 <xsl:variable name="recAct" select="*[(@kind='component') and (@name)]/@name"/>
                 <xsl:for-each select=".//*[@kind='property'][@name]"><xsl:text>
   </xsl:text><xsl:value-of select="$recAct"/>->set<xsl:value-of select="@name"/>(<xsl:value-of select="@value"/>);<xsl:text/>
                  </xsl:for-each>
           </xsl:for-each>
          
           <xsl:variable name="dataPool" select="*[(@kind='component') and (@name)]/@name"/>

            <!-- Set the properties of the data pool (the only property is associated to the time stamp) -->
            <xsl:if test=".//TimeStamp"><xsl:text>
   </xsl:text>// Set the properties of the data pool<xsl:text/>
                  <xsl:for-each select=".//TimeStamp//*[@kind='property'][@name]"><xsl:text>
   </xsl:text><xsl:value-of select="$dataPool"/>->set<xsl:value-of select="@name"/>(<xsl:value-of select="@value"/>);
                  </xsl:for-each>
            </xsl:if>
   
            <!-- Configure the data items -->
            <xsl:for-each select=".//DataPoolItem"><xsl:text>
                  
   </xsl:text>// ---- Configuration of data pool item  "<xsl:value-of select="Name/@value"/>" ---- <xsl:text/> 
                  <xsl:call-template name="loadMonitoringProfile">
                        <xsl:with-param name="dataPool" select="$dataPool"/>
                  </xsl:call-template>
                  <xsl:call-template name="loadRecoveryAction">
                        <xsl:with-param name="dataPool" select="$dataPool"/>
                  </xsl:call-template>
            </xsl:for-each>
            
      </xsl:template>

      <!-- ====================================================================== -->

      <xsl:template name="loadMonitoringProfile">
            <xsl:param name="dataPool"/>
            
            <!-- if there is more than one monitoring profiles, link them together -->
            <xsl:if test="count(MonitoringProfile)>1">
                  <xsl:for-each select="MonitoringProfile">
                        <xsl:variable name="pos" select="position()"/>
                        <xsl:if test="not(position()=last())">
                              <xsl:variable name="current" select="*[(@kind='component') and (@name)]/@name"/>
                              <xsl:variable name="next" select="../MonitoringProfile[position()=number($pos+1)]/*[(@kind='component') and (@name)]/@name"/><xsl:text>
   </xsl:text><xsl:value-of select="$current"/>->setNextMonitoringProfile(<xsl:value-of select="$next"/>);<xsl:text/>
                        </xsl:if>
                  </xsl:for-each>
            </xsl:if>
            
            <!-- attach the first monitoring profile to the data item -->
            <xsl:variable name="dataItemID" select="Name/@value"/><xsl:text>
   </xsl:text><xsl:value-of select="$dataPool"/>->setMonitoringProfile(DP_<xsl:value-of select="$dataItemID"/>,<xsl:value-of 
                                                            select="MonitoringProfile[position()=1]/*[(@kind='component') and (@name)]/@name"/>);<xsl:text/>
            
      </xsl:template>            
      
      <!-- ====================================================================== -->

      <xsl:template name="loadRecoveryAction">
            <xsl:param name="dataPool"/>
            
            <!-- if there is more than one recovery action, link them together -->
            <xsl:if test="count(RecoveryAction)>1">
                  <xsl:for-each select="RecoveryAction">
                        <xsl:variable name="pos" select="position()"/>
                        <xsl:if test="not(position()=last())">
                              <xsl:variable name="current" select="*[(@kind='component') and (@name)]/@name"/>
                              <xsl:variable name="next" select="../RecoveryAction[position()=number($pos+1)]/*[(@kind='component') and (@name)]/@name"/><xsl:text>
   </xsl:text><xsl:value-of select="$current"/>->setNextRecoveryAction(<xsl:value-of select="$next"/>);<xsl:text/>
                        </xsl:if>
                  </xsl:for-each>
            </xsl:if>
            
            <!-- attach the first RecoveryAction to the data item -->
            <xsl:variable name="dataItemID" select="Name/@value"/><xsl:text>
   </xsl:text><xsl:value-of select="$dataPool"/>->setRecoveryAction(DP_<xsl:value-of select="$dataItemID"/>,<xsl:value-of 
                                                            select="RecoveryAction[position()=1]/*[(@kind='component') and (@name)]/@name"/>);<xsl:text/>
            
      </xsl:template>            
      
</xsl:stylesheet>
