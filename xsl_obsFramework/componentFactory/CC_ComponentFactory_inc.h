
//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// CC_ComponentFactory_inc.h
//
// This an automatically generated file

/**
 * @file CC_ComponentFactory.h 
 * This file defines symbolic names for the components created by the <li>application component factory<li>.
 * For each component created by the application component factory, a symbolic name is provided. 
 * The symbolic name takes the form of an integer constant. This name should be used as an argument
 * in the getter methods of the application component factory (instance of class <code>CC_ComponentFactory</code>).
 * The names of the components are read from the <i>application model</i>. Their symbolic
 * names are constructed as follows: CI_XXX where "XXX" is the component name read from the application
 * model file.
 * <p>
 * This file also defines the symbolic names for the types of the components returned by the application
 * component factory. The symbolic names of the types take the form of an integer constant. 
 * The symbolic name of the type is formed as follows. If the name of the type is TYPE, then its
 * symbolic name is constructed as follows: TN_TYPE. The symbolic names of the types of the
 * application components should not normally be used by an application. They are provided here for future
 * extensions.
 * <p>
 * Finally, this file defines the forward declarations for all the classes from which application components
 * are instantiated.
 * <p>
 * This file was generated automatically by an XSL program that processes the 
 * XML-based application model.
 * @see CC_ComponentFactory
 * @author Automatically Generated File
 */

