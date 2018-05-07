
//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// CC_ComponentFactory.c
//
// This file was automatically generated by an XSL program

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "CC_ComponentFactory_inc.h"
#include "CC_ComponentFactory.h"
#include "../Base/CC_RootObject.h"   


#include "../Data/DC_ControlAction.h"        
#include "../Data/DC_SampleControlBlock_1.h"        
#include "../Data/DC_SampleControlBlock_2.h"        
#include "../Data/DC_SampleControlBlock_3.h"        
#include "../Data/DC_SampleControlBlock_4.h"        
#include "../Data/DC_SampleFullDataPool.h"        
#include "../Data/DC_SampleR2Database.h"        
#include "../Event/DC_PUSEventRepository.h"        
#include "../FDIR/DC_NullRecoveryAction.h"        
#include "../FDIR/DC_OutOfRangeProfile.h"        
#include "../FDIR/DC_SampleMonitoringProfile.h"        
#include "../FDIR/DC_SampleRecoveryAction.h"        
#include "../FDIR/DC_StuckDataProfile.h"        
#include "../FSM/CC_FSM.h"        
#include "../FSM/DC_AfsFsmState.h"        
#include "../FSM/DC_DummyFsmState.h"        
#include "../FSM/DC_FromFsmEvent.h"        
#include "../FSM/DC_NestedFsmActivatorWithEndState.h"        
#include "../FSM/DC_NestedFsmActivatorWithExitCheck.h"        
#include "../FSM/DC_OCM_FsmState.h"        
#include "../FSM/DC_SBY_PostSepFsmState.h"        
#include "../FSM/DC_SBY_PreSepFsmState.h"        
#include "../FSM/DC_SCM_FsmState.h"        
#include "../FSM/DC_SM_PreSepFsmState.h"        
#include "../FSM/DC_UnstableFsmState.h"        
#include "../Manoeuvre/CC_ManoeuvreManager.h"        
#include "../Manoeuvre/DC_DummyConfigurableManoeuvre.h"        
#include "../Manoeuvre/DC_DummyManoeuvre.h"        
#include "../Manoeuvre/DC_TestPUSConfigurableManoeuvre.h"        
#include "../System/DC_DummyObsClock.h"        
#include "../System/DC_DummyTracer.h"        
#include "../Telecommand/CC_TelecommandManager.h"        
#include "../Telecommand/DC_BasicPUSTcLoader.h"        
#include "../Telecommand/DC_DummyPUSTelecommand.h"        
#include "../Telecommand/DC_DummyTelecommand.h"        
#include "../Telecommand/DC_PUSControlDataReporting.h"        
#include "../Telecommand/DC_PUSDefineDataReporting.h"        
#include "../Telecommand/DC_PUSDumpMemoryAbsolute.h"        
#include "../Telecommand/DC_PUSDumpMemoryOffset.h"        
#include "../Telecommand/DC_PUSMemoryLoadAbsolute.h"        
#include "../Telecommand/DC_PUSMemoryLoadOffset.h"        
#include "../Telecommand/DC_TestPUSTelecommand.h"        
#include "../Telemetry/CC_TelemetryManager.h"        
#include "../Telemetry/DC_BasicPUSTmStream.h"        
#include "../Telemetry/DC_DummyPUSTelemetryPacket.h"        
#include "../Telemetry/DC_PUSDataReportingPacket.h"        
#include "../Telemetry/DC_PUSMemoryDumpAbsolute.h"        
#include "../Telemetry/DC_PUSMemoryDumpOffset.h"        
#include "../Telemetry/DC_PUSTcVerificationPacket.h"        
#include "../Telemetry/DC_PUSTelemetryModeManager.h"        

// Disable type mismatch warning that arise when calling
// the configuration methods on monitoring profiles
#pragma warning( disable : 4305 )



// Create the parameter database storage areas. In an operational
// context the two pointers should be made to point to the database
// operational and default tables. The names of the pointers must 
// match the names in the parameter database application models.
char* PARDATABASE_OP_TABLE_START = (char*)malloc(50*sizeof(char));
char* PARDATABASE_DEF_TABLE_START = (char*)malloc(50*sizeof(char));

// Create the telecommand storage area. In an operational setting,
// this should be linked to the area where TCs are written. The name
// used here must match the name used in the telecommand loader model and
// the size of the allocated memory should be consistent with the configuration
// parameters of the telecommand loader.
unsigned char* TC_LOADER_AREA_START = new unsigned char[1000];

// Create the telemetry storage area. In an operational setting,
// this should be linked to the area from where TMs are read. The name
// used here must match the name used in the telemetry stream model and
// the size of the allocated memory should be consistent with the configuration
// parameters of the telemetry stream.

unsigned char* TM_STREAM_START = (unsigned char*)malloc(5000*sizeof(unsigned char));

///////////////////////////////////////////////////////////////////////////////
//
//                            class data
//
///////////////////////////////////////////////////////////////////////////////


CC_ComponentFactory* pInstance = pNULL;


///////////////////////////////////////////////////////////////////////////////
//
//                            class  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////


CC_ComponentFactory* CC_ComponentFactory_getInstance(void) {
   if (pInstance==pNULL)
      pInstance = CC_ComponentFactory_new();
   return pInstance;
}


///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////



void CC_ComponentFactory_configureApplication(CC_ComponentFactory *this) {

   CC_ComponentFactory_configureRootObject(this);
   CC_ComponentFactory_configureEventRepository(this);
   CC_ComponentFactory_configureObsClock(this);
   CC_ComponentFactory_configureDataPool(this);
   CC_ComponentFactory_configureParameterDatabase(this);
   CC_ComponentFactory_configureFSM(this);
   CC_ComponentFactory_configureFunctionalityManagers(this);
   CC_ComponentFactory_configureControllers(this);
   }

void CC_ComponentFactory_configureRootObject(CC_ComponentFactory *this) {
   

   // Load the event repository
   CC_RootObject_setEventRepository(evtRep);

   // Load the parameter database
   CC_RootObject_setParameterDatabase(parDB);
           
   // Load the datapool
   CC_RootObject_setDataPool(fullDataPool);

   // Load the tracer
   CC_RootObject_setTracer(tracer);

      
}


void CC_ComponentFactory_configureObsClock(CC_ComponentFactory *this) {
   
   // ---- Configure the OBS Clock "obsClk" ----
   DC_DUMMYOBSCLOCK_GET_CLASS(obsClk)->setTime(10);
   DC_DUMMYOBSCLOCK_GET_CLASS(obsClk)->setCycle(20);

}

void CC_ComponentFactory_configureEventRepository(CC_ComponentFactory *this) {
   
   // ---- Configure the event repository "evtRep" ----
   DC_PUSEVENTREPOSITORY_GET_CLASS(evtRep)->setRepositorySize(10);
   DC_PUSEVENTREPOSITORY_GET_CLASS(evtRep)->setObsClock(obsClk);
   DC_PUSEVENTREPOSITORY_GET_CLASS(evtRep)->setTelemetryManager(tmMan);
   DC_PUSEVENTREPOSITORY_GET_CLASS(evtRep)->setEnabled(ENABLED);

}

