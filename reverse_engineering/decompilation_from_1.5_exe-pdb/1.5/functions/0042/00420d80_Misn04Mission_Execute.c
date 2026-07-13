/*
 * Entry: 00420d80
 * Name: Misn04Mission::Execute
 * Namespace: Misn04Mission
 * Signature: void Execute(Misn04Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn04Mission::Execute(Misn04Mission *this)

{
  int *piVar1;
  Misn04Mission_u_260 *pMVar2;
  bool bVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int extraout_EAX_03;
  int extraout_EAX_04;
  int extraout_EAX_05;
  int extraout_EAX_06;
  int extraout_EAX_07;
  int extraout_EAX_08;
  int extraout_EAX_09;
  int extraout_EAX_10;
  int extraout_EAX_11;
  int extraout_EAX_12;
  int extraout_EAX_13;
  int extraout_EAX_14;
  int extraout_EAX_15;
  int extraout_EAX_16;
  float fVar7;
  char *pcVar8;
  
  iVar4 = GetPlayerHandle();
  bVar3 = (this->field16_0x40)._s_0.missionstart;
  (this->field18_0x104)._s_0.player = iVar4;
  if (bVar3 == false) {
    fVar7 = Get_Time();
    (this->field17_0x88)._s_0.wave1 = fVar7 + 30.0;
    fVar7 = Get_Time();
    (this->field17_0x88)._s_0.fetch = fVar7 + 240.0;
    AudioMessage("misn0401.wav");
    iVar4 = GetHandle("apcamr352_camerapod");
    (this->field18_0x104)._s_0.cam1 = iVar4;
    iVar4 = GetHandle("apcamr350_camerapod");
    (this->field18_0x104)._s_0.cam2 = iVar4;
    iVar4 = GetHandle("apcamr351_camerapod");
    (this->field18_0x104)._s_0.cam3 = iVar4;
    iVar4 = GetHandle("apcamr-1_camerapod");
    (this->field18_0x104)._s_0.basecam = iVar4;
    iVar4 = GetHandle("svrecy-1_recycler");
    (this->field18_0x104)._s_0.svrec = iVar4;
    iVar4 = GetHandle("avrecy-1_recycler");
    (this->field18_0x104)._s_0.avrec = iVar4;
    iVar4 = BuildObject("obdata",0,"relicstart1",0);
    (this->field18_0x104)._s_0.relic = iVar4;
    iVar4 = GetHandle("svfigh-1_wingman");
    (this->field18_0x104)._s_0.pu1 = iVar4;
    iVar4 = GetHandle("svfigh282_wingman");
    (this->field18_0x104)._s_0.pu3 = iVar4;
    iVar4 = GetHandle("svfigh279_wingman");
    (this->field18_0x104)._s_0.pu6 = iVar4;
    iVar4 = GetHandle("svfigh278_wingman");
    (this->field18_0x104)._s_0.pu8 = iVar4;
    SetObjectiveName((this->field18_0x104)._s_0.cam1,"SW Geyser");
    SetObjectiveName((this->field18_0x104)._s_0.cam2,"NW Geyser");
    SetObjectiveName((this->field18_0x104)._s_0.cam3,"NE Geyser");
    SetObjectiveName((this->field18_0x104)._s_0.basecam,"CCA Base");
    Patrol((this->field18_0x104)._s_0.pu1,"innerpatrol",1);
    Patrol((this->field18_0x104)._s_0.pu3,"innerpatrol",1);
    Patrol((this->field18_0x104)._s_0.pu6,"outerpatrol",1);
    Patrol((this->field18_0x104)._s_0.pu8,"scouting",1);
    InfoDisplay::AddObjective(&infoDisplay,"misn0401.otf",DisplayInterface::colorWhite,8.0);
    InfoDisplay::AddObjective(&infoDisplay,"misn0400.otf",DisplayInterface::colorWhite,8.0);
    (this->field16_0x40)._s_0.missionstart = true;
    (this->field16_0x40)._s_0.cheater = false;
    uVar5 = rand();
    uVar5 = uVar5 & 0x80000003;
    if ((int)uVar5 < 0) {
      uVar5 = (uVar5 - 1 | 0xfffffffc) + 1;
    }
    (this->field19_0x20c)._s_0.relicstartpos = uVar5;
    fVar7 = Get_Time();
    (this->field17_0x88)._s_0.tur1 = fVar7 + 30.0;
    fVar7 = Get_Time();
    (this->field17_0x88)._s_0.tur2 = fVar7 + 45.0;
    fVar7 = Get_Time();
    (this->field17_0x88)._s_0.tur3 = fVar7 + 60.0;
    fVar7 = Get_Time();
    (this->field17_0x88)._s_0.tur4 = fVar7 + 75.0;
    fVar7 = Get_Time();
    (this->field17_0x88)._s_0.investigate = fVar7 + 3.0;
  }
  iVar4 = GetPlayerHandle();
  piVar1 = &(this->field18_0x104)._s_0.cam1;
  (this->field18_0x104)._s_0.player = iVar4;
  bVar3 = IsAlive(piVar1);
  if (bVar3) {
    AddHealth(*piVar1,100.0);
  }
  piVar1 = &(this->field18_0x104)._s_0.cam2;
  bVar3 = IsAlive(piVar1);
  if (bVar3) {
    AddHealth(*piVar1,100.0);
  }
  piVar1 = &(this->field18_0x104)._s_0.cam3;
  bVar3 = IsAlive(piVar1);
  if (bVar3) {
    AddHealth(*piVar1,100.0);
  }
  if ((this->field16_0x40)._s_0.relicmoved == false) {
    iVar4 = (this->field19_0x20c)._s_0.relicstartpos;
    if (iVar4 == 0) {
      pcVar8 = "relicstart1";
LAB_00421077:
      SetPosition((this->field18_0x104)._s_0.relic,pcVar8,0);
    }
    else {
      if (iVar4 == 1) {
        pcVar8 = "relicstart2";
        goto LAB_00421077;
      }
      if (iVar4 == 2) {
        pcVar8 = "relicstart3";
        goto LAB_00421077;
      }
      if (iVar4 == 3) {
        pcVar8 = "relicstart4";
        goto LAB_00421077;
      }
    }
    (this->field16_0x40)._s_0.relicmoved = true;
  }
  if (((this->field16_0x40)._s_0.reconsent == false) && ((this->field16_0x40)._s_0.cheater == false)
     ) {
    fVar7 = GetDistance((this->field18_0x104)._s_0.player,(this->field18_0x104)._s_0.relic);
    if (fVar7 < 600.0) {
      iVar4 = BuildObject("svfigh",2,(this->field18_0x104)._s_0.relic);
      (this->field18_0x104)._s_0.cheat1 = iVar4;
      iVar4 = BuildObject("svfigh",2,(this->field18_0x104)._s_0.relic);
      (this->field18_0x104)._s_0.cheat2 = iVar4;
      iVar4 = BuildObject("svfigh",2,(this->field18_0x104)._s_0.relic);
      (this->field18_0x104)._s_0.cheat3 = iVar4;
      iVar4 = BuildObject("svfigh",2,(this->field18_0x104)._s_0.relic);
      (this->field18_0x104)._s_0.cheat4 = iVar4;
      iVar4 = BuildObject("svfigh",2,(this->field18_0x104)._s_0.relic);
      (this->field18_0x104)._s_0.cheat5 = iVar4;
      iVar6 = BuildObject("svfigh",2,(this->field18_0x104)._s_0.relic);
      iVar4 = (this->field19_0x20c)._s_0.relicstartpos;
      (this->field18_0x104)._s_0.cheat6 = iVar6;
      if (iVar4 == 0) {
        Patrol((this->field18_0x104)._s_0.cheat1,"relicpatrolpath1a",1);
        Patrol((this->field18_0x104)._s_0.cheat2,"relicpatrolpath1a",1);
        Patrol((this->field18_0x104)._s_0.cheat3,"relicpatrolpath1a",1);
        Patrol((this->field18_0x104)._s_0.cheat4,"relicpatrolpath1b",1);
        Patrol((this->field18_0x104)._s_0.cheat5,"relicpatrolpath1b",1);
        Patrol((this->field18_0x104)._s_0.cheat6,"relicpatrolpath1b",1);
        SetIndependence((this->field18_0x104)._s_0.cheat1,1);
        SetIndependence((this->field18_0x104)._s_0.cheat2,1);
        SetIndependence((this->field18_0x104)._s_0.cheat3,1);
        SetIndependence((this->field18_0x104)._s_0.cheat4,1);
        SetIndependence((this->field18_0x104)._s_0.cheat5,1);
        SetIndependence((this->field18_0x104)._s_0.cheat6,1);
      }
      if ((this->field19_0x20c)._s_0.relicstartpos == 1) {
        Patrol((this->field18_0x104)._s_0.cheat1,"relicpatrolpath2a",1);
        Patrol((this->field18_0x104)._s_0.cheat2,"relicpatrolpath2a",1);
        Patrol((this->field18_0x104)._s_0.cheat3,"relicpatrolpath2a",1);
        Patrol((this->field18_0x104)._s_0.cheat4,"relicpatrolpath2b",1);
        Patrol((this->field18_0x104)._s_0.cheat5,"relicpatrolpath2b",1);
        Patrol((this->field18_0x104)._s_0.cheat6,"relicpatrolpath2b",1);
        SetIndependence((this->field18_0x104)._s_0.cheat1,1);
        SetIndependence((this->field18_0x104)._s_0.cheat2,1);
        SetIndependence((this->field18_0x104)._s_0.cheat3,1);
        SetIndependence((this->field18_0x104)._s_0.cheat4,1);
        SetIndependence((this->field18_0x104)._s_0.cheat5,1);
        SetIndependence((this->field18_0x104)._s_0.cheat6,1);
      }
      if ((this->field19_0x20c)._s_0.relicstartpos == 2) {
        Patrol((this->field18_0x104)._s_0.cheat1,"relicpatrolpath3a",1);
        Patrol((this->field18_0x104)._s_0.cheat2,"relicpatrolpath3a",1);
        Patrol((this->field18_0x104)._s_0.cheat3,"relicpatrolpath3a",1);
        Patrol((this->field18_0x104)._s_0.cheat4,"relicpatrolpath3b",1);
        Patrol((this->field18_0x104)._s_0.cheat5,"relicpatrolpath3b",1);
        Patrol((this->field18_0x104)._s_0.cheat6,"relicpatrolpath3b",1);
        SetIndependence((this->field18_0x104)._s_0.cheat1,1);
        SetIndependence((this->field18_0x104)._s_0.cheat2,1);
        SetIndependence((this->field18_0x104)._s_0.cheat3,1);
        SetIndependence((this->field18_0x104)._s_0.cheat4,1);
        SetIndependence((this->field18_0x104)._s_0.cheat5,1);
        SetIndependence((this->field18_0x104)._s_0.cheat6,1);
      }
      if ((this->field19_0x20c)._s_0.relicstartpos == 3) {
        Patrol((this->field18_0x104)._s_0.cheat1,"relicpatrolpath4a",1);
        Patrol((this->field18_0x104)._s_0.cheat2,"relicpatrolpath4a",1);
        Patrol((this->field18_0x104)._s_0.cheat3,"relicpatrolpath4a",1);
        Patrol((this->field18_0x104)._s_0.cheat4,"relicpatrolpath4b",1);
        Patrol((this->field18_0x104)._s_0.cheat5,"relicpatrolpath4b",1);
        Patrol((this->field18_0x104)._s_0.cheat6,"relicpatrolpath4b",1);
        SetIndependence((this->field18_0x104)._s_0.cheat1,1);
        SetIndependence((this->field18_0x104)._s_0.cheat2,1);
        SetIndependence((this->field18_0x104)._s_0.cheat3,1);
        SetIndependence((this->field18_0x104)._s_0.cheat4,1);
        SetIndependence((this->field18_0x104)._s_0.cheat5,1);
        SetIndependence((this->field18_0x104)._s_0.cheat6,1);
      }
      (this->field16_0x40)._s_0.surveysent = true;
      (this->field16_0x40)._s_0.cheater = true;
      fVar7 = Get_Time();
      (this->field17_0x88)._s_0.reconcca = fVar7;
    }
  }
  fVar7 = Get_Time();
  if (((this->field17_0x88)._s_0.fetch < fVar7) && ((this->field16_0x40)._s_0.surveysent == false))
  {
    piVar1 = &(this->field18_0x104)._s_0.relic;
    iVar4 = BuildObject("svfigh",2,*piVar1);
    (this->field18_0x104)._s_0.surv1 = iVar4;
    iVar6 = BuildObject("svfigh",2,*piVar1);
    iVar4 = (this->field19_0x20c)._s_0.relicstartpos;
    (this->field18_0x104)._s_0.surv2 = iVar6;
    if (iVar4 == 0) {
      Patrol((this->field18_0x104)._s_0.surv1,"relicpatrolpath1a",1);
      Patrol((this->field18_0x104)._s_0.surv2,"relicpatrolpath1b",1);
      SetIndependence((this->field18_0x104)._s_0.surv1,1);
      SetIndependence((this->field18_0x104)._s_0.surv2,1);
    }
    if ((this->field19_0x20c)._s_0.relicstartpos == 1) {
      Patrol((this->field18_0x104)._s_0.surv1,"relicpatrolpath2a",1);
      Patrol((this->field18_0x104)._s_0.surv2,"relicpatrolpath2b",1);
      SetIndependence((this->field18_0x104)._s_0.surv1,1);
      SetIndependence((this->field18_0x104)._s_0.surv2,1);
    }
    if ((this->field19_0x20c)._s_0.relicstartpos == 2) {
      Patrol((this->field18_0x104)._s_0.surv1,"relicpatrolpath3a",1);
      Patrol((this->field18_0x104)._s_0.surv2,"relicpatrolpath3b",1);
      SetIndependence((this->field18_0x104)._s_0.surv1,1);
      SetIndependence((this->field18_0x104)._s_0.surv2,1);
    }
    if ((this->field19_0x20c)._s_0.relicstartpos == 3) {
      Patrol((this->field18_0x104)._s_0.surv1,"relicpatrolpath4a",1);
      Patrol((this->field18_0x104)._s_0.surv2,"relicpatrolpath4b",1);
      SetIndependence((this->field18_0x104)._s_0.surv1,1);
      SetIndependence((this->field18_0x104)._s_0.surv2,1);
    }
    (this->field16_0x40)._s_0.surveysent = true;
    fVar7 = Get_Time();
    (this->field17_0x88)._s_0.reconcca = fVar7 + 60.0;
  }
  if ((this->field16_0x40)._s_0.tur1sent == false) {
    fVar7 = Get_Time();
    if ((this->field17_0x88)._s_0.tur1 < fVar7) {
      bVar3 = IsAlive((this->field18_0x104).h_array);
      if (bVar3) {
        iVar4 = BuildObject("svturr",2,(this->field18_0x104)._s_0.svrec);
        (this->field18_0x104)._s_0.turret1 = iVar4;
        Goto(iVar4,"turret1",1);
        (this->field16_0x40)._s_0.tur1sent = true;
      }
    }
  }
  if ((this->field16_0x40)._s_0.tur2sent == false) {
    fVar7 = Get_Time();
    if ((this->field17_0x88)._s_0.tur2 < fVar7) {
      bVar3 = IsAlive((this->field18_0x104).h_array);
      if (bVar3) {
        iVar4 = BuildObject("svturr",2,(this->field18_0x104)._s_0.svrec);
        (this->field18_0x104)._s_0.turret2 = iVar4;
        Goto(iVar4,"turret2",1);
        (this->field16_0x40)._s_0.tur2sent = true;
      }
    }
  }
  if ((this->field16_0x40)._s_0.tur3sent == false) {
    fVar7 = Get_Time();
    if ((this->field17_0x88)._s_0.tur3 < fVar7) {
      bVar3 = IsAlive((this->field18_0x104).h_array);
      if (bVar3) {
        iVar4 = BuildObject("svturr",2,(this->field18_0x104)._s_0.svrec);
        (this->field18_0x104)._s_0.turret3 = iVar4;
        Goto(iVar4,"turret3",1);
        (this->field16_0x40)._s_0.tur3sent = true;
      }
    }
  }
  if ((this->field16_0x40)._s_0.tur4sent == false) {
    fVar7 = Get_Time();
    if ((this->field17_0x88)._s_0.tur4 < fVar7) {
      bVar3 = IsAlive((this->field18_0x104).h_array);
      if (bVar3) {
        iVar4 = BuildObject("svturr",2,(this->field18_0x104)._s_0.svrec);
        (this->field18_0x104)._s_0.turret4 = iVar4;
        Goto(iVar4,"turret4",1);
        (this->field16_0x40)._s_0.tur4sent = true;
      }
    }
  }
  fVar7 = Get_Time();
  if ((((this->field17_0x88)._s_0.reconcca < fVar7) &&
      ((this->field16_0x40)._s_0.reconsent == false)) &&
     ((this->field16_0x40)._s_0.surveysent == true)) {
    iVar6 = AudioMessage("misn0406.wav");
    iVar4 = (this->field19_0x20c)._s_0.relicstartpos;
    (this->field17_0x88)._s_0.aud4 = (float)iVar6;
    if (iVar4 == 0) {
      pcVar8 = "reliccam1";
LAB_00421758:
      iVar4 = BuildObject("apcamr",1,pcVar8,0);
      (this->field18_0x104)._s_0.reliccam = iVar4;
    }
    else {
      if (iVar4 == 1) {
        pcVar8 = "reliccam2";
        goto LAB_00421758;
      }
      if (iVar4 == 2) {
        pcVar8 = "reliccam3";
        goto LAB_00421758;
      }
      if (iVar4 == 3) {
        pcVar8 = "reliccam4";
        goto LAB_00421758;
      }
    }
    (this->field16_0x40)._s_0.reconsent = true;
    (this->field16_0x40)._s_0.obset = true;
    fVar7 = Get_Time();
    (this->field17_0x88)._s_0.notfound = fVar7 + 90.0;
  }
  if ((this->field16_0x40)._s_0.obset == true) {
    _ftol2_sse();
    bVar3 = IsAudioMessageDone(extraout_EAX);
    if (bVar3) {
      SetObjectiveName((this->field18_0x104)._s_0.reliccam,"Investigate CCA");
      (this->field16_0x40)._s_0.newobjective = true;
      (this->field16_0x40)._s_0.obset = false;
    }
  }
  if (((this->field16_0x40)._s_0.found == true) && ((this->field16_0x40)._s_0.halfway == false)) {
    bVar3 = HasCargo((this->field18_0x104)._s_0.tug);
    if (bVar3) {
      AudioMessage("misn0419.wav");
      iVar4 = (this->field18_0x104)._s_0.relic;
      (this->field16_0x40)._s_0.halfway = true;
      SetObjectiveOff(iVar4);
      piVar1 = &(this->field18_0x104)._s_0.tuge1;
      bVar3 = IsAlive(piVar1);
      if (bVar3) {
        Attack(*piVar1,(this->field18_0x104)._s_0.tug,1);
      }
      piVar1 = &(this->field18_0x104)._s_0.tuge2;
      bVar3 = IsAlive(piVar1);
      if (bVar3) {
        Attack(*piVar1,(this->field18_0x104)._s_0.tug,1);
      }
    }
  }
  if ((this->field16_0x40)._s_0.reconsent == true) {
    fVar7 = GetDistance((this->field18_0x104)._s_0.relic,(this->field18_0x104)._s_0.avrec);
    if ((fVar7 < 100.0) && ((this->field16_0x40)._s_0.relicsecure == false)) {
      iVar4 = AudioMessage("misn0420.wav");
      (this->field16_0x40)._s_0.relicsecure = true;
      (this->field16_0x40)._s_0.newobjective = true;
      (this->field17_0x88)._s_0.aud23 = (float)iVar4;
    }
  }
  fVar7 = Get_Time();
  if (((this->field17_0x88)._s_0.ccatug < fVar7) && ((this->field16_0x40)._s_0.ccatugsent == false))
  {
    pMVar2 = &this->field18_0x104;
    bVar3 = IsAlive(pMVar2->h_array);
    if (bVar3) {
      iVar4 = BuildObject("svhaul",2,(pMVar2->_s_0).svrec);
      (this->field18_0x104)._s_0.svtug = iVar4;
      iVar4 = BuildObject("svfigh",2,(pMVar2->_s_0).svrec);
      (this->field18_0x104)._s_0.tuge1 = iVar4;
      iVar4 = BuildObject("svfigh",2,(pMVar2->_s_0).svrec);
      (this->field18_0x104)._s_0.tuge2 = iVar4;
      Pickup((this->field18_0x104)._s_0.svtug,(this->field18_0x104)._s_0.relic,1);
      Follow((this->field18_0x104)._s_0.tuge1,(this->field18_0x104)._s_0.svtug,1);
      Follow((this->field18_0x104)._s_0.tuge2,(this->field18_0x104)._s_0.svtug,1);
      (this->field16_0x40)._s_0.ccatugsent = true;
    }
  }
  if (((this->field16_0x40)._s_0.ccatugsent == true) &&
     ((this->field16_0x40)._s_0.ccahasrelic == false)) {
    piVar1 = &(this->field18_0x104)._s_0.svtug;
    bVar3 = IsAlive(piVar1);
    if (bVar3) {
      bVar3 = HasCargo(*piVar1);
      if (bVar3) {
        bVar3 = HasCargo((this->field18_0x104)._s_0.tug);
        if (!bVar3) {
          iVar4 = *piVar1;
          (this->field16_0x40)._s_0.ccahasrelic = true;
          Goto(iVar4,"dropoff",1);
          AudioMessage("misn0427.wav");
          SetObjectiveOn(*piVar1);
          SetObjectiveName(*piVar1,"CCA Tug");
        }
      }
    }
  }
  if ((this->field16_0x40)._s_0.ccahasrelic == true) {
    fVar7 = GetDistance((this->field18_0x104)._s_0.svtug,(this->field18_0x104)._s_0.svrec);
    if ((fVar7 < 60.0) && ((this->field16_0x40)._s_0.missionfail2 == false)) {
      iVar4 = AudioMessage("misn0431.wav");
      (this->field17_0x88)._s_0.aud10 = (float)iVar4;
      iVar4 = AudioMessage("misn0432.wav");
      (this->field17_0x88)._s_0.aud11 = (float)iVar4;
      iVar4 = AudioMessage("misn0433.wav");
      (this->field17_0x88)._s_0.aud12 = (float)iVar4;
      iVar4 = AudioMessage("misn0434.wav");
      (this->field16_0x40)._s_0.missionfail2 = true;
      (this->field17_0x88)._s_0.aud13 = (float)iVar4;
      CameraReady();
    }
  }
  if (((this->field16_0x40)._s_0.missionfail2 == true) && ((this->field16_0x40)._s_0.done == false))
  {
    CameraPath("ccareliccam",3000,1000,(this->field18_0x104)._s_0.svtug);
    _ftol2_sse();
    bVar3 = IsAudioMessageDone(extraout_EAX_00);
    if (bVar3) {
      _ftol2_sse();
      bVar3 = IsAudioMessageDone(extraout_EAX_01);
      if (!bVar3) goto LAB_00421ab4;
      _ftol2_sse();
      bVar3 = IsAudioMessageDone(extraout_EAX_02);
      if (!bVar3) goto LAB_00421ab4;
      _ftol2_sse();
      bVar3 = IsAudioMessageDone(extraout_EAX_03);
      if (!bVar3) goto LAB_00421ab4;
    }
    else {
LAB_00421ab4:
      bVar3 = CameraCancelled();
      if (!bVar3) goto LAB_00421b1e;
    }
    CameraFinish();
    _ftol2_sse();
    StopAudioMessage(extraout_EAX_04);
    _ftol2_sse();
    StopAudioMessage(extraout_EAX_05);
    _ftol2_sse();
    StopAudioMessage(extraout_EAX_06);
    _ftol2_sse();
    StopAudioMessage(extraout_EAX_07);
    pcVar8 = "misn04l1.des";
    fVar7 = Get_Time();
    FailMission(fVar7,pcVar8);
    (this->field16_0x40)._s_0.done = true;
  }
LAB_00421b1e:
  if (((this->field16_0x40)._s_0.discoverrelic == false) &&
     ((this->field16_0x40)._s_0.reconsent == true)) {
    fVar7 = Get_Time();
    if ((fVar7 <= (this->field17_0x88)._s_0.notfound) ||
       ((this->field16_0x40)._s_0.ccahasrelic != false)) goto LAB_00421b6c;
    iVar4 = (this->field19_0x20c)._s_0.warn;
    if (iVar4 < 4) {
      AudioMessage("misn0429.wav");
      fVar7 = Get_Time();
      piVar1 = &(this->field19_0x20c)._s_0.warn;
      *piVar1 = *piVar1 + 1;
      (this->field17_0x88)._s_0.notfound = fVar7 + 85.0;
      goto LAB_00421b6c;
    }
  }
  else {
LAB_00421b6c:
    iVar4 = (this->field19_0x20c)._s_0.warn;
  }
  if (iVar4 == 4) {
    fVar7 = Get_Time();
    if (((this->field17_0x88)._s_0.notfound < fVar7) &&
       ((this->field16_0x40)._s_0.missionfail == false)) {
      iVar4 = AudioMessage("misn0694.wav");
      (this->field16_0x40)._s_0.missionfail = true;
      (this->field17_0x88)._s_0.aud14 = (float)iVar4;
    }
  }
  if (((this->field16_0x40)._s_0.missionfail == true) && ((this->field19_0x20c)._s_0.warn == 4)) {
    _ftol2_sse();
    bVar3 = IsAudioMessageDone(extraout_EAX_08);
    if (bVar3) {
      pcVar8 = "misn04l4.des";
      fVar7 = Get_Time();
      FailMission(fVar7,pcVar8);
      (this->field19_0x20c)._s_0.warn = 0;
    }
  }
  if ((this->field16_0x40)._s_0.discoverrelic == false) {
    fVar7 = Get_Time();
    if ((this->field17_0x88)._s_0.investigate < fVar7) {
      iVar4 = CountUnitsNearObject((this->field18_0x104)._s_0.relic,400.0,1,(char *)0x0);
      (this->field19_0x20c)._s_0.investigator = iVar4;
      bVar3 = IsAlive(&(this->field18_0x104)._s_0.reliccam);
      if (bVar3) {
        piVar1 = &(this->field19_0x20c)._s_0.investigator;
        *piVar1 = *piVar1 + -1;
      }
    }
    if (0 < (this->field19_0x20c)._s_0.investigator) {
      iVar4 = AudioMessage("misn0408.wav");
      (this->field17_0x88)._s_0.aud2 = (float)iVar4;
      iVar4 = AudioMessage("misn0409.wav");
      (this->field16_0x40)._s_0.relicseen = true;
      (this->field16_0x40)._s_0.newobjective = true;
      (this->field17_0x88)._s_0.aud3 = (float)iVar4;
      fVar7 = Get_Time();
      (this->field16_0x40)._s_0.discoverrelic = true;
      (this->field17_0x88)._s_0.ccatug = fVar7 + 200.0;
      CameraReady();
      fVar7 = Get_Time();
      (this->field17_0x88)._s_0.cintime1 = fVar7 + 23.0;
    }
  }
  if ((this->field16_0x40)._s_0.discoverrelic == true) {
    if ((this->field16_0x40)._s_0.cin1done == false) {
      _ftol2_sse();
      bVar3 = IsAudioMessageDone(extraout_EAX_09);
      if (bVar3) {
        _ftol2_sse();
        bVar3 = IsAudioMessageDone(extraout_EAX_10);
        if (!bVar3) goto LAB_00421ce5;
      }
      else {
LAB_00421ce5:
        bVar3 = CameraCancelled();
        if (!bVar3) goto LAB_00421d17;
      }
      CameraFinish();
      _ftol2_sse();
      StopAudioMessage(extraout_EAX_11);
      _ftol2_sse();
      StopAudioMessage(extraout_EAX_12);
      (this->field16_0x40)._s_0.cin1done = true;
    }
LAB_00421d17:
    if ((this->field16_0x40)._s_0.discoverrelic == true) {
      fVar7 = Get_Time();
      if ((fVar7 < (this->field17_0x88)._s_0.cintime1) &&
         ((this->field16_0x40)._s_0.cin1done == false)) {
        if ((this->field19_0x20c)._s_0.relicstartpos == 0) {
          CameraPath("reliccin1",500,400,(this->field18_0x104)._s_0.relic);
        }
        if ((this->field19_0x20c)._s_0.relicstartpos == 1) {
          CameraPath("reliccin2",500,400,(this->field18_0x104)._s_0.relic);
        }
        if ((this->field19_0x20c)._s_0.relicstartpos == 2) {
          CameraPath("reliccin3",500,400,(this->field18_0x104)._s_0.relic);
        }
        if ((this->field19_0x20c)._s_0.relicstartpos == 3) {
          CameraPath("reliccin4",500,400,(this->field18_0x104)._s_0.relic);
        }
      }
    }
  }
  if ((this->field16_0x40)._s_0.newobjective == true) {
    InfoDisplay::ClearObjectives(&infoDisplay);
    if ((this->field16_0x40)._s_0.basesecure == false) {
      InfoDisplay::AddObjective(&infoDisplay,"misn0401.otf",DisplayInterface::colorWhite,8.0);
    }
    if ((this->field16_0x40)._s_0.basesecure == true) {
      InfoDisplay::AddObjective(&infoDisplay,"misn0401.otf",DisplayInterface::colorGreen,8.0);
    }
    if (((this->field16_0x40)._s_0.relicsecure == false) &&
       ((this->field16_0x40)._s_0.relicseen == true)) {
      InfoDisplay::AddObjective(&infoDisplay,"misn0403.otf",DisplayInterface::colorWhite,8.0);
    }
    if ((this->field16_0x40)._s_0.relicsecure == true) {
      InfoDisplay::AddObjective(&infoDisplay,"misn0403.otf",DisplayInterface::colorGreen,8.0);
    }
    if (((this->field16_0x40)._s_0.reconsent == true) &&
       ((this->field16_0x40)._s_0.discoverrelic == false)) {
      InfoDisplay::AddObjective(&infoDisplay,"misn0405.otf",DisplayInterface::colorWhite,8.0);
    }
    if ((this->field16_0x40)._s_0.discoverrelic == true) {
      InfoDisplay::AddObjective(&infoDisplay,"misn0405.otf",DisplayInterface::colorGreen,8.0);
    }
    (this->field16_0x40)._s_0.newobjective = false;
  }
  if ((this->field19_0x20c)._s_0.wavenumber == 1) {
    IsAlive(&(this->field18_0x104)._s_0.w1u1);
    IsAlive(&(this->field18_0x104)._s_0.w1u2);
    if ((this->field19_0x20c)._s_0.wavenumber == 1) {
      fVar7 = Get_Time();
      if ((this->field17_0x88)._s_0.wave1 < fVar7) {
        iVar4 = BuildObject("svfigh",2,"wave1",0);
        (this->field18_0x104)._s_0.w1u1 = iVar4;
        iVar4 = BuildObject("svfigh",2,"wave1",0);
        piVar1 = &(this->field18_0x104)._s_0.avrec;
        (this->field18_0x104)._s_0.w1u2 = iVar4;
        Attack((this->field18_0x104)._s_0.w1u1,*piVar1,1);
        Attack((this->field18_0x104)._s_0.w1u2,*piVar1,1);
        SetIndependence((this->field18_0x104)._s_0.w1u1,1);
        SetIndependence((this->field18_0x104)._s_0.w1u2,1);
        (this->field19_0x20c)._s_0.wavenumber = 2;
        (this->field16_0x40)._s_0.wave1arrive = false;
      }
    }
  }
  if ((this->field19_0x20c)._s_0.wavenumber == 2) {
    IsAlive(&(this->field18_0x104)._s_0.w1u1);
    IsAlive(&(this->field18_0x104)._s_0.w1u2);
    if ((this->field19_0x20c)._s_0.wavenumber == 2) {
      bVar3 = IsAlive(&(this->field18_0x104)._s_0.w1u1);
      if (!bVar3) {
        bVar3 = IsAlive(&(this->field18_0x104)._s_0.w1u2);
        if ((!bVar3) && ((this->field16_0x40)._s_0.build2 == false)) {
          fVar7 = Get_Time();
          (this->field16_0x40)._s_0.build2 = true;
          (this->field16_0x40)._s_0.wave1dead = true;
          (this->field17_0x88)._s_0.wave2 = fVar7 + 60.0;
        }
      }
    }
  }
  fVar7 = Get_Time();
  if ((this->field17_0x88)._s_0.wave2 < fVar7) {
    bVar3 = IsAlive((this->field18_0x104).h_array);
    if (bVar3) {
      iVar4 = BuildObject("svtank",2,"spawn2new",0);
      (this->field18_0x104)._s_0.w2u1 = iVar4;
      iVar4 = BuildObject("svfigh",2,"spawn2new",0);
      piVar1 = &(this->field18_0x104)._s_0.avrec;
      (this->field18_0x104)._s_0.w2u2 = iVar4;
      Goto((this->field18_0x104)._s_0.w2u1,*piVar1,1);
      Goto((this->field18_0x104)._s_0.w2u2,*piVar1,1);
      SetIndependence((this->field18_0x104)._s_0.w2u1,1);
      SetIndependence((this->field18_0x104)._s_0.w2u2,1);
      (this->field17_0x88)._s_0.wave2 = 99999.0;
      (this->field19_0x20c)._s_0.wavenumber = 3;
      (this->field16_0x40)._s_0.wave2arrive = false;
    }
  }
  if ((this->field19_0x20c)._s_0.wavenumber == 3) {
    IsAlive(&(this->field18_0x104)._s_0.w2u1);
    IsAlive(&(this->field18_0x104)._s_0.w2u2);
    if ((this->field19_0x20c)._s_0.wavenumber == 3) {
      bVar3 = IsAlive(&(this->field18_0x104)._s_0.w2u1);
      if (!bVar3) {
        bVar3 = IsAlive(&(this->field18_0x104)._s_0.w2u2);
        if ((!bVar3) && ((this->field16_0x40)._s_0.build3 == false)) {
          fVar7 = Get_Time();
          (this->field16_0x40)._s_0.build3 = true;
          (this->field16_0x40)._s_0.wave2dead = true;
          (this->field17_0x88)._s_0.wave3 = fVar7 + 74.0;
        }
      }
    }
  }
  fVar7 = Get_Time();
  if ((this->field17_0x88)._s_0.wave3 < fVar7) {
    pMVar2 = &this->field18_0x104;
    bVar3 = IsAlive(pMVar2->h_array);
    if (bVar3) {
      iVar4 = BuildObject("svfigh",2,(pMVar2->_s_0).svrec);
      (this->field18_0x104)._s_0.w3u1 = iVar4;
      iVar4 = BuildObject("svfigh",2,(pMVar2->_s_0).svrec);
      (this->field18_0x104)._s_0.w3u2 = iVar4;
      iVar4 = BuildObject("svfigh",2,(pMVar2->_s_0).svrec);
      (this->field18_0x104)._s_0.w3u3 = iVar4;
      Goto((this->field18_0x104)._s_0.w3u1,(this->field18_0x104)._s_0.avrec,1);
      Goto((this->field18_0x104)._s_0.w3u2,(this->field18_0x104)._s_0.avrec,1);
      Goto((this->field18_0x104)._s_0.w3u3,(this->field18_0x104)._s_0.avrec,1);
      SetIndependence((this->field18_0x104)._s_0.w3u1,1);
      SetIndependence((this->field18_0x104)._s_0.w3u2,1);
      SetIndependence((this->field18_0x104)._s_0.w3u3,1);
      (this->field17_0x88)._s_0.wave3 = 99999.0;
      (this->field19_0x20c)._s_0.wavenumber = 4;
      (this->field16_0x40)._s_0.wave3arrive = false;
    }
  }
  if ((this->field19_0x20c)._s_0.wavenumber == 4) {
    IsAlive(&(this->field18_0x104)._s_0.w3u1);
    IsAlive(&(this->field18_0x104)._s_0.w3u2);
    IsAlive(&(this->field18_0x104)._s_0.w3u3);
    if ((this->field19_0x20c)._s_0.wavenumber == 4) {
      bVar3 = IsAlive(&(this->field18_0x104)._s_0.w3u1);
      if (!bVar3) {
        bVar3 = IsAlive(&(this->field18_0x104)._s_0.w3u2);
        if (!bVar3) {
          bVar3 = IsAlive(&(this->field18_0x104)._s_0.w3u3);
          if ((!bVar3) && ((this->field16_0x40)._s_0.build4 == false)) {
            fVar7 = Get_Time();
            (this->field16_0x40)._s_0.build4 = true;
            (this->field16_0x40)._s_0.wave3dead = true;
            (this->field17_0x88)._s_0.wave4 = fVar7 + 60.0;
          }
        }
      }
    }
  }
  fVar7 = Get_Time();
  if ((this->field17_0x88)._s_0.wave4 < fVar7) {
    bVar3 = IsAlive((this->field18_0x104).h_array);
    if (bVar3) {
      iVar4 = BuildObject("svtank",2,"spawnotherside",0);
      (this->field18_0x104)._s_0.w4u1 = iVar4;
      iVar4 = BuildObject("svfigh",2,"spawnotherside",0);
      (this->field18_0x104)._s_0.w4u2 = iVar4;
      iVar4 = BuildObject("svfigh",2,"spawnotherside",0);
      (this->field18_0x104)._s_0.w4u3 = iVar4;
      Goto((this->field18_0x104)._s_0.w4u1,(this->field18_0x104)._s_0.avrec,1);
      Goto((this->field18_0x104)._s_0.w4u2,(this->field18_0x104)._s_0.avrec,1);
      Goto((this->field18_0x104)._s_0.w4u3,(this->field18_0x104)._s_0.avrec,1);
      SetIndependence((this->field18_0x104)._s_0.w4u1,1);
      SetIndependence((this->field18_0x104)._s_0.w4u2,1);
      SetIndependence((this->field18_0x104)._s_0.w4u3,1);
      (this->field19_0x20c)._s_0.wavenumber = 5;
      (this->field16_0x40)._s_0.wave4arrive = false;
      (this->field17_0x88)._s_0.wave4 = 99999.0;
    }
  }
  if ((this->field19_0x20c)._s_0.wavenumber == 5) {
    IsAlive(&(this->field18_0x104)._s_0.w4u1);
    IsAlive(&(this->field18_0x104)._s_0.w4u2);
    IsAlive(&(this->field18_0x104)._s_0.w4u3);
    if ((this->field19_0x20c)._s_0.wavenumber == 5) {
      bVar3 = IsAlive(&(this->field18_0x104)._s_0.w4u1);
      if (!bVar3) {
        bVar3 = IsAlive(&(this->field18_0x104)._s_0.w4u2);
        if (!bVar3) {
          bVar3 = IsAlive(&(this->field18_0x104)._s_0.w4u3);
          if ((!bVar3) && ((this->field16_0x40)._s_0.build5 == false)) {
            fVar7 = Get_Time();
            (this->field17_0x88)._s_0.wave5 = fVar7 + 30.0;
            (this->field16_0x40)._s_0.build5 = true;
            (this->field16_0x40)._s_0.wave4dead = true;
          }
        }
      }
    }
  }
  fVar7 = Get_Time();
  if ((this->field17_0x88)._s_0.wave5 < fVar7) {
    pMVar2 = &this->field18_0x104;
    bVar3 = IsAlive(pMVar2->h_array);
    if (bVar3) {
      iVar4 = BuildObject("svtank",2,(pMVar2->_s_0).svrec);
      (this->field18_0x104)._s_0.w5u1 = iVar4;
      iVar4 = BuildObject("svfigh",2,(pMVar2->_s_0).svrec);
      (this->field18_0x104)._s_0.w5u2 = iVar4;
      iVar4 = BuildObject("svfigh",2,(pMVar2->_s_0).svrec);
      (this->field18_0x104)._s_0.w5u3 = iVar4;
      iVar4 = BuildObject("svfigh",2,(pMVar2->_s_0).svrec);
      (this->field18_0x104)._s_0.w5u4 = iVar4;
      Goto((this->field18_0x104)._s_0.w5u1,(this->field18_0x104)._s_0.avrec,1);
      Goto((this->field18_0x104)._s_0.w5u2,(this->field18_0x104)._s_0.avrec,1);
      Goto((this->field18_0x104)._s_0.w5u3,(this->field18_0x104)._s_0.avrec,1);
      Goto((this->field18_0x104)._s_0.w5u4,(this->field18_0x104)._s_0.avrec,1);
      SetIndependence((this->field18_0x104)._s_0.w5u1,1);
      SetIndependence((this->field18_0x104)._s_0.w5u2,1);
      SetIndependence((this->field18_0x104)._s_0.w5u3,1);
      SetIndependence((this->field18_0x104)._s_0.w5u4,1);
      (this->field19_0x20c)._s_0.wavenumber = 6;
      (this->field16_0x40)._s_0.wave5arrive = false;
      (this->field17_0x88)._s_0.wave5 = 99999.0;
    }
  }
  if ((this->field16_0x40)._s_0.wave1arrive == false) {
    piVar1 = &(this->field18_0x104)._s_0.avrec;
    bVar3 = IsAlive(piVar1);
    if (bVar3) {
      fVar7 = GetDistance(*piVar1,(this->field18_0x104)._s_0.w1u1);
      if (300.0 <= fVar7) {
        fVar7 = GetDistance(*piVar1,(this->field18_0x104)._s_0.w1u2);
        if (300.0 <= fVar7) goto LAB_0042252b;
      }
      AudioMessage("misn0402.wav");
      (this->field16_0x40)._s_0.wave1arrive = true;
      (this->field16_0x40)._s_0.wave1dead = true;
    }
  }
LAB_0042252b:
  if ((this->field16_0x40)._s_0.wave2arrive == false) {
    piVar1 = &(this->field18_0x104)._s_0.avrec;
    bVar3 = IsAlive(piVar1);
    if (bVar3) {
      fVar7 = GetDistance(*piVar1,(this->field18_0x104)._s_0.w2u1);
      if (300.0 <= fVar7) {
        fVar7 = GetDistance(*piVar1,(this->field18_0x104)._s_0.w2u2);
        if (300.0 <= fVar7) goto LAB_00422588;
      }
      AudioMessage("misn0404.wav");
      (this->field16_0x40)._s_0.wave2arrive = true;
    }
  }
LAB_00422588:
  if ((this->field16_0x40)._s_0.wave3arrive == false) {
    piVar1 = &(this->field18_0x104)._s_0.avrec;
    bVar3 = IsAlive(piVar1);
    if (bVar3) {
      fVar7 = GetDistance(*piVar1,(this->field18_0x104)._s_0.w3u1);
      if (300.0 <= fVar7) {
        fVar7 = GetDistance(*piVar1,(this->field18_0x104)._s_0.w3u2);
        if (300.0 <= fVar7) {
          fVar7 = GetDistance(*piVar1,(this->field18_0x104)._s_0.w3u3);
          if (300.0 <= fVar7) goto LAB_00422601;
        }
      }
      AudioMessage("misn0410.wav");
      (this->field16_0x40)._s_0.wave3arrive = true;
    }
  }
LAB_00422601:
  if ((this->field16_0x40)._s_0.wave4arrive == false) {
    piVar1 = &(this->field18_0x104)._s_0.avrec;
    bVar3 = IsAlive(piVar1);
    if (bVar3) {
      fVar7 = GetDistance(*piVar1,(this->field18_0x104)._s_0.w4u1);
      if (300.0 <= fVar7) {
        fVar7 = GetDistance(*piVar1,(this->field18_0x104)._s_0.w4u2);
        if (300.0 <= fVar7) {
          fVar7 = GetDistance(*piVar1,(this->field18_0x104)._s_0.w4u3);
          if (300.0 <= fVar7) goto LAB_0042267a;
        }
      }
      AudioMessage("misn0412.wav");
      (this->field16_0x40)._s_0.wave4arrive = true;
    }
  }
LAB_0042267a:
  if ((this->field16_0x40)._s_0.wave5arrive == false) {
    piVar1 = &(this->field18_0x104)._s_0.avrec;
    bVar3 = IsAlive(piVar1);
    if (bVar3) {
      fVar7 = GetDistance(*piVar1,(this->field18_0x104)._s_0.w5u1);
      if (300.0 <= fVar7) {
        fVar7 = GetDistance(*piVar1,(this->field18_0x104)._s_0.w5u2);
        if (300.0 <= fVar7) {
          fVar7 = GetDistance(*piVar1,(this->field18_0x104)._s_0.w5u3);
          if (300.0 <= fVar7) {
            fVar7 = GetDistance(*piVar1,(this->field18_0x104)._s_0.w5u4);
            if (300.0 <= fVar7) goto LAB_00422713;
          }
        }
      }
      AudioMessage("misn0414.wav");
      (this->field16_0x40)._s_0.wave5arrive = true;
    }
  }
LAB_00422713:
  if ((this->field16_0x40)._s_0.attackccabase == false) {
    fVar7 = GetDistance((this->field18_0x104)._s_0.player,(this->field18_0x104)._s_0.svrec);
    if (fVar7 < 300.0) {
      AudioMessage("misn0423.wav");
      (this->field16_0x40)._s_0.attackccabase = true;
    }
  }
  if ((this->field16_0x40)._s_0.wave1dead == true) {
    bVar3 = IsAlive(&(this->field18_0x104)._s_0.w1u1);
    if (!bVar3) {
      bVar3 = IsAlive(&(this->field18_0x104)._s_0.w1u2);
      if (!bVar3) {
        AudioMessage("misn0403.wav");
        (this->field16_0x40)._s_0.wave1dead = false;
      }
    }
  }
  if ((this->field16_0x40)._s_0.wave2dead == true) {
    AudioMessage("misn0405.wav");
    (this->field16_0x40)._s_0.wave2dead = false;
  }
  if ((this->field16_0x40)._s_0.wave3dead == true) {
    AudioMessage("misn0411.wav");
    (this->field16_0x40)._s_0.wave3dead = false;
  }
  if ((this->field16_0x40)._s_0.wave4dead == true) {
    AudioMessage("misn0413.wav");
    (this->field16_0x40)._s_0.wave4dead = false;
  }
  if ((((this->field16_0x40)._s_0.loopbreak == false) &&
      ((this->field16_0x40)._s_0.possiblewin == false)) &&
     ((this->field16_0x40)._s_0.missionwon == false)) {
    bVar3 = IsAlive((this->field18_0x104).h_array);
    if (!bVar3) {
      AudioMessage("misn0417.wav");
      (this->field16_0x40)._s_0.possiblewin = true;
      (this->field16_0x40)._s_0.chewedout = true;
      bVar3 = IsAlive((this->field18_0x104).h_array);
      if (!bVar3) {
        bVar3 = IsAlive(&(this->field18_0x104)._s_0.w1u1);
        if (!bVar3) {
          bVar3 = IsAlive(&(this->field18_0x104)._s_0.w1u2);
          if (!bVar3) {
            bVar3 = IsAlive(&(this->field18_0x104)._s_0.w2u1);
            if (!bVar3) {
              bVar3 = IsAlive(&(this->field18_0x104)._s_0.w2u2);
              if (!bVar3) {
                bVar3 = IsAlive(&(this->field18_0x104)._s_0.w3u1);
                if (!bVar3) {
                  bVar3 = IsAlive(&(this->field18_0x104)._s_0.w3u2);
                  if (!bVar3) {
                    bVar3 = IsAlive(&(this->field18_0x104)._s_0.w3u3);
                    if (!bVar3) {
                      bVar3 = IsAlive(&(this->field18_0x104)._s_0.w4u1);
                      if (!bVar3) {
                        bVar3 = IsAlive(&(this->field18_0x104)._s_0.w4u2);
                        if (!bVar3) {
                          bVar3 = IsAlive(&(this->field18_0x104)._s_0.w4u3);
                          if (!bVar3) {
                            bVar3 = IsAlive(&(this->field18_0x104)._s_0.w5u1);
                            if (!bVar3) {
                              bVar3 = IsAlive(&(this->field18_0x104)._s_0.w5u2);
                              if (!bVar3) {
                                bVar3 = IsAlive(&(this->field18_0x104)._s_0.w5u3);
                                if (!bVar3) {
                                  bVar3 = IsAlive(&(this->field18_0x104)._s_0.w5u4);
                                  if (!bVar3) goto LAB_00422920;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
        AudioMessage("misn0418.wav");
        (this->field16_0x40)._s_0.loopbreak = true;
      }
    }
  }
LAB_00422920:
  if ((this->field16_0x40)._s_0.basesecure == false) {
    bVar3 = IsAlive((this->field18_0x104).h_array);
    if (!bVar3) {
      bVar3 = IsAlive(&(this->field18_0x104)._s_0.w1u1);
      if (!bVar3) {
        bVar3 = IsAlive(&(this->field18_0x104)._s_0.w1u2);
        if (!bVar3) {
          bVar3 = IsAlive(&(this->field18_0x104)._s_0.w2u1);
          if (!bVar3) {
            bVar3 = IsAlive(&(this->field18_0x104)._s_0.w2u2);
            if (!bVar3) {
              bVar3 = IsAlive(&(this->field18_0x104)._s_0.w3u1);
              if (!bVar3) {
                bVar3 = IsAlive(&(this->field18_0x104)._s_0.w3u2);
                if (!bVar3) {
                  bVar3 = IsAlive(&(this->field18_0x104)._s_0.w3u3);
                  if (!bVar3) {
                    bVar3 = IsAlive(&(this->field18_0x104)._s_0.w4u1);
                    if (!bVar3) {
                      bVar3 = IsAlive(&(this->field18_0x104)._s_0.w4u2);
                      if (!bVar3) {
                        bVar3 = IsAlive(&(this->field18_0x104)._s_0.w4u3);
                        if (!bVar3) {
                          bVar3 = IsAlive(&(this->field18_0x104)._s_0.w5u1);
                          if (!bVar3) {
                            bVar3 = IsAlive(&(this->field18_0x104)._s_0.w5u2);
                            if (!bVar3) {
                              bVar3 = IsAlive(&(this->field18_0x104)._s_0.w5u3);
                              if (!bVar3) {
                                bVar3 = IsAlive(&(this->field18_0x104)._s_0.w5u4);
                                if (!bVar3) {
                                  (this->field16_0x40)._s_0.basesecure = true;
                                  (this->field16_0x40)._s_0.newobjective = true;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  if (((this->field16_0x40)._s_0.relicsecure == true) &&
     ((this->field16_0x40)._s_0.basesecure == true)) {
    (this->field16_0x40)._s_0.missionwon = true;
  }
  if (((this->field16_0x40)._s_0.missionwon == true) &&
     ((this->field16_0x40)._s_0.endmission == false)) {
    _ftol2_sse();
    bVar3 = IsAudioMessageDone(extraout_EAX_13);
    if (bVar3) {
      _ftol2_sse();
      bVar3 = IsAudioMessageDone(extraout_EAX_14);
      if (bVar3) {
        _ftol2_sse();
        bVar3 = IsAudioMessageDone(extraout_EAX_15);
        if (bVar3) {
          _ftol2_sse();
          bVar3 = IsAudioMessageDone(extraout_EAX_16);
          if (bVar3) {
            pcVar8 = "misn04w1.des";
            fVar7 = Get_Time();
            SucceedMission(fVar7,pcVar8);
          }
        }
      }
    }
  }
  if ((this->field16_0x40)._s_0.missionwon == false) {
    bVar3 = IsAlive(&(this->field18_0x104)._s_0.avrec);
    if ((!bVar3) && ((this->field16_0x40)._s_0.missionfail == false)) {
      AudioMessage("misn0421.wav");
      AudioMessage("misn0422.wav");
      (this->field16_0x40)._s_0.missionfail = true;
      pcVar8 = "misn04l3.des";
      fVar7 = Get_Time();
      FailMission(fVar7 + 20.0,pcVar8);
    }
  }
  if ((((this->field16_0x40)._s_0.basesecure == false) &&
      ((this->field16_0x40)._s_0.secureloopbreak == false)) &&
     ((this->field19_0x20c)._s_0.wavenumber == 6)) {
    bVar3 = IsAlive(&(this->field18_0x104)._s_0.w5u1);
    if (!bVar3) {
      bVar3 = IsAlive(&(this->field18_0x104)._s_0.w5u2);
      if (!bVar3) {
        bVar3 = IsAlive(&(this->field18_0x104)._s_0.w5u3);
        if (!bVar3) {
          bVar3 = IsAlive(&(this->field18_0x104)._s_0.w5u4);
          if (!bVar3) {
            bVar3 = IsAlive((this->field18_0x104).h_array);
            if (bVar3) {
              if ((this->field16_0x40)._s_0.retreat == false) {
                piVar1 = &(this->field18_0x104)._s_0.tuge1;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.tuge2;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint28",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.pu1;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint27",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.pu2;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint26",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.pu3;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint25",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.pu4;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint24",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.pu5;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint23",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.pu6;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint22",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.pu7;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint21",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.pu8;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint20",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.cheat1;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint19",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.cheat2;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint18",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.cheat3;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint17",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.cheat4;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint16",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.cheat5;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint15",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.cheat6;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint14",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.cheat7;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint13",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.cheat8;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint12",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.cheat9;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint11",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.cheat10;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint10",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.surv1;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint9",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.surv2;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint8",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.surv3;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint7",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.surv4;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint6",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.turret1;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint2",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.turret2;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint3",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.turret3;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint4",1);
                }
                piVar1 = &(this->field18_0x104)._s_0.turret4;
                bVar3 = IsAlive(piVar1);
                if (bVar3) {
                  Retreat(*piVar1,"retreatpoint5",1);
                }
                (this->field16_0x40)._s_0.retreat = true;
              }
              iVar4 = AudioMessage("misn0415.wav");
              (this->field17_0x88)._s_0.aud21 = (float)iVar4;
              iVar4 = AudioMessage("misn0416.wav");
              (this->field17_0x88)._s_0.aud22 = (float)iVar4;
              (this->field16_0x40)._s_0.basesecure = true;
              (this->field16_0x40)._s_0.newobjective = true;
              (this->field16_0x40)._s_0.secureloopbreak = true;
            }
          }
        }
      }
    }
  }
  bVar3 = IsAlive(&(this->field18_0x104)._s_0.relic);
  if ((!bVar3) && ((this->field16_0x40)._s_0.missionfail == false)) {
    pcVar8 = "misn04l2.des";
    fVar7 = Get_Time();
    FailMission(fVar7 + 20.0,pcVar8);
    AudioMessage("misn0431.wav");
    AudioMessage("misn0432.wav");
    AudioMessage("misn0433.wav");
    AudioMessage("misn0434.wav");
    (this->field16_0x40)._s_0.missionfail = true;
  }
  if ((this->field19_0x20c)._s_0.wavenumber == 6) {
    IsAlive(&(this->field18_0x104)._s_0.w5u1);
    IsAlive(&(this->field18_0x104)._s_0.w5u2);
    IsAlive(&(this->field18_0x104)._s_0.w5u3);
    IsAlive(&(this->field18_0x104)._s_0.w5u4);
  }
  if ((((this->field16_0x40)._s_0.basesecure == false) &&
      ((this->field16_0x40)._s_0.secureloopbreak == false)) &&
     ((this->field19_0x20c)._s_0.wavenumber == 6)) {
    bVar3 = IsAlive(&(this->field18_0x104)._s_0.w5u1);
    if (!bVar3) {
      bVar3 = IsAlive(&(this->field18_0x104)._s_0.w5u2);
      if (!bVar3) {
        bVar3 = IsAlive(&(this->field18_0x104)._s_0.w5u3);
        if (!bVar3) {
          bVar3 = IsAlive(&(this->field18_0x104)._s_0.w5u4);
          if (!bVar3) {
            bVar3 = IsAlive((this->field18_0x104).h_array);
            if ((!bVar3) && ((this->field16_0x40)._s_0.chewedout == true)) {
              iVar4 = AudioMessage("misn0425.wav");
              (this->field17_0x88)._s_0.aud20 = (float)iVar4;
              (this->field16_0x40)._s_0.basesecure = true;
              (this->field16_0x40)._s_0.newobjective = true;
              (this->field16_0x40)._s_0.secureloopbreak = true;
            }
          }
        }
      }
    }
  }
  return;
}