#ifndef CC_ComponentFactory_inc_H
#define CC_ComponentFactory_inc_H 
    
      
  /**  
   * Sample data pool with full functionality.   
   * This component is instantiated from class <code>DC_SampleFullDataPool</code>.
   * @see DC_SampleFullDataPool 
   */
  const int CI_fullDataPool = 1;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_StuckDataProfile</code>.
   * @see DC_StuckDataProfile 
   */
  const int CI_sdMonProf_1 = 2;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_OutOfRangeProfile</code>.
   * @see DC_OutOfRangeProfile 
   */
  const int CI_orMonProf_1 = 3;
    
      
  /**  
   * Sample application-specific monitoring profile.   
   * This component is instantiated from class <code>DC_SampleMonitoringProfile</code>.
   * @see DC_SampleMonitoringProfile 
   */
  const int CI_sMonProf_1 = 4;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_NullRecoveryAction</code>.
   * @see DC_NullRecoveryAction 
   */
  const int CI_nRecAct_1 = 5;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_OutOfRangeProfile</code>.
   * @see DC_OutOfRangeProfile 
   */
  const int CI_orMonProf_2 = 6;
    
      
  /**  
   * Sample application-specific recovery action.   
   * This component is instantiated from class <code>DC_SampleRecoveryAction</code>.
   * @see DC_SampleRecoveryAction 
   */
  const int CI_sRecAct_2 = 7;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_NullRecoveryAction</code>.
   * @see DC_NullRecoveryAction 
   */
  const int CI_nRecAct_2 = 8;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_StuckDataProfile</code>.
   * @see DC_StuckDataProfile 
   */
  const int CI_sdMonProf_4 = 9;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_OutOfRangeProfile</code>.
   * @see DC_OutOfRangeProfile 
   */
  const int CI_orMonProf_4 = 10;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_NullRecoveryAction</code>.
   * @see DC_NullRecoveryAction 
   */
  const int CI_nRecAct_4 = 11;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_OutOfRangeProfile</code>.
   * @see DC_OutOfRangeProfile 
   */
  const int CI_orMonProf_5 = 12;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_NullRecoveryAction</code>.
   * @see DC_NullRecoveryAction 
   */
  const int CI_nRecAct_5 = 13;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_StuckDataProfile</code>.
   * @see DC_StuckDataProfile 
   */
  const int CI_sdMonProf_7 = 14;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_OutOfRangeProfile</code>.
   * @see DC_OutOfRangeProfile 
   */
  const int CI_orMonProf_7 = 15;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_NullRecoveryAction</code>.
   * @see DC_NullRecoveryAction 
   */
  const int CI_nRecAct_7 = 16;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_OutOfRangeProfile</code>.
   * @see DC_OutOfRangeProfile 
   */
  const int CI_orMonProf_8 = 17;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_NullRecoveryAction</code>.
   * @see DC_NullRecoveryAction 
   */
  const int CI_nRecAct_8 = 18;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_StuckDataProfile</code>.
   * @see DC_StuckDataProfile 
   */
  const int CI_sdMonProf_10 = 19;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_OutOfRangeProfile</code>.
   * @see DC_OutOfRangeProfile 
   */
  const int CI_orMonProf_10 = 20;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_NullRecoveryAction</code>.
   * @see DC_NullRecoveryAction 
   */
  const int CI_nRecAct_10 = 21;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_OutOfRangeProfile</code>.
   * @see DC_OutOfRangeProfile 
   */
  const int CI_orMonProf_11 = 22;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_NullRecoveryAction</code>.
   * @see DC_NullRecoveryAction 
   */
  const int CI_nRecAct_11 = 23;
    
      
  /**  
   * A sample database with intermediate level of robustness against illegal accesses 
   * to database parameters. This database contains real-typed gains.   
   * This component is instantiated from class <code>DC_SampleR2Database</code>.
   * @see DC_SampleR2Database 
   */
  const int CI_parDB = 24;
    
      
  /**  
   * FSM for the sample application class. Top-level FSM that controls nominal 
   * mode operation. To each state of this FSM, a nominal operational 
   * model is associated. To each state, another FSM is attached that 
   * implements the FSM logic of the corresponding nominal mode.   
   * This component is instantiated from class <code>CC_FSM</code>.
   * @see CC_FSM 
   */
  const int CI_Nominal_FSM = 25;
    
      
  /**  
   * FSM for the SBY mode.   
   * This component is instantiated from class <code>DC_NestedFsmActivatorWithEndState</code>.
   * @see DC_NestedFsmActivatorWithEndState 
   */
  const int CI_SBY_FsmState = 26;
    
      
  /**  
   * FsmState component for the SAM mode.   
   * This component is instantiated from class <code>DC_NestedFsmActivatorWithExitCheck</code>.
   * @see DC_NestedFsmActivatorWithExitCheck 
   */
  const int CI_SAM_FsmState = 27;
    
      
  /**  
   * Sample FsmState application class. This FsmState models the SCM mode logic.   
   * This component is instantiated from class <code>DC_SCM_FsmState</code>.
   * @see DC_SCM_FsmState 
   */
  const int CI_SCM_FsmState = 28;
    
      
  /**  
   * Sample FsmState application class. This FsmState models the OCM mode logic.   
   * This component is instantiated from class <code>DC_OCM_FsmState</code>.
   * @see DC_OCM_FsmState 
   */
  const int CI_OCM_FsmState = 29;
    
      
  /**  
   * FsmEvent component triggering transition from SAM to OCM mode.   
   * This component is instantiated from class <code>DC_FromFsmEvent</code>.
   * @see DC_FromFsmEvent 
   */
  const int CI_SAM_to_OCM = 30;
    
      
  /**  
   * FsmEvent component triggering transition from OCM to SAM mode.   
   * This component is instantiated from class <code>DC_FromFsmEvent</code>.
   * @see DC_FromFsmEvent 
   */
  const int CI_OCM_to_SAM = 31;
    
      
  /**  
   * FsmEvent component triggering transition from SCM to SAM mode.   
   * This component is instantiated from class <code>DC_FromFsmEvent</code>.
   * @see DC_FromFsmEvent 
   */
  const int CI_SCM_to_SAM = 32;
    
      
  /**  
   * FsmEvent component triggering transition from SAM to SCM mode.   
   * This component is instantiated from class <code>DC_FromFsmEvent</code>.
   * @see DC_FromFsmEvent 
   */
  const int CI_SAM_to_SCM = 33;
    
      
  /**  
   * FsmEvent component triggering transition from SCM to OCM mode.   
   * This component is instantiated from class <code>DC_FromFsmEvent</code>.
   * @see DC_FromFsmEvent 
   */
  const int CI_SCM_to_OCM = 34;
    
      
  /**  
   * FsmEvent component triggering transition from OCM to SCM mode.   
   * This component is instantiated from class <code>DC_FromFsmEvent</code>.
   * @see DC_FromFsmEvent 
   */
  const int CI_OCM_to_SCM = 35;
    
      
  /**  
   * FSM for the sample application. This FSM models the SBY mode 
   * logic.   
   * This component is instantiated from class <code>CC_FSM</code>.
   * @see CC_FSM 
   */
  const int CI_SBY_FSM = 36;
    
      
  /**  
   * Sample FsmState application class. FsmState component for the SBY preseparation mode.   
   * This component is instantiated from class <code>DC_SBY_PreSepFsmState</code>.
   * @see DC_SBY_PreSepFsmState 
   */
  const int CI_SBY_PreSeparation = 37;
    
      
  /**  
   * Sample FsmState application class. FsmState component for the SBY postseparation mode.   
   * This component is instantiated from class <code>DC_SBY_PostSepFsmState</code>.
   * @see DC_SBY_PostSepFsmState 
   */
  const int CI_SBY_PostSeparation = 38;
    
      
  /**  
   * Dummy FsmState component for the end state of an FSM.   
   * This component is instantiated from class <code>DC_DummyFsmState</code>.
   * @see DC_DummyFsmState 
   */
  const int CI_END = 39;
    
      
  /**  
   * FSM for the sample application. This FSM models the SAM mode 
   * logic.   
   * This component is instantiated from class <code>CC_FSM</code>.
   * @see CC_FSM 
   */
  const int CI_SAM_FSM = 40;
    
      
  /**  
   * FsmState component for the SAM-SunAcquisition submode.   
   * This component is instantiated from class <code>DC_UnstableFsmState</code>.
   * @see DC_UnstableFsmState 
   */
  const int CI_SAM_SunAcquisition = 41;
    
      
  /**  
   * FsmState component for the SAM-SunPointing submode.   
   * This component is instantiated from class <code>DC_DummyFsmState</code>.
   * @see DC_DummyFsmState 
   */
  const int CI_SAM_SunPointing = 42;
    
      
  /**  
   * FSM for the sample application. This FSM models the OCM mode 
   * logic.   
   * This component is instantiated from class <code>CC_FSM</code>.
   * @see CC_FSM 
   */
  const int CI_OCM_FSM = 43;
    
      
  /**  
   * FsmState component for the OCM-Slewing submode.   
   * This component is instantiated from class <code>DC_UnstableFsmState</code>.
   * @see DC_UnstableFsmState 
   */
  const int CI_OCM_Slewing = 44;
    
      
  /**  
   * FsmState component for the OCM-Pointing submode.   
   * This component is instantiated from class <code>DC_DummyFsmState</code>.
   * @see DC_DummyFsmState 
   */
  const int CI_OCM_Pointing = 45;
    
      
  /**  
   * FsmState component for the OCM-Thrusting submode.   
   * This component is instantiated from class <code>DC_DummyFsmState</code>.
   * @see DC_DummyFsmState 
   */
  const int CI_OCM_Thrusting = 46;
    
      
  /**  
   * FSM for the sample application. This FSM models the SCM mode 
   * logic.   
   * This component is instantiated from class <code>CC_FSM</code>.
   * @see CC_FSM 
   */
  const int CI_SCM_FSM = 47;
    
      
  /**  
   * FsmState component for the SCM-Slewing submode.   
   * This component is instantiated from class <code>DC_DummyFsmState</code>.
   * @see DC_DummyFsmState 
   */
  const int CI_SCM_Slewing = 48;
    
      
  /**  
   * FsmState component for the SCM-Pointing submode.   
   * This component is instantiated from class <code>DC_DummyFsmState</code>.
   * @see DC_DummyFsmState 
   */
  const int CI_SCM_Pointing = 49;
    
      
  /**  
   * FsmState component for the SCM-Scanning submode.   
   * This component is instantiated from class <code>DC_DummyFsmState</code>.
   * @see DC_DummyFsmState 
   */
  const int CI_SCM_Scanning = 50;
    
      
  /**  
   * FSM for the sample application class. Top-level FSM that controls survival 
   * mode operation.   
   * This component is instantiated from class <code>CC_FSM</code>.
   * @see CC_FSM 
   */
  const int CI_SM_FSM = 51;
    
      
  /**  
   * Sample FsmState application class. FsmState component for the survival mode pre-separation 
   * submode.   
   * This component is instantiated from class <code>DC_SM_PreSepFsmState</code>.
   * @see DC_SM_PreSepFsmState 
   */
  const int CI_SM_PreSeparation = 52;
    
      
  /**  
   * FsmState component for the survival mode post-separation submode.   
   * This component is instantiated from class <code>DC_UnstableFsmState</code>.
   * @see DC_UnstableFsmState 
   */
  const int CI_SM_PostSeparation = 53;
    
      
  /**  
   * FsmState component for survival mode sun-acquisition submode.   
   * This component is instantiated from class <code>DC_UnstableFsmState</code>.
   * @see DC_UnstableFsmState 
   */
  const int CI_SM_SunAcquisition = 54;
    
      
  /**  
   * FsmState component for survival mode sun-pointing submode.   
   * This component is instantiated from class <code>DC_DummyFsmState</code>.
   * @see DC_DummyFsmState 
   */
  const int CI_SM_SunPointing = 55;
    
      
  /**  
   * FsmEvent component to trigger transition from SM pre- to post-seperation.   
   * This component is instantiated from class <code>DC_FromFsmEvent</code>.
   * @see DC_FromFsmEvent 
   */
  const int CI_SM_PreToPost = 56;
    
      
  /**  
   * FSM for the sample application. This FSM controls FDIR operation.   
   * This component is instantiated from class <code>CC_FSM</code>.
   * @see CC_FSM 
   */
  const int CI_FDIR_FSM = 57;
    
      
  /**  
   * Sample application class. FsmState component representing the AFS state of the 
   * FDIR FSM.   
   * This component is instantiated from class <code>DC_AfsFsmState</code>.
   * @see DC_AfsFsmState 
   */
  const int CI_AFS = 58;
    
      
  /**  
   * FsmState component representing the AFO state of the FDIR FSM.   
   * This component is instantiated from class <code>DC_DummyFsmState</code>.
   * @see DC_DummyFsmState 
   */
  const int CI_AFO = 59;
    
      
  /**  
   * FsmEvent component to trigger a transition from the AFS to AFO 
   * state of the FDIR FSM.   
   * This component is instantiated from class <code>DC_FromFsmEvent</code>.
   * @see DC_FromFsmEvent 
   */
  const int CI_AFS_to_AFO = 60;
    
      
  /**  
   * FsmEvent component to trigger a transition from the AFO to AFS 
   * state of the FDIR FSM.   
   * This component is instantiated from class <code>DC_FromFsmEvent</code>.
   * @see DC_FromFsmEvent 
   */
  const int CI_AFO_to_AFS = 61;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_ControlAction</code>.
   * @see DC_ControlAction 
   */
  const int CI_contAction_1 = 62;
    
      
  /**  
   * Sample control block number 1. This control block has one input 
   * (the speed of reaction wheel 1), one output (the torque of 
   * reaction wheel 1), and one parameter (the gain K1).   
   * This component is instantiated from class <code>DC_SampleControlBlock_1</code>.
   * @see DC_SampleControlBlock_1 
   */
  const int CI_contBlock_1 = 63;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_ControlAction</code>.
   * @see DC_ControlAction 
   */
  const int CI_contAction_2 = 64;
    
      
  /**  
   * Sample control block number 2. This control block has one input 
   * (the speed of reaction wheel 2), one output (the torque of 
   * reaction wheel 2), and one parameter (the gain K2).   
   * This component is instantiated from class <code>DC_SampleControlBlock_2</code>.
   * @see DC_SampleControlBlock_2 
   */
  const int CI_contBlock_2 = 65;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_ControlAction</code>.
   * @see DC_ControlAction 
   */
  const int CI_contAction_3 = 66;
    
      
  /**  
   * Sample control block number 3. This control block has one input 
   * (the speed of reaction wheel 3), one output (the torque of 
   * reaction wheel 3), and one parameter (the gain K3).   
   * This component is instantiated from class <code>DC_SampleControlBlock_3</code>.
   * @see DC_SampleControlBlock_3 
   */
  const int CI_contBlock_3 = 67;
    
      
  /**  
   *    
   * This component is instantiated from class <code>DC_ControlAction</code>.
   * @see DC_ControlAction 
   */
  const int CI_contAction_4 = 68;
    
      
  /**  
   * Sample control block number 4. This control block has one input 
   * (the speed of reaction wheel 4), one output (the torque of 
   * reaction wheel 4), and one parameter (the gain K4).   
   * This component is instantiated from class <code>DC_SampleControlBlock_4</code>.
   * @see DC_SampleControlBlock_4 
   */
  const int CI_contBlock_4 = 69;
    
      
  /**  
   * The OBS Clock of the sample application.   
   * This component is instantiated from class <code>DC_DummyObsClock</code>.
   * @see DC_DummyObsClock 
   */
  const int CI_obsClk = 70;
    
      
  /**  
   * PUS event repository for the sample application.   
   * This component is instantiated from class <code>DC_PUSEventRepository</code>.
   * @see DC_PUSEventRepository 
   */
  const int CI_evtRep = 71;
    
      
  /**  
   * The tracer component of the sample application.   
   * This component is instantiated from class <code>DC_DummyTracer</code>.
   * @see DC_DummyTracer 
   */
  const int CI_tracer = 72;
    
      
  /**  
   *    
   * This component is instantiated from class <code>CC_ManoeuvreManager</code>.
   * @see CC_ManoeuvreManager 
   */
  const int CI_manMan = 73;
    
      
  /**  
   * Sample dummy manoeuvre.   
   * This component is instantiated from class <code>DC_DummyManoeuvre</code>.
   * @see DC_DummyManoeuvre 
   */
  const int CI_man_1 = 74;
    
      
  /**  
   * Sample configurable dummy manoeuvre.   
   * This component is instantiated from class <code>DC_DummyConfigurableManoeuvre</code>.
   * @see DC_DummyConfigurableManoeuvre 
   */
  const int CI_man_2 = 75;
    
      
  /**  
   * Sample configurable dummy manoeuvre.   
   * This component is instantiated from class <code>DC_TestPUSConfigurableManoeuvre</code>.
   * @see DC_TestPUSConfigurableManoeuvre 
   */
  const int CI_man_3 = 76;
    
      
  /**  
   * Sample telecommand manager.   
   * This component is instantiated from class <code>CC_TelecommandManager</code>.
   * @see CC_TelecommandManager 
   */
  const int CI_tcMan = 77;
    
      
  /**  
   * Sample telecommand loader.   
   * This component is instantiated from class <code>DC_BasicPUSTcLoader</code>.
   * @see DC_BasicPUSTcLoader 
   */
  const int CI_tcLoader = 78;
    
      
  /**  
   * Sample dummy telecommand.   
   * This component is instantiated from class <code>DC_DummyTelecommand</code>.
   * @see DC_DummyTelecommand 
   */
  const int CI_tc_1 = 79;
    
      
  /**  
   * Sample dummy telecommand.   
   * This component is instantiated from class <code>DC_DummyTelecommand</code>.
   * @see DC_DummyTelecommand 
   */
  const int CI_tc_2 = 80;
    
      
  /**  
   * Sample PUS dummy telecommand.   
   * This component is instantiated from class <code>DC_DummyPUSTelecommand</code>.
   * @see DC_DummyPUSTelecommand 
   */
  const int CI_tc_3 = 81;
    
      
  /**  
   * Sample PUSDefineDataReporting telecommand.   
   * This component is instantiated from class <code>DC_PUSDefineDataReporting</code>.
   * @see DC_PUSDefineDataReporting 
   */
  const int CI_tc_4 = 82;
    
      
  /**  
   * Sample PUSControlDataReporting telecommand.   
   * This component is instantiated from class <code>DC_PUSControlDataReporting</code>.
   * @see DC_PUSControlDataReporting 
   */
  const int CI_tc_5 = 83;
    
      
  /**  
   * Sample test PUS telecommand.   
   * This component is instantiated from class <code>DC_TestPUSTelecommand</code>.
   * @see DC_TestPUSTelecommand 
   */
  const int CI_tc_6 = 84;
    
      
  /**  
   * Sample test PUS telecommand.   
   * This component is instantiated from class <code>DC_TestPUSTelecommand</code>.
   * @see DC_TestPUSTelecommand 
   */
  const int CI_tc_7 = 85;
    
      
  /**  
   * Sample test PUS telecommand.   
   * This component is instantiated from class <code>DC_TestPUSTelecommand</code>.
   * @see DC_TestPUSTelecommand 
   */
  const int CI_tc_8 = 86;
    
      
  /**  
   * Sample PUS memory dump telecommand with absolute addresses.   
   * This component is instantiated from class <code>DC_PUSDumpMemoryAbsolute</code>.
   * @see DC_PUSDumpMemoryAbsolute 
   */
  const int CI_tc_9 = 87;
    
      
  /**  
   * Sample PUS memory dump telecommand with offset.   
   * This component is instantiated from class <code>DC_PUSDumpMemoryOffset</code>.
   * @see DC_PUSDumpMemoryOffset 
   */
  const int CI_tc_10 = 88;
    
      
  /**  
   * Sample PUS memory load telecommand with absolute addresses.   
   * This component is instantiated from class <code>DC_PUSMemoryLoadAbsolute</code>.
   * @see DC_PUSMemoryLoadAbsolute 
   */
  const int CI_tc_11 = 89;
    
      
  /**  
   * Sample PUS memory load telecommand with absolute addresses.   
   * This component is instantiated from class <code>DC_PUSMemoryLoadAbsolute</code>.
   * @see DC_PUSMemoryLoadAbsolute 
   */
  const int CI_tc_12 = 90;
    
      
  /**  
   * Sample PUS memory load telecommand with offset addresses.   
   * This component is instantiated from class <code>DC_PUSMemoryLoadOffset</code>.
   * @see DC_PUSMemoryLoadOffset 
   */
  const int CI_tc_13 = 91;
    
      
  /**  
   * Sample telemetry manager.   
   * This component is instantiated from class <code>CC_TelemetryManager</code>.
   * @see CC_TelemetryManager 
   */
  const int CI_tmMan = 92;
    
      
  /**  
   * Sample telemetry stream.   
   * This component is instantiated from class <code>DC_BasicPUSTmStream</code>.
   * @see DC_BasicPUSTmStream 
   */
  const int CI_tmStream = 93;
    
      
  /**  
   * A dummy PUS telemetry packet.   
   * This component is instantiated from class <code>DC_DummyPUSTelemetryPacket</code>.
   * @see DC_DummyPUSTelemetryPacket 
   */
  const int CI_tm_1 = 94;
    
      
  /**  
   * A dummy PUS telemetry packet.   
   * This component is instantiated from class <code>DC_DummyPUSTelemetryPacket</code>.
   * @see DC_DummyPUSTelemetryPacket 
   */
  const int CI_tm_2 = 95;
    
      
  /**  
   * A TC verification telemetry packet for the sample application.   
   * This component is instantiated from class <code>DC_PUSTcVerificationPacket</code>.
   * @see DC_PUSTcVerificationPacket 
   */
  const int CI_tm_3 = 96;
    
      
  /**  
   * A data reporting packet with large capacity for the sample application.   
   * This component is instantiated from class <code>DC_PUSDataReportingPacket</code>.
   * @see DC_PUSDataReportingPacket 
   */
  const int CI_tm_4 = 97;
    
      
  /**  
   * A data reporting packet with small capacity for the sample application.   
   * This component is instantiated from class <code>DC_PUSDataReportingPacket</code>.
   * @see DC_PUSDataReportingPacket 
   */
  const int CI_tm_5 = 98;
    
      
  /**  
   * A memory dump absolute telemetry packet for the sample application.   
   * This component is instantiated from class <code>DC_PUSMemoryDumpAbsolute</code>.
   * @see DC_PUSMemoryDumpAbsolute 
   */
  const int CI_tm_6 = 99;
    
      
  /**  
   * A memory dump offset telemetry packet for the sample application.   
   * This component is instantiated from class <code>DC_PUSMemoryDumpOffset</code>.
   * @see DC_PUSMemoryDumpOffset 
   */
  const int CI_tm_7 = 100;
    
      
  /**  
   * The PUS telemetry mode manager for the sample application.   
   * This component is instantiated from class <code>DC_PUSTelemetryModeManager</code>.
   * @see DC_PUSTelemetryModeManager 
   */
  const int CI_tmModeMan = 101;


   // Now define the symbolic names for the types  
   const int TN_ControlAction = 1;  
   const int TN_SampleControlBlock_1 = 5;  
   const int TN_SampleControlBlock_2 = 6;  
   const int TN_SampleControlBlock_3 = 7;  
   const int TN_SampleControlBlock_4 = 8;  
   const int TN_SampleFullDataPool = 9;  
   const int TN_SampleR2Database = 10;  
   const int TN_PUSEventRepository = 11;  
   const int TN_NullRecoveryAction = 12;  
   const int TN_OutOfRangeProfile = 20;  
   const int TN_SampleMonitoringProfile = 28;  
   const int TN_SampleRecoveryAction = 29;  
   const int TN_StuckDataProfile = 30;  
   const int TN_FSM = 34;  
   const int TN_AfsFsmState = 41;  
   const int TN_DummyFsmState = 42;  
   const int TN_FromFsmEvent = 51;  
   const int TN_NestedFsmActivatorWithEndState = 60;  
   const int TN_NestedFsmActivatorWithExitCheck = 61;  
   const int TN_OCM_FsmState = 62;  
   const int TN_SBY_PostSepFsmState = 63;  
   const int TN_SBY_PreSepFsmState = 64;  
   const int TN_SCM_FsmState = 65;  
   const int TN_SM_PreSepFsmState = 66;  
   const int TN_UnstableFsmState = 67;  
   const int TN_ManoeuvreManager = 71;  
   const int TN_DummyConfigurableManoeuvre = 72;  
   const int TN_DummyManoeuvre = 73;  
   const int TN_TestPUSConfigurableManoeuvre = 74;  
   const int TN_DummyObsClock = 75;  
   const int TN_DummyTracer = 76;  
   const int TN_TelecommandManager = 77;  
   const int TN_BasicPUSTcLoader = 78;  
   const int TN_DummyPUSTelecommand = 79;  
   const int TN_DummyTelecommand = 80;  
   const int TN_PUSControlDataReporting = 82;  
   const int TN_PUSDefineDataReporting = 83;  
   const int TN_PUSDumpMemoryAbsolute = 84;  
   const int TN_PUSDumpMemoryOffset = 85;  
   const int TN_PUSMemoryLoadAbsolute = 86;  
   const int TN_PUSMemoryLoadOffset = 88;  
   const int TN_TestPUSTelecommand = 89;  
   const int TN_TelemetryManager = 92;  
   const int TN_BasicPUSTmStream = 93;  
   const int TN_DummyPUSTelemetryPacket = 94;  
   const int TN_PUSDataReportingPacket = 96;  
   const int TN_PUSMemoryDumpAbsolute = 98;  
   const int TN_PUSMemoryDumpOffset = 99;  
   const int TN_PUSTcVerificationPacket = 100;  
   const int TN_PUSTelemetryModeManager = 101;  

   // Now define the forward declarations for the types   
   class DC_ControlAction;  
   class DC_SampleControlBlock_1;  
   class DC_SampleControlBlock_2;  
   class DC_SampleControlBlock_3;  
   class DC_SampleControlBlock_4;  
   class DC_SampleFullDataPool;  
   class DC_SampleR2Database;  
   class DC_PUSEventRepository;  
   class DC_NullRecoveryAction;  
   class DC_OutOfRangeProfile;  
   class DC_SampleMonitoringProfile;  
   class DC_SampleRecoveryAction;  
   class DC_StuckDataProfile;  
   class CC_FSM;  
   class DC_AfsFsmState;  
   class DC_DummyFsmState;  
   class DC_FromFsmEvent;  
   class DC_NestedFsmActivatorWithEndState;  
   class DC_NestedFsmActivatorWithExitCheck;  
   class DC_OCM_FsmState;  
   class DC_SBY_PostSepFsmState;  
   class DC_SBY_PreSepFsmState;  
   class DC_SCM_FsmState;  
   class DC_SM_PreSepFsmState;  
   class DC_UnstableFsmState;  
   class CC_ManoeuvreManager;  
   class DC_DummyConfigurableManoeuvre;  
   class DC_DummyManoeuvre;  
   class DC_TestPUSConfigurableManoeuvre;  
   class DC_DummyObsClock;  
   class DC_DummyTracer;  
   class CC_TelecommandManager;  
   class DC_BasicPUSTcLoader;  
   class DC_DummyPUSTelecommand;  
   class DC_DummyTelecommand;  
   class DC_PUSControlDataReporting;  
   class DC_PUSDefineDataReporting;  
   class DC_PUSDumpMemoryAbsolute;  
   class DC_PUSDumpMemoryOffset;  
   class DC_PUSMemoryLoadAbsolute;  
   class DC_PUSMemoryLoadOffset;  
   class DC_TestPUSTelecommand;  
   class CC_TelemetryManager;  
   class DC_BasicPUSTmStream;  
   class DC_DummyPUSTelemetryPacket;  
   class DC_PUSDataReportingPacket;  
   class DC_PUSMemoryDumpAbsolute;  
   class DC_PUSMemoryDumpOffset;  
   class DC_PUSTcVerificationPacket;  
   class DC_PUSTelemetryModeManager;  



#endif
