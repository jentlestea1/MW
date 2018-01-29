<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2004 P&P Software GmbH                                                                                  -->
<!--================================================================-->

<!--===================================================================
This rule writes out the configuration code for the FSM, the FsmEvent and the 
FsmState elements of  an application model. This rule does not write out the
statement to reset an FSM. This is because this should only be done after all
 FSMs and FsmStates have been configured.
===================================================================-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
      <xsl:strip-space elements="*"/>
      <xsl:output omit-xml-declaration="yes" method="text"/>

      <xsl:template match="FSM">

          <!-- Configure the FsmEvents attached to this FSM -->
           <xsl:apply-templates select="FsmEvent" mode="FsmConfiguration"/>
          
          <!-- Configure the FsmStates  attached to this FSM -->
           <xsl:apply-templates select="FsmState" mode="FsmConfiguration"/>
          
           <xsl:variable name="fsm" select="@name"/>
           <xsl:variable name="type" select="@type"/>
           <xsl:variable name="classType" select="substring-after($type,'/')"/>
<xsl:text>
   </xsl:text>// ---- Configure the FSM "<xsl:value-of select="$fsm"/>" ----
<xsl:text/>
<xsl:text>   </xsl:text>
           <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$fsm"/>)->setNumberOfStates(<xsl:value-of select="count(FsmState)"/>);
<xsl:text/>

           <!-- Set the initial enable status -->
           <xsl:if test="InitialEnableStatus">
                 <xsl:choose>
                       <xsl:when test="@value='ENABLED'">
                           <xsl:text>   </xsl:text>
                           <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$fsm"/>)->setInitialEnabledStatus(true);
<xsl:text/>
                       </xsl:when>
                       <xsl:when test="@value='DISABLED'">
                           <xsl:text>   </xsl:text>
                           <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$fsm"/>)->setInitialEnabledStatus(false);
<xsl:text/>
                       </xsl:when>
                       <xsl:otherwise>
                       -- FSM Configuration Error: illegal value for the initial enabled status of an FSM
                       </xsl:otherwise>
                 </xsl:choose>
           </xsl:if>

            <!-- Load the FsmState into the FSM -->
            <xsl:for-each select="FsmState/Index">
                <xsl:text>   </xsl:text>
                <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$fsm"/>)->setState(<xsl:value-of select="@value"/>,<xsl:value-of select="../*[@kind='component']/@name"/>);
<xsl:text/>
            </xsl:for-each>

      </xsl:template>

      <!-- ====================================================================== -->

      <xsl:template match="FsmState" mode="FsmConfiguration">
      
            <!-- Construct the name of the fsmState -->
            <xsl:variable name="fsmState" select="*[@kind='component']/@name"/>
            <xsl:variable name="type" select="*[@kind='component']/@type"/>
            <xsl:variable name="classType" select="substring-after($type,'/')"/>
           
<xsl:text>
   </xsl:text>// ---- Configuration of FsmState "<xsl:value-of select="$fsmState"/>" ----  
<xsl:text/>
           <xsl:if test="InitialEnableStatus">
                 <xsl:choose>
                       <xsl:when test="@value='ENABLED'">
                           <xsl:text>   </xsl:text>
                           <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$fsmState"/>)->setInitialEnabledStatus(true);
<xsl:text/>
                       </xsl:when>
                       <xsl:when test="@value='DISABLED'">
                           <xsl:text>   </xsl:text>
                           <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$fsmState"/>)->setInitialEnabledStatus(false);
<xsl:text/>
                       </xsl:when>
                       <xsl:otherwise>
                       -- FsmState Configuration Error: illegal value for the initial enabled status of an FSM
<xsl:text/>
                       </xsl:otherwise>
                 </xsl:choose>
           </xsl:if>

            <!-- Set the target FsmState (NB: the argument of the setter method is the index of the target FsmState, not the FsmState component itself)
                   This rule was designed for FsmStates of type DC_NestedFsmActivatorWithEndState and DC_NestedFsmActivatorWithExitCheck -->
            <xsl:variable name="targetStateName" select=".//TargetFsmState/@value"/>
            <xsl:if test="$targetStateName">
                <xsl:variable name="targetFSM" select=".//NestedFSM/@value"/>
                <xsl:variable name="targetStateIndex" select="//FSM[@name=$targetFSM]/FsmState[*/@name=$targetStateName]/Index/@value"/>
                <xsl:text>   </xsl:text>
                <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$fsmState"/>)->setTargetState(<xsl:value-of select="$targetStateIndex"/>);