void CC_ComponentFactory_configureFSM(CC_ComponentFactory *this) {
   
   // ---- Configuration of FsmEvent "SAM_to_OCM" ---- 
   DC_FROMFSMEVENT_GET_CLASS(SAM_to_OCM)->setTargetFsm(Nominal_FSM);  
   DC_FROMFSMEVENT_GET_CLASS(SAM_to_OCM)->setTargetState(3);
   DC_FROMFSMEVENT_GET_CLASS(SAM_to_OCM)->setStartingState(1);

   // ---- Configuration of FsmEvent "OCM_to_SAM" ---- 
   DC_FROMFSMEVENT_GET_CLASS(OCM_to_SAM)->setTargetFsm(Nominal_FSM);  
   DC_FROMFSMEVENT_GET_CLASS(OCM_to_SAM)->setTargetState(1);
   DC_FROMFSMEVENT_GET_CLASS(OCM_to_SAM)->setStartingState(3);

   // ---- Configuration of FsmEvent "SCM_to_SAM" ---- 
   DC_FROMFSMEVENT_GET_CLASS(SCM_to_SAM)->setTargetFsm(Nominal_FSM);  
   DC_FROMFSMEVENT_GET_CLASS(SCM_to_SAM)->setTargetState(1);
   DC_FROMFSMEVENT_GET_CLASS(SCM_to_SAM)->setStartingState(2);

   // ---- Configuration of FsmEvent "SAM_to_SCM" ---- 
   DC_FROMFSMEVENT_GET_CLASS(SAM_to_SCM)->setTargetFsm(Nominal_FSM);  
   DC_FROMFSMEVENT_GET_CLASS(SAM_to_SCM)->setTargetState(2);
   DC_FROMFSMEVENT_GET_CLASS(SAM_to_SCM)->setStartingState(1);

   // ---- Configuration of FsmEvent "SCM_to_OCM" ---- 
   DC_FROMFSMEVENT_GET_CLASS(SCM_to_OCM)->setTargetFsm(Nominal_FSM);  
   DC_FROMFSMEVENT_GET_CLASS(SCM_to_OCM)->setTargetState(3);
   DC_FROMFSMEVENT_GET_CLASS(SCM_to_OCM)->setStartingState(2);

   // ---- Configuration of FsmEvent "OCM_to_SCM" ---- 
   DC_FROMFSMEVENT_GET_CLASS(OCM_to_SCM)->setTargetFsm(Nominal_FSM);  
   DC_FROMFSMEVENT_GET_CLASS(OCM_to_SCM)->setTargetState(2);
   DC_FROMFSMEVENT_GET_CLASS(OCM_to_SCM)->setStartingState(3);

   // ---- Configuration of FsmState "SBY_FsmState" ----  
   DC_NESTEDFSMACTIVATORWITHENDSTATE_GET_CLASS(SBY_FsmState)->setTargetState(2);
   DC_NESTEDFSMACTIVATORWITHENDSTATE_GET_CLASS(SBY_FsmState)->setNextState(SAM_FsmState);
   DC_NESTEDFSMACTIVATORWITHENDSTATE_GET_CLASS(SBY_FsmState)->setTargetFsm(SBY_FSM);

   // ---- Configuration of FsmState "SAM_FsmState" ----  
   DC_NESTEDFSMACTIVATORWITHEXITCHECK_GET_CLASS(SAM_FsmState)->setTargetState(1);
   DC_NESTEDFSMACTIVATORWITHEXITCHECK_GET_CLASS(SAM_FsmState)->setTargetFsm(SAM_FSM);

   // ---- Configuration of FsmState "SCM_FsmState" ----  
   DC_SCM_FSMSTATE_GET_CLASS(SCM_FsmState)->setNextState(SAM_FsmState);

   // ---- Configuration of FsmState "OCM_FsmState" ----  
   DC_OCM_FSMSTATE_GET_CLASS(OCM_FsmState)->setNextState(SAM_FsmState);

   // ---- Configure the FSM "Nominal_FSM" ----
   CC_FSM_GET_CLASS(Nominal_FSM)->setNumberOfStates(4);
   CC_FSM_GET_CLASS(Nominal_FSM)->setState(0,SBY_FsmState);
   CC_FSM_GET_CLASS(Nominal_FSM)->setState(1,SAM_FsmState);
   CC_FSM_GET_CLASS(Nominal_FSM)->setState(2,SCM_FsmState);
   CC_FSM_GET_CLASS(Nominal_FSM)->setState(3,OCM_FsmState);

   // ---- Configuration of FsmState "SBY_PreSeparation" ----  
   DC_SBY_PRESEPFSMSTATE_GET_CLASS(SBY_PreSeparation)->setNextState(SBY_PostSeparation);

   // ---- Configuration of FsmState "SBY_PostSeparation" ----  
   DC_SBY_POSTSEPFSMSTATE_GET_CLASS(SBY_PostSeparation)->setNextState(END);

   // ---- Configuration of FsmState "END" ----  
   DC_DUMMYFSMSTATE_GET_CLASS(END)->setNextState(END);

   // ---- Configure the FSM "SBY_FSM" ----
   CC_FSM_GET_CLASS(SBY_FSM)->setNumberOfStates(3);
   CC_FSM_GET_CLASS(SBY_FSM)->setState(0,SBY_PreSeparation);
   CC_FSM_GET_CLASS(SBY_FSM)->setState(1,SBY_PostSeparation);
   CC_FSM_GET_CLASS(SBY_FSM)->setState(2,END);

   // ---- Configuration of FsmState "SAM_SunAcquisition" ----  
   DC_UNSTABLEFSMSTATE_GET_CLASS(SAM_SunAcquisition)->setNextState(SAM_SunPointing);

   // ---- Configuration of FsmState "SAM_SunPointing" ----  

   // ---- Configure the FSM "SAM_FSM" ----
   CC_FSM_GET_CLASS(SAM_FSM)->setNumberOfStates(2);
   CC_FSM_GET_CLASS(SAM_FSM)->setState(0,SAM_SunAcquisition);
   CC_FSM_GET_CLASS(SAM_FSM)->setState(1,SAM_SunPointing);

   // ---- Configuration of FsmState "OCM_Slewing" ----  
   DC_UNSTABLEFSMSTATE_GET_CLASS(OCM_Slewing)->setNextState(OCM_Pointing);

   // ---- Configuration of FsmState "OCM_Pointing" ----  

   // ---- Configuration of FsmState "OCM_Thrusting" ----  

   // ---- Configure the FSM "OCM_FSM" ----
   CC_FSM_GET_CLASS(OCM_FSM)->setNumberOfStates(3);
   CC_FSM_GET_CLASS(OCM_FSM)->setState(0,OCM_Slewing);
   CC_FSM_GET_CLASS(OCM_FSM)->setState(1,OCM_Pointing);
   CC_FSM_GET_CLASS(OCM_FSM)->setState(2,OCM_Thrusting);

   // ---- Configuration of FsmState "SCM_Slewing" ----  

   // ---- Configuration of FsmState "SCM_Pointing" ----  

   // ---- Configuration of FsmState "SCM_Scanning" ----  

   // ---- Configure the FSM "SCM_FSM" ----
   CC_FSM_GET_CLASS(SCM_FSM)->setNumberOfStates(3);
   CC_FSM_GET_CLASS(SCM_FSM)->setState(0,SCM_Slewing);
   CC_FSM_GET_CLASS(SCM_FSM)->setState(1,SCM_Pointing);
   CC_FSM_GET_CLASS(SCM_FSM)->setState(2,SCM_Scanning);

   // ---- Configuration of FsmEvent "SM_PreToPost" ---- 
   DC_FROMFSMEVENT_GET_CLASS(SM_PreToPost)->setTargetFsm(SM_FSM);  
   DC_FROMFSMEVENT_GET_CLASS(SM_PreToPost)->setTargetState(1);
   DC_FROMFSMEVENT_GET_CLASS(SM_PreToPost)->setStartingState(0);

   // ---- Configuration of FsmState "SM_PreSeparation" ----  
   DC_SM_PRESEPFSMSTATE_GET_CLASS(SM_PreSeparation)->setNextState(SM_PostSeparation);

   // ---- Configuration of FsmState "SM_PostSeparation" ----  
   DC_UNSTABLEFSMSTATE_GET_CLASS(SM_PostSeparation)->setNextState(SM_SunAcquisition);

   // ---- Configuration of FsmState "SM_SunAcquisition" ----  
   DC_UNSTABLEFSMSTATE_GET_CLASS(SM_SunAcquisition)->setNextState(SM_SunPointing);

   // ---- Configuration of FsmState "SM_SunPointing" ----  

   // ---- Configure the FSM "SM_FSM" ----
   CC_FSM_GET_CLASS(SM_FSM)->setNumberOfStates(4);
   CC_FSM_GET_CLASS(SM_FSM)->setState(0,SM_PreSeparation);
   CC_FSM_GET_CLASS(SM_FSM)->setState(1,SM_PostSeparation);
   CC_FSM_GET_CLASS(SM_FSM)->setState(2,SM_SunAcquisition);
   CC_FSM_GET_CLASS(SM_FSM)->setState(3,SM_SunPointing);

   // ---- Configuration of FsmEvent "AFS_to_AFO" ---- 
   DC_FROMFSMEVENT_GET_CLASS(AFS_to_AFO)->setTargetFsm(FDIR_FSM);  
   DC_FROMFSMEVENT_GET_CLASS(AFS_to_AFO)->setTargetState(1);
   DC_FROMFSMEVENT_GET_CLASS(AFS_to_AFO)->setStartingState(0);

   // ---- Configuration of FsmEvent "AFO_to_AFS" ---- 
   DC_FROMFSMEVENT_GET_CLASS(AFO_to_AFS)->setTargetFsm(FDIR_FSM);  
   DC_FROMFSMEVENT_GET_CLASS(AFO_to_AFS)->setTargetState(0);
   DC_FROMFSMEVENT_GET_CLASS(AFO_to_AFS)->setStartingState(1);

   // ---- Configuration of FsmState "AFS" ----  

   // ---- Configuration of FsmState "AFO" ----  

   // ---- Configure the FSM "FDIR_FSM" ----
   CC_FSM_GET_CLASS(FDIR_FSM)->setNumberOfStates(2);
   CC_FSM_GET_CLASS(FDIR_FSM)->setState(0,AFS);
   CC_FSM_GET_CLASS(FDIR_FSM)->setState(1,AFO);

   // 
CC_FSM_GET_CLASS(this->Nominal_FSM)->reset();
CC_FSM_GET_CLASS(this->SBY_FSM)->reset();
CC_FSM_GET_CLASS(this->SAM_FSM)->reset();
CC_FSM_GET_CLASS(this->OCM_FSM)->reset();
CC_FSM_GET_CLASS(this->SCM_FSM)->reset();
CC_FSM_GET_CLASS(this->SM_FSM)->reset();
CC_FSM_GET_CLASS(this->FDIR_FSM)->reset();

}

