/*
 * Entry: 00440799
 * Name: Misns2Mission::Execute
 * Namespace: Misns2Mission
 * Signature: void Execute(Misns2Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns2Mission::Execute(Misns2Mission *this)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  char *pcVar6;
  
  if ((this->field16_0x40)._s_0.missionstart == false) {
    iVar3 = AudioMessage("misns200.wav");
    (this->field19_0x234)._s_0.aud1 = iVar3;
    iVar3 = GetHandle("sblpad59_i76building");
    (this->field18_0x90)._s_0.launchpad = iVar3;
    iVar3 = GetHandle("svtank0_wingman");
    (this->field18_0x90)._s_0.player = iVar3;
    iVar3 = GetHandle("svfigh2_wingman");
    (this->field18_0x90)._s_0.lu = iVar3;
    iVar3 = GetHandle("apcamr5_camerapod");
    (this->field18_0x90)._s_0.nav1route = iVar3;
    iVar3 = GetHandle("svfigh3_wingman");
    (this->field18_0x90)._s_0.e1a = iVar3;
    iVar3 = GetHandle("svfigh5_wingman");
    (this->field18_0x90)._s_0.e2b = iVar3;
    iVar3 = GetHandle("svfigh6_wingman");
    (this->field18_0x90)._s_0.e3a = iVar3;
    iVar3 = GetHandle("svtank5_wingman");
    (this->field18_0x90)._s_0.e2a = iVar3;
    iVar3 = GetHandle("svtank4_wingman");
    (this->field18_0x90)._s_0.e1b = iVar3;
    iVar3 = GetHandle("svtank12_wingman");
    (this->field18_0x90)._s_0.e3b = iVar3;
    iVar3 = GetHandle("svapc0_apc");
    (this->field18_0x90)._s_0.t1 = iVar3;
    iVar3 = GetHandle("svapc1_apc");
    (this->field18_0x90)._s_0.t2 = iVar3;
    iVar3 = GetHandle("svapc2_apc");
    (this->field18_0x90)._s_0.t3 = iVar3;
    fVar5 = Get_Time();
    (this->field16_0x40)._s_0.missionstart = true;
    (this->field17_0x68)._s_0.wave1start = fVar5 + 10.0;
    InfoDisplay::AddObjective(&infoDisplay,"misns201.otf",DisplayInterface::colorWhite,8.0);
    InfoDisplay::AddObjective(&infoDisplay,"misns202.otf",DisplayInterface::colorWhite,8.0);
    InfoDisplay::AddObjective(&infoDisplay,"misns203.otf",DisplayInterface::colorWhite,8.0);
    CameraReady();
    iVar3 = GetHandle("cam1");
    (this->field18_0x90)._s_0.cam1 = iVar3;
    fVar5 = Get_Time();
    (this->field17_0x68)._s_0.cam1t = fVar5 + 9.0;
    fVar5 = Get_Time();
    (this->field17_0x68)._s_0.cam2t = fVar5 + 9.01;
    fVar5 = Get_Time();
    (this->field17_0x68)._s_0.cam3t = fVar5 + 24.0;
    fVar5 = Get_Time();
    (this->field17_0x68)._s_0.cam4t = fVar5 + 34.0;
    SetObjectiveName((this->field18_0x90)._s_0.cam1,"Launch Pad");
  }
  if ((this->field16_0x40)._s_0.openingcindone == false) {
    CameraPath("cinpath1",500,200,(this->field18_0x90)._s_0.t1);
    bVar2 = IsAudioMessageDone((this->field19_0x234)._s_0.aud1);
    if ((bVar2) || (bVar2 = CameraCancelled(), bVar2)) {
      (this->field16_0x40)._s_0.openingcindone = true;
      CameraFinish();
      StopAudioMessage((this->field19_0x234)._s_0.aud1);
      AudioMessage("misns202.wav");
    }
  }
  if ((this->field16_0x40)._s_0.newobjective == true) {
    InfoDisplay::ClearObjectives(&infoDisplay);
    bVar2 = IsAlive(&(this->field18_0x90)._s_0.t1);
    if (!bVar2) {
      InfoDisplay::AddObjective(&infoDisplay,"misns201.otf",DisplayInterface::colorRed,8.0);
    }
    bVar2 = IsAlive(&(this->field18_0x90)._s_0.t2);
    if (!bVar2) {
      InfoDisplay::AddObjective(&infoDisplay,"misns202.otf",DisplayInterface::colorRed,8.0);
    }
    bVar2 = IsAlive(&(this->field18_0x90)._s_0.t3);
    if (!bVar2) {
      InfoDisplay::AddObjective(&infoDisplay,"misns203.otf",DisplayInterface::colorRed,8.0);
    }
    bVar2 = IsAlive(&(this->field18_0x90)._s_0.t1);
    if ((bVar2) && ((this->field16_0x40)._s_0.t1arrive == false)) {
      InfoDisplay::AddObjective(&infoDisplay,"misns201.otf",DisplayInterface::colorWhite,8.0);
    }
    bVar2 = IsAlive(&(this->field18_0x90)._s_0.t1);
    if ((bVar2) && ((this->field16_0x40)._s_0.t1arrive == true)) {
      InfoDisplay::AddObjective(&infoDisplay,"misns201.otf",DisplayInterface::colorGreen,8.0);
    }
    piVar1 = &(this->field18_0x90)._s_0.t2;
    bVar2 = IsAlive(piVar1);
    if ((bVar2) && ((this->field16_0x40)._s_0.t2arrive == true)) {
      InfoDisplay::AddObjective(&infoDisplay,"misns202.otf",DisplayInterface::colorGreen,8.0);
    }
    bVar2 = IsAlive(piVar1);
    if ((bVar2) && ((this->field16_0x40)._s_0.t2arrive == false)) {
      InfoDisplay::AddObjective(&infoDisplay,"misns202.otf",DisplayInterface::colorWhite,8.0);
    }
    piVar1 = &(this->field18_0x90)._s_0.t3;
    bVar2 = IsAlive(piVar1);
    if ((bVar2) && ((this->field16_0x40)._s_0.t3arrive == true)) {
      InfoDisplay::AddObjective(&infoDisplay,"misns203.otf",DisplayInterface::colorGreen,8.0);
    }
    bVar2 = IsAlive(piVar1);
    if ((bVar2) && ((this->field16_0x40)._s_0.t3arrive == false)) {
      InfoDisplay::AddObjective(&infoDisplay,"misns203.otf",DisplayInterface::colorWhite,8.0);
    }
    (this->field16_0x40)._s_0.newobjective = false;
  }
  fVar5 = Get_Time();
  if (((this->field17_0x68)._s_0.wave1start < fVar5) &&
     ((this->field16_0x40)._s_0.wave1gone == false)) {
    iVar3 = BuildObject("bvtank",2,"bdsp1",0);
    (this->field18_0x90)._s_0.bd1 = iVar3;
    iVar3 = BuildObject("bvraz",2,"bdsp1",0);
    (this->field18_0x90)._s_0.bd2 = iVar3;
    Attack((this->field18_0x90)._s_0.bd1,(this->field18_0x90)._s_0.t1,1);
    Attack((this->field18_0x90)._s_0.bd2,(this->field18_0x90)._s_0.t3,1);
    SetIndependence((this->field18_0x90)._s_0.bd1,1);
    SetIndependence((this->field18_0x90)._s_0.bd2,1);
    (this->field17_0x68)._s_0.wave1start = 1e+12;
    (this->field16_0x40)._s_0.wave1gone = true;
  }
  if (((((this->field16_0x40)._s_0.wave1gone == true) &&
       (bVar2 = IsAlive(&(this->field18_0x90)._s_0.bd1), !bVar2)) &&
      (bVar2 = IsAlive(&(this->field18_0x90)._s_0.bd2), !bVar2)) &&
     ((this->field16_0x40)._s_0.cintimeset == false)) {
    AudioMessage("misns203.wav");
    fVar5 = Get_Time();
    (this->field16_0x40)._s_0.cintimeset = true;
    (this->field17_0x68)._s_0.cintime = fVar5 + 3.0;
  }
  bVar2 = IsAlive(&(this->field18_0x90)._s_0.bd1);
  if (((!bVar2) && (bVar2 = IsAlive(&(this->field18_0x90)._s_0.bd2), !bVar2)) &&
     (((this->field16_0x40)._s_0.surrender == false &&
      (((this->field16_0x40)._s_0.wave1gone == true &&
       (fVar5 = Get_Time(), (this->field17_0x68)._s_0.cintime < fVar5)))))) {
    iVar3 = AudioMessage("misns204.wav");
    (this->field19_0x234)._s_0.aud2 = iVar3;
    iVar3 = AudioMessage("misns205.wav");
    (this->field19_0x234)._s_0.aud3 = iVar3;
    (this->field16_0x40)._s_0.surrender = true;
    CameraReady();
    fVar5 = Get_Time();
    (this->field17_0x68)._s_0.platooncam = fVar5 + 20.0;
    iVar3 = BuildObject("bvtank",2,"100",0);
    (this->field18_0x90)._s_0.bd100 = iVar3;
    iVar3 = BuildObject("bvtank",2,"101",0);
    (this->field18_0x90)._s_0.bd101 = iVar3;
    iVar3 = BuildObject("bvtank",2,"102",0);
    (this->field18_0x90)._s_0.bd102 = iVar3;
    iVar3 = BuildObject("bvtank",2,"103",0);
    (this->field18_0x90)._s_0.bd103 = iVar3;
    iVar3 = BuildObject("bvtank",2,"104",0);
    (this->field18_0x90)._s_0.bd104 = iVar3;
    iVar3 = BuildObject("bvtank",2,"105",0);
    (this->field18_0x90)._s_0.bd105 = iVar3;
    iVar3 = BuildObject("bvtank",2,"106",0);
    (this->field18_0x90)._s_0.bd106 = iVar3;
    iVar3 = BuildObject("bvtank",2,"107",0);
    (this->field18_0x90)._s_0.bd107 = iVar3;
    iVar3 = BuildObject("bvtank",2,"108",0);
    (this->field18_0x90)._s_0.bd108 = iVar3;
    iVar3 = BuildObject("bvtank",2,"109",0);
    (this->field18_0x90)._s_0.bd109 = iVar3;
    iVar3 = BuildObject("bvtank",2,"110",0);
    (this->field18_0x90)._s_0.bd110 = iVar3;
  }
  if (((this->field16_0x40)._s_0.bdcindone == false) &&
     ((this->field16_0x40)._s_0.surrender == true)) {
    CameraPath("platooncam",1000,600,(this->field18_0x90)._s_0.bd100);
    bVar2 = IsAudioMessageDone((this->field19_0x234)._s_0.aud2);
    if (((bVar2) && (bVar2 = IsAudioMessageDone((this->field19_0x234)._s_0.aud3), bVar2)) ||
       (bVar2 = CameraCancelled(), bVar2)) {
      CameraFinish();
      StopAudioMessage((this->field19_0x234)._s_0.aud2);
      StopAudioMessage((this->field19_0x234)._s_0.aud3);
      iVar4 = AudioMessage("misns206.wav");
      iVar3 = (this->field18_0x90)._s_0.t3;
      (this->field19_0x234)._s_0.aud4 = iVar4;
      iVar4 = (this->field18_0x90)._s_0.bd103;
      (this->field16_0x40)._s_0.platooncamdone = true;
      Attack(iVar4,iVar3,1);
      Attack((this->field18_0x90)._s_0.bd104,(this->field18_0x90)._s_0.t2,1);
      RemoveObject((this->field18_0x90)._s_0.bd100);
      RemoveObject((this->field18_0x90)._s_0.bd101);
      RemoveObject((this->field18_0x90)._s_0.bd102);
      RemoveObject((this->field18_0x90)._s_0.bd105);
      RemoveObject((this->field18_0x90)._s_0.bd106);
      RemoveObject((this->field18_0x90)._s_0.bd107);
      RemoveObject((this->field18_0x90)._s_0.bd108);
      RemoveObject((this->field18_0x90)._s_0.bd109);
      RemoveObject((this->field18_0x90)._s_0.bd110);
      (this->field16_0x40)._s_0.bdcindone = true;
    }
  }
  if ((this->field16_0x40)._s_0.wave2gone == false) {
    iVar3 = GetNearestVehicle("bdsp2",1);
    (this->field18_0x90)._s_0.enemy3 = iVar3;
    if (((this->field16_0x40)._s_0.wave2gone == false) &&
       (fVar5 = GetDistance(iVar3,"bdsp2",0), fVar5 < 420.0)) {
      iVar3 = BuildObject("bvraz",2,"bdsp2",0);
      (this->field18_0x90)._s_0.bd5 = iVar3;
      iVar3 = BuildObject("bvraz",2,"bdsp2",0);
      (this->field18_0x90)._s_0.bd6 = iVar3;
      iVar3 = BuildObject("bvraz",2,"bdsp2",0);
      (this->field18_0x90)._s_0.bd7 = iVar3;
      iVar3 = BuildObject("bvtank",2,"bdsp2",0);
      (this->field18_0x90)._s_0.bd8 = iVar3;
      Attack((this->field18_0x90)._s_0.bd5,(this->field18_0x90)._s_0.t3,1);
      Attack((this->field18_0x90)._s_0.bd6,(this->field18_0x90)._s_0.t1,1);
      Attack((this->field18_0x90)._s_0.bd7,(this->field18_0x90)._s_0.t3,1);
      Attack((this->field18_0x90)._s_0.bd8,(this->field18_0x90)._s_0.t2,1);
      SetIndependence((this->field18_0x90)._s_0.bd5,1);
      SetIndependence((this->field18_0x90)._s_0.bd6,1);
      SetIndependence((this->field18_0x90)._s_0.bd7,1);
      SetIndependence((this->field18_0x90)._s_0.bd8,1);
      (this->field16_0x40)._s_0.wave2gone = true;
    }
  }
  fVar5 = GetDistance((this->field18_0x90)._s_0.t1,"nav1",0);
  if ((((fVar5 < 200.0) ||
       (fVar5 = GetDistance((this->field18_0x90)._s_0.t2,"nav1",0), fVar5 < 200.0)) ||
      (fVar5 = GetDistance((this->field18_0x90)._s_0.t3,"nav1",0), fVar5 < 200.0)) &&
     ((this->field16_0x40)._s_0.wave2gone == false)) {
    iVar3 = BuildObject("bvraz",2,"bdsp2",0);
    (this->field18_0x90)._s_0.bd5 = iVar3;
    iVar3 = BuildObject("bvraz",2,"bdsp2",0);
    (this->field18_0x90)._s_0.bd6 = iVar3;
    iVar3 = BuildObject("bvraz",2,"bdsp2",0);
    (this->field18_0x90)._s_0.bd7 = iVar3;
    iVar3 = BuildObject("bvtank",2,"bdsp2",0);
    (this->field18_0x90)._s_0.bd8 = iVar3;
    Attack((this->field18_0x90)._s_0.bd5,(this->field18_0x90)._s_0.t1,1);
    piVar1 = &(this->field18_0x90)._s_0.t2;
    Attack((this->field18_0x90)._s_0.bd6,*piVar1,1);
    Attack((this->field18_0x90)._s_0.bd7,*piVar1,1);
    Attack((this->field18_0x90)._s_0.bd8,(this->field18_0x90)._s_0.t3,1);
    SetIndependence((this->field18_0x90)._s_0.bd5,1);
    SetIndependence((this->field18_0x90)._s_0.bd6,1);
    SetIndependence((this->field18_0x90)._s_0.bd7,1);
    SetIndependence((this->field18_0x90)._s_0.bd8,1);
    (this->field16_0x40)._s_0.wave2gone = true;
  }
  if ((this->field16_0x40)._s_0.wave3gone == false) {
    iVar3 = GetNearestVehicle("bdsp3",1);
    (this->field18_0x90)._s_0.enemy1 = iVar3;
    if ((this->field16_0x40)._s_0.wave3gone == false) {
      fVar5 = GetDistance(iVar3,"bdsp3",0);
      if ((fVar5 < 450.0) && (iVar3 = GetTeamNum((this->field18_0x90)._s_0.enemy1), iVar3 == 1)) {
        iVar3 = BuildObject("bvartl",2,"bdsp3",0);
        (this->field18_0x90)._s_0.bd9 = iVar3;
        iVar3 = BuildObject("bvartl",2,"bdsp3",0);
        (this->field18_0x90)._s_0.bd10 = iVar3;
        iVar3 = BuildObject("bvtank",2,"bdsp3",0);
        (this->field18_0x90)._s_0.bd11 = iVar3;
        SetIndependence(iVar3,1);
        (this->field16_0x40)._s_0.wave3gone = true;
      }
      if (((this->field16_0x40)._s_0.wave3gone == false) &&
         (((fVar5 = GetDistance((this->field18_0x90)._s_0.t1,"nav3",0), fVar5 < 400.0 ||
           (fVar5 = GetDistance((this->field18_0x90)._s_0.t2,"nav3",0), fVar5 < 400.0)) ||
          (fVar5 = GetDistance((this->field18_0x90)._s_0.t3,"nav3",0), fVar5 < 400.0)))) {
        iVar3 = BuildObject("bvartl",2,"bdsp3",0);
        (this->field18_0x90)._s_0.bd9 = iVar3;
        iVar3 = BuildObject("bvartl",2,"bdsp3",0);
        (this->field18_0x90)._s_0.bd10 = iVar3;
        iVar3 = BuildObject("bvtank",2,"bdsp3",0);
        (this->field18_0x90)._s_0.bd11 = iVar3;
        BuildObject("proxmine",2,"mine1",0);
        BuildObject("proxmine",2,"mine2",0);
        BuildObject("proxmine",2,"mine3",0);
        BuildObject("proxmine",2,"mine4",0);
        BuildObject("proxmine",2,"mine5",0);
        BuildObject("proxmine",2,"mine6",0);
        BuildObject("proxmine",2,"mine7",0);
        BuildObject("proxmine",2,"mine8",0);
        BuildObject("proxmine",2,"mine9",0);
        BuildObject("proxmine",2,"mine10",0);
        BuildObject("proxmine",2,"mine11",0);
        BuildObject("proxmine",2,"mine12",0);
        BuildObject("proxmine",2,"mine13",0);
        BuildObject("proxmine",2,"mine14",0);
        BuildObject("proxmine",2,"mine15",0);
        BuildObject("proxmine",2,"mine16",0);
        BuildObject("proxmine",2,"mine17",0);
        BuildObject("proxmine",2,"mine18",0);
        BuildObject("proxmine",2,"mine19",0);
        Attack((this->field18_0x90)._s_0.bd9,(this->field18_0x90)._s_0.t3,1);
        Attack((this->field18_0x90)._s_0.bd10,(this->field18_0x90)._s_0.t2,1);
        Follow((this->field18_0x90)._s_0.bd11,(this->field18_0x90)._s_0.bd9,1);
        SetIndependence((this->field18_0x90)._s_0.bd11,1);
        (this->field16_0x40)._s_0.wave3gone = true;
        fVar5 = Get_Time();
        (this->field17_0x68)._s_0.alerttime = fVar5 + 15.0;
      }
    }
  }
  fVar5 = Get_Time();
  if (((this->field17_0x68)._s_0.alerttime < fVar5) &&
     ((this->field16_0x40)._s_0.artwarning == false)) {
    SetObjectiveOn((this->field18_0x90)._s_0.bd9);
    SetObjectiveOn((this->field18_0x90)._s_0.bd10);
    AudioMessage("misns210.wav");
    SetObjectiveOn((this->field18_0x90)._s_0.bd12);
    SetObjectiveOn((this->field18_0x90)._s_0.bd13);
    (this->field16_0x40)._s_0.artwarning = true;
  }
  if ((this->field16_0x40)._s_0.wave4gone == false) {
    iVar3 = GetNearestVehicle("bdsp4",1);
    (this->field18_0x90)._s_0.enemy2 = iVar3;
    if ((this->field16_0x40)._s_0.wave4gone == false) {
      fVar5 = GetDistance(iVar3,"bdsp4",0);
      if ((fVar5 < 450.0) && (iVar3 = GetTeamNum((this->field18_0x90)._s_0.enemy2), iVar3 == 1)) {
        iVar3 = BuildObject("bvartl",2,"bdsp4",0);
        (this->field18_0x90)._s_0.bd12 = iVar3;
        iVar3 = BuildObject("bvtank",2,"bdsp4",0);
        (this->field18_0x90)._s_0.bd13 = iVar3;
        iVar3 = BuildObject("bvtank",2,"bdsp4",0);
        (this->field18_0x90)._s_0.bd14 = iVar3;
        SetIndependence(iVar3,1);
        (this->field16_0x40)._s_0.wave4gone = true;
      }
      if (((this->field16_0x40)._s_0.wave4gone == false) &&
         (((fVar5 = GetDistance((this->field18_0x90)._s_0.t1,"nav3",0), fVar5 < 200.0 ||
           (fVar5 = GetDistance((this->field18_0x90)._s_0.t2,"nav3",0), fVar5 < 200.0)) ||
          (fVar5 = GetDistance((this->field18_0x90)._s_0.t3,"nav3",0), fVar5 < 200.0)))) {
        iVar3 = BuildObject("bvartl",2,"bdsp4",0);
        (this->field18_0x90)._s_0.bd12 = iVar3;
        iVar3 = BuildObject("bvartl",2,"bdsp4",0);
        (this->field18_0x90)._s_0.bd13 = iVar3;
        iVar3 = BuildObject("bvtank",2,"bdsp4",0);
        (this->field18_0x90)._s_0.bd14 = iVar3;
        Attack((this->field18_0x90)._s_0.bd12,(this->field18_0x90)._s_0.t1,1);
        Attack((this->field18_0x90)._s_0.bd13,(this->field18_0x90)._s_0.t2,1);
        Follow((this->field18_0x90)._s_0.bd14,(this->field18_0x90)._s_0.bd12,1);
        SetIndependence((this->field18_0x90)._s_0.bd14,1);
        (this->field16_0x40)._s_0.wave4gone = true;
      }
    }
  }
  if ((((((this->field16_0x40)._s_0.wave4gone == true) &&
        ((this->field16_0x40)._s_0.wave3gone == true)) &&
       (((this->field16_0x40)._s_0.bdplatoonspawned == false &&
        ((bVar2 = IsAlive(&(this->field18_0x90)._s_0.bd9), !bVar2 &&
         (bVar2 = IsAlive(&(this->field18_0x90)._s_0.bd10), !bVar2)))))) &&
      (bVar2 = IsAlive(&(this->field18_0x90)._s_0.bd12), !bVar2)) &&
     (bVar2 = IsAlive(&(this->field18_0x90)._s_0.bd13), !bVar2)) {
    iVar3 = BuildObject("bvtank",2,"bdspmain",0);
    (this->field18_0x90)._s_0.bd15 = iVar3;
    iVar3 = BuildObject("bvtank",2,"bdspmain",0);
    (this->field18_0x90)._s_0.bd16 = iVar3;
    iVar3 = BuildObject("bvtank",2,"bdspmain",0);
    (this->field18_0x90)._s_0.bd17 = iVar3;
    iVar4 = BuildObject("bvtank",2,"bdspmain",0);
    iVar3 = (this->field18_0x90)._s_0.t1;
    (this->field18_0x90)._s_0.bd18 = iVar4;
    iVar4 = (this->field18_0x90)._s_0.bd15;
    (this->field16_0x40)._s_0.bdplatoonspawned = true;
    Attack(iVar4,iVar3,1);
    Attack((this->field18_0x90)._s_0.bd16,(this->field18_0x90)._s_0.t1,1);
    Attack((this->field18_0x90)._s_0.bd17,(this->field18_0x90)._s_0.t2,1);
    Attack((this->field18_0x90)._s_0.bd18,(this->field18_0x90)._s_0.t2,1);
  }
  if (((this->field16_0x40)._s_0.wave5gone == false) &&
     ((((fVar5 = GetDistance((this->field18_0x90)._s_0.player,(this->field18_0x90)._s_0.launchpad),
        fVar5 < 550.0 ||
        (fVar5 = GetDistance((this->field18_0x90)._s_0.t1,(this->field18_0x90)._s_0.launchpad),
        fVar5 < 550.0)) ||
       (fVar5 = GetDistance((this->field18_0x90)._s_0.t2,(this->field18_0x90)._s_0.launchpad),
       fVar5 < 550.0)) ||
      (fVar5 = GetDistance((this->field18_0x90)._s_0.t3,(this->field18_0x90)._s_0.launchpad),
      fVar5 < 550.0)))) {
    iVar3 = BuildObject("bvraz",2,"bdsp5",0);
    (this->field18_0x90)._s_0.bd22 = iVar3;
    iVar3 = BuildObject("bvraz",2,"bdsp5",0);
    (this->field18_0x90)._s_0.bd23 = iVar3;
    iVar3 = BuildObject("bvraz",2,"bdsp5",0);
    (this->field18_0x90)._s_0.bd24 = iVar3;
    Attack((this->field18_0x90)._s_0.bd22,(this->field18_0x90)._s_0.t1,1);
    Attack((this->field18_0x90)._s_0.bd23,(this->field18_0x90)._s_0.t2,1);
    Attack((this->field18_0x90)._s_0.bd24,(this->field18_0x90)._s_0.t3,1);
    (this->field16_0x40)._s_0.wave5gone = true;
  }
  if ((this->field16_0x40)._s_0.bdplatoonspawned == false) {
    iVar3 = GetNearestVehicle("bdspmain",1);
    (this->field18_0x90)._s_0.dummy = iVar3;
  }
  fVar5 = GetDistance((this->field18_0x90)._s_0.dummy,"bdspmain",0);
  if (((fVar5 < 420.0) && ((this->field16_0x40)._s_0.bdplatoonspawned == false)) &&
     (iVar3 = GetTeamNum((this->field18_0x90)._s_0.dummy), iVar3 == 1)) {
    iVar3 = BuildObject("bvtank",2,"bdspmain",0);
    (this->field18_0x90)._s_0.bd15 = iVar3;
    iVar3 = BuildObject("bvtank",2,"bdspmain",0);
    (this->field18_0x90)._s_0.bd16 = iVar3;
    iVar3 = BuildObject("bvtank",2,"bdspmain",0);
    (this->field18_0x90)._s_0.bd17 = iVar3;
    iVar3 = BuildObject("bvtank",2,"bdspmain",0);
    (this->field18_0x90)._s_0.bd18 = iVar3;
    iVar3 = BuildObject("bvraz",2,"bdspmain",0);
    (this->field18_0x90)._s_0.bd19 = iVar3;
    iVar3 = BuildObject("bvraz",2,"bdspmain",0);
    (this->field18_0x90)._s_0.bd20 = iVar3;
    iVar3 = BuildObject("bvraz",2,"bdspmain",0);
    (this->field18_0x90)._s_0.bd21 = iVar3;
    (this->field16_0x40)._s_0.bdplatoonspawned = true;
  }
  fVar5 = GetDistance((this->field18_0x90)._s_0.player,"bdnet4",0);
  if ((fVar5 < 550.0) && ((this->field16_0x40)._s_0.camnet1found == false)) {
    iVar3 = BuildObject("bvtank",2,"bdnet4",0);
    (this->field18_0x90)._s_0.cutoff1 = iVar3;
    iVar3 = BuildObject("bvtank",2,"bdnet4",0);
    (this->field18_0x90)._s_0.cutoff2 = iVar3;
    iVar3 = BuildObject("bvraz",2,"bdnet4",0);
    (this->field18_0x90)._s_0.cutoff3 = iVar3;
    iVar3 = BuildObject("bvraz",2,"bdnet4",0);
    (this->field18_0x90)._s_0.cutoff4 = iVar3;
    iVar3 = BuildObject("bvraz",2,"bdnet4",0);
    (this->field18_0x90)._s_0.cutoff5 = iVar3;
    iVar3 = BuildObject("bvraz",2,"bdnet4",0);
    (this->field18_0x90)._s_0.cutoff6 = iVar3;
    Attack((this->field18_0x90)._s_0.cutoff1,(this->field18_0x90)._s_0.t1,1);
    SetIndependence((this->field18_0x90)._s_0.cutoff1,1);
    Attack((this->field18_0x90)._s_0.cutoff2,(this->field18_0x90)._s_0.t1,1);
    SetIndependence((this->field18_0x90)._s_0.cutoff2,1);
    Attack((this->field18_0x90)._s_0.cutoff3,(this->field18_0x90)._s_0.t2,1);
    SetIndependence((this->field18_0x90)._s_0.cutoff3,1);
    Attack((this->field18_0x90)._s_0.cutoff4,(this->field18_0x90)._s_0.t2,1);
    SetIndependence((this->field18_0x90)._s_0.cutoff4,1);
    Attack((this->field18_0x90)._s_0.cutoff5,(this->field18_0x90)._s_0.t3,1);
    SetIndependence((this->field18_0x90)._s_0.cutoff5,1);
    Attack((this->field18_0x90)._s_0.cutoff6,(this->field18_0x90)._s_0.t3,1);
    SetIndependence((this->field18_0x90)._s_0.cutoff6,1);
    (this->field16_0x40)._s_0.camnet1found = true;
    iVar3 = BuildObject("bvartl",2,"bdsp4",0);
    (this->field18_0x90)._s_0.bd12 = iVar3;
    iVar3 = BuildObject("bvartl",2,"bdsp4",0);
    (this->field18_0x90)._s_0.bd13 = iVar3;
    iVar4 = BuildObject("bvtank",2,"bdsp4",0);
    iVar3 = (this->field18_0x90)._s_0.t3;
    (this->field18_0x90)._s_0.bd14 = iVar4;
    iVar4 = (this->field18_0x90)._s_0.bd12;
    (this->field16_0x40)._s_0.wave3gone = true;
    Attack(iVar4,iVar3,1);
    Follow((this->field18_0x90)._s_0.bd13,(this->field18_0x90)._s_0.bd12,1);
    Follow((this->field18_0x90)._s_0.bd14,(this->field18_0x90)._s_0.bd12,1);
  }
  if (((this->field16_0x40)._s_0.camnet1found == true) &&
     ((this->field16_0x40)._s_0.nicetry == false)) {
    iVar3 = GetNearestEnemy((this->field18_0x90)._s_0.cutoff1);
    (this->field18_0x90)._s_0.cutoff = iVar3;
  }
  fVar5 = GetDistance((this->field18_0x90)._s_0.cutoff,(this->field18_0x90)._s_0.cutoff1);
  if ((fVar5 < 400.0) && ((this->field16_0x40)._s_0.nicetry == false)) {
    AudioMessage("misns209.wav");
    (this->field16_0x40)._s_0.nicetry = true;
  }
  fVar5 = GetDistance((this->field18_0x90)._s_0.player,"bdnet9",0);
  if (((fVar5 < 410.0) ||
      (fVar5 = GetDistance((this->field18_0x90)._s_0.player,"bdnet12",0), fVar5 < 410.0)) &&
     ((this->field16_0x40)._s_0.camnet2found == false)) {
    iVar3 = BuildObject("apcamr",2,"bdnet7",0);
    (this->field18_0x90)._s_0.nav7 = iVar3;
    iVar3 = BuildObject("apcamr",2,"bdnet8",0);
    (this->field18_0x90)._s_0.nav8 = iVar3;
    iVar3 = BuildObject("apcamr",2,"bdnet9",0);
    (this->field18_0x90)._s_0.nav9 = iVar3;
    iVar3 = BuildObject("apcamr",2,"bdnet10",0);
    (this->field18_0x90)._s_0.nav10 = iVar3;
    iVar3 = BuildObject("apcamr",2,"bdnet11",0);
    (this->field18_0x90)._s_0.nav11 = iVar3;
    iVar3 = BuildObject("apcamr",2,"bdnet12",0);
    (this->field18_0x90)._s_0.nav12 = iVar3;
    iVar3 = BuildObject("apcamr",2,"bdnet13",0);
    (this->field18_0x90)._s_0.nav13 = iVar3;
    iVar3 = BuildObject("apcamr",2,"bdnet14",0);
    (this->field18_0x90)._s_0.nav14 = iVar3;
    (this->field16_0x40)._s_0.camnet2found = true;
    AudioMessage("misns207.wav");
  }
  if ((this->field16_0x40)._s_0.camnet2found == true) {
    iVar3 = GetNearestVehicle("bdnet7",1);
    (this->field18_0x90)._s_0.one = iVar3;
    iVar3 = GetNearestVehicle("bdnet8",1);
    (this->field18_0x90)._s_0.two = iVar3;
    iVar3 = GetNearestVehicle("bdnet9",1);
    (this->field18_0x90)._s_0.three = iVar3;
    iVar3 = GetNearestVehicle("bdnet10",1);
    (this->field18_0x90)._s_0.four = iVar3;
    iVar3 = GetNearestVehicle("bdnet11",1);
    (this->field18_0x90)._s_0.five = iVar3;
    iVar3 = GetNearestVehicle("bdnet12",1);
    (this->field18_0x90)._s_0.six = iVar3;
    iVar3 = GetNearestVehicle("bdnet13",1);
    (this->field18_0x90)._s_0.seven = iVar3;
    iVar3 = GetNearestVehicle("bdnet14",1);
    (this->field18_0x90)._s_0.eight = iVar3;
    fVar5 = GetDistance((this->field18_0x90)._s_0.one,"bdnet7",0);
    if (((((fVar5 < 20.0) ||
          (fVar5 = GetDistance((this->field18_0x90)._s_0.two,"bdnet8",0), fVar5 < 20.0)) ||
         ((fVar5 = GetDistance((this->field18_0x90)._s_0.three,"bdnet9",0), fVar5 < 20.0 ||
          ((fVar5 = GetDistance((this->field18_0x90)._s_0.four,"bdnet10",0), fVar5 < 20.0 ||
           (fVar5 = GetDistance((this->field18_0x90)._s_0.five,"bdnet11",0), fVar5 < 20.0)))))) ||
        ((fVar5 = GetDistance((this->field18_0x90)._s_0.six,"bdnet12",0), fVar5 < 20.0 ||
         ((fVar5 = GetDistance((this->field18_0x90)._s_0.seven,"bdnet13",0), fVar5 < 20.0 ||
          (fVar5 = GetDistance((this->field18_0x90)._s_0.eight,"bdnet14",0), fVar5 < 20.0)))))) &&
       ((this->field16_0x40)._s_0.wave3gone == false)) {
      iVar3 = BuildObject("bvartl",2,"bdsp3",0);
      (this->field18_0x90)._s_0.bd9 = iVar3;
      iVar3 = BuildObject("bvartl",2,"bdsp3",0);
      (this->field18_0x90)._s_0.bd10 = iVar3;
      iVar3 = BuildObject("bvtank",2,"bdsp3",0);
      (this->field18_0x90)._s_0.bd11 = iVar3;
      Attack((this->field18_0x90)._s_0.bd9,(this->field18_0x90)._s_0.t3,1);
      Attack((this->field18_0x90)._s_0.bd10,(this->field18_0x90)._s_0.t2,1);
      Follow((this->field18_0x90)._s_0.bd11,(this->field18_0x90)._s_0.bd9,1);
      (this->field16_0x40)._s_0.wave3gone = true;
    }
    if (((this->field16_0x40)._s_0.camnet2found == true) &&
       (((((((bVar2 = IsAlive(&(this->field18_0x90)._s_0.nav7), !bVar2 ||
             (bVar2 = IsAlive(&(this->field18_0x90)._s_0.nav8), !bVar2)) ||
            (bVar2 = IsAlive(&(this->field18_0x90)._s_0.nav9), !bVar2)) ||
           ((bVar2 = IsAlive(&(this->field18_0x90)._s_0.nav10), !bVar2 ||
            (bVar2 = IsAlive(&(this->field18_0x90)._s_0.nav11), !bVar2)))) ||
          (bVar2 = IsAlive(&(this->field18_0x90)._s_0.nav12), !bVar2)) ||
         ((bVar2 = IsAlive(&(this->field18_0x90)._s_0.nav13), !bVar2 ||
          (bVar2 = IsAlive(&(this->field18_0x90)._s_0.nav14), !bVar2)))) &&
        ((this->field16_0x40)._s_0.sneaktimeset == false)))) {
      fVar5 = Get_Time();
      (this->field17_0x68)._s_0.sneaktime = fVar5 + 45.0;
      (this->field16_0x40)._s_0.sneaktimeset = true;
      AudioMessage("misns208.wav");
    }
  }
  fVar5 = Get_Time();
  if (((this->field17_0x68)._s_0.sneaktime < fVar5) &&
     ((this->field16_0x40)._s_0.patrolsent == false)) {
    iVar3 = BuildObject("svfigh",2,"bdspmain",0);
    (this->field18_0x90)._s_0.pat1 = iVar3;
    iVar3 = BuildObject("svfigh",2,"bdspmain",0);
    (this->field18_0x90)._s_0.pat2 = iVar3;
    (this->field16_0x40)._s_0.patrolsent = true;
    Goto((this->field18_0x90)._s_0.pat1,"bdnet9",1);
    Goto((this->field18_0x90)._s_0.pat2,"bdnet12",1);
  }
  if ((this->field16_0x40)._s_0.patrolsent == true) {
    if ((this->field16_0x40)._s_0.playerfound == false) {
      iVar3 = GetNearestEnemy((this->field18_0x90)._s_0.pat1);
      (this->field18_0x90)._s_0.ten = iVar3;
      iVar3 = GetNearestEnemy((this->field18_0x90)._s_0.pat2);
      (this->field18_0x90)._s_0.nine = iVar3;
      fVar5 = GetDistance(iVar3,(this->field18_0x90)._s_0.pat1);
      if ((fVar5 < 50.0) && ((this->field16_0x40)._s_0.wave3gone == false)) {
        iVar3 = BuildObject("bvartl",2,"bdsp3",0);
        (this->field18_0x90)._s_0.bd9 = iVar3;
        iVar3 = BuildObject("bvartl",2,"bdsp3",0);
        (this->field18_0x90)._s_0.bd10 = iVar3;
        iVar3 = BuildObject("bvtank",2,"bdsp3",0);
        (this->field18_0x90)._s_0.bd11 = iVar3;
        Attack((this->field18_0x90)._s_0.bd9,(this->field18_0x90)._s_0.t3,1);
        Attack((this->field18_0x90)._s_0.bd10,(this->field18_0x90)._s_0.t2,1);
        Follow((this->field18_0x90)._s_0.bd11,(this->field18_0x90)._s_0.bd9,1);
        (this->field16_0x40)._s_0.wave3gone = true;
        bVar2 = IsAlive(&(this->field18_0x90)._s_0.bd9);
        if (bVar2) {
          Attack((this->field18_0x90)._s_0.bd9,(this->field18_0x90)._s_0.nine,1);
        }
        bVar2 = IsAlive(&(this->field18_0x90)._s_0.bd10);
        if (bVar2) {
          Attack((this->field18_0x90)._s_0.bd10,(this->field18_0x90)._s_0.nine,1);
        }
        bVar2 = IsAlive(&(this->field18_0x90)._s_0.bd11);
        if (bVar2) {
          Follow((this->field18_0x90)._s_0.bd11,(this->field18_0x90)._s_0.bd9,1);
        }
        (this->field16_0x40)._s_0.wave3gone = true;
      }
      fVar5 = GetDistance((this->field18_0x90)._s_0.nine,(this->field18_0x90)._s_0.pat1);
      if ((fVar5 < 50.0) && ((this->field16_0x40)._s_0.wave3gone == false)) {
        iVar3 = BuildObject("bvartl",2,"bdsp3",0);
        (this->field18_0x90)._s_0.bd9 = iVar3;
        iVar3 = BuildObject("bvartl",2,"bdsp3",0);
        (this->field18_0x90)._s_0.bd10 = iVar3;
        iVar3 = BuildObject("bvtank",2,"bdsp3",0);
        (this->field18_0x90)._s_0.bd11 = iVar3;
        Attack((this->field18_0x90)._s_0.bd9,(this->field18_0x90)._s_0.ten,1);
        Attack((this->field18_0x90)._s_0.bd10,(this->field18_0x90)._s_0.ten,1);
        Follow((this->field18_0x90)._s_0.bd11,(this->field18_0x90)._s_0.bd9,1);
        (this->field16_0x40)._s_0.wave3gone = true;
        bVar2 = IsAlive(&(this->field18_0x90)._s_0.bd9);
        if (bVar2) {
          Attack((this->field18_0x90)._s_0.bd9,(this->field18_0x90)._s_0.ten,1);
        }
        bVar2 = IsAlive(&(this->field18_0x90)._s_0.bd10);
        if (bVar2) {
          Attack((this->field18_0x90)._s_0.bd10,(this->field18_0x90)._s_0.ten,1);
        }
        bVar2 = IsAlive(&(this->field18_0x90)._s_0.bd11);
        if (bVar2) {
          Follow((this->field18_0x90)._s_0.bd11,(this->field18_0x90)._s_0.ten,1);
        }
        (this->field16_0x40)._s_0.wave3gone = true;
      }
    }
    if ((this->field16_0x40)._s_0.patrolsent == true) {
      if (((this->field16_0x40)._s_0.playerfound == false) &&
         (((fVar5 = GetDistance((this->field18_0x90)._s_0.pat1,"bdnet9",0), fVar5 < 20.0 ||
           (fVar5 = GetDistance((this->field18_0x90)._s_0.pat2,"bdnet12",0), fVar5 < 20.0)) &&
          ((this->field16_0x40)._s_0.bdplatoonspawned == false)))) {
        iVar3 = BuildObject("bvtank",2,"bdspmain",0);
        (this->field18_0x90)._s_0.bd15 = iVar3;
        iVar3 = BuildObject("bvtank",2,"bdspmain",0);
        (this->field18_0x90)._s_0.bd16 = iVar3;
        iVar3 = BuildObject("bvtank",2,"bdspmain",0);
        (this->field18_0x90)._s_0.bd17 = iVar3;
        iVar3 = BuildObject("bvtank",2,"bdspmain",0);
        (this->field18_0x90)._s_0.bd18 = iVar3;
        iVar3 = BuildObject("bvraz",2,"bdspmain",0);
        (this->field18_0x90)._s_0.bd19 = iVar3;
        iVar3 = BuildObject("bvraz",2,"bdspmain",0);
        (this->field18_0x90)._s_0.bd20 = iVar3;
        iVar4 = BuildObject("bvraz",2,"bdspmain",0);
        iVar3 = (this->field18_0x90)._s_0.t1;
        (this->field18_0x90)._s_0.bd21 = iVar4;
        iVar4 = (this->field18_0x90)._s_0.bd15;
        (this->field16_0x40)._s_0.bdplatoonspawned = true;
        Attack(iVar4,iVar3,1);
        SetIndependence((this->field18_0x90)._s_0.bd15,1);
        Attack((this->field18_0x90)._s_0.bd16,(this->field18_0x90)._s_0.t1,1);
        SetIndependence((this->field18_0x90)._s_0.bd16,1);
        Attack((this->field18_0x90)._s_0.bd17,(this->field18_0x90)._s_0.t2,1);
        SetIndependence((this->field18_0x90)._s_0.bd17,1);
        Attack((this->field18_0x90)._s_0.bd18,(this->field18_0x90)._s_0.t2,1);
        SetIndependence((this->field18_0x90)._s_0.bd18,1);
        Attack((this->field18_0x90)._s_0.bd19,(this->field18_0x90)._s_0.t3,1);
        SetIndependence((this->field18_0x90)._s_0.bd19,1);
        Attack((this->field18_0x90)._s_0.bd20,(this->field18_0x90)._s_0.t3,1);
        SetIndependence((this->field18_0x90)._s_0.bd20,1);
        Attack((this->field18_0x90)._s_0.bd21,(this->field18_0x90)._s_0.t1,1);
        SetIndependence((this->field18_0x90)._s_0.bd21,1);
      }
      if ((((this->field16_0x40)._s_0.patrolsent == true) &&
          ((this->field16_0x40)._s_0.playerfound == false)) &&
         ((fVar5 = GetDistance((this->field18_0x90)._s_0.pat1,"bdnet9",0), fVar5 < 20.0 ||
          (fVar5 = GetDistance((this->field18_0x90)._s_0.pat2,"bdnet12",0), fVar5 < 20.0)))) {
        if ((this->field16_0x40)._s_0.wave3gone == false) {
          iVar3 = BuildObject("bvartl",2,"bdsp3",0);
          (this->field18_0x90)._s_0.bd9 = iVar3;
          iVar3 = BuildObject("bvartl",2,"bdsp3",0);
          (this->field18_0x90)._s_0.bd10 = iVar3;
          iVar3 = BuildObject("bvtank",2,"bdsp3",0);
          (this->field18_0x90)._s_0.bd11 = iVar3;
          Attack((this->field18_0x90)._s_0.bd9,(this->field18_0x90)._s_0.t3,1);
          Attack((this->field18_0x90)._s_0.bd10,(this->field18_0x90)._s_0.t2,1);
          Follow((this->field18_0x90)._s_0.bd11,(this->field18_0x90)._s_0.bd9,1);
          (this->field16_0x40)._s_0.wave3gone = true;
        }
        if ((this->field16_0x40)._s_0.wave3gone == true) {
          piVar1 = &(this->field18_0x90)._s_0.bd9;
          bVar2 = IsAlive(piVar1);
          if (bVar2) {
            Attack(*piVar1,(this->field18_0x90)._s_0.t3,1);
          }
          bVar2 = IsAlive(&(this->field18_0x90)._s_0.bd10);
          if (bVar2) {
            Attack((this->field18_0x90)._s_0.bd10,(this->field18_0x90)._s_0.t2,1);
          }
          bVar2 = IsAlive(&(this->field18_0x90)._s_0.bd11);
          if (bVar2) {
            Follow((this->field18_0x90)._s_0.bd11,*piVar1,1);
          }
        }
        (this->field16_0x40)._s_0.wave3gone = true;
      }
    }
  }
  bVar2 = IsAlive(&(this->field18_0x90)._s_0.t1);
  if ((!bVar2) && ((this->field16_0x40)._s_0.missionfail == false)) {
    iVar3 = AudioMessage("misns212.wav");
    (this->field19_0x234)._s_0.aud10 = iVar3;
    (this->field16_0x40)._s_0.missionfail = true;
    (this->field16_0x40)._s_0.newobjective = true;
  }
  bVar2 = IsAlive(&(this->field18_0x90)._s_0.t2);
  if ((!bVar2) && ((this->field16_0x40)._s_0.missionfail == false)) {
    iVar3 = AudioMessage("misns212.wav");
    (this->field19_0x234)._s_0.aud10 = iVar3;
    (this->field16_0x40)._s_0.missionfail = true;
    (this->field16_0x40)._s_0.newobjective = true;
  }
  bVar2 = IsAlive(&(this->field18_0x90)._s_0.t3);
  if ((!bVar2) && ((this->field16_0x40)._s_0.missionfail == false)) {
    iVar3 = AudioMessage("misns212.wav");
    (this->field19_0x234)._s_0.aud10 = iVar3;
    (this->field16_0x40)._s_0.missionfail = true;
    (this->field16_0x40)._s_0.newobjective = true;
  }
  if (((this->field16_0x40)._s_0.missionfail == true) &&
     (bVar2 = IsAudioMessageDone((this->field19_0x234)._s_0.aud10), bVar2)) {
    pcVar6 = "misns2l1.des";
    fVar5 = Get_Time();
    FailMission(fVar5,pcVar6);
  }
  fVar5 = GetDistance((this->field18_0x90)._s_0.t1,(this->field18_0x90)._s_0.launchpad);
  if ((fVar5 < 100.0) && ((this->field16_0x40)._s_0.t1arrive == false)) {
    AudioMessage("misns216.wav");
    (this->field16_0x40)._s_0.t1arrive = true;
    (this->field16_0x40)._s_0.newobjective = true;
  }
  fVar5 = GetDistance((this->field18_0x90)._s_0.t2,(this->field18_0x90)._s_0.launchpad);
  if ((fVar5 < 100.0) && ((this->field16_0x40)._s_0.t2arrive == false)) {
    AudioMessage("misns217.wav");
    (this->field16_0x40)._s_0.t2arrive = true;
    (this->field16_0x40)._s_0.newobjective = true;
  }
  fVar5 = GetDistance((this->field18_0x90)._s_0.t3,(this->field18_0x90)._s_0.launchpad);
  if ((fVar5 < 100.0) && ((this->field16_0x40)._s_0.t3arrive == false)) {
    AudioMessage("misns218.wav");
    (this->field16_0x40)._s_0.t3arrive = true;
    (this->field16_0x40)._s_0.newobjective = true;
  }
  if (((((this->field16_0x40)._s_0.missionwon == false) &&
       ((this->field16_0x40)._s_0.t1arrive == true)) && ((this->field16_0x40)._s_0.t2arrive == true)
      ) && ((this->field16_0x40)._s_0.t3arrive == true)) {
    (this->field16_0x40)._s_0.missionwon = true;
    iVar3 = AudioMessage("misns213.wav");
    (this->field19_0x234)._s_0.aud50 = iVar3;
    iVar3 = AudioMessage("misns214.wav");
    (this->field19_0x234)._s_0.aud51 = iVar3;
    iVar3 = AudioMessage("misns215.wav");
    piVar1 = &(this->field18_0x90)._s_0.bd3;
    (this->field19_0x234)._s_0.aud52 = iVar3;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd4;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd5;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd6;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd7;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd8;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd9;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd10;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd11;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd12;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd13;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd14;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd15;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd16;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd17;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd18;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd19;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd20;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd21;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd22;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd23;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd24;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd25;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd26;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd27;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd100;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd101;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd102;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd103;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd104;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd105;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd106;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd107;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd108;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd109;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.bd110;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.cutoff1;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.cutoff2;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.cutoff3;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.cutoff4;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.cutoff5;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.cutoff6;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.pat1;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
    piVar1 = &(this->field18_0x90)._s_0.pat2;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Retreat(*piVar1,"bdspmain",1000);
    }
  }
  if ((((this->field16_0x40)._s_0.missionwon == true) &&
      (bVar2 = IsAudioMessageDone((this->field19_0x234)._s_0.aud50), bVar2)) &&
     ((bVar2 = IsAudioMessageDone((this->field19_0x234)._s_0.aud51), bVar2 &&
      (bVar2 = IsAudioMessageDone((this->field19_0x234)._s_0.aud52), bVar2)))) {
    pcVar6 = "misns2w1.des";
    fVar5 = Get_Time();
    SucceedMission(fVar5,pcVar6);
  }
  return;
}