<xsl:text/>
            <xsl:text/>
            </xsl:if>
            
            <!-- Set the property values (except the target state which is already set) -->
            <xsl:for-each select=".//*[@kind='property'][@name][not(@name='TargetState')]">
                <xsl:text>   </xsl:text>
                <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$fsmState"/>)->set<xsl:value-of select="@name"/>(<xsl:value-of select="@value"/>);
<xsl:text/>
            </xsl:for-each>

      </xsl:template>            
      
      <!-- ====================================================================== -->

      <xsl:template match="FsmEvent" mode="FsmConfiguration">
      
            <!-- Construct the name of the fsmEvent -->
            <xsl:variable name="fsmEvent" select="*[@kind='component']/@name"/>
            <xsl:variable name="type" select="*[@kind='component']/@type"/>
            <xsl:variable name="classType" select="substring-after($type,'/')"/>
           
<xsl:text>
   </xsl:text>// ---- Configuration of FsmEvent "<xsl:value-of select="$fsmEvent"/>" ---- 
<xsl:text/>
           <xsl:if test="InitialEnableStatus">
                 <xsl:choose>
                       <xsl:when test="@value='ENABLED'">
                           <xsl:text>   </xsl:text>
                           <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$fsmEvent"/>)->setInitialEnabledStatus(true);
<xsl:text/>
                       </xsl:when>
                       <xsl:when test="@value='DISABLED'">
                           <xsl:text>   </xsl:text>
                           <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$fsmEvent"/>)->setInitialEnabledStatus(false);
<xsl:text/>
                       </xsl:when>
                       <xsl:otherwise>
                       -- FsmEvent Configuration Error: illegal value for the initial enabled status of an FSM
<xsl:text/>
                       </xsl:otherwise>
                 </xsl:choose>
           </xsl:if>

            <!-- Set the target FSM -->
            <xsl:variable name="fsm" select="../@name"/>
            <xsl:text>   </xsl:text>
            <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$fsmEvent"/>)->setTargetFsm(<xsl:value-of select="$fsm"/>);  
<xsl:text/>
            
            
            <!-- Set the target FsmState (NB: the argument of the setter method is the index of the target FsmState, not the FsmState component itself) -->
            <xsl:variable name="targetStateName" select="TargetState/@value"/>
            <xsl:variable name="targetStateIndex" select="../FsmState[*/@name=$targetStateName]/Index/@value"/>
            <xsl:text>   </xsl:text>
            <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$fsmEvent"/>)->setTargetState(<xsl:value-of select="$targetStateIndex"/>);
<xsl:text/>
            <xsl:text/>
            
            <!-- Set the starting FsmState (NB: the argument of the setter method is the index of the starting FsmState, not the FsmState component itself) -->
            <xsl:if test=".//FromFsmState">
                <xsl:variable name="fromStateName" select=".//FromFsmState/@value"/>
                <xsl:variable name="fromStateIndex" select="../FsmState[*/@name=$fromStateName]/Index/@value"/>
                <xsl:text>   </xsl:text>
                <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$fsmEvent"/>)->setStartingState(<xsl:value-of select="$fromStateIndex"/>);
<xsl:text/>
            </xsl:if>
            <xsl:text/>
            
            <!-- Set the property values (except the target and starting states which are already set) -->
            <xsl:for-each select=".//*[@kind='property'][@name][not(@name='TargetState') and not(@name='StartingState')]">
                <xsl:text>   </xsl:text>
                <xsl:value-of select="translate($classType,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>_GET_CLASS(<xsl:value-of select="$fsmEvent"/>)->set<xsl:value-of select="@name"/>(<xsl:value-of select="@value"/>);
<xsl:text/>
            </xsl:for-each>

      </xsl:template>            
      
</xsl:stylesheet>
