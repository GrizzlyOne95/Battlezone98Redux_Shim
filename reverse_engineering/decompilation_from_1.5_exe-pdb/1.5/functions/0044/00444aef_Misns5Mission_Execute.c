/*
 * Entry: 00444aef
 * Name: Misns5Mission::Execute
 * Namespace: Misns5Mission
 * Signature: void Execute(Misns5Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns5Mission::Execute(Misns5Mission *this)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  float fVar5;
  char *pcVar6;
  char *pcVar7;
  
  if ((this->field16_0x40)._s_0.start_done == false) {
    iVar3 = GetHandle("svrecy0_recycler");
    (this->field18_0x68)._s_0.recy = iVar3;
    AddScrap(1,10);
    (this->field16_0x40)._s_0.camera1 = true;
    fVar5 = Get_Time();
    (this->field17_0x50)._s_0.camera_time = fVar5 + 17.0;
    fVar5 = Get_Time();
    (this->field16_0x40)._s_0.start_done = true;
    (this->field17_0x50)._s_0.apc_wave = fVar5 + 70.0;
    iVar3 = GetHandle("sbhang0_repairdepot");
    (this->field18_0x68)._s_0.t4 = iVar3;
    iVar3 = BuildObject("avartl",2,"spawn1",0);
    (this->field18_0x68)._s_0.a1 = iVar3;
    iVar3 = BuildObject("avartl",2,"spawn2",0);
    (this->field18_0x68)._s_0.a2 = iVar3;
    CameraReady();
    iVar3 = AudioMessage("misns501.wav");
    (this->field19_0xa8)._s_0.aud = iVar3;
  }
  if ((this->field16_0x40)._s_0.camera1 != false) {
    CameraPath("campath",5000,0x9c4,(this->field18_0x68)._s_0.t4);
    bVar2 = IsAudioMessageDone((this->field19_0xa8)._s_0.aud);
    if ((bVar2) && ((this->field16_0x40)._s_0.second_message == false)) {
      iVar3 = AudioMessage("misns503.wav");
      (this->field19_0xa8)._s_0.aud = iVar3;
      (this->field16_0x40)._s_0.second_message = true;
    }
    bVar2 = CameraCancelled();
    if ((bVar2) || (bVar2 = IsAudioMessageDone((this->field19_0xa8)._s_0.aud), bVar2)) {
      fVar5 = Get_Time();
      (this->field17_0x50)._s_0.chaff = fVar5 + 180.0;
      iVar3 = GetHandle("sblpow2_powerplant");
      (this->field18_0x68)._s_0.t1 = iVar3;
      iVar3 = GetHandle("sblpow3_powerplant");
      (this->field18_0x68)._s_0.t2 = iVar3;
      iVar3 = GetHandle("sblpow4_powerplant");
      (this->field18_0x68)._s_0.t3 = iVar3;
      iVar3 = GetHandle("svrecy0_recycler");
      (this->field18_0x68)._s_0.recy = iVar3;
      iVar3 = GetHandle("svmuf0_factory");
      (this->field18_0x68)._s_0.muf = iVar3;
      piVar1 = &(this->field18_0x68)._s_0.geyser1;
      iVar3 = GetHandle("eggeizr11_geyser");
      *piVar1 = iVar3;
      iVar3 = GetHandle("eggeizr12_geyser");
      (this->field18_0x68)._s_0.geyser2 = iVar3;
      Goto((this->field18_0x68)._s_0.recy,*piVar1,1);
      Goto((this->field18_0x68)._s_0.muf,(this->field18_0x68)._s_0.geyser2,1);
      Attack((this->field18_0x68)._s_0.a1,(this->field18_0x68)._s_0.t1,1);
      Attack((this->field18_0x68)._s_0.a2,(this->field18_0x68)._s_0.t2,1);
      fVar5 = Get_Time();
      (this->field17_0x50)._s_0.add_defender = fVar5 + 10.0;
      CameraFinish();
      InfoDisplay::ClearObjectives(&infoDisplay);
      InfoDisplay::AddObjective(&infoDisplay,"misns501.otf",DisplayInterface::colorWhite,8.0);
      StopAudioMessage((this->field19_0xa8)._s_0.aud);
      (this->field16_0x40)._s_0.camera1 = false;
    }
  }
  if ((this->field16_0x40)._s_0.defender != false) {
    if (((this->field16_0x40)._s_0.third_attack == false) &&
       (bVar2 = IsAlive(&(this->field18_0x68)._s_0.t1), !bVar2)) {
      Attack((this->field18_0x68)._s_0.a1,(this->field18_0x68)._s_0.t3,1);
      (this->field16_0x40)._s_0.third_attack = true;
    }
    if ((((this->field16_0x40)._s_0.defender != false) &&
        ((this->field16_0x40)._s_0.fourth_attack == false)) &&
       (bVar2 = IsAlive(&(this->field18_0x68)._s_0.t2), !bVar2)) {
      Attack((this->field18_0x68)._s_0.a2,(this->field18_0x68)._s_0.t4,1);
      (this->field16_0x40)._s_0.fourth_attack = true;
    }
  }
  fVar5 = Get_Time();
  if ((this->field17_0x50)._s_0.add_defender < fVar5) {
    BuildObject("avwalk",2,"spawn3",0);
    (this->field17_0x50)._s_0.add_defender = 99999.0;
    SetPilot(2,0x1e);
    (this->field16_0x40)._s_0.defender = true;
  }
  if ((this->field16_0x40)._s_0.defender != false) {
    if ((((this->field16_0x40)._s_0.art_dead == false) &&
        (bVar2 = IsAlive((this->field18_0x68).h_array), !bVar2)) &&
       (bVar2 = IsAlive(&(this->field18_0x68)._s_0.a2), !bVar2)) {
      AudioMessage("misns504.wav");
      (this->field16_0x40)._s_0.art_dead = true;
    }
    if ((((this->field16_0x40)._s_0.defender != false) &&
        (iVar3 = (this->field18_0x68)._s_0.h1, iVar3 != 0)) &&
       (((this->field16_0x40)._s_0.apc_here == false &&
        (fVar5 = GetDistance(iVar3,(this->field18_0x68)._s_0.muf), fVar5 < 100.0)))) {
      (this->field16_0x40)._s_0.apc_here = true;
      AudioMessage("misns505.wav");
    }
  }
  fVar5 = Get_Time();
  if ((this->field17_0x50)._s_0.chaff < fVar5) {
    fVar5 = Get_Time();
    uVar4 = rand();
    uVar4 = uVar4 & 0x80000003;
    if ((int)uVar4 < 0) {
      uVar4 = (uVar4 - 1 | 0xfffffffc) + 1;
    }
    (this->field17_0x50)._s_0.chaff = (float)(int)uVar4 * 10.0 + fVar5 + 50.0;
    BuildObject("avfigh",2,"spawn5",0);
  }
  fVar5 = Get_Time();
  if ((this->field17_0x50)._s_0.apc_wave < fVar5) {
    iVar3 = BuildObject("avapc",2,"spawn6",0);
    (this->field18_0x68)._s_0.h1 = iVar3;
    iVar3 = BuildObject("avapc",2,"spawn6",0);
    (this->field18_0x68)._s_0.h2 = iVar3;
    iVar3 = BuildObject("avrecy",2,"spawn7",0);
    (this->field18_0x68)._s_0.killme = iVar3;
    iVar3 = BuildObject("bvtank",2,"spawn7",0);
    Defend(iVar3,(this->field18_0x68)._s_0.killme);
    iVar3 = BuildObject("bvtank",2,"spawn7",0);
    Defend(iVar3,(this->field18_0x68)._s_0.killme);
    piVar1 = &(this->field18_0x68)._s_0.muf;
    Attack((this->field18_0x68)._s_0.h1,*piVar1,1);
    Attack((this->field18_0x68)._s_0.h2,*piVar1,1);
    (this->field17_0x50)._s_0.apc_wave = 99999.0;
  }
  if ((((this->field16_0x40)._s_0.defender != false) &&
      (bVar2 = IsAlive(&(this->field18_0x68)._s_0.commander), !bVar2)) &&
     ((this->field16_0x40)._s_0.com_dead == false)) {
    fVar5 = Get_Time();
    (this->field16_0x40)._s_0.com_dead = true;
    (this->field17_0x50)._s_0.wave = fVar5 + 120.0;
  }
  fVar5 = Get_Time();
  if ((this->field17_0x50)._s_0.wave < fVar5) {
    (this->field19_0xa8)._s_0.wave_count = (this->field19_0xa8)._s_0.wave_count + 1;
    fVar5 = Get_Time();
    (this->field17_0x50)._s_0.wave = fVar5 + 180.0;
    AudioMessage("misns505.wav");
    if ((this->field19_0xa8)._s_0.wave_count == 1) {
      BuildObject("bvhraz",2,"spawn6",0);
      BuildObject("bvhraz",2,"spawn6",0);
      pcVar7 = "spawn6";
      pcVar6 = "bvhraz";
    }
    else {
      BuildObject("bvltnk",2,"spawn5",0);
      BuildObject("bvltnk",2,"spawn5",0);
      pcVar7 = "spawn5";
      pcVar6 = "bvltnk";
    }
    BuildObject(pcVar6,2,pcVar7,0);
    if ((this->field19_0xa8)._s_0.wave_count == 3) {
      (this->field16_0x40)._s_0.last_phase = true;
      BuildObject("avscav",2,"spawn7",0);
      BuildObject("avscav",2,"spawn7",0);
      BuildObject("spcamr",1,"camera1",0);
      SetObjectiveOn((this->field18_0x68)._s_0.killme);
      InfoDisplay::AddObjective(&infoDisplay,"misns502.otf",DisplayInterface::colorWhite,8.0);
      AudioMessage("misns506.wav");
      SetAIP("misns5.aip",2);
    }
  }
  if ((((this->field16_0x40)._s_0.last_phase != false) &&
      (bVar2 = IsAlive(&(this->field18_0x68)._s_0.killme), !bVar2)) &&
     (((this->field16_0x40)._s_0.won == false && ((this->field16_0x40)._s_0.lost == false)))) {
    (this->field16_0x40)._s_0.won = true;
    AudioMessage("misns508.wav");
    pcVar6 = "misns5w1.des";
    fVar5 = Get_Time();
    SucceedMission(fVar5 + 10.0,pcVar6);
  }
  bVar2 = IsAlive(&(this->field18_0x68)._s_0.recy);
  if (((!bVar2) && ((this->field16_0x40)._s_0.lost == false)) &&
     ((this->field16_0x40)._s_0.won == false)) {
    (this->field16_0x40)._s_0.lost = true;
    AudioMessage("misns507.wav");
    pcVar6 = "misns5l1.des";
    fVar5 = Get_Time();
    FailMission(fVar5 + 10.0,pcVar6);
  }
  return;
}
