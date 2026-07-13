/*
 * Entry: 00442ff2
 * Name: Misns3Mission::Execute
 * Namespace: Misns3Mission
 * Signature: void Execute(Misns3Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns3Mission::Execute(Misns3Mission *this)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int extraout_EAX_03;
  int extraout_EAX_04;
  float fVar4;
  char *pcVar5;
  
  if ((this->field16_0x40)._s_0.missionstart == false) {
    AudioMessage("misns301.wav");
    (this->field16_0x40)._s_0.newobjective = true;
    (this->field16_0x40)._s_0.missionstart = true;
    iVar3 = GetHandle("avrecy1_recycler");
    (this->field18_0x70)._s_0.avrec = iVar3;
    iVar3 = GetPlayerHandle();
    (this->field18_0x70)._s_0.player = iVar3;
    fVar4 = Get_Time();
    (this->field17_0x5c)._s_0.withdraw = fVar4 + 600.0;
    fVar4 = Get_Time();
    (this->field17_0x5c)._s_0.help1 = fVar4 + 120.0;
    fVar4 = Get_Time();
    (this->field17_0x5c)._s_0.help2 = fVar4 + 280.0;
    fVar4 = Get_Time();
    (this->field17_0x5c)._s_0.help3 = fVar4 + 380.0;
    Get_Time();
    _ftol2_sse();
    (this->field19_0x104)._s_0.Checkdist = extraout_EAX;
    Get_Time();
    _ftol2_sse();
    (this->field19_0x104)._s_0.Checkdist2 = extraout_EAX_00;
    Get_Time();
    _ftol2_sse();
    (this->field19_0x104)._s_0.Checkalive = extraout_EAX_01;
    iVar3 = GetHandle("bomb1");
    (this->field18_0x70)._s_0.bomb1 = iVar3;
    iVar3 = GetHandle("bomb2");
    (this->field18_0x70)._s_0.bomb2 = iVar3;
    iVar3 = GetHandle("bomb3");
    (this->field18_0x70)._s_0.bomb3 = iVar3;
    iVar3 = GetHandle("bomb4");
    (this->field18_0x70)._s_0.bomb4 = iVar3;
    iVar3 = GetHandle("basenav");
    (this->field18_0x70)._s_0.cam1 = iVar3;
    piVar1 = &(this->field18_0x70)._s_0.cam2;
    iVar3 = GetHandle("avrecy");
    *piVar1 = iVar3;
    SetObjectiveName((this->field18_0x70)._s_0.cam1,"Home Base");
    SetObjectiveName(*piVar1,"Black Dog Outpost");
  }
  iVar3 = GetPlayerHandle();
  bVar2 = (this->field16_0x40)._s_0.newobjective;
  (this->field18_0x70)._s_0.player = iVar3;
  if (bVar2 == true) {
    InfoDisplay::ClearObjectives(&infoDisplay);
    if ((this->field16_0x40)._s_0.recyclerdestroyed == true) {
      InfoDisplay::AddObjective(&infoDisplay,"misns302.otf",DisplayInterface::colorWhite,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misns301.otf",DisplayInterface::colorGreen,8.0);
    }
    if ((this->field16_0x40)._s_0.recyclerdestroyed == false) {
      InfoDisplay::AddObjective(&infoDisplay,"misns301.otf",DisplayInterface::colorWhite,8.0);
    }
    if ((this->field16_0x40)._s_0.missionwon == true) {
      InfoDisplay::AddObjective(&infoDisplay,"misns302.otf",DisplayInterface::colorGreen,8.0);
    }
    (this->field16_0x40)._s_0.newobjective = false;
  }
  fVar4 = Get_Time();
  if ((((this->field17_0x5c)._s_0.help1 < fVar4) && ((this->field16_0x40)._s_0.plea1 == false)) &&
     ((this->field16_0x40)._s_0.recyclerdestroyed == false)) {
    AudioMessage("misns307.wav");
    (this->field16_0x40)._s_0.plea1 = true;
  }
  fVar4 = Get_Time();
  if ((((this->field17_0x5c)._s_0.help2 < fVar4) && ((this->field16_0x40)._s_0.plea2 == false)) &&
     ((this->field16_0x40)._s_0.recyclerdestroyed == false)) {
    AudioMessage("misns308.wav");
    (this->field16_0x40)._s_0.plea2 = true;
  }
  fVar4 = Get_Time();
  if ((((this->field17_0x5c)._s_0.help3 < fVar4) && ((this->field16_0x40)._s_0.plea3 == false)) &&
     ((this->field16_0x40)._s_0.recyclerdestroyed == false)) {
    AudioMessage("misns309.wav");
    (this->field16_0x40)._s_0.plea3 = true;
  }
  bVar2 = IsAlive(&(this->field18_0x70)._s_0.avrec);
  if (((bVar2) &&
      (fVar4 = GetDistance((this->field18_0x70)._s_0.player,"bdspawntrig",0), fVar4 < 200.0)) &&
     ((this->field16_0x40)._s_0.bdspawned == false)) {
    iVar3 = BuildObject("avtank",2,"bdspawn1",0);
    (this->field18_0x70)._s_0.bd1 = iVar3;
    iVar3 = BuildObject("avtank",2,"bdspawn1",0);
    (this->field18_0x70)._s_0.bd2 = iVar3;
    iVar3 = BuildObject("avtank",2,"bdspawn1",0);
    (this->field18_0x70)._s_0.bd3 = iVar3;
    iVar3 = BuildObject("avfigh",2,"bdspawn1",0);
    (this->field18_0x70)._s_0.bd4 = iVar3;
    iVar3 = BuildObject("avfigh",2,"bdspawn1",0);
    (this->field18_0x70)._s_0.bd5 = iVar3;
    Attack((this->field18_0x70)._s_0.bd1,(this->field18_0x70)._s_0.player,1);
    Attack((this->field18_0x70)._s_0.bd2,(this->field18_0x70)._s_0.player,1);
    Attack((this->field18_0x70)._s_0.bd3,(this->field18_0x70)._s_0.player,1);
    Attack((this->field18_0x70)._s_0.bd4,(this->field18_0x70)._s_0.player,1);
    Attack((this->field18_0x70)._s_0.bd5,(this->field18_0x70)._s_0.player,1);
    (this->field16_0x40)._s_0.bdspawned = true;
    AudioMessage("misns310.wav");
  }
  if ((this->field16_0x40)._s_0.bdspawned == true) {
    IsAlive((this->field18_0x70).h_array);
    IsAlive((this->field18_0x70).h_array);
    IsAlive((this->field18_0x70).h_array);
    IsAlive((this->field18_0x70).h_array);
    IsAlive((this->field18_0x70).h_array);
    if (((this->field16_0x40)._s_0.bdspawned == true) &&
       (fVar4 = Get_Time(), (float)(this->field19_0x104)._s_0.Checkalive < fVar4)) {
      bVar2 = IsAlive((this->field18_0x70).h_array);
      if (bVar2) {
        Attack((this->field18_0x70)._s_0.bd1,(this->field18_0x70)._s_0.player,1);
      }
      bVar2 = IsAlive(&(this->field18_0x70)._s_0.bd2);
      if (bVar2) {
        Attack((this->field18_0x70)._s_0.bd2,(this->field18_0x70)._s_0.player,1);
      }
      bVar2 = IsAlive(&(this->field18_0x70)._s_0.bd3);
      if (bVar2) {
        Attack((this->field18_0x70)._s_0.bd3,(this->field18_0x70)._s_0.player,1);
      }
      bVar2 = IsAlive(&(this->field18_0x70)._s_0.bd4);
      if (bVar2) {
        Attack((this->field18_0x70)._s_0.bd4,(this->field18_0x70)._s_0.player,1);
      }
      bVar2 = IsAlive(&(this->field18_0x70)._s_0.bd5);
      if (bVar2) {
        Attack((this->field18_0x70)._s_0.bd5,(this->field18_0x70)._s_0.player,1);
      }
      bVar2 = IsAlive((this->field18_0x70).h_array);
      if (((!bVar2) && (bVar2 = IsAlive(&(this->field18_0x70)._s_0.bd2), !bVar2)) &&
         ((bVar2 = IsAlive(&(this->field18_0x70)._s_0.bd3), !bVar2 &&
          ((bVar2 = IsAlive(&(this->field18_0x70)._s_0.bd4), !bVar2 &&
           (bVar2 = IsAlive(&(this->field18_0x70)._s_0.bd5), !bVar2)))))) {
        iVar3 = BuildObject("avtank",2,"bdspawn1",0);
        (this->field18_0x70)._s_0.bd1 = iVar3;
        iVar3 = BuildObject("avtank",2,"bdspawn1",0);
        (this->field18_0x70)._s_0.bd2 = iVar3;
        iVar3 = BuildObject("avtank",2,"bdspawn1",0);
        (this->field18_0x70)._s_0.bd3 = iVar3;
        iVar3 = BuildObject("avfigh",2,"bdspawn1",0);
        (this->field18_0x70)._s_0.bd4 = iVar3;
        iVar3 = BuildObject("avfigh",2,"bdspawn1",0);
        (this->field18_0x70)._s_0.bd5 = iVar3;
      }
      Get_Time();
      _ftol2_sse();
      (this->field19_0x104)._s_0.Checkalive = extraout_EAX_02;
    }
  }
  bVar2 = IsAlive(&(this->field18_0x70)._s_0.avrec);
  if ((!bVar2) && ((this->field16_0x40)._s_0.recyclerdestroyed == false)) {
    AudioMessage("misns302.wav");
    if ((this->field16_0x40)._s_0.bdspawned2 == false) {
      iVar3 = BuildObject("avtank",2,"bdspawn1",0);
      (this->field18_0x70)._s_0.bd50 = iVar3;
      iVar3 = BuildObject("avfigh",2,"bdspawn1",0);
      (this->field18_0x70)._s_0.bd60 = iVar3;
      iVar3 = BuildObject("avfigh",2,"bdspawn1",0);
      (this->field18_0x70)._s_0.bd70 = iVar3;
      iVar3 = BuildObject("avtank",2,"bdspawn1",0);
      (this->field18_0x70)._s_0.bd80 = iVar3;
      Goto((this->field18_0x70)._s_0.bd50,"bdpath1",1);
      Goto((this->field18_0x70)._s_0.bd60,"bdpath2",1);
      Goto((this->field18_0x70)._s_0.bd70,"bdpath3",1);
      Goto((this->field18_0x70)._s_0.bd80,"bdpath4",1);
      (this->field16_0x40)._s_0.bdspawned2 = true;
      (this->field16_0x40)._s_0.bdspawned = false;
    }
    (this->field16_0x40)._s_0.economy1 = true;
    (this->field16_0x40)._s_0.economy2 = true;
    (this->field16_0x40)._s_0.economy3 = true;
    (this->field16_0x40)._s_0.economy4 = true;
    (this->field16_0x40)._s_0.recyclerdestroyed = true;
    (this->field16_0x40)._s_0.newobjective = true;
  }
  if ((((this->field16_0x40)._s_0.economy1 == true) &&
      (fVar4 = GetDistance((this->field18_0x70)._s_0.player,(this->field18_0x70)._s_0.bd50),
      fVar4 < 410.0)) && ((this->field16_0x40)._s_0.unit1spawned == false)) {
    iVar3 = BuildObject("avtank",2,(this->field18_0x70)._s_0.bd50);
    (this->field18_0x70)._s_0.bd51 = iVar3;
    iVar3 = BuildObject("avtank",2,(this->field18_0x70)._s_0.bd50);
    (this->field18_0x70)._s_0.bd52 = iVar3;
    Follow((this->field18_0x70)._s_0.bd51,(this->field18_0x70)._s_0.bd50,1);
    Follow((this->field18_0x70)._s_0.bd52,(this->field18_0x70)._s_0.bd50,1);
    (this->field16_0x40)._s_0.unit1spawned = true;
  }
  if ((((this->field16_0x40)._s_0.economy2 == true) &&
      (fVar4 = GetDistance((this->field18_0x70)._s_0.player,(this->field18_0x70)._s_0.bd60),
      fVar4 < 410.0)) && ((this->field16_0x40)._s_0.unit2spawned == false)) {
    iVar3 = BuildObject("avfigh",2,(this->field18_0x70)._s_0.bd60);
    (this->field18_0x70)._s_0.bd61 = iVar3;
    iVar3 = BuildObject("avfigh",2,(this->field18_0x70)._s_0.bd60);
    (this->field18_0x70)._s_0.bd62 = iVar3;
    Follow((this->field18_0x70)._s_0.bd61,(this->field18_0x70)._s_0.bd60,1);
    Follow((this->field18_0x70)._s_0.bd62,(this->field18_0x70)._s_0.bd60,1);
    (this->field16_0x40)._s_0.unit2spawned = true;
  }
  if ((((this->field16_0x40)._s_0.economy3 == true) &&
      (fVar4 = GetDistance((this->field18_0x70)._s_0.player,(this->field18_0x70)._s_0.bd70),
      fVar4 < 410.0)) && ((this->field16_0x40)._s_0.unit3spawned == false)) {
    iVar3 = BuildObject("avfigh",2,(this->field18_0x70)._s_0.bd70);
    (this->field18_0x70)._s_0.bd71 = iVar3;
    iVar3 = BuildObject("avtank",2,(this->field18_0x70)._s_0.bd70);
    (this->field18_0x70)._s_0.bd72 = iVar3;
    Follow((this->field18_0x70)._s_0.bd71,(this->field18_0x70)._s_0.bd70,1);
    Follow((this->field18_0x70)._s_0.bd72,(this->field18_0x70)._s_0.bd70,1);
    (this->field16_0x40)._s_0.unit3spawned = true;
  }
  if ((((this->field16_0x40)._s_0.economy4 == true) &&
      (fVar4 = GetDistance((this->field18_0x70)._s_0.player,(this->field18_0x70)._s_0.bd80),
      fVar4 < 410.0)) && ((this->field16_0x40)._s_0.unit4spawned == false)) {
    iVar3 = BuildObject("avtank",2,(this->field18_0x70)._s_0.bd80);
    (this->field18_0x70)._s_0.bd81 = iVar3;
    iVar3 = BuildObject("avtank",2,(this->field18_0x70)._s_0.bd80);
    (this->field18_0x70)._s_0.bd82 = iVar3;
    Follow((this->field18_0x70)._s_0.bd81,(this->field18_0x70)._s_0.bd80,1);
    Follow((this->field18_0x70)._s_0.bd82,(this->field18_0x70)._s_0.bd80,1);
    (this->field16_0x40)._s_0.unit4spawned = true;
  }
  fVar4 = GetDistance((this->field18_0x70)._s_0.player,"homesweethome",0);
  if (((fVar4 < 200.0) && ((this->field16_0x40)._s_0.missionwon == false)) &&
     ((this->field16_0x40)._s_0.recyclerdestroyed == true)) {
    iVar3 = AudioMessage("misns303.wav");
    (this->field19_0x104)._s_0.aud50 = iVar3;
    (this->field16_0x40)._s_0.missionwon = true;
  }
  if (((this->field16_0x40)._s_0.missionwon == true) &&
     (bVar2 = IsAudioMessageDone((this->field19_0x104)._s_0.aud50), bVar2)) {
    pcVar5 = "misns3w1.des";
    fVar4 = Get_Time();
    SucceedMission(fVar4,pcVar5);
  }
  fVar4 = Get_Time();
  if ((((this->field17_0x5c)._s_0.withdraw < fVar4) &&
      ((this->field16_0x40)._s_0.recyclerdestroyed == false)) &&
     ((this->field16_0x40)._s_0.missionfail == false)) {
    iVar3 = AudioMessage("misns304.wav");
    (this->field19_0x104)._s_0.aud2 = iVar3;
    (this->field16_0x40)._s_0.missionfail = true;
  }
  if (((this->field16_0x40)._s_0.missionfail == true) &&
     (bVar2 = IsAudioMessageDone((this->field19_0x104)._s_0.aud2), bVar2)) {
    pcVar5 = "misns3l1.des";
    fVar4 = Get_Time();
    FailMission(fVar4,pcVar5);
  }
  fVar4 = GetDistance((this->field18_0x70)._s_0.player,"don\'tgohere",0);
  if (((fVar4 < 50.0) && ((this->field16_0x40)._s_0.warn1 == false)) &&
     ((this->field16_0x40)._s_0.recyclerdestroyed == false)) {
    AudioMessage("misns305.wav");
    (this->field16_0x40)._s_0.warn1 = true;
  }
  fVar4 = GetDistance((this->field18_0x70)._s_0.player,"iwarnedyou",0);
  if (((fVar4 < 50.0) && ((this->field16_0x40)._s_0.warn2 == false)) &&
     ((this->field16_0x40)._s_0.recyclerdestroyed == false)) {
    iVar3 = AudioMessage("misns306.wav");
    (this->field19_0x104)._s_0.aud1 = iVar3;
    (this->field16_0x40)._s_0.warn2 = true;
  }
  if (((this->field16_0x40)._s_0.warn2 == true) &&
     (bVar2 = IsAudioMessageDone((this->field19_0x104)._s_0.aud1), bVar2)) {
    pcVar5 = "misns3l2.des";
    fVar4 = Get_Time();
    FailMission(fVar4,pcVar5);
  }
  if ((((this->field16_0x40)._s_0.patrolspawned == false) &&
      ((this->field16_0x40)._s_0.bdspawned == false)) &&
     ((bVar2 = IsAlive(&(this->field18_0x70)._s_0.avrec), bVar2 &&
      (fVar4 = Get_Time(), (float)(this->field19_0x104)._s_0.Checkdist < fVar4)))) {
    fVar4 = GetDistance((this->field18_0x70)._s_0.bomb1,"patroltrig1",0);
    if ((((fVar4 < 100.0) ||
         (fVar4 = GetDistance((this->field18_0x70)._s_0.bomb2,"patroltrig1",0), fVar4 < 100.0)) ||
        (fVar4 = GetDistance((this->field18_0x70)._s_0.bomb3,"patroltrig1",0), fVar4 < 100.0)) ||
       ((fVar4 = GetDistance((this->field18_0x70)._s_0.bomb4,"patroltrig1",0), fVar4 < 100.0 ||
        (fVar4 = GetDistance((this->field18_0x70)._s_0.player,"patroltrig1",0), fVar4 < 100.0)))) {
      iVar3 = BuildObject("bvraz",2,"patrolspawn1",0);
      (this->field18_0x70)._s_0.pat1 = iVar3;
      iVar3 = BuildObject("bvraz",2,"patrolspawn1",0);
      (this->field18_0x70)._s_0.pat2 = iVar3;
      AudioMessage("misns219.wav");
      Goto((this->field18_0x70)._s_0.pat1,"patrolpath1",1);
      Goto((this->field18_0x70)._s_0.pat2,"patrolpath1",1);
      SetIndependence((this->field18_0x70)._s_0.pat1,0);
      SetIndependence((this->field18_0x70)._s_0.pat2,0);
      (this->field16_0x40)._s_0.patrolspawned = true;
    }
    fVar4 = GetDistance((this->field18_0x70)._s_0.bomb1,"patroltrig2",0);
    if (((fVar4 < 100.0) ||
        (fVar4 = GetDistance((this->field18_0x70)._s_0.bomb2,"patroltrig2",0), fVar4 < 100.0)) ||
       ((fVar4 = GetDistance((this->field18_0x70)._s_0.bomb3,"patroltrig2",0), fVar4 < 100.0 ||
        ((fVar4 = GetDistance((this->field18_0x70)._s_0.bomb4,"patroltrig2",0), fVar4 < 100.0 ||
         (fVar4 = GetDistance((this->field18_0x70)._s_0.player,"patroltrig2",0), fVar4 < 100.0))))))
    {
      iVar3 = BuildObject("bvraz",2,"patrolspawn2",0);
      (this->field18_0x70)._s_0.pat1 = iVar3;
      iVar3 = BuildObject("bvraz",2,"patrolspawn2",0);
      (this->field18_0x70)._s_0.pat2 = iVar3;
      AudioMessage("misns219.wav");
      Goto((this->field18_0x70)._s_0.pat1,"patrolpath2",1);
      Goto((this->field18_0x70)._s_0.pat2,"patrolpath2",1);
      SetIndependence((this->field18_0x70)._s_0.pat1,0);
      SetIndependence((this->field18_0x70)._s_0.pat2,0);
      (this->field16_0x40)._s_0.patrolspawned = true;
    }
    Get_Time();
    _ftol2_sse();
    (this->field19_0x104)._s_0.Checkdist = extraout_EAX_03;
  }
  if ((((this->field16_0x40)._s_0.mark1 == false) &&
      ((this->field16_0x40)._s_0.patrolspawned == true)) &&
     ((this->field16_0x40)._s_0.bdspawned == false)) {
    iVar3 = GetNearestEnemy((this->field18_0x70)._s_0.pat1);
    (this->field18_0x70)._s_0.Enemy1 = iVar3;
    iVar3 = GetNearestEnemy((this->field18_0x70)._s_0.pat2);
    (this->field18_0x70)._s_0.Enemy2 = iVar3;
    fVar4 = Get_Time();
    piVar1 = &(this->field19_0x104)._s_0.Checkdist2;
    if ((float)*piVar1 < fVar4) {
      fVar4 = GetDistance((this->field18_0x70)._s_0.pat1,(this->field18_0x70)._s_0.Enemy1);
      if (fVar4 < 180.0) {
        iVar3 = (this->field18_0x70)._s_0.Enemy1;
        (this->field16_0x40)._s_0.bdspawned = true;
        Attack((this->field18_0x70)._s_0.pat1,iVar3,1);
        Attack((this->field18_0x70)._s_0.pat2,(this->field18_0x70)._s_0.Enemy1,1);
        (this->field16_0x40)._s_0.play = true;
      }
      fVar4 = GetDistance((this->field18_0x70)._s_0.pat2,(this->field18_0x70)._s_0.Enemy2);
      if (fVar4 < 180.0) {
        iVar3 = (this->field18_0x70)._s_0.Enemy2;
        (this->field16_0x40)._s_0.bdspawned = true;
        Attack((this->field18_0x70)._s_0.pat2,iVar3,1);
        Attack((this->field18_0x70)._s_0.pat1,(this->field18_0x70)._s_0.Enemy2,1);
        (this->field16_0x40)._s_0.play = true;
      }
      Get_Time();
      _ftol2_sse();
      bVar2 = (this->field16_0x40)._s_0.play;
      *piVar1 = extraout_EAX_04;
      if ((bVar2 == true) && ((this->field16_0x40)._s_0.mark1 == false)) {
        AudioMessage("misns220.wav");
        (this->field16_0x40)._s_0.mark1 = true;
      }
    }
  }
  if (((this->field16_0x40)._s_0.minefield1 == false) &&
     ((fVar4 = GetDistance((this->field18_0x70)._s_0.player,"minetrig1",0), fVar4 < 200.0 ||
      (fVar4 = GetDistance((this->field18_0x70)._s_0.player,"minetrig1b",0), fVar4 < 200.0)))) {
    BuildObject("proxmine",2,"path_1",0);
    BuildObject("proxmine",2,"path_2",0);
    BuildObject("proxmine",2,"path_3",0);
    BuildObject("proxmine",2,"path_4",0);
    BuildObject("proxmine",2,"path_5",0);
    BuildObject("proxmine",2,"path_6",0);
    BuildObject("proxmine",2,"path_7",0);
    BuildObject("proxmine",2,"path_8",0);
    BuildObject("proxmine",2,"path_9",0);
    BuildObject("proxmine",2,"path_10",0);
    BuildObject("proxmine",2,"path_11",0);
    (this->field16_0x40)._s_0.minefield1 = true;
  }
  if (((this->field16_0x40)._s_0.minefield2 == false) &&
     ((fVar4 = GetDistance((this->field18_0x70)._s_0.player,"minetrig2",0), fVar4 < 200.0 ||
      (fVar4 = GetDistance((this->field18_0x70)._s_0.player,"minetrig2b",0), fVar4 < 200.0)))) {
    BuildObject("proxmine",2,"path_12",0);
    BuildObject("proxmine",2,"path_13",0);
    BuildObject("proxmine",2,"path_14",0);
    BuildObject("proxmine",2,"path_15",0);
    BuildObject("proxmine",2,"path_16",0);
    BuildObject("proxmine",2,"path_17",0);
    BuildObject("proxmine",2,"path_18",0);
    BuildObject("proxmine",2,"path_19",0);
    BuildObject("proxmine",2,"path_20",0);
    BuildObject("proxmine",2,"path_21",0);
    BuildObject("proxmine",2,"path_22",0);
    (this->field16_0x40)._s_0.minefield2 = true;
  }
  if (((this->field16_0x40)._s_0.minefield3 == false) &&
     ((fVar4 = GetDistance((this->field18_0x70)._s_0.player,"minetrig3",0), fVar4 < 200.0 ||
      (fVar4 = GetDistance((this->field18_0x70)._s_0.player,"minetrig3b",0), fVar4 < 200.0)))) {
    BuildObject("proxmine",2,"path_23",0);
    BuildObject("proxmine",2,"path_24",0);
    BuildObject("proxmine",2,"path_25",0);
    BuildObject("proxmine",2,"path_26",0);
    BuildObject("proxmine",2,"path_27",0);
    BuildObject("proxmine",2,"path_28",0);
    BuildObject("proxmine",2,"path_29",0);
    BuildObject("proxmine",2,"path_30",0);
    BuildObject("proxmine",2,"path_31",0);
    BuildObject("proxmine",2,"path_32",0);
    BuildObject("proxmine",2,"path_33",0);
    BuildObject("proxmine",2,"path_34",0);
    (this->field16_0x40)._s_0.minefield3 = true;
  }
  return;
}