void CC_ComponentFactory_configureControllers(CC_ComponentFactory *this) {
      
   // ---- Configure the control block "contBlock_1" ----
   DC_SAMPLECONTROLBLOCK_1_GET_CLASS(contBlock_1)->setInputLink(0,DP_RW_SPD_1);
   DC_SAMPLECONTROLBLOCK_1 _GET_CLASS(contBlock_1)->setOutputLink(0,DP_RW_TOR_1);
   DC_SAMPLECONTROLBLOCK_1_GET_CLASS(contBlock_1)->setParameter(0,PARAMETERDATABASE_GET_CLASS(CC_RootObject_getParameterDatabase())->getParameterFloat(DB_G1));

   // ---- Configure the control block "contBlock_2" ----
   DC_SAMPLECONTROLBLOCK_2_GET_CLASS(contBlock_2)->setInputLink(0,DP_RW_SPD_2);
   DC_SAMPLECONTROLBLOCK_2 _GET_CLASS(contBlock_2)->setOutputLink(0,DP_RW_TOR_2);
   DC_SAMPLECONTROLBLOCK_2_GET_CLASS(contBlock_2)->setParameter(0,PARAMETERDATABASE_GET_CLASS(CC_RootObject_getParameterDatabase())->getParameterFloat(DB_G2));

   // ---- Configure the control block "contBlock_3" ----
   DC_SAMPLECONTROLBLOCK_3_GET_CLASS(contBlock_3)->setInputLink(0,DP_RW_SPD_3);
   DC_SAMPLECONTROLBLOCK_3 _GET_CLASS(contBlock_3)->setOutputLink(0,DP_RW_TOR_3);
   DC_SAMPLECONTROLBLOCK_3_GET_CLASS(contBlock_3)->setParameter(0,PARAMETERDATABASE_GET_CLASS(CC_RootObject_getParameterDatabase())->getParameterFloat(DB_G3));

   // ---- Configure the control block "contBlock_4" ----
   DC_SAMPLECONTROLBLOCK_4_GET_CLASS(contBlock_4)->setInputLink(0,DP_RW_SPD_4);
   DC_SAMPLECONTROLBLOCK_4 _GET_CLASS(contBlock_4)->setOutputLink(0,DP_RW_TOR_4);
   DC_SAMPLECONTROLBLOCK_4_GET_CLASS(contBlock_4)->setParameter(0,PARAMETERDATABASE_GET_CLASS(CC_RootObject_getParameterDatabase())->getParameterFloat(DB_G4));

         // ---- Configure the control  action "contAction_1" ----
   contAction_1->setTargetControlBlock(contBlock_1);

         // ---- Configure the control  action "contAction_2" ----
   contAction_2->setTargetControlBlock(contBlock_2);

         // ---- Configure the control  action "contAction_3" ----
   contAction_3->setTargetControlBlock(contBlock_3);

         // ---- Configure the control  action "contAction_4" ----
   contAction_4->setTargetControlBlock(contBlock_4);
      
}     

