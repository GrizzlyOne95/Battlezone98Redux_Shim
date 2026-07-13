/*
 * Entry: 00432bfd
 * Name: Misn12Mission::Execute
 * Namespace: Misn12Mission
 * Signature: void Execute(Misn12Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn12Mission::Execute(Misn12Mission *this)

{
  Misn12Mission_u_272 *pMVar1;
  int *piVar2;
  bool *pbVar3;
  int *piVar4;
  bool bVar5;
  int iVar6;
  float fVar7;
  float fVar8;
  char *pcVar9;
  
  pMVar1 = &this->field18_0x110;
  iVar6 = GetPlayerHandle();
  (pMVar1->_s_0).user = iVar6;
  if ((this->field16_0x40)._s_0.start_done == false) {
    AudioMessage("misn1200.wav");
    iVar6 = GetPlayerHandle();
    (this->field18_0x110)._s_0.user_tank = iVar6;
    Defend((this->field18_0x110)._s_0.guard_tank1,1);
    Defend((this->field18_0x110)._s_0.guard_tank2,1);
    Defend((this->field18_0x110)._s_0.patrol1_1,1);
    Defend((this->field18_0x110)._s_0.patrol1_2,1);
    Defend((this->field18_0x110)._s_0.patrol2_1,1);
    Defend((this->field18_0x110)._s_0.patrol2_2,1);
    Defend((this->field18_0x110)._s_0.patrol3_1,1);
    Defend((this->field18_0x110)._s_0.patrol3_2,1);
    Defend((this->field18_0x110)._s_0.patrol4_1,1);
    Defend((this->field18_0x110)._s_0.patrol4_2,1);
    StartCockpitTimer(0x4b0,300,0x78);
    piVar2 = &(this->field18_0x110)._s_0.checkpoint1;
    SetObjectiveOn(*piVar2);
    SetObjectiveName(*piVar2,"Check Point");
    iVar6 = BuildObject("apcamr",3,"center_cam",0);
    (this->field18_0x110)._s_0.center_cam = iVar6;
    iVar6 = BuildObject("apcamr",3,"start_cam",0);
    (this->field18_0x110)._s_0.start_cam = iVar6;
    iVar6 = BuildObject("apcamr",3,"check2_cam",0);
    (this->field18_0x110)._s_0.check2_cam = iVar6;
    iVar6 = BuildObject("apcamr",3,"check3_cam",0);
    (this->field18_0x110)._s_0.check3_cam = iVar6;
    iVar6 = BuildObject("apcamr",3,"check4_cam",0);
    (this->field18_0x110)._s_0.check4_cam = iVar6;
    iVar6 = BuildObject("apcamr",3,"goal_cam",0);
    (this->field18_0x110)._s_0.goal_cam = iVar6;
    iVar6 = BuildObject("svfi12",2,(this->field18_0x110)._s_0.spawn_geyser);
    piVar2 = &(this->field18_0x110)._s_0.key_ship;
    *piVar2 = iVar6;
    SetWeaponMask(iVar6,3);
    Goto(*piVar2,"first_path",1);
    fVar7 = Get_Time();
    (this->field17_0xa0)._s_0.key_check = fVar7 + 2.0;
    CameraReady();
    fVar7 = Get_Time();
    iVar6 = (this->field18_0x110)._s_0.nav1;
    (this->field17_0xa0)._s_0.camera_time = fVar7 + 12.0;
    SetObjectiveName(iVar6,"Drop Zone");
    (this->field16_0x40)._s_0.start_done = true;
  }
  piVar2 = &(this->field18_0x110)._s_0.ccacom_tower;
  bVar5 = IsAlive(piVar2);
  if ((bVar5) && (fVar7 = Get_Time(), (this->field17_0xa0)._s_0.next_second < fVar7)) {
    AddHealth(*piVar2,200.0);
    fVar7 = Get_Time();
    (this->field17_0xa0)._s_0.next_second = fVar7 + 1.0;
  }
  if (((this->field16_0x40)._s_0.game_blown == false) &&
     ((this->field16_0x40)._s_0.key_captured == false)) {
    piVar2 = &(this->field18_0x110)._s_0.user_tank;
    bVar5 = IsAlive(piVar2);
    if ((bVar5) && (fVar7 = GetHealth(*piVar2), fVar7 < 0.9)) {
      AudioMessage("misn1213.wav");
      fVar7 = Get_Time();
      (this->field16_0x40)._s_0.game_blown = true;
      (this->field17_0xa0)._s_0.death_spawn = fVar7 + 5.0;
    }
  }
  piVar2 = &(this->field18_0x110)._s_0.key_ship;
  bVar5 = IsValid(piVar2);
  if ((((bVar5) && ((this->field16_0x40)._s_0.game_blown == false)) &&
      ((this->field16_0x40)._s_0.key_captured == false)) &&
     (fVar7 = GetHealth(*piVar2), fVar7 < 0.5)) {
    AudioMessage("misn1228.wav");
    fVar7 = Get_Time();
    (this->field16_0x40)._s_0.game_blown = true;
    (this->field17_0xa0)._s_0.death_spawn = fVar7 + 5.0;
  }
  bVar5 = IsAlive(&(this->field18_0x110)._s_0.user_tank);
  if (((!bVar5) ||
      (fVar7 = GetDistance((this->field18_0x110)._s_0.user_tank,
                           (this->field18_0x110)._s_0.checkpoint1), 75.0 <= fVar7)) ||
     ((this->field16_0x40)._s_0.key_captured != false)) {
LAB_00432f3e:
    if ((this->field16_0x40)._s_0.game_blown != false) goto LAB_00432f48;
  }
  else {
    if ((this->field16_0x40)._s_0.game_blown == false) {
      AudioMessage("misn1213.wav");
      fVar7 = Get_Time();
      (this->field17_0xa0)._s_0.death_spawn = fVar7 + 5.0;
      InfoDisplay::ClearObjectives(&infoDisplay);
      InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorRed,8.0);
      (this->field16_0x40)._s_0.game_blown = true;
      goto LAB_00432f3e;
    }
LAB_00432f48:
    fVar7 = Get_Time();
    if ((this->field17_0xa0)._s_0.death_spawn < fVar7) {
      fVar7 = Get_Time();
      iVar6 = (this->field18_0x110)._s_0.spawn_geyser;
      (this->field17_0xa0)._s_0.death_spawn = fVar7 + 120.0;
      iVar6 = BuildObject("svfigh",2,iVar6);
      (this->field18_0x110)._s_0.death_squad1 = iVar6;
      iVar6 = BuildObject("svfigh",2,(this->field18_0x110)._s_0.spawn_geyser);
      (this->field18_0x110)._s_0.death_squad2 = iVar6;
      iVar6 = BuildObject("svltnk",2,(this->field18_0x110)._s_0.spawn_geyser);
      (this->field18_0x110)._s_0.death_squad3 = iVar6;
      iVar6 = BuildObject("svltnk",2,(this->field18_0x110)._s_0.spawn_geyser);
      (this->field18_0x110)._s_0.death_squad4 = iVar6;
      Attack((this->field18_0x110)._s_0.death_squad1,(pMVar1->_s_0).user,1);
      Attack((this->field18_0x110)._s_0.death_squad2,(pMVar1->_s_0).user,1);
      Attack((this->field18_0x110)._s_0.death_squad3,(pMVar1->_s_0).user,1);
      Attack((this->field18_0x110)._s_0.death_squad4,(pMVar1->_s_0).user,1);
    }
    if ((((this->field16_0x40)._s_0.game_blown != false) &&
        (bVar5 = IsAlive(&(this->field18_0x110)._s_0.user_tank), !bVar5)) &&
       ((this->field16_0x40)._s_0.dead_meat == false)) {
      SetPerceivedTeam((pMVar1->_s_0).user,1);
      (this->field16_0x40)._s_0.dead_meat = true;
    }
  }
  if (((this->field16_0x40)._s_0.start_done != false) &&
     ((this->field16_0x40)._s_0.camera4 == false)) {
    CameraPath("start_camera_path",4000,900,(this->field18_0x110)._s_0.ccacom_tower);
  }
  bVar5 = CameraCancelled();
  if (((bVar5) || (fVar7 = Get_Time(), (this->field17_0xa0)._s_0.camera_time < fVar7)) &&
     ((this->field16_0x40)._s_0.camera4 == false)) {
    CameraFinish();
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorWhite,8.0);
    (this->field16_0x40)._s_0.camera4 = true;
  }
  if ((this->field16_0x40)._s_0.camera_off == false) {
LAB_004330e7:
    if ((this->field16_0x40)._s_0.patrol1_create != false) goto LAB_004330f1;
LAB_00433186:
    if ((this->field16_0x40)._s_0.patrol1_moved1 != false) goto LAB_00433190;
LAB_00433255:
    if ((this->field16_0x40)._s_0.patrol1_moved2 != false) goto LAB_00433262;
  }
  else {
    if ((this->field16_0x40)._s_0.patrol1_create == false) {
      Goto((this->field18_0x110)._s_0.patrol1_1,"path1_to",1);
      Goto((this->field18_0x110)._s_0.patrol1_2,"path1_to",1);
      (this->field16_0x40)._s_0.patrol1_create = true;
      goto LAB_004330e7;
    }
LAB_004330f1:
    bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol1_1);
    if ((!bVar5) ||
       (fVar7 = GetDistance((this->field18_0x110)._s_0.patrol1_1,
                            (this->field18_0x110)._s_0.checkpoint1), 50.0 <= fVar7))
    goto LAB_00433186;
    if ((this->field16_0x40)._s_0.patrol1_moved1 == false) {
      bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol1_2);
      if ((bVar5) &&
         (fVar7 = GetDistance((this->field18_0x110)._s_0.patrol1_2,
                              (this->field18_0x110)._s_0.checkpoint1), fVar7 < 70.0)) {
        Goto((this->field18_0x110)._s_0.patrol1_1,"path1_from",1);
        Goto((this->field18_0x110)._s_0.patrol1_2,"path1_from",1);
        (this->field16_0x40)._s_0.patrol1_moved1 = true;
      }
      goto LAB_00433186;
    }
LAB_00433190:
    bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol1_1);
    if ((!bVar5) ||
       (fVar7 = GetDistance((this->field18_0x110)._s_0.patrol1_1,
                            (this->field18_0x110)._s_0.center_geyser), 50.0 <= fVar7))
    goto LAB_00433255;
    if ((this->field16_0x40)._s_0.patrol1_moved2 == false) {
      bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol1_2);
      if ((bVar5) &&
         (fVar7 = GetDistance((this->field18_0x110)._s_0.patrol1_2,
                              (this->field18_0x110)._s_0.center_geyser), fVar7 < 50.0)) {
        Goto((this->field18_0x110)._s_0.patrol1_1,"path2",1);
        Patrol((this->field18_0x110)._s_0.patrol1_2,"path5",1);
        Goto((this->field18_0x110)._s_0.patrol2_1,"path3",1);
        fVar7 = Get_Time();
        (this->field16_0x40)._s_0.patrol1_moved2 = true;
        (this->field17_0xa0)._s_0.patrol2_1_time = fVar7 + 15.0;
      }
      goto LAB_00433255;
    }
LAB_00433262:
    bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol1_1);
    if (((bVar5) &&
        (fVar7 = GetDistance((this->field18_0x110)._s_0.patrol1_1,
                             (this->field18_0x110)._s_0.check2_geyser), fVar7 < 400.0)) &&
       ((this->field16_0x40)._s_0.patrol2_moved1 == false)) {
      Goto((this->field18_0x110)._s_0.patrol2_2,"path2",1);
      Goto((this->field18_0x110)._s_0.patrol4_1,"path4",1);
      (this->field16_0x40)._s_0.p4_1center = true;
      fVar7 = Get_Time();
      (this->field17_0xa0)._s_0.patrol2_2_time = fVar7 + 11.0;
      fVar7 = Get_Time();
      (this->field17_0xa0)._s_0.patrol1_1_time = fVar7 + 10.0;
      fVar7 = Get_Time();
      (this->field16_0x40)._s_0.patrol2_moved1 = true;
      (this->field17_0xa0)._s_0.patrol4_1_time = fVar7 + 12.0;
    }
  }
  bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol2_1);
  if (((bVar5) &&
      (fVar7 = GetDistance((this->field18_0x110)._s_0.patrol2_1,(this->field18_0x110)._s_0.ccamuf),
      fVar7 < 400.0)) && ((this->field16_0x40)._s_0.patrol3_moved1 == false)) {
    Goto((this->field18_0x110)._s_0.patrol3_1,"path4",1);
    fVar7 = Get_Time();
    (this->field16_0x40)._s_0.p3_1center = true;
    (this->field16_0x40)._s_0.patrol3_moved1 = true;
    (this->field17_0xa0)._s_0.patrol3_1_time = fVar7 + 5.0;
  }
  bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol2_2);
  if (((bVar5) &&
      (fVar7 = GetDistance((this->field18_0x110)._s_0.patrol2_2,(this->field18_0x110)._s_0.ccamuf),
      fVar7 < 400.0)) && ((this->field16_0x40)._s_0.patrol3_moved2 == false)) {
    Goto((this->field18_0x110)._s_0.patrol3_2,"path4",1);
    (this->field16_0x40)._s_0.p3_2center = true;
    fVar7 = Get_Time();
    (this->field16_0x40)._s_0.patrol3_moved2 = true;
    (this->field17_0xa0)._s_0.patrol3_2_time = fVar7 + 10.0;
  }
  bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol3_1);
  if (((bVar5) &&
      (fVar7 = GetDistance((this->field18_0x110)._s_0.patrol3_1,
                           (this->field18_0x110)._s_0.checkpoint4), fVar7 < 400.0)) &&
     ((this->field16_0x40)._s_0.patrol4_moved2 == false)) {
    Goto((this->field18_0x110)._s_0.patrol4_2,"path4",1);
    fVar7 = Get_Time();
    (this->field16_0x40)._s_0.p4_2center = true;
    (this->field16_0x40)._s_0.patrol4_moved2 = true;
    (this->field17_0xa0)._s_0.patrol4_2_time = fVar7 + 5.0;
  }
  if (((this->field16_0x40)._s_0.real_bad == false) ||
     ((this->field16_0x40)._s_0.game_blown == false)) {
    bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol1_1);
    if ((bVar5) && (fVar7 = Get_Time(), (this->field17_0xa0)._s_0.patrol1_1_time < fVar7)) {
      fVar7 = Get_Time();
      bVar5 = (this->field16_0x40)._s_0.p1_1center;
      (this->field17_0xa0)._s_0.patrol1_1_time = fVar7 + 10.0;
      if ((bVar5 != false) ||
         (fVar7 = GetDistance((this->field18_0x110)._s_0.patrol1_1,
                              (this->field18_0x110)._s_0.center_geyser), 50.0 <= fVar7)) {
        fVar7 = GetDistance((this->field18_0x110)._s_0.patrol1_1,
                            (this->field18_0x110)._s_0.center_geyser);
        if (50.0 <= fVar7) {
          fVar7 = GetDistance((this->field18_0x110)._s_0.patrol1_1,(this->field18_0x110)._s_0.ccamuf
                             );
          if (fVar7 < 70.0) {
            Goto((this->field18_0x110)._s_0.patrol1_1,"path4",1);
          }
        }
        else {
          Goto((this->field18_0x110)._s_0.patrol1_1,"path2",1);
          (this->field16_0x40)._s_0.p1_1center = false;
        }
      }
      else {
        Goto((this->field18_0x110)._s_0.patrol1_1,"path3",1);
        (this->field16_0x40)._s_0.p1_1center = true;
      }
    }
    bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol2_1);
    if ((bVar5) && (fVar7 = Get_Time(), (this->field17_0xa0)._s_0.patrol2_1_time < fVar7)) {
      fVar7 = Get_Time();
      bVar5 = (this->field16_0x40)._s_0.p2_1center;
      (this->field17_0xa0)._s_0.patrol2_1_time = fVar7 + 10.0;
      if ((bVar5 != false) ||
         (fVar7 = GetDistance((this->field18_0x110)._s_0.patrol2_1,
                              (this->field18_0x110)._s_0.center_geyser), 50.0 <= fVar7)) {
        fVar7 = GetDistance((this->field18_0x110)._s_0.patrol2_1,
                            (this->field18_0x110)._s_0.center_geyser);
        if (50.0 <= fVar7) {
          fVar7 = GetDistance((this->field18_0x110)._s_0.patrol2_1,(this->field18_0x110)._s_0.ccamuf
                             );
          if (fVar7 < 70.0) {
            Goto((this->field18_0x110)._s_0.patrol2_1,"path4",1);
          }
        }
        else {
          Goto((this->field18_0x110)._s_0.patrol2_1,"path2",1);
          (this->field16_0x40)._s_0.p2_1center = false;
        }
      }
      else {
        Goto((this->field18_0x110)._s_0.patrol1_1,"path3",1);
        (this->field16_0x40)._s_0.p2_1center = true;
      }
    }
    bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol2_2);
    if ((bVar5) && (fVar7 = Get_Time(), (this->field17_0xa0)._s_0.patrol2_2_time < fVar7)) {
      fVar7 = Get_Time();
      bVar5 = (this->field16_0x40)._s_0.p2_2center;
      (this->field17_0xa0)._s_0.patrol2_2_time = fVar7 + 10.0;
      if ((bVar5 != false) ||
         (fVar7 = GetDistance((this->field18_0x110)._s_0.patrol2_2,
                              (this->field18_0x110)._s_0.center_geyser), 50.0 <= fVar7)) {
        fVar7 = GetDistance((this->field18_0x110)._s_0.patrol2_2,
                            (this->field18_0x110)._s_0.center_geyser);
        if (50.0 <= fVar7) {
          fVar7 = GetDistance((this->field18_0x110)._s_0.patrol2_2,(this->field18_0x110)._s_0.ccamuf
                             );
          if (fVar7 < 70.0) {
            Goto((this->field18_0x110)._s_0.patrol2_2,"path4",1);
          }
        }
        else {
          Goto((this->field18_0x110)._s_0.patrol2_2,"path2",1);
          (this->field16_0x40)._s_0.p2_2center = false;
        }
      }
      else {
        Goto((this->field18_0x110)._s_0.patrol2_2,"path3",1);
        (this->field16_0x40)._s_0.p2_2center = true;
      }
    }
    bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol3_1);
    if ((bVar5) && (fVar7 = Get_Time(), (this->field17_0xa0)._s_0.patrol3_1_time < fVar7)) {
      fVar7 = Get_Time();
      bVar5 = (this->field16_0x40)._s_0.p3_1center;
      (this->field17_0xa0)._s_0.patrol3_1_time = fVar7 + 10.0;
      if ((bVar5 != false) ||
         (fVar7 = GetDistance((this->field18_0x110)._s_0.patrol3_1,
                              (this->field18_0x110)._s_0.center_geyser), 50.0 <= fVar7)) {
        fVar7 = GetDistance((this->field18_0x110)._s_0.patrol3_1,
                            (this->field18_0x110)._s_0.center_geyser);
        if (50.0 <= fVar7) {
          fVar7 = GetDistance((this->field18_0x110)._s_0.patrol3_1,(this->field18_0x110)._s_0.ccamuf
                             );
          if (fVar7 < 70.0) {
            Goto((this->field18_0x110)._s_0.patrol3_1,"path4",1);
          }
        }
        else {
          Goto((this->field18_0x110)._s_0.patrol3_1,"path2",1);
          (this->field16_0x40)._s_0.p3_1center = false;
        }
      }
      else {
        Goto((this->field18_0x110)._s_0.patrol3_1,"path3",1);
        (this->field16_0x40)._s_0.p3_1center = true;
      }
    }
    bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol3_2);
    if ((bVar5) && (fVar7 = Get_Time(), (this->field17_0xa0)._s_0.patrol3_2_time < fVar7)) {
      fVar7 = Get_Time();
      bVar5 = (this->field16_0x40)._s_0.p3_2center;
      (this->field17_0xa0)._s_0.patrol3_2_time = fVar7 + 10.0;
      if ((bVar5 != false) ||
         (fVar7 = GetDistance((this->field18_0x110)._s_0.patrol3_2,
                              (this->field18_0x110)._s_0.center_geyser), 50.0 <= fVar7)) {
        fVar7 = GetDistance((this->field18_0x110)._s_0.patrol3_2,
                            (this->field18_0x110)._s_0.center_geyser);
        if (50.0 <= fVar7) {
          fVar7 = GetDistance((this->field18_0x110)._s_0.patrol3_2,(this->field18_0x110)._s_0.ccamuf
                             );
          if (fVar7 < 70.0) {
            Goto((this->field18_0x110)._s_0.patrol3_2,"path4",1);
          }
        }
        else {
          Goto((this->field18_0x110)._s_0.patrol3_2,"path2",1);
          (this->field16_0x40)._s_0.p3_2center = false;
        }
      }
      else {
        Goto((this->field18_0x110)._s_0.patrol3_2,"path3",1);
        (this->field16_0x40)._s_0.p3_2center = true;
      }
    }
    bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol4_1);
    if ((bVar5) && (fVar7 = Get_Time(), (this->field17_0xa0)._s_0.patrol4_1_time < fVar7)) {
      fVar7 = Get_Time();
      bVar5 = (this->field16_0x40)._s_0.p4_1center;
      (this->field17_0xa0)._s_0.patrol4_1_time = fVar7 + 10.0;
      if ((bVar5 != false) ||
         (fVar7 = GetDistance((this->field18_0x110)._s_0.patrol4_1,
                              (this->field18_0x110)._s_0.center_geyser), 50.0 <= fVar7)) {
        fVar7 = GetDistance((this->field18_0x110)._s_0.patrol4_1,
                            (this->field18_0x110)._s_0.center_geyser);
        if (50.0 <= fVar7) {
          fVar7 = GetDistance((this->field18_0x110)._s_0.patrol4_1,(this->field18_0x110)._s_0.ccamuf
                             );
          if (fVar7 < 70.0) {
            Goto((this->field18_0x110)._s_0.patrol4_1,"path4",1);
          }
        }
        else {
          Goto((this->field18_0x110)._s_0.patrol4_1,"path2",1);
          (this->field16_0x40)._s_0.p4_1center = false;
        }
      }
      else {
        Goto((this->field18_0x110)._s_0.patrol4_1,"path3",1);
        (this->field16_0x40)._s_0.p4_1center = true;
      }
    }
    bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol4_2);
    if ((bVar5) && (fVar7 = Get_Time(), (this->field17_0xa0)._s_0.patrol4_2_time < fVar7)) {
      fVar7 = Get_Time();
      bVar5 = (this->field16_0x40)._s_0.p4_2center;
      (this->field17_0xa0)._s_0.patrol4_2_time = fVar7 + 10.0;
      if ((bVar5 != false) ||
         (fVar7 = GetDistance((this->field18_0x110)._s_0.patrol4_2,
                              (this->field18_0x110)._s_0.center_geyser), 50.0 <= fVar7)) {
        fVar7 = GetDistance((this->field18_0x110)._s_0.patrol4_2,
                            (this->field18_0x110)._s_0.center_geyser);
        if (50.0 <= fVar7) {
          fVar7 = GetDistance((this->field18_0x110)._s_0.patrol4_2,(this->field18_0x110)._s_0.ccamuf
                             );
          if (fVar7 < 70.0) {
            Goto((this->field18_0x110)._s_0.patrol4_2,"path4",1);
          }
        }
        else {
          Goto((this->field18_0x110)._s_0.patrol4_2,"path2",1);
          (this->field16_0x40)._s_0.p4_2center = false;
        }
      }
      else {
        Goto((this->field18_0x110)._s_0.patrol4_2,"path3",1);
        (this->field16_0x40)._s_0.p4_2center = true;
      }
    }
    if ((this->field16_0x40)._s_0.game_blown == false) {
      if (((this->field16_0x40)._s_0.start_done == false) ||
         ((this->field16_0x40)._s_0.key_captured != false)) {
LAB_00433b3d:
        if ((this->field16_0x40)._s_0.checked_in != false) goto LAB_00433b43;
LAB_00433b8b:
        if ((this->field16_0x40)._s_0.going_again != false) goto LAB_00433b95;
      }
      else {
        if ((this->field16_0x40)._s_0.checked_in == false) {
          bVar5 = IsValid(&(this->field18_0x110)._s_0.key_ship);
          if ((bVar5) &&
             (fVar7 = GetDistance((this->field18_0x110)._s_0.key_ship,
                                  (this->field18_0x110)._s_0.checkpoint1), fVar7 < 80.0)) {
            Stop((this->field18_0x110)._s_0.key_ship,1);
            fVar7 = Get_Time();
            (this->field16_0x40)._s_0.checked_in = true;
            (this->field17_0xa0)._s_0.wait_time = fVar7 + 20.0;
          }
          goto LAB_00433b3d;
        }
LAB_00433b43:
        fVar7 = Get_Time();
        if (fVar7 <= (this->field17_0xa0)._s_0.wait_time) goto LAB_00433b8b;
        if ((this->field16_0x40)._s_0.going_again == false) {
          if ((this->field16_0x40)._s_0.key_captured == false) {
            Goto((this->field18_0x110)._s_0.key_ship,"first_path",1);
            fVar7 = Get_Time();
            (this->field16_0x40)._s_0.going_again = true;
            (this->field17_0xa0)._s_0.key_remove = fVar7 + 10.0;
          }
          goto LAB_00433b8b;
        }
LAB_00433b95:
        fVar7 = Get_Time();
        if (((this->field17_0xa0)._s_0.key_remove < fVar7) &&
           ((this->field16_0x40)._s_0.key_captured == false)) {
          fVar7 = Get_Time();
          piVar2 = &(this->field18_0x110)._s_0.key_ship;
          iVar6 = *piVar2;
          (this->field17_0xa0)._s_0.key_remove = fVar7 + 3.0;
          fVar7 = GetDistance(iVar6,(this->field18_0x110)._s_0.spawn_geyser);
          if (fVar7 < 100.0) {
            RemoveObject(*piVar2);
            iVar6 = BuildObject("svfi12",2,(this->field18_0x110)._s_0.spawn_geyser);
            *piVar2 = iVar6;
            SetWeaponMask(iVar6,3);
            Goto(*piVar2,"first_path",1);
            (this->field16_0x40)._s_0.checked_in = false;
            (this->field16_0x40)._s_0.going_again = false;
          }
        }
      }
      bVar5 = IsOdf((pMVar1->_s_0).user,"svfi12");
      if (bVar5) {
        if ((this->field16_0x40)._s_0.key_captured == false) {
          bVar5 = IsAlive(pMVar1->h_array);
          if (bVar5) {
            AddAmmo((pMVar1->_s_0).user,2000);
          }
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1201.otf",DisplayInterface::colorWhite,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1202.otf",DisplayInterface::colorWhite,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1203.otf",DisplayInterface::colorWhite,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1204.otf",DisplayInterface::colorWhite,8.0);
          AudioMessage("misn1217.wav");
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.camera_time = fVar7 + 10.0;
          bVar5 = IsAlive(&(this->field18_0x110)._s_0.checkpoint1);
          if (bVar5) {
            SetObjectiveOff((this->field18_0x110)._s_0.checkpoint1);
          }
          (this->field16_0x40)._s_0.key_captured = true;
          goto LAB_00433d28;
        }
LAB_00433d2e:
        bVar5 = IsOdf((pMVar1->_s_0).user,"svfigh");
        if (((bVar5) || (bVar5 = IsOdf((pMVar1->_s_0).user,"svtank"), bVar5)) &&
           (pbVar3 = &(this->field16_0x40)._s_0.out_of_ship, *pbVar3 == false)) {
          *pbVar3 = true;
        }
      }
      else {
LAB_00433d28:
        if ((this->field16_0x40)._s_0.key_captured != false) goto LAB_00433d2e;
      }
      if (((this->field16_0x40)._s_0.out_of_ship != false) &&
         ((this->field16_0x40)._s_0.grump == false)) {
        bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol1_1);
        if (bVar5) {
          Attack((this->field18_0x110)._s_0.patrol1_1,(pMVar1->_s_0).user,1);
        }
        bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol1_2);
        if (bVar5) {
          Attack((this->field18_0x110)._s_0.patrol1_2,(pMVar1->_s_0).user,1);
        }
        bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol2_1);
        if (bVar5) {
          Attack((this->field18_0x110)._s_0.patrol2_1,(pMVar1->_s_0).user,1);
        }
        bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol2_2);
        if (bVar5) {
          Attack((this->field18_0x110)._s_0.patrol2_2,(pMVar1->_s_0).user,1);
        }
        bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol3_1);
        if (bVar5) {
          Attack((this->field18_0x110)._s_0.patrol3_1,(pMVar1->_s_0).user,1);
        }
        bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol3_2);
        if (bVar5) {
          Attack((this->field18_0x110)._s_0.patrol3_2,(pMVar1->_s_0).user,1);
        }
        bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol4_1);
        if (bVar5) {
          Attack((this->field18_0x110)._s_0.patrol4_1,(pMVar1->_s_0).user,1);
        }
        bVar5 = IsAlive(&(this->field18_0x110)._s_0.patrol4_2);
        if (bVar5) {
          Attack((this->field18_0x110)._s_0.patrol4_2,(pMVar1->_s_0).user,1);
        }
        bVar5 = IsAlive(&(this->field18_0x110)._s_0.guard_tank1);
        if (bVar5) {
          Attack((this->field18_0x110)._s_0.guard_tank1,(pMVar1->_s_0).user,1);
        }
        bVar5 = IsAlive(&(this->field18_0x110)._s_0.guard_tank2);
        if (bVar5) {
          Attack((this->field18_0x110)._s_0.guard_tank2,(pMVar1->_s_0).user,1);
        }
        if (((this->field16_0x40)._s_0.interface_complete == false) &&
           ((this->field16_0x40)._s_0.blown_otf == false)) {
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misn1206.otf",DisplayInterface::colorWhite,8.0);
          (this->field16_0x40)._s_0.blown_otf = true;
        }
        fVar7 = Get_Time();
        (this->field16_0x40)._s_0.grump = true;
        (this->field17_0xa0)._s_0.grump_time = fVar7 + 180.0;
      }
      fVar7 = Get_Time();
      if ((this->field17_0xa0)._s_0.grump_time < fVar7) {
        (this->field16_0x40)._s_0.grump = false;
      }
      if (((this->field16_0x40)._s_0.key_captured == false) ||
         (fVar7 = Get_Time(), fVar7 <= (this->field17_0xa0)._s_0.camera_time)) {
LAB_00433f7b:
        if ((this->field16_0x40)._s_0.camera_on != false) goto LAB_00433f81;
LAB_00433fda:
        if ((this->field16_0x40)._s_0.camera1 != false) goto LAB_00433fe0;
LAB_00434055:
        if ((this->field16_0x40)._s_0.camera2 != false) goto LAB_0043405b;
LAB_004340d1:
        if ((this->field16_0x40)._s_0.camera3 != false) goto LAB_004340d7;
      }
      else {
        if ((this->field16_0x40)._s_0.camera_on == false) {
          if ((this->field16_0x40)._s_0.camera_off == false) {
            CameraReady();
            (this->field16_0x40)._s_0.camera_on = true;
          }
          goto LAB_00433f7b;
        }
LAB_00433f81:
        if ((this->field16_0x40)._s_0.camera1 == false) {
          if ((((this->field16_0x40)._s_0.camera2 == false) &&
              ((this->field16_0x40)._s_0.camera3 == false)) &&
             ((this->field16_0x40)._s_0.camera_off == false)) {
            iVar6 = (this->field18_0x110)._s_0.checkpoint2;
            CameraObject(iVar6,0,1000,6000,iVar6);
            iVar6 = AudioMessage("misn1218.wav");
            (this->field19_0x1f8)._s_0.audmsg = iVar6;
            fVar7 = Get_Time();
            (this->field16_0x40)._s_0.camera1 = true;
            (this->field17_0xa0)._s_0.camera_time = fVar7 + 6.0;
          }
          goto LAB_00433fda;
        }
LAB_00433fe0:
        if ((this->field16_0x40)._s_0.camera2 == false) {
          if ((((this->field16_0x40)._s_0.camera3 == false) &&
              ((this->field16_0x40)._s_0.camera_off == false)) &&
             ((fVar7 = Get_Time(), (this->field17_0xa0)._s_0.camera_time < fVar7 ||
              (bVar5 = CameraCancelled(), bVar5)))) {
            StopAudioMessage((this->field19_0x1f8)._s_0.audmsg);
            iVar6 = (this->field18_0x110)._s_0.checkpoint3;
            CameraObject(iVar6,3000,3000,3000,iVar6);
            iVar6 = AudioMessage("misn1219.wav");
            (this->field19_0x1f8)._s_0.audmsg = iVar6;
            fVar7 = Get_Time();
            (this->field16_0x40)._s_0.camera2 = true;
            (this->field17_0xa0)._s_0.camera_time = fVar7 + 6.0;
          }
          goto LAB_00434055;
        }
LAB_0043405b:
        if ((this->field16_0x40)._s_0.camera3 == false) {
          if (((this->field16_0x40)._s_0.camera_off == false) &&
             ((fVar7 = Get_Time(), (this->field17_0xa0)._s_0.camera_time < fVar7 ||
              (bVar5 = CameraCancelled(), bVar5)))) {
            StopAudioMessage((this->field19_0x1f8)._s_0.audmsg);
            iVar6 = (this->field18_0x110)._s_0.checkpoint4;
            CameraObject(iVar6,-1000,0x5dc,4000,iVar6);
            iVar6 = AudioMessage("misn1220.wav");
            (this->field19_0x1f8)._s_0.audmsg = iVar6;
            fVar7 = Get_Time();
            (this->field16_0x40)._s_0.camera3 = true;
            (this->field17_0xa0)._s_0.camera_time = fVar7 + 6.0;
          }
          goto LAB_004340d1;
        }
LAB_004340d7:
        if (((this->field16_0x40)._s_0.camera_off == false) &&
           ((fVar7 = Get_Time(), (this->field17_0xa0)._s_0.camera_time < fVar7 ||
            (bVar5 = CameraCancelled(), bVar5)))) {
          StopAudioMessage((this->field19_0x1f8)._s_0.audmsg);
          AudioMessage("misn1221.wav");
          AudioMessage("misn1222.wav");
          CameraFinish();
          (this->field16_0x40)._s_0.camera_off = true;
        }
      }
      fVar7 = GetDistance((pMVar1->_s_0).user,(this->field18_0x110)._s_0.checkpoint2);
      if (fVar7 < 150.0) {
        (this->field16_0x40)._s_0.check_point2_done = true;
      }
      if (((this->field16_0x40)._s_0.check_point2_done != false) &&
         (fVar7 = GetDistance((pMVar1->_s_0).user,(this->field18_0x110)._s_0.checkpoint2),
         150.0 < fVar7)) {
        (this->field16_0x40)._s_0.check_point2_done = false;
      }
      fVar7 = GetDistance((pMVar1->_s_0).user,(this->field18_0x110)._s_0.checkpoint3);
      if (fVar7 < 150.0) {
        (this->field16_0x40)._s_0.check_point3_done = true;
      }
      if (((this->field16_0x40)._s_0.check_point3_done != false) &&
         (fVar7 = GetDistance((pMVar1->_s_0).user,(this->field18_0x110)._s_0.checkpoint3),
         150.0 < fVar7)) {
        (this->field16_0x40)._s_0.check_point3_done = false;
      }
      fVar7 = GetDistance((pMVar1->_s_0).user,(this->field18_0x110)._s_0.checkpoint4);
      if (fVar7 < 150.0) {
        (this->field16_0x40)._s_0.check_point4_done = true;
      }
      if (((this->field16_0x40)._s_0.check_point4_done != false) &&
         (fVar7 = GetDistance((pMVar1->_s_0).user,(this->field18_0x110)._s_0.checkpoint4),
         150.0 < fVar7)) {
        (this->field16_0x40)._s_0.check_point4_done = false;
      }
      fVar7 = GetDistance((pMVar1->_s_0).user,(this->field18_0x110)._s_0.ccacom_tower);
      if (fVar7 < 150.0) {
        (this->field16_0x40)._s_0.check_point5_done = true;
      }
      if (((this->field16_0x40)._s_0.check_point5_done != false) &&
         (fVar7 = GetDistance((pMVar1->_s_0).user,(this->field18_0x110)._s_0.ccacom_tower),
         150.0 < fVar7)) {
        (this->field16_0x40)._s_0.check_point5_done = false;
      }
      if ((this->field16_0x40)._s_0.interface_complete == false) {
        fVar7 = GetDistance((pMVar1->_s_0).user,(this->field18_0x110)._s_0.checkpoint2);
        if ((((fVar7 < 70.0) && ((this->field16_0x40)._s_0.cca_warning_message == false)) &&
            ((this->field16_0x40)._s_0.identify_message == false)) &&
           ((this->field16_0x40)._s_0.check2 == false)) {
          CameraReady();
          iVar6 = (pMVar1->_s_0).user;
          (this->field16_0x40)._s_0.good1 = true;
          CameraObject(iVar6,0,700,-0x5dc,iVar6);
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.camera_time = fVar7 + 5.0;
          AudioMessage("misn1207.wav");
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1201.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1202.otf",DisplayInterface::colorWhite,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1203.otf",DisplayInterface::colorWhite,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1204.otf",DisplayInterface::colorWhite,8.0);
          (this->field16_0x40)._s_0.check2 = true;
        }
        if ((((this->field16_0x40)._s_0.good1 != false) &&
            (fVar7 = Get_Time(), (this->field17_0xa0)._s_0.camera_time < fVar7)) &&
           ((this->field16_0x40)._s_0.good1_off == false)) {
          CameraFinish();
          (this->field16_0x40)._s_0.good1_off = true;
        }
        if ((((this->field16_0x40)._s_0.check2 != false) &&
            (fVar7 = GetDistance((pMVar1->_s_0).user,(this->field18_0x110)._s_0.checkpoint3),
            fVar7 < 70.0)) &&
           (((this->field16_0x40)._s_0.cca_warning_message == false &&
            (((this->field16_0x40)._s_0.identify_message == false &&
             ((this->field16_0x40)._s_0.check3 == false)))))) {
          CameraReady();
          iVar6 = (pMVar1->_s_0).user;
          (this->field16_0x40)._s_0.good2 = true;
          CameraObject(iVar6,0,700,-0x5dc,iVar6);
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.camera_time = fVar7 + 6.0;
          AudioMessage("misn1208.wav");
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1201.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1202.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1203.otf",DisplayInterface::colorWhite,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1204.otf",DisplayInterface::colorWhite,8.0);
          (this->field16_0x40)._s_0.check3 = true;
        }
        if ((((this->field16_0x40)._s_0.good2 != false) &&
            (fVar7 = Get_Time(), (this->field17_0xa0)._s_0.camera_time < fVar7)) &&
           ((this->field16_0x40)._s_0.good2_off == false)) {
          CameraFinish();
          (this->field16_0x40)._s_0.good2_off = true;
        }
        fVar7 = GetDistance((pMVar1->_s_0).user,(this->field18_0x110)._s_0.checkpoint4);
        if (((fVar7 < 70.0) && ((this->field16_0x40)._s_0.check3 != false)) &&
           (((this->field16_0x40)._s_0.check4 == false &&
            (((this->field16_0x40)._s_0.cca_warning_message == false &&
             ((this->field16_0x40)._s_0.identify_message == false)))))) {
          CameraReady();
          iVar6 = (pMVar1->_s_0).user;
          (this->field16_0x40)._s_0.good3 = true;
          CameraObject(iVar6,0,700,-0x5dc,iVar6);
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.camera_time = fVar7 + 6.0;
          AudioMessage("misn1209.wav");
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1201.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1202.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1203.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1204.otf",DisplayInterface::colorWhite,8.0);
          (this->field16_0x40)._s_0.check4 = true;
        }
        if ((((this->field16_0x40)._s_0.good3 != false) &&
            (fVar7 = Get_Time(), (this->field17_0xa0)._s_0.camera_time < fVar7)) &&
           ((this->field16_0x40)._s_0.good3_off == false)) {
          CameraFinish();
          (this->field16_0x40)._s_0.good3_off = true;
        }
      }
      if ((this->field16_0x40)._s_0.check2 == false) {
LAB_00434ac7:
        if ((this->field16_0x40)._s_0.check3 != false) goto LAB_00434ad1;
      }
      else {
        if ((((this->field16_0x40)._s_0.check3 == false) &&
            ((this->field16_0x40)._s_0.check_point4_done != false)) &&
           (((this->field16_0x40)._s_0.cca_warning_message == false &&
            (((this->field16_0x40)._s_0.identify_message == false &&
             ((this->field16_0x40)._s_0.real_bad == false)))))) {
          AudioMessage("misn1205.wav");
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1201.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1202.otf",DisplayInterface::colorWhite,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1203.otf",DisplayInterface::colorYellow,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1204.otf",DisplayInterface::colorWhite,8.0);
          (this->field16_0x40)._s_0.cca_warning_message = true;
        }
        if ((this->field16_0x40)._s_0.check2 == false) goto LAB_00434ac7;
        if (((((this->field16_0x40)._s_0.cca_warning_message != false) &&
             (fVar7 = GetDistance((pMVar1->_s_0).user,(this->field18_0x110)._s_0.checkpoint3),
             fVar7 < 70.0)) && ((this->field16_0x40)._s_0.identify_message == false)) &&
           (((this->field16_0x40)._s_0.real_bad == false &&
            ((this->field16_0x40)._s_0.check4 == false)))) {
          CameraReady();
          iVar6 = (pMVar1->_s_0).user;
          (this->field16_0x40)._s_0.good2 = true;
          CameraObject(iVar6,0,700,-0x5dc,iVar6);
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.camera_time = fVar7 + 6.0;
          AudioMessage("misn1210.wav");
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1201.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1202.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1203.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1204.otf",DisplayInterface::colorWhite,8.0);
          (this->field16_0x40)._s_0.better_message = true;
          (this->field16_0x40)._s_0.check4 = true;
        }
        if ((this->field16_0x40)._s_0.check2 == false) goto LAB_00434ac7;
        if ((((this->field16_0x40)._s_0.cca_warning_message != false) &&
            ((this->field16_0x40)._s_0.check4 == false)) &&
           (((this->field16_0x40)._s_0.check_point2_done != false &&
            (((this->field16_0x40)._s_0.identify_message == false &&
             ((this->field16_0x40)._s_0.real_bad == false)))))) {
          AudioMessage("misn1206.wav");
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.next_message_time = fVar7 + 20.0;
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1201.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1202.otf",DisplayInterface::colorWhite,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1203.otf",DisplayInterface::colorRed,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1204.otf",DisplayInterface::colorWhite,8.0);
          (this->field16_0x40)._s_0.identify_message = true;
        }
        if ((this->field16_0x40)._s_0.check2 == false) goto LAB_00434ac7;
        if (((((this->field16_0x40)._s_0.cca_warning_message != false) &&
             ((this->field16_0x40)._s_0.check4 == false)) &&
            ((this->field16_0x40)._s_0.check_point5_done != false)) &&
           (((this->field16_0x40)._s_0.identify_message == false &&
            ((this->field16_0x40)._s_0.real_bad == false)))) {
          AudioMessage("misn1206.wav");
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.next_message_time = fVar7 + 20.0;
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1201.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1202.otf",DisplayInterface::colorWhite,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1203.otf",DisplayInterface::colorYellow,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1204.otf",DisplayInterface::colorRed,8.0);
          (this->field16_0x40)._s_0.identify_message = true;
        }
        if (((this->field16_0x40)._s_0.check2 == false) ||
           ((this->field16_0x40)._s_0.check_point5_done == false)) goto LAB_00434ac7;
        if ((this->field16_0x40)._s_0.check3 == false) {
          if ((((this->field16_0x40)._s_0.cca_warning_message == false) &&
              ((this->field16_0x40)._s_0.identify_message == false)) &&
             ((this->field16_0x40)._s_0.real_bad == false)) {
            AudioMessage("misn1206.wav");
            fVar7 = Get_Time();
            (this->field17_0xa0)._s_0.next_message_time = fVar7 + 20.0;
            InfoDisplay::ClearObjectives(&infoDisplay);
            InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorGreen,8.0);
            InfoDisplay::AddObjective(&infoDisplay,"misn1201.otf",DisplayInterface::colorGreen,8.0);
            InfoDisplay::AddObjective(&infoDisplay,"misn1202.otf",DisplayInterface::colorWhite,8.0);
            InfoDisplay::AddObjective(&infoDisplay,"misn1203.otf",DisplayInterface::colorWhite,8.0);
            InfoDisplay::AddObjective(&infoDisplay,"misn1204.otf",DisplayInterface::colorYellow,8.0)
            ;
            (this->field16_0x40)._s_0.identify_message = true;
          }
          goto LAB_00434ac7;
        }
LAB_00434ad1:
        if ((((this->field16_0x40)._s_0.check4 == false) &&
            ((this->field16_0x40)._s_0.check_point5_done != false)) &&
           (((this->field16_0x40)._s_0.cca_warning_message == false &&
            (((this->field16_0x40)._s_0.identify_message == false &&
             ((this->field16_0x40)._s_0.real_bad == false)))))) {
          AudioMessage("misn1206.wav");
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.next_message_time = fVar7 + 20.0;
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1201.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1202.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1203.otf",DisplayInterface::colorWhite,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1204.otf",DisplayInterface::colorYellow,8.0);
          (this->field16_0x40)._s_0.identify_message = true;
        }
      }
      if ((this->field16_0x40)._s_0.check_point3_done == false) {
LAB_00434c8c:
        if ((((this->field16_0x40)._s_0.check2 != false) ||
            ((this->field16_0x40)._s_0.cca_warning_message == false)) ||
           (((this->field16_0x40)._s_0.identify_message != false ||
            (fVar7 = GetDistance((pMVar1->_s_0).user,(this->field18_0x110)._s_0.checkpoint2),
            70.0 <= fVar7)))) goto LAB_00434da5;
        if ((this->field16_0x40)._s_0.better_message == false) {
          CameraReady();
          iVar6 = (pMVar1->_s_0).user;
          (this->field16_0x40)._s_0.good1 = true;
          CameraObject(iVar6,0,700,-0x5dc,iVar6);
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.camera_time = fVar7 + 7.0;
          AudioMessage("misn1210.wav");
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1201.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1202.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1203.otf",DisplayInterface::colorWhite,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1204.otf",DisplayInterface::colorWhite,8.0);
          (this->field16_0x40)._s_0.better_message = true;
          goto LAB_00434da5;
        }
LAB_00434daf:
        if ((((this->field16_0x40)._s_0.check4 == false) &&
            ((this->field16_0x40)._s_0.check_point3_done != false)) &&
           (((this->field16_0x40)._s_0.identify_message == false &&
            ((this->field16_0x40)._s_0.real_bad == false)))) {
          AudioMessage("misn1206.wav");
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.next_message_time = fVar7 + 20.0;
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1201.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1202.otf",DisplayInterface::colorRed,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1203.otf",DisplayInterface::colorWhite,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1204.otf",DisplayInterface::colorWhite,8.0);
          (this->field16_0x40)._s_0.identify_message = true;
        }
        if (((((this->field16_0x40)._s_0.better_message != false) &&
             ((this->field16_0x40)._s_0.check_point5_done != false)) &&
            ((this->field16_0x40)._s_0.check4 == false)) &&
           (((this->field16_0x40)._s_0.identify_message == false &&
            ((this->field16_0x40)._s_0.real_bad == false)))) {
          AudioMessage("misn1206.wav");
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.next_message_time = fVar7 + 20.0;
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1201.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1202.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1203.otf",DisplayInterface::colorWhite,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1204.otf",DisplayInterface::colorYellow,8.0);
          (this->field16_0x40)._s_0.identify_message = true;
        }
      }
      else {
        if ((this->field16_0x40)._s_0.check2 == false) {
          if (((((this->field16_0x40)._s_0.cca_warning_message == false) &&
               ((this->field16_0x40)._s_0.identify_message == false)) &&
              ((this->field16_0x40)._s_0.better_message == false)) &&
             ((this->field16_0x40)._s_0.real_bad == false)) {
            AudioMessage("misn1205.wav");
            InfoDisplay::ClearObjectives(&infoDisplay);
            InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorGreen,8.0);
            InfoDisplay::AddObjective(&infoDisplay,"misn1201.otf",DisplayInterface::colorWhite,8.0);
            InfoDisplay::AddObjective(&infoDisplay,"misn1202.otf",DisplayInterface::colorYellow,8.0)
            ;
            InfoDisplay::AddObjective(&infoDisplay,"misn1203.otf",DisplayInterface::colorWhite,8.0);
            InfoDisplay::AddObjective(&infoDisplay,"misn1204.otf",DisplayInterface::colorWhite,8.0);
            (this->field16_0x40)._s_0.cca_warning_message = true;
          }
          goto LAB_00434c8c;
        }
LAB_00434da5:
        if ((this->field16_0x40)._s_0.better_message != false) goto LAB_00434daf;
      }
      if ((((this->field16_0x40)._s_0.check2 == false) &&
          ((this->field16_0x40)._s_0.check_point4_done != false)) &&
         (((this->field16_0x40)._s_0.cca_warning_message != false &&
          ((((this->field16_0x40)._s_0.better_message == false &&
            ((this->field16_0x40)._s_0.identify_message == false)) &&
           ((this->field16_0x40)._s_0.real_bad == false)))))) {
        InfoDisplay::ClearObjectives(&infoDisplay);
        InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorGreen,8.0);
        InfoDisplay::AddObjective(&infoDisplay,"misn1201.otf",DisplayInterface::colorWhite,8.0);
        InfoDisplay::AddObjective(&infoDisplay,"misn1202.otf",DisplayInterface::colorYellow,8.0);
        InfoDisplay::AddObjective(&infoDisplay,"misn1203.otf",DisplayInterface::colorRed,8.0);
        InfoDisplay::AddObjective(&infoDisplay,"misn1204.otf",DisplayInterface::colorWhite,8.0);
        (this->field16_0x40)._s_0.real_bad = true;
      }
      if (((this->field16_0x40)._s_0.check_point5_done == false) ||
         ((this->field16_0x40)._s_0.cca_warning_message == false)) {
LAB_00435105:
        if ((this->field16_0x40)._s_0.better_message != false) goto LAB_0043510f;
      }
      else {
        if ((this->field16_0x40)._s_0.better_message == false) {
          if ((((this->field16_0x40)._s_0.identify_message == false) &&
              ((this->field16_0x40)._s_0.real_bad == false)) &&
             ((this->field16_0x40)._s_0.check4 == false)) {
            InfoDisplay::ClearObjectives(&infoDisplay);
            InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorGreen,8.0);
            InfoDisplay::AddObjective(&infoDisplay,"misn1201.otf",DisplayInterface::colorWhite,8.0);
            InfoDisplay::AddObjective(&infoDisplay,"misn1202.otf",DisplayInterface::colorYellow,8.0)
            ;
            InfoDisplay::AddObjective(&infoDisplay,"misn1203.otf",DisplayInterface::colorWhite,8.0);
            InfoDisplay::AddObjective(&infoDisplay,"misn1204.otf",DisplayInterface::colorRed,8.0);
            (this->field16_0x40)._s_0.real_bad = true;
          }
          goto LAB_00435105;
        }
LAB_0043510f:
        fVar7 = GetDistance((pMVar1->_s_0).user,(this->field18_0x110)._s_0.checkpoint4);
        if ((((fVar7 < 70.0) && ((this->field16_0x40)._s_0.identify_message == false)) &&
            ((this->field16_0x40)._s_0.real_bad == false)) &&
           ((this->field16_0x40)._s_0.check4 == false)) {
          CameraReady();
          iVar6 = (pMVar1->_s_0).user;
          (this->field16_0x40)._s_0.good3 = true;
          CameraObject(iVar6,0,700,-0x5dc,iVar6);
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.camera_time = fVar7 + 6.0;
          AudioMessage("misn1209.wav");
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1201.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1202.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1203.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1204.otf",DisplayInterface::colorWhite,8.0);
          (this->field16_0x40)._s_0.check4 = true;
        }
      }
      if ((((this->field16_0x40)._s_0.check_point4_done != false) &&
          ((this->field16_0x40)._s_0.check2 == false)) &&
         (((this->field16_0x40)._s_0.cca_warning_message == false &&
          (((this->field16_0x40)._s_0.identify_message == false &&
           ((this->field16_0x40)._s_0.real_bad == false)))))) {
        AudioMessage("misn1206.wav");
        fVar7 = Get_Time();
        (this->field17_0xa0)._s_0.next_message_time = fVar7 + 20.0;
        InfoDisplay::ClearObjectives(&infoDisplay);
        InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorGreen,8.0);
        InfoDisplay::AddObjective(&infoDisplay,"misn1201.otf",DisplayInterface::colorWhite,8.0);
        InfoDisplay::AddObjective(&infoDisplay,"misn1202.otf",DisplayInterface::colorWhite,8.0);
        InfoDisplay::AddObjective(&infoDisplay,"misn1203.otf",DisplayInterface::colorYellow,8.0);
        InfoDisplay::AddObjective(&infoDisplay,"misn1204.otf",DisplayInterface::colorWhite,8.0);
        (this->field16_0x40)._s_0.identify_message = true;
      }
      if ((this->field16_0x40)._s_0.check_point5_done == false) {
LAB_004355c4:
        if ((this->field16_0x40)._s_0.did_it_right != false) goto LAB_004355ca;
      }
      else {
        if (((((this->field16_0x40)._s_0.cca_warning_message == false) &&
             ((this->field16_0x40)._s_0.check2 == false)) &&
            ((this->field16_0x40)._s_0.identify_message == false)) &&
           (((this->field16_0x40)._s_0.real_bad == false &&
            ((this->field16_0x40)._s_0.straight_to_5 == false)))) {
          AudioMessage("misn1206.wav");
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.next_message_time = fVar7 + 15.0;
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1201.otf",DisplayInterface::colorWhite,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1202.otf",DisplayInterface::colorWhite,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1203.otf",DisplayInterface::colorWhite,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1204.otf",DisplayInterface::colorYellow,8.0);
          (this->field16_0x40)._s_0.identify_message = true;
          (this->field16_0x40)._s_0.straight_to_5 = true;
        }
        if ((this->field16_0x40)._s_0.check_point5_done == false) goto LAB_004355c4;
        if ((((this->field16_0x40)._s_0.cca_warning_message != false) &&
            ((this->field16_0x40)._s_0.check4 != false)) &&
           (((this->field16_0x40)._s_0.identify_message == false &&
            (((this->field16_0x40)._s_0.real_bad == false &&
             ((this->field16_0x40)._s_0.final_warned == false)))))) {
          AudioMessage("misn1214.wav");
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.final_warning = fVar7 + 20.0;
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1201.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1202.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1203.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1204.otf",DisplayInterface::colorYellow,8.0);
          (this->field16_0x40)._s_0.final_warned = true;
        }
        if (((((this->field16_0x40)._s_0.check_point5_done == false) ||
             ((this->field16_0x40)._s_0.check4 == false)) ||
            ((this->field16_0x40)._s_0.cca_warning_message != false)) ||
           (((this->field16_0x40)._s_0.identify_message != false ||
            ((this->field16_0x40)._s_0.real_bad != false)))) goto LAB_004355c4;
        if ((this->field16_0x40)._s_0.did_it_right == false) {
          AudioMessage("misn1205.wav");
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.last_warning = fVar7 + 30.0;
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misn1200.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1201.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1202.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1203.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn1204.otf",DisplayInterface::colorGreen,8.0);
          (this->field16_0x40)._s_0.did_it_right = true;
          goto LAB_004355c4;
        }
LAB_004355ca:
        fVar7 = Get_Time();
        if (((this->field17_0xa0)._s_0.last_warning < fVar7) &&
           ((this->field16_0x40)._s_0.final_warned == false)) {
          AudioMessage("misn1214.wav");
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.final_warning = fVar7 + 20.0;
          (this->field16_0x40)._s_0.final_warned = true;
        }
      }
      if (((((this->field16_0x40)._s_0.cca_warning_message == false) ||
           ((this->field16_0x40)._s_0.better_message != false)) ||
          ((this->field16_0x40)._s_0.check4 != false)) ||
         ((this->field16_0x40)._s_0.identify_message != false)) {
LAB_00435635:
        if ((this->field16_0x40)._s_0.last_warned != false) goto LAB_0043563b;
LAB_0043567f:
        if ((this->field16_0x40)._s_0.final_warned != false) goto LAB_00435685;
LAB_004356bd:
        if ((this->field16_0x40)._s_0.identify_message != false) goto LAB_004356c3;
LAB_00435738:
        if ((this->field16_0x40)._s_0.real_bad != false) goto LAB_00435742;
      }
      else {
        if ((this->field16_0x40)._s_0.last_warned == false) {
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.last_warning = fVar7 + 100.0;
          (this->field16_0x40)._s_0.last_warned = true;
          goto LAB_00435635;
        }
LAB_0043563b:
        fVar7 = Get_Time();
        if (((fVar7 <= (this->field17_0xa0)._s_0.last_warning) ||
            ((this->field16_0x40)._s_0.better_message != false)) ||
           ((this->field16_0x40)._s_0.check4 != false)) goto LAB_0043567f;
        if ((this->field16_0x40)._s_0.final_warned == false) {
          AudioMessage("misn1214.wav");
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.final_warning = fVar7 + 40.0;
          (this->field16_0x40)._s_0.final_warned = true;
          goto LAB_0043567f;
        }
LAB_00435685:
        fVar7 = Get_Time();
        if (fVar7 <= (this->field17_0xa0)._s_0.final_warning) goto LAB_004356bd;
        if ((this->field16_0x40)._s_0.identify_message == false) {
          AudioMessage("misn1206.wav");
          fVar7 = Get_Time();
          (this->field16_0x40)._s_0.identify_message = true;
          (this->field17_0xa0)._s_0.next_message_time = fVar7 + 10.0;
          goto LAB_004356bd;
        }
LAB_004356c3:
        fVar7 = Get_Time();
        if (((this->field17_0xa0)._s_0.next_message_time < fVar7) &&
           ((this->field16_0x40)._s_0.real_bad == false)) {
          (this->field16_0x40)._s_0.real_bad = true;
        }
        if ((this->field16_0x40)._s_0.identify_message == false) goto LAB_00435738;
        if ((this->field16_0x40)._s_0.real_bad == false) {
          if ((this->field16_0x40)._s_0.check_point5_done == false) {
            piVar2 = &(this->field18_0x110)._s_0.ccacom_tower;
            Goto((this->field18_0x110)._s_0.guard_tank1,*piVar2,1);
            Goto((this->field18_0x110)._s_0.guard_tank2,*piVar2,1);
          }
          else {
            Follow((this->field18_0x110)._s_0.guard_tank1,(pMVar1->_s_0).user,1);
            Follow((this->field18_0x110)._s_0.guard_tank2,(pMVar1->_s_0).user,1);
          }
          goto LAB_00435738;
        }
LAB_00435742:
        if ((this->field16_0x40)._s_0.discovered == false) {
          AudioMessage("misn1211.wav");
          if ((this->field16_0x40)._s_0.interface_connect == false) {
            InfoDisplay::ClearObjectives(&infoDisplay);
            InfoDisplay::AddObjective(&infoDisplay,"misn1206.otf",DisplayInterface::colorWhite,8.0);
          }
          SetPerceivedTeam((pMVar1->_s_0).user,1);
          iVar6 = BuildObject("svtank",2,(this->field18_0x110)._s_0.spawn_point1);
          (this->field18_0x110)._s_0.guard1 = iVar6;
          iVar6 = BuildObject("svtank",2,(this->field18_0x110)._s_0.spawn_point1);
          (this->field18_0x110)._s_0.guard2 = iVar6;
          iVar6 = BuildObject("svtank",2,(this->field18_0x110)._s_0.spawn_point2);
          (this->field18_0x110)._s_0.guard3 = iVar6;
          iVar6 = BuildObject("svtank",2,(this->field18_0x110)._s_0.spawn_point2);
          (this->field18_0x110)._s_0.guard4 = iVar6;
          Goto((this->field18_0x110)._s_0.parked_tank2,(this->field18_0x110)._s_0.ccacom_tower,1);
          Goto((this->field18_0x110)._s_0.parked_tank1,(this->field18_0x110)._s_0.ccacom_tower,1);
          Attack((this->field18_0x110)._s_0.guard1,(pMVar1->_s_0).user,1);
          Attack((this->field18_0x110)._s_0.guard2,(pMVar1->_s_0).user,1);
          Attack((this->field18_0x110)._s_0.guard3,(pMVar1->_s_0).user,1);
          Attack((this->field18_0x110)._s_0.guard4,(pMVar1->_s_0).user,1);
          Attack((this->field18_0x110)._s_0.patrol1_1,(pMVar1->_s_0).user,1);
          Attack((this->field18_0x110)._s_0.patrol1_2,(pMVar1->_s_0).user,1);
          Attack((this->field18_0x110)._s_0.patrol2_1,(pMVar1->_s_0).user,1);
          Attack((this->field18_0x110)._s_0.patrol2_2,(pMVar1->_s_0).user,1);
          (this->field16_0x40)._s_0.discovered = true;
        }
      }
      if (((((this->field16_0x40)._s_0.discovered != false) &&
           (bVar5 = IsAlive(&(this->field18_0x110)._s_0.guard1), !bVar5)) &&
          (bVar5 = IsAlive(&(this->field18_0x110)._s_0.guard2), !bVar5)) &&
         (bVar5 = IsAlive(&(this->field18_0x110)._s_0.guard3), !bVar5)) {
        iVar6 = BuildObject("svtank",2,(this->field18_0x110)._s_0.spawn_point1);
        (this->field18_0x110)._s_0.guard1 = iVar6;
        iVar6 = BuildObject("svtank",2,(this->field18_0x110)._s_0.spawn_point1);
        (this->field18_0x110)._s_0.guard2 = iVar6;
        iVar6 = BuildObject("svtank",2,(this->field18_0x110)._s_0.spawn_point2);
        (this->field18_0x110)._s_0.guard3 = iVar6;
        iVar6 = BuildObject("svtank",2,(this->field18_0x110)._s_0.spawn_point2);
        (this->field18_0x110)._s_0.guard4 = iVar6;
        Attack((this->field18_0x110)._s_0.guard1,(pMVar1->_s_0).user,1);
        Attack((this->field18_0x110)._s_0.guard2,(pMVar1->_s_0).user,1);
        Attack((this->field18_0x110)._s_0.guard3,(pMVar1->_s_0).user,1);
        Attack((this->field18_0x110)._s_0.guard4,(pMVar1->_s_0).user,1);
        if ((this->field16_0x40)._s_0.follow_spawn == false) {
          piVar2 = &(this->field18_0x110)._s_0.pturret1;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            Goto(*piVar2,"turret1_path",1);
          }
          piVar2 = &(this->field18_0x110)._s_0.pturret6;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            Goto(*piVar2,"turret2_path",1);
          }
        }
      }
      if (((this->field16_0x40)._s_0.cca_warning_message != false) &&
         ((this->field16_0x40)._s_0.follow_spawn == false)) {
        Goto((this->field18_0x110)._s_0.pturret1,"turret1_path",1);
        Goto((this->field18_0x110)._s_0.pturret6,"turret2_path",1);
        fVar7 = GetDistance((pMVar1->_s_0).user,(this->field18_0x110)._s_0.checkpoint4);
        fVar8 = GetDistance((pMVar1->_s_0).user,(this->field18_0x110)._s_0.checkpoint3);
        if (fVar7 <= fVar8) {
          pcVar9 = "4spawn";
        }
        else {
          pcVar9 = "3spawn";
        }
        iVar6 = BuildObject("svfigh",2,pcVar9,0);
        (this->field18_0x110)._s_0.follower = iVar6;
        Follow(iVar6,(pMVar1->_s_0).user,1);
        (this->field16_0x40)._s_0.follow_spawn = true;
      }
      piVar2 = &(this->field18_0x110)._s_0.ccacom_tower;
      fVar7 = GetDistance((pMVar1->_s_0).user,*piVar2);
      if (((fVar7 < 60.0) && ((this->field16_0x40)._s_0.interface_connect == false)) &&
         ((this->field16_0x40)._s_0.interface_complete == false)) {
        AudioMessage("misn1201.wav");
        (this->field16_0x40)._s_0.interface_connect = true;
        fVar7 = Get_Time();
        (this->field17_0xa0)._s_0.interface_time = fVar7 + 45.0;
      }
      fVar7 = GetDistance((pMVar1->_s_0).user,*piVar2);
      if (((fVar7 <= 75.0) || ((this->field16_0x40)._s_0.interface_connect == false)) ||
         ((this->field16_0x40)._s_0.interface_complete != false)) {
LAB_00435aef:
        if ((this->field16_0x40)._s_0.warning_message != false) goto LAB_00435af5;
LAB_00435b57:
        if ((this->field16_0x40)._s_0.interface_connect == false) goto LAB_00435c0c;
        fVar7 = GetDistance((pMVar1->_s_0).user,*piVar2);
        if ((85.0 < fVar7) && ((this->field16_0x40)._s_0.interface_complete == false)) {
          AudioMessage("misn1203.wav");
          (this->field16_0x40)._s_0.interface_connect = false;
        }
        if (((this->field16_0x40)._s_0.interface_connect == false) ||
           (fVar7 = Get_Time(), fVar7 <= (this->field17_0xa0)._s_0.interface_time))
        goto LAB_00435c0c;
        if ((this->field16_0x40)._s_0.interface_complete == false) {
          AudioMessage("misn1204.wav");
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misn1205.otf",DisplayInterface::colorWhite,8.0);
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.win_check_time = fVar7 + 120.0;
          cockpitTimer.active = false;
          CockpitTimer::HideTimer(&cockpitTimer);
          AudioMessage("misn1223.wav");
          (this->field16_0x40)._s_0.interface_complete = true;
          goto LAB_00435c0c;
        }
LAB_00435c16:
        if ((this->field16_0x40)._s_0.discovered == false) {
          piVar2 = &(this->field18_0x110)._s_0.patrol1_1;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            Attack(*piVar2,(pMVar1->_s_0).user,1);
          }
          piVar2 = &(this->field18_0x110)._s_0.patrol1_2;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            Attack(*piVar2,(pMVar1->_s_0).user,1);
          }
          piVar2 = &(this->field18_0x110)._s_0.patrol2_1;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            Attack(*piVar2,(pMVar1->_s_0).user,1);
          }
          piVar2 = &(this->field18_0x110)._s_0.patrol2_2;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            Attack(*piVar2,(pMVar1->_s_0).user,1);
          }
          piVar2 = &(this->field18_0x110)._s_0.patrol3_1;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            Attack(*piVar2,(pMVar1->_s_0).user,1);
          }
          piVar2 = &(this->field18_0x110)._s_0.patrol3_2;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            Attack(*piVar2,(pMVar1->_s_0).user,1);
          }
          piVar2 = &(this->field18_0x110)._s_0.patrol4_1;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            Attack(*piVar2,(pMVar1->_s_0).user,1);
          }
          piVar2 = &(this->field18_0x110)._s_0.patrol4_2;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            Attack(*piVar2,(pMVar1->_s_0).user,1);
          }
          piVar2 = &(this->field18_0x110)._s_0.guard_tank1;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            Attack(*piVar2,(pMVar1->_s_0).user,1);
          }
          piVar2 = &(this->field18_0x110)._s_0.guard_tank2;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            Attack(*piVar2,(pMVar1->_s_0).user,1);
          }
          (this->field16_0x40)._s_0.discovered = true;
        }
      }
      else {
        if ((this->field16_0x40)._s_0.warning_message == false) {
          AudioMessage("misn1202.wav");
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.warning_repeat_time = fVar7 + 5.0;
          (this->field16_0x40)._s_0.warning_message = true;
          goto LAB_00435aef;
        }
LAB_00435af5:
        fVar7 = GetDistance((pMVar1->_s_0).user,*piVar2);
        if (((75.0 < fVar7) &&
            (fVar7 = Get_Time(), (this->field17_0xa0)._s_0.warning_repeat_time < fVar7)) &&
           ((this->field16_0x40)._s_0.interface_connect != false)) {
          (this->field16_0x40)._s_0.warning_message = false;
        }
        if (((this->field16_0x40)._s_0.warning_message == false) ||
           (fVar7 = GetDistance((pMVar1->_s_0).user,*piVar2), 75.0 <= fVar7)) goto LAB_00435b57;
        if ((this->field16_0x40)._s_0.interface_connect != false) {
          (this->field16_0x40)._s_0.warning_message = false;
          goto LAB_00435b57;
        }
LAB_00435c0c:
        if ((this->field16_0x40)._s_0.interface_complete != false) goto LAB_00435c16;
      }
      if ((this->field16_0x40)._s_0.interface_connect != false) {
        if (((this->field16_0x40)._s_0.interface_complete == false) &&
           ((this->field16_0x40)._s_0.noise == false)) {
          AudioMessage("misn1212.wav");
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.next_noise_time = fVar7 + 3.0;
          (this->field16_0x40)._s_0.noise = true;
        }
        if (((((this->field16_0x40)._s_0.interface_connect != false) &&
             ((this->field16_0x40)._s_0.interface_complete == false)) &&
            ((this->field16_0x40)._s_0.noise != false)) &&
           (fVar7 = Get_Time(), (this->field17_0xa0)._s_0.next_noise_time < fVar7)) {
          (this->field16_0x40)._s_0.noise = false;
        }
      }
      if ((((this->field16_0x40)._s_0.key_captured != false) &&
          ((bVar5 = IsInfo("sbhqt1"), bVar5 || (bVar5 = IsInfo("sbhqt2"), bVar5)))) &&
         (((this->field16_0x40)._s_0.camera_swap1 == false ||
          ((this->field16_0x40)._s_0.camera_swap2 == false)))) {
        fVar7 = GetDistance((pMVar1->_s_0).user,(this->field18_0x110)._s_0.center);
        if (fVar7 < 100.0) {
          piVar2 = &(this->field18_0x110)._s_0.start_cam;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            SetTeamNum(*piVar2,1);
          }
          piVar2 = &(this->field18_0x110)._s_0.check2_cam;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            SetTeamNum(*piVar2,1);
          }
          piVar2 = &(this->field18_0x110)._s_0.check3_cam;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            SetTeamNum(*piVar2,1);
          }
          piVar2 = &(this->field18_0x110)._s_0.check4_cam;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            SetTeamNum(*piVar2,1);
          }
          piVar4 = &(this->field18_0x110)._s_0.goal_cam;
          bVar5 = IsAlive(piVar4);
          if (bVar5) {
            SetTeamNum(*piVar4,1);
          }
          SetObjectiveName((this->field18_0x110)._s_0.start_cam,"Check Point");
          SetObjectiveName((this->field18_0x110)._s_0.check2_cam,"Check Point");
          SetObjectiveName((this->field18_0x110)._s_0.check3_cam,"Check Point");
          SetObjectiveName(*piVar2,"Check Point");
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.swap_check = fVar7 + 1.0;
          (this->field16_0x40)._s_0.camera_swap1 = true;
          (this->field16_0x40)._s_0.camera_swap_back = false;
        }
        fVar7 = GetDistance((pMVar1->_s_0).user,(this->field18_0x110)._s_0.checkpoint1);
        if (fVar7 < 100.0) {
          piVar2 = &(this->field18_0x110)._s_0.center_cam;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            SetTeamNum(*piVar2,1);
          }
          fVar7 = Get_Time();
          (this->field17_0xa0)._s_0.swap_check = fVar7 + 1.0;
          (this->field16_0x40)._s_0.camera_swap2 = true;
          (this->field16_0x40)._s_0.camera_swap_back = false;
        }
      }
      if ((((this->field16_0x40)._s_0.camera_swap1 != false) ||
          ((this->field16_0x40)._s_0.camera_swap2 != false)) &&
         (pbVar3 = &(this->field16_0x40)._s_0.camera_noise, *pbVar3 == false)) {
        AudioMessage("misn1229.wav");
        *pbVar3 = true;
      }
      if ((((this->field16_0x40)._s_0.camera_swap_back == false) &&
          (fVar7 = Get_Time(), (this->field17_0xa0)._s_0.swap_check < fVar7)) &&
         (((this->field16_0x40)._s_0.camera_swap1 != false ||
          ((this->field16_0x40)._s_0.camera_swap2 != false)))) {
        fVar7 = Get_Time();
        (this->field17_0xa0)._s_0.swap_check = fVar7 + 1.0;
        if (((this->field16_0x40)._s_0.camera_swap1 != false) &&
           (fVar7 = GetDistance((pMVar1->_s_0).user,(this->field18_0x110)._s_0.center),
           300.0 < fVar7)) {
          AudioMessage("misn1230.wav");
          piVar2 = &(this->field18_0x110)._s_0.start_cam;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            SetTeamNum(*piVar2,3);
          }
          piVar2 = &(this->field18_0x110)._s_0.check2_cam;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            SetTeamNum(*piVar2,3);
          }
          piVar2 = &(this->field18_0x110)._s_0.check3_cam;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            SetTeamNum(*piVar2,3);
          }
          piVar2 = &(this->field18_0x110)._s_0.check4_cam;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            SetTeamNum(*piVar2,3);
          }
          piVar2 = &(this->field18_0x110)._s_0.goal_cam;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            SetTeamNum(*piVar2,3);
          }
          (this->field17_0xa0)._s_0.swap_check = 99999.0;
          (this->field16_0x40)._s_0.camera_swap1 = false;
          (this->field16_0x40)._s_0.camera_noise = false;
          (this->field16_0x40)._s_0.camera_swap_back = true;
        }
        if (((this->field16_0x40)._s_0.camera_swap2 != false) &&
           (fVar7 = GetDistance((pMVar1->_s_0).user,(this->field18_0x110)._s_0.checkpoint1),
           300.0 < fVar7)) {
          AudioMessage("misn1230.wav");
          piVar2 = &(this->field18_0x110)._s_0.center_cam;
          bVar5 = IsAlive(piVar2);
          if (bVar5) {
            SetTeamNum(*piVar2,3);
          }
          (this->field17_0xa0)._s_0.swap_check = 99999.0;
          (this->field16_0x40)._s_0.camera_swap2 = false;
          (this->field16_0x40)._s_0.camera_noise = false;
          (this->field16_0x40)._s_0.camera_swap_back = true;
        }
      }
      if ((this->field16_0x40)._s_0.game_blown == false) goto LAB_00436149;
    }
  }
  if ((this->field16_0x40)._s_0.game_over == false) {
    pcVar9 = (char *)0x0;
    fVar7 = Get_Time();
    FailMission(fVar7 + 10.0,pcVar9);
    (this->field16_0x40)._s_0.game_over = true;
  }
LAB_00436149:
  if ((this->field16_0x40)._s_0.interface_complete != false) {
    fVar7 = Get_Time();
    if ((this->field17_0xa0)._s_0.win_check_time < fVar7) {
      fVar7 = Get_Time();
      (this->field17_0xa0)._s_0.win_check_time = fVar7 + 5.0;
      fVar7 = GetDistance((pMVar1->_s_0).user,(this->field18_0x110)._s_0.nav1);
      if ((fVar7 < 75.0) && ((this->field16_0x40)._s_0.win == false)) {
        AudioMessage("misn1216.wav");
        pcVar9 = "misn12w1.des";
        fVar7 = Get_Time();
        SucceedMission(fVar7 + 7.0,pcVar9);
        (this->field16_0x40)._s_0.win = true;
      }
    }
    if ((this->field16_0x40)._s_0.interface_complete != false) {
      return;
    }
  }
  if ((cockpitTimer.timer == 0) && ((this->field16_0x40)._s_0.game_over == false)) {
    AudioMessage("misn1215.wav");
    pcVar9 = "misn12f1.des";
    fVar7 = Get_Time();
    FailMission(fVar7 + 15.0,pcVar9);
    (this->field16_0x40)._s_0.game_over = true;
  }
  return;
}
