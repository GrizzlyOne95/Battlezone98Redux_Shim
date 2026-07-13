/*
 * Entry: 0043d7e6
 * Name: Misn18Mission::Execute
 * Namespace: Misn18Mission
 * Signature: void Execute(Misn18Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn18Mission::Execute(Misn18Mission *this)

{
  Misn18Mission_u_424 *pMVar1;
  int *piVar2;
  int *piVar3;
  bool bVar4;
  int iVar5;
  int extraout_EAX;
  float fVar6;
  char *pcVar7;
  
  if ((this->field16_0x40)._s_0.missionstart == false) {
    iVar5 = AudioMessage("misn1801.wav");
    (this->field18_0xa4)._s_0.aud1 = iVar5;
    iVar5 = GetHandle("avrecy2_recycler");
    (this->field18_0xa4)._s_0.avrec = iVar5;
    SetScrap(1,0x50);
    iVar5 = GetHandle("scrapcam");
    (this->field18_0xa4)._s_0.scrapcam = iVar5;
    iVar5 = GetHandle("scrapcam2");
    (this->field18_0xa4)._s_0.scrapcam2 = iVar5;
    fVar6 = Get_Time();
    (this->field17_0x6c)._s_0.rand1 = fVar6 + 150.0;
    fVar6 = Get_Time();
    (this->field17_0x6c)._s_0.rand2 = fVar6 + 230.0;
    fVar6 = Get_Time();
    (this->field17_0x6c)._s_0.rand3 = fVar6 + 310.0;
    fVar6 = Get_Time();
    (this->field17_0x6c)._s_0.gettosavtrans = fVar6 + 600.0;
    iVar5 = GetHandle("basenav");
    (this->field18_0xa4)._s_0.basenav = iVar5;
    SetObjectiveName(iVar5,"Home Base");
    (this->field16_0x40)._s_0.missionstart = true;
    iVar5 = GetHandle("hbtrn20049_i76building");
    (this->field18_0xa4)._s_0.thrusterone = iVar5;
    iVar5 = GetHandle("hbtrn20050_i76building");
    (this->field18_0xa4)._s_0.thrustertwo = iVar5;
    iVar5 = GetHandle("hbtrn20051_i76building");
    (this->field18_0xa4)._s_0.thrusterthree = iVar5;
    iVar5 = GetHandle("hbtrn20052_i76building");
    (this->field18_0xa4)._s_0.thrusterfour = iVar5;
    iVar5 = GetHandle("hbtran0038_i76building");
    (this->field18_0xa4)._s_0.transport = iVar5;
    EarthQuake::StartQuake(&earthQuake,2.0);
    (this->field19_0x1a8)._s_0.quake_level = 2;
    fVar6 = Get_Time();
    iVar5 = (this->field18_0xa4)._s_0.transport;
    (this->field16_0x40)._s_0.newobjective = true;
    (this->field17_0x6c)._s_0.quake_check = fVar6 + 2.0;
    SetObjectiveOn(iVar5);
    SetObjectiveName((this->field18_0xa4)._s_0.transport,"Fury Transport");
    fVar6 = Get_Time();
    (this->field17_0x6c)._s_0.next_second = fVar6 + 5.0;
    fVar6 = Get_Time();
    (this->field17_0x6c)._s_0.enemycheck = fVar6 + 3.0;
  }
  iVar5 = GetPlayerHandle();
  (this->field18_0xa4)._s_0.player = iVar5;
  if ((this->field16_0x40)._s_0.transportfound == false) {
    fVar6 = Get_Time();
    if ((this->field17_0x6c)._s_0.enemycheck < fVar6) {
      bVar4 = IsAlive((this->field18_0xa4).h_array);
      if (bVar4) {
        iVar5 = GetNearestEnemy((this->field18_0xa4)._s_0.transport);
        (this->field18_0xa4)._s_0.enemy = iVar5;
        fVar6 = Get_Time();
        (this->field17_0x6c)._s_0.enemycheck = fVar6 + 3.0;
      }
    }
  }
  if ((this->field16_0x40)._s_0.newobjective == true) {
    InfoDisplay::ClearObjectives(&infoDisplay);
    if ((this->field16_0x40)._s_0.missionwon == true) {
      InfoDisplay::AddObjective(&infoDisplay,"misn1803.otf",DisplayInterface::colorGreen,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn1802.otf",DisplayInterface::colorGreen,8.0);
    }
    if (((this->field16_0x40)._s_0.transdestroyed == true) &&
       ((this->field16_0x40)._s_0.missionwon == false)) {
      InfoDisplay::AddObjective(&infoDisplay,"misn1803.otf",DisplayInterface::colorWhite,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn1802.otf",DisplayInterface::colorGreen,8.0);
    }
    if (((this->field16_0x40)._s_0.transdestroyed == false) &&
       ((this->field16_0x40)._s_0.transportfound == true)) {
      InfoDisplay::AddObjective(&infoDisplay,"misn1802.otf",DisplayInterface::colorWhite,8.0);
    }
    if ((this->field16_0x40)._s_0.transportfound == false) {
      InfoDisplay::AddObjective(&infoDisplay,"misn1801.otf",DisplayInterface::colorWhite,8.0);
    }
    (this->field16_0x40)._s_0.newobjective = false;
  }
  if ((this->field16_0x40)._s_0.openingcin == false) {
    CameraReady();
    (this->field16_0x40)._s_0.camera1 = true;
    (this->field16_0x40)._s_0.openingcin = true;
  }
  if ((this->field16_0x40)._s_0.camera2 == true) {
    bVar4 = CameraPath("opencam1",0x5dc,8000,(this->field18_0xa4)._s_0.scrapcam);
    if (bVar4) {
      (this->field16_0x40)._s_0.camera2 = false;
      (this->field16_0x40)._s_0.camera3 = true;
    }
  }
  if ((this->field16_0x40)._s_0.camera3 == true) {
    bVar4 = CameraPath("opencam2",0x5dc,9000,(this->field18_0xa4)._s_0.scrapcam2);
    if (bVar4) {
      iVar5 = (this->field18_0xa4)._s_0.scrapcam;
      (this->field16_0x40)._s_0.camera3 = false;
      RemoveObject(iVar5);
      RemoveObject((this->field18_0xa4)._s_0.scrapcam2);
    }
  }
  if ((this->field16_0x40)._s_0.camera1 == true) {
    pMVar1 = &this->field19_0x1a8;
    TimeStep();
    _ftol2_sse();
    (pMVar1->_s_0).x = (pMVar1->_s_0).x + extraout_EAX;
    bVar4 = CameraPath("opencam3",(pMVar1->_s_0).x,2000,(this->field18_0xa4)._s_0.transport);
    if (bVar4) {
      (this->field16_0x40)._s_0.camera1 = false;
      (this->field16_0x40)._s_0.camera2 = true;
    }
  }
  if ((this->field16_0x40)._s_0.openingcindone == false) {
    piVar2 = &(this->field18_0xa4)._s_0.aud1;
    bVar4 = IsAudioMessageDone(*piVar2);
    if (!bVar4) {
      bVar4 = CameraCancelled();
      if (!bVar4) goto LAB_0043db93;
    }
    StopAudioMessage(*piVar2);
    (this->field16_0x40)._s_0.openingcindone = true;
    (this->field16_0x40)._s_0.camera1 = false;
    (this->field16_0x40)._s_0.camera2 = false;
    (this->field16_0x40)._s_0.camera3 = false;
    CameraFinish();
  }
LAB_0043db93:
  if ((this->field16_0x40)._s_0.transdestroyed == false) {
    bVar4 = IsAlive((this->field18_0xa4).h_array);
    if (bVar4) {
      fVar6 = Get_Time();
      if ((this->field17_0x6c)._s_0.next_second < fVar6) {
        AddHealth((this->field18_0xa4)._s_0.transport,100.0);
      }
    }
  }
  if (((this->field16_0x40)._s_0.transdestroyed == true) &&
     ((this->field16_0x40)._s_0.transblownup == false)) {
    Damage((this->field18_0xa4)._s_0.transport,1000000000);
    (this->field16_0x40)._s_0.transblownup = true;
  }
  if ((this->field16_0x40)._s_0.transportfound == false) {
    fVar6 = Get_Time();
    if ((this->field17_0x6c)._s_0.next_second < fVar6) {
      piVar2 = &(this->field18_0xa4)._s_0.thrusterone;
      bVar4 = IsAlive(piVar2);
      if (bVar4) {
        AddHealth(*piVar2,50.0);
      }
      piVar2 = &(this->field18_0xa4)._s_0.thrustertwo;
      bVar4 = IsAlive(piVar2);
      if (bVar4) {
        AddHealth(*piVar2,50.0);
      }
      piVar2 = &(this->field18_0xa4)._s_0.thrusterthree;
      bVar4 = IsAlive(piVar2);
      if (bVar4) {
        AddHealth(*piVar2,50.0);
      }
      piVar2 = &(this->field18_0xa4)._s_0.thrusterfour;
      bVar4 = IsAlive(piVar2);
      if (bVar4) {
        AddHealth(*piVar2,50.0);
      }
      fVar6 = Get_Time();
      (this->field17_0x6c)._s_0.next_second = fVar6 + 1.0;
    }
  }
  if ((this->field16_0x40)._s_0.wave1start == false) {
    fVar6 = GetDistance((this->field18_0xa4)._s_0.player,"spawn1a",0);
    if (100.0 <= fVar6) {
      fVar6 = GetDistance((this->field18_0xa4)._s_0.player,"spawnalt1a",0);
      if (100.0 <= fVar6) {
        fVar6 = GetDistance((this->field18_0xa4)._s_0.player,"cheat1a",0);
        if (200.0 <= fVar6) {
          fVar6 = GetDistance((this->field18_0xa4)._s_0.player,"cheatalt1a",0);
          if (200.0 <= fVar6) goto LAB_0043ddb1;
        }
      }
    }
    iVar5 = BuildObject("hvsat",2,"spawn1b",0);
    (this->field18_0xa4)._s_0.w1u1 = iVar5;
    iVar5 = BuildObject("hvsat",2,"spawnalt1b",0);
    (this->field18_0xa4)._s_0.w1u3 = iVar5;
    Goto((this->field18_0xa4)._s_0.w1u1,"transport1",1);
    Goto((this->field18_0xa4)._s_0.w1u3,"transport2",1);
    SetIndependence((this->field18_0xa4)._s_0.w1u1,1);
    SetIndependence((this->field18_0xa4)._s_0.w1u3,1);
    (this->field16_0x40)._s_0.wave1start = true;
  }
LAB_0043ddb1:
  if ((this->field16_0x40)._s_0.wave2start == false) {
    fVar6 = GetDistance((this->field18_0xa4)._s_0.player,"spawn2a",0);
    if (100.0 <= fVar6) {
      fVar6 = GetDistance((this->field18_0xa4)._s_0.player,"spawnalt2a",0);
      if (100.0 <= fVar6) {
        fVar6 = GetDistance((this->field18_0xa4)._s_0.player,"cheat2a",0);
        if (200.0 <= fVar6) {
          fVar6 = GetDistance((this->field18_0xa4)._s_0.player,"cheatalt2a",0);
          if (200.0 <= fVar6) goto LAB_0043dea9;
        }
      }
    }
    iVar5 = BuildObject("hvsat",2,"spawn2b",0);
    (this->field18_0xa4)._s_0.w2u2 = iVar5;
    iVar5 = BuildObject("hvsat",2,"spawnalt2b",0);
    (this->field18_0xa4)._s_0.w2u4 = iVar5;
    Goto((this->field18_0xa4)._s_0.w2u2,"transport3",1);
    Goto((this->field18_0xa4)._s_0.w2u4,"transport4",1);
    SetIndependence((this->field18_0xa4)._s_0.w2u2,1);
    SetIndependence((this->field18_0xa4)._s_0.w2u4,1);
    (this->field16_0x40)._s_0.wave2start = true;
  }
LAB_0043dea9:
  if ((this->field16_0x40)._s_0.wave3start == false) {
    fVar6 = GetDistance((this->field18_0xa4)._s_0.player,"spawn3a",0);
    if (100.0 <= fVar6) {
      fVar6 = GetDistance((this->field18_0xa4)._s_0.player,"spawnalt3a",0);
      if (100.0 <= fVar6) {
        fVar6 = GetDistance((this->field18_0xa4)._s_0.player,"cheat3a",0);
        if (200.0 <= fVar6) {
          fVar6 = GetDistance((this->field18_0xa4)._s_0.player,"cheatalt3a",0);
          if (200.0 <= fVar6) goto LAB_0043dfa1;
        }
      }
    }
    iVar5 = BuildObject("hvsat",2,"spawn3b",0);
    (this->field18_0xa4)._s_0.w3u1 = iVar5;
    iVar5 = BuildObject("hvsat",2,"spawnalt3b",0);
    (this->field18_0xa4)._s_0.w3u3 = iVar5;
    Goto((this->field18_0xa4)._s_0.w3u1,"transport5",1);
    Goto((this->field18_0xa4)._s_0.w3u3,"transport6",1);
    SetIndependence((this->field18_0xa4)._s_0.w3u1,1);
    SetIndependence((this->field18_0xa4)._s_0.w3u3,1);
    (this->field16_0x40)._s_0.wave3start = true;
  }
LAB_0043dfa1:
  fVar6 = Get_Time();
  if (((this->field17_0x6c)._s_0.rand1 < fVar6) && ((this->field16_0x40)._s_0.rand1brk == false)) {
    iVar5 = BuildObject("hvsav",2,"spawnrand",0);
    (this->field18_0xa4)._s_0.rand1a = iVar5;
    Goto(iVar5,"transport7",1);
    SetIndependence((this->field18_0xa4)._s_0.rand1a,1);
    (this->field16_0x40)._s_0.rand1brk = true;
  }
  fVar6 = Get_Time();
  if (((this->field17_0x6c)._s_0.rand2 < fVar6) && ((this->field16_0x40)._s_0.rand2brk == false)) {
    iVar5 = BuildObject("hvsav",2,"spawnrand",0);
    (this->field18_0xa4)._s_0.rand2a = iVar5;
    Goto(iVar5,"transport8",1);
    SetIndependence((this->field18_0xa4)._s_0.rand2a,1);
    (this->field16_0x40)._s_0.rand2brk = true;
  }
  fVar6 = Get_Time();
  if (((this->field17_0x6c)._s_0.rand3 < fVar6) && ((this->field16_0x40)._s_0.rand3brk == false)) {
    iVar5 = BuildObject("hvsav",2,"spawnrand",0);
    (this->field18_0xa4)._s_0.rand3a = iVar5;
    Goto(iVar5,"transport9",1);
    SetIndependence((this->field18_0xa4)._s_0.rand3a,1);
    (this->field16_0x40)._s_0.rand3brk = true;
  }
  if (((this->field16_0x40)._s_0.transdestroyed == true) &&
     ((this->field16_0x40)._s_0.dontgo == false)) {
    fVar6 = GetDistance((this->field18_0xa4)._s_0.player,"dontgo",0);
    if (fVar6 < 50.0) {
      AudioMessage("misn1805.wav");
      (this->field16_0x40)._s_0.dontgo = true;
    }
  }
  if ((this->field16_0x40)._s_0.dontgo == true) {
    fVar6 = GetDistance((this->field18_0xa4)._s_0.player,"dontgo1",0);
    if ((fVar6 < 100.0) && ((this->field16_0x40)._s_0.dg1 == false)) {
      iVar5 = BuildObject("hvsat",2,"dgs1",0);
      (this->field18_0xa4)._s_0.dg1a = iVar5;
      iVar5 = BuildObject("hvsav",2,"spawn1",0);
      (this->field18_0xa4)._s_0.dg1b = iVar5;
      (this->field16_0x40)._s_0.dg1 = true;
    }
    if ((this->field16_0x40)._s_0.dontgo == true) {
      fVar6 = GetDistance((this->field18_0xa4)._s_0.player,"dontgo2",0);
      if ((fVar6 < 100.0) && ((this->field16_0x40)._s_0.dg2 == false)) {
        iVar5 = BuildObject("hvsat",2,"dgs2",0);
        (this->field18_0xa4)._s_0.dg2a = iVar5;
        iVar5 = BuildObject("hvsav",2,"spawn1",0);
        (this->field18_0xa4)._s_0.dg2b = iVar5;
        (this->field16_0x40)._s_0.dg2 = true;
      }
      if ((this->field16_0x40)._s_0.dontgo == true) {
        fVar6 = GetDistance((this->field18_0xa4)._s_0.player,"dontgo3",0);
        if ((fVar6 < 100.0) && ((this->field16_0x40)._s_0.dg3 == false)) {
          iVar5 = BuildObject("hvsat",2,"dgs3",0);
          (this->field18_0xa4)._s_0.dg3a = iVar5;
          iVar5 = BuildObject("hvsav",2,"spawn1",0);
          (this->field18_0xa4)._s_0.dg3b = iVar5;
          (this->field16_0x40)._s_0.dg3 = true;
        }
      }
    }
  }
  bVar4 = IsAlive(&(this->field18_0xa4)._s_0.thrusterone);
  if (!bVar4) {
    bVar4 = IsAlive(&(this->field18_0xa4)._s_0.thrustertwo);
    if (!bVar4) {
      bVar4 = IsAlive(&(this->field18_0xa4)._s_0.thrusterthree);
      if (!bVar4) {
        bVar4 = IsAlive(&(this->field18_0xa4)._s_0.thrusterfour);
        if ((!bVar4) && ((this->field16_0x40)._s_0.transdestroyed == false)) {
          AudioMessage("misn1804.wav");
          (this->field16_0x40)._s_0.transdestroyed = true;
          (this->field16_0x40)._s_0.newobjective = true;
          fVar6 = Get_Time();
          (this->field17_0x6c)._s_0.hurry1 = fVar6 + 60.0;
          fVar6 = Get_Time();
          (this->field17_0x6c)._s_0.hurry2 = fVar6 + 85.0;
          fVar6 = Get_Time();
          (this->field17_0x6c)._s_0.hurry3 = fVar6 + 115.0;
          fVar6 = Get_Time();
          (this->field17_0x6c)._s_0.hurry4 = fVar6 + 140.0;
          (this->field19_0x1a8)._s_0.quake_level = 6;
          StartCockpitTimer(0xb4,0x78,0x1e);
        }
      }
    }
  }
  fVar6 = Get_Time();
  if (((this->field17_0x6c)._s_0.hurry1 < fVar6) && ((this->field16_0x40)._s_0.missionwon == false))
  {
    AudioMessage("misn1809.wav");
    fVar6 = Get_Time();
    (this->field17_0x6c)._s_0.hurry1 = fVar6 + 1e+08;
  }
  fVar6 = Get_Time();
  if (((this->field17_0x6c)._s_0.hurry2 < fVar6) && ((this->field16_0x40)._s_0.missionwon == false))
  {
    AudioMessage("misn1810.wav");
    fVar6 = Get_Time();
    (this->field17_0x6c)._s_0.hurry2 = fVar6 + 1e+08;
  }
  fVar6 = Get_Time();
  if (((this->field17_0x6c)._s_0.hurry3 < fVar6) && ((this->field16_0x40)._s_0.missionwon == false))
  {
    AudioMessage("misn1811.wav");
    fVar6 = Get_Time();
    (this->field17_0x6c)._s_0.hurry3 = fVar6 + 1e+08;
  }
  fVar6 = Get_Time();
  if (((this->field17_0x6c)._s_0.hurry4 < fVar6) && ((this->field16_0x40)._s_0.missionwon == false))
  {
    AudioMessage("misn1812.wav");
    fVar6 = Get_Time();
    (this->field17_0x6c)._s_0.hurry4 = fVar6 + 1e+08;
  }
  if ((this->field16_0x40)._s_0.transportfound == false) {
    fVar6 = GetDistance((this->field18_0xa4)._s_0.player,"transfound",0);
    if (100.0 <= fVar6) {
      fVar6 = GetDistance((this->field18_0xa4)._s_0.enemy,(this->field18_0xa4)._s_0.transport);
      if (200.0 <= fVar6) goto LAB_0043e5c6;
    }
    AudioMessage("misn1816.wav");
    (this->field16_0x40)._s_0.transportfound = true;
    bVar4 = IsAlive((this->field18_0xa4).h_array);
    if (bVar4) {
      SetObjectiveOff((this->field18_0xa4)._s_0.transport);
    }
    bVar4 = IsAlive(&(this->field18_0xa4)._s_0.thrusterone);
    if (bVar4) {
      SetObjectiveOn((this->field18_0xa4)._s_0.thrusterone);
    }
    bVar4 = IsAlive(&(this->field18_0xa4)._s_0.thrustertwo);
    if (bVar4) {
      SetObjectiveOn((this->field18_0xa4)._s_0.thrustertwo);
    }
    bVar4 = IsAlive(&(this->field18_0xa4)._s_0.thrusterthree);
    if (bVar4) {
      SetObjectiveOn((this->field18_0xa4)._s_0.thrusterthree);
    }
    bVar4 = IsAlive(&(this->field18_0xa4)._s_0.thrusterfour);
    if (bVar4) {
      SetObjectiveOn((this->field18_0xa4)._s_0.thrusterfour);
    }
    fVar6 = Get_Time();
    (this->field16_0x40)._s_0.newobjective = true;
    (this->field17_0x6c)._s_0.savattack = fVar6 + 180.0;
    if ((this->field16_0x40)._s_0.wave1start == false) {
      iVar5 = BuildObject("hvsat",2,"spawn1b",0);
      (this->field18_0xa4)._s_0.w1u1 = iVar5;
      iVar5 = BuildObject("hvsat",2,"spawnalt1b",0);
      (this->field18_0xa4)._s_0.w1u3 = iVar5;
      Goto((this->field18_0xa4)._s_0.w1u1,"transport1",1);
      Goto((this->field18_0xa4)._s_0.w1u3,"transport2",1);
      SetIndependence((this->field18_0xa4)._s_0.w1u1,1);
      SetIndependence((this->field18_0xa4)._s_0.w1u3,1);
      (this->field16_0x40)._s_0.wave1start = true;
    }
    if ((this->field16_0x40)._s_0.wave2start == false) {
      iVar5 = BuildObject("hvsat",2,"spawn2b",0);
      (this->field18_0xa4)._s_0.w2u2 = iVar5;
      iVar5 = BuildObject("hvsat",2,"spawnalt2b",0);
      (this->field18_0xa4)._s_0.w2u4 = iVar5;
      Goto((this->field18_0xa4)._s_0.w2u2,"transport3",1);
      Goto((this->field18_0xa4)._s_0.w2u4,"transport4",1);
      SetIndependence((this->field18_0xa4)._s_0.w2u2,1);
      SetIndependence((this->field18_0xa4)._s_0.w2u4,1);
      (this->field16_0x40)._s_0.wave2start = true;
    }
    if ((this->field16_0x40)._s_0.wave3start == false) {
      iVar5 = BuildObject("hvsat",2,"spawn3b",0);
      (this->field18_0xa4)._s_0.w3u1 = iVar5;
      iVar5 = BuildObject("hvsat",2,"spawnalt3b",0);
      (this->field18_0xa4)._s_0.w3u3 = iVar5;
      Goto((this->field18_0xa4)._s_0.w3u1,"transport5",1);
      Goto((this->field18_0xa4)._s_0.w3u3,"transport6",1);
      SetIndependence((this->field18_0xa4)._s_0.w3u1,1);
      SetIndependence((this->field18_0xa4)._s_0.w3u3,1);
      (this->field16_0x40)._s_0.wave3start = true;
    }
  }
LAB_0043e5c6:
  if (((this->field16_0x40)._s_0.transdestroyed == false) &&
     ((this->field16_0x40)._s_0.savwaves == false)) {
    fVar6 = Get_Time();
    if ((this->field17_0x6c)._s_0.savattack < fVar6) {
      (this->field16_0x40)._s_0.savwaves = true;
      iVar5 = BuildObject("hvsav",2,"spawnrand",0);
      (this->field18_0xa4)._s_0.fury1 = iVar5;
      iVar5 = BuildObject("hvsav",2,"spawnrand",0);
      (this->field18_0xa4)._s_0.fury2 = iVar5;
      iVar5 = BuildObject("hvsav",2,"spawnrand2",0);
      (this->field18_0xa4)._s_0.fury3 = iVar5;
      iVar5 = BuildObject("hvsav",2,"spawnrand2",0);
      (this->field18_0xa4)._s_0.fury4 = iVar5;
      Attack((this->field18_0xa4)._s_0.fury1,(this->field18_0xa4)._s_0.avrec,1);
      Attack((this->field18_0xa4)._s_0.fury2,(this->field18_0xa4)._s_0.avrec,1);
      Attack((this->field18_0xa4)._s_0.fury3,(this->field18_0xa4)._s_0.avrec,1);
      Attack((this->field18_0xa4)._s_0.fury4,(this->field18_0xa4)._s_0.avrec,1);
    }
  }
  if ((this->field16_0x40)._s_0.savwaves == true) {
    bVar4 = IsAlive(&(this->field18_0xa4)._s_0.fury1);
    if (!bVar4) {
      bVar4 = IsAlive(&(this->field18_0xa4)._s_0.fury2);
      if (!bVar4) {
        bVar4 = IsAlive(&(this->field18_0xa4)._s_0.fury3);
        if (!bVar4) {
          bVar4 = IsAlive(&(this->field18_0xa4)._s_0.fury4);
          if (!bVar4) {
            iVar5 = BuildObject("hvsav",2,"spawnrand",0);
            (this->field18_0xa4)._s_0.fury1 = iVar5;
            iVar5 = BuildObject("hvsav",2,"spawnrand",0);
            (this->field18_0xa4)._s_0.fury2 = iVar5;
            iVar5 = BuildObject("hvsav",2,"spawnrand2",0);
            (this->field18_0xa4)._s_0.fury3 = iVar5;
            iVar5 = BuildObject("hvsav",2,"spawnrand2",0);
            piVar2 = &(this->field18_0xa4)._s_0.fury4;
            *piVar2 = iVar5;
            Attack((this->field18_0xa4)._s_0.fury1,(this->field18_0xa4)._s_0.avrec,1);
            Attack((this->field18_0xa4)._s_0.fury2,(this->field18_0xa4)._s_0.avrec,1);
            Attack((this->field18_0xa4)._s_0.fury3,(this->field18_0xa4)._s_0.avrec,1);
            Attack(*piVar2,(this->field18_0xa4)._s_0.avrec,1);
          }
        }
      }
    }
  }
  if ((this->field16_0x40)._s_0.transportfound == false) {
    fVar6 = Get_Time();
    if (((this->field17_0x6c)._s_0.gettosavtrans < fVar6) &&
       ((this->field16_0x40)._s_0.fail1 == false)) {
      pcVar7 = "misn18l1.des";
      fVar6 = Get_Time();
      FailMission(fVar6 + 5.0,pcVar7);
      AudioMessage("misn1806.wav");
      (this->field16_0x40)._s_0.fail1 = true;
    }
  }
  if ((this->field16_0x40)._s_0.transdestroyed == true) {
    fVar6 = GetDistance((this->field18_0xa4)._s_0.player,(this->field18_0xa4)._s_0.avrec);
    if (((400.0 < fVar6) && (cockpitTimer.timer < 1)) && ((this->field16_0x40)._s_0.fail2 == false))
    {
      CameraReady();
      pcVar7 = "misn18l2.des";
      fVar6 = Get_Time();
      FailMission(fVar6 + 7.0,pcVar7);
      AudioMessage("misn1807.wav");
      (this->field16_0x40)._s_0.fail2 = true;
      (this->field16_0x40)._s_0.blastoff = true;
    }
  }
  piVar2 = &(this->field18_0xa4)._s_0.avrec;
  bVar4 = IsAlive(piVar2);
  if ((!bVar4) && ((this->field16_0x40)._s_0.fail3 == false)) {
    pcVar7 = "misn18l3.des";
    (this->field16_0x40)._s_0.fail3 = true;
    fVar6 = Get_Time();
    FailMission(fVar6 + 7.0,pcVar7);
    AudioMessage("misn1704.wav");
  }
  if ((this->field16_0x40)._s_0.blastoff == true) {
    iVar5 = (this->field18_0xa4)._s_0.player;
    piVar3 = &(this->field19_0x1a8)._s_0.y;
    *piVar3 = *piVar3 + 500;
    CameraObject(iVar5,1,*piVar3,1000,iVar5);
  }
  fVar6 = GetDistance((this->field18_0xa4)._s_0.player,"return1",0);
  if (100.0 <= fVar6) {
    fVar6 = GetDistance((this->field18_0xa4)._s_0.player,"return2",0);
    if (100.0 <= fVar6) goto LAB_0043e90f;
  }
  if (((this->field16_0x40)._s_0.returnwave == false) &&
     ((this->field16_0x40)._s_0.transdestroyed == true)) {
    iVar5 = BuildObject("hvsat",2,"spawnreturn",0);
    (this->field18_0xa4)._s_0.sav1 = iVar5;
    (this->field16_0x40)._s_0.returnwave = true;
  }
LAB_0043e90f:
  fVar6 = GetDistance((this->field18_0xa4)._s_0.player,*piVar2);
  if (((fVar6 < 200.0) && ((this->field16_0x40)._s_0.transdestroyed == true)) &&
     ((this->field16_0x40)._s_0.missionwon == false)) {
    AudioMessage("misn1808.wav");
    pcVar7 = (char *)0x0;
    fVar6 = Get_Time();
    SucceedMission(fVar6 + 12.0,pcVar7);
    (this->field16_0x40)._s_0.fail2 = true;
    (this->field16_0x40)._s_0.missionwon = true;
    (this->field16_0x40)._s_0.newobjective = true;
  }
  bVar4 = IsAlive(&(this->field18_0xa4)._s_0.thrusterone);
  if ((!bVar4) && ((this->field16_0x40)._s_0.thrust1 == false)) {
    piVar2 = &(this->field19_0x1a8)._s_0.z;
    *piVar2 = *piVar2 + 1;
    (this->field16_0x40)._s_0.thrust1 = true;
  }
  bVar4 = IsAlive(&(this->field18_0xa4)._s_0.thrustertwo);
  if ((!bVar4) && ((this->field16_0x40)._s_0.thrust2 == false)) {
    piVar2 = &(this->field19_0x1a8)._s_0.z;
    *piVar2 = *piVar2 + 1;
    (this->field16_0x40)._s_0.thrust2 = true;
  }
  bVar4 = IsAlive(&(this->field18_0xa4)._s_0.thrusterthree);
  if ((!bVar4) && ((this->field16_0x40)._s_0.thrust3 == false)) {
    piVar2 = &(this->field19_0x1a8)._s_0.z;
    *piVar2 = *piVar2 + 1;
    (this->field16_0x40)._s_0.thrust3 = true;
  }
  bVar4 = IsAlive(&(this->field18_0xa4)._s_0.thrusterfour);
  if ((!bVar4) && ((this->field16_0x40)._s_0.thrust4 == false)) {
    piVar2 = &(this->field19_0x1a8)._s_0.z;
    *piVar2 = *piVar2 + 1;
    (this->field16_0x40)._s_0.thrust4 = true;
  }
  if (((this->field19_0x1a8)._s_0.z == 1) && ((this->field16_0x40)._s_0.message1 == false)) {
    AudioMessage("misn1813.wav");
    (this->field16_0x40)._s_0.message1 = true;
  }
  if (((this->field19_0x1a8)._s_0.z == 2) && ((this->field16_0x40)._s_0.message2 == false)) {
    AudioMessage("misn1814.wav");
    (this->field16_0x40)._s_0.message2 = true;
  }
  if (((this->field19_0x1a8)._s_0.z == 3) && ((this->field16_0x40)._s_0.message3 == false)) {
    AudioMessage("misn1815.wav");
    (this->field16_0x40)._s_0.message3 = true;
  }
  return;
}