void CC_ComponentFactory_configureDataPool(CC_ComponentFactory *this) {
   
   DC_STUCKDATAPROFILE_GET_CLASS(sdMonProf_1)->setStuckThreshold(3);
   DC_OUTOFRANGEPROFILE_GET_CLASS(orMonProf_1)->setLowerBound(-2400);
   DC_OUTOFRANGEPROFILE_GET_CLASS(orMonProf_1)->setUpperBound(2400);
   DC_OUTOFRANGEPROFILE_GET_CLASS(orMonProf_2)->setLowerBound(-0.2);
   DC_OUTOFRANGEPROFILE_GET_CLASS(orMonProf_2)->setUpperBound(0.2);
   DC_STUCKDATAPROFILE_GET_CLASS(sdMonProf_4)->setStuckThreshold(3);
   DC_OUTOFRANGEPROFILE_GET_CLASS(orMonProf_4)->setLowerBound(-2400);
   DC_OUTOFRANGEPROFILE_GET_CLASS(orMonProf_4)->setUpperBound(2400);
   DC_OUTOFRANGEPROFILE_GET_CLASS(orMonProf_5)->setLowerBound(-0.2);
   DC_OUTOFRANGEPROFILE_GET_CLASS(orMonProf_5)->setUpperBound(0.2);
   DC_STUCKDATAPROFILE_GET_CLASS(sdMonProf_7)->setStuckThreshold(3);
   DC_OUTOFRANGEPROFILE_GET_CLASS(orMonProf_7)->setLowerBound(-2400);
   DC_OUTOFRANGEPROFILE_GET_CLASS(orMonProf_7)->setUpperBound(2400);
   DC_OUTOFRANGEPROFILE_GET_CLASS(orMonProf_8)->setLowerBound(-0.2);
   DC_OUTOFRANGEPROFILE_GET_CLASS(orMonProf_8)->setUpperBound(0.2);
   DC_STUCKDATAPROFILE_GET_CLASS(sdMonProf_10)->setStuckThreshold(3);
   DC_OUTOFRANGEPROFILE_GET_CLASS(orMonProf_10)->setLowerBound(-2400);
   DC_OUTOFRANGEPROFILE_GET_CLASS(orMonProf_10)->setUpperBound(2400);
   DC_OUTOFRANGEPROFILE_GET_CLASS(orMonProf_11)->setLowerBound(-0.2);
   DC_OUTOFRANGEPROFILE_GET_CLASS(orMonProf_11)->setUpperBound(0.2);
                 
                 
                 
                 
                 
                 
                 
                 
                 
                 
   // Set the properties of the data pool
   DC_SAMPLEFULLDATAPOOL_GET_CLASS(fullDataPool)->setObsClock(obsClk);
                  
                  
   // ---- Configuration of data pool item  "RW_SPD_1" ---- 
                              DC_STUCKDATAPROFILE_GET_CLASS(sdMonProf_1)->setNextMonitoringProfile(orMonProf_1);
                              DC_OUTOFRANGEPROFILE_GET_CLASS(orMonProf_1)->setNextMonitoringProfile(sMonProf_1);
   DC_SAMPLEFULLDATAPOOL_GET_CLASS(fullDataPool)->setMonitoringProfile(DP_RW_SPD_1,sdMonProf_1);
   DC_SAMPLEFULLDATAPOOL_GET_CLASS(fullDataPool)->setRecoveryAction(DP_RW_SPD_1,nRecAct_1);
                  
   // ---- Configuration of data pool item  "RW_TOR_1" ---- 
   DC_SAMPLEFULLDATAPOOL_GET_CLASS(fullDataPool)->setMonitoringProfile(DP_RW_TOR_1,orMonProf_2);
   DC_SAMPLERECOVERYACTION_GET_CLASS(sRecAct_2)->setNextRecoveryAction(nRecAct_2);
   DC_SAMPLEFULLDATAPOOL_GET_CLASS(fullDataPool)->setRecoveryAction(DP_RW_TOR_1,sRecAct_2);
                  
   // ---- Configuration of data pool item  "RW_SPD_2" ---- 
                              DC_STUCKDATAPROFILE_GET_CLASS(sdMonProf_4)->setNextMonitoringProfile(orMonProf_4);
   DC_SAMPLEFULLDATAPOOL_GET_CLASS(fullDataPool)->setMonitoringProfile(DP_RW_SPD_2,sdMonProf_4);
   DC_SAMPLEFULLDATAPOOL_GET_CLASS(fullDataPool)->setRecoveryAction(DP_RW_SPD_2,nRecAct_4);
                  
   // ---- Configuration of data pool item  "RW_TOR_2" ---- 
   DC_SAMPLEFULLDATAPOOL_GET_CLASS(fullDataPool)->setMonitoringProfile(DP_RW_TOR_2,orMonProf_5);
   DC_SAMPLEFULLDATAPOOL_GET_CLASS(fullDataPool)->setRecoveryAction(DP_RW_TOR_2,nRecAct_5);
                  
   // ---- Configuration of data pool item  "RW_SPD_3" ---- 
                              DC_STUCKDATAPROFILE_GET_CLASS(sdMonProf_7)->setNextMonitoringProfile(orMonProf_7);
   DC_SAMPLEFULLDATAPOOL_GET_CLASS(fullDataPool)->setMonitoringProfile(DP_RW_SPD_3,sdMonProf_7);
   DC_SAMPLEFULLDATAPOOL_GET_CLASS(fullDataPool)->setRecoveryAction(DP_RW_SPD_3,nRecAct_7);
                  
   // ---- Configuration of data pool item  "RW_TOR_3" ---- 
   DC_SAMPLEFULLDATAPOOL_GET_CLASS(fullDataPool)->setMonitoringProfile(DP_RW_TOR_3,orMonProf_8);
   DC_SAMPLEFULLDATAPOOL_GET_CLASS(fullDataPool)->setRecoveryAction(DP_RW_TOR_3,nRecAct_8);
                  
   // ---- Configuration of data pool item  "RW_SPD_4" ---- 
                              DC_STUCKDATAPROFILE_GET_CLASS(sdMonProf_10)->setNextMonitoringProfile(orMonProf_10);
   DC_SAMPLEFULLDATAPOOL_GET_CLASS(fullDataPool)->setMonitoringProfile(DP_RW_SPD_4,sdMonProf_10);
   DC_SAMPLEFULLDATAPOOL_GET_CLASS(fullDataPool)->setRecoveryAction(DP_RW_SPD_4,nRecAct_10);
                  
   // ---- Configuration of data pool item  "RW_TOR_4" ---- 
   DC_SAMPLEFULLDATAPOOL_GET_CLASS(fullDataPool)->setMonitoringProfile(DP_RW_TOR_4,orMonProf_11);
   DC_SAMPLEFULLDATAPOOL_GET_CLASS(fullDataPool)->setRecoveryAction(DP_RW_TOR_4,nRecAct_11);
}

