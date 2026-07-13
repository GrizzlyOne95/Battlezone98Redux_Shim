/*
 * Entry: 0041e8a4
 * Name: Misn03Mission::Execute
 * Namespace: Misn03Mission
 * Signature: void Execute(Misn03Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn03Mission::Execute(Misn03Mission *this)

{
  Misn03Mission_u_572 *pMVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  float fVar6;
  char *pcVar7;
  
  iVar3 = GetPlayerHandle();
  (this->field18_0xdc)._s_0.user = iVar3;
  if ((this->field16_0x40)._s_0.start_done == false) {
    SetScrap(1,8);
    SetPilot(1,10);
    piVar5 = &(this->field18_0xdc)._s_0.solar1;
    SetObjectiveOn(*piVar5);
    SetObjectiveName(*piVar5,"Command Tower");
    piVar5 = &(this->field18_0xdc)._s_0.solar2;
    SetObjectiveOn(*piVar5);
    SetObjectiveName(*piVar5,"Solar Array");
    Goto((this->field18_0xdc)._s_0.avrecycler,"recycle_point",1);
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misn0301.otf",DisplayInterface::colorWhite,8.0);
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.second_wave_time = fVar6 + 200.0;
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.third_wave_time = fVar6 + 310.0;
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.fourth_wave_time = fVar6 + 430.0;
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.apc_spawn_time = fVar6 + 530.0;
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.support_time = fVar6 + 430.0;
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.next_second = fVar6 + 1.0;
    fVar6 = Get_Time();
    (this->field16_0x40)._s_0.start_done = true;
    (this->field17_0x78)._s_0.unit_check = fVar6 + 60.0;
  }
  piVar5 = &(this->field18_0xdc)._s_0.solar1;
  bVar2 = IsAlive(piVar5);
  if (((bVar2) && ((this->field16_0x40)._s_0.show_tank_attack == false)) &&
     (fVar6 = Get_Time(), (this->field17_0x78)._s_0.next_second < fVar6)) {
    AddHealth(*piVar5,50.0);
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.next_second = fVar6 + 1.0;
  }
  if ((this->field16_0x40)._s_0.message1 == false) {
    if ((this->field16_0x40)._s_0.start_done != false) {
      iVar3 = AudioMessage("misn0311.wav");
      (this->field19_0x23c)._s_0.audmsg = iVar3;
      (this->field16_0x40)._s_0.message1 = true;
      goto LAB_0041ea24;
    }
  }
  else {
LAB_0041ea24:
    if ((((this->field16_0x40)._s_0.start_done != false) &&
        (fVar6 = GetDistance((this->field18_0xdc)._s_0.avrecycler,"recycle_point",0), fVar6 < 50.0))
       && ((this->field16_0x40)._s_0.recycle_stop == false)) {
      Stop((this->field18_0xdc)._s_0.avrecycler,0);
      (this->field16_0x40)._s_0.recycle_stop = true;
    }
  }
  if ((this->field16_0x40)._s_0.first_wave_done == false) {
    Attack((this->field18_0xdc)._s_0.wave1_1,*piVar5,1);
    Attack((this->field18_0xdc)._s_0.wave1_2,*piVar5,1);
    (this->field16_0x40)._s_0.first_wave_done = true;
    if ((this->field16_0x40)._s_0.first_wave_done != false) goto LAB_0041ea92;
  }
  else {
LAB_0041ea92:
    if ((this->field16_0x40)._s_0.start_retreat == false) {
      piVar5 = &(this->field18_0xdc)._s_0.wave1_1;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        bVar2 = IsAlive(&(this->field18_0xdc)._s_0.wave1_2);
        if (bVar2) goto LAB_0041eb02;
        Retreat(*piVar5,"retreat_path",1);
        fVar6 = Get_Time();
        fVar6 = fVar6 + 10.0;
      }
      else {
        Retreat((this->field18_0xdc)._s_0.wave1_2,"retreat_path",1);
        fVar6 = Get_Time();
        fVar6 = fVar6 + 13.0;
      }
      (this->field17_0x78)._s_0.new_message_time = fVar6;
      (this->field16_0x40)._s_0.start_retreat = true;
    }
  }
LAB_0041eb02:
  if ((((this->field16_0x40)._s_0.start_retreat != false) &&
      (fVar6 = Get_Time(), (this->field17_0x78)._s_0.new_message_time < fVar6)) &&
     ((this->field16_0x40)._s_0.done_retreat == false)) {
    AudioMessage("misn0312.wav");
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misn0302.otf",DisplayInterface::colorWhite,8.0);
    InfoDisplay::AddObjective(&infoDisplay,"misn0301.otf",DisplayInterface::colorWhite,8.0);
    (this->field16_0x40)._s_0.done_retreat = true;
  }
  if ((((this->field16_0x40)._s_0.turrets_set == false) &&
      (bVar2 = IsAlive(&(this->field18_0xdc)._s_0.solar1), bVar2)) &&
     (fVar6 = Get_Time(), (this->field17_0x78)._s_0.unit_check < fVar6)) {
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.unit_check = fVar6 + 5.0;
    iVar3 = CountUnitsNearObject((this->field18_0xdc)._s_0.solar1,200.0,1,"avturr");
    (this->field19_0x23c)._s_0.z = iVar3;
    if (3 < iVar3) {
      InfoDisplay::ClearObjectives(&infoDisplay);
      InfoDisplay::AddObjective(&infoDisplay,"misn0302.otf",DisplayInterface::colorGreen,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn0301.otf",DisplayInterface::colorWhite,8.0);
      (this->field16_0x40)._s_0.turrets_set = true;
    }
  }
  if (((this->field16_0x40)._s_0.second_wave_done == false) &&
     (fVar6 = Get_Time(), (this->field17_0x78)._s_0.second_wave_time < fVar6)) {
    iVar3 = BuildObject("svfigh",2,"spawn_scrap1",0);
    (this->field18_0xdc)._s_0.wave2_1 = iVar3;
    iVar3 = BuildObject("svfigh",2,"spawn_scrap1",0);
    (this->field18_0xdc)._s_0.wave2_2 = iVar3;
    Attack((this->field18_0xdc)._s_0.wave2_1,(this->field18_0xdc)._s_0.solar1,1);
    Goto((this->field18_0xdc)._s_0.wave2_2,(this->field18_0xdc)._s_0.solar1,1);
    (this->field16_0x40)._s_0.second_wave_done = true;
  }
  if (((this->field16_0x40)._s_0.third_wave_done == false) &&
     (fVar6 = Get_Time(), (this->field17_0x78)._s_0.third_wave_time < fVar6)) {
    iVar3 = BuildObject("svfigh",2,"spawn_scrap1",0);
    (this->field18_0xdc)._s_0.wave3_1 = iVar3;
    iVar3 = BuildObject("svfigh",2,"spawn_scrap1",0);
    (this->field18_0xdc)._s_0.wave3_2 = iVar3;
    Attack((this->field18_0xdc)._s_0.wave3_1,(this->field18_0xdc)._s_0.solar1,1);
    Attack((this->field18_0xdc)._s_0.wave3_2,(this->field18_0xdc)._s_0.solar1,1);
    (this->field16_0x40)._s_0.third_wave_done = true;
  }
  if (((this->field16_0x40)._s_0.scavhunt == false) &&
     ((this->field16_0x40)._s_0.third_wave_done != false)) {
    bVar2 = IsAlive(&(this->field18_0xdc)._s_0.wave1_1);
    if (bVar2) {
      Attack((this->field18_0xdc)._s_0.wave1_1,(this->field18_0xdc)._s_0.scav1,1);
    }
    bVar2 = IsAlive(&(this->field18_0xdc)._s_0.wave1_2);
    if (bVar2) {
      Attack((this->field18_0xdc)._s_0.wave1_2,(this->field18_0xdc)._s_0.scav1,1);
    }
    (this->field16_0x40)._s_0.scavhunt = true;
  }
  if (((this->field16_0x40)._s_0.fourth_wave_done == false) &&
     (fVar6 = Get_Time(), (this->field17_0x78)._s_0.fourth_wave_time < fVar6)) {
    iVar3 = BuildObject("svapc",2,"spawn_scrap1",0);
    (this->field18_0xdc)._s_0.wave4_1 = iVar3;
    iVar3 = BuildObject("svtank",2,"spawn_scrap1",0);
    (this->field18_0xdc)._s_0.wave4_2 = iVar3;
    iVar3 = BuildObject("svfigh",2,"spawn_scrap1",0);
    piVar5 = &(this->field18_0xdc)._s_0.avrecycler;
    (this->field18_0xdc)._s_0.wave5_1 = iVar3;
    bVar2 = IsAlive(piVar5);
    if (bVar2) {
LAB_0041ede0:
      Attack((this->field18_0xdc)._s_0.wave4_1,*piVar5,1);
    }
    else {
      piVar5 = &(this->field18_0xdc)._s_0.solar3;
      bVar2 = IsAlive(piVar5);
      if (bVar2) goto LAB_0041ede0;
      piVar5 = &(this->field18_0xdc)._s_0.solar4;
      bVar2 = IsAlive(piVar5);
      if (bVar2) goto LAB_0041ede0;
    }
    Attack((this->field18_0xdc)._s_0.wave4_2,(this->field18_0xdc)._s_0.solar2,1);
    (this->field16_0x40)._s_0.fourth_wave_done = true;
  }
  if (((this->field16_0x40)._s_0.scavhunt2 == false) &&
     ((this->field16_0x40)._s_0.fourth_wave_done != false)) {
    piVar5 = &(this->field18_0xdc)._s_0.wave5_1;
    bVar2 = IsAlive(piVar5);
    if (bVar2) {
      bVar2 = IsAlive(&(this->field18_0xdc)._s_0.scav1);
      if (bVar2) {
        iVar3 = (this->field18_0xdc)._s_0.scav1;
LAB_0041ee5c:
        Attack(*piVar5,iVar3,1);
      }
      else {
        bVar2 = IsAlive(&(this->field18_0xdc)._s_0.scav2);
        if (!bVar2) {
          iVar3 = (this->field18_0xdc)._s_0.scav2;
          goto LAB_0041ee5c;
        }
      }
      (this->field16_0x40)._s_0.scavhunt2 = true;
    }
  }
  if ((this->field16_0x40)._s_0.help_spawn == false) {
    fVar6 = Get_Time();
    if ((this->field17_0x78)._s_0.support_time < fVar6) {
      iVar3 = BuildObject("avfigh",1,"spawn_scrap2",0);
      (this->field18_0xdc)._s_0.help1 = iVar3;
      iVar3 = BuildObject("avtank",1,"spawn_scrap2",0);
      (this->field18_0xdc)._s_0.help2 = iVar3;
      AudioMessage("misn0314.wav");
      piVar5 = &(this->field18_0xdc)._s_0.solar2;
      Goto((this->field18_0xdc)._s_0.help1,*piVar5,0);
      Goto((this->field18_0xdc)._s_0.help2,*piVar5,0);
      (this->field16_0x40)._s_0.help_spawn = true;
    }
    if ((this->field16_0x40)._s_0.help_spawn != false) goto LAB_0041eeed;
  }
  else {
LAB_0041eeed:
    piVar5 = &(this->field18_0xdc)._s_0.help1;
    bVar2 = IsAlive(piVar5);
    if ((((bVar2) && (bVar2 = IsAlive(&(this->field18_0xdc)._s_0.solar2), bVar2)) &&
        ((this->field16_0x40)._s_0.help_stop1 == false)) &&
       (fVar6 = GetDistance(*piVar5,(this->field18_0xdc)._s_0.solar2), fVar6 < 75.0)) {
      Stop(*piVar5,0);
      (this->field16_0x40)._s_0.help_stop1 = true;
    }
    if ((this->field16_0x40)._s_0.help_spawn != false) {
      piVar5 = &(this->field18_0xdc)._s_0.help2;
      bVar2 = IsAlive(piVar5);
      if (((bVar2) && (bVar2 = IsAlive(&(this->field18_0xdc)._s_0.solar2), bVar2)) &&
         (((this->field16_0x40)._s_0.help_stop2 == false &&
          (fVar6 = GetDistance(*piVar5,(this->field18_0xdc)._s_0.solar2), fVar6 < 75.0)))) {
        Stop(*piVar5,0);
        (this->field16_0x40)._s_0.help_stop2 = true;
      }
      if ((this->field16_0x40)._s_0.help_spawn != false) {
        if (((this->field16_0x40)._s_0.help_arrive == false) &&
           (fVar6 = GetDistance((this->field18_0xdc)._s_0.help1,(this->field18_0xdc)._s_0.user),
           fVar6 < 50.0)) {
          Goto((this->field18_0xdc)._s_0.help1,(this->field18_0xdc)._s_0.solar2,0);
          (this->field16_0x40)._s_0.help_arrive = true;
        }
        if ((((this->field16_0x40)._s_0.help_spawn != false) &&
            ((this->field16_0x40)._s_0.help_arrive == false)) &&
           (fVar6 = GetDistance((this->field18_0xdc)._s_0.help2,(this->field18_0xdc)._s_0.user),
           fVar6 < 50.0)) {
          Goto((this->field18_0xdc)._s_0.help2,(this->field18_0xdc)._s_0.solar2,0);
          (this->field16_0x40)._s_0.help_arrive = true;
        }
      }
    }
  }
  if (((this->field16_0x40)._s_0.second_objective == false) &&
     (fVar6 = Get_Time(), (this->field17_0x78)._s_0.apc_spawn_time < fVar6)) {
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.apc_spawn_time = fVar6 + 1.0;
    iVar4 = CountUnitsNearObject((this->field18_0xdc)._s_0.user,500.0,2,"svtank");
    iVar3 = (this->field18_0xdc)._s_0.user;
    (this->field19_0x23c)._s_0.z = iVar4;
    iVar3 = CountUnitsNearObject(iVar3,500.0,2,"svfigh");
    (this->field19_0x23c)._s_0.y = iVar3;
    if (((this->field19_0x23c)._s_0.z == 0) && (iVar3 == 0)) {
      iVar3 = AudioMessage("misn0305.wav");
      (this->field19_0x23c)._s_0.audmsg = iVar3;
      (this->field16_0x40)._s_0.second_objective = true;
    }
  }
  if ((this->field16_0x40)._s_0.camera_ready == false) {
    if ((this->field16_0x40)._s_0.second_objective != false) {
      CameraReady();
      fVar6 = Get_Time();
      (this->field17_0x78)._s_0.movie_time = fVar6 + 14.5;
      fVar6 = Get_Time();
      (this->field17_0x78)._s_0.new_unit_time = fVar6 + 7.5;
      iVar3 = BuildObject("svrecy",2,"recy_spawn",0);
      (this->field18_0xdc)._s_0.prop1 = iVar3;
      iVar3 = BuildObject("svmuf",2,"muf_spawn",0);
      (this->field18_0xdc)._s_0.prop2 = iVar3;
      iVar3 = BuildObject("svtank",2,"tank1_spawn",0);
      (this->field18_0xdc)._s_0.prop3 = iVar3;
      iVar3 = BuildObject("svtank",2,"tank2_spawn",0);
      (this->field18_0xdc)._s_0.prop4 = iVar3;
      iVar3 = BuildObject("svfigh",2,"fighter1_spawn",0);
      (this->field18_0xdc)._s_0.prop5 = iVar3;
      iVar3 = BuildObject("sssold",2,"guy1_spawn",0);
      (this->field18_0xdc)._s_0.guy1 = iVar3;
      iVar3 = BuildObject("sssold",2,"guy2_spawn",0);
      (this->field18_0xdc)._s_0.guy2 = iVar3;
      iVar3 = BuildObject("sssold",2,"guy1_spawn",0);
      (this->field18_0xdc)._s_0.guy3 = iVar3;
      iVar3 = BuildObject("sssold",2,"guy2_spawn",0);
      (this->field18_0xdc)._s_0.guy4 = iVar3;
      Defend((this->field18_0xdc)._s_0.prop1,1);
      Goto((this->field18_0xdc)._s_0.prop2,"tank1_spawn",1);
      Goto((this->field18_0xdc)._s_0.prop3,"that_path",1);
      Goto((this->field18_0xdc)._s_0.prop4,"cool_path",1);
      Goto((this->field18_0xdc)._s_0.prop5,"cool_path",1);
      Goto((this->field18_0xdc)._s_0.guy1,"guy_spot",1);
      Goto((this->field18_0xdc)._s_0.guy2,"guy_spot",1);
      Goto((this->field18_0xdc)._s_0.guy3,"guy_spot",1);
      Goto((this->field18_0xdc)._s_0.guy4,"guy_spot",1);
      (this->field16_0x40)._s_0.camera_ready = true;
    }
    if ((this->field16_0x40)._s_0.camera_ready != false) goto LAB_0041f267;
  }
  else {
LAB_0041f267:
    if ((this->field16_0x40)._s_0.movie_over == false) {
      piVar5 = &(this->field18_0xdc)._s_0.prop1;
      CameraPath("movie_path",0xaf,0x352,*piVar5);
      Defend(*piVar5,1);
      (this->field16_0x40)._s_0.start_movie = true;
    }
    if ((((this->field16_0x40)._s_0.camera_ready != false) &&
        ((this->field16_0x40)._s_0.more_show == false)) &&
       (((this->field16_0x40)._s_0.movie_over == false &&
        (fVar6 = Get_Time(), (this->field17_0x78)._s_0.new_unit_time < fVar6)))) {
      iVar3 = BuildObject("svfigh",2,"muf_spawn",0);
      (this->field18_0xdc)._s_0.prop8 = iVar3;
      iVar3 = BuildObject("svfigh",2,"muf_spawn",0);
      (this->field18_0xdc)._s_0.prop9 = iVar3;
      Goto((this->field18_0xdc)._s_0.prop8,"tank2_spawn",1);
      Goto((this->field18_0xdc)._s_0.prop9,"fighter1_spawn",1);
      (this->field16_0x40)._s_0.more_show = true;
    }
  }
  if ((this->field16_0x40)._s_0.start_movie == false) {
LAB_0041f470:
    if ((this->field16_0x40)._s_0.movie_over != false) goto LAB_0041f479;
LAB_0041f56b:
    if ((this->field16_0x40)._s_0.remove_props != false) goto LAB_0041f570;
  }
  else {
    if ((this->field16_0x40)._s_0.movie_over == false) {
      bVar2 = CameraCancelled();
      if ((bVar2) || (fVar6 = Get_Time(), (this->field17_0x78)._s_0.movie_time < fVar6)) {
        CameraFinish();
        StopAudioMessage((this->field19_0x23c)._s_0.audmsg);
        iVar3 = BuildObject("avapc",1,"apc1_spawn",0);
        (this->field18_0xdc)._s_0.rescue1 = iVar3;
        iVar3 = BuildObject("avapc",1,"apc2_spawn",0);
        (this->field18_0xdc)._s_0.rescue2 = iVar3;
        fVar6 = Get_Time();
        (this->field17_0x78)._s_0.pull_out_time = fVar6 + 28.0;
        fVar6 = Get_Time();
        iVar3 = (this->field18_0xdc)._s_0.solar1;
        (this->field17_0x78)._s_0.turret_move_time = fVar6 + 30.0;
        SetObjectiveOff(iVar3);
        SetObjectiveOff((this->field18_0xdc)._s_0.solar2);
        SetObjectiveOn((this->field18_0xdc)._s_0.rescue1);
        SetObjectiveName((this->field18_0xdc)._s_0.rescue1,"Transport 1");
        SetObjectiveOn((this->field18_0xdc)._s_0.rescue2);
        SetObjectiveName((this->field18_0xdc)._s_0.rescue2,"Transport 2");
        piVar5 = &(this->field18_0xdc)._s_0.launch;
        SetObjectiveOn(*piVar5);
        SetObjectiveName(*piVar5,"Launch Pad");
        InfoDisplay::ClearObjectives(&infoDisplay);
        InfoDisplay::AddObjective(&infoDisplay,"misn0311.otf",DisplayInterface::colorGreen,8.0);
        InfoDisplay::AddObjective(&infoDisplay,"misn0312.otf",DisplayInterface::colorGreen,8.0);
        InfoDisplay::AddObjective(&infoDisplay,"misn0303.otf",DisplayInterface::colorWhite,8.0);
        (this->field16_0x40)._s_0.movie_over = true;
      }
      goto LAB_0041f470;
    }
LAB_0041f479:
    if ((this->field16_0x40)._s_0.remove_props == false) {
      iVar4 = AudioMessage("misn0306.wav");
      iVar3 = (this->field18_0xdc)._s_0.prop1;
      (this->field19_0x23c)._s_0.audmsg = iVar4;
      RemoveObject(iVar3);
      RemoveObject((this->field18_0xdc)._s_0.prop2);
      RemoveObject((this->field18_0xdc)._s_0.prop3);
      RemoveObject((this->field18_0xdc)._s_0.prop4);
      RemoveObject((this->field18_0xdc)._s_0.prop5);
      piVar5 = &(this->field18_0xdc)._s_0.prop8;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.prop9;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.guy1;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.guy2;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.guy3;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.guy4;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      (this->field16_0x40)._s_0.remove_props = true;
      goto LAB_0041f56b;
    }
LAB_0041f570:
    if (((this->field16_0x40)._s_0.trans_underway == false) &&
       (fVar6 = Get_Time(), (this->field17_0x78)._s_0.pull_out_time < fVar6)) {
      Retreat((this->field18_0xdc)._s_0.rescue1,"rescue_path",1);
      Retreat((this->field18_0xdc)._s_0.rescue2,"rescue_path",1);
      fVar6 = Get_Time();
      (this->field16_0x40)._s_0.trans_underway = true;
      (this->field16_0x40)._s_0.rescue_move_done = true;
      (this->field17_0x78)._s_0.ambush_message_time = fVar6 + 15.0;
    }
  }
  if ((this->field16_0x40)._s_0.remove_props != false) {
    if (((this->field16_0x40)._s_0.turret_move_done == false) &&
       (fVar6 = Get_Time(), (this->field17_0x78)._s_0.turret_move_time < fVar6)) {
      Retreat((this->field18_0xdc)._s_0.turret1,"turret_path1",1);
      Retreat((this->field18_0xdc)._s_0.turret2,"turret_path2",1);
      Retreat((this->field18_0xdc)._s_0.turret3,"turret_path3",1);
      Retreat((this->field18_0xdc)._s_0.turret4,"base",1);
      (this->field16_0x40)._s_0.turret_move_done = true;
    }
    bVar2 = IsAlive(&(this->field18_0xdc)._s_0.wave1_1);
    if (bVar2) {
      Attack((this->field18_0xdc)._s_0.wave1_1,(this->field18_0xdc)._s_0.rescue1,1);
    }
    bVar2 = IsAlive(&(this->field18_0xdc)._s_0.wave1_2);
    if (bVar2) {
      Attack((this->field18_0xdc)._s_0.wave1_2,(this->field18_0xdc)._s_0.rescue1,1);
    }
    bVar2 = IsAlive(&(this->field18_0xdc)._s_0.wave5_1);
    if (bVar2) {
      Attack((this->field18_0xdc)._s_0.wave5_1,(this->field18_0xdc)._s_0.rescue2,1);
    }
    bVar2 = IsAlive(&(this->field18_0xdc)._s_0.wave5_2);
    if (bVar2) {
      Attack((this->field18_0xdc)._s_0.wave5_2,(this->field18_0xdc)._s_0.rescue1,1);
    }
    bVar2 = IsAlive(&(this->field18_0xdc)._s_0.wave5_3);
    if (bVar2) {
      Attack((this->field18_0xdc)._s_0.wave5_3,(this->field18_0xdc)._s_0.rescue2,1);
    }
  }
  if ((((this->field16_0x40)._s_0.trans_underway != false) &&
      (fVar6 = Get_Time(), (this->field17_0x78)._s_0.ambush_message_time < fVar6)) &&
     ((this->field16_0x40)._s_0.ambush_message == false)) {
    AudioMessage("misn0315.wav");
    iVar3 = BuildObject("svfigh",2,"spawn_scrap1",0);
    (this->field18_0xdc)._s_0.wave6_1 = iVar3;
    iVar3 = BuildObject("svtank",2,"spawn_scrap1",0);
    (this->field18_0xdc)._s_0.wave6_2 = iVar3;
    iVar3 = BuildObject("svtank",2,"spawn_scrap1",0);
    (this->field18_0xdc)._s_0.wave6_3 = iVar3;
    Attack((this->field18_0xdc)._s_0.wave6_1,(this->field18_0xdc)._s_0.solar2,1);
    Attack((this->field18_0xdc)._s_0.wave6_2,(this->field18_0xdc)._s_0.solar1,1);
    Goto((this->field18_0xdc)._s_0.wave6_3,"base",1);
    (this->field16_0x40)._s_0.ambush_message = true;
  }
  if ((((this->field16_0x40)._s_0.remove_props != false) &&
      ((this->field16_0x40)._s_0.lost == false)) &&
     (((this->field16_0x40)._s_0.third_objective == false &&
      ((fVar6 = GetDistance((this->field18_0xdc)._s_0.rescue1,(this->field18_0xdc)._s_0.launch),
       fVar6 < 100.0 &&
       (fVar6 = GetDistance((this->field18_0xdc)._s_0.rescue2,(this->field18_0xdc)._s_0.launch),
       fVar6 < 100.0)))))) {
    AudioMessage("misn0310.wav");
    bVar2 = IsAlive(&(this->field18_0xdc)._s_0.rescue1);
    if (bVar2) {
      SetObjectiveOff((this->field18_0xdc)._s_0.rescue1);
    }
    bVar2 = IsAlive(&(this->field18_0xdc)._s_0.rescue1);
    if (bVar2) {
      SetObjectiveOff((this->field18_0xdc)._s_0.rescue2);
    }
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misn0313.otf",DisplayInterface::colorGreen,8.0);
    InfoDisplay::AddObjective(&infoDisplay,"misn0304.otf",DisplayInterface::colorWhite,8.0);
    iVar3 = BuildObject("svtank",2,"spawn_scrap1",0);
    (this->field18_0xdc)._s_0.wave7_1 = iVar3;
    iVar3 = BuildObject("svtank",2,"spawn_scrap1",0);
    (this->field18_0xdc)._s_0.wave7_2 = iVar3;
    iVar3 = BuildObject("svtank",2,"spawn_scrap1",0);
    (this->field18_0xdc)._s_0.wave7_3 = iVar3;
    Goto((this->field18_0xdc)._s_0.wave7_1,"base",1);
    Goto((this->field18_0xdc)._s_0.wave7_2,"base",1);
    Goto((this->field18_0xdc)._s_0.wave7_3,"base",1);
    fVar6 = Get_Time();
    (this->field16_0x40)._s_0.third_objective = true;
    (this->field17_0x78)._s_0.final_check = fVar6 + 120.0;
  }
  if ((this->field16_0x40)._s_0.final_objective == false) {
    if (((this->field16_0x40)._s_0.second_warning == false) &&
       (fVar6 = Get_Time(), (this->field17_0x78)._s_0.final_check < fVar6)) {
      fVar6 = Get_Time();
      (this->field17_0x78)._s_0.final_check = fVar6 + 120.0;
      InfoDisplay::ClearObjectives(&infoDisplay);
      InfoDisplay::AddObjective(&infoDisplay,"misn0313.otf",DisplayInterface::colorGreen,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn0304.otf",DisplayInterface::colorWhite,8.0);
      AudioMessage("misn0310.wav");
      (this->field16_0x40)._s_0.second_warning = true;
    }
    if ((this->field16_0x40)._s_0.final_objective != false) goto LAB_0041fabb;
    if ((((this->field16_0x40)._s_0.second_warning != false) &&
        ((this->field16_0x40)._s_0.last_warning == false)) &&
       (fVar6 = Get_Time(), (this->field17_0x78)._s_0.final_check < fVar6)) {
      fVar6 = Get_Time();
      (this->field17_0x78)._s_0.final_check = fVar6 + 120.0;
      InfoDisplay::ClearObjectives(&infoDisplay);
      InfoDisplay::AddObjective(&infoDisplay,"misn0313.otf",DisplayInterface::colorGreen,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn0304.otf",DisplayInterface::colorWhite,8.0);
      AudioMessage("misn0310.wav");
      (this->field16_0x40)._s_0.last_warning = true;
    }
    if ((this->field16_0x40)._s_0.final_objective != false) goto LAB_0041fabb;
    if ((this->field16_0x40)._s_0.third_objective != false) {
      iVar3 = CountUnitsNearObject((this->field18_0xdc)._s_0.geyser,5000.0,2,"svtank");
      if ((float)iVar3 < 5.0) {
        iVar3 = BuildObject("svtank",2,"spawn_scrap1",0);
        (this->field18_0xdc)._s_0.wave7_4 = iVar3;
        iVar3 = BuildObject("svtank",2,"spawn_scrap1",0);
        (this->field18_0xdc)._s_0.wave7_5 = iVar3;
        Goto((this->field18_0xdc)._s_0.wave7_4,"base",1);
        Goto((this->field18_0xdc)._s_0.wave7_5,"base",1);
      }
      goto LAB_0041fabb;
    }
  }
  else {
LAB_0041fabb:
    if ((((this->field16_0x40)._s_0.third_objective != false) &&
        (fVar6 = GetDistance((this->field18_0xdc)._s_0.user,(this->field18_0xdc)._s_0.launch),
        fVar6 < 100.0)) &&
       (((this->field16_0x40)._s_0.lost == false &&
        ((this->field16_0x40)._s_0.final_objective == false)))) {
      (this->field16_0x40)._s_0.final_objective = true;
    }
  }
  if ((this->field16_0x40)._s_0.startfinishingmovie == false) {
    if ((this->field16_0x40)._s_0.final_objective != false) {
      piVar5 = &(this->field18_0xdc)._s_0.avrecycler;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.scav1;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.scav2;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.scav3;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.scav4;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.scav5;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.scav6;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.avturret1;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.avturret2;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.avturret3;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.avturret4;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.avturret5;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.avturret6;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.avturret7;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.avturret8;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.avturret9;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.avturret10;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.help1;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.help2;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.wave4_1;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.wave4_2;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.wave6_1;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.wave6_2;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.wave6_3;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.wave7_1;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.wave7_2;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.wave7_3;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.wave7_4;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.wave7_5;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.turret1;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.turret2;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.turret3;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.turret4;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      piVar5 = &(this->field18_0xdc)._s_0.wave4_1;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        RemoveObject(*piVar5);
      }
      fVar6 = Get_Time();
      (this->field17_0x78)._s_0.clean_sweep_time = fVar6 + 14.0;
      fVar6 = Get_Time();
      (this->field17_0x78)._s_0.next_shot = fVar6 + 18.5;
      fVar6 = Get_Time();
      (this->field17_0x78)._s_0.new_unit_time = fVar6 + 2.0;
      iVar3 = AudioMessage("misn0316.wav");
      (this->field19_0x23c)._s_0.audmsg = iVar3;
      iVar3 = BuildObject("svtank",2,"spawna",0);
      (this->field18_0xdc)._s_0.prop1 = iVar3;
      iVar3 = BuildObject("svtank",2,"spawnb",0);
      (this->field18_0xdc)._s_0.prop2 = iVar3;
      iVar3 = BuildObject("svtank",2,"spawnc",0);
      (this->field18_0xdc)._s_0.prop3 = iVar3;
      CameraReady();
      (this->field16_0x40)._s_0.startfinishingmovie = true;
    }
    if ((this->field16_0x40)._s_0.startfinishingmovie != false) goto LAB_0041ff0d;
  }
  else {
LAB_0041ff0d:
    if ((this->field16_0x40)._s_0.camera_2 == false) {
      pMVar1 = &this->field19_0x23c;
      CameraPath("camera_path",(pMVar1->_s_0).x,0xdac,(this->field18_0xdc)._s_0.cam_geyser);
      (pMVar1->_s_0).x = (pMVar1->_s_0).x + -0xf;
      (this->field16_0x40)._s_0.camera_on = true;
    }
    if ((this->field16_0x40)._s_0.startfinishingmovie != false) {
      if ((this->field16_0x40)._s_0.tanks_go == false) {
        fVar6 = Get_Time();
        if (fVar6 <= (this->field17_0x78)._s_0.new_unit_time) {
          Defend((this->field18_0xdc)._s_0.prop1,1);
          Defend((this->field18_0xdc)._s_0.prop2,1);
          Defend((this->field18_0xdc)._s_0.prop3,1);
        }
        else {
          Goto((this->field18_0xdc)._s_0.prop1,"line1",1);
          Goto((this->field18_0xdc)._s_0.prop2,"line2",1);
          Goto((this->field18_0xdc)._s_0.prop3,"line3",1);
          (this->field16_0x40)._s_0.tanks_go = true;
        }
      }
      if ((this->field16_0x40)._s_0.startfinishingmovie != false) {
        fVar6 = Get_Time();
        if (((this->field17_0x78)._s_0.clean_sweep_time < fVar6) &&
           ((this->field16_0x40)._s_0.clean_sweep == false)) {
          (this->field16_0x40)._s_0.clean_sweep = true;
        }
        if ((((this->field16_0x40)._s_0.startfinishingmovie != false) &&
            (fVar6 = Get_Time(), (this->field17_0x78)._s_0.next_shot < fVar6)) &&
           ((this->field16_0x40)._s_0.camera_off == false)) {
          CameraPath("inbase_path",0xa0,0x5a,(this->field18_0xdc)._s_0.prop1);
          (this->field16_0x40)._s_0.camera_2 = true;
        }
      }
    }
  }
  if ((this->field16_0x40)._s_0.camera_2 == false) {
LAB_00420121:
    if ((this->field16_0x40)._s_0.show_tank_attack != false) goto LAB_00420126;
LAB_00420161:
    if ((this->field16_0x40)._s_0.tower_dead != false) goto LAB_00420166;
  }
  else {
    if ((this->field16_0x40)._s_0.speach2 == false) {
      iVar3 = AudioMessage("misn0317.wav");
      (this->field19_0x23c)._s_0.audmsg = iVar3;
      (this->field16_0x40)._s_0.speach2 = true;
    }
    if ((this->field16_0x40)._s_0.camera_2 == false) goto LAB_00420121;
    if ((this->field16_0x40)._s_0.show_tank_attack == false) {
      fVar6 = GetDistance((this->field18_0xdc)._s_0.prop1,(this->field18_0xdc)._s_0.shot_geyser);
      if (fVar6 < 20.0) {
        piVar5 = &(this->field18_0xdc)._s_0.solar1;
        bVar2 = IsAlive(piVar5);
        if (bVar2) {
          Attack((this->field18_0xdc)._s_0.prop1,*piVar5,1);
          Attack((this->field18_0xdc)._s_0.prop2,*piVar5,1);
          piVar5 = &(this->field18_0xdc)._s_0.solar2;
          bVar2 = IsAlive(piVar5);
          if (bVar2) {
            Damage(*piVar5,20000);
          }
          piVar5 = &(this->field18_0xdc)._s_0.solar3;
          bVar2 = IsAlive(piVar5);
          if (bVar2) {
            Damage(*piVar5,20000);
          }
          piVar5 = &(this->field18_0xdc)._s_0.solar4;
          bVar2 = IsAlive(piVar5);
          if (bVar2) {
            Damage(*piVar5,20000);
          }
          fVar6 = Get_Time();
          (this->field17_0x78)._s_0.kill_tower = fVar6 + 7.0;
          (this->field16_0x40)._s_0.show_tank_attack = true;
        }
      }
      goto LAB_00420121;
    }
LAB_00420126:
    if ((this->field16_0x40)._s_0.tower_dead == false) {
      fVar6 = Get_Time();
      if ((this->field17_0x78)._s_0.kill_tower < fVar6) {
        piVar5 = &(this->field18_0xdc)._s_0.solar1;
        bVar2 = IsAlive(piVar5);
        if (bVar2) {
          Damage(*piVar5,25000);
          (this->field16_0x40)._s_0.tower_dead = true;
        }
      }
      goto LAB_00420161;
    }
LAB_00420166:
    if ((this->field16_0x40)._s_0.climax1 == false) {
      Retreat((this->field18_0xdc)._s_0.prop1,"climax_path1",1);
      Retreat((this->field18_0xdc)._s_0.prop2,"spawn_scrap1",1);
      Retreat((this->field18_0xdc)._s_0.prop3,"spawn_scrap1",1);
      fVar6 = Get_Time();
      (this->field17_0x78)._s_0.clear_debis_time = fVar6 + 6.0;
      iVar3 = AudioMessage("misn0318.wav");
      (this->field19_0x23c)._s_0.audmsg = iVar3;
      (this->field16_0x40)._s_0.climax1 = true;
    }
  }
  if ((this->field16_0x40)._s_0.climax1 == false) {
LAB_00420300:
    if ((this->field16_0x40)._s_0.climax2 != false) goto LAB_00420309;
LAB_0042040b:
    if ((this->field16_0x40)._s_0.last_blown == false) goto LAB_00420460;
  }
  else {
    if (((this->field16_0x40)._s_0.clear_debis == false) &&
       (fVar6 = Get_Time(), (this->field17_0x78)._s_0.clear_debis_time < fVar6)) {
      bVar2 = IsAlive(&(this->field18_0xdc)._s_0.build3);
      if (bVar2) {
        Damage((this->field18_0xdc)._s_0.build3,20000);
      }
      iVar3 = BuildObject("svtank",2,(this->field18_0xdc)._s_0.cam_geyser);
      (this->field18_0xdc)._s_0.prop8 = iVar3;
      Retreat(iVar3,"climax_path2",1);
      (this->field16_0x40)._s_0.clear_debis = true;
    }
    if ((this->field16_0x40)._s_0.climax1 == false) goto LAB_00420300;
    if ((this->field16_0x40)._s_0.climax2 == false) {
      fVar6 = GetDistance((this->field18_0xdc)._s_0.prop1,(this->field18_0xdc)._s_0.cam_geyser);
      if (fVar6 < 100.0) {
        Retreat((this->field18_0xdc)._s_0.prop1,"climax_path2",1);
        iVar3 = BuildObject("svfigh",2,"solar_spot",0);
        (this->field18_0xdc)._s_0.prop9 = iVar3;
        iVar3 = BuildObject("svfigh",2,"solar_spot",0);
        (this->field18_0xdc)._s_0.prop0 = iVar3;
        Retreat((this->field18_0xdc)._s_0.prop9,"camera_pass",1);
        Retreat((this->field18_0xdc)._s_0.prop0,"camera_pass",1);
        piVar5 = &(this->field18_0xdc)._s_0.hanger;
        bVar2 = IsAlive(piVar5);
        if (bVar2) {
          Damage(*piVar5,20000);
        }
        fVar6 = Get_Time();
        (this->field17_0x78)._s_0.clear_debis_time = fVar6 + 3.0;
        (this->field16_0x40)._s_0.climax2 = true;
      }
      goto LAB_00420300;
    }
LAB_00420309:
    if ((this->field16_0x40)._s_0.last_blown == false) {
      fVar6 = Get_Time();
      if ((this->field17_0x78)._s_0.clear_debis_time < fVar6) {
        bVar2 = IsAlive(&(this->field18_0xdc)._s_0.box1);
        if (bVar2) {
          Damage((this->field18_0xdc)._s_0.box1,20000);
        }
        bVar2 = IsAlive(&(this->field18_0xdc)._s_0.build1);
        if (bVar2) {
          Damage((this->field18_0xdc)._s_0.build1,20000);
        }
        bVar2 = IsAlive(&(this->field18_0xdc)._s_0.crate1);
        if (bVar2) {
          Damage((this->field18_0xdc)._s_0.crate1,20000);
        }
        bVar2 = IsAlive(&(this->field18_0xdc)._s_0.crate2);
        if (bVar2) {
          Damage((this->field18_0xdc)._s_0.crate2,20000);
        }
        bVar2 = IsAlive(&(this->field18_0xdc)._s_0.crate3);
        if (bVar2) {
          Damage((this->field18_0xdc)._s_0.crate3,20000);
        }
        Retreat((this->field18_0xdc)._s_0.prop2,"solar_spot",1);
        Retreat((this->field18_0xdc)._s_0.prop8,"spawn_scrap1",1);
        iVar3 = BuildObject("abwpow",1,"sucker_spot",0);
        (this->field18_0xdc)._s_0.sucker = iVar3;
        (this->field16_0x40)._s_0.last_blown = true;
      }
      goto LAB_0042040b;
    }
  }
  if (((this->field16_0x40)._s_0.end_shot == false) &&
     (fVar6 = GetDistance((this->field18_0xdc)._s_0.prop1,(this->field18_0xdc)._s_0.sucker),
     fVar6 < 65.0)) {
    Attack((this->field18_0xdc)._s_0.prop1,(this->field18_0xdc)._s_0.sucker,1);
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.camera_off_time = fVar6 + 1.5;
    (this->field16_0x40)._s_0.end_shot = true;
  }
LAB_00420460:
  if ((((this->field16_0x40)._s_0.camera_on != false) &&
      ((this->field16_0x40)._s_0.camera_off == false)) &&
     ((bVar2 = CameraCancelled(), bVar2 ||
      (fVar6 = Get_Time(), (this->field17_0x78)._s_0.camera_off_time < fVar6)))) {
    (this->field16_0x40)._s_0.startfinishingmovie = false;
    CameraFinish();
    StopAudioMessage((this->field19_0x23c)._s_0.audmsg);
    SucceedMission(0.1,"misn03w1.des");
    (this->field16_0x40)._s_0.camera_off = true;
  }
  if (((((this->field16_0x40)._s_0.last_warning != false) &&
       (fVar6 = Get_Time(), (this->field17_0x78)._s_0.final_check < fVar6)) &&
      ((this->field16_0x40)._s_0.final_objective == false)) &&
     ((this->field16_0x40)._s_0.lost == false)) {
    pcVar7 = "misn03f5.des";
    fVar6 = Get_Time();
    FailMission(fVar6 + 1.0,pcVar7);
    (this->field16_0x40)._s_0.lost = true;
  }
  if ((((this->field16_0x40)._s_0.dead1 == false) &&
      ((this->field16_0x40)._s_0.show_tank_attack == false)) &&
     (((this->field16_0x40)._s_0.second_objective == false &&
      (bVar2 = IsValid(&(this->field18_0xdc)._s_0.solar1), !bVar2)))) {
    AudioMessage("misn0302.wav");
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misn0311.otf",DisplayInterface::colorRed,8.0);
    InfoDisplay::AddObjective(&infoDisplay,"misn0312.otf",DisplayInterface::colorWhite,8.0);
    (this->field16_0x40)._s_0.lost = true;
    (this->field16_0x40)._s_0.dead1 = true;
    if ((this->field16_0x40)._s_0.turrets_set == false) {
      pcVar7 = "misn03f1.des";
    }
    else {
      pcVar7 = "misn03f2.des";
    }
    fVar6 = Get_Time();
    FailMission(fVar6 + 10.0,pcVar7);
  }
  if ((((this->field16_0x40)._s_0.dead2 == false) && ((this->field16_0x40)._s_0.tanks_go == false))
     && (((this->field16_0x40)._s_0.second_objective == false &&
         (bVar2 = IsValid(&(this->field18_0xdc)._s_0.solar2), !bVar2)))) {
    AudioMessage("misn0303.wav");
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misn0311.otf",DisplayInterface::colorRed,8.0);
    InfoDisplay::AddObjective(&infoDisplay,"misn0312.otf",DisplayInterface::colorWhite,8.0);
    (this->field16_0x40)._s_0.lost = true;
    pcVar7 = "misn03f3.des";
    (this->field16_0x40)._s_0.dead2 = true;
    fVar6 = Get_Time();
    FailMission(fVar6 + 10.0,pcVar7);
  }
  if ((this->field16_0x40)._s_0.movie_over != false) {
    if ((((this->field16_0x40)._s_0.dead3 == false) &&
        (bVar2 = IsAlive(&(this->field18_0xdc)._s_0.rescue1), !bVar2)) &&
       ((this->field16_0x40)._s_0.third_objective == false)) {
      AudioMessage("misn0304.wav");
      InfoDisplay::ClearObjectives(&infoDisplay);
      InfoDisplay::AddObjective(&infoDisplay,"misn0311.otf",DisplayInterface::colorGreen,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn0312.otf",DisplayInterface::colorGreen,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn0303.otf",DisplayInterface::colorRed,8.0);
      (this->field16_0x40)._s_0.lost = true;
      pcVar7 = "misn03f4.des";
      (this->field16_0x40)._s_0.dead3 = true;
      fVar6 = Get_Time();
      FailMission(fVar6 + 10.0,pcVar7);
    }
    if ((((this->field16_0x40)._s_0.movie_over != false) &&
        ((this->field16_0x40)._s_0.dead3 == false)) &&
       ((bVar2 = IsAlive(&(this->field18_0xdc)._s_0.rescue2), !bVar2 &&
        ((this->field16_0x40)._s_0.third_objective == false)))) {
      AudioMessage("misn0304.wav");
      InfoDisplay::ClearObjectives(&infoDisplay);
      InfoDisplay::AddObjective(&infoDisplay,"misn0311.otf",DisplayInterface::colorGreen,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn0312.otf",DisplayInterface::colorGreen,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn0303.otf",DisplayInterface::colorRed,8.0);
      (this->field16_0x40)._s_0.lost = true;
      pcVar7 = "misn03f4.des";
      (this->field16_0x40)._s_0.dead3 = true;
      fVar6 = Get_Time();
      FailMission(fVar6 + 10.0,pcVar7);
    }
  }
  bVar2 = IsAlive(&(this->field18_0xdc)._s_0.launch);
  if ((!bVar2) && ((this->field16_0x40)._s_0.lost == false)) {
    pcVar7 = (char *)0x0;
    fVar6 = Get_Time();
    FailMission(fVar6 + 1.0,pcVar7);
    (this->field16_0x40)._s_0.lost = true;
  }
  return;
}
