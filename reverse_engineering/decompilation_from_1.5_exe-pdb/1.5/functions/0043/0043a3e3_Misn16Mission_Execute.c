/*
 * Entry: 0043a3e3
 * Name: Misn16Mission::Execute
 * Namespace: Misn16Mission
 * Signature: void Execute(Misn16Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn16Mission::Execute(Misn16Mission *this)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  float fVar6;
  char *pcVar7;
  int local_c;
  int local_8;
  int local_4;
  
  local_c = GetPlayerHandle();
  if ((this->field16_0x40)._s_0.start_done == false) {
    iVar3 = AudioMessage("misn1601.wav");
    (this->field18_0x70)._s_0.audmsg1 = iVar3;
    iVar3 = AudioMessage("misn1602.wav");
    (this->field18_0x70)._s_0.audmsg2 = iVar3;
    iVar3 = GetHandle("avrecy0_recycler");
    (this->field18_0x70)._s_0.recy = iVar3;
    fVar6 = Get_Time();
    (this->field17_0x48)._s_0.next_reinforcement = fVar6 + 120.0;
    uVar4 = rand();
    uVar4 = uVar4 & 0x80000001;
    if ((int)uVar4 < 0) {
      uVar4 = (uVar4 - 1 | 0xfffffffe) + 1;
    }
    (this->field19_0xc8)._s_0.rtype = uVar4 + 1;
    (this->field16_0x40)._s_0.start_done = true;
    iVar3 = GetHandle("alien_hq");
    (this->field18_0x70)._s_0.base1 = iVar3;
    iVar3 = GetHandle("alien_hangar");
    (this->field18_0x70)._s_0.base2 = iVar3;
    SetScrap(1,0x32);
    SetAIP("misn16.aip",2);
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misn1601.otf",DisplayInterface::colorWhite,8.0);
    fVar6 = Get_Time();
    (this->field17_0x48)._s_0.alien_wave = fVar6 + 60.0;
    fVar6 = Get_Time();
    (this->field17_0x48)._s_0.alien_wave1 = fVar6 + 90.0;
    iVar3 = GetHandle("apcamr12_camerapod");
    (this->field18_0x70)._s_0.cam1 = iVar3;
    iVar3 = GetHandle("apcamr15_camerapod");
    (this->field18_0x70)._s_0.cam2 = iVar3;
    iVar3 = GetHandle("apcamr13_camerapod");
    (this->field18_0x70)._s_0.cam3 = iVar3;
    iVar3 = GetHandle("apcamr11_camerapod");
    (this->field18_0x70)._s_0.cam4 = iVar3;
    iVar3 = (this->field18_0x70)._s_0.cam1;
    if (iVar3 != 0) {
      SetObjectiveName(iVar3,"NW Geyser");
    }
    iVar3 = (this->field18_0x70)._s_0.cam2;
    if (iVar3 != 0) {
      SetObjectiveName(iVar3,"Foothill Geysers");
    }
    iVar3 = (this->field18_0x70)._s_0.cam3;
    if (iVar3 != 0) {
      SetObjectiveName(iVar3,"Geyser Site");
    }
    iVar3 = (this->field18_0x70)._s_0.cam4;
    if (iVar3 != 0) {
      SetObjectiveName(iVar3,"Alien HQ");
    }
    iVar3 = GetHandle("sbtowe0_turret");
    (this->field18_0x70)._s_0.tow1 = iVar3;
    iVar3 = GetHandle("sbtowe1_turret");
    (this->field18_0x70)._s_0.tow2 = iVar3;
    iVar3 = GetHandle("sbtowe2_turret");
    (this->field18_0x70)._s_0.tow3 = iVar3;
    iVar3 = GetHandle("sbtowe3_turret");
    (this->field18_0x70)._s_0.tow4 = iVar3;
    iVar3 = GetHandle("hvsat0_wingman");
    (this->field18_0x70)._s_0.sat1 = iVar3;
    iVar3 = GetHandle("hvsat1_wingman");
    (this->field18_0x70)._s_0.sat2 = iVar3;
    iVar3 = GetHandle("hvsat2_wingman");
    (this->field18_0x70)._s_0.sat3 = iVar3;
    iVar3 = (this->field18_0x70)._s_0.sat1;
    if (iVar3 != 0) {
      Defend(iVar3,1);
    }
    iVar3 = (this->field18_0x70)._s_0.sat2;
    if (iVar3 != 0) {
      Defend(iVar3,1);
    }
    iVar3 = (this->field18_0x70)._s_0.sat3;
    if (iVar3 != 0) {
      Defend(iVar3,1);
    }
    iVar3 = GetHandle("avmuf26_factory");
    (this->field18_0x70)._s_0.muf = iVar3;
    (this->field16_0x40)._s_0.camera1 = true;
    fVar6 = Get_Time();
    (this->field17_0x48)._s_0.cam_time1 = fVar6 + 20.0;
    CameraReady();
  }
  if ((((this->field16_0x40)._s_0.camera1 != false) &&
      (CameraPath("camera_path1",4000,500,(this->field18_0x70)._s_0.base2),
      (this->field16_0x40)._s_0.camera1 != false)) &&
     ((bVar2 = CameraCancelled(), bVar2 ||
      ((fVar6 = Get_Time(), (this->field17_0x48)._s_0.cam_time1 < fVar6 ||
       (bVar2 = IsAudioMessageDone((this->field18_0x70)._s_0.audmsg2), bVar2)))))) {
    (this->field16_0x40)._s_0.camera1 = false;
    CameraFinish();
  }
  fVar6 = Get_Time();
  if (fVar6 <= (this->field17_0x48)._s_0.next_reinforcement) goto LAB_0043a8a4;
  piVar1 = &(this->field19_0xc8)._s_0.rcount;
  *piVar1 = *piVar1 + 1;
  if (9 < *piVar1) goto LAB_0043a8a4;
  iVar3 = (this->field19_0xc8)._s_0.rtype;
  if (iVar3 == 1) {
    AudioMessage("misn1603.wav");
    BuildObject("svfigh",1,"starta",0);
    pcVar5 = "svhaul";
LAB_0043a858:
    BuildObject(pcVar5,1,"starta2",0);
    pcVar7 = "starta3";
LAB_0043a86d:
    BuildObject(pcVar5,1,pcVar7,0);
  }
  else {
    if (iVar3 == 2) {
      AudioMessage("misn1604.wav");
      BuildObject("svscav",1,"startb",0);
      BuildObject("svscav",1,"startb2",0);
      pcVar7 = "startb3";
LAB_0043a7ff:
      pcVar5 = "svfigh";
      goto LAB_0043a86d;
    }
    if (iVar3 == 3) {
      AudioMessage("misn1605.wav");
      BuildObject("svscav",1,"starta",0);
      BuildObject("svturr",1,"starta2",0);
      pcVar7 = "starta3";
      goto LAB_0043a7ff;
    }
    if (iVar3 != 4) {
      pcVar5 = "svtank";
      if (iVar3 == 5) {
        AudioMessage("misn1607.wav");
        BuildObject("svfigh",1,"starta",0);
        BuildObject("svfigh",1,"starta2",0);
        BuildObject("svtank",1,"starta3",0);
      }
      else if (iVar3 != 6) {
        if (iVar3 == 7) {
          AudioMessage("misn1608.wav");
          pcVar5 = "svwalk";
          BuildObject("svwalk",1,"starta",0);
          goto LAB_0043a858;
        }
        goto LAB_0043a875;
      }
      AudioMessage("misn1607.wav");
      BuildObject("svtank",1,"startb",0);
      BuildObject("svtank",1,"startb2",0);
      pcVar7 = "startb3";
      goto LAB_0043a86d;
    }
    AudioMessage("misn1606.wav");
    BuildObject("svfigh",1,"startb",0);
    BuildObject("svfigh",1,"startb2",0);
  }
LAB_0043a875:
  iVar3 = rand();
  (this->field19_0xc8)._s_0.rtype = iVar3 % 7 + 1;
  fVar6 = Get_Time();
  (this->field17_0x48)._s_0.next_reinforcement = fVar6 + 180.0;
  fVar6 = Get_Time();
  (this->field17_0x48)._s_0.start_time = fVar6 + 2.0;
LAB_0043a8a4:
  fVar6 = Get_Time();
  if ((this->field17_0x48)._s_0.start_time < fVar6) {
    bVar2 = IsAlive(&local_c);
    if (bVar2) {
      local_8 = GetNearestEnemy(local_c);
    }
    fVar6 = GetDistance(local_c,local_8);
    if (150.0 < fVar6) {
      (this->field16_0x40)._s_0.rcam = true;
      fVar6 = Get_Time();
      (this->field17_0x48)._s_0.rcam_time = fVar6 + 4.0;
      CameraReady();
    }
    (this->field17_0x48)._s_0.start_time = 99999.0;
  }
  if ((((this->field16_0x40)._s_0.rcam != false) &&
      (iVar3 = (this->field18_0x70)._s_0.newbie, CameraObject(iVar3,0,2000,3000,iVar3),
      (this->field16_0x40)._s_0.rcam != false)) &&
     ((fVar6 = Get_Time(), (this->field17_0x48)._s_0.rcam_time < fVar6 ||
      (bVar2 = CameraCancelled(), bVar2)))) {
    (this->field16_0x40)._s_0.rcam = false;
    CameraFinish();
    (this->field17_0x48)._s_0.rcam_time = 99999.0;
  }
  fVar6 = Get_Time();
  if ((this->field17_0x48)._s_0.alien_wave < fVar6) {
    BuildObject("hvsav",2,(this->field18_0x70)._s_0.base2);
    fVar6 = Get_Time();
    (this->field17_0x48)._s_0.alien_wave = fVar6 + (this->field17_0x48)._s_0.wave_gap;
    if (60.0 < (this->field17_0x48)._s_0.wave_gap) {
      (this->field17_0x48)._s_0.wave_gap = (this->field17_0x48)._s_0.wave_gap - 5.0;
    }
  }
  fVar6 = Get_Time();
  if ((this->field17_0x48)._s_0.alien_wave1 < fVar6) {
    iVar3 = BuildObject("hvsat",2,"sat1",0);
    Goto(iVar3,"strike1",1);
    iVar3 = BuildObject("hvsat",2,"sat2",0);
    Goto(iVar3,"strike2",1);
    (this->field17_0x48)._s_0.alien_wave1 = (this->field17_0x48)._s_0.alien_wave + 90.0;
  }
  if (((((this->field16_0x40)._s_0.won == false) && ((this->field16_0x40)._s_0.lost == false)) &&
      ((this->field16_0x40)._s_0.counter == false)) &&
     ((((bVar2 = IsAlive(&(this->field18_0x70)._s_0.tow1), !bVar2 &&
        (bVar2 = IsAlive(&(this->field18_0x70)._s_0.tow2), !bVar2)) ||
       ((bVar2 = IsAlive(&(this->field18_0x70)._s_0.tow3), !bVar2 &&
        (bVar2 = IsAlive(&(this->field18_0x70)._s_0.tow4), !bVar2)))) ||
      ((bVar2 = IsAlive((this->field18_0x70).h_array), !bVar2 ||
       (bVar2 = IsAlive(&(this->field18_0x70)._s_0.base2), !bVar2)))))) {
    local_8 = BuildObject("hvsav",2,(this->field18_0x70)._s_0.base2);
    local_4 = BuildObject("hvsav",2,(this->field18_0x70)._s_0.base2);
    piVar1 = &(this->field18_0x70)._s_0.muf;
    Attack(local_8,*piVar1,1);
    Attack(local_4,*piVar1,1);
    (this->field16_0x40)._s_0.counter = true;
    fVar6 = Get_Time();
    (this->field17_0x48)._s_0.counter_strike2 = fVar6 + 120.0;
  }
  fVar6 = Get_Time();
  if ((this->field17_0x48)._s_0.counter_strike2 < fVar6) {
    iVar3 = BuildObject("hvsav",2,(this->field18_0x70)._s_0.base2);
    local_4 = BuildObject("hvsav",2,(this->field18_0x70)._s_0.base2);
    piVar1 = &(this->field18_0x70)._s_0.recy;
    Attack(iVar3,*piVar1,1);
    Attack(local_4,*piVar1,1);
    (this->field17_0x48)._s_0.counter_strike2 = 99999.0;
  }
  if ((((this->field16_0x40)._s_0.won == false) &&
      (bVar2 = IsAlive((this->field18_0x70).h_array), !bVar2)) &&
     (bVar2 = IsAlive(&(this->field18_0x70)._s_0.base2), !bVar2)) {
    AudioMessage("misn1613.wav");
    (this->field16_0x40)._s_0.won = true;
    pcVar5 = "misn16w1.des";
    fVar6 = Get_Time();
    SucceedMission(fVar6 + 15.0,pcVar5);
  }
  if (((this->field16_0x40)._s_0.lost == false) &&
     (bVar2 = IsAlive(&(this->field18_0x70)._s_0.recy), !bVar2)) {
    AudioMessage("misn1612.wav");
    (this->field16_0x40)._s_0.lost = true;
    pcVar5 = "misn16l1.des";
    fVar6 = Get_Time();
    FailMission(fVar6 + 15.0,pcVar5);
  }
  return;
}