void CC_ComponentFactory_configureParameterDatabase(CC_ComponentFactory *this) {
      DC_SAMPLER2DATABASE_GET_CLASS(parDB)->setOperationalTable(PARDATABASE_OP_TABLE_START);
   DC_SAMPLER2DATABASE_GET_CLASS(parDB)->setDefaultTable(PARDATABASE_DEF_TABLE_START);
   parDB->reset();

}


void CC_ComponentFactory_configureFunctionalityManagers(CC_ComponentFactory *this) {
   
   // ---- Configure the manoeuvre manager
   CC_MANOEUVREMANAGER_GET_CLASS(manMan)->setPendingManoeuvreListSize(10);

   // ---- Configure the telecommand manager
   CC_TELECOMMANDMANAGER_GET_CLASS(tcMan)->setPendingTelecommandListSize(10);
   CC_TELECOMMANDMANAGER_GET_CLASS(tcMan)->setTelecommandLoader(tcLoader);

            
   // ---- Configure the telecommand loader
   DC_BASICPUSTCLOADER_GET_CLASS(tcLoader)->setMaxNumberOfTc(4);
   DC_BASICPUSTCLOADER_GET_CLASS(tcLoader)->setMaxTcLength(100);
   DC_BASICPUSTCLOADER_GET_CLASS(tcLoader)->setTcLoadAreaStart(TC_LOADER_AREA_START);
   DC_BASICPUSTCLOADER_GET_CLASS(tcLoader)->setTelecommandManager(tcMan);
                  
       
   // ---- Configure the telemetry manager
   CC_TELEMETRYMANAGER_GET_CLASS(tmMan)->setImmediateQueueSize(5);
   CC_TELEMETRYMANAGER_GET_CLASS(tmMan)->setTelemetryStream(tmStream);
   CC_TELEMETRYMANAGER_GET_CLASS(tmMan)->setTelemetryModeManager(tmModeMan);

   // ---- Configure the telemetry stream
   DC_BASICPUSTMSTREAM_GET_CLASS(tmStream)->setCapacity(100);
   DC_BASICPUSTMSTREAM_GET_CLASS(tmStream)->setStartAddress(TM_STREAM_START);

   // ---- Configure the telemetry mode manager
   DC_PUSTELEMETRYMODEMANAGER_GET_CLASS(tmModeMan)->setMaxNumberOfPackets(10);

}

///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////


