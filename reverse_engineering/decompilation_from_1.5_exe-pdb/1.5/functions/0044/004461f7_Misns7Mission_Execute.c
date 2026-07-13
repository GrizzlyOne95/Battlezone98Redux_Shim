/*
 * Entry: 004461f7
 * Name: Misns7Mission::Execute
 * Namespace: Misns7Mission
 * Signature: void Execute(Misns7Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns7Mission::Execute(Misns7Mission *this)

{
  int *piVar1;
  bool *pbVar2;
  int *piVar3;
  bool bVar4;
  int iVar5;
  float fVar6;
  char *pcVar7;
  long lVar8;
  
  iVar5 = GetPlayerHandle();
  (this->field18_0x130)._s_0.user = iVar5;
  if ((this->field16_0x40)._s_0.start_done == false) {
    SetPilot(1,8);
    SetScrap(2,0x28);
    SetPilot(2,0x28);
    piVar1 = &(this->field18_0x130)._s_0.jail;
    SetObjectiveOn(*piVar1);
    SetObjectiveName(*piVar1,"Military Prison");
    AudioMessage("misns700.wav");
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misns700.otf",DisplayInterface::colorWhite,8.0);
    fVar6 = Get_Time();
    (this->field17_0xa0)._s_0.build_scav_time = fVar6 + 8.0;
    Defend((this->field18_0x130)._s_0.svmuf,1);
    Defend((this->field18_0x130)._s_0.avrig,1);
    Defend((this->field18_0x130)._s_0.bturret1,1);
    Defend((this->field18_0x130)._s_0.bturret2,1);
    fVar6 = Get_Time();
    iVar5 = (this->field18_0x130)._s_0.guntower1;
    (this->field17_0xa0)._s_0.bturret_time = fVar6 + 60.0;
    SetPerceivedTeam(iVar5,2);
    SetPerceivedTeam((this->field18_0x130)._s_0.guntower2,2);
    SetPerceivedTeam((this->field18_0x130)._s_0.svrecycle,2);
    fVar6 = Get_Time();
    iVar5 = (this->field18_0x130)._s_0.avrig;
    (this->field17_0xa0)._s_0.muf_scan_time = fVar6 + 240.0;
    ::Build(iVar5,"abtowe",1);
    (this->field16_0x40)._s_0.start_done = true;
  }
  fVar6 = Get_Time();
  if ((this->field17_0xa0)._s_0.bturret_time < fVar6) {
    fVar6 = Get_Time();
    piVar1 = &(this->field18_0x130)._s_0.bturret1;
    (this->field17_0xa0)._s_0.bturret_time = fVar6 + 180.0;
    bVar4 = IsAlive(piVar1);
    if (bVar4) {
      Defend(*piVar1,1);
    }
    piVar1 = &(this->field18_0x130)._s_0.bturret2;
    bVar4 = IsAlive(piVar1);
    if (bVar4) {
      Defend(*piVar1,1);
    }
  }
  if ((((this->field16_0x40)._s_0.start_done != false) &&
      (fVar6 = GetDistance((this->field18_0x130)._s_0.user,(this->field18_0x130)._s_0.jail),
      fVar6 < 150.0)) && ((this->field16_0x40)._s_0.jail_found == false)) {
    AudioMessage("misns722.wav");
    fVar6 = Get_Time();
    (this->field16_0x40)._s_0.jail_found = true;
    (this->field17_0xa0)._s_0.adjust_timer = fVar6 + 120.0;
  }
  if ((((this->field16_0x40)._s_0.start_done != false) &&
      (fVar6 = Get_Time(), (this->field17_0xa0)._s_0.build_scav_time < fVar6)) &&
     ((this->field16_0x40)._s_0.build_scav == false)) {
    iVar5 = BuildObject("bvscav",2,"muf_point",0);
    (this->field18_0x130)._s_0.avscav1 = iVar5;
    iVar5 = BuildObject("bvscav",2,"muf_point",0);
    piVar1 = &(this->field18_0x130)._s_0.fed_up_scrap;
    (this->field18_0x130)._s_0.avscav2 = iVar5;
    Goto((this->field18_0x130)._s_0.avscav1,*piVar1,0);
    Goto((this->field18_0x130)._s_0.avscav2,*piVar1,0);
    fVar6 = Get_Time();
    (this->field16_0x40)._s_0.build_scav = true;
    (this->field17_0xa0)._s_0.silo_check = fVar6 + 10.0;
  }
  if ((this->field16_0x40)._s_0.jail_dead == false) {
    piVar1 = &(this->field18_0x130)._s_0.avscav1;
    bVar4 = IsAlive(piVar1);
    if ((!bVar4) || (fVar6 = GetHealth(*piVar1), 0.91 <= fVar6)) {
      piVar1 = &(this->field18_0x130)._s_0.avscav2;
      bVar4 = IsAlive(piVar1);
      if ((!bVar4) || (fVar6 = GetHealth(*piVar1), 0.91 <= fVar6)) {
        piVar1 = &(this->field18_0x130)._s_0.main_power;
        bVar4 = IsAlive(piVar1);
        if ((!bVar4) || (fVar6 = GetHealth(*piVar1), 0.95 <= fVar6)) {
          piVar1 = &(this->field18_0x130)._s_0.avrecycle;
          bVar4 = IsAlive(piVar1);
          if ((!bVar4) || (fVar6 = GetHealth(*piVar1), 0.95 <= fVar6)) {
            piVar1 = &(this->field18_0x130)._s_0.avrig;
            bVar4 = IsAlive(piVar1);
            if ((!bVar4) || (fVar6 = GetHealth(*piVar1), 0.95 <= fVar6)) goto LAB_0044651f;
          }
        }
      }
    }
    if ((this->field16_0x40)._s_0.nsdf_adjust == false) {
      (this->field16_0x40)._s_0.nsdf_adjust = true;
    }
  }
LAB_0044651f:
  piVar1 = &(this->field18_0x130)._s_0.jail;
  bVar4 = IsAlive(piVar1);
  if (((bVar4) && ((this->field16_0x40)._s_0.in_base == false)) &&
     (fVar6 = GetHealth(*piVar1), fVar6 < 0.5)) {
    (this->field16_0x40)._s_0.in_base = true;
  }
  if ((((this->field16_0x40)._s_0.jail_found != false) &&
      (fVar6 = Get_Time(), (this->field17_0xa0)._s_0.adjust_timer < fVar6)) &&
     (((this->field16_0x40)._s_0.nsdf_adjust == false &&
      ((this->field16_0x40)._s_0.jail_dead == false)))) {
    (this->field16_0x40)._s_0.nsdf_adjust = true;
  }
  if ((this->field16_0x40)._s_0.nsdf_adjust != false) {
    if ((this->field16_0x40)._s_0.fight1_built == false) {
      iVar5 = BuildObject("bvraz",2,"muf_point",0);
      (this->field18_0x130)._s_0.avfight1 = iVar5;
      Attack(iVar5,(this->field18_0x130)._s_0.user,1);
      fVar6 = Get_Time();
      (this->field16_0x40)._s_0.fight1_built = true;
      (this->field17_0xa0)._s_0.avfigh2_time = fVar6 + 20.0;
    }
    if ((this->field16_0x40)._s_0.nsdf_adjust != false) {
      if ((((this->field16_0x40)._s_0.fight1_built != false) &&
          (fVar6 = Get_Time(), (this->field17_0xa0)._s_0.avfigh2_time < fVar6)) &&
         ((this->field16_0x40)._s_0.fight2_built == false)) {
        iVar5 = BuildObject("bvraz",2,"muf_point",0);
        (this->field18_0x130)._s_0.avfight2 = iVar5;
        Attack(iVar5,(this->field18_0x130)._s_0.user,1);
        fVar6 = Get_Time();
        (this->field16_0x40)._s_0.fight2_built = true;
        (this->field17_0xa0)._s_0.avfigh3_time = fVar6 + 20.0;
      }
      if ((this->field16_0x40)._s_0.nsdf_adjust != false) {
        if ((((this->field16_0x40)._s_0.fight2_built != false) &&
            (fVar6 = Get_Time(), (this->field17_0xa0)._s_0.avfigh3_time < fVar6)) &&
           ((this->field16_0x40)._s_0.fight3_built == false)) {
          iVar5 = BuildObject("bvraz",2,"muf_point",0);
          (this->field18_0x130)._s_0.avfight3 = iVar5;
          bVar4 = IsAlive(&(this->field18_0x130)._s_0.avfight2);
          if (bVar4) {
            iVar5 = (this->field18_0x130)._s_0.apc;
          }
          else {
            iVar5 = (this->field18_0x130)._s_0.user;
          }
          Attack((this->field18_0x130)._s_0.avfight3,iVar5,1);
          SetScrap(2,0x28);
          (this->field16_0x40)._s_0.fight3_built = true;
        }
        if ((((this->field16_0x40)._s_0.nsdf_adjust != false) &&
            (bVar4 = IsAlive(&(this->field18_0x130)._s_0.avfight3), bVar4)) &&
           (((this->field16_0x40)._s_0.jail_dead == false &&
            ((this->field16_0x40)._s_0.build_turret == false)))) {
          iVar5 = BuildObject("bvturr",2,"muf_point",0);
          (this->field18_0x130)._s_0.avturr1 = iVar5;
          (this->field16_0x40)._s_0.build_turret = true;
        }
      }
    }
  }
  bVar4 = IsAlive(&(this->field18_0x130)._s_0.jail);
  if (bVar4) {
LAB_004466f7:
    if ((this->field16_0x40)._s_0.jail_dead != false) goto LAB_004466fc;
  }
  else {
    if ((this->field16_0x40)._s_0.jail_dead == false) {
      CameraReady();
      fVar6 = Get_Time();
      (this->field16_0x40)._s_0.jail_dead = true;
      (this->field17_0xa0)._s_0.con_spawn_time = fVar6 + 1.5;
      goto LAB_004466f7;
    }
LAB_004466fc:
    if ((this->field16_0x40)._s_0.jail_camera_on == false) {
      CameraObject((this->field18_0x130)._s_0.geyser1,-0x5dc,1000,-5000,
                   (this->field18_0x130)._s_0.boxes);
      fVar6 = Get_Time();
      (this->field16_0x40)._s_0.jail_camera_on = true;
      (this->field17_0xa0)._s_0.camera_off_time = fVar6 + 3.5;
    }
  }
  if ((((this->field16_0x40)._s_0.jail_dead != false) &&
      (fVar6 = Get_Time(), (this->field17_0xa0)._s_0.con_spawn_time < fVar6)) &&
     ((this->field16_0x40)._s_0.jail_unit_spawn == false)) {
    iVar5 = BuildObject("sssold",1,"con1_spot",0);
    (this->field18_0x130)._s_0.con1 = iVar5;
    iVar5 = BuildObject("sssold",1,"con2_spot",0);
    (this->field18_0x130)._s_0.con2 = iVar5;
    iVar5 = BuildObject("sssold",1,"con3_spot",0);
    (this->field18_0x130)._s_0.con3 = iVar5;
    SetIndependence((this->field18_0x130)._s_0.con1,0);
    SetIndependence((this->field18_0x130)._s_0.con2,0);
    SetIndependence((this->field18_0x130)._s_0.con3,0);
    GetIn((this->field18_0x130)._s_0.con1,(this->field18_0x130)._s_0.apc,1);
    GetIn((this->field18_0x130)._s_0.con2,(this->field18_0x130)._s_0.apc,1);
    GetIn((this->field18_0x130)._s_0.con3,(this->field18_0x130)._s_0.apc,1);
    (this->field16_0x40)._s_0.jail_unit_spawn = true;
  }
  if (((this->field16_0x40)._s_0.jail_camera_on == false) ||
     (fVar6 = Get_Time(), fVar6 <= (this->field17_0xa0)._s_0.camera_off_time)) {
LAB_0044683f:
    if ((this->field16_0x40)._s_0.jail_camera_off != false) goto LAB_00446848;
  }
  else {
    if ((this->field16_0x40)._s_0.jail_camera_off == false) {
      CameraFinish();
      fVar6 = Get_Time();
      (this->field16_0x40)._s_0.jail_camera_off = true;
      (this->field17_0xa0)._s_0.muf_build_time = fVar6 + 5.0;
      goto LAB_0044683f;
    }
LAB_00446848:
    if ((this->field16_0x40)._s_0.closer_message == false) {
      fVar6 = GetDistance((this->field18_0x130)._s_0.apc,(this->field18_0x130)._s_0.boxes);
      if (70.0 < fVar6) {
        AudioMessage("misns710.wav");
      }
      (this->field16_0x40)._s_0.closer_message = true;
    }
    if ((this->field16_0x40)._s_0.jail_camera_off != false) {
      piVar1 = &(this->field18_0x130)._s_0.apc;
      bVar4 = IsAlive(piVar1);
      if ((((bVar4) && (fVar6 = Get_Time(), (this->field17_0xa0)._s_0.avfigh2_time < fVar6)) &&
          ((this->field16_0x40)._s_0.fully_loaded == false)) &&
         ((fVar6 = GetHealth(*piVar1), fVar6 < 0.8 &&
          (pbVar2 = &(this->field16_0x40)._s_0.apc_panic_message, *pbVar2 == false)))) {
        AudioMessage("misns723.wav");
        *pbVar2 = true;
      }
      if ((((this->field16_0x40)._s_0.jail_camera_off != false) &&
          (fVar6 = Get_Time(), (this->field17_0xa0)._s_0.muf_build_time < fVar6)) &&
         ((this->field16_0x40)._s_0.avmuf_built == false)) {
        iVar5 = BuildObject("bvmuf",2,"muf_point",0);
        piVar1 = &(this->field18_0x130)._s_0.avmuf;
        *piVar1 = iVar5;
        Defend(iVar5,1);
        Goto(*piVar1,(this->field18_0x130)._s_0.geyser1,1);
        fVar6 = Get_Time();
        (this->field16_0x40)._s_0.avmuf_built = true;
        (this->field17_0xa0)._s_0.avfigh1_time = fVar6 + 30.0;
      }
    }
  }
  bVar4 = IsAlive(&(this->field18_0x130)._s_0.avtank1);
  if (bVar4) {
    (this->field16_0x40)._s_0.muf_deployed = true;
  }
  if ((((this->field16_0x40)._s_0.avmuf_built != false) &&
      (fVar6 = Get_Time(), (this->field17_0xa0)._s_0.avfigh1_time < fVar6)) &&
     ((this->field16_0x40)._s_0.fight1_built == false)) {
    iVar5 = BuildObject("bvraz",2,"muf_point",0);
    (this->field18_0x130)._s_0.avfight1 = iVar5;
    SetPerceivedTeam((this->field18_0x130)._s_0.guntower1,2);
    SetPerceivedTeam((this->field18_0x130)._s_0.guntower2,2);
    SetPerceivedTeam((this->field18_0x130)._s_0.svrecycle,2);
    fVar6 = Get_Time();
    (this->field16_0x40)._s_0.fight1_built = true;
    (this->field17_0xa0)._s_0.avfigh2_time = fVar6 + 30.0;
  }
  if ((((this->field16_0x40)._s_0.avmuf_built != false) &&
      ((this->field16_0x40)._s_0.fight1_built != false)) &&
     ((fVar6 = Get_Time(), (this->field17_0xa0)._s_0.avfigh2_time < fVar6 &&
      ((this->field16_0x40)._s_0.fight2_built == false)))) {
    iVar5 = BuildObject("bvraz",2,"muf_point",0);
    (this->field18_0x130)._s_0.avfight2 = iVar5;
    bVar4 = IsAlive(&(this->field18_0x130)._s_0.avfight1);
    if ((bVar4) &&
       (fVar6 = GetDistance((this->field18_0x130)._s_0.apc,(this->field18_0x130)._s_0.boxes),
       fVar6 < 200.0)) {
      Attack((this->field18_0x130)._s_0.avfight2,(this->field18_0x130)._s_0.apc,1);
    }
    SetAIP("misns7.aip",2);
    SetPerceivedTeam((this->field18_0x130)._s_0.guntower1,2);
    SetPerceivedTeam((this->field18_0x130)._s_0.guntower2,2);
    SetPerceivedTeam((this->field18_0x130)._s_0.svrecycle,2);
    AddScrap(2,0x28);
    (this->field16_0x40)._s_0.fight2_built = true;
  }
  piVar1 = &(this->field18_0x130)._s_0.avturr1;
  bVar4 = IsAlive(piVar1);
  if ((bVar4) && ((this->field16_0x40)._s_0.turret_move1 == false)) {
    Goto(*piVar1,"turret_spot",1);
    (this->field16_0x40)._s_0.turret_move1 = true;
  }
  if (((this->field16_0x40)._s_0.avmuf_built == false) ||
     (bVar4 = IsAlive(&(this->field18_0x130)._s_0.avmuf), bVar4)) {
LAB_00446b19:
    if ((this->field16_0x40)._s_0.plan_b != false) goto LAB_00446b1e;
  }
  else {
    if ((this->field16_0x40)._s_0.plan_b == false) {
      AddScrap(2,0x14);
      SetAIP("misns7c.aip",2);
      SetPerceivedTeam((this->field18_0x130)._s_0.guntower1,2);
      SetPerceivedTeam((this->field18_0x130)._s_0.guntower2,2);
      SetPerceivedTeam((this->field18_0x130)._s_0.svrecycle,2);
      (this->field16_0x40)._s_0.plan_c = false;
      (this->field16_0x40)._s_0.plan_b = true;
      goto LAB_00446b19;
    }
LAB_00446b1e:
    piVar1 = &(this->field18_0x130)._s_0.avmuf;
    bVar4 = IsAlive(piVar1);
    if ((bVar4) && ((this->field16_0x40)._s_0.plan_c == false)) {
      if ((this->field16_0x40)._s_0.plan_a == false) {
        pcVar7 = "misns7.aip";
      }
      else {
        pcVar7 = "misns7a.aip";
      }
      SetAIP(pcVar7,2);
      SetPerceivedTeam((this->field18_0x130)._s_0.guntower1,2);
      SetPerceivedTeam((this->field18_0x130)._s_0.guntower2,2);
      SetPerceivedTeam((this->field18_0x130)._s_0.svrecycle,2);
      Goto(*piVar1,(this->field18_0x130)._s_0.geyser1,1);
      (this->field16_0x40)._s_0.plan_b = false;
      (this->field16_0x40)._s_0.plan_c = true;
    }
  }
  if ((this->field16_0x40)._s_0.jail_unit_spawn != false) {
    bVar4 = IsAlive(&(this->field18_0x130)._s_0.con1);
    if ((!bVar4) && ((this->field16_0x40)._s_0.con1_in_apc == false)) {
      (this->field16_0x40)._s_0.con1_dead = true;
    }
    if ((this->field16_0x40)._s_0.jail_unit_spawn != false) {
      bVar4 = IsAlive(&(this->field18_0x130)._s_0.con2);
      if ((!bVar4) && ((this->field16_0x40)._s_0.con2_in_apc == false)) {
        (this->field16_0x40)._s_0.con2_dead = true;
      }
      if ((this->field16_0x40)._s_0.jail_unit_spawn != false) {
        bVar4 = IsAlive(&(this->field18_0x130)._s_0.con3);
        if ((!bVar4) && ((this->field16_0x40)._s_0.con3_in_apc == false)) {
          (this->field16_0x40)._s_0.con3_dead = true;
        }
        if (((((this->field16_0x40)._s_0.jail_unit_spawn != false) &&
             (fVar6 = GetDistance((this->field18_0x130)._s_0.con1,(this->field18_0x130)._s_0.apc),
             fVar6 < 20.0)) && ((this->field16_0x40)._s_0.con1_dead == false)) &&
           ((this->field16_0x40)._s_0.con1_in_apc == false)) {
          fVar6 = Get_Time();
          (this->field16_0x40)._s_0.con1_in_apc = true;
          (this->field17_0xa0)._s_0.con1_pickup_time = fVar6 + 0.2;
        }
      }
    }
  }
  if ((((this->field16_0x40)._s_0.con1_in_apc != false) &&
      (fVar6 = Get_Time(), (this->field17_0xa0)._s_0.con1_pickup_time < fVar6)) &&
     ((this->field16_0x40)._s_0.con1_safe == false)) {
    RemoveObject((this->field18_0x130)._s_0.con1);
    AddPilot(1,1);
    AudioMessage("misns702.wav");
    fVar6 = Get_Time();
    (this->field16_0x40)._s_0.pick_up = true;
    (this->field16_0x40)._s_0.con1_safe = true;
    (this->field17_0xa0)._s_0.goo_time = fVar6 + 5.0;
  }
  if ((((this->field16_0x40)._s_0.jail_unit_spawn == false) ||
      (fVar6 = GetDistance((this->field18_0x130)._s_0.con2,(this->field18_0x130)._s_0.apc),
      20.0 <= fVar6)) || ((this->field16_0x40)._s_0.con2_dead != false)) {
LAB_00446cd1:
    if ((this->field16_0x40)._s_0.con2_in_apc != false) goto LAB_00446cd6;
  }
  else {
    if ((this->field16_0x40)._s_0.con2_in_apc == false) {
      fVar6 = Get_Time();
      (this->field16_0x40)._s_0.con2_in_apc = true;
      (this->field17_0xa0)._s_0.con2_pickup_time = fVar6 + 0.2;
      goto LAB_00446cd1;
    }
LAB_00446cd6:
    fVar6 = Get_Time();
    if (((this->field17_0xa0)._s_0.con2_pickup_time < fVar6) &&
       ((this->field16_0x40)._s_0.con2_safe == false)) {
      RemoveObject((this->field18_0x130)._s_0.con2);
      AddPilot(1,1);
      AudioMessage("misns702.wav");
      fVar6 = Get_Time();
      (this->field16_0x40)._s_0.pick_up = true;
      (this->field16_0x40)._s_0.con2_safe = true;
      (this->field17_0xa0)._s_0.goo_time = fVar6 + 5.0;
    }
  }
  if ((((this->field16_0x40)._s_0.jail_unit_spawn == false) ||
      (fVar6 = GetDistance((this->field18_0x130)._s_0.con3,(this->field18_0x130)._s_0.apc),
      20.0 <= fVar6)) || ((this->field16_0x40)._s_0.con3_dead != false)) {
LAB_00446d65:
    if ((this->field16_0x40)._s_0.con3_in_apc != false) goto LAB_00446d6a;
  }
  else {
    if ((this->field16_0x40)._s_0.con3_in_apc == false) {
      fVar6 = Get_Time();
      (this->field16_0x40)._s_0.con3_in_apc = true;
      (this->field17_0xa0)._s_0.con3_pickup_time = fVar6 + 0.2;
      goto LAB_00446d65;
    }
LAB_00446d6a:
    fVar6 = Get_Time();
    if (((this->field17_0xa0)._s_0.con3_pickup_time < fVar6) &&
       ((this->field16_0x40)._s_0.con3_safe == false)) {
      RemoveObject((this->field18_0x130)._s_0.con3);
      AddPilot(1,1);
      AudioMessage("misns702.wav");
      fVar6 = Get_Time();
      (this->field16_0x40)._s_0.pick_up = true;
      (this->field16_0x40)._s_0.con3_safe = true;
      (this->field17_0xa0)._s_0.goo_time = fVar6 + 5.0;
    }
  }
  if ((((this->field16_0x40)._s_0.con1_safe != false) &&
      ((this->field16_0x40)._s_0.con2_safe != false)) &&
     (((this->field16_0x40)._s_0.con3_safe != false &&
      (((((this->field16_0x40)._s_0.fully_loaded == false &&
         ((this->field16_0x40)._s_0.first_message_done == false)) &&
        ((this->field16_0x40)._s_0.get_recycle == false)) &&
       (((this->field16_0x40)._s_0.get_muf == false &&
        ((this->field16_0x40)._s_0.get_supply == false)))))))) {
    AudioMessage("misns704.wav");
    (this->field16_0x40)._s_0.fully_loaded = true;
    fVar6 = Get_Time();
    (this->field17_0xa0)._s_0.muf_message_time = fVar6 + 3.0;
    fVar6 = Get_Time();
    (this->field17_0xa0)._s_0.check_a = fVar6 + 1.0;
    fVar6 = Get_Time();
    (this->field17_0xa0)._s_0.check_b = fVar6 + 2.0;
    fVar6 = Get_Time();
    (this->field16_0x40)._s_0.first_message_done = true;
    (this->field17_0xa0)._s_0.check_c = fVar6 + 3.0;
  }
  bVar4 = (this->field16_0x40)._s_0.con1_safe;
  if (((bVar4 != false) &&
      (((((this->field16_0x40)._s_0.con2_safe != false &&
         ((this->field16_0x40)._s_0.con3_dead != false)) &&
        ((this->field16_0x40)._s_0.two_loaded == false)) ||
       ((((bVar4 != false && ((this->field16_0x40)._s_0.con2_dead != false)) &&
         ((this->field16_0x40)._s_0.con3_safe != false)) &&
        ((this->field16_0x40)._s_0.two_loaded == false)))))) ||
     ((((((this->field16_0x40)._s_0.con1_dead != false &&
         ((this->field16_0x40)._s_0.con2_safe != false)) &&
        (((this->field16_0x40)._s_0.con3_safe != false &&
         (((this->field16_0x40)._s_0.two_loaded == false &&
          ((this->field16_0x40)._s_0.first_message_done == false)))))) &&
       ((this->field16_0x40)._s_0.get_recycle == false)) &&
      (((this->field16_0x40)._s_0.get_muf == false &&
       ((this->field16_0x40)._s_0.get_supply == false)))))) {
    AudioMessage("misns705.wav");
    (this->field16_0x40)._s_0.two_loaded = true;
    fVar6 = Get_Time();
    (this->field17_0xa0)._s_0.muf_message_time = fVar6 + 3.0;
    fVar6 = Get_Time();
    (this->field17_0xa0)._s_0.check_a = fVar6 + 1.0;
    fVar6 = Get_Time();
    (this->field17_0xa0)._s_0.check_b = fVar6 + 2.0;
    fVar6 = Get_Time();
    (this->field16_0x40)._s_0.first_message_done = true;
    (this->field17_0xa0)._s_0.check_c = fVar6 + 3.0;
  }
  if ((((((this->field16_0x40)._s_0.con1_safe != false) &&
        ((this->field16_0x40)._s_0.con2_dead != false)) &&
       ((this->field16_0x40)._s_0.con3_dead != false)) &&
      ((this->field16_0x40)._s_0.one_loaded == false)) ||
     ((bVar4 = (this->field16_0x40)._s_0.con1_dead, bVar4 != false &&
      (((((this->field16_0x40)._s_0.con2_safe != false &&
         ((this->field16_0x40)._s_0.con3_dead != false)) &&
        ((this->field16_0x40)._s_0.one_loaded == false)) ||
       (((bVar4 != false && ((this->field16_0x40)._s_0.con2_dead != false)) &&
        (((this->field16_0x40)._s_0.con3_safe != false &&
         (((((this->field16_0x40)._s_0.one_loaded == false &&
            ((this->field16_0x40)._s_0.first_message_done == false)) &&
           ((this->field16_0x40)._s_0.get_recycle == false)) &&
          (((this->field16_0x40)._s_0.get_muf == false &&
           ((this->field16_0x40)._s_0.get_supply == false)))))))))))))) {
    AudioMessage("misns706.wav");
    (this->field16_0x40)._s_0.one_loaded = true;
    fVar6 = Get_Time();
    (this->field17_0xa0)._s_0.muf_message_time = fVar6 + 3.0;
    fVar6 = Get_Time();
    (this->field17_0xa0)._s_0.check_a = fVar6 + 1.0;
    fVar6 = Get_Time();
    (this->field17_0xa0)._s_0.check_b = fVar6 + 2.0;
    fVar6 = Get_Time();
    (this->field16_0x40)._s_0.first_message_done = true;
    (this->field17_0xa0)._s_0.check_c = fVar6 + 3.0;
  }
  piVar1 = &(this->field18_0x130)._s_0.apc;
  bVar4 = IsAlive(piVar1);
  if (((bVar4) && ((this->field16_0x40)._s_0.pick_up != false)) &&
     ((fVar6 = Get_Time(), (this->field17_0xa0)._s_0.goo_time < fVar6 &&
      ((this->field16_0x40)._s_0.first_message_done == false)))) {
    fVar6 = Get_Time();
    (this->field17_0xa0)._s_0.goo_time = fVar6 + 5.0;
    iVar5 = CountUnitsNearObject(*piVar1,200.0,2,(char *)0x0);
    (this->field19_0x264)._s_0.stuff = iVar5;
    if (iVar5 == 0) {
      piVar3 = &(this->field18_0x130)._s_0.con1;
      bVar4 = IsAlive(piVar3);
      if (bVar4) {
        RemoveObject(*piVar3);
      }
      piVar3 = &(this->field18_0x130)._s_0.con2;
      bVar4 = IsAlive(piVar3);
      if (bVar4) {
        RemoveObject(*piVar3);
      }
      piVar3 = &(this->field18_0x130)._s_0.con3;
      bVar4 = IsAlive(piVar3);
      if (bVar4) {
        RemoveObject(*piVar3);
      }
    }
  }
  bVar4 = IsAlive(piVar1);
  if ((((bVar4) && ((this->field16_0x40)._s_0.first_message_done != false)) &&
      (fVar6 = Get_Time(), (this->field17_0xa0)._s_0.muf_message_time < fVar6)) &&
     ((this->field16_0x40)._s_0.muf_message == false)) {
    fVar6 = Get_Time();
    (this->field17_0xa0)._s_0.muf_message_time = fVar6 + 3.0;
    iVar5 = CountUnitsNearObject(*piVar1,200.0,2,(char *)0x0);
    (this->field19_0x264)._s_0.stuff4 = iVar5;
    if (iVar5 == 0) {
      if ((this->field16_0x40)._s_0.fully_loaded == false) {
        if ((this->field16_0x40)._s_0.two_loaded != false) {
          AudioMessage("misns725.wav");
          pcVar7 = "misns718.wav";
          goto LAB_004470f8;
        }
        if ((this->field16_0x40)._s_0.one_loaded != false) {
          AudioMessage("misns725.wav");
          pcVar7 = "misns708.wav";
          goto LAB_004470f8;
        }
      }
      else {
        AudioMessage("misns724.wav");
        pcVar7 = "misns717.wav";
LAB_004470f8:
        AudioMessage(pcVar7);
        fVar6 = Get_Time();
        (this->field17_0xa0)._s_0.muf_message_time = fVar6 + 30.0;
      }
      InfoDisplay::ClearObjectives(&infoDisplay);
      InfoDisplay::AddObjective(&infoDisplay,"misns703.otf",DisplayInterface::colorGreen,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misns701.otf",DisplayInterface::colorWhite,8.0);
      (this->field16_0x40)._s_0.muf_message = true;
    }
  }
  if ((((this->field16_0x40)._s_0.muf_message2 == false) &&
      ((this->field16_0x40)._s_0.muf_message != false)) &&
     (fVar6 = Get_Time(), (this->field17_0xa0)._s_0.muf_message_time < fVar6)) {
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misns703.otf",DisplayInterface::colorGreen,8.0);
    InfoDisplay::AddObjective(&infoDisplay,"misns701.otf",DisplayInterface::colorWhite,8.0);
    InfoDisplay::AddObjective(&infoDisplay,"misns702.otf",DisplayInterface::colorWhite,8.0);
    (this->field16_0x40)._s_0.muf_message2 = true;
  }
  if ((this->field16_0x40)._s_0.first_message_done == false) {
LAB_00447366:
    if ((this->field16_0x40)._s_0.get_recycle != false) goto LAB_0044736b;
  }
  else {
    if ((this->field16_0x40)._s_0.get_recycle == false) {
      fVar6 = Get_Time();
      if (((this->field17_0xa0)._s_0.check_a < fVar6) &&
         (fVar6 = GetDistance(*piVar1,(this->field18_0x130)._s_0.svrecycle), fVar6 < 50.0)) {
        fVar6 = Get_Time();
        (this->field17_0xa0)._s_0.check_a = fVar6 + 3.0;
        if ((this->field16_0x40)._s_0.apc_empty == false) {
          if ((((this->field16_0x40)._s_0.fully_loaded != false) &&
              ((this->field16_0x40)._s_0.get_recycle == false)) &&
             ((this->field16_0x40)._s_0.down_to_two == false)) {
            (this->field16_0x40)._s_0.get_recycle = true;
            CameraReady();
            Stop(*piVar1,0);
            fVar6 = Get_Time();
            (this->field16_0x40)._s_0.down_to_two = true;
            (this->field17_0xa0)._s_0.unit_spawn_time1 = fVar6 + 2.0;
          }
          if ((this->field16_0x40)._s_0.apc_empty == false) {
            if ((((this->field16_0x40)._s_0.two_loaded != false) &&
                ((this->field16_0x40)._s_0.get_recycle == false)) &&
               ((this->field16_0x40)._s_0.down_to_one == false)) {
              (this->field16_0x40)._s_0.get_recycle = true;
              CameraReady();
              Stop(*piVar1,0);
              fVar6 = Get_Time();
              (this->field16_0x40)._s_0.down_to_one = true;
              (this->field17_0xa0)._s_0.unit_spawn_time1 = fVar6 + 2.0;
            }
            if ((this->field16_0x40)._s_0.apc_empty == false) {
              if (((this->field16_0x40)._s_0.one_loaded != false) &&
                 ((this->field16_0x40)._s_0.get_recycle == false)) {
                (this->field16_0x40)._s_0.get_recycle = true;
                CameraReady();
                Stop(*piVar1,0);
                fVar6 = Get_Time();
                (this->field16_0x40)._s_0.apc_empty = true;
                (this->field17_0xa0)._s_0.unit_spawn_time1 = fVar6 + 2.0;
              }
              if ((this->field16_0x40)._s_0.apc_empty == false) {
                if ((((this->field16_0x40)._s_0.down_to_two != false) &&
                    ((this->field16_0x40)._s_0.get_recycle == false)) &&
                   ((this->field16_0x40)._s_0.down_to_one == false)) {
                  (this->field16_0x40)._s_0.get_recycle = true;
                  CameraReady();
                  Stop(*piVar1,0);
                  fVar6 = Get_Time();
                  (this->field16_0x40)._s_0.down_to_one = true;
                  (this->field17_0xa0)._s_0.unit_spawn_time1 = fVar6 + 2.0;
                }
                if (((this->field16_0x40)._s_0.apc_empty == false) &&
                   ((this->field16_0x40)._s_0.down_to_one != false)) {
                  if ((this->field16_0x40)._s_0.get_recycle != false) goto LAB_0044736b;
                  (this->field16_0x40)._s_0.get_recycle = true;
                  CameraReady();
                  Stop(*piVar1,0);
                  fVar6 = Get_Time();
                  (this->field16_0x40)._s_0.apc_empty = true;
                  (this->field17_0xa0)._s_0.unit_spawn_time1 = fVar6 + 2.0;
                }
              }
            }
          }
        }
      }
      goto LAB_00447366;
    }
LAB_0044736b:
    if ((this->field16_0x40)._s_0.camera_off_recycle == false) {
      iVar5 = (this->field18_0x130)._s_0.svrecycle;
      CameraObject(iVar5,-4000,1000,2000,iVar5);
      (this->field16_0x40)._s_0.camera_on_recycle = true;
    }
  }
  if (((this->field16_0x40)._s_0.camera_on_recycle == false) ||
     (fVar6 = Get_Time(), fVar6 <= (this->field17_0xa0)._s_0.unit_spawn_time1)) {
LAB_004473e1:
    if ((this->field16_0x40)._s_0.svrecycle_unit_spawn != false) goto LAB_004473ea;
  }
  else {
    if ((this->field16_0x40)._s_0.svrecycle_unit_spawn == false) {
      iVar5 = BuildObject("sssold",1,*piVar1);
      (this->field18_0x130)._s_0.engineer = iVar5;
      Retreat(iVar5,(this->field18_0x130)._s_0.svrecycle,1);
      AddPilot(1,-1);
      (this->field16_0x40)._s_0.svrecycle_unit_spawn = true;
      goto LAB_004473e1;
    }
LAB_004473ea:
    if (((this->field16_0x40)._s_0.svrecycle_on == false) &&
       (fVar6 = GetDistance((this->field18_0x130)._s_0.engineer,(this->field18_0x130)._s_0.svrecycle
                           ), fVar6 < 25.0)) {
      RemoveObject((this->field18_0x130)._s_0.engineer);
      (this->field16_0x40)._s_0.svrecycle_on = true;
    }
    if ((((this->field16_0x40)._s_0.svrecycle_unit_spawn != false) &&
        ((this->field16_0x40)._s_0.camera_off_recycle == false)) &&
       (((this->field16_0x40)._s_0.svrecycle_on != false || (bVar4 = CameraCancelled(), bVar4)))) {
      CameraFinish();
      bVar4 = IsAlive(&(this->field18_0x130)._s_0.engineer);
      if (bVar4) {
        RemoveObject((this->field18_0x130)._s_0.engineer);
      }
      iVar5 = BuildObject("svmine",0,(this->field18_0x130)._s_0.svrecycle);
      (this->field18_0x130)._s_0.temp = iVar5;
      Defend(iVar5,1);
      RemoveObject((this->field18_0x130)._s_0.svrecycle);
      iVar5 = BuildObject("svrecy",1,(this->field18_0x130)._s_0.temp);
      (this->field18_0x130)._s_0.svrecycle = iVar5;
      RemoveObject((this->field18_0x130)._s_0.temp);
      bVar4 = (this->field16_0x40)._s_0.camera_off_muf;
      if (bVar4 == false) {
        if ((this->field16_0x40)._s_0.camera_off_supply == false) {
          InfoDisplay::ClearObjectives(&infoDisplay);
          pcVar7 = "misns708.otf";
          lVar8 = DisplayInterface::colorWhite;
          goto LAB_004475a2;
        }
      }
      else {
        if ((this->field16_0x40)._s_0.camera_off_supply == false) {
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misns708.otf",DisplayInterface::colorWhite,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misns704.otf",DisplayInterface::colorGreen,8.0);
          pcVar7 = "misns705.otf";
          lVar8 = DisplayInterface::colorWhite;
        }
        else {
          if ((bVar4 == false) || ((this->field16_0x40)._s_0.camera_off_supply == false))
          goto LAB_004475a9;
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misns708.otf",DisplayInterface::colorWhite,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misns704.otf",DisplayInterface::colorGreen,8.0);
          pcVar7 = "misns706.otf";
          lVar8 = DisplayInterface::colorGreen;
        }
LAB_004475a2:
        InfoDisplay::AddObjective(&infoDisplay,pcVar7,lVar8,8.0);
      }
LAB_004475a9:
      AudioMessage("misns727.wav");
      AddScrap(1,0x14);
      SetAIP("misns7a.aip",2);
      SetPerceivedTeam((this->field18_0x130)._s_0.guntower1,2);
      SetPerceivedTeam((this->field18_0x130)._s_0.guntower2,2);
      SetPerceivedTeam((this->field18_0x130)._s_0.svrecycle,2);
      (this->field16_0x40)._s_0.camera_off_recycle = true;
    }
  }
  if ((this->field16_0x40)._s_0.new_muf == false) {
    if ((this->field16_0x40)._s_0.first_message_done == false) {
LAB_00447789:
      if ((this->field16_0x40)._s_0.get_muf != false) goto LAB_0044778e;
    }
    else {
      if ((this->field16_0x40)._s_0.get_muf == false) {
        fVar6 = Get_Time();
        if (((this->field17_0xa0)._s_0.check_b < fVar6) &&
           (fVar6 = GetDistance(*piVar1,(this->field18_0x130)._s_0.svmuf), fVar6 < 40.0)) {
          fVar6 = Get_Time();
          (this->field17_0xa0)._s_0.check_b = fVar6 + 3.0;
          if ((this->field16_0x40)._s_0.apc_empty == false) {
            if ((((this->field16_0x40)._s_0.fully_loaded != false) &&
                ((this->field16_0x40)._s_0.get_muf == false)) &&
               ((this->field16_0x40)._s_0.down_to_two == false)) {
              (this->field16_0x40)._s_0.get_muf = true;
              CameraReady();
              Stop(*piVar1,0);
              fVar6 = Get_Time();
              (this->field16_0x40)._s_0.down_to_two = true;
              (this->field17_0xa0)._s_0.unit_spawn_time1 = fVar6 + 2.0;
            }
            if ((this->field16_0x40)._s_0.apc_empty == false) {
              if ((((this->field16_0x40)._s_0.two_loaded != false) &&
                  ((this->field16_0x40)._s_0.get_muf == false)) &&
                 ((this->field16_0x40)._s_0.down_to_one == false)) {
                (this->field16_0x40)._s_0.get_muf = true;
                CameraReady();
                Stop(*piVar1,0);
                fVar6 = Get_Time();
                (this->field16_0x40)._s_0.down_to_one = true;
                (this->field17_0xa0)._s_0.unit_spawn_time1 = fVar6 + 2.0;
              }
              if ((this->field16_0x40)._s_0.apc_empty == false) {
                if (((this->field16_0x40)._s_0.one_loaded != false) &&
                   ((this->field16_0x40)._s_0.get_muf == false)) {
                  (this->field16_0x40)._s_0.get_muf = true;
                  CameraReady();
                  Stop(*piVar1,0);
                  fVar6 = Get_Time();
                  (this->field16_0x40)._s_0.apc_empty = true;
                  (this->field17_0xa0)._s_0.unit_spawn_time1 = fVar6 + 2.0;
                }
                if ((this->field16_0x40)._s_0.apc_empty == false) {
                  if ((((this->field16_0x40)._s_0.down_to_two != false) &&
                      ((this->field16_0x40)._s_0.get_muf == false)) &&
                     ((this->field16_0x40)._s_0.down_to_one == false)) {
                    (this->field16_0x40)._s_0.get_muf = true;
                    CameraReady();
                    Stop(*piVar1,0);
                    fVar6 = Get_Time();
                    (this->field16_0x40)._s_0.down_to_one = true;
                    (this->field17_0xa0)._s_0.unit_spawn_time1 = fVar6 + 2.0;
                  }
                  if (((this->field16_0x40)._s_0.apc_empty == false) &&
                     ((this->field16_0x40)._s_0.down_to_one != false)) {
                    if ((this->field16_0x40)._s_0.get_muf != false) goto LAB_0044778e;
                    (this->field16_0x40)._s_0.get_muf = true;
                    CameraReady();
                    Stop(*piVar1,0);
                    fVar6 = Get_Time();
                    (this->field16_0x40)._s_0.apc_empty = true;
                    (this->field17_0xa0)._s_0.unit_spawn_time1 = fVar6 + 2.0;
                  }
                }
              }
            }
          }
        }
        goto LAB_00447789;
      }
LAB_0044778e:
      if ((this->field16_0x40)._s_0.camera_off_muf == false) {
        iVar5 = (this->field18_0x130)._s_0.svmuf;
        CameraObject(iVar5,-3000,1000,4000,iVar5);
        (this->field16_0x40)._s_0.camera_on_muf = true;
      }
    }
    if (((this->field16_0x40)._s_0.camera_on_muf != false) &&
       (fVar6 = Get_Time(), (this->field17_0xa0)._s_0.unit_spawn_time1 < fVar6)) {
      if ((this->field16_0x40)._s_0.svmuf_unit_spawn == false) {
        iVar5 = BuildObject("sssold",1,*piVar1);
        (this->field18_0x130)._s_0.engineer = iVar5;
        Retreat(iVar5,(this->field18_0x130)._s_0.svmuf,1);
        AddPilot(1,-1);
        (this->field16_0x40)._s_0.svmuf_unit_spawn = true;
        goto LAB_00447804;
      }
LAB_0044780d:
      if (((this->field16_0x40)._s_0.svmuf_on == false) &&
         (fVar6 = GetDistance((this->field18_0x130)._s_0.engineer,(this->field18_0x130)._s_0.svmuf),
         fVar6 < 20.0)) {
        RemoveObject((this->field18_0x130)._s_0.engineer);
        (this->field16_0x40)._s_0.svmuf_on = true;
      }
      if ((this->field16_0x40)._s_0.svmuf_unit_spawn == false) goto LAB_004478e1;
      if ((this->field16_0x40)._s_0.camera_off_muf == false) {
        if (((this->field16_0x40)._s_0.svmuf_on != false) || (bVar4 = CameraCancelled(), bVar4)) {
          bVar4 = IsAlive(&(this->field18_0x130)._s_0.engineer);
          if (bVar4) {
            RemoveObject((this->field18_0x130)._s_0.engineer);
          }
          iVar5 = BuildObject("svmine",0,(this->field18_0x130)._s_0.svmuf);
          (this->field18_0x130)._s_0.temp = iVar5;
          Defend(iVar5,1);
          RemoveObject((this->field18_0x130)._s_0.svmuf);
          iVar5 = BuildObject("svmuf",1,(this->field18_0x130)._s_0.temp);
          (this->field18_0x130)._s_0.svmuf = iVar5;
          RemoveObject((this->field18_0x130)._s_0.temp);
          AddScrap(1,0x14);
          CameraFinish();
          (this->field16_0x40)._s_0.camera_off_muf = true;
        }
        goto LAB_004478e1;
      }
LAB_004478ea:
      if ((this->field16_0x40)._s_0.supply_message == false) {
        if (((this->field16_0x40)._s_0.supply_first == false) ||
           (AudioMessage("misns709.wav"), (this->field16_0x40)._s_0.supply_first == false)) {
          AudioMessage("misns714.wav");
        }
        if ((this->field16_0x40)._s_0.camera_off_recycle == false) {
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misns703.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misns701.otf",DisplayInterface::colorWhite,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misns704.otf",DisplayInterface::colorGreen,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misns705.otf",DisplayInterface::colorWhite,8.0);
        }
        (this->field16_0x40)._s_0.supply_message = true;
      }
      goto LAB_00447993;
    }
LAB_00447804:
    if ((this->field16_0x40)._s_0.svmuf_unit_spawn != false) goto LAB_0044780d;
LAB_004478e1:
    if ((this->field16_0x40)._s_0.camera_off_muf != false) goto LAB_004478ea;
  }
  else {
LAB_00447993:
    if ((this->field16_0x40)._s_0.camera_off_muf != false) {
      if ((this->field16_0x40)._s_0.first_message_done == false) {
LAB_00447b23:
        if ((this->field16_0x40)._s_0.get_supply != false) goto LAB_00447b28;
      }
      else {
        if ((this->field16_0x40)._s_0.get_supply == false) {
          fVar6 = Get_Time();
          if (((this->field17_0xa0)._s_0.check_c < fVar6) &&
             (fVar6 = GetDistance(*piVar1,(this->field18_0x130)._s_0.supply), fVar6 < 70.0)) {
            fVar6 = Get_Time();
            (this->field17_0xa0)._s_0.check_c = fVar6 + 3.0;
            if ((this->field16_0x40)._s_0.apc_empty == false) {
              if ((((this->field16_0x40)._s_0.fully_loaded != false) &&
                  ((this->field16_0x40)._s_0.get_supply == false)) &&
                 ((this->field16_0x40)._s_0.down_to_two == false)) {
                (this->field16_0x40)._s_0.get_supply = true;
                CameraReady();
                Stop(*piVar1,0);
                fVar6 = Get_Time();
                (this->field16_0x40)._s_0.down_to_two = true;
                (this->field17_0xa0)._s_0.unit_spawn_time1 = fVar6 + 2.0;
              }
              if ((this->field16_0x40)._s_0.apc_empty == false) {
                if ((((this->field16_0x40)._s_0.two_loaded != false) &&
                    ((this->field16_0x40)._s_0.get_supply == false)) &&
                   ((this->field16_0x40)._s_0.down_to_one == false)) {
                  (this->field16_0x40)._s_0.get_supply = true;
                  CameraReady();
                  Stop(*piVar1,0);
                  fVar6 = Get_Time();
                  (this->field16_0x40)._s_0.down_to_one = true;
                  (this->field17_0xa0)._s_0.unit_spawn_time1 = fVar6 + 2.0;
                }
                if ((this->field16_0x40)._s_0.apc_empty == false) {
                  if (((this->field16_0x40)._s_0.one_loaded != false) &&
                     ((this->field16_0x40)._s_0.get_supply == false)) {
                    (this->field16_0x40)._s_0.get_supply = true;
                    CameraReady();
                    Stop(*piVar1,0);
                    fVar6 = Get_Time();
                    (this->field16_0x40)._s_0.apc_empty = true;
                    (this->field17_0xa0)._s_0.unit_spawn_time1 = fVar6 + 2.0;
                  }
                  if ((this->field16_0x40)._s_0.apc_empty == false) {
                    if ((((this->field16_0x40)._s_0.down_to_two != false) &&
                        ((this->field16_0x40)._s_0.get_supply == false)) &&
                       ((this->field16_0x40)._s_0.down_to_one == false)) {
                      (this->field16_0x40)._s_0.get_supply = true;
                      CameraReady();
                      Stop(*piVar1,0);
                      fVar6 = Get_Time();
                      (this->field16_0x40)._s_0.down_to_one = true;
                      (this->field17_0xa0)._s_0.unit_spawn_time1 = fVar6 + 2.0;
                    }
                    if (((this->field16_0x40)._s_0.apc_empty == false) &&
                       ((this->field16_0x40)._s_0.down_to_one != false)) {
                      if ((this->field16_0x40)._s_0.get_supply != false) goto LAB_00447b28;
                      (this->field16_0x40)._s_0.get_supply = true;
                      CameraReady();
                      Stop(*piVar1,0);
                      fVar6 = Get_Time();
                      (this->field16_0x40)._s_0.apc_empty = true;
                      (this->field17_0xa0)._s_0.unit_spawn_time1 = fVar6 + 2.0;
                    }
                  }
                }
              }
            }
          }
          goto LAB_00447b23;
        }
LAB_00447b28:
        if ((this->field16_0x40)._s_0.camera_off_supply == false) {
          iVar5 = (this->field18_0x130)._s_0.supply;
          CameraObject(iVar5,1000,1000,8000,iVar5);
          (this->field16_0x40)._s_0.camera_on_supply = true;
        }
      }
      if (((this->field16_0x40)._s_0.camera_on_supply == false) ||
         (fVar6 = Get_Time(), fVar6 <= (this->field17_0xa0)._s_0.unit_spawn_time1)) {
LAB_00447b9a:
        if ((this->field16_0x40)._s_0.supply_unit_spawn != false) goto LAB_00447ba3;
LAB_00447cbf:
        if ((this->field16_0x40)._s_0.camera_off_supply != false) goto LAB_00447cc4;
      }
      else {
        if ((this->field16_0x40)._s_0.supply_unit_spawn == false) {
          iVar5 = BuildObject("sssold",1,*piVar1);
          (this->field18_0x130)._s_0.engineer = iVar5;
          Retreat(iVar5,"con_path",1);
          AddPilot(1,-1);
          (this->field16_0x40)._s_0.supply_unit_spawn = true;
          goto LAB_00447b9a;
        }
LAB_00447ba3:
        piVar1 = &(this->field18_0x130)._s_0.engineer;
        bVar4 = IsAlive(piVar1);
        if (((bVar4) && ((this->field16_0x40)._s_0.supply_on == false)) &&
           (fVar6 = GetDistance(*piVar1,(this->field18_0x130)._s_0.con_geyser), fVar6 < 30.0)) {
          RemoveObject(*piVar1);
          (this->field16_0x40)._s_0.supply_on = true;
        }
        if ((this->field16_0x40)._s_0.supply_unit_spawn == false) goto LAB_00447cbf;
        if ((this->field16_0x40)._s_0.camera_off_supply == false) {
          if (((this->field16_0x40)._s_0.supply_on != false) || (bVar4 = CameraCancelled(), bVar4))
          {
            piVar1 = &(this->field18_0x130)._s_0.engineer;
            bVar4 = IsAlive(piVar1);
            if (bVar4) {
              RemoveObject(*piVar1);
            }
            if ((this->field16_0x40)._s_0.camera_off_recycle == false) {
              InfoDisplay::ClearObjectives(&infoDisplay);
              InfoDisplay::AddObjective
                        (&infoDisplay,"misns703.otf",DisplayInterface::colorGreen,8.0);
              pcVar7 = "misns701.otf";
            }
            else {
              InfoDisplay::ClearObjectives(&infoDisplay);
              pcVar7 = "misns708.otf";
            }
            InfoDisplay::AddObjective(&infoDisplay,pcVar7,DisplayInterface::colorWhite,8.0);
            InfoDisplay::AddObjective(&infoDisplay,"misns704.otf",DisplayInterface::colorGreen,8.0);
            InfoDisplay::AddObjective(&infoDisplay,"misns706.otf",DisplayInterface::colorGreen,8.0);
            (this->field16_0x40)._s_0.camera_off_supply = true;
            CameraFinish();
          }
          goto LAB_00447cbf;
        }
LAB_00447cc4:
        if ((this->field16_0x40)._s_0.supply2_message == false) {
          AudioMessage("misns707.wav");
          fVar6 = Get_Time();
          (this->field17_0xa0)._s_0.supply_spawn_time = fVar6 + 15.0;
          (this->field16_0x40)._s_0.supply2_message = true;
        }
      }
      if (((this->field16_0x40)._s_0.supply_message == false) ||
         (fVar6 = Get_Time(), fVar6 <= (this->field17_0xa0)._s_0.supply_spawn_time)) {
LAB_00447e03:
        if ((this->field16_0x40)._s_0.supplies_spawned == false) goto LAB_00447e3c;
      }
      else if ((this->field16_0x40)._s_0.supplies_spawned == false) {
        iVar5 = BuildObject("svscav",1,"supply1",0);
        (this->field18_0x130)._s_0.supply1 = iVar5;
        iVar5 = BuildObject("svturr",1,"supply2",0);
        (this->field18_0x130)._s_0.supply2 = iVar5;
        iVar5 = BuildObject("svturr",1,"supply3",0);
        (this->field18_0x130)._s_0.supply3 = iVar5;
        iVar5 = BuildObject("svscav",1,"supply4",0);
        (this->field18_0x130)._s_0.supply4 = iVar5;
        iVar5 = BuildObject("spammo",1,"supply5",0);
        (this->field18_0x130)._s_0.supply5 = iVar5;
        iVar5 = BuildObject("spammo",1,"supply6",0);
        (this->field18_0x130)._s_0.supply6 = iVar5;
        iVar5 = BuildObject("spammo",1,"supply7",0);
        (this->field18_0x130)._s_0.supply7 = iVar5;
        iVar5 = BuildObject("sprepa",1,"supply8",0);
        (this->field18_0x130)._s_0.supply8 = iVar5;
        iVar5 = BuildObject("sprepa",1,"supply9",0);
        (this->field18_0x130)._s_0.supply9 = iVar5;
        Stop((this->field18_0x130)._s_0.supply1,0);
        Stop((this->field18_0x130)._s_0.supply4,0);
        (this->field16_0x40)._s_0.supplies_spawned = true;
        goto LAB_00447e03;
      }
      if ((this->field16_0x40)._s_0.turret_message == false) {
        AudioMessage("misns721.wav");
        Stop((this->field18_0x130)._s_0.supply1,0);
        Stop((this->field18_0x130)._s_0.supply4,0);
        (this->field16_0x40)._s_0.turret_message = true;
      }
    }
  }
LAB_00447e3c:
  piVar1 = &(this->field18_0x130)._s_0.supply;
  bVar4 = IsAlive(piVar1);
  if (((!bVar4) || ((this->field16_0x40)._s_0.camera_off_muf != false)) ||
     (fVar6 = GetDistance((this->field18_0x130)._s_0.user,*piVar1), 70.0 <= fVar6)) {
LAB_00447e82:
    if (((this->field16_0x40)._s_0.supply_first != false) ||
       ((this->field16_0x40)._s_0.camera_off_muf != false)) goto LAB_00447e90;
  }
  else {
    if ((this->field16_0x40)._s_0.supply_first == false) {
      AudioMessage("misns715.wav");
      (this->field16_0x40)._s_0.supply_first = true;
      goto LAB_00447e82;
    }
LAB_00447e90:
    if ((this->field16_0x40)._s_0.plan_a == false) {
      piVar1 = &(this->field18_0x130)._s_0.avsilo;
      bVar4 = IsAlive(piVar1);
      if (bVar4) {
        piVar3 = &(this->field18_0x130)._s_0.avscav1;
        bVar4 = IsAlive(piVar3);
        if (bVar4) {
          Goto(*piVar3,*piVar1,1);
        }
        piVar3 = &(this->field18_0x130)._s_0.avscav2;
        bVar4 = IsAlive(piVar3);
        if (bVar4) {
          Goto(*piVar3,*piVar1,1);
        }
        piVar3 = &(this->field18_0x130)._s_0.avturr1;
        bVar4 = IsAlive(piVar3);
        if (bVar4) {
          Goto(*piVar3,"avsilo_spot1",1);
        }
        piVar3 = &(this->field18_0x130)._s_0.avturr2;
        bVar4 = IsAlive(piVar3);
        if (bVar4) {
          Goto(*piVar3,"avsilo_spot2",1);
        }
        piVar3 = &(this->field18_0x130)._s_0.avfight1;
        bVar4 = IsAlive(piVar3);
        if (bVar4) {
          Goto(*piVar3,*piVar1,0);
        }
        piVar3 = &(this->field18_0x130)._s_0.avfight2;
        bVar4 = IsAlive(piVar3);
        if (bVar4) {
          Goto(*piVar3,*piVar1,0);
        }
      }
      SetAIP("misns7b.aip",2);
      SetPerceivedTeam((this->field18_0x130)._s_0.guntower1,2);
      SetPerceivedTeam((this->field18_0x130)._s_0.guntower2,2);
      SetPerceivedTeam((this->field18_0x130)._s_0.svrecycle,2);
      piVar1 = &(this->field18_0x130)._s_0.avrig;
      bVar4 = IsAlive(piVar1);
      if (bVar4) {
        Defend(*piVar1,1);
      }
      (this->field16_0x40)._s_0.plan_a = true;
    }
  }
  fVar6 = Get_Time();
  if (((this->field17_0xa0)._s_0.muf_scan_time < fVar6) &&
     ((this->field16_0x40)._s_0.muf_located == false)) {
    fVar6 = Get_Time();
    piVar1 = &(this->field18_0x130)._s_0.svmuf;
    (this->field17_0xa0)._s_0.muf_scan_time = fVar6 + 3.0;
    bVar4 = IsAlive(piVar1);
    if (bVar4) {
      iVar5 = CountUnitsNearObject(*piVar1,200.0,2,(char *)0x0);
      (this->field19_0x264)._s_0.stuff2 = iVar5;
      if (0 < iVar5) {
        (this->field16_0x40)._s_0.muf_located = true;
      }
    }
  }
  piVar1 = &(this->field18_0x130)._s_0.avgech;
  bVar4 = IsAlive(piVar1);
  if (bVar4) {
    if ((this->field16_0x40)._s_0.gech_sent == false) {
      if ((this->field16_0x40)._s_0.muf_located == false) {
        piVar3 = &(this->field18_0x130)._s_0.avsilo;
        bVar4 = IsAlive(piVar3);
        if (bVar4) {
          Goto(*piVar1,*piVar3,0);
        }
      }
      else {
        piVar3 = &(this->field18_0x130)._s_0.svmuf;
        bVar4 = IsAlive(piVar3);
        if (bVar4) {
          Attack(*piVar1,*piVar3,1);
        }
      }
      (this->field16_0x40)._s_0.gech_sent = true;
      goto LAB_00448090;
    }
LAB_00448098:
    if ((((this->field16_0x40)._s_0.muf_located != false) &&
        ((this->field16_0x40)._s_0.gech_adjust == false)) && (bVar4 = IsAlive(piVar1), bVar4)) {
      piVar3 = &(this->field18_0x130)._s_0.svmuf;
      bVar4 = IsAlive(piVar3);
      if (bVar4) {
        Attack(*piVar1,*piVar3,1);
        (this->field16_0x40)._s_0.gech_adjust = true;
      }
    }
  }
  else {
LAB_00448090:
    if ((this->field16_0x40)._s_0.gech_sent != false) goto LAB_00448098;
  }
  if (((this->field16_0x40)._s_0.in_base != false) &&
     ((this->field16_0x40)._s_0.build_tower1 == false)) {
    piVar1 = &(this->field18_0x130)._s_0.avrig;
    bVar4 = IsAlive(piVar1);
    if (bVar4) {
      Dropoff(*piVar1,"tower1_spot",1);
      (this->field16_0x40)._s_0.build_tower1 = true;
    }
  }
  if (((this->field16_0x40)._s_0.build_tower1 == false) ||
     (bVar4 = IsAlive(&(this->field18_0x130)._s_0.avtower1), !bVar4)) {
LAB_00448171:
    if ((this->field18_0x130)._s_0.b1 != 0) goto LAB_00448179;
LAB_004481d7:
    if ((this->field16_0x40)._s_0.build_power1 != false) goto LAB_004481df;
LAB_00448258:
    if ((this->field18_0x130)._s_0.b2 != 0) goto LAB_00448260;
  }
  else {
    if ((this->field18_0x130)._s_0.b1 == 0) {
      piVar1 = &(this->field18_0x130)._s_0.avrig;
      bVar4 = IsAlive(piVar1);
      if (bVar4) {
        ::Build(*piVar1,"abwpow",1);
        fVar6 = Get_Time();
        (this->field17_0xa0)._s_0.b1_time = fVar6 + 5.0;
        (this->field18_0x130)._s_0.b1 = 1;
      }
      goto LAB_00448171;
    }
LAB_00448179:
    fVar6 = Get_Time();
    if (fVar6 <= (this->field17_0xa0)._s_0.b1_time) goto LAB_004481d7;
    if ((this->field16_0x40)._s_0.build_power1 == false) {
      piVar1 = &(this->field18_0x130)._s_0.avrig;
      bVar4 = IsAlive(piVar1);
      if (bVar4) {
        AddScrap(2,0x14);
        Dropoff(*piVar1,"power1_spot",1);
        fVar6 = Get_Time();
        (this->field17_0xa0)._s_0.b2_time = fVar6 + 5.0;
        (this->field16_0x40)._s_0.build_power1 = true;
      }
      goto LAB_004481d7;
    }
LAB_004481df:
    if ((((this->field16_0x40)._s_0.main_off != false) ||
        ((this->field16_0x40)._s_0.maint_off != false)) ||
       (bVar4 = IsAlive(&(this->field18_0x130)._s_0.avpower1), !bVar4)) goto LAB_00448258;
    if ((this->field18_0x130)._s_0.b2 == 0) {
      fVar6 = Get_Time();
      if ((this->field17_0xa0)._s_0.b2_time < fVar6) {
        piVar1 = &(this->field18_0x130)._s_0.avrig;
        bVar4 = IsAlive(piVar1);
        if (bVar4) {
          ::Build(*piVar1,"abtowe",1);
          fVar6 = Get_Time();
          (this->field17_0xa0)._s_0.b3_time = fVar6 + 5.0;
          (this->field18_0x130)._s_0.b2 = 1;
        }
      }
      goto LAB_00448258;
    }
LAB_00448260:
    fVar6 = Get_Time();
    if (((this->field17_0xa0)._s_0.b3_time < fVar6) &&
       ((this->field16_0x40)._s_0.build_tower2 == false)) {
      piVar1 = &(this->field18_0x130)._s_0.avrig;
      bVar4 = IsAlive(piVar1);
      if (bVar4) {
        Dropoff(*piVar1,"tower2_spot",1);
        fVar6 = Get_Time();
        (this->field17_0xa0)._s_0.b4_time = fVar6 + 5.0;
        (this->field16_0x40)._s_0.build_tower2 = true;
      }
    }
  }
  bVar4 = IsAlive(&(this->field18_0x130)._s_0.avtower2);
  if (bVar4) {
    piVar1 = &(this->field18_0x130)._s_0.avrig;
    bVar4 = IsAlive(piVar1);
    if (((bVar4) && ((this->field16_0x40)._s_0.new_rig == false)) &&
       ((fVar6 = GetDistance((this->field18_0x130)._s_0.user,*piVar1), 400.0 < fVar6 &&
        (fVar6 = Get_Time(), (this->field17_0xa0)._s_0.b4_time < fVar6)))) {
      RemoveObject(*piVar1);
      fVar6 = Get_Time();
      (this->field17_0xa0)._s_0.rig_check = fVar6 + 10.0;
      (this->field16_0x40)._s_0.new_rig = true;
    }
  }
  if ((this->field16_0x40)._s_0.rig_show != false) {
    piVar1 = &(this->field18_0x130)._s_0.avrig;
    bVar4 = IsAlive(piVar1);
    if ((!bVar4) || (bVar4 = IsAlive(&(this->field18_0x130)._s_0.main_power), bVar4)) {
LAB_0044838b:
      if ((this->field16_0x40)._s_0.main_off != false) goto LAB_00448393;
    }
    else {
      if ((this->field16_0x40)._s_0.main_off == false) {
        ::Build(*piVar1,"abwpow",1);
        fVar6 = Get_Time();
        (this->field17_0xa0)._s_0.bm_time = fVar6 + 10.0;
        (this->field16_0x40)._s_0.main_off = true;
        goto LAB_0044838b;
      }
LAB_00448393:
      fVar6 = Get_Time();
      if ((((this->field17_0xa0)._s_0.bm_time < fVar6) &&
          ((this->field16_0x40)._s_0.main_build == false)) && (bVar4 = IsAlive(piVar1), bVar4)) {
        Dropoff(*piVar1,"main_power",1);
        (this->field16_0x40)._s_0.main_build = true;
      }
    }
    pbVar2 = &(this->field16_0x40)._s_0.main_build;
    if ((*pbVar2 != false) && (bVar4 = IsAlive(&(this->field18_0x130)._s_0.main_power), bVar4)) {
      *pbVar2 = false;
      (this->field16_0x40)._s_0.main_off = false;
    }
    bVar4 = IsAlive(piVar1);
    if (((!bVar4) || (bVar4 = IsAlive(&(this->field18_0x130)._s_0.main_tower), bVar4)) ||
       ((this->field16_0x40)._s_0.main_off != false)) {
LAB_0044844a:
      if ((this->field16_0x40)._s_0.maint_off != false) goto LAB_00448452;
    }
    else {
      if ((this->field16_0x40)._s_0.maint_off == false) {
        ::Build(*piVar1,"abtowe",1);
        fVar6 = Get_Time();
        (this->field17_0xa0)._s_0.bm_time = fVar6 + 10.0;
        (this->field16_0x40)._s_0.maint_off = true;
        goto LAB_0044844a;
      }
LAB_00448452:
      if ((((this->field16_0x40)._s_0.maint_build == false) &&
          (fVar6 = Get_Time(), (this->field17_0xa0)._s_0.bm_time < fVar6)) &&
         (bVar4 = IsAlive(piVar1), bVar4)) {
        Dropoff(*piVar1,"main_tower",1);
        (this->field16_0x40)._s_0.maint_build = true;
      }
    }
    pbVar2 = &(this->field16_0x40)._s_0.maint_build;
    if ((*pbVar2 != false) && (bVar4 = IsAlive(&(this->field18_0x130)._s_0.main_tower), bVar4)) {
      *pbVar2 = false;
      (this->field16_0x40)._s_0.maint_off = false;
    }
  }
  if ((this->field16_0x40)._s_0.rig_show == false) {
    fVar6 = Get_Time();
    if ((this->field17_0xa0)._s_0.rig_check < fVar6) {
      fVar6 = Get_Time();
      (this->field17_0xa0)._s_0.rig_check = fVar6 + 5.0;
      fVar6 = GetDistance((this->field18_0x130)._s_0.user,(this->field18_0x130)._s_0.avrecycle);
      if (fVar6 < 400.0) {
        iVar5 = BuildObject("avcns7",2,"barrack_spot",0);
        piVar1 = &(this->field18_0x130)._s_0.avrig;
        *piVar1 = iVar5;
        Defend(iVar5,1);
        ::Build(*piVar1,"abbarr",1);
        fVar6 = Get_Time();
        (this->field17_0xa0)._s_0.rig_check = fVar6 + 20.0;
        (this->field16_0x40)._s_0.rig_show = true;
      }
    }
    if ((this->field16_0x40)._s_0.rig_show == false) goto LAB_004485cb;
  }
  piVar1 = &(this->field18_0x130)._s_0.avrig;
  bVar4 = IsAlive(piVar1);
  if (((bVar4) && (fVar6 = Get_Time(), (this->field17_0xa0)._s_0.rig_check < fVar6)) &&
     ((this->field16_0x40)._s_0.blah == false)) {
    Dropoff(*piVar1,"barrack_spot",1);
    iVar5 = BuildObject("bvturr",2,"muf_point",0);
    (this->field18_0x130)._s_0.avturr4 = iVar5;
    Goto(iVar5,"base_turret_spot1",1);
    fVar6 = Get_Time();
    (this->field17_0xa0)._s_0.turret_check = fVar6 + 60.0;
    (this->field16_0x40)._s_0.blah = true;
  }
LAB_004485cb:
  piVar1 = &(this->field18_0x130)._s_0.avturr4;
  bVar4 = IsAlive(piVar1);
  if (((bVar4) && (fVar6 = Get_Time(), (this->field17_0xa0)._s_0.turret_check < fVar6)) &&
     ((this->field16_0x40)._s_0.turret4_defend == false)) {
    Defend(*piVar1,1);
    piVar1 = &(this->field18_0x130)._s_0.avrig;
    bVar4 = IsAlive(piVar1);
    if (bVar4) {
      Defend(*piVar1,1);
    }
    (this->field16_0x40)._s_0.turret4_defend = true;
  }
  if ((((this->field16_0x40)._s_0.camera_off_recycle != false) &&
      ((this->field16_0x40)._s_0.camera_off_muf == false)) &&
     ((bVar4 = IsAlive(&(this->field18_0x130)._s_0.newmuf), bVar4 &&
      ((this->field16_0x40)._s_0.new_muf == false)))) {
    (this->field16_0x40)._s_0.new_muf = true;
  }
  if ((this->field16_0x40)._s_0.silo_message == false) {
    piVar1 = &(this->field18_0x130)._s_0.svsilo;
    bVar4 = IsAlive(piVar1);
    if ((bVar4) && (fVar6 = Get_Time(), (this->field17_0xa0)._s_0.silo_check < fVar6)) {
      fVar6 = Get_Time();
      (this->field17_0xa0)._s_0.silo_check = fVar6 + 5.0;
      fVar6 = GetDistance((this->field18_0x130)._s_0.user,*piVar1);
      if (fVar6 < 90.0) {
        AudioMessage("misns720.wav");
        (this->field16_0x40)._s_0.silo_message = true;
      }
    }
  }
  bVar4 = IsAlive(&(this->field18_0x130)._s_0.avrecycle);
  if ((!bVar4) && ((this->field16_0x40)._s_0.game_over == false)) {
    AudioMessage("misns712.wav");
    pcVar7 = "misns7w1.des";
    fVar6 = Get_Time();
    SucceedMission(fVar6 + 10.0,pcVar7);
    (this->field16_0x40)._s_0.game_over = true;
  }
  bVar4 = (this->field16_0x40)._s_0.con1_dead;
  if ((bVar4 != false) &&
     ((((((this->field16_0x40)._s_0.con2_dead != false &&
         ((this->field16_0x40)._s_0.con3_dead != false)) &&
        ((this->field16_0x40)._s_0.fully_loaded == false)) ||
       ((bVar4 != false &&
        (((((this->field16_0x40)._s_0.con2_dead != false &&
           ((this->field16_0x40)._s_0.con3_dead != false)) &&
          ((this->field16_0x40)._s_0.two_loaded == false)) ||
         (((bVar4 != false && ((this->field16_0x40)._s_0.con2_dead != false)) &&
          (((this->field16_0x40)._s_0.con3_dead != false &&
           ((this->field16_0x40)._s_0.one_loaded == false)))))))))) &&
      ((this->field16_0x40)._s_0.game_over == false)))) {
    AudioMessage("misns711.wav");
    pcVar7 = "misns7f1.des";
    fVar6 = Get_Time();
    FailMission(fVar6 + 10.0,pcVar7);
    (this->field16_0x40)._s_0.game_over = true;
  }
  bVar4 = IsAlive(&(this->field18_0x130)._s_0.apc);
  if ((((!bVar4) && ((this->field16_0x40)._s_0.camera_off_recycle == false)) &&
      ((this->field16_0x40)._s_0.camera_off_muf == false)) &&
     ((this->field16_0x40)._s_0.game_over == false)) {
    AudioMessage("misns716.wav");
    pcVar7 = "misns7f2.des";
    fVar6 = Get_Time();
    FailMission(fVar6 + 10.0,pcVar7);
    (this->field16_0x40)._s_0.game_over = true;
  }
  return;
}
