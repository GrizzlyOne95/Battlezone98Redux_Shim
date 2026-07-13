/*
 * Entry: 0043eeef
 * Name: Misns1Mission::Execute
 * Namespace: Misns1Mission
 * Signature: void Execute(Misns1Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns1Mission::Execute(Misns1Mission *this)

{
  Misns1Mission_u_244 *pMVar1;
  int *piVar2;
  float *pfVar3;
  bool bVar4;
  int iVar5;
  uint uVar6;
  float fVar7;
  char *pcVar8;
  
  if ((this->field16_0x40)._s_0.missionstart == false) {
    AudioMessage("misns101.wav");
    iVar5 = GetHandle("eggeizr10_geyser");
    (this->field18_0xf4)._s_0.geyser = iVar5;
    iVar5 = GetHandle("avmuf1_factory");
    (this->field18_0xf4)._s_0.muf = iVar5;
    iVar5 = GetHandle("absilo1_i76building");
    (this->field18_0xf4)._s_0.silo = iVar5;
    iVar5 = GetHandle("avrecy1_recycler");
    (this->field18_0xf4)._s_0.colorado = iVar5;
    iVar5 = GetHandle("svrecy2_recycler");
    (this->field18_0xf4)._s_0.svrec = iVar5;
    SetScrap(2,0x32);
    SetScrap(1,0x14);
    iVar5 = GetHandle("avfigh3_wingman");
    (this->field18_0xf4)._s_0.ef1 = iVar5;
    iVar5 = GetHandle("avfigh4_wingman");
    (this->field18_0xf4)._s_0.ef2 = iVar5;
    iVar5 = GetHandle("avfigh5_wingman");
    (this->field18_0xf4)._s_0.ef3 = iVar5;
    iVar5 = GetHandle("avtank5_wingman");
    (this->field18_0xf4)._s_0.et1 = iVar5;
    iVar5 = GetHandle("avtank6_wingman");
    (this->field18_0xf4)._s_0.et2 = iVar5;
    iVar5 = GetHandle("avtank7_wingman");
    (this->field18_0xf4)._s_0.et3 = iVar5;
    iVar5 = GetHandle("avtank8_wingman");
    (this->field18_0xf4)._s_0.et4 = iVar5;
    iVar5 = GetHandle("ambase");
    (this->field18_0xf4)._s_0.ambase = iVar5;
    iVar5 = BuildObject("svwalk",1,"spawnwalker1",0);
    (this->field18_0xf4)._s_0.walker1 = iVar5;
    iVar5 = BuildObject("apcamr",1,"walkcam1",0);
    (this->field18_0xf4)._s_0.walkcam1 = iVar5;
    iVar5 = BuildObject("apcamr",1,"hidcamupper",0);
    (this->field18_0xf4)._s_0.hidcam1 = iVar5;
    iVar5 = BuildObject("apcamr",1,"hidcammiddle",0);
    (this->field18_0xf4)._s_0.hidcam2 = iVar5;
    iVar5 = BuildObject("apcamr",1,"hidcamlower",0);
    (this->field18_0xf4)._s_0.hidcam3 = iVar5;
    iVar5 = GetHandle("apcamr0_camerapod");
    (this->field18_0xf4)._s_0.basecam = iVar5;
    SetObjectiveName((this->field18_0xf4)._s_0.walkcam1,"Walker Cut Off");
    SetObjectiveName((this->field18_0xf4)._s_0.ambase,"American Outpost");
    SetObjectiveName((this->field18_0xf4)._s_0.hidcam1,"Upper Pass Exit");
    SetObjectiveName((this->field18_0xf4)._s_0.hidcam2,"Middle Pass Exit");
    SetObjectiveName((this->field18_0xf4)._s_0.hidcam3,"Lower Pass Exit");
    SetObjectiveName((this->field18_0xf4)._s_0.basecam,"Home Base");
    RemoveObject((this->field18_0xf4)._s_0.et3);
    RemoveObject((this->field18_0xf4)._s_0.et4);
    BuildObject("svtank",1,"tank1",0);
    BuildObject("svtank",1,"tank2",0);
    BuildObject("svfigh",1,"figh1",0);
    BuildObject("svturr",1,"turr1",0);
    BuildObject("svturr",1,"turr2",0);
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.startconvoy = fVar7 + 180.0;
    (this->field16_0x40)._s_0.missionstart = true;
    SetScrap(1,0x14);
    SetScrap(2,0x32);
    iVar5 = rand();
    (this->field19_0x1ac)._s_0.path = iVar5 % 3;
    uVar6 = rand();
    uVar6 = uVar6 & 0x80000003;
    if ((int)uVar6 < 0) {
      uVar6 = (uVar6 - 1 | 0xfffffffc) + 1;
    }
    (this->field19_0x1ac)._s_0.cav = uVar6;
    (this->field16_0x40)._s_0.newobjective = true;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.cintime = fVar7 + 11.0;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.cintime05 = fVar7 + 11.1;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.cintime2 = fVar7 + 20.0;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.cintime3 = fVar7 + 27.0;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.cintime4 = fVar7 + 29.0;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.cintime5 = fVar7 + 31.0;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.cintime6 = fVar7 + 33.0;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.cintime7 = fVar7 + 44.0;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.cintime8 = fVar7 + 46.0;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.cintime9 = fVar7 + 48.0;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.cintime09 = fVar7 + 50.0;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.cintime10 = fVar7 + 60.0;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.cintime11 = fVar7 + 66.0;
  }
  pMVar1 = &this->field18_0xf4;
  IsAlive(pMVar1->h_array);
  if ((this->field16_0x40)._s_0.newobjective == true) {
    InfoDisplay::ClearObjectives(&infoDisplay);
    bVar4 = IsAlive(pMVar1->h_array);
    if ((bVar4) && ((this->field16_0x40)._s_0.coloradosafe == false)) {
      InfoDisplay::AddObjective(&infoDisplay,"misns101.otf",DisplayInterface::colorWhite,8.0);
    }
    bVar4 = IsAlive(pMVar1->h_array);
    if ((!bVar4) && ((this->field16_0x40)._s_0.coloradosafe == false)) {
      InfoDisplay::AddObjective(&infoDisplay,"misns101.otf",DisplayInterface::colorGreen,8.0);
    }
    if ((this->field16_0x40)._s_0.coloradoreachedsafepoint == true) {
      InfoDisplay::AddObjective(&infoDisplay,"misns101.otf",DisplayInterface::colorRed,8.0);
    }
    if (((this->field16_0x40)._s_0.coloradosafe == false) &&
       ((bVar4 = IsAlive(&(this->field18_0xf4)._s_0.muf), bVar4 ||
        (bVar4 = IsAlive(&(this->field18_0xf4)._s_0.silo), bVar4)))) {
      InfoDisplay::AddObjective(&infoDisplay,"misns102.otf",DisplayInterface::colorWhite,8.0);
    }
    if (((this->field16_0x40)._s_0.coloradosafe == true) &&
       (((bVar4 = IsAlive(&(this->field18_0xf4)._s_0.muf), bVar4 ||
         (bVar4 = IsAlive(&(this->field18_0xf4)._s_0.silo), bVar4)) ||
        (bVar4 = IsAlive(pMVar1->h_array), bVar4)))) {
      InfoDisplay::AddObjective(&infoDisplay,"misns102.otf",DisplayInterface::colorWhite,8.0);
    }
    if ((((this->field16_0x40)._s_0.coloradosafe == false) &&
        (bVar4 = IsAlive(&(this->field18_0xf4)._s_0.muf), !bVar4)) &&
       (bVar4 = IsAlive(&(this->field18_0xf4)._s_0.silo), !bVar4)) {
      InfoDisplay::AddObjective(&infoDisplay,"misns102.otf",DisplayInterface::colorGreen,8.0);
    }
    if ((((this->field16_0x40)._s_0.coloradosafe == true) &&
        (bVar4 = IsAlive(&(this->field18_0xf4)._s_0.muf), !bVar4)) &&
       ((bVar4 = IsAlive(&(this->field18_0xf4)._s_0.silo), !bVar4 &&
        (bVar4 = IsAlive(pMVar1->h_array), !bVar4)))) {
      InfoDisplay::AddObjective(&infoDisplay,"misns102.otf",DisplayInterface::colorGreen,8.0);
    }
    bVar4 = IsAlive(&(this->field18_0xf4)._s_0.svrec);
    if ((bVar4) && ((this->field16_0x40)._s_0.missionwon == false)) {
      InfoDisplay::AddObjective(&infoDisplay,"misns103.otf",DisplayInterface::colorWhite,8.0);
    }
    bVar4 = IsAlive(&(this->field18_0xf4)._s_0.svrec);
    if (!bVar4) {
      InfoDisplay::AddObjective(&infoDisplay,"misns103.otf",DisplayInterface::colorRed,8.0);
    }
    if ((this->field16_0x40)._s_0.missionwon == true) {
      InfoDisplay::AddObjective(&infoDisplay,"misns103.otf",DisplayInterface::colorGreen,8.0);
    }
    if (((this->field16_0x40)._s_0.coloradosafe == true) &&
       ((this->field16_0x40)._s_0.missionwon == false)) {
      InfoDisplay::AddObjective(&infoDisplay,"misns101.otf",DisplayInterface::colorRed,8.0);
    }
    (this->field16_0x40)._s_0.newobjective = false;
  }
  if (((this->field16_0x40)._s_0.pickpath == false) &&
     (fVar7 = Get_Time(), (this->field17_0x84)._s_0.startconvoy < fVar7)) {
    iVar5 = (this->field19_0x1ac)._s_0.path;
    if (iVar5 == 0) {
      Follow((this->field18_0xf4)._s_0.ef1,(pMVar1->_s_0).colorado,1);
      Follow((this->field18_0xf4)._s_0.ef2,(pMVar1->_s_0).colorado,1);
      Follow((this->field18_0xf4)._s_0.ef3,(pMVar1->_s_0).colorado,1);
      pcVar8 = "upperpath";
LAB_0043f5a9:
      Goto((pMVar1->_s_0).colorado,pcVar8,1);
      Follow((this->field18_0xf4)._s_0.et1,(pMVar1->_s_0).colorado,1);
      Follow((this->field18_0xf4)._s_0.et2,(pMVar1->_s_0).colorado,1);
    }
    else {
      if (iVar5 == 1) {
        Follow((this->field18_0xf4)._s_0.ef1,(pMVar1->_s_0).colorado,1);
        Follow((this->field18_0xf4)._s_0.ef2,(pMVar1->_s_0).colorado,1);
        Follow((this->field18_0xf4)._s_0.ef3,(pMVar1->_s_0).colorado,1);
        pcVar8 = "midpath";
        goto LAB_0043f5a9;
      }
      if (iVar5 == 2) {
        Follow((this->field18_0xf4)._s_0.ef1,(pMVar1->_s_0).colorado,1);
        Follow((this->field18_0xf4)._s_0.ef2,(pMVar1->_s_0).colorado,1);
        Follow((this->field18_0xf4)._s_0.ef3,(pMVar1->_s_0).colorado,1);
        pcVar8 = "lowerpath";
        goto LAB_0043f5a9;
      }
    }
    SetIndependence((this->field18_0xf4)._s_0.ef1,1);
    SetIndependence((this->field18_0xf4)._s_0.ef2,1);
    SetIndependence((this->field18_0xf4)._s_0.ef3,1);
    SetIndependence((this->field18_0xf4)._s_0.et1,1);
    SetIndependence((this->field18_0xf4)._s_0.et2,1);
    (this->field16_0x40)._s_0.pickpath = true;
    AudioMessage("misns125.wav");
  }
  fVar7 = GetDistance((this->field18_0xf4)._s_0.walker1,(this->field18_0xf4)._s_0.walkcam1);
  if ((((fVar7 < 50.0) && ((this->field16_0x40)._s_0.trapset == false)) &&
      ((this->field16_0x40)._s_0.blockaderun == false)) && (bVar4 = IsAlive(pMVar1->h_array), bVar4)
     ) {
    (this->field16_0x40)._s_0.trapset = true;
    AudioMessage("misns123.wav");
  }
  if (((this->field16_0x40)._s_0.halfwaywarn == true) &&
     ((this->field16_0x40)._s_0.blockaderun == false)) {
    if (((this->field19_0x1ac)._s_0.path == 0) &&
       (fVar7 = GetDistance((pMVar1->_s_0).colorado,(this->field18_0xf4)._s_0.hidcam1), fVar7 < 70.0
       )) {
      (this->field16_0x40)._s_0.blockaderun = true;
      AudioMessage("misns124.wav");
    }
    if (((this->field19_0x1ac)._s_0.path == 1) &&
       (fVar7 = GetDistance((pMVar1->_s_0).colorado,(this->field18_0xf4)._s_0.hidcam2), fVar7 < 70.0
       )) {
      (this->field16_0x40)._s_0.blockaderun = true;
      AudioMessage("misns124.wav");
    }
    if (((this->field19_0x1ac)._s_0.path == 2) &&
       (fVar7 = GetDistance((pMVar1->_s_0).colorado,(this->field18_0xf4)._s_0.hidcam3), fVar7 < 70.0
       )) {
      (this->field16_0x40)._s_0.blockaderun = true;
      AudioMessage("misns124.wav");
    }
  }
  if (((this->field16_0x40)._s_0.retreat == false) &&
     ((this->field16_0x40)._s_0.blockaderun == false)) {
    iVar5 = GetNearestEnemy((pMVar1->_s_0).colorado);
    (this->field18_0xf4)._s_0.hostile = iVar5;
    fVar7 = GetDistance(iVar5,(pMVar1->_s_0).colorado);
    if (fVar7 < 200.0) {
      (this->field16_0x40)._s_0.retreat = true;
      AudioMessage("misns114.wav");
    }
  }
  if ((this->field16_0x40)._s_0.retreatpathset == false) {
    if ((this->field16_0x40)._s_0.retreat == true) {
      Goto((pMVar1->_s_0).colorado,"retreat1",1);
      Attack((this->field18_0xf4)._s_0.ef1,(this->field18_0xf4)._s_0.hostile,1);
      Follow((this->field18_0xf4)._s_0.ef2,(this->field18_0xf4)._s_0.ef1,1);
      Follow((this->field18_0xf4)._s_0.et3,(this->field18_0xf4)._s_0.ef1,1);
      SetIndependence((this->field18_0xf4)._s_0.ef1,1);
      SetIndependence((this->field18_0xf4)._s_0.ef2,1);
      SetIndependence((this->field18_0xf4)._s_0.et3,1);
      (this->field16_0x40)._s_0.retreatpathset = true;
      goto LAB_0043f7c1;
    }
  }
  else {
LAB_0043f7c1:
    if ((((this->field16_0x40)._s_0.retreat == true) &&
        (fVar7 = GetDistance((pMVar1->_s_0).colorado,(this->field18_0xf4)._s_0.geyser), fVar7 < 50.0
        )) && ((this->field16_0x40)._s_0.coloradosafe == false)) {
      (this->field16_0x40)._s_0.coloradosafe = true;
      SetAIP("misn09.aip",2);
      SetObjectiveOn((pMVar1->_s_0).colorado);
      SetObjectiveOn((this->field18_0xf4)._s_0.silo);
      SetObjectiveOn((this->field18_0xf4)._s_0.muf);
      AudioMessage("misns106.wav");
      fVar7 = Get_Time();
      (this->field17_0x84)._s_0.aw1at = fVar7 + 25.0;
      fVar7 = Get_Time();
      (this->field17_0x84)._s_0.aw1bt = fVar7 + 30.0;
      fVar7 = Get_Time();
      (this->field17_0x84)._s_0.aw1ct = fVar7 + 35.0;
      fVar7 = Get_Time();
      (this->field17_0x84)._s_0.aw2at = fVar7 + 90.0;
      fVar7 = Get_Time();
      (this->field17_0x84)._s_0.aw2bt = fVar7 + 95.0;
      fVar7 = Get_Time();
      (this->field17_0x84)._s_0.aw2ct = fVar7 + 100.0;
      fVar7 = Get_Time();
      (this->field17_0x84)._s_0.aw3at = fVar7 + 190.0;
      fVar7 = Get_Time();
      (this->field17_0x84)._s_0.aw3bt = fVar7 + 195.0;
      fVar7 = Get_Time();
      (this->field17_0x84)._s_0.aw3ct = fVar7 + 200.0;
      fVar7 = Get_Time();
      (this->field17_0x84)._s_0.du1at = fVar7 + 60.0;
      fVar7 = Get_Time();
      (this->field16_0x40)._s_0.newobjective = true;
      (this->field17_0x84)._s_0.du1bt = fVar7 + 75.0;
    }
  }
  bVar4 = IsAlive(pMVar1->h_array);
  if ((!bVar4) && ((this->field16_0x40)._s_0.escortretreat == false)) {
    Goto((this->field18_0xf4)._s_0.ef1,(this->field18_0xf4)._s_0.muf,1000);
    Goto((this->field18_0xf4)._s_0.ef2,(this->field18_0xf4)._s_0.muf,1000);
    Goto((this->field18_0xf4)._s_0.ef3,(this->field18_0xf4)._s_0.muf,1000);
    (this->field16_0x40)._s_0.escortretreat = true;
  }
  if ((((this->field16_0x40)._s_0.safety1 == false) &&
      ((this->field16_0x40)._s_0.coloradosafe == false)) &&
     (bVar4 = IsAlive(pMVar1->h_array), !bVar4)) {
    SetAIP("misn14.aip",2);
    iVar5 = BuildObject("avscav",2,(this->field18_0xf4)._s_0.muf);
    (this->field18_0xf4)._s_0.scav1 = iVar5;
    iVar5 = BuildObject("avscav",2,(this->field18_0xf4)._s_0.muf);
    (this->field18_0xf4)._s_0.scav2 = iVar5;
    SetObjectiveOn((this->field18_0xf4)._s_0.silo);
    SetObjectiveOn((this->field18_0xf4)._s_0.muf);
    (this->field16_0x40)._s_0.safety1 = true;
    AudioMessage("misns105.wav");
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.aw1at = fVar7 + 25.0;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.aw1bt = fVar7 + 35.0;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.aw1ct = fVar7 + 40.0;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.aw2at = fVar7 + 90.0;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.aw2bt = fVar7 + 95.0;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.aw2ct = fVar7 + 100.0;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.aw3at = fVar7 + 190.0;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.aw3bt = fVar7 + 195.0;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.aw3ct = fVar7 + 200.0;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.du1at = fVar7 + 60.0;
    fVar7 = Get_Time();
    (this->field16_0x40)._s_0.newobjective = true;
    (this->field17_0x84)._s_0.du1bt = fVar7 + 75.0;
  }
  fVar7 = Get_Time();
  if (((this->field17_0x84)._s_0.aw1at < fVar7) && ((this->field16_0x40)._s_0.aw1amade == false)) {
    piVar2 = &(this->field18_0xf4)._s_0.muf;
    bVar4 = IsAlive(piVar2);
    if (bVar4) {
      BuildObject("avtank",2,*piVar2);
      (this->field16_0x40)._s_0.aw1amade = true;
    }
  }
  fVar7 = Get_Time();
  if ((((this->field17_0x84)._s_0.aw1bt < fVar7) && ((this->field16_0x40)._s_0.aw1bmade == false))
     && (bVar4 = IsAlive(&(this->field18_0xf4)._s_0.muf), bVar4)) {
    BuildObject("avfigh",2,(this->field18_0xf4)._s_0.muf);
    (this->field16_0x40)._s_0.aw1bmade = true;
  }
  fVar7 = Get_Time();
  if ((((this->field17_0x84)._s_0.aw1ct < fVar7) && ((this->field16_0x40)._s_0.aw1cmade == false))
     && (bVar4 = IsAlive(&(this->field18_0xf4)._s_0.muf), bVar4)) {
    BuildObject("avfigh",2,(this->field18_0xf4)._s_0.muf);
    (this->field16_0x40)._s_0.aw1cmade = true;
  }
  fVar7 = Get_Time();
  if (((this->field17_0x84)._s_0.aw2at < fVar7) && ((this->field16_0x40)._s_0.aw2amade == false)) {
    piVar2 = &(this->field18_0xf4)._s_0.muf;
    bVar4 = IsAlive(piVar2);
    if (bVar4) {
      BuildObject("avtank",2,*piVar2);
      (this->field16_0x40)._s_0.aw2amade = true;
    }
  }
  fVar7 = Get_Time();
  if (((this->field17_0x84)._s_0.aw2bt < fVar7) && ((this->field16_0x40)._s_0.aw2bmade == false)) {
    piVar2 = &(this->field18_0xf4)._s_0.muf;
    bVar4 = IsAlive(piVar2);
    if (bVar4) {
      BuildObject("avfigh",2,*piVar2);
      (this->field16_0x40)._s_0.aw2bmade = true;
    }
  }
  fVar7 = Get_Time();
  if (((this->field17_0x84)._s_0.aw2ct < fVar7) && ((this->field16_0x40)._s_0.aw2cmade == false)) {
    piVar2 = &(this->field18_0xf4)._s_0.muf;
    bVar4 = IsAlive(piVar2);
    if (bVar4) {
      BuildObject("avtank",2,*piVar2);
      (this->field16_0x40)._s_0.aw2cmade = true;
    }
  }
  fVar7 = Get_Time();
  if (((this->field17_0x84)._s_0.aw3at < fVar7) && ((this->field16_0x40)._s_0.aw3amade == false)) {
    piVar2 = &(this->field18_0xf4)._s_0.muf;
    bVar4 = IsAlive(piVar2);
    if ((bVar4) && (bVar4 = IsAlive(&(this->field18_0xf4)._s_0.silo), bVar4)) {
      BuildObject("avtank",2,*piVar2);
      (this->field16_0x40)._s_0.aw3amade = true;
    }
  }
  fVar7 = Get_Time();
  if (((this->field17_0x84)._s_0.aw3bt < fVar7) && ((this->field16_0x40)._s_0.aw3bmade == false)) {
    piVar2 = &(this->field18_0xf4)._s_0.muf;
    bVar4 = IsAlive(piVar2);
    if ((bVar4) && (bVar4 = IsAlive(&(this->field18_0xf4)._s_0.silo), bVar4)) {
      BuildObject("avtank",2,*piVar2);
      (this->field16_0x40)._s_0.aw3bmade = true;
    }
  }
  fVar7 = Get_Time();
  if (((this->field17_0x84)._s_0.aw3ct < fVar7) && ((this->field16_0x40)._s_0.aw3cmade == false)) {
    piVar2 = &(this->field18_0xf4)._s_0.muf;
    bVar4 = IsAlive(piVar2);
    if ((bVar4) && (bVar4 = IsAlive(&(this->field18_0xf4)._s_0.silo), bVar4)) {
      BuildObject("avfigh",2,*piVar2);
      (this->field16_0x40)._s_0.aw3cmade = true;
    }
  }
  fVar7 = Get_Time();
  if (((this->field17_0x84)._s_0.du1at < fVar7) && ((this->field16_0x40)._s_0.du1amade == false)) {
    BuildObject("avturr",2,(this->field18_0xf4)._s_0.muf);
    (this->field16_0x40)._s_0.du1amade = true;
  }
  fVar7 = Get_Time();
  if (((this->field17_0x84)._s_0.du1bt < fVar7) && ((this->field16_0x40)._s_0.du1bmade == false)) {
    BuildObject("avturr",2,(this->field18_0xf4)._s_0.muf);
    (this->field16_0x40)._s_0.du1bmade = true;
  }
  bVar4 = IsAlive(pMVar1->h_array);
  if ((!bVar4) && ((this->field16_0x40)._s_0.coloradodestroyed == false)) {
    (this->field16_0x40)._s_0.coloradodestroyed = true;
    fVar7 = Get_Time();
    (this->field17_0x84)._s_0.wave1 = fVar7 + 180.0;
  }
  bVar4 = IsAlive(&(this->field18_0xf4)._s_0.muf);
  if ((!bVar4) && ((this->field16_0x40)._s_0.mufdestroyed == false)) {
    AudioMessage("misns108.wav");
    (this->field16_0x40)._s_0.mufdestroyed = true;
    (this->field16_0x40)._s_0.possible1 = true;
  }
  bVar4 = IsAlive(&(this->field18_0xf4)._s_0.silo);
  if ((!bVar4) && ((this->field16_0x40)._s_0.silodestroyed == false)) {
    (this->field16_0x40)._s_0.possible2 = true;
    AudioMessage("misns107.wav");
    (this->field16_0x40)._s_0.silodestroyed = true;
  }
  if (((this->field16_0x40)._s_0.possible1 == true) && ((this->field16_0x40)._s_0.possible2 == true)
     ) {
    (this->field16_0x40)._s_0.newobjective = true;
  }
  if (((((this->field16_0x40)._s_0.mufdestroyed == true) &&
       ((this->field16_0x40)._s_0.silodestroyed == true)) &&
      ((this->field16_0x40)._s_0.coloradodestroyed == true)) &&
     ((this->field16_0x40)._s_0.missionwon == false)) {
    (this->field16_0x40)._s_0.newobjective = true;
    (this->field16_0x40)._s_0.missionwon = true;
  }
  if (((this->field16_0x40)._s_0.missionwon == true) && ((this->field16_0x40)._s_0.finish == false))
  {
    iVar5 = AudioMessage("misns110.wav");
    (this->field19_0x1ac)._s_0.aud1 = iVar5;
    (this->field16_0x40)._s_0.finish = true;
  }
  if (((this->field16_0x40)._s_0.finish == true) &&
     (bVar4 = IsAudioMessageDone((this->field19_0x1ac)._s_0.aud1), bVar4)) {
    pcVar8 = "misns1w1.des";
    fVar7 = Get_Time();
    SucceedMission(fVar7,pcVar8);
  }
  if (((this->field16_0x40)._s_0.enterwarning == false) &&
     (fVar7 = GetDistance((pMVar1->_s_0).colorado,(this->field18_0xf4)._s_0.walkcam1), fVar7 < 70.0)
     ) {
    if ((this->field19_0x1ac)._s_0.path == 0) {
      AudioMessage("misns117.wav");
      (this->field16_0x40)._s_0.enterwarning = true;
    }
    if ((this->field19_0x1ac)._s_0.path == 1) {
      AudioMessage("misns116.wav");
      (this->field16_0x40)._s_0.enterwarning = true;
    }
    if ((this->field19_0x1ac)._s_0.path == 2) {
      AudioMessage("misns115.wav");
      (this->field16_0x40)._s_0.enterwarning = true;
    }
  }
  fVar7 = GetDistance((pMVar1->_s_0).colorado,"halfwayupper",0);
  if ((fVar7 < 100.0) && ((this->field16_0x40)._s_0.halfwaywarn == false)) {
    (this->field16_0x40)._s_0.halfwaywarn = true;
    AudioMessage("misns102.wav");
  }
  fVar7 = GetDistance((pMVar1->_s_0).colorado,"halfwaymid",0);
  if ((fVar7 < 100.0) && ((this->field16_0x40)._s_0.halfwaywarn == false)) {
    (this->field16_0x40)._s_0.halfwaywarn = true;
    AudioMessage("misns103.wav");
  }
  fVar7 = GetDistance((pMVar1->_s_0).colorado,"halfwaylower",0);
  if ((fVar7 < 100.0) && ((this->field16_0x40)._s_0.halfwaywarn == false)) {
    (this->field16_0x40)._s_0.halfwaywarn = true;
    AudioMessage("misns104.wav");
  }
  if ((((this->field16_0x40)._s_0.blockaderun == true) &&
      (fVar7 = GetDistance((pMVar1->_s_0).colorado,"safepoint",0), fVar7 < 60.0)) &&
     ((this->field16_0x40)._s_0.coloradoreachedsafepoint == false)) {
    iVar5 = AudioMessage("misns109.wav");
    (this->field19_0x1ac)._s_0.aud20 = iVar5;
    iVar5 = AudioMessage("misns111.wav");
    (this->field19_0x1ac)._s_0.aud21 = iVar5;
    (this->field16_0x40)._s_0.coloradoreachedsafepoint = true;
    (this->field16_0x40)._s_0.newobjective = true;
    CameraReady();
    CameraObject((this->field18_0xf4)._s_0.geyser2,0x4b0,500,0x4b0,(pMVar1->_s_0).colorado);
  }
  if ((((this->field16_0x40)._s_0.coloradoreachedsafepoint == true) &&
      (bVar4 = IsAudioMessageDone((this->field19_0x1ac)._s_0.aud20), bVar4)) &&
     (bVar4 = IsAudioMessageDone((this->field19_0x1ac)._s_0.aud21), bVar4)) {
    pcVar8 = "misns1l1.des";
    fVar7 = Get_Time();
    FailMission(fVar7,pcVar8);
  }
  bVar4 = IsAlive(&(this->field18_0xf4)._s_0.svrec);
  if ((!bVar4) && ((this->field16_0x40)._s_0.missionfail == false)) {
    iVar5 = AudioMessage("misns112.wav");
    (this->field19_0x1ac)._s_0.aud22 = iVar5;
    iVar5 = AudioMessage("misns113.wav");
    (this->field19_0x1ac)._s_0.aud23 = iVar5;
    (this->field16_0x40)._s_0.missionfail = true;
    (this->field16_0x40)._s_0.newobjective = true;
  }
  if ((((this->field16_0x40)._s_0.missionfail == true) &&
      (bVar4 = IsAudioMessageDone((this->field19_0x1ac)._s_0.aud22), bVar4)) &&
     (bVar4 = IsAudioMessageDone((this->field19_0x1ac)._s_0.aud23), bVar4)) {
    pcVar8 = "misns1l2.des";
    fVar7 = Get_Time();
    FailMission(fVar7,pcVar8);
  }
  fVar7 = Get_Time();
  pfVar3 = &(this->field17_0x84)._s_0.wave1;
  if ((*pfVar3 < fVar7) && ((this->field16_0x40)._s_0.cavalry == false)) {
    *pfVar3 = 1e+11;
    (this->field16_0x40)._s_0.cavalry = true;
    iVar5 = BuildObject("avfigh",2,"cavspawn",0);
    (this->field18_0xf4)._s_0.cav1 = iVar5;
    iVar5 = BuildObject("avtank",2,"cavspawn",0);
    (this->field18_0xf4)._s_0.cav2 = iVar5;
    iVar5 = BuildObject("avfigh",2,"cavspawn",0);
    (this->field18_0xf4)._s_0.cav3 = iVar5;
    AudioMessage("misns122.wav");
  }
  if (((this->field16_0x40)._s_0.cavalry != true) || ((this->field16_0x40)._s_0.cavsent != false))
  goto LAB_0044013a;
  iVar5 = (this->field19_0x1ac)._s_0.cav;
  if (iVar5 == 0) {
LAB_00440105:
    Goto((this->field18_0xf4)._s_0.cav1,"cavpath1",1);
    Goto((this->field18_0xf4)._s_0.cav2,"cavpath1",1);
    Goto((this->field18_0xf4)._s_0.cav3,"cavpath1",1);
    (this->field16_0x40)._s_0.cavpath1 = true;
  }
  else if (iVar5 == 1) {
LAB_004400d4:
    Goto((this->field18_0xf4)._s_0.cav1,"cavpath2",1);
    Goto((this->field18_0xf4)._s_0.cav2,"cavpath2",1);
    Goto((this->field18_0xf4)._s_0.cav3,"cavpath2",1);
    (this->field16_0x40)._s_0.cavpath2 = true;
  }
  else {
    if (iVar5 == 2) goto LAB_00440105;
    if (iVar5 == 3) goto LAB_004400d4;
  }
  (this->field16_0x40)._s_0.cavsent = true;
LAB_0044013a:
  if (((this->field16_0x40)._s_0.cavpath1 == true) &&
     ((((fVar7 = GetDistance((this->field18_0xf4)._s_0.cav1,(this->field18_0xf4)._s_0.walkcam1),
        fVar7 < 200.0 ||
        (fVar7 = GetDistance((this->field18_0xf4)._s_0.cav2,(this->field18_0xf4)._s_0.walkcam1),
        fVar7 < 200.0)) ||
       (fVar7 = GetDistance((this->field18_0xf4)._s_0.cav3,(this->field18_0xf4)._s_0.walkcam1),
       fVar7 < 200.0)) && ((this->field16_0x40)._s_0.cav1pathwarn1 == false)))) {
    AudioMessage("misns118.wav");
    (this->field16_0x40)._s_0.cav1pathwarn1 = true;
  }
  if (((this->field16_0x40)._s_0.cavpath2 == true) &&
     ((((fVar7 = GetDistance((this->field18_0xf4)._s_0.cav1,(this->field18_0xf4)._s_0.walkcam2),
        fVar7 < 50.0 ||
        (fVar7 = GetDistance((this->field18_0xf4)._s_0.cav2,(this->field18_0xf4)._s_0.walkcam2),
        fVar7 < 50.0)) ||
       (fVar7 = GetDistance((this->field18_0xf4)._s_0.cav3,(this->field18_0xf4)._s_0.walkcam2),
       fVar7 < 50.0)) && ((this->field16_0x40)._s_0.cav2pathwarn1 == false)))) {
    AudioMessage("misns119.wav");
    (this->field16_0x40)._s_0.cav2pathwarn1 = true;
  }
  return;
}
