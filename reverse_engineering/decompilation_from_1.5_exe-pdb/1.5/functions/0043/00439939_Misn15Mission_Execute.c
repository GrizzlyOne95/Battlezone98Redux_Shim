/*
 * Entry: 00439939
 * Name: Misn15Mission::Execute
 * Namespace: Misn15Mission
 * Signature: void Execute(Misn15Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn15Mission::Execute(Misn15Mission *this)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  AiCommand AVar5;
  int *piVar6;
  float fVar7;
  char *pcVar8;
  int local_4;
  
  iVar2 = GetPlayerHandle();
  (this->field18_0x80)._s_0.player = iVar2;
  if ((this->field16_0x40)._s_0.start_done == false) {
    AddScrap(1,10);
    showStuff(this);
    iVar2 = GetHandle("misn15b");
    (this->field16_0x40)._s_0.misn15b = iVar2 != 0;
    iVar2 = GetHandle("ubtart0_i76building");
    (this->field18_0x80)._s_0.tart = iVar2;
    iVar2 = GetHandle("avrecy0_recycler");
    (this->field18_0x80)._s_0.recy = iVar2;
    iVar2 = GetHandle("apcamr0_camerapod");
    (this->field18_0x80)._s_0.cam1 = iVar2;
    iVar2 = GetHandle("apcamr1_camerapod");
    (this->field18_0x80)._s_0.cam2 = iVar2;
    iVar2 = GetHandle("apcamr2_camerapod");
    (this->field18_0x80)._s_0.cam3 = iVar2;
    iVar2 = GetHandle("apcamr3_camerapod");
    (this->field18_0x80)._s_0.cam4 = iVar2;
    iVar2 = GetHandle("apcamr4_camerapod");
    (this->field18_0x80)._s_0.cam5 = iVar2;
    iVar2 = GetHandle("apcamr5_camerapod");
    (this->field18_0x80)._s_0.cam6 = iVar2;
    iVar2 = GetHandle("svtank0_wingman");
    (this->field18_0x80)._s_0.tank1 = iVar2;
    iVar2 = GetHandle("svtank1_wingman");
    (this->field18_0x80)._s_0.tank2 = iVar2;
    iVar2 = GetHandle("svapc0_apc");
    (this->field18_0x80)._s_0.hov1 = iVar2;
    iVar2 = GetHandle("eggeizr15_geyser");
    (this->field18_0x80)._s_0.goal = iVar2;
    fVar7 = Get_Time();
    (this->field17_0x50)._s_0.rendezvous1 = fVar7 + 180.0;
    fVar7 = Get_Time();
    (this->field17_0x50)._s_0.rendezvous2 = fVar7 + 240.0;
    fVar7 = Get_Time();
    (this->field17_0x50)._s_0.deny_time1 = fVar7 + 300.0;
    fVar7 = Get_Time();
    (this->field17_0x50)._s_0.deny_time2 = fVar7 + 400.0;
    fVar7 = Get_Time();
    iVar2 = (this->field18_0x80)._s_0.cam1;
    (this->field17_0x50)._s_0.check_time = fVar7 + 5.0;
    SetObjectiveName(iVar2,"Geyser Site");
    SetObjectiveName((this->field18_0x80)._s_0.cam2,"NW Geyser");
    SetObjectiveName((this->field18_0x80)._s_0.cam3,"NE Geyser");
    SetObjectiveName((this->field18_0x80)._s_0.cam4,"Geyser Site");
    SetObjectiveName((this->field18_0x80)._s_0.cam5,"Supply");
    SetObjectiveName((this->field18_0x80)._s_0.cam6,"Nav Beta");
    Goto((this->field18_0x80)._s_0.tank1,"tank_path",0);
    Goto((this->field18_0x80)._s_0.tank2,"tank_path",0);
    Goto((this->field18_0x80)._s_0.hov1,"tank_path",0);
    iVar2 = AudioMessage("misn1501.wav");
    (this->field18_0x80)._s_0.audmsg = iVar2;
    fVar7 = Get_Time();
    (this->field17_0x50)._s_0.second_message = fVar7 + 2.0;
    fVar7 = Get_Time();
    (this->field18_0x80)._s_0.scav_du_jour = (this->field18_0x80)._s_0.recy;
    iVar2 = (this->field18_0x80)._s_0.cam6;
    (this->field17_0x50)._s_0.sav_timer = fVar7 + 120.0;
    (this->field16_0x40)._s_0.start_done = true;
    (this->field17_0x50)._s_0.misl_time = 40.0;
    if (iVar2 != 0) {
      SetUserTarget(iVar2);
    }
  }
  bVar1 = IsAudioMessageDone((this->field18_0x80)._s_0.audmsg);
  if (bVar1) {
    fVar7 = Get_Time();
    if ((this->field17_0x50)._s_0.second_message < fVar7) {
      AudioMessage("misn1502.wav");
      CameraReady();
      fVar7 = Get_Time();
      (this->field16_0x40)._s_0.camera1 = true;
      (this->field17_0x50)._s_0.camera_time = fVar7 + 8.0;
      (this->field17_0x50)._s_0.second_message = 99999.0;
    }
  }
  if ((this->field16_0x40)._s_0.camera1 != false) {
    iVar2 = (this->field18_0x80)._s_0.tank1;
    CameraObject(iVar2,800,600,0x4b0,iVar2);
    if ((this->field16_0x40)._s_0.camera1 != false) {
      fVar7 = Get_Time();
      if (fVar7 <= (this->field17_0x50)._s_0.camera_time) {
        bVar1 = CameraCancelled();
        if (!bVar1) goto LAB_00439c0f;
      }
      (this->field16_0x40)._s_0.camera1 = false;
      CameraFinish();
    }
  }
LAB_00439c0f:
  if ((this->field16_0x40)._s_0.cca_here == false) {
    fVar7 = GetDistance((this->field18_0x80)._s_0.cam6,(this->field18_0x80)._s_0.tank1);
    if (100.0 <= fVar7) {
      fVar7 = GetDistance((this->field18_0x80)._s_0.cam4,(this->field18_0x80)._s_0.tank1);
      if (100.0 <= fVar7) goto LAB_00439c6a;
    }
    (this->field16_0x40)._s_0.cca_here = true;
    AudioMessage("misn1503.wav");
    showStuff(this);
  }
LAB_00439c6a:
  if ((this->field16_0x40)._s_0.found_group1 == false) {
    fVar7 = Get_Time();
    if ((this->field17_0x50)._s_0.rendezvous1 < fVar7) {
      SetUserTarget((this->field18_0x80)._s_0.cam2);
      AudioMessage("misn1511.wav");
      (this->field17_0x50)._s_0.rendezvous1 = 99999.0;
    }
    if ((this->field16_0x40)._s_0.found_group1 == false) {
      fVar7 = GetDistance((this->field18_0x80)._s_0.cam2,(this->field18_0x80)._s_0.player);
      if (fVar7 < 150.0) {
        AudioMessage("misn1518.wav");
        iVar2 = BuildObject("avscav",1,"scav3here",0);
        (this->field18_0x80)._s_0.scavcam = iVar2;
        BuildObject("avapc",1,"mufhere",0);
        BuildObject("avturr",1,"turhere",0);
        (this->field16_0x40)._s_0.found_group1 = true;
        showStuff(this);
        (this->field16_0x40)._s_0.camera2 = true;
        fVar7 = Get_Time();
        (this->field17_0x50)._s_0.rcam1 = fVar7 + 3.0;
        CameraReady();
      }
    }
  }
  if ((this->field16_0x40)._s_0.camera2 != false) {
    CameraPath("rescue_cam1",1000,0,(this->field18_0x80)._s_0.scavcam);
  }
  if ((this->field16_0x40)._s_0.found_group1 != false) {
    fVar7 = Get_Time();
    if ((this->field17_0x50)._s_0.rcam1 < fVar7) {
      (this->field16_0x40)._s_0.camera2 = false;
      (this->field17_0x50)._s_0.rcam1 = 99999.0;
      CameraFinish();
    }
  }
  if ((this->field16_0x40)._s_0.tartarus == false) {
    fVar7 = GetDistance((this->field18_0x80)._s_0.player,(this->field18_0x80)._s_0.tart);
    if (fVar7 < 150.0) {
      (this->field16_0x40)._s_0.tartarus = true;
      AudioMessage("misn1513.wav");
      AudioMessage("misn1514.wav");
    }
  }
  fVar7 = Get_Time();
  if (((this->field17_0x50)._s_0.sav_timer < fVar7) && ((this->field19_0x288)._s_0.savcount < 0x32))
  {
    uVar3 = rand();
    uVar3 = uVar3 & 0x80000001;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
    }
    if (uVar3 == 1) {
      pcVar8 = "alien1";
    }
    else {
      pcVar8 = "alien2";
    }
    iVar4 = BuildObject("hvsav",2,pcVar8,0);
    Attack(iVar4,(this->field18_0x80)._s_0.scav_du_jour,1);
    fVar7 = Get_Time();
    iVar2 = (this->field19_0x288)._s_0.savcount;
    (this->field17_0x50)._s_0.sav_timer = fVar7 + 240.0;
    *(int *)((int)&this->field18_0x80 + iVar2 * 4 + 0x74) = iVar4;
    (this->field19_0x288)._s_0.savcount = (this->field19_0x288)._s_0.savcount + 1;
  }
  fVar7 = Get_Time();
  if ((this->field17_0x50)._s_0.check_time < fVar7) {
    local_4 = 0;
    if (0 < (this->field19_0x288)._s_0.savcount) {
      piVar6 = (this->field18_0x80)._s_0.savlist;
      do {
        bVar1 = IsAlive(piVar6);
        if (bVar1) {
          AVar5 = GetCurrentCommand(*piVar6);
          if (AVar5 == CMD_NONE) {
            Goto(*piVar6,"alien_path",1);
          }
        }
        local_4 = local_4 + 1;
        piVar6 = piVar6 + 1;
      } while (local_4 < (this->field19_0x288)._s_0.savcount);
    }
    fVar7 = Get_Time();
    (this->field17_0x50)._s_0.check_time = fVar7 + 5.0;
  }
  if ((this->field16_0x40)._s_0.misn15b != false) {
    fVar7 = Get_Time();
    if ((this->field17_0x50)._s_0.deny_time1 < fVar7) {
      iVar2 = BuildObject("hvsat",2,"alien1",0);
      (this->field18_0x80)._s_0.sat1 = iVar2;
      iVar2 = BuildObject("hvsat",2,"alien1",0);
      (this->field18_0x80)._s_0.sat2 = iVar2;
      Goto((this->field18_0x80)._s_0.sat1,"deny1",1);
      Goto((this->field18_0x80)._s_0.sat2,"deny1",1);
      (this->field17_0x50)._s_0.deny_time1 = 99999.0;
    }
    if ((this->field16_0x40)._s_0.misn15b != false) {
      fVar7 = Get_Time();
      if ((this->field17_0x50)._s_0.deny_time2 < fVar7) {
        iVar2 = BuildObject("hvsat",2,"alien2",0);
        (this->field18_0x80)._s_0.sat1 = iVar2;
        iVar2 = BuildObject("hvsat",2,"alien2",0);
        (this->field18_0x80)._s_0.sat2 = iVar2;
        Goto((this->field18_0x80)._s_0.sat1,"deny2",1);
        Goto((this->field18_0x80)._s_0.sat2,"deny2",1);
        (this->field17_0x50)._s_0.deny_time2 = 99999.0;
      }
    }
  }
  if ((this->field16_0x40)._s_0.lost == false) {
    bVar1 = IsAlive(&(this->field18_0x80)._s_0.recy);
    if (!bVar1) {
      AudioMessage("misn1414.wav");
      (this->field16_0x40)._s_0.lost = true;
      pcVar8 = "misn15l1.des";
      fVar7 = Get_Time();
      FailMission(fVar7 + 10.0,pcVar8);
    }
  }
  if ((1 < (this->field19_0x288)._s_0.silocount) && ((this->field16_0x40)._s_0.silo_built == false))
  {
    (this->field16_0x40)._s_0.silo_built = true;
    showStuff(this);
  }
  if ((this->field16_0x40)._s_0.got_dough == false) {
    iVar2 = GetScrap(1);
    if (0x4a < iVar2) {
      InfoDisplay::ClearObjectives(&infoDisplay);
      InfoDisplay::AddObjective(&infoDisplay,"misn1501.otf",DisplayInterface::colorGreen,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn1502.otf",DisplayInterface::colorGreen,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn1503.otf",DisplayInterface::colorGreen,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn1504.otf",DisplayInterface::colorGreen,8.0);
      (this->field16_0x40)._s_0.got_dough = true;
      AudioMessage("misn1510.wav");
      pcVar8 = "misn15w1.des";
      fVar7 = Get_Time();
      SucceedMission(fVar7 + 10.0,pcVar8);
    }
  }
  return;
}
