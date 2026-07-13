/*
 * Entry: 00465639
 * Name: Tran05Mission::Execute
 * Namespace: Tran05Mission
 * Signature: void Execute(Tran05Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tran05Mission::Execute(Tran05Mission *this)

{
  int *piVar1;
  int *piVar2;
  bool bVar3;
  int iVar4;
  GameObject *pGVar5;
  float fVar6;
  char *pcVar7;
  
  iVar4 = GetPlayerHandle();
  (this->field18_0x7c)._s_0.bplayer = iVar4;
  if ((this->field16_0x40)._s_0.start_done == false) {
    SetPilot(1,2);
    SetScrap(1,5);
    SetAIP("misn02.aip",2);
    iVar4 = GetHandle("fake_player");
    (this->field18_0x7c)._s_0.dummy = iVar4;
    iVar4 = GetHandle("avland0_wingman");
    (this->field18_0x7c)._s_0.lander = iVar4;
    iVar4 = GetHandle("sscr_171_scrap");
    (this->field18_0x7c)._s_0.bhandle = iVar4;
    iVar4 = GetHandle("abcomm1_i76building");
    (this->field18_0x7c)._s_0.bhome = iVar4;
    iVar4 = GetHandle("avrecy-1_recycler");
    (this->field18_0x7c)._s_0.recycler = iVar4;
    piVar1 = &(this->field18_0x7c)._s_0.bgoal;
    iVar4 = GetHandle("apscrap-1_camerapod");
    *piVar1 = iVar4;
    iVar4 = GetHandle("sscr_176_scrap");
    (this->field18_0x7c)._s_0.bhandle2 = iVar4;
    SetUserTarget(*piVar1);
    (this->field16_0x40)._s_0.start_done = true;
    (this->field16_0x40)._s_0.camera1 = true;
    fVar6 = Get_Time();
    (this->field17_0x5c)._s_0.cam_time = fVar6 + 30.0;
    CameraReady();
    iVar4 = AudioMessage("misn0230.wav");
    (this->field20_0xd8)._s_0.audmsg = iVar4;
  }
  if (((this->field16_0x40)._s_0.camera1 != false) &&
     (((bVar3 = CameraPath("fixcam",0x4b0,0xfa,(this->field18_0x7c)._s_0.lander), bVar3 ||
       (bVar3 = CameraCancelled(), bVar3)) ||
      (bVar3 = IsAudioMessageDone((this->field20_0xd8)._s_0.audmsg), bVar3)))) {
    (this->field16_0x40)._s_0.camera1 = false;
    fVar6 = Get_Time();
    (this->field16_0x40)._s_0.camera2 = true;
    (this->field17_0x5c)._s_0.cam_time = fVar6 + 10.0;
  }
  if ((this->field16_0x40)._s_0.camera2 != false) {
    iVar4 = (this->field18_0x7c)._s_0.dummy;
    (this->field16_0x40)._s_0.camera2 = false;
    (this->field16_0x40)._s_0.camera3 = true;
    Goto(iVar4,"player_path",1);
    fVar6 = Get_Time();
    (this->field17_0x5c)._s_0.cam_time = fVar6 + 25.0;
  }
  if (((this->field16_0x40)._s_0.camera3 != false) &&
     (((bVar3 = CameraPath("zoomcam",0x4b0,800,(this->field18_0x7c)._s_0.dummy), bVar3 ||
       (bVar3 = IsAudioMessageDone((this->field20_0xd8)._s_0.audmsg), bVar3)) ||
      (bVar3 = CameraCancelled(), bVar3)))) {
    (this->field16_0x40)._s_0.camera3 = false;
    (this->field17_0x5c)._s_0.cam_time = 99999.0;
    CameraFinish();
    RemoveObject((this->field18_0x7c)._s_0.dummy);
    piVar1 = &(this->field20_0xd8)._s_0.audmsg;
    StopAudioMessage(*piVar1);
    *piVar1 = 0;
    AudioMessage("misn0224.wav");
    fVar6 = Get_Time();
    (this->field17_0x5c)._s_0.wave_timer = fVar6 + 30.0;
    InfoDisplay::AddObjective(&infoDisplay,"misn02b1.otf",DisplayInterface::colorWhite,8.0);
  }
  if ((((this->field16_0x40)._s_0.patrol1 != false) || ((this->field16_0x40)._s_0.found == false))
     || (fVar6 = GetDistance((this->field18_0x7c)._s_0.bhandle,(this->field18_0x7c)._s_0.bscav),
        75.0 <= fVar6)) {
LAB_004658c0:
    if (((this->field16_0x40)._s_0.message4 == false) && ((this->field16_0x40)._s_0.found2 != false)
       ) {
      (this->field16_0x40)._s_0.message4 = true;
    }
  }
  else {
    pGVar5 = GameObjectHandle::GetObj((this->field18_0x7c)._s_0.bhandle);
    (**(code **)(pGVar5->_padding_ + 0xc))();
    BuildObject("svfigh",2,"spawn1",0);
    AudioMessage("misn0233.wav");
    (this->field16_0x40)._s_0.message1 = true;
    (this->field16_0x40)._s_0.patrol1 = true;
    if ((this->field16_0x40)._s_0.message4 == false) {
      if ((this->field16_0x40)._s_0.found2 != false) {
        (this->field16_0x40)._s_0.message4 = true;
      }
      goto LAB_004658c0;
    }
  }
  if ((this->field16_0x40)._s_0.message4 == false) {
LAB_0046591c:
    if ((this->field16_0x40)._s_0.message5 != false) goto LAB_00465921;
  }
  else {
    if ((this->field16_0x40)._s_0.message5 == false) {
      fVar6 = GetDistance((this->field18_0x7c)._s_0.bscav,(this->field18_0x7c)._s_0.bhandle2);
      if (fVar6 < 200.0) {
        BuildObject("svfigh",2,"spawn2",0);
        (this->field16_0x40)._s_0.message5 = true;
        fVar6 = Get_Time();
        (this->field17_0x5c)._s_0.wave_timer = fVar6 + 30.0;
      }
      goto LAB_0046591c;
    }
LAB_00465921:
    fVar6 = Get_Time();
    if ((this->field17_0x5c)._s_0.wave_timer < fVar6) {
      BuildObject("svfigh",2,"spawn2",0);
      fVar6 = Get_Time();
      (this->field17_0x5c)._s_0.wave_timer = fVar6 + 45.0;
    }
  }
  if (((((this->field16_0x40)._s_0.message1 != false) &&
       ((this->field16_0x40)._s_0.message5 != false)) &&
      ((this->field16_0x40)._s_0.message2 == false)) &&
     ((pGVar5 = GameObjectHandle::GetObj((this->field18_0x7c)._s_0.bscav),
      pGVar5 == (GameObject *)0x0 ||
      (pGVar5 = GameObjectHandle::GetObj((this->field18_0x7c)._s_0.bscav), 0.0 < pGVar5->enemyShot))
     )) {
    pGVar5 = GameObjectHandle::GetObj((this->field18_0x7c)._s_0.bscav);
    if (pGVar5 != (GameObject *)0x0) {
      Follow((this->field18_0x7c)._s_0.bscav,(this->field18_0x7c)._s_0.bhome,0);
    }
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misn02b2.otf",DisplayInterface::colorWhite,8.0);
    AudioMessage("misn0225.wav");
    iVar4 = GetHandle("apbase-1_camerapod");
    SetUserTarget(iVar4);
    (this->field16_0x40)._s_0.message2 = true;
  }
  piVar1 = &(this->field18_0x7c)._s_0.bscav;
  if (((*piVar1 == 0) ||
      (((bVar3 = IsAlive(&(this->field18_0x7c)._s_0.bplayer), bVar3 &&
        (bVar3 = IsAlive(piVar1), bVar3)) &&
       (((this->field16_0x40)._s_0.message3 == false ||
        (bVar3 = IsAlive(&(this->field18_0x7c)._s_0.scav2), bVar3)))))) &&
     ((bVar3 = IsAlive(&(this->field18_0x7c)._s_0.bhome), bVar3 &&
      (bVar3 = IsAlive(&(this->field18_0x7c)._s_0.recycler), bVar3)))) {
LAB_00465aa2:
    if ((this->field16_0x40)._s_0.mission_lost != false) goto LAB_00465aa7;
  }
  else {
    if ((this->field16_0x40)._s_0.mission_lost == false) {
      InfoDisplay::ClearObjectives(&infoDisplay);
      InfoDisplay::AddObjective(&infoDisplay,"misn02b4.otf",DisplayInterface::colorRed,8.0);
      iVar4 = AudioMessage("misn0227.wav");
      (this->field20_0xd8)._s_0.audmsg = iVar4;
      (this->field16_0x40)._s_0.mission_lost = true;
      goto LAB_00465aa2;
    }
LAB_00465aa7:
    bVar3 = IsAudioMessageDone((this->field20_0xd8)._s_0.audmsg);
    if (bVar3) {
      pcVar7 = "misn02l1.des";
      fVar6 = Get_Time();
      FailMission(fVar6,pcVar7);
    }
  }
  bVar3 = IsAlive(&(this->field18_0x7c)._s_0.bplayer);
  if ((((bVar3) && ((this->field16_0x40)._s_0.message1 != false)) &&
      ((this->field16_0x40)._s_0.message4 != false)) &&
     ((fVar6 = GetDistance((this->field18_0x7c)._s_0.bhome,*piVar1), fVar6 < 300.0 &&
      ((this->field16_0x40)._s_0.message3 == false)))) {
    Follow(*piVar1,(this->field18_0x7c)._s_0.bhome,1);
    fVar6 = Get_Time();
    (this->field17_0x5c)._s_0.wave_timer = fVar6 + 45.0;
    iVar4 = BuildObject("avscav",1,"spawn3",0);
    piVar2 = &(this->field18_0x7c)._s_0.scav2;
    *piVar2 = iVar4;
    Retreat(iVar4,"retreat",1);
    SetObjectiveOn(*piVar2);
    AudioMessage("misn0228.wav");
    fVar6 = Get_Time();
    (this->field17_0x5c)._s_0.last_wave_time = fVar6 + 10.0;
    fVar6 = Get_Time();
    (this->field16_0x40)._s_0.message3 = true;
    (this->field17_0x5c)._s_0.NextSecond = fVar6 + 1.0;
  }
  bVar3 = IsAlive(piVar1);
  if (((bVar3) && ((this->field16_0x40)._s_0.message3 != false)) &&
     (fVar6 = Get_Time(), (this->field17_0x5c)._s_0.NextSecond < fVar6)) {
    AddHealth(*piVar1,200.0);
    fVar6 = Get_Time();
    (this->field17_0x5c)._s_0.NextSecond = fVar6 + 1.0;
  }
  fVar6 = Get_Time();
  if ((this->field17_0x5c)._s_0.last_wave_time < fVar6) {
    iVar4 = BuildObject("svfigh",2,"spawn4",0);
    Attack(iVar4,(this->field18_0x7c)._s_0.scav2,1);
    (this->field17_0x5c)._s_0.last_wave_time = 99999.0;
  }
  fVar6 = GetDistance((this->field18_0x7c)._s_0.bhome,(this->field18_0x7c)._s_0.scav2);
  if ((fVar6 < 200.0) && ((this->field16_0x40)._s_0.message3 != false)) {
    if ((this->field16_0x40)._s_0.mission_won != false) goto LAB_00465ca4;
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misn02b3.otf",DisplayInterface::colorGreen,8.0);
    AddHealth(*piVar1,1000.0);
    AddHealth((this->field18_0x7c)._s_0.scav2,1000.0);
    iVar4 = AudioMessage("misn0234.wav");
    (this->field20_0xd8)._s_0.audmsg = iVar4;
    (this->field16_0x40)._s_0.mission_won = true;
  }
  if ((this->field16_0x40)._s_0.mission_won == false) {
    return;
  }
LAB_00465ca4:
  bVar3 = IsAudioMessageDone((this->field20_0xd8)._s_0.audmsg);
  if (bVar3) {
    pcVar7 = "misn02w1.des";
    fVar6 = Get_Time();
    SucceedMission(fVar6,pcVar7);
  }
  return;
}
