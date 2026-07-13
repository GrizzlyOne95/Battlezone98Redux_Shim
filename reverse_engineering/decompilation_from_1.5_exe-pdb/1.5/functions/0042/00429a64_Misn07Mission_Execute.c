/*
 * Entry: 00429a64
 * Name: Misn07Mission::Execute
 * Namespace: Misn07Mission
 * Signature: void Execute(Misn07Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall Misn07Mission::Execute(Misn07Mission *this)

{
  int *piVar1;
  bool *pbVar2;
  int *piVar3;
  bool bVar4;
  int iVar5;
  AiPath *pAVar6;
  int iVar7;
  float fVar8;
  char *pcVar9;
  char local_10 [12];
  uint local_4;
  
  local_4 = __security_cookie ^ (uint)local_10;
  iVar5 = GetPlayerHandle();
  (this->field18_0x1e4)._s_0.user = iVar5;
  piVar1 = &(this->field20_0x6cc)._s_0.mine_check;
  *piVar1 = *piVar1 + 10;
  if (0x6e < *piVar1) {
    *piVar1 = 1;
  }
  if ((this->field16_0x40)._s_0.start_done == false) {
    SetObjectiveName((this->field18_0x1e4)._s_0.nav3,"Rendezvous Point");
    SetScrap(1,10);
    SetObjectiveOff((this->field18_0x1e4)._s_0.ccacomtower);
    Patrol((this->field18_0x1e4)._s_0.patrol1_1,"patrol_path3",1);
    Patrol((this->field18_0x1e4)._s_0.patrol1_2,"patrol_path3",1);
    Patrol((this->field18_0x1e4)._s_0.svpatrol3_1,"patrol_path1",1);
    Patrol((this->field18_0x1e4)._s_0.svpatrol3_2,"patrol_path1",1);
    Patrol((this->field18_0x1e4)._s_0.svpatrol4_1,"patrol_path2",1);
    Patrol((this->field18_0x1e4)._s_0.svpatrol4_2,"patrol_path2",1);
    piVar1 = &(this->field18_0x1e4)._s_0.wingtank2;
    SetIndependence(*piVar1,0);
    Stop(*piVar1,1);
    SetPerceivedTeam(*piVar1,1);
    piVar1 = &(this->field18_0x1e4)._s_0.wingtank3;
    SetIndependence(*piVar1,0);
    Stop(*piVar1,1);
    SetPerceivedTeam(*piVar1,1);
    Stop((this->field18_0x1e4)._s_0.svpatrol2_1,1);
    Stop((this->field18_0x1e4)._s_0.svpatrol2_2,1);
    fVar8 = Get_Time();
    (this->field17_0x16c)._s_0.rendezous_check = fVar8 + 9.0;
    fVar8 = Get_Time();
    (this->field17_0x16c)._s_0.patrol2_move_time = fVar8 + 121.0;
    fVar8 = Get_Time();
    (this->field17_0x16c)._s_0.alarm_check = fVar8 + 27.0;
    pAVar6 = AiPath::Find("turret1_spot");
    (this->field19_0x508)._s_0.turret1_spot = pAVar6;
    (this->field20_0x6cc)._s_0.count = 0;
    do {
      sprintf(local_10,"m%0.3d",(this->field20_0x6cc)._s_0.count);
      pAVar6 = AiPath::Find(local_10);
      *(AiPath **)((int)&this->field19_0x508 + (this->field20_0x6cc)._s_0.count * 4 + 4) = pAVar6;
      (this->field20_0x6cc)._s_0.count = (this->field20_0x6cc)._s_0.count + 1;
    } while ((this->field20_0x6cc)._s_0.count < 0x6f);
    (this->field16_0x40)._s_0.start_done = true;
  }
  if ((this->field16_0x40)._s_0.opening_vo == false) {
    if ((this->field16_0x40)._s_0.start_done != false) {
      fVar8 = Get_Time();
      if ((this->field17_0x16c)._s_0.rendezous_check < fVar8) {
        fVar8 = Get_Time();
        (this->field17_0x16c)._s_0.rendezous_check = fVar8 + 15.0;
        AudioMessage("misn0700.wav");
        InfoDisplay::ClearObjectives(&infoDisplay);
        InfoDisplay::AddObjective(&infoDisplay,"misn0700.otf",DisplayInterface::colorWhite,8.0);
        (this->field16_0x40)._s_0.opening_vo = true;
      }
      goto LAB_00429c8b;
    }
  }
  else {
LAB_00429c8b:
    if (((((this->field16_0x40)._s_0.start_done != false) &&
         (fVar8 = Get_Time(), (this->field17_0x16c)._s_0.patrol2_move_time < fVar8)) &&
        ((this->field16_0x40)._s_0.rendezvous == false)) &&
       (((bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol2_1), bVar4 &&
         (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol2_2), bVar4)) &&
        ((this->field16_0x40)._s_0.fighter_moved == false)))) {
      Patrol((this->field18_0x1e4)._s_0.svpatrol2_1,"patrol_path1",1);
      Patrol((this->field18_0x1e4)._s_0.svpatrol2_2,"patrol_path1",1);
      (this->field16_0x40)._s_0.fighter_moved = true;
    }
  }
  if ((this->field16_0x40)._s_0.first_objective == false) {
    fVar8 = Get_Time();
    if (fVar8 <= (this->field17_0x16c)._s_0.rendezous_check) {
LAB_00429ec2:
      if ((this->field16_0x40)._s_0.rendezvous != false) goto LAB_00429ec7;
    }
    else {
      if ((this->field16_0x40)._s_0.rendezvous == false) {
        if ((this->field16_0x40)._s_0.alarm_on == false) {
          fVar8 = Get_Time();
          piVar1 = &(this->field18_0x1e4)._s_0.wingtank2;
          (this->field17_0x16c)._s_0.rendezous_check = fVar8 + 3.0;
          bVar4 = IsAlive(piVar1);
          if (((!bVar4) ||
              (fVar8 = GetDistance((this->field18_0x1e4)._s_0.user,*piVar1), 150.0 <= fVar8)) ||
             ((this->field16_0x40)._s_0.rendezvous != false)) {
            bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.wingtank3);
            if ((!bVar4) ||
               (fVar8 = GetDistance((this->field18_0x1e4)._s_0.user,
                                    (this->field18_0x1e4)._s_0.wingtank3), 150.0 <= fVar8))
            goto LAB_00429ec2;
            if ((this->field16_0x40)._s_0.rendezvous != false) goto LAB_00429ec7;
          }
          iVar5 = AudioMessage("misn0701.wav");
          (this->field20_0x6cc)._s_0.audmsg = iVar5;
          bVar4 = IsAlive(piVar1);
          if (bVar4) {
            iVar5 = BuildObject("avtank",1,*piVar1);
            (this->field18_0x1e4)._s_0.new_tank1 = iVar5;
            RemoveObject(*piVar1);
          }
          piVar1 = &(this->field18_0x1e4)._s_0.wingtank3;
          bVar4 = IsAlive(piVar1);
          if (bVar4) {
            iVar5 = BuildObject("avtank",1,*piVar1);
            (this->field18_0x1e4)._s_0.new_tank2 = iVar5;
            RemoveObject(*piVar1);
          }
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misn0700.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn0701.otf",DisplayInterface::colorWhite,8.0);
          fVar8 = Get_Time();
          (this->field17_0x16c)._s_0.recon_message_time = fVar8 + 240.0;
          fVar8 = Get_Time();
          (this->field17_0x16c)._s_0.runner_check = fVar8 + 6.0;
          fVar8 = Get_Time();
          (this->field17_0x16c)._s_0.patrol2_move_time = fVar8 + 60.0;
          iVar5 = BuildObject("apcamr",1,"cam1_spawn",0);
          (this->field18_0x1e4)._s_0.nav1 = iVar5;
          SetObjectiveName(iVar5,"CCA Outpost");
          fVar8 = Get_Time();
          (this->field16_0x40)._s_0.rendezvous = true;
          (this->field17_0x16c)._s_0.tower_check = fVar8 + 10.0;
        }
        goto LAB_00429ec2;
      }
LAB_00429ec7:
      fVar8 = Get_Time();
      if (((this->field17_0x16c)._s_0.patrol2_move_time < fVar8) &&
         ((this->field16_0x40)._s_0.fighter_moved == false)) {
        iVar5 = (this->field18_0x1e4)._s_0.svpatrol2_1;
        if (iVar5 != 0) {
          Attack(iVar5,(this->field18_0x1e4)._s_0.user,1);
        }
        iVar5 = (this->field18_0x1e4)._s_0.svpatrol2_2;
        if (iVar5 != 0) {
          Attack(iVar5,(this->field18_0x1e4)._s_0.user,1);
        }
        (this->field16_0x40)._s_0.fighter_moved = true;
      }
    }
    piVar1 = &(this->field18_0x1e4)._s_0.nav1;
    bVar4 = IsAlive(piVar1);
    if (((bVar4) && (fVar8 = Get_Time(), (this->field17_0x16c)._s_0.tower_check < fVar8)) &&
       ((this->field16_0x40)._s_0.tower_warning == false)) {
      fVar8 = Get_Time();
      iVar5 = *piVar1;
      iVar7 = (this->field18_0x1e4)._s_0.user;
      (this->field17_0x16c)._s_0.tower_check = fVar8 + 4.0;
      fVar8 = GetDistance(iVar7,iVar5);
      if (fVar8 < 90.0) {
        AudioMessage("misn0716.wav");
        (this->field16_0x40)._s_0.tower_warning = true;
      }
    }
    if ((((this->field16_0x40)._s_0.first_objective == false) &&
        ((this->field16_0x40)._s_0.alarm_on == false)) &&
       ((this->field16_0x40)._s_0.out_of_car == false)) {
      if ((this->field16_0x40)._s_0.rendezvous == false) {
LAB_0042a087:
        if ((this->field16_0x40)._s_0.jump_cam_spawned != false) goto LAB_0042a08c;
LAB_0042a0d4:
        if ((this->field16_0x40)._s_0.rookie_moved != false) goto LAB_0042a0dd;
LAB_0042a163:
        if ((this->field16_0x40)._s_0.rookie_found == false) goto LAB_0042a1b0;
      }
      else {
        if ((this->field16_0x40)._s_0.jump_cam_spawned == false) {
          fVar8 = Get_Time();
          if (((this->field17_0x16c)._s_0.recon_message_time < fVar8) ||
             ((this->field16_0x40)._s_0.tower_warning != false)) {
            fVar8 = Get_Time();
            (this->field17_0x16c)._s_0.recon_message_time = fVar8 + 5.0;
            iVar7 = CountUnitsNearObject((this->field18_0x1e4)._s_0.user,200.0,2,"svfigh");
            iVar5 = (this->field18_0x1e4)._s_0.jump_geyz;
            (this->field20_0x6cc)._s_0.units = iVar7;
            fVar8 = GetDistance((this->field18_0x1e4)._s_0.user,iVar5);
            if ((400.0 < fVar8) && ((this->field20_0x6cc)._s_0.units == 0)) {
              AudioMessage("misn0702.wav");
              iVar5 = BuildObject("apcamr",1,"jump_cam_spawn",0);
              (this->field18_0x1e4)._s_0.jump_cam = iVar5;
              iVar5 = BuildObject("avfigh",1,(this->field18_0x1e4)._s_0.jump_geyz);
              (this->field18_0x1e4)._s_0.rookie = iVar5;
              Follow(iVar5,(this->field18_0x1e4)._s_0.jump_geyz,1);
              fVar8 = Get_Time();
              (this->field16_0x40)._s_0.jump_cam_spawned = true;
              (this->field17_0x16c)._s_0.rookie_move_time = fVar8 + 10.0;
            }
          }
          goto LAB_0042a087;
        }
LAB_0042a08c:
        iVar5 = (this->field18_0x1e4)._s_0.jump_cam;
        if (iVar5 != 0) {
          SetObjectiveName(iVar5,"Volcano Peak");
        }
        if (((this->field16_0x40)._s_0.jump_cam_spawned == false) ||
           (fVar8 = Get_Time(), fVar8 <= (this->field17_0x16c)._s_0.rookie_move_time))
        goto LAB_0042a0d4;
        if ((this->field16_0x40)._s_0.rookie_moved == false) {
          fVar8 = Get_Time();
          (this->field16_0x40)._s_0.rookie_moved = true;
          (this->field17_0x16c)._s_0.rookie_remove_time = fVar8 + 10.0;
          goto LAB_0042a0d4;
        }
LAB_0042a0dd:
        fVar8 = Get_Time();
        if (fVar8 <= (this->field17_0x16c)._s_0.rookie_remove_time) goto LAB_0042a163;
        if ((this->field16_0x40)._s_0.rookie_found == false) {
          fVar8 = Get_Time();
          piVar1 = &(this->field18_0x1e4)._s_0.rookie;
          (this->field17_0x16c)._s_0.rookie_remove_time = fVar8 + 3.0;
          bVar4 = IsAlive(piVar1);
          if ((bVar4) &&
             (fVar8 = GetDistance((this->field18_0x1e4)._s_0.user,*piVar1), fVar8 < 70.0)) {
            Defend(*piVar1,1);
            AudioMessage("misn0718.wav");
            fVar8 = Get_Time();
            (this->field16_0x40)._s_0.rookie_found = true;
            (this->field17_0x16c)._s_0.rookie_remove_time = fVar8 + 10.0;
          }
          goto LAB_0042a163;
        }
      }
      fVar8 = Get_Time();
      if (((this->field17_0x16c)._s_0.rookie_remove_time < fVar8) &&
         ((this->field16_0x40)._s_0.rookie_removed == false)) {
        piVar1 = &(this->field18_0x1e4)._s_0.rookie;
        bVar4 = IsAlive(piVar1);
        if (bVar4) {
          AudioMessage("misn0715.wav");
          EjectPilot(*piVar1);
          (this->field16_0x40)._s_0.rookie_removed = true;
        }
      }
    }
  }
LAB_0042a1b0:
  fVar8 = Get_Time();
  if (((this->field17_0x16c)._s_0.alarm_check < fVar8) &&
     ((this->field16_0x40)._s_0.alarm_on == false)) {
    fVar8 = Get_Time();
    (this->field17_0x16c)._s_0.alarm_check = fVar8 + 5.0;
    if (((this->field16_0x40)._s_0.alarm_on == false) &&
       (((this->field16_0x40)._s_0.out_of_car == false &&
        (fVar8 = GetDistance((this->field18_0x1e4)._s_0.user,(this->field19_0x508)._s_0.turret1_spot
                             ,0), fVar8 < 70.0)))) {
      AudioMessage("misn0710.wav");
      piVar1 = &(this->field18_0x1e4)._s_0.ccacomtower;
      SetObjectiveOn(*piVar1);
      SetObjectiveName(*piVar1,"Radar Array");
      (this->field16_0x40)._s_0.alarm_on = true;
    }
  }
  if ((this->field16_0x40)._s_0.first_objective == false) {
    if ((this->field16_0x40)._s_0.alarm_on != false) {
      piVar1 = &(this->field18_0x1e4)._s_0.ccacomtower;
      if (((*piVar1 != 0) &&
          (fVar8 = GetDistance((this->field18_0x1e4)._s_0.user,*piVar1), fVar8 < 170.0)) &&
         ((this->field16_0x40)._s_0.alarm_sound == false)) {
        AudioMessage("misn0708.wav");
        fVar8 = Get_Time();
        (this->field16_0x40)._s_0.alarm_sound = true;
        (this->field17_0x16c)._s_0.alarm_timer = fVar8 + 6.0;
      }
      pbVar2 = &(this->field16_0x40)._s_0.alarm_sound;
      if ((*pbVar2 != false) && (fVar8 = Get_Time(), (this->field17_0x16c)._s_0.alarm_timer < fVar8)
         ) {
        *pbVar2 = false;
      }
      if ((this->field16_0x40)._s_0.turret_move == false) {
        SetObjectiveOn(*piVar1);
        SetObjectiveName(*piVar1,"Radar Array");
        Retreat((this->field18_0x1e4)._s_0.guard_turret1,*piVar1,1);
        Retreat((this->field18_0x1e4)._s_0.guard_turret2,*piVar1,1);
        (this->field16_0x40)._s_0.turret_move = true;
      }
      if ((this->field16_0x40)._s_0.start_evac == false) {
        fVar8 = Get_Time();
        (this->field16_0x40)._s_0.start_evac = true;
        (this->field17_0x16c)._s_0.unit_spawn_time = fVar8 + 20.0;
      }
      if ((this->field16_0x40)._s_0.start_evac == false) {
LAB_0042a577:
        if ((this->field16_0x40)._s_0.unit_spawn != false) goto LAB_0042a580;
      }
      else {
        fVar8 = Get_Time();
        if ((((this->field17_0x16c)._s_0.unit_spawn_time < fVar8) &&
            ((this->field16_0x40)._s_0.unit_spawn == false)) &&
           ((this->field16_0x40)._s_0.alarm_special == false)) {
          iVar5 = BuildObject("sspilo",2,"hut2_spawn",0);
          (this->field18_0x1e4)._s_0.pilot1 = iVar5;
          iVar5 = BuildObject("sspilo",2,"hut2_spawn",0);
          (this->field18_0x1e4)._s_0.pilot2 = iVar5;
          iVar5 = BuildObject("sspilo",2,"hut2_spawn",0);
          (this->field18_0x1e4)._s_0.pilot3 = iVar5;
          iVar5 = BuildObject("sspilo",2,"hut1_spawn",0);
          (this->field18_0x1e4)._s_0.pilot4 = iVar5;
          iVar5 = BuildObject("sspilo",2,"hut1_spawn",0);
          (this->field18_0x1e4)._s_0.pilot5 = iVar5;
          iVar5 = (this->field18_0x1e4)._s_0.parkturret1;
          if (iVar5 != (this->field18_0x1e4)._s_0.user) {
            iVar5 = BuildObject("svturr",2,iVar5);
            (this->field18_0x1e4)._s_0.spawn_turret1 = iVar5;
            Defend(iVar5,1);
            RemoveObject((this->field18_0x1e4)._s_0.parkturret1);
          }
          iVar5 = (this->field18_0x1e4)._s_0.parkturret2;
          if (iVar5 != (this->field18_0x1e4)._s_0.user) {
            iVar5 = BuildObject("svturr",2,iVar5);
            (this->field18_0x1e4)._s_0.spawn_turret2 = iVar5;
            Defend(iVar5,1);
            RemoveObject((this->field18_0x1e4)._s_0.parkturret2);
          }
          iVar5 = (this->field18_0x1e4)._s_0.parked1;
          if (iVar5 != 0) {
            Retreat((this->field18_0x1e4)._s_0.pilot1,iVar5,1);
          }
          iVar5 = (this->field18_0x1e4)._s_0.parked2;
          if (iVar5 != 0) {
            Retreat((this->field18_0x1e4)._s_0.pilot2,iVar5,1);
          }
          iVar5 = (this->field18_0x1e4)._s_0.parked3;
          if (iVar5 != 0) {
            Retreat((this->field18_0x1e4)._s_0.pilot3,iVar5,1);
          }
          (this->field16_0x40)._s_0.unit_spawn = true;
        }
        if ((((this->field16_0x40)._s_0.start_evac == false) ||
            ((this->field16_0x40)._s_0.alarm_special == false)) ||
           (fVar8 = Get_Time(), fVar8 <= (this->field17_0x16c)._s_0.unit_spawn_time))
        goto LAB_0042a577;
        if ((this->field16_0x40)._s_0.unit_spawn == false) {
          iVar5 = BuildObject("sspilo",2,"hut2_spawn",0);
          (this->field18_0x1e4)._s_0.pilot1 = iVar5;
          iVar5 = BuildObject("sspilo",2,"hut2_spawn",0);
          (this->field18_0x1e4)._s_0.pilot2 = iVar5;
          iVar5 = BuildObject("sssold",2,"hut2_spawn",0);
          (this->field18_0x1e4)._s_0.pilot3 = iVar5;
          iVar5 = BuildObject("sspilo",2,"hut1_spawn",0);
          (this->field18_0x1e4)._s_0.pilot4 = iVar5;
          iVar5 = BuildObject("sssold",2,"hut1_spawn",0);
          (this->field18_0x1e4)._s_0.pilot5 = iVar5;
          Attack((this->field18_0x1e4)._s_0.pilot3,(this->field18_0x1e4)._s_0.user,1);
          Attack((this->field18_0x1e4)._s_0.pilot5,(this->field18_0x1e4)._s_0.user,1);
          iVar5 = (this->field18_0x1e4)._s_0.parked1;
          if (iVar5 != 0) {
            Retreat((this->field18_0x1e4)._s_0.pilot1,iVar5,1);
          }
          iVar5 = (this->field18_0x1e4)._s_0.parked2;
          if (iVar5 != 0) {
            Retreat((this->field18_0x1e4)._s_0.pilot2,iVar5,1);
          }
          if ((this->field18_0x1e4)._s_0.parked3 != 0) {
            Retreat((this->field18_0x1e4)._s_0.pilot4,(this->field18_0x1e4)._s_0.parkturret1,1);
          }
          (this->field16_0x40)._s_0.unit_spawn = true;
          goto LAB_0042a577;
        }
LAB_0042a580:
        if ((this->field16_0x40)._s_0.alarm_special == false) {
          bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.pilot1);
          if ((!bVar4) && (iVar5 = (this->field18_0x1e4)._s_0.parked1, iVar5 != 0)) {
            Attack(iVar5,(this->field18_0x1e4)._s_0.user,1);
          }
          bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.pilot2);
          if ((!bVar4) && (iVar5 = (this->field18_0x1e4)._s_0.parked2, iVar5 != 0)) {
            Attack(iVar5,(this->field18_0x1e4)._s_0.user,1);
          }
          bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.pilot3);
          if ((!bVar4) && (iVar5 = (this->field18_0x1e4)._s_0.parked3, iVar5 != 0)) {
            Attack(iVar5,(this->field18_0x1e4)._s_0.user,1);
          }
        }
        if (((this->field16_0x40)._s_0.unit_spawn != false) &&
           ((this->field16_0x40)._s_0.alarm_special != false)) {
          bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.pilot1);
          if ((!bVar4) && (iVar5 = (this->field18_0x1e4)._s_0.parked1, iVar5 != 0)) {
            Goto(iVar5,(this->field18_0x1e4)._s_0.ccacomtower,1);
          }
          bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.pilot2);
          if ((!bVar4) && (iVar5 = (this->field18_0x1e4)._s_0.parked2, iVar5 != 0)) {
            Goto(iVar5,(this->field18_0x1e4)._s_0.ccacomtower,1);
          }
          bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.pilot4);
          if ((!bVar4) && (iVar5 = (this->field18_0x1e4)._s_0.parkturret1, iVar5 != 0)) {
            Retreat(iVar5,"turret1_spot",1);
          }
        }
      }
      piVar1 = &(this->field18_0x1e4)._s_0.ccacomtower;
      bVar4 = IsAlive(piVar1);
      if (((bVar4) && (fVar8 = GetHealth(*piVar1), fVar8 < 0.5)) &&
         ((this->field16_0x40)._s_0.forces_enroute == false)) {
        piVar3 = &(this->field18_0x1e4)._s_0.svpatrol1_2;
        bVar4 = IsAlive(piVar3);
        if (bVar4) {
          Goto(*piVar3,*piVar1,1);
        }
        piVar3 = &(this->field18_0x1e4)._s_0.svpatrol3_1;
        bVar4 = IsAlive(piVar3);
        if (bVar4) {
          Goto(*piVar3,*piVar1,1);
        }
        piVar3 = &(this->field18_0x1e4)._s_0.svpatrol4_1;
        bVar4 = IsAlive(piVar3);
        if (bVar4) {
          Goto(*piVar3,*piVar1,1);
        }
        (this->field16_0x40)._s_0.forces_enroute = true;
      }
    }
    if ((this->field16_0x40)._s_0.first_objective == false) {
      if ((this->field16_0x40)._s_0.alarm_on == false) {
        if ((this->field16_0x40)._s_0.out_of_car == false) {
          fVar8 = GetDistance((this->field18_0x1e4)._s_0.user,
                              (this->field18_0x1e4)._s_0.camera_geyser);
          if (fVar8 < 160.0) {
            piVar1 = &(this->field18_0x1e4)._s_0.ccacomtower;
            SetObjectiveOn(*piVar1);
            SetObjectiveName(*piVar1,"Radar Array");
            (this->field16_0x40)._s_0.out_of_car = true;
          }
          goto LAB_0042a78f;
        }
LAB_0042a794:
        bVar4 = IsOdf((this->field18_0x1e4)._s_0.user,"svtank");
        if ((bVar4) ||
           (((this->field16_0x40)._s_0.out_of_car != false &&
            ((bVar4 = IsOdf((this->field18_0x1e4)._s_0.user,"svfigh"), bVar4 ||
             ((((this->field16_0x40)._s_0.out_of_car != false &&
               (bVar4 = IsOdf((this->field18_0x1e4)._s_0.user,"svturr"), bVar4)) &&
              ((this->field16_0x40)._s_0.vehicle_stolen == false)))))))) {
          (this->field16_0x40)._s_0.vehicle_stolen = true;
        }
      }
      else {
LAB_0042a78f:
        if ((this->field16_0x40)._s_0.out_of_car != false) goto LAB_0042a794;
      }
      if ((((this->field16_0x40)._s_0.trigger1 == false) &&
          ((this->field16_0x40)._s_0.out_of_car != false)) &&
         ((((bVar4 = IsDamaged((this->field18_0x1e4)._s_0.ccaguntower1,0.95), bVar4 ||
            ((((((bVar4 = IsDamaged((this->field18_0x1e4)._s_0.ccaguntower2,0.95), bVar4 ||
                 (bVar4 = IsDamaged((this->field18_0x1e4)._s_0.ccacomtower,0.95), bVar4)) ||
                (bVar4 = IsDamaged((this->field18_0x1e4)._s_0.powrplnt1,0.95), bVar4)) ||
               ((bVar4 = IsDamaged((this->field18_0x1e4)._s_0.barrack1,0.95), bVar4 ||
                (bVar4 = IsDamaged((this->field18_0x1e4)._s_0.barrack2,0.95), bVar4)))) ||
              (bVar4 = IsDamaged((this->field18_0x1e4)._s_0.parked1,0.95), bVar4)) ||
             ((bVar4 = IsDamaged((this->field18_0x1e4)._s_0.parked2,0.95), bVar4 ||
              (bVar4 = IsDamaged((this->field18_0x1e4)._s_0.parked3,0.95), bVar4)))))) ||
           (bVar4 = IsDamaged((this->field18_0x1e4)._s_0.parkturret1,0.95), bVar4)) ||
          (bVar4 = IsDamaged((this->field18_0x1e4)._s_0.parkturret2,0.95), bVar4)))) {
        (this->field16_0x40)._s_0.trigger1 = true;
      }
      bVar4 = (this->field16_0x40)._s_0.trigger1;
      if (bVar4 != false) {
        if (((this->field16_0x40)._s_0.vehicle_stolen != false) &&
           ((this->field16_0x40)._s_0.alarm_on == false)) {
          (this->field16_0x40)._s_0.alarm_on = true;
        }
        if (((bVar4 != false) && ((this->field16_0x40)._s_0.vehicle_stolen == false)) &&
           ((this->field16_0x40)._s_0.alarm_on == false)) {
          (this->field16_0x40)._s_0.alarm_on = true;
          (this->field16_0x40)._s_0.alarm_special = true;
        }
      }
      if ((this->field16_0x40)._s_0.first_objective == false) {
        if ((this->field16_0x40)._s_0.alarm_on == false) {
          if (((this->field16_0x40)._s_0.out_of_car == false) &&
             (fVar8 = GetDistance((this->field18_0x1e4)._s_0.wingman1,
                                  (this->field19_0x508)._s_0.turret1_spot,0), fVar8 < 100.0)) {
            AudioMessage("misn0709.wav");
            (this->field16_0x40)._s_0.alarm_on = true;
          }
          if ((this->field16_0x40)._s_0.alarm_on == false) {
            if (((this->field16_0x40)._s_0.out_of_car == false) &&
               (fVar8 = GetDistance((this->field18_0x1e4)._s_0.wingman2,
                                    (this->field19_0x508)._s_0.turret1_spot,0), fVar8 < 100.0)) {
              AudioMessage("misn0709.wav");
              (this->field16_0x40)._s_0.alarm_on = true;
            }
            if ((this->field16_0x40)._s_0.alarm_on == false) {
              if (((this->field16_0x40)._s_0.out_of_car == false) &&
                 (fVar8 = GetDistance((this->field18_0x1e4)._s_0.wingtank1,
                                      (this->field19_0x508)._s_0.turret1_spot,0), fVar8 < 100.0)) {
                AudioMessage("misn0709.wav");
                (this->field16_0x40)._s_0.alarm_on = true;
              }
              if ((this->field16_0x40)._s_0.alarm_on == false) {
                if (((this->field16_0x40)._s_0.out_of_car == false) &&
                   (fVar8 = GetDistance((this->field18_0x1e4)._s_0.new_tank1,
                                        (this->field19_0x508)._s_0.turret1_spot,0), fVar8 < 100.0))
                {
                  AudioMessage("misn0709.wav");
                  (this->field16_0x40)._s_0.alarm_on = true;
                }
                if ((((this->field16_0x40)._s_0.alarm_on == false) &&
                    ((this->field16_0x40)._s_0.out_of_car == false)) &&
                   (fVar8 = GetDistance((this->field18_0x1e4)._s_0.new_tank2,
                                        (this->field19_0x508)._s_0.turret1_spot,0), fVar8 < 100.0))
                {
                  AudioMessage("misn0709.wav");
                  (this->field16_0x40)._s_0.alarm_on = true;
                }
              }
            }
          }
        }
        if ((this->field16_0x40)._s_0.first_objective == false) {
          if ((this->field16_0x40)._s_0.retreat_success == false) {
            bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol1_2);
            if (((bVar4) && (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol1_1), !bVar4)) &&
               ((this->field16_0x40)._s_0.rendezvous != false)) {
              piVar1 = &(this->field18_0x1e4)._s_0.ccarecycle;
              bVar4 = IsAlive(piVar1);
              if (((bVar4) && ((this->field16_0x40)._s_0.first_objective == false)) &&
                 (((this->field16_0x40)._s_0.mine_pathed == false &&
                  (((((this->field16_0x40)._s_0.alarm_on == false &&
                     (fVar8 = GetDistance((this->field18_0x1e4)._s_0.user,
                                          (this->field18_0x1e4)._s_0.svpatrol1_2), fVar8 < 50.0)) &&
                    ((this->field16_0x40)._s_0.p1_retreat == false)) &&
                   (((this->field16_0x40)._s_0.p2_retreat == false &&
                    ((this->field16_0x40)._s_0.p3_retreat == false)))))))) {
                Retreat((this->field18_0x1e4)._s_0.svpatrol1_2,*piVar1,1);
                piVar1 = &(this->field18_0x1e4)._s_0.svpatrol1_2;
                SetObjectiveOn(*piVar1);
                SetObjectiveName(*piVar1,"Runner");
                fVar8 = Get_Time();
                (this->field16_0x40)._s_0.p1_retreat = true;
                (this->field17_0x16c)._s_0.getaway_message_time = fVar8 + 3.0;
              }
            }
            bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol1_1);
            if (((bVar4) && (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol1_2), !bVar4)) &&
               ((this->field16_0x40)._s_0.rendezvous != false)) {
              piVar1 = &(this->field18_0x1e4)._s_0.ccarecycle;
              bVar4 = IsAlive(piVar1);
              if ((((bVar4) && ((this->field16_0x40)._s_0.first_objective == false)) &&
                  ((this->field16_0x40)._s_0.mine_pathed == false)) &&
                 ((((this->field16_0x40)._s_0.alarm_on == false &&
                   (fVar8 = GetDistance((this->field18_0x1e4)._s_0.user,
                                        (this->field18_0x1e4)._s_0.svpatrol1_1), fVar8 < 50.0)) &&
                  (((this->field16_0x40)._s_0.p1_retreat == false &&
                   (((this->field16_0x40)._s_0.p2_retreat == false &&
                    ((this->field16_0x40)._s_0.p3_retreat == false)))))))) {
                Retreat((this->field18_0x1e4)._s_0.svpatrol1_1,*piVar1,1);
                piVar1 = &(this->field18_0x1e4)._s_0.svpatrol1_1;
                SetObjectiveOn(*piVar1);
                SetObjectiveName(*piVar1,"Runner");
                fVar8 = Get_Time();
                (this->field16_0x40)._s_0.p1_retreat = true;
                (this->field17_0x16c)._s_0.getaway_message_time = fVar8 + 3.0;
              }
            }
            bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol3_2);
            if (((bVar4) && (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol3_1), !bVar4)) &&
               ((this->field16_0x40)._s_0.rendezvous != false)) {
              piVar1 = &(this->field18_0x1e4)._s_0.ccarecycle;
              bVar4 = IsAlive(piVar1);
              if ((((bVar4) && ((this->field16_0x40)._s_0.first_objective == false)) &&
                  (((this->field16_0x40)._s_0.mine_pathed == false &&
                   (((this->field16_0x40)._s_0.alarm_on == false &&
                    (fVar8 = GetDistance((this->field18_0x1e4)._s_0.user,
                                         (this->field18_0x1e4)._s_0.svpatrol3_2), fVar8 < 50.0))))))
                 && (((this->field16_0x40)._s_0.p2_retreat == false &&
                     (((this->field16_0x40)._s_0.p1_retreat == false &&
                      ((this->field16_0x40)._s_0.p3_retreat == false)))))) {
                Retreat((this->field18_0x1e4)._s_0.svpatrol3_2,*piVar1,1);
                piVar1 = &(this->field18_0x1e4)._s_0.svpatrol3_2;
                SetObjectiveOn(*piVar1);
                SetObjectiveName(*piVar1,"Runner");
                fVar8 = Get_Time();
                (this->field16_0x40)._s_0.p3_retreat = true;
                (this->field17_0x16c)._s_0.getaway_message_time = fVar8 + 3.0;
              }
            }
            bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol3_1);
            if (((bVar4) && (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol3_2), !bVar4)) &&
               ((this->field16_0x40)._s_0.rendezvous != false)) {
              piVar1 = &(this->field18_0x1e4)._s_0.ccarecycle;
              bVar4 = IsAlive(piVar1);
              if (((((bVar4) && ((this->field16_0x40)._s_0.first_objective == false)) &&
                   (((this->field16_0x40)._s_0.mine_pathed == false &&
                    (((this->field16_0x40)._s_0.alarm_on == false &&
                     (fVar8 = GetDistance((this->field18_0x1e4)._s_0.user,
                                          (this->field18_0x1e4)._s_0.svpatrol3_1), fVar8 < 50.0)))))
                   ) && ((this->field16_0x40)._s_0.p2_retreat == false)) &&
                 (((this->field16_0x40)._s_0.p1_retreat == false &&
                  ((this->field16_0x40)._s_0.p3_retreat == false)))) {
                Retreat((this->field18_0x1e4)._s_0.svpatrol3_1,*piVar1,1);
                piVar1 = &(this->field18_0x1e4)._s_0.svpatrol3_1;
                SetObjectiveOn(*piVar1);
                SetObjectiveName(*piVar1,"Runner");
                fVar8 = Get_Time();
                (this->field16_0x40)._s_0.p3_retreat = true;
                (this->field17_0x16c)._s_0.getaway_message_time = fVar8 + 3.0;
              }
            }
            if (((this->field16_0x40)._s_0.retreat_success == false) &&
               ((this->field16_0x40)._s_0.getum == false)) {
              if (((this->field16_0x40)._s_0.p1_retreat != false) &&
                 ((((fVar8 = Get_Time(), (this->field17_0x16c)._s_0.getaway_message_time < fVar8 &&
                    (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.new_tank1), bVar4)) &&
                   ((this->field16_0x40)._s_0.getum == false)) ||
                  ((((this->field16_0x40)._s_0.p1_retreat != false &&
                    (fVar8 = Get_Time(), (this->field17_0x16c)._s_0.getaway_message_time < fVar8))
                   && ((bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.new_tank2), bVar4 &&
                       ((this->field16_0x40)._s_0.getum == false)))))))) {
                AudioMessage("misn0705.wav");
                (this->field16_0x40)._s_0.getum = true;
              }
              if (((this->field16_0x40)._s_0.p2_retreat != false) &&
                 ((((fVar8 = Get_Time(), (this->field17_0x16c)._s_0.getaway_message_time < fVar8 &&
                    (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.new_tank1), bVar4)) &&
                   ((this->field16_0x40)._s_0.getum == false)) ||
                  (((((this->field16_0x40)._s_0.p2_retreat != false &&
                     (fVar8 = Get_Time(), (this->field17_0x16c)._s_0.getaway_message_time < fVar8))
                    && (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.new_tank2), bVar4)) &&
                   ((this->field16_0x40)._s_0.getum == false)))))) {
                AudioMessage("misn0705.wav");
                (this->field16_0x40)._s_0.getum = true;
              }
              if (((this->field16_0x40)._s_0.p3_retreat != false) &&
                 ((((fVar8 = Get_Time(), (this->field17_0x16c)._s_0.getaway_message_time < fVar8 &&
                    (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.new_tank1), bVar4)) &&
                   ((this->field16_0x40)._s_0.getum == false)) ||
                  ((((this->field16_0x40)._s_0.p3_retreat != false &&
                    (fVar8 = Get_Time(), (this->field17_0x16c)._s_0.getaway_message_time < fVar8))
                   && ((bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.new_tank2), bVar4 &&
                       ((this->field16_0x40)._s_0.getum == false)))))))) {
                AudioMessage("misn0705.wav");
                (this->field16_0x40)._s_0.getum = true;
              }
            }
            if ((this->field16_0x40)._s_0.p1_retreat != false) {
              bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol1_1);
              if (bVar4) {
                (this->field16_0x40)._s_0.patrola1 = true;
              }
              if (((this->field16_0x40)._s_0.p1_retreat != false) &&
                 (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol1_2), bVar4)) {
                (this->field16_0x40)._s_0.patrola2 = true;
              }
            }
            if ((this->field16_0x40)._s_0.p2_retreat != false) {
              bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol2_1);
              if (bVar4) {
                (this->field16_0x40)._s_0.patrolb1 = true;
              }
              if (((this->field16_0x40)._s_0.p2_retreat != false) &&
                 (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol2_2), bVar4)) {
                (this->field16_0x40)._s_0.patrolb2 = true;
              }
            }
            if ((this->field16_0x40)._s_0.p3_retreat != false) {
              bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol3_1);
              if (bVar4) {
                (this->field16_0x40)._s_0.patrolc1 = true;
              }
              if (((this->field16_0x40)._s_0.p3_retreat != false) &&
                 (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol3_2), bVar4)) {
                (this->field16_0x40)._s_0.patrolc2 = true;
              }
            }
            if ((this->field16_0x40)._s_0.p1_retreat != false) {
              if ((((this->field16_0x40)._s_0.patrola1 == false) ||
                  (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol1_1), bVar4)) ||
                 (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.new_tank1), !bVar4)) {
                if ((this->field16_0x40)._s_0.p1_retreat == false) goto LAB_0042b066;
                if ((((this->field16_0x40)._s_0.patrola1 != false) &&
                    (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol1_1), !bVar4)) &&
                   (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.new_tank2), bVar4))
                goto LAB_0042afee;
              }
              else {
LAB_0042afee:
                AudioMessage("misn0706.wav");
                (this->field16_0x40)._s_0.p1_retreat = false;
                (this->field16_0x40)._s_0.patrola1 = false;
                (this->field16_0x40)._s_0.getum = false;
              }
              if (((this->field16_0x40)._s_0.p1_retreat != false) &&
                 (((((this->field16_0x40)._s_0.patrola2 != false &&
                    (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol1_2), !bVar4)) &&
                   (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.new_tank1), bVar4)) ||
                  (((((this->field16_0x40)._s_0.p1_retreat != false &&
                     ((this->field16_0x40)._s_0.patrola2 != false)) &&
                    (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol1_2), !bVar4)) &&
                   (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.new_tank2), bVar4)))))) {
                AudioMessage("misn0706.wav");
                (this->field16_0x40)._s_0.p1_retreat = false;
                (this->field16_0x40)._s_0.patrola2 = false;
                (this->field16_0x40)._s_0.getum = false;
              }
            }
LAB_0042b066:
            if ((this->field16_0x40)._s_0.p2_retreat != false) {
              if ((((this->field16_0x40)._s_0.patrolb1 == false) ||
                  (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol2_1), bVar4)) ||
                 (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.new_tank1), !bVar4)) {
                if ((this->field16_0x40)._s_0.p2_retreat == false) goto LAB_0042b13e;
                if ((((this->field16_0x40)._s_0.patrolb1 != false) &&
                    (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol2_1), !bVar4)) &&
                   (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.new_tank2), bVar4))
                goto LAB_0042b0c6;
              }
              else {
LAB_0042b0c6:
                AudioMessage("misn0706.wav");
                (this->field16_0x40)._s_0.p2_retreat = false;
                (this->field16_0x40)._s_0.patrolb1 = false;
                (this->field16_0x40)._s_0.getum = false;
              }
              if (((this->field16_0x40)._s_0.p2_retreat != false) &&
                 (((((this->field16_0x40)._s_0.patrolb2 != false &&
                    (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol2_2), !bVar4)) &&
                   (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.new_tank1), bVar4)) ||
                  ((((this->field16_0x40)._s_0.p2_retreat != false &&
                    ((this->field16_0x40)._s_0.patrolb2 != false)) &&
                   ((bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol2_2), !bVar4 &&
                    (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.new_tank2), bVar4)))))))) {
                AudioMessage("misn0706.wav");
                (this->field16_0x40)._s_0.p2_retreat = false;
                (this->field16_0x40)._s_0.patrolb2 = false;
                (this->field16_0x40)._s_0.getum = false;
              }
            }
LAB_0042b13e:
            if ((this->field16_0x40)._s_0.p3_retreat != false) {
              if ((((this->field16_0x40)._s_0.patrolc1 == false) ||
                  (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol3_1), bVar4)) ||
                 (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.new_tank1), !bVar4)) {
                if ((this->field16_0x40)._s_0.p3_retreat == false) goto LAB_0042b216;
                if ((((this->field16_0x40)._s_0.patrolc1 != false) &&
                    (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol3_1), !bVar4)) &&
                   (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.new_tank2), bVar4))
                goto LAB_0042b19e;
              }
              else {
LAB_0042b19e:
                AudioMessage("misn0706.wav");
                (this->field16_0x40)._s_0.p3_retreat = false;
                (this->field16_0x40)._s_0.patrolc1 = false;
                (this->field16_0x40)._s_0.getum = false;
              }
              if (((this->field16_0x40)._s_0.p3_retreat != false) &&
                 (((((this->field16_0x40)._s_0.patrolc2 != false &&
                    (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol3_2), !bVar4)) &&
                   (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.new_tank1), bVar4)) ||
                  ((((this->field16_0x40)._s_0.p3_retreat != false &&
                    ((this->field16_0x40)._s_0.patrolc2 != false)) &&
                   ((bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol3_2), !bVar4 &&
                    (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.new_tank2), bVar4)))))))) {
                AudioMessage("misn0706.wav");
                (this->field16_0x40)._s_0.p3_retreat = false;
                (this->field16_0x40)._s_0.patrolc2 = false;
                (this->field16_0x40)._s_0.getum = false;
              }
            }
          }
LAB_0042b216:
          if ((((this->field16_0x40)._s_0.patrola1 != false) &&
              ((this->field16_0x40)._s_0.retreat_success == false)) &&
             ((this->field16_0x40)._s_0.alarm_on == false)) {
            piVar1 = &(this->field18_0x1e4)._s_0.ccarecycle;
            fVar8 = GetDistance((this->field18_0x1e4)._s_0.svpatrol1_1,*piVar1);
            if (((fVar8 < 100.0) && (*piVar1 != 0)) && (bVar4 = IsAlive(piVar1), bVar4)) {
              SetObjectiveOff((this->field18_0x1e4)._s_0.svpatrol1_1);
              (this->field16_0x40)._s_0.retreat_success = true;
            }
          }
          if ((((this->field16_0x40)._s_0.patrola2 != false) &&
              ((this->field16_0x40)._s_0.retreat_success == false)) &&
             ((this->field16_0x40)._s_0.alarm_on == false)) {
            piVar1 = &(this->field18_0x1e4)._s_0.ccarecycle;
            fVar8 = GetDistance((this->field18_0x1e4)._s_0.svpatrol1_2,*piVar1);
            if (((fVar8 < 100.0) && (*piVar1 != 0)) && (bVar4 = IsAlive(piVar1), bVar4)) {
              SetObjectiveOff((this->field18_0x1e4)._s_0.svpatrol1_2);
              (this->field16_0x40)._s_0.retreat_success = true;
            }
          }
          if ((((this->field16_0x40)._s_0.patrolb1 != false) &&
              ((this->field16_0x40)._s_0.retreat_success == false)) &&
             ((this->field16_0x40)._s_0.alarm_on == false)) {
            piVar1 = &(this->field18_0x1e4)._s_0.ccarecycle;
            fVar8 = GetDistance((this->field18_0x1e4)._s_0.svpatrol2_1,*piVar1);
            if (((fVar8 < 100.0) && (*piVar1 != 0)) && (bVar4 = IsAlive(piVar1), bVar4)) {
              SetObjectiveOff((this->field18_0x1e4)._s_0.svpatrol2_1);
              (this->field16_0x40)._s_0.retreat_success = true;
            }
          }
          if ((((this->field16_0x40)._s_0.patrolb2 != false) &&
              ((this->field16_0x40)._s_0.retreat_success == false)) &&
             ((this->field16_0x40)._s_0.alarm_on == false)) {
            piVar1 = &(this->field18_0x1e4)._s_0.ccarecycle;
            fVar8 = GetDistance((this->field18_0x1e4)._s_0.svpatrol2_2,*piVar1);
            if (((fVar8 < 100.0) && (*piVar1 != 0)) && (bVar4 = IsAlive(piVar1), bVar4)) {
              SetObjectiveOff((this->field18_0x1e4)._s_0.svpatrol2_2);
              (this->field16_0x40)._s_0.retreat_success = true;
            }
          }
          if ((((this->field16_0x40)._s_0.patrolc1 != false) &&
              ((this->field16_0x40)._s_0.retreat_success == false)) &&
             ((this->field16_0x40)._s_0.alarm_on == false)) {
            piVar1 = &(this->field18_0x1e4)._s_0.ccarecycle;
            fVar8 = GetDistance((this->field18_0x1e4)._s_0.svpatrol3_1,*piVar1);
            if (((fVar8 < 100.0) && (*piVar1 != 0)) && (bVar4 = IsAlive(piVar1), bVar4)) {
              SetObjectiveOff((this->field18_0x1e4)._s_0.svpatrol3_1);
              (this->field16_0x40)._s_0.retreat_success = true;
            }
          }
          if ((this->field16_0x40)._s_0.patrolc2 == false) {
LAB_0042b3f6:
            if ((this->field16_0x40)._s_0.retreat_success != false) goto LAB_0042b3ff;
          }
          else {
            if ((this->field16_0x40)._s_0.retreat_success == false) {
              if ((this->field16_0x40)._s_0.alarm_on == false) {
                piVar1 = &(this->field18_0x1e4)._s_0.ccarecycle;
                fVar8 = GetDistance((this->field18_0x1e4)._s_0.svpatrol3_2,*piVar1);
                if (((fVar8 < 100.0) && (*piVar1 != 0)) && (bVar4 = IsAlive(piVar1), bVar4)) {
                  SetObjectiveOff((this->field18_0x1e4)._s_0.svpatrol3_2);
                  (this->field16_0x40)._s_0.retreat_success = true;
                }
              }
              goto LAB_0042b3f6;
            }
LAB_0042b3ff:
            bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.new_tank1);
            if ((bVar4) && ((this->field16_0x40)._s_0.detected_message == false)) {
LAB_0042b434:
              AudioMessage("misn0707.wav");
              (this->field16_0x40)._s_0.detected_message = true;
            }
            else {
              if ((this->field16_0x40)._s_0.retreat_success == false) goto LAB_0042b4dd;
              bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.new_tank2);
              if ((bVar4) && ((this->field16_0x40)._s_0.detected_message == false))
              goto LAB_0042b434;
            }
            if (((this->field16_0x40)._s_0.retreat_success != false) &&
               (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol1_1), !bVar4)) {
              piVar1 = &(this->field18_0x1e4)._s_0.svpatrol1_2;
              bVar4 = IsAlive(piVar1);
              if ((!bVar4) && (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol1_3), !bVar4)) {
                piVar3 = &(this->field18_0x1e4)._s_0.ccarecycle;
                bVar4 = IsAlive(piVar3);
                if (bVar4) {
                  iVar5 = BuildObject("svtank",2,*piVar3);
                  (this->field18_0x1e4)._s_0.svpatrol1_1 = iVar5;
                  iVar5 = BuildObject("svtank",2,*piVar3);
                  *piVar1 = iVar5;
                  Patrol((this->field18_0x1e4)._s_0.svpatrol1_1,"patrol_path1",1);
                  Patrol(*piVar1,"patrol_path1",1);
                }
              }
            }
          }
LAB_0042b4dd:
          if (((((this->field16_0x40)._s_0.retreat_success != false) &&
               (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol3_1), !bVar4)) &&
              (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol3_2), !bVar4)) &&
             (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol3_3), !bVar4)) {
            piVar1 = &(this->field18_0x1e4)._s_0.ccarecycle;
            bVar4 = IsAlive(piVar1);
            if (bVar4) {
              iVar5 = BuildObject("svtank",2,*piVar1);
              (this->field18_0x1e4)._s_0.svpatrol3_1 = iVar5;
              iVar5 = BuildObject("svtank",2,*piVar1);
              piVar1 = &(this->field18_0x1e4)._s_0.svpatrol3_2;
              *piVar1 = iVar5;
              Patrol((this->field18_0x1e4)._s_0.svpatrol3_1,"patrol_path1",1);
              Patrol(*piVar1,"patrol_path1",1);
            }
          }
        }
      }
    }
  }
  if ((this->field16_0x40)._s_0.first_objective == false) {
    bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol1_1);
    if ((!bVar4) && (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol1_2), !bVar4)) {
      piVar1 = &(this->field18_0x1e4)._s_0.ccarecycle;
      bVar4 = IsAlive(piVar1);
      if ((bVar4) && ((this->field16_0x40)._s_0.detected == false)) {
        iVar5 = BuildObject("svfigh",2,*piVar1);
        (this->field18_0x1e4)._s_0.svpatrol1_1 = iVar5;
        iVar5 = BuildObject("svfigh",2,*piVar1);
        piVar1 = &(this->field18_0x1e4)._s_0.svpatrol1_2;
        *piVar1 = iVar5;
        Patrol((this->field18_0x1e4)._s_0.svpatrol1_1,"patrol_path1",1);
        Patrol(*piVar1,"patrol_path1",1);
        (this->field16_0x40)._s_0.p1_retreat = false;
        (this->field16_0x40)._s_0.getum = false;
        (this->field16_0x40)._s_0.patrola1 = false;
        (this->field16_0x40)._s_0.patrola2 = false;
      }
    }
    bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol3_1);
    if ((!bVar4) && (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol3_2), !bVar4)) {
      piVar1 = &(this->field18_0x1e4)._s_0.ccarecycle;
      bVar4 = IsAlive(piVar1);
      if ((bVar4) && ((this->field16_0x40)._s_0.detected == false)) {
        iVar5 = BuildObject("svfigh",2,*piVar1);
        (this->field18_0x1e4)._s_0.svpatrol3_1 = iVar5;
        iVar5 = BuildObject("svfigh",2,*piVar1);
        piVar1 = &(this->field18_0x1e4)._s_0.svpatrol3_2;
        *piVar1 = iVar5;
        Patrol((this->field18_0x1e4)._s_0.svpatrol3_1,"patrol_path1",1);
        Patrol(*piVar1,"patrol_path1",1);
        (this->field16_0x40)._s_0.p3_retreat = false;
        (this->field16_0x40)._s_0.getum = false;
        (this->field16_0x40)._s_0.patrolc1 = false;
        (this->field16_0x40)._s_0.patrolc2 = false;
      }
    }
    bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.svpatrol4_1);
    if (!bVar4) {
      piVar1 = &(this->field18_0x1e4)._s_0.svpatrol4_2;
      bVar4 = IsAlive(piVar1);
      if (!bVar4) {
        piVar3 = &(this->field18_0x1e4)._s_0.ccarecycle;
        bVar4 = IsAlive(piVar3);
        if (bVar4) {
          iVar5 = BuildObject("svfigh",2,*piVar3);
          (this->field18_0x1e4)._s_0.svpatrol4_1 = iVar5;
          iVar5 = BuildObject("svfigh",2,*piVar3);
          *piVar1 = iVar5;
          Patrol((this->field18_0x1e4)._s_0.svpatrol4_1,"patrol_path2",1);
          Patrol(*piVar1,"patrol_path2",1);
        }
      }
    }
  }
  bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.ccacomtower);
  if (bVar4) {
LAB_0042b767:
    if ((this->field16_0x40)._s_0.first_objective == false) goto LAB_0042b8ec;
  }
  else if ((this->field16_0x40)._s_0.first_objective == false) {
    iVar5 = AudioMessage("misn0714.wav");
    (this->field20_0x6cc)._s_0.audmsg = iVar5;
    fVar8 = Get_Time();
    (this->field17_0x16c)._s_0.radar_camera_time = fVar8 + 10.0;
    fVar8 = Get_Time();
    (this->field17_0x16c)._s_0.next_mission_time = fVar8 + 7.5;
    (this->field16_0x40)._s_0.first_objective = true;
    goto LAB_0042b767;
  }
  if (((this->field16_0x40)._s_0.next_mission == false) &&
     (fVar8 = Get_Time(), (this->field17_0x16c)._s_0.next_mission_time < fVar8)) {
    iVar5 = BuildObject("avrec7",1,"recycle_spawn",0);
    (this->field18_0x1e4)._s_0.nsdfrecycle = iVar5;
    iVar5 = BuildObject("avmu7",1,"muf_spawn",0);
    (this->field18_0x1e4)._s_0.nsdfmuf = iVar5;
    Goto((this->field18_0x1e4)._s_0.nsdfrecycle,"recycle_path",0);
    Goto((this->field18_0x1e4)._s_0.nsdfmuf,"muf_path",0);
    iVar5 = BuildObject("apcamr",1,"recycle_cam_spawn",0);
    (this->field18_0x1e4)._s_0.nav6 = iVar5;
    iVar5 = BuildObject("apcamr",1,"recy_cam_spawn",0);
    (this->field18_0x1e4)._s_0.nav7 = iVar5;
    SetObjectiveName((this->field18_0x1e4)._s_0.nav6,"Utah Rendezvous");
    SetObjectiveName((this->field18_0x1e4)._s_0.nav7,"CCA BASE");
    AddScrap(1,0x1e);
    SetPilot(1,0x14);
    AddScrap(2,0x3c);
    SetPilot(2,0x28);
    SetAIP("misn07.aip",2);
    iVar5 = BuildObject("sbtowe",2,"base_tower1_spawn",0);
    (this->field18_0x1e4)._s_0.ccabaseguntower1 = iVar5;
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misn0701.otf",DisplayInterface::colorGreen,8.0);
    InfoDisplay::AddObjective(&infoDisplay,"misn0703.otf",DisplayInterface::colorWhite,8.0);
    InfoDisplay::AddObjective(&infoDisplay,"misn0702.otf",DisplayInterface::colorWhite,8.0);
    (this->field16_0x40)._s_0.next_mission = true;
  }
LAB_0042b8ec:
  if ((this->field16_0x40)._s_0.next_mission != false) {
    bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.ccarecycle);
    if (!bVar4) {
      (this->field16_0x40)._s_0.second_objective = true;
    }
    if (((((this->field16_0x40)._s_0.next_mission != false) &&
         ((this->field16_0x40)._s_0.utah_found == false)) &&
        (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.nsdfrecycle), bVar4)) &&
       (bVar4 = IsDeployed((this->field18_0x1e4)._s_0.nsdfrecycle), bVar4)) {
      InfoDisplay::ClearObjectives(&infoDisplay);
      InfoDisplay::AddObjective(&infoDisplay,"misn0703.otf",DisplayInterface::colorGreen,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn0702.otf",DisplayInterface::colorWhite,8.0);
      (this->field16_0x40)._s_0.utah_found = true;
    }
  }
  bVar4 = IsAlive((this->field18_0x1e4).h_array);
  if ((!bVar4) && (bVar4 = IsOdf((this->field18_0x1e4)._s_0.user,"asuser"), bVar4)) {
    pcVar9 = (char *)0x0;
    fVar8 = Get_Time();
    FailMission(fVar8 + 5.0,pcVar9);
  }
  if ((this->field16_0x40)._s_0.next_mission != false) {
    bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.nsdfrecycle);
    if ((!bVar4) && ((this->field16_0x40)._s_0.game_over == false)) {
      AudioMessage("misn0712.wav");
      if ((this->field16_0x40)._s_0.utah_found == false) {
        InfoDisplay::ClearObjectives(&infoDisplay);
        InfoDisplay::AddObjective(&infoDisplay,"misn0701.otf",DisplayInterface::colorGreen,8.0);
        InfoDisplay::AddObjective(&infoDisplay,"misn0703.otf",DisplayInterface::colorRed,8.0);
        InfoDisplay::AddObjective(&infoDisplay,"misn0702.otf",DisplayInterface::colorWhite,8.0);
      }
      pcVar9 = "misn07f1.des";
      fVar8 = Get_Time();
      FailMission(fVar8 + 15.0,pcVar9);
      (this->field16_0x40)._s_0.game_over = true;
    }
    if (((this->field16_0x40)._s_0.next_mission != false) &&
       (bVar4 = IsAlive(&(this->field18_0x1e4)._s_0.ccarecycle), !bVar4)) {
      (this->field16_0x40)._s_0.second_objective = true;
    }
  }
  if ((((this->field16_0x40)._s_0.first_objective != false) &&
      ((this->field16_0x40)._s_0.second_objective != false)) &&
     ((this->field16_0x40)._s_0.game_over == false)) {
    AudioMessage("misn0713.wav");
    pcVar9 = "misn07w1.des";
    fVar8 = Get_Time();
    SucceedMission(fVar8 + 15.0,pcVar9);
    (this->field16_0x40)._s_0.game_over = true;
  }
  return;
}
