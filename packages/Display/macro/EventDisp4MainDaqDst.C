#if ROOT_VERSION_CODE >= ROOT_VERSION(6,00,0)
#include "G4_SensitiveDetectors.C"
#include "G4_Target.C"
R__LOAD_LIBRARY(libinterface_main)
R__LOAD_LIBRARY(libfun4all)
R__LOAD_LIBRARY(libdecoder_maindaq)
R__LOAD_LIBRARY(libg4testbench)
R__LOAD_LIBRARY(libg4detectors)
R__LOAD_LIBRARY(libg4eval)
R__LOAD_LIBRARY(libevt_filter)
R__LOAD_LIBRARY(libpheve_display)
R__LOAD_LIBRARY(libpheve_modules)
R__LOAD_LIBRARY(libpheve_interface)
#endif
void InitInput();

void EventDisp4MainDaqDst(const bool online=true)
{
  EventDispUI* ui = new EventDispUI();
  ui->Init(online);
  InitInput();
  ui->Run();
}

void InitInput()
{
  Fun4AllServer* se = Fun4AllServer::instance();
  se->Verbosity(0);

  JobOptsSvc *jobopt_svc = JobOptsSvc::instance();
  jobopt_svc->init("run6_data.opts");

  PHG4Reco *g4Reco = new PHG4Reco();
  se->registerSubsystem(g4Reco);
  g4Reco->SetWorldSizeX(1000);
  g4Reco->SetWorldSizeY(1000);
  g4Reco->SetWorldSizeZ(5000);
  g4Reco->SetWorldShape("G4BOX");
  g4Reco->SetWorldMaterial("G4_AIR"); //G4_Galactic, G4_AIR
  g4Reco->SetPhysicsList("FTFP_BERT");

  PHG4E1039InsensSubsystem* insens = new PHG4E1039InsensSubsystem("Insens");
  g4Reco->registerSubsystem(insens);

  SetupTarget(g4Reco);

  SetupSensitiveDetectors(g4Reco);

  se->registerSubsystem(new EvtFilter());

  /// (width, height, use_fieldmap, use_geofile, field-map name, geo-file name)
  PHEventDisplay* disp = new PHEventDisplay(1920, 1080, false, false, "", "geom.root");
  //disp->set_verbosity(3);
  se->registerSubsystem(disp);
  
  g4Reco->InitRun(se->topNode());
  disp  ->InitRun(se->topNode());

  Fun4AllInputManager *in = new Fun4AllDstInputManager("DSTIN");
  se->registerInputManager(in);
}