// the following may be useful if you don't need it, just delete.
// CC_ComponentFactory *this = CC_CF(obj)
static void instance_init(Object *obj)
{
   
   // Initialize the system list size. The size is computed as the number of components
   // defined in the application model plus a (heuritically defined) margin of ten to
   // account for components that are created internally to other components
   CC_RootObject_setSystemListSize(101+10);

   fullDataPool = DC_SampleFullDataPool_new();
    DC_SampleFullDataPool(obj)->list[1] = fullDataPool;
    DC_SampleFullDataPool(obj)->type[1] =  TN_SampleFullDataPool;
   sdMonProf_1 = DC_StuckDataProfile_new();
    DC_StuckDataProfile(obj)->list[2] = sdMonProf_1;
    DC_StuckDataProfile(obj)->type[2] =  TN_StuckDataProfile;
   orMonProf_1 = DC_OutOfRangeProfile_new();
    DC_OutOfRangeProfile(obj)->list[3] = orMonProf_1;
    DC_OutOfRangeProfile(obj)->type[3] =  TN_OutOfRangeProfile;
   sMonProf_1 = DC_SampleMonitoringProfile_new();
    DC_SampleMonitoringProfile(obj)->list[4] = sMonProf_1;
    DC_SampleMonitoringProfile(obj)->type[4] =  TN_SampleMonitoringProfile;
   nRecAct_1 = DC_NullRecoveryAction_new();
    DC_NullRecoveryAction(obj)->list[5] = nRecAct_1;
    DC_NullRecoveryAction(obj)->type[5] =  TN_NullRecoveryAction;
   orMonProf_2 = DC_OutOfRangeProfile_new();
    DC_OutOfRangeProfile(obj)->list[6] = orMonProf_2;
    DC_OutOfRangeProfile(obj)->type[6] =  TN_OutOfRangeProfile;
   sRecAct_2 = DC_SampleRecoveryAction_new();
    DC_SampleRecoveryAction(obj)->list[7] = sRecAct_2;
    DC_SampleRecoveryAction(obj)->type[7] =  TN_SampleRecoveryAction;
   nRecAct_2 = DC_NullRecoveryAction_new();
    DC_NullRecoveryAction(obj)->list[8] = nRecAct_2;
    DC_NullRecoveryAction(obj)->type[8] =  TN_NullRecoveryAction;
   sdMonProf_4 = DC_StuckDataProfile_new();
    DC_StuckDataProfile(obj)->list[9] = sdMonProf_4;
    DC_StuckDataProfile(obj)->type[9] =  TN_StuckDataProfile;
   orMonProf_4 = DC_OutOfRangeProfile_new();
    DC_OutOfRangeProfile(obj)->list[10] = orMonProf_4;
    DC_OutOfRangeProfile(obj)->type[10] =  TN_OutOfRangeProfile;
   nRecAct_4 = DC_NullRecoveryAction_new();
    DC_NullRecoveryAction(obj)->list[11] = nRecAct_4;
    DC_NullRecoveryAction(obj)->type[11] =  TN_NullRecoveryAction;
   orMonProf_5 = DC_OutOfRangeProfile_new();
    DC_OutOfRangeProfile(obj)->list[12] = orMonProf_5;
    DC_OutOfRangeProfile(obj)->type[12] =  TN_OutOfRangeProfile;
   nRecAct_5 = DC_NullRecoveryAction_new();
    DC_NullRecoveryAction(obj)->list[13] = nRecAct_5;
    DC_NullRecoveryAction(obj)->type[13] =  TN_NullRecoveryAction;
   sdMonProf_7 = DC_StuckDataProfile_new();
    DC_StuckDataProfile(obj)->list[14] = sdMonProf_7;
    DC_StuckDataProfile(obj)->type[14] =  TN_StuckDataProfile;
   orMonProf_7 = DC_OutOfRangeProfile_new();
    DC_OutOfRangeProfile(obj)->list[15] = orMonProf_7;
    DC_OutOfRangeProfile(obj)->type[15] =  TN_OutOfRangeProfile;
   nRecAct_7 = DC_NullRecoveryAction_new();
    DC_NullRecoveryAction(obj)->list[16] = nRecAct_7;
    DC_NullRecoveryAction(obj)->type[16] =  TN_NullRecoveryAction;
   orMonProf_8 = DC_OutOfRangeProfile_new();
    DC_OutOfRangeProfile(obj)->list[17] = orMonProf_8;
    DC_OutOfRangeProfile(obj)->type[17] =  TN_OutOfRangeProfile;
   nRecAct_8 = DC_NullRecoveryAction_new();
    DC_NullRecoveryAction(obj)->list[18] = nRecAct_8;
    DC_NullRecoveryAction(obj)->type[18] =  TN_NullRecoveryAction;
   sdMonProf_10 = DC_StuckDataProfile_new();
    DC_StuckDataProfile(obj)->list[19] = sdMonProf_10;
    DC_StuckDataProfile(obj)->type[19] =  TN_StuckDataProfile;
   orMonProf_10 = DC_OutOfRangeProfile_new();
    DC_OutOfRangeProfile(obj)->list[20] = orMonProf_10;
    DC_OutOfRangeProfile(obj)->type[20] =  TN_OutOfRangeProfile;
   nRecAct_10 = DC_NullRecoveryAction_new();
    DC_NullRecoveryAction(obj)->list[21] = nRecAct_10;
    DC_NullRecoveryAction(obj)->type[21] =  TN_NullRecoveryAction;
   orMonProf_11 = DC_OutOfRangeProfile_new();
    DC_OutOfRangeProfile(obj)->list[22] = orMonProf_11;
    DC_OutOfRangeProfile(obj)->type[22] =  TN_OutOfRangeProfile;
   nRecAct_11 = DC_NullRecoveryAction_new();
    DC_NullRecoveryAction(obj)->list[23] = nRecAct_11;
    DC_NullRecoveryAction(obj)->type[23] =  TN_NullRecoveryAction;
   parDB = DC_SampleR2Database_new();
    DC_SampleR2Database(obj)->list[24] = parDB;
    DC_SampleR2Database(obj)->type[24] =  TN_SampleR2Database;
   Nominal_FSM = CC_FSM_new();
    CC_FSM(obj)->list[25] = Nominal_FSM;
    CC_FSM(obj)->type[25] =  TN_FSM;
   SBY_FsmState = DC_NestedFsmActivatorWithEndState_new();
    DC_NestedFsmActivatorWithEndState(obj)->list[26] = SBY_FsmState;
    DC_NestedFsmActivatorWithEndState(obj)->type[26] =  TN_NestedFsmActivatorWithEndState;
   SAM_FsmState = DC_NestedFsmActivatorWithExitCheck_new();
    DC_NestedFsmActivatorWithExitCheck(obj)->list[27] = SAM_FsmState;
    DC_NestedFsmActivatorWithExitCheck(obj)->type[27] =  TN_NestedFsmActivatorWithExitCheck;
   SCM_FsmState = DC_SCM_FsmState_new();
    DC_SCM_FsmState(obj)->list[28] = SCM_FsmState;
    DC_SCM_FsmState(obj)->type[28] =  TN_SCM_FsmState;
   OCM_FsmState = DC_OCM_FsmState_new();
    DC_OCM_FsmState(obj)->list[29] = OCM_FsmState;
    DC_OCM_FsmState(obj)->type[29] =  TN_OCM_FsmState;
   SAM_to_OCM = DC_FromFsmEvent_new();
    DC_FromFsmEvent(obj)->list[30] = SAM_to_OCM;
    DC_FromFsmEvent(obj)->type[30] =  TN_FromFsmEvent;
   OCM_to_SAM = DC_FromFsmEvent_new();
    DC_FromFsmEvent(obj)->list[31] = OCM_to_SAM;
    DC_FromFsmEvent(obj)->type[31] =  TN_FromFsmEvent;
   SCM_to_SAM = DC_FromFsmEvent_new();
    DC_FromFsmEvent(obj)->list[32] = SCM_to_SAM;
    DC_FromFsmEvent(obj)->type[32] =  TN_FromFsmEvent;
   SAM_to_SCM = DC_FromFsmEvent_new();
    DC_FromFsmEvent(obj)->list[33] = SAM_to_SCM;
    DC_FromFsmEvent(obj)->type[33] =  TN_FromFsmEvent;
   SCM_to_OCM = DC_FromFsmEvent_new();
    DC_FromFsmEvent(obj)->list[34] = SCM_to_OCM;
    DC_FromFsmEvent(obj)->type[34] =  TN_FromFsmEvent;
   OCM_to_SCM = DC_FromFsmEvent_new();
    DC_FromFsmEvent(obj)->list[35] = OCM_to_SCM;
    DC_FromFsmEvent(obj)->type[35] =  TN_FromFsmEvent;
   SBY_FSM = CC_FSM_new();
    CC_FSM(obj)->list[36] = SBY_FSM;
    CC_FSM(obj)->type[36] =  TN_FSM;
   SBY_PreSeparation = DC_SBY_PreSepFsmState_new();
    DC_SBY_PreSepFsmState(obj)->list[37] = SBY_PreSeparation;
    DC_SBY_PreSepFsmState(obj)->type[37] =  TN_SBY_PreSepFsmState;
   SBY_PostSeparation = DC_SBY_PostSepFsmState_new();
    DC_SBY_PostSepFsmState(obj)->list[38] = SBY_PostSeparation;
    DC_SBY_PostSepFsmState(obj)->type[38] =  TN_SBY_PostSepFsmState;
   END = DC_DummyFsmState_new();
    DC_DummyFsmState(obj)->list[39] = END;
    DC_DummyFsmState(obj)->type[39] =  TN_DummyFsmState;
   SAM_FSM = CC_FSM_new();
    CC_FSM(obj)->list[40] = SAM_FSM;
    CC_FSM(obj)->type[40] =  TN_FSM;
   SAM_SunAcquisition = DC_UnstableFsmState_new();
    DC_UnstableFsmState(obj)->list[41] = SAM_SunAcquisition;
    DC_UnstableFsmState(obj)->type[41] =  TN_UnstableFsmState;
   SAM_SunPointing = DC_DummyFsmState_new();
    DC_DummyFsmState(obj)->list[42] = SAM_SunPointing;
    DC_DummyFsmState(obj)->type[42] =  TN_DummyFsmState;
   OCM_FSM = CC_FSM_new();
    CC_FSM(obj)->list[43] = OCM_FSM;
    CC_FSM(obj)->type[43] =  TN_FSM;
   OCM_Slewing = DC_UnstableFsmState_new();
    DC_UnstableFsmState(obj)->list[44] = OCM_Slewing;
    DC_UnstableFsmState(obj)->type[44] =  TN_UnstableFsmState;
   OCM_Pointing = DC_DummyFsmState_new();
    DC_DummyFsmState(obj)->list[45] = OCM_Pointing;
    DC_DummyFsmState(obj)->type[45] =  TN_DummyFsmState;
   OCM_Thrusting = DC_DummyFsmState_new();
    DC_DummyFsmState(obj)->list[46] = OCM_Thrusting;
    DC_DummyFsmState(obj)->type[46] =  TN_DummyFsmState;
   SCM_FSM = CC_FSM_new();
    CC_FSM(obj)->list[47] = SCM_FSM;
    CC_FSM(obj)->type[47] =  TN_FSM;
   SCM_Slewing = DC_DummyFsmState_new();
    DC_DummyFsmState(obj)->list[48] = SCM_Slewing;
    DC_DummyFsmState(obj)->type[48] =  TN_DummyFsmState;
   SCM_Pointing = DC_DummyFsmState_new();
    DC_DummyFsmState(obj)->list[49] = SCM_Pointing;
    DC_DummyFsmState(obj)->type[49] =  TN_DummyFsmState;
   SCM_Scanning = DC_DummyFsmState_new();
    DC_DummyFsmState(obj)->list[50] = SCM_Scanning;
    DC_DummyFsmState(obj)->type[50] =  TN_DummyFsmState;
   SM_FSM = CC_FSM_new();
    CC_FSM(obj)->list[51] = SM_FSM;
    CC_FSM(obj)->type[51] =  TN_FSM;
   SM_PreSeparation = DC_SM_PreSepFsmState_new();
    DC_SM_PreSepFsmState(obj)->list[52] = SM_PreSeparation;
    DC_SM_PreSepFsmState(obj)->type[52] =  TN_SM_PreSepFsmState;
   SM_PostSeparation = DC_UnstableFsmState_new();
    DC_UnstableFsmState(obj)->list[53] = SM_PostSeparation;
    DC_UnstableFsmState(obj)->type[53] =  TN_UnstableFsmState;
   SM_SunAcquisition = DC_UnstableFsmState_new();
    DC_UnstableFsmState(obj)->list[54] = SM_SunAcquisition;
    DC_UnstableFsmState(obj)->type[54] =  TN_UnstableFsmState;
   SM_SunPointing = DC_DummyFsmState_new();
    DC_DummyFsmState(obj)->list[55] = SM_SunPointing;
    DC_DummyFsmState(obj)->type[55] =  TN_DummyFsmState;
   SM_PreToPost = DC_FromFsmEvent_new();
    DC_FromFsmEvent(obj)->list[56] = SM_PreToPost;
    DC_FromFsmEvent(obj)->type[56] =  TN_FromFsmEvent;
   FDIR_FSM = CC_FSM_new();
    CC_FSM(obj)->list[57] = FDIR_FSM;
    CC_FSM(obj)->type[57] =  TN_FSM;
   AFS = DC_AfsFsmState_new();
    DC_AfsFsmState(obj)->list[58] = AFS;
    DC_AfsFsmState(obj)->type[58] =  TN_AfsFsmState;
   AFO = DC_DummyFsmState_new();
    DC_DummyFsmState(obj)->list[59] = AFO;
    DC_DummyFsmState(obj)->type[59] =  TN_DummyFsmState;
   AFS_to_AFO = DC_FromFsmEvent_new();
    DC_FromFsmEvent(obj)->list[60] = AFS_to_AFO;
    DC_FromFsmEvent(obj)->type[60] =  TN_FromFsmEvent;
   AFO_to_AFS = DC_FromFsmEvent_new();
    DC_FromFsmEvent(obj)->list[61] = AFO_to_AFS;
    DC_FromFsmEvent(obj)->type[61] =  TN_FromFsmEvent;
   contAction_1 = DC_ControlAction_new();
    DC_ControlAction(obj)->list[62] = contAction_1;
    DC_ControlAction(obj)->type[62] =  TN_ControlAction;
   contBlock_1 = DC_SampleControlBlock_1_new();
    DC_SampleControlBlock_1(obj)->list[63] = contBlock_1;
    DC_SampleControlBlock_1(obj)->type[63] =  TN_SampleControlBlock_1;
   contAction_2 = DC_ControlAction_new();
    DC_ControlAction(obj)->list[64] = contAction_2;
    DC_ControlAction(obj)->type[64] =  TN_ControlAction;
   contBlock_2 = DC_SampleControlBlock_2_new();
    DC_SampleControlBlock_2(obj)->list[65] = contBlock_2;
    DC_SampleControlBlock_2(obj)->type[65] =  TN_SampleControlBlock_2;
   contAction_3 = DC_ControlAction_new();
    DC_ControlAction(obj)->list[66] = contAction_3;
    DC_ControlAction(obj)->type[66] =  TN_ControlAction;
   contBlock_3 = DC_SampleControlBlock_3_new();
    DC_SampleControlBlock_3(obj)->list[67] = contBlock_3;
    DC_SampleControlBlock_3(obj)->type[67] =  TN_SampleControlBlock_3;
   contAction_4 = DC_ControlAction_new();
    DC_ControlAction(obj)->list[68] = contAction_4;
    DC_ControlAction(obj)->type[68] =  TN_ControlAction;
   contBlock_4 = DC_SampleControlBlock_4_new();
    DC_SampleControlBlock_4(obj)->list[69] = contBlock_4;
    DC_SampleControlBlock_4(obj)->type[69] =  TN_SampleControlBlock_4;
   obsClk = DC_DummyObsClock_new();
    DC_DummyObsClock(obj)->list[70] = obsClk;
    DC_DummyObsClock(obj)->type[70] =  TN_DummyObsClock;
   evtRep = DC_PUSEventRepository_new();
    DC_PUSEventRepository(obj)->list[71] = evtRep;
    DC_PUSEventRepository(obj)->type[71] =  TN_PUSEventRepository;
   tracer = DC_DummyTracer_new();
    DC_DummyTracer(obj)->list[72] = tracer;
    DC_DummyTracer(obj)->type[72] =  TN_DummyTracer;
   manMan = CC_ManoeuvreManager_new();
    CC_ManoeuvreManager(obj)->list[73] = manMan;
    CC_ManoeuvreManager(obj)->type[73] =  TN_ManoeuvreManager;
   man_1 = DC_DummyManoeuvre_new();
    DC_DummyManoeuvre(obj)->list[74] = man_1;
    DC_DummyManoeuvre(obj)->type[74] =  TN_DummyManoeuvre;
   man_2 = DC_DummyConfigurableManoeuvre_new();
    DC_DummyConfigurableManoeuvre(obj)->list[75] = man_2;
    DC_DummyConfigurableManoeuvre(obj)->type[75] =  TN_DummyConfigurableManoeuvre;
   man_3 = DC_TestPUSConfigurableManoeuvre_new();
    DC_TestPUSConfigurableManoeuvre(obj)->list[76] = man_3;
    DC_TestPUSConfigurableManoeuvre(obj)->type[76] =  TN_TestPUSConfigurableManoeuvre;
   tcMan = CC_TelecommandManager_new();
    CC_TelecommandManager(obj)->list[77] = tcMan;
    CC_TelecommandManager(obj)->type[77] =  TN_TelecommandManager;
   tcLoader = DC_BasicPUSTcLoader_new();
    DC_BasicPUSTcLoader(obj)->list[78] = tcLoader;
    DC_BasicPUSTcLoader(obj)->type[78] =  TN_BasicPUSTcLoader;
   tc_1 = DC_DummyTelecommand_new();
    DC_DummyTelecommand(obj)->list[79] = tc_1;
    DC_DummyTelecommand(obj)->type[79] =  TN_DummyTelecommand;
   tc_2 = DC_DummyTelecommand_new();
    DC_DummyTelecommand(obj)->list[80] = tc_2;
    DC_DummyTelecommand(obj)->type[80] =  TN_DummyTelecommand;
   tc_3 = DC_DummyPUSTelecommand_new();
    DC_DummyPUSTelecommand(obj)->list[81] = tc_3;
    DC_DummyPUSTelecommand(obj)->type[81] =  TN_DummyPUSTelecommand;
   tc_4 = DC_PUSDefineDataReporting_new();
    DC_PUSDefineDataReporting(obj)->list[82] = tc_4;
    DC_PUSDefineDataReporting(obj)->type[82] =  TN_PUSDefineDataReporting;
   tc_5 = DC_PUSControlDataReporting_new();
    DC_PUSControlDataReporting(obj)->list[83] = tc_5;
    DC_PUSControlDataReporting(obj)->type[83] =  TN_PUSControlDataReporting;
   tc_6 = DC_TestPUSTelecommand_new();
    DC_TestPUSTelecommand(obj)->list[84] = tc_6;
    DC_TestPUSTelecommand(obj)->type[84] =  TN_TestPUSTelecommand;
   tc_7 = DC_TestPUSTelecommand_new();
    DC_TestPUSTelecommand(obj)->list[85] = tc_7;
    DC_TestPUSTelecommand(obj)->type[85] =  TN_TestPUSTelecommand;
   tc_8 = DC_TestPUSTelecommand_new();
    DC_TestPUSTelecommand(obj)->list[86] = tc_8;
    DC_TestPUSTelecommand(obj)->type[86] =  TN_TestPUSTelecommand;
   tc_9 = DC_PUSDumpMemoryAbsolute_new();
    DC_PUSDumpMemoryAbsolute(obj)->list[87] = tc_9;
    DC_PUSDumpMemoryAbsolute(obj)->type[87] =  TN_PUSDumpMemoryAbsolute;
   tc_10 = DC_PUSDumpMemoryOffset_new();
    DC_PUSDumpMemoryOffset(obj)->list[88] = tc_10;
    DC_PUSDumpMemoryOffset(obj)->type[88] =  TN_PUSDumpMemoryOffset;
   tc_11 = DC_PUSMemoryLoadAbsolute_new();
    DC_PUSMemoryLoadAbsolute(obj)->list[89] = tc_11;
    DC_PUSMemoryLoadAbsolute(obj)->type[89] =  TN_PUSMemoryLoadAbsolute;
   tc_12 = DC_PUSMemoryLoadAbsolute_new();
    DC_PUSMemoryLoadAbsolute(obj)->list[90] = tc_12;
    DC_PUSMemoryLoadAbsolute(obj)->type[90] =  TN_PUSMemoryLoadAbsolute;
   tc_13 = DC_PUSMemoryLoadOffset_new();
    DC_PUSMemoryLoadOffset(obj)->list[91] = tc_13;
    DC_PUSMemoryLoadOffset(obj)->type[91] =  TN_PUSMemoryLoadOffset;
   tmMan = CC_TelemetryManager_new();
    CC_TelemetryManager(obj)->list[92] = tmMan;
    CC_TelemetryManager(obj)->type[92] =  TN_TelemetryManager;
   tmStream = DC_BasicPUSTmStream_new();
    DC_BasicPUSTmStream(obj)->list[93] = tmStream;
    DC_BasicPUSTmStream(obj)->type[93] =  TN_BasicPUSTmStream;
   tm_1 = DC_DummyPUSTelemetryPacket_new();
    DC_DummyPUSTelemetryPacket(obj)->list[94] = tm_1;
    DC_DummyPUSTelemetryPacket(obj)->type[94] =  TN_DummyPUSTelemetryPacket;
   tm_2 = DC_DummyPUSTelemetryPacket_new();
    DC_DummyPUSTelemetryPacket(obj)->list[95] = tm_2;
    DC_DummyPUSTelemetryPacket(obj)->type[95] =  TN_DummyPUSTelemetryPacket;
   tm_3 = DC_PUSTcVerificationPacket_new();
    DC_PUSTcVerificationPacket(obj)->list[96] = tm_3;
    DC_PUSTcVerificationPacket(obj)->type[96] =  TN_PUSTcVerificationPacket;
   tm_4 = DC_PUSDataReportingPacket_new();
    DC_PUSDataReportingPacket(obj)->list[97] = tm_4;
    DC_PUSDataReportingPacket(obj)->type[97] =  TN_PUSDataReportingPacket;
   tm_5 = DC_PUSDataReportingPacket_new();
    DC_PUSDataReportingPacket(obj)->list[98] = tm_5;
    DC_PUSDataReportingPacket(obj)->type[98] =  TN_PUSDataReportingPacket;
   tm_6 = DC_PUSMemoryDumpAbsolute_new();
    DC_PUSMemoryDumpAbsolute(obj)->list[99] = tm_6;
    DC_PUSMemoryDumpAbsolute(obj)->type[99] =  TN_PUSMemoryDumpAbsolute;
   tm_7 = DC_PUSMemoryDumpOffset_new();
    DC_PUSMemoryDumpOffset(obj)->list[100] = tm_7;
    DC_PUSMemoryDumpOffset(obj)->type[100] =  TN_PUSMemoryDumpOffset;
   tmModeMan = DC_PUSTelemetryModeManager_new();
    DC_PUSTelemetryModeManager(obj)->list[101] = tmModeMan;
    DC_PUSTelemetryModeManager(obj)->type[101] =  TN_PUSTelemetryModeManager;


}

CC_ComponentFactory* CC_ComponentFactory_new(void)
{
        return (CC_ComponentFactory*)object_new(TYPE_CC_CF);

}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
CC_ComponentFactoryClass *dc_p_class = CC_CF_CLASS(oc);

}

static const TypeInfo type_info = {
        .name = TYPE_CC_CF,
        .parent = Object,
        .instance_size = sizeof(CC_ComponentFactory),
        .abstract = false,
        .class_size = sizeof(CC_ComponentFactoryClass),
        .instance_init = instance_init,
        .class_init = class_init,

};

void CC_ComponentFactory_register(void)
{
        type_register_static(&type_info);

}


