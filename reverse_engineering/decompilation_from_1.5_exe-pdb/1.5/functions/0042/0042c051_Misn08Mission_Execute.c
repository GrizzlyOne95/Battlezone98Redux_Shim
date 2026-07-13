/*
 * Entry: 0042c051
 * Name: Misn08Mission::Execute
 * Namespace: Misn08Mission
 * Signature: void Execute(Misn08Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn08Mission::Execute(Misn08Mission *this)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  float fVar6;
  char *pcVar7;
  
  iVar3 = GetPlayerHandle();
  (this->field18_0xf8)._s_0.user = iVar3;
  if ((this->field16_0x40)._s_0.start_done == false) {
    AudioMessage("misn0800.wav");
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misn0800.otf",DisplayInterface::colorWhite,8.0);
    InfoDisplay::AddObjective(&infoDisplay,"misn0801.otf",DisplayInterface::colorWhite,8.0);
    SetScrap(1,0x1e);
    Defend((this->field18_0xf8)._s_0.ccagech1,1);
    Defend((this->field18_0xf8)._s_0.ccagech2,1);
    fVar6 = Get_Time();
    (this->field17_0x70)._s_0.start_gech_time = fVar6 + 329.0;
    fVar6 = Get_Time();
    (this->field17_0x70)._s_0.gech_spawn_time = fVar6 + 280.0;
    fVar6 = Get_Time();
    (this->field17_0x70)._s_0.trigger_check = fVar6 + 285.0;
    (this->field17_0x70)._s_0.fresh_meat_time = 100.0;
    fVar6 = Get_Time();
    (this->field17_0x70)._s_0.gech_check = fVar6 + 61.0;
    fVar6 = Get_Time();
    iVar3 = (this->field18_0xf8)._s_0.ccagech1;
    (this->field17_0x70)._s_0.first_wave_time = fVar6 + 20.0;
    SetWeaponMask(iVar3,1);
    SetWeaponMask((this->field18_0xf8)._s_0.ccagech2,1);
    SetObjectiveName((this->field18_0xf8)._s_0.nav1,"Drop Zone");
    SetObjectiveName((this->field18_0xf8)._s_0.nav5,"Colorado Base");
    SetObjectiveName((this->field18_0xf8)._s_0.nav4,"CCA Main Base");
    fVar6 = Get_Time();
    (this->field16_0x40)._s_0.start_done = true;
    bVar2 = (this->field16_0x40)._s_0.start_done;
    (this->field17_0x70)._s_0.base_check = fVar6 + 5.0;
    if (bVar2 != false) goto LAB_0042c1a5;
  }
  else {
LAB_0042c1a5:
    fVar6 = Get_Time();
    if (((this->field17_0x70)._s_0.start_gech_time < fVar6) &&
       ((this->field16_0x40)._s_0.gech_started == false)) {
      Goto((this->field18_0xf8)._s_0.ccagech1,"gech_path1",1);
      Goto((this->field18_0xf8)._s_0.ccagech2,"gech_path2",1);
      (this->field16_0x40)._s_0.gech_started = true;
    }
  }
  fVar6 = Get_Time();
  if (((this->field17_0x70)._s_0.first_wave_time < fVar6) &&
     ((this->field16_0x40)._s_0.first_wave == false)) {
    piVar1 = &(this->field18_0xf8)._s_0.nsdfrecycle;
    Goto((this->field18_0xf8)._s_0.svpatrol2_2,*piVar1,1);
    Goto((this->field18_0xf8)._s_0.svpatrol2_3,*piVar1,1);
    (this->field16_0x40)._s_0.first_wave = true;
  }
  fVar6 = Get_Time();
  if ((((this->field17_0x70)._s_0.fresh_meat_time < fVar6) &&
      ((this->field16_0x40)._s_0.colorado_under_attack == false)) &&
     ((this->field16_0x40)._s_0.fresh_meat == false)) {
    iVar3 = BuildObject("svfigh",2,(this->field18_0xf8)._s_0.ccarecycle);
    (this->field18_0xf8)._s_0.cannon_fodder1 = iVar3;
    iVar3 = BuildObject("svfigh",2,(this->field18_0xf8)._s_0.ccarecycle);
    (this->field18_0xf8)._s_0.cannon_fodder2 = iVar3;
    iVar3 = BuildObject("svfigh",2,(this->field18_0xf8)._s_0.ccarecycle);
    (this->field18_0xf8)._s_0.cannon_fodder3 = iVar3;
    Goto((this->field18_0xf8)._s_0.cannon_fodder1,"gech_path2",1);
    Goto((this->field18_0xf8)._s_0.cannon_fodder2,"gech_path2",1);
    Goto((this->field18_0xf8)._s_0.cannon_fodder3,"gech_path2",1);
    (this->field16_0x40)._s_0.fresh_meat = true;
  }
  fVar6 = Get_Time();
  if ((((this->field17_0x70)._s_0.fighter_message_time < fVar6) &&
      ((this->field16_0x40)._s_0.colorado_under_attack == false)) &&
     ((this->field16_0x40)._s_0.fighter_message == false)) {
    AudioMessage("misn0817.wav");
    (this->field16_0x40)._s_0.fighter_message = true;
  }
  fVar6 = Get_Time();
  if (((this->field17_0x70)._s_0.gech_spawn_time < fVar6) &&
     ((this->field16_0x40)._s_0.colorado_under_attack == false)) {
    fVar6 = Get_Time();
    iVar3 = (this->field18_0xf8)._s_0.user;
    (this->field17_0x70)._s_0.gech_spawn_time = fVar6 + 10.0;
    fVar6 = GetDistance(iVar3,(this->field18_0xf8)._s_0.nav5);
    if (400.0 < fVar6) {
      piVar1 = &(this->field18_0xf8)._s_0.ccarecycle;
      piVar5 = &(this->field18_0xf8)._s_0.svpatrol2_2;
      iVar3 = BuildObject("svfigh",2,*piVar1);
      *piVar5 = iVar3;
      iVar3 = BuildObject("svltnk",2,*piVar1);
      *piVar5 = iVar3;
      iVar3 = BuildObject("svwalk",2,"gech_spawn",0);
      piVar1 = &(this->field18_0xf8)._s_0.ccagech3;
      *piVar1 = iVar3;
      SetWeaponMask(iVar3,1);
      Attack(*piVar1,(this->field18_0xf8)._s_0.colorado,1);
      AudioMessage("misn0801.wav");
      fVar6 = Get_Time();
      piVar1 = &(this->field18_0xf8)._s_0.svpatrol2_1;
      (this->field17_0x70)._s_0.colorado_message2_time = fVar6 + 10.0;
      bVar2 = IsAlive(piVar1);
      if (bVar2) {
        Goto(*piVar1,(this->field18_0xf8)._s_0.nav1,1);
      }
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        Goto(*piVar5,(this->field18_0xf8)._s_0.nav1,1);
      }
      piVar1 = &(this->field18_0xf8)._s_0.svpatrol2_3;
      bVar2 = IsAlive(piVar1);
      if (bVar2) {
        Goto(*piVar1,(this->field18_0xf8)._s_0.nav1,1);
      }
      (this->field16_0x40)._s_0.colorado_under_attack = true;
    }
  }
  fVar6 = Get_Time();
  if (fVar6 <= (this->field17_0x70)._s_0.player_nosey_time) {
LAB_0042c550:
    if ((this->field16_0x40)._s_0.colorado_under_attack != false) goto LAB_0042c556;
LAB_0042c588:
    if ((this->field16_0x40)._s_0.colorado_message2 != false) goto LAB_0042c58e;
  }
  else {
    if ((this->field16_0x40)._s_0.colorado_under_attack == false) {
      fVar6 = Get_Time();
      iVar3 = (this->field18_0xf8)._s_0.nav5;
      iVar4 = (this->field18_0xf8)._s_0.user;
      (this->field17_0x70)._s_0.player_nosey_time = fVar6 + 32.0;
      fVar6 = GetDistance(iVar4,iVar3);
      if (fVar6 < 700.0) {
        fVar6 = Get_Time();
        piVar1 = &(this->field18_0xf8)._s_0.svpatrol1_1;
        (this->field17_0x70)._s_0.gech_spawn_time = fVar6 + 10.0;
        bVar2 = IsAlive(piVar1);
        if (bVar2) {
          Attack(*piVar1,(this->field18_0xf8)._s_0.user,1);
        }
        piVar1 = &(this->field18_0xf8)._s_0.svpatrol1_2;
        bVar2 = IsAlive(piVar1);
        if (bVar2) {
          Attack(*piVar1,(this->field18_0xf8)._s_0.user,1);
        }
        piVar1 = &(this->field18_0xf8)._s_0.svpatrol1_3;
        bVar2 = IsAlive(piVar1);
        if (bVar2) {
          Attack(*piVar1,(this->field18_0xf8)._s_0.user,1);
        }
        piVar1 = &(this->field18_0xf8)._s_0.svpatrol2_1;
        bVar2 = IsAlive(piVar1);
        if (bVar2) {
          Attack(*piVar1,(this->field18_0xf8)._s_0.nsdfrecycle,1);
        }
        piVar1 = &(this->field18_0xf8)._s_0.svpatrol2_2;
        bVar2 = IsAlive(piVar1);
        if (bVar2) {
          Attack(*piVar1,(this->field18_0xf8)._s_0.nsdfrecycle,1);
        }
        piVar1 = &(this->field18_0xf8)._s_0.svpatrol2_3;
        bVar2 = IsAlive(piVar1);
        if (bVar2) {
          Attack(*piVar1,(this->field18_0xf8)._s_0.nsdfrecycle,1);
        }
      }
      goto LAB_0042c550;
    }
LAB_0042c556:
    fVar6 = Get_Time();
    if (fVar6 <= (this->field17_0x70)._s_0.colorado_message2_time) goto LAB_0042c588;
    if ((this->field16_0x40)._s_0.colorado_message2 == false) {
      AudioMessage("misn0803.wav");
      fVar6 = Get_Time();
      (this->field16_0x40)._s_0.colorado_message2 = true;
      (this->field17_0x70)._s_0.colorado_message3_time = fVar6 + 7.0;
      goto LAB_0042c588;
    }
LAB_0042c58e:
    fVar6 = Get_Time();
    if (((this->field17_0x70)._s_0.colorado_message3_time < fVar6) &&
       ((this->field16_0x40)._s_0.colorado_message3 == false)) {
      AudioMessage("misn0802.wav");
      AudioMessage("misn0804.wav");
      fVar6 = Get_Time();
      (this->field16_0x40)._s_0.colorado_message3 = true;
      (this->field17_0x70)._s_0.colorado_message4_time = fVar6 + 10.0;
    }
  }
  fVar6 = Get_Time();
  if (((this->field17_0x70)._s_0.colorado_message4_time < fVar6) &&
     ((this->field16_0x40)._s_0.kill_colorado == false)) {
    (this->field16_0x40)._s_0.kill_colorado = true;
  }
  piVar1 = &(this->field18_0xf8)._s_0.colorado;
  bVar2 = IsAlive(piVar1);
  if (((bVar2) && ((this->field16_0x40)._s_0.kill_colorado == false)) &&
     (fVar6 = Get_Time(), (this->field17_0x70)._s_0.next_second < fVar6)) {
    AddHealth(*piVar1,500.0);
    fVar6 = Get_Time();
    (this->field17_0x70)._s_0.next_second = fVar6 + 1.0;
  }
  if (((this->field16_0x40)._s_0.colorado_message3 == false) ||
     ((this->field16_0x40)._s_0.kill_colorado == false)) {
LAB_0042c678:
    if ((this->field16_0x40)._s_0.colorado_message4 != false) goto LAB_0042c67e;
LAB_0042c6b7:
    if ((this->field16_0x40)._s_0.colorado_destroyed != false) goto LAB_0042c6bd;
LAB_0042c6f5:
    if ((this->field16_0x40)._s_0.bad_news != false) goto LAB_0042c6fb;
  }
  else {
    if ((this->field16_0x40)._s_0.colorado_message4 == false) {
      bVar2 = IsAlive(piVar1);
      if (bVar2) {
        Damage(*piVar1,20000);
      }
      fVar6 = Get_Time();
      (this->field16_0x40)._s_0.colorado_message4 = true;
      (this->field17_0x70)._s_0.remove_nav5_time = fVar6 + 15.0;
      goto LAB_0042c678;
    }
LAB_0042c67e:
    fVar6 = Get_Time();
    if (fVar6 <= (this->field17_0x70)._s_0.remove_nav5_time) goto LAB_0042c6b7;
    if ((this->field16_0x40)._s_0.colorado_destroyed == false) {
      RemoveObject((this->field18_0xf8)._s_0.nav5);
      fVar6 = Get_Time();
      (this->field16_0x40)._s_0.colorado_destroyed = true;
      (this->field17_0x70)._s_0.bad_news_time = fVar6 + 5.0;
      goto LAB_0042c6b7;
    }
LAB_0042c6bd:
    if ((this->field16_0x40)._s_0.bad_news == false) {
      fVar6 = Get_Time();
      if ((this->field17_0x70)._s_0.bad_news_time < fVar6) {
        AudioMessage("misn0805.wav");
        fVar6 = Get_Time();
        (this->field16_0x40)._s_0.bad_news = true;
        (this->field17_0x70)._s_0.bad_news_time = fVar6 + 30.0;
      }
      goto LAB_0042c6f5;
    }
LAB_0042c6fb:
    fVar6 = Get_Time();
    if (((this->field17_0x70)._s_0.bad_news_time < fVar6) &&
       ((this->field16_0x40)._s_0.gen_message == false)) {
      AudioMessage("misn0810.wav");
      (this->field16_0x40)._s_0.gen_message = true;
    }
  }
  if (((this->field16_0x40)._s_0.bad_news != false) &&
     ((this->field16_0x40)._s_0.ccarecycle_spawned == false)) {
    SetAIP("misn08.aip",2);
    SetScrap(2,0x28);
    SetPilot(2,0x28);
    fVar6 = Get_Time();
    piVar1 = &(this->field18_0xf8)._s_0.ccagech3;
    (this->field17_0x70)._s_0.new_aip_time = fVar6 + 420.0;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Goto(*piVar1,"gech_path2",1);
    }
    piVar1 = &(this->field18_0xf8)._s_0.svpatrol1_1;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Goto(*piVar1,"cam3_spawn",1);
    }
    piVar1 = &(this->field18_0xf8)._s_0.svpatrol1_2;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Goto(*piVar1,"cam3_spawn",1);
    }
    piVar1 = &(this->field18_0xf8)._s_0.svpatrol1_3;
    bVar2 = IsAlive(piVar1);
    if (bVar2) {
      Goto(*piVar1,"cam3_spawn",1);
    }
    (this->field16_0x40)._s_0.ccarecycle_spawned = true;
  }
  fVar6 = Get_Time();
  if (fVar6 <= (this->field17_0x70)._s_0.gech_check) {
LAB_0042c93a:
    if ((this->field16_0x40)._s_0.gech_found != false) goto LAB_0042c940;
  }
  else {
    if ((this->field16_0x40)._s_0.gech_found == false) {
      if ((this->field16_0x40)._s_0.gech_at_nav == false) {
        fVar6 = Get_Time();
        iVar3 = (this->field18_0xf8)._s_0.user;
        (this->field17_0x70)._s_0.gech_check = fVar6 + 6.0;
        fVar6 = GetDistance(iVar3,(this->field18_0xf8)._s_0.ccagech1);
        if ((((fVar6 < 400.0) && ((this->field16_0x40)._s_0.gech_found1 == false)) &&
            ((this->field16_0x40)._s_0.gech_found == false)) &&
           ((this->field16_0x40)._s_0.gech_at_nav == false)) {
          AudioMessage("misn0806.wav");
          fVar6 = Get_Time();
          (this->field17_0x70)._s_0.followup_message_time = fVar6 + 20.0;
          fVar6 = Get_Time();
          (this->field17_0x70)._s_0.stumble2_check = fVar6 + 10.0;
          fVar6 = Get_Time();
          (this->field16_0x40)._s_0.gech_found1 = true;
          (this->field16_0x40)._s_0.gech_found = true;
          (this->field17_0x70)._s_0.no_stumble_check = fVar6 + 13.0;
          (this->field17_0x70)._s_0.gech1_there_time = 100.0;
          (this->field17_0x70)._s_0.gech2_there_time = 105.0;
        }
        fVar6 = GetDistance((this->field18_0xf8)._s_0.user,(this->field18_0xf8)._s_0.ccagech2);
        if (fVar6 < 400.0) {
          if ((this->field16_0x40)._s_0.gech_found != false) goto LAB_0042c940;
          if (((this->field16_0x40)._s_0.gech_found2 == false) &&
             ((this->field16_0x40)._s_0.gech_at_nav == false)) {
            AudioMessage("misn0806.wav");
            fVar6 = Get_Time();
            (this->field17_0x70)._s_0.followup_message_time = fVar6 + 5.0;
            fVar6 = Get_Time();
            (this->field17_0x70)._s_0.stumble2_check = fVar6 + 60.0;
            fVar6 = Get_Time();
            (this->field16_0x40)._s_0.gech_found2 = true;
            (this->field16_0x40)._s_0.gech_found = true;
            (this->field17_0x70)._s_0.no_stumble_check = fVar6 + 13.0;
            (this->field17_0x70)._s_0.gech1_there_time = 100.0;
            (this->field17_0x70)._s_0.gech2_there_time = 105.0;
          }
        }
      }
      goto LAB_0042c93a;
    }
LAB_0042c940:
    fVar6 = Get_Time();
    if (((this->field17_0x70)._s_0.followup_message_time < fVar6) &&
       ((this->field16_0x40)._s_0.followup_message == false)) {
      AudioMessage("misn0807.wav");
      (this->field16_0x40)._s_0.followup_message = true;
    }
  }
  fVar6 = Get_Time();
  if (((this->field17_0x70)._s_0.base_check < fVar6) &&
     ((this->field16_0x40)._s_0.base_set == false)) {
    fVar6 = Get_Time();
    piVar1 = &(this->field18_0xf8)._s_0.nsdfmuf;
    (this->field17_0x70)._s_0.base_check = fVar6 + 2.0;
    bVar2 = IsAlive(piVar1);
    if ((bVar2) && (bVar2 = IsDeployed(*piVar1), bVar2)) {
      InfoDisplay::ClearObjectives(&infoDisplay);
      InfoDisplay::AddObjective(&infoDisplay,"misn0800.otf",DisplayInterface::colorGreen,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn0801.otf",DisplayInterface::colorWhite,8.0);
      (this->field16_0x40)._s_0.base_set = true;
    }
  }
  if (((((this->field16_0x40)._s_0.gech_found != false) &&
       (fVar6 = Get_Time(), (this->field17_0x70)._s_0.stumble2_check < fVar6)) &&
      ((this->field16_0x40)._s_0.second_gech_warning == false)) &&
     ((this->field16_0x40)._s_0.run_into_other_gech == false)) {
    fVar6 = Get_Time();
    bVar2 = (this->field16_0x40)._s_0.gech_found1;
    (this->field17_0x70)._s_0.stumble2_check = fVar6 + 21.0;
    if (((bVar2 != false) &&
        (fVar6 = GetDistance((this->field18_0xf8)._s_0.user,(this->field18_0xf8)._s_0.ccagech2),
        fVar6 < 100.0)) && ((this->field16_0x40)._s_0.run_into_other_gech == false)) {
      AudioMessage("misn0813.wav");
      (this->field16_0x40)._s_0.run_into_other_gech = true;
    }
    if ((((this->field16_0x40)._s_0.gech_found2 != false) &&
        (fVar6 = GetDistance((this->field18_0xf8)._s_0.user,(this->field18_0xf8)._s_0.ccagech1),
        fVar6 < 100.0)) && ((this->field16_0x40)._s_0.run_into_other_gech == false)) {
      AudioMessage("misn0813.wav");
      (this->field16_0x40)._s_0.run_into_other_gech = true;
    }
  }
  if (((((this->field16_0x40)._s_0.gech_found != false) &&
       (fVar6 = Get_Time(), (this->field17_0x70)._s_0.no_stumble_check < fVar6)) &&
      ((this->field16_0x40)._s_0.run_into_other_gech == false)) &&
     ((this->field16_0x40)._s_0.second_gech_warning == false)) {
    fVar6 = Get_Time();
    bVar2 = (this->field16_0x40)._s_0.gech_found1;
    (this->field17_0x70)._s_0.no_stumble_check = fVar6 + 9.0;
    if (((bVar2 != false) &&
        (fVar6 = GetDistance((this->field18_0xf8)._s_0.gech_trigger2,
                             (this->field18_0xf8)._s_0.ccagech2), fVar6 < 100.0)) &&
       ((this->field16_0x40)._s_0.second_gech_warning == false)) {
      AudioMessage("misn0815.wav");
      iVar3 = BuildObject("apcamr",1,"cam2_spawn",0);
      (this->field18_0xf8)._s_0.nav2 = iVar3;
      SetObjectiveName(iVar3,"Nav Alpha 1");
      (this->field16_0x40)._s_0.second_gech_warning = true;
    }
    if ((((this->field16_0x40)._s_0.gech_found2 != false) &&
        (fVar6 = GetDistance((this->field18_0xf8)._s_0.gech_trigger3,
                             (this->field18_0xf8)._s_0.ccagech1), fVar6 < 100.0)) &&
       ((this->field16_0x40)._s_0.second_gech_warning == false)) {
      AudioMessage("misn0814.wav");
      iVar3 = BuildObject("apcamr",1,"cam3_spawn",0);
      (this->field18_0xf8)._s_0.nav3 = iVar3;
      SetObjectiveName(iVar3,"Nav Alpha 2");
      (this->field16_0x40)._s_0.second_gech_warning = true;
    }
  }
  if (((((this->field16_0x40)._s_0.colorado_under_attack != false) &&
       (fVar6 = Get_Time(), (this->field17_0x70)._s_0.trigger_check < fVar6)) &&
      ((this->field16_0x40)._s_0.gech_at_nav == false)) &&
     ((this->field16_0x40)._s_0.gech_found == false)) {
    fVar6 = Get_Time();
    bVar2 = (this->field16_0x40)._s_0.gech_found;
    (this->field17_0x70)._s_0.trigger_check = fVar6 + 19.0;
    if (bVar2 == false) {
      fVar6 = GetDistance((this->field18_0xf8)._s_0.gech_trigger2,(this->field18_0xf8)._s_0.ccagech2
                         );
      if ((fVar6 < 100.0) && ((this->field16_0x40)._s_0.gech_at_nav == false)) {
        AudioMessage("misn0809.wav");
        fVar6 = Get_Time();
        (this->field16_0x40)._s_0.gech_at_nav = true;
        (this->field16_0x40)._s_0.gech_at_nav2 = true;
        (this->field17_0x70)._s_0.gech_warning_message = fVar6 + 20.0;
        (this->field17_0x70)._s_0.gech1_there_time = 100.0;
        (this->field17_0x70)._s_0.gech2_there_time = 105.0;
      }
      if ((((this->field16_0x40)._s_0.gech_found == false) &&
          (fVar6 = GetDistance((this->field18_0xf8)._s_0.gech_trigger3,
                               (this->field18_0xf8)._s_0.ccagech1), fVar6 < 100.0)) &&
         ((this->field16_0x40)._s_0.gech_at_nav == false)) {
        AudioMessage("misn0808.wav");
        fVar6 = Get_Time();
        (this->field16_0x40)._s_0.gech_at_nav = true;
        (this->field16_0x40)._s_0.gech_at_nav3 = true;
        (this->field17_0x70)._s_0.gech_warning_message = fVar6 + 20.0;
        (this->field17_0x70)._s_0.gech1_there_time = 100.0;
        (this->field17_0x70)._s_0.gech2_there_time = 105.0;
      }
    }
  }
  if ((((this->field16_0x40)._s_0.gech_at_nav2 != false) &&
      (fVar6 = Get_Time(), (this->field17_0x70)._s_0.gech_warning_message < fVar6)) &&
     ((this->field16_0x40)._s_0.player_warned_ofgech == false)) {
    AudioMessage("misn0814.wav");
    iVar3 = BuildObject("apcamr",1,"cam2_spawn",0);
    (this->field18_0xf8)._s_0.nav2 = iVar3;
    SetObjectiveName(iVar3,"Nav Alpha 1");
    fVar6 = Get_Time();
    (this->field17_0x70)._s_0.time_waist = fVar6 + 14.0;
    fVar6 = Get_Time();
    (this->field16_0x40)._s_0.player_warned_ofgech = true;
    (this->field17_0x70)._s_0.stumble1_check = fVar6 + 100.0;
  }
  if (((this->field16_0x40)._s_0.gech_at_nav3 == false) ||
     (fVar6 = Get_Time(), fVar6 <= (this->field17_0x70)._s_0.gech_warning_message)) {
LAB_0042cd9f:
    if ((this->field16_0x40)._s_0.player_warned_ofgech != false) goto LAB_0042cda9;
  }
  else {
    if ((this->field16_0x40)._s_0.player_warned_ofgech == false) {
      AudioMessage("misn0815.wav");
      iVar3 = BuildObject("apcamr",1,"cam3_spawn",0);
      (this->field18_0xf8)._s_0.nav3 = iVar3;
      SetObjectiveName(iVar3,"Nav Alpha 2");
      fVar6 = Get_Time();
      (this->field17_0x70)._s_0.time_waist = fVar6 + 14.0;
      fVar6 = Get_Time();
      (this->field16_0x40)._s_0.player_warned_ofgech = true;
      (this->field17_0x70)._s_0.stumble1_check = fVar6 + 100.0;
      goto LAB_0042cd9f;
    }
LAB_0042cda9:
    fVar6 = Get_Time();
    if ((((this->field17_0x70)._s_0.time_waist < fVar6) &&
        ((this->field16_0x40)._s_0.second_gech_warning == false)) &&
       ((this->field16_0x40)._s_0.bump_into_gech == false)) {
      fVar6 = Get_Time();
      bVar2 = (this->field16_0x40)._s_0.gech_at_nav2;
      (this->field17_0x70)._s_0.time_waist = fVar6 + 14.0;
      if (((bVar2 != false) &&
          (fVar6 = GetDistance((this->field18_0xf8)._s_0.gech_trigger3,
                               (this->field18_0xf8)._s_0.ccagech1), fVar6 < 75.0)) &&
         ((this->field16_0x40)._s_0.second_gech_warning == false)) {
        AudioMessage("misn0812.wav");
        iVar3 = BuildObject("apcamr",1,"cam3_spawn",0);
        (this->field18_0xf8)._s_0.nav3 = iVar3;
        SetObjectiveName(iVar3,"Nav Alpha 2");
        (this->field16_0x40)._s_0.second_gech_warning = true;
      }
      if ((((this->field16_0x40)._s_0.gech_at_nav3 != false) &&
          (fVar6 = GetDistance((this->field18_0xf8)._s_0.gech_trigger2,
                               (this->field18_0xf8)._s_0.ccagech2), fVar6 < 75.0)) &&
         ((this->field16_0x40)._s_0.second_gech_warning == false)) {
        AudioMessage("misn0811.wav");
        iVar3 = BuildObject("apcamr",1,"cam2_spawn",0);
        (this->field18_0xf8)._s_0.nav2 = iVar3;
        SetObjectiveName(iVar3,"Nav Alpha 1");
        (this->field16_0x40)._s_0.second_gech_warning = true;
      }
    }
  }
  if ((((this->field16_0x40)._s_0.player_warned_ofgech != false) &&
      (fVar6 = Get_Time(), (this->field17_0x70)._s_0.stumble1_check < fVar6)) &&
     (((this->field16_0x40)._s_0.second_gech_warning == false &&
      ((this->field16_0x40)._s_0.bump_into_gech == false)))) {
    fVar6 = Get_Time();
    bVar2 = (this->field16_0x40)._s_0.gech_at_nav2;
    (this->field17_0x70)._s_0.stumble1_check = fVar6 + 23.0;
    if (((bVar2 != false) &&
        (fVar6 = GetDistance((this->field18_0xf8)._s_0.user,(this->field18_0xf8)._s_0.ccagech1),
        fVar6 < 100.0)) && ((this->field16_0x40)._s_0.bump_into_gech == false)) {
      AudioMessage("misn0813.wav");
      (this->field16_0x40)._s_0.bump_into_gech = true;
    }
    if ((((this->field16_0x40)._s_0.gech_at_nav3 != false) &&
        (fVar6 = GetDistance((this->field18_0xf8)._s_0.user,(this->field18_0xf8)._s_0.ccagech2),
        fVar6 < 100.0)) && ((this->field16_0x40)._s_0.bump_into_gech == false)) {
      AudioMessage("misn0813.wav");
      (this->field16_0x40)._s_0.bump_into_gech = true;
    }
  }
  if (((this->field16_0x40)._s_0.gech_found != false) ||
     ((this->field16_0x40)._s_0.gech_at_nav != false)) {
    fVar6 = Get_Time();
    if (((this->field17_0x70)._s_0.gech1_there_time < fVar6) &&
       ((this->field16_0x40)._s_0.gech1_at_base == false)) {
      fVar6 = Get_Time();
      piVar1 = &(this->field18_0xf8)._s_0.ccagech1;
      (this->field17_0x70)._s_0.gech1_there_time = fVar6 + 30.0;
      bVar2 = IsAlive(piVar1);
      if ((bVar2) &&
         (fVar6 = GetDistance(*piVar1,(this->field18_0xf8)._s_0.stop_geyser3), fVar6 < 100.0)) {
        piVar5 = &(this->field18_0xf8)._s_0.nsdfrecycle;
        bVar2 = IsAlive(piVar5);
        if (!bVar2) {
          piVar5 = &(this->field18_0xf8)._s_0.nsdfmuf;
          bVar2 = IsAlive(piVar5);
          if (!bVar2) goto LAB_0042d012;
        }
        Attack(*piVar1,*piVar5,1);
        if ((this->field16_0x40)._s_0.gech1_blossom != false) {
          SetWeaponMask(*piVar1,5);
        }
        (this->field16_0x40)._s_0.gech1_at_base = true;
      }
    }
LAB_0042d012:
    fVar6 = Get_Time();
    if (((this->field17_0x70)._s_0.gech2_there_time < fVar6) &&
       ((this->field16_0x40)._s_0.gech2_at_base == false)) {
      fVar6 = Get_Time();
      piVar1 = &(this->field18_0xf8)._s_0.ccagech2;
      (this->field17_0x70)._s_0.gech2_there_time = fVar6 + 30.0;
      bVar2 = IsAlive(piVar1);
      if ((bVar2) &&
         (fVar6 = GetDistance(*piVar1,(this->field18_0xf8)._s_0.stop_geyser3), fVar6 < 100.0)) {
        piVar5 = &(this->field18_0xf8)._s_0.nsdfrecycle;
        bVar2 = IsAlive(piVar5);
        if (!bVar2) {
          piVar5 = &(this->field18_0xf8)._s_0.nsdfmuf;
          bVar2 = IsAlive(piVar5);
          if (!bVar2) goto LAB_0042d0b4;
        }
        Attack(*piVar1,*piVar5,1);
        if ((this->field16_0x40)._s_0.gech2_blossom != false) {
          SetWeaponMask(*piVar1,5);
        }
        (this->field16_0x40)._s_0.gech2_at_base = true;
      }
    }
LAB_0042d0b4:
    fVar6 = Get_Time();
    if (((this->field17_0x70)._s_0.gech3_there_time < fVar6) &&
       ((this->field16_0x40)._s_0.gech3_at_base == false)) {
      fVar6 = Get_Time();
      piVar1 = &(this->field18_0xf8)._s_0.ccagech3;
      (this->field17_0x70)._s_0.gech3_there_time = fVar6 + 30.0;
      bVar2 = IsAlive(piVar1);
      if ((bVar2) &&
         (fVar6 = GetDistance(*piVar1,(this->field18_0xf8)._s_0.stop_geyser3), fVar6 < 100.0)) {
        piVar5 = &(this->field18_0xf8)._s_0.nsdfrecycle;
        bVar2 = IsAlive(piVar5);
        if (!bVar2) {
          piVar5 = &(this->field18_0xf8)._s_0.nsdfmuf;
          bVar2 = IsAlive(piVar5);
          if (!bVar2) goto LAB_0042d156;
        }
        Attack(*piVar1,*piVar5,1);
        if ((this->field16_0x40)._s_0.gech3_blossom != false) {
          SetWeaponMask(*piVar1,5);
        }
        (this->field16_0x40)._s_0.gech3_at_base = true;
      }
    }
  }
LAB_0042d156:
  fVar6 = Get_Time();
  if ((this->field17_0x70)._s_0.new_aip_time < fVar6) {
    fVar6 = Get_Time();
    (this->field17_0x70)._s_0.new_aip_time = fVar6 + 420.0;
    iVar4 = CountUnitsNearObject((this->field18_0xf8)._s_0.stop_geyser2,5000.0,1,"avfigh");
    iVar3 = (this->field18_0xf8)._s_0.stop_geyser2;
    (this->field19_0x1a0)._s_0.units1 = iVar4;
    iVar3 = CountUnitsNearObject(iVar3,5000.0,1,"avtank");
    (this->field19_0x1a0)._s_0.units2 = iVar3;
    if (iVar3 < (this->field19_0x1a0)._s_0.units1) {
      pcVar7 = "misn08b.aip";
    }
    else {
      pcVar7 = "misn08a.aip";
    }
    SetAIP(pcVar7,2);
  }
  piVar1 = &(this->field18_0xf8)._s_0.ccaapc;
  bVar2 = IsAlive(piVar1);
  if (bVar2) {
    if ((this->field16_0x40)._s_0.apc_attack == false) {
      piVar5 = &(this->field18_0xf8)._s_0.guntower1;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
LAB_0042d239:
        Attack(*piVar1,*piVar5,1);
      }
      else {
        piVar5 = &(this->field18_0xf8)._s_0.guntower2;
        bVar2 = IsAlive(piVar5);
        if (bVar2) goto LAB_0042d239;
        piVar5 = &(this->field18_0xf8)._s_0.nsdfmuf;
        bVar2 = IsAlive(piVar5);
        if (bVar2) goto LAB_0042d239;
        piVar5 = &(this->field18_0xf8)._s_0.nsdfrecycle;
        bVar2 = IsAlive(piVar5);
        if (bVar2) goto LAB_0042d239;
      }
      (this->field16_0x40)._s_0.apc_attack = true;
      goto LAB_0042d24a;
    }
  }
  else {
LAB_0042d24a:
    if ((this->field16_0x40)._s_0.apc_attack == false) goto LAB_0042d25e;
  }
  bVar2 = IsAlive(piVar1);
  if (!bVar2) {
    (this->field16_0x40)._s_0.apc_attack = false;
  }
LAB_0042d25e:
  fVar6 = Get_Time();
  if (((this->field17_0x70)._s_0.pull_out_message < fVar6) &&
     ((this->field16_0x40)._s_0.too_close_message == false)) {
    AudioMessage("misn0816.wav");
    (this->field16_0x40)._s_0.too_close_message = true;
  }
  piVar1 = &(this->field18_0xf8)._s_0.ccagech1;
  bVar2 = IsAlive(piVar1);
  if (((bVar2) && ((this->field16_0x40)._s_0.gech1_blossom == false)) &&
     (fVar6 = GetHealth(*piVar1), fVar6 < 0.25)) {
    SetWeaponMask(*piVar1,4);
    fVar6 = Get_Time();
    (this->field16_0x40)._s_0.gech1_blossom = true;
    (this->field17_0x70)._s_0.pull_out_message = fVar6 + 6.0;
  }
  piVar1 = &(this->field18_0xf8)._s_0.ccagech2;
  bVar2 = IsAlive(piVar1);
  if (((bVar2) && ((this->field16_0x40)._s_0.gech2_blossom == false)) &&
     (fVar6 = GetHealth(*piVar1), fVar6 < 0.25)) {
    SetWeaponMask(*piVar1,4);
    fVar6 = Get_Time();
    (this->field16_0x40)._s_0.gech2_blossom = true;
    (this->field17_0x70)._s_0.pull_out_message = fVar6 + 6.0;
  }
  piVar1 = &(this->field18_0xf8)._s_0.ccagech3;
  bVar2 = IsAlive(piVar1);
  if (((bVar2) && ((this->field16_0x40)._s_0.gech3_blossom == false)) &&
     (fVar6 = GetHealth(*piVar1), fVar6 < 0.25)) {
    SetWeaponMask(*piVar1,4);
    fVar6 = Get_Time();
    (this->field16_0x40)._s_0.gech3_blossom = true;
    (this->field17_0x70)._s_0.pull_out_message = fVar6 + 6.0;
  }
  if ((((this->field16_0x40)._s_0.cerb_found == false) &&
      ((this->field16_0x40)._s_0.relic_message == false)) &&
     ((bVar2 = IsInfo("hbblde"), bVar2 || (bVar2 = IsInfo("hbbldf"), bVar2)))) {
    if ((this->field16_0x40)._s_0.base_dead == false) {
      pcVar7 = "misn0822.wav";
    }
    else {
      pcVar7 = "misn0821.wav";
    }
    AudioMessage(pcVar7);
    (this->field16_0x40)._s_0.relic_message = true;
  }
  if (((this->field16_0x40)._s_0.cerb_found == false) &&
     (fVar6 = Get_Time(), (this->field17_0x70)._s_0.cerb_check < fVar6)) {
    fVar6 = Get_Time();
    iVar3 = (this->field18_0xf8)._s_0.main_relic;
    iVar4 = (this->field18_0xf8)._s_0.user;
    (this->field17_0x70)._s_0.cerb_check = fVar6 + 3.0;
    fVar6 = GetDistance(iVar4,iVar3);
    if (fVar6 < 70.0) {
      if ((this->field16_0x40)._s_0.base_dead == false) {
        AudioMessage("misn0819.wav");
      }
      else {
        AudioMessage("misn0818.wav");
        AudioMessage("misn0826.wav");
        pcVar7 = "misn08w1.des";
        fVar6 = Get_Time();
        SucceedMission(fVar6 + 30.0,pcVar7);
      }
      (this->field16_0x40)._s_0.cerb_found = true;
    }
  }
  piVar1 = &(this->field18_0xf8)._s_0.main_relic;
  bVar2 = IsAlive(piVar1);
  if ((bVar2) && (fVar6 = Get_Time(), (this->field17_0x70)._s_0.next_second2 < fVar6)) {
    AddHealth(*piVar1,500.0);
    fVar6 = Get_Time();
    (this->field17_0x70)._s_0.next_second2 = fVar6 + 1.0;
  }
  bVar2 = IsAlive(&(this->field18_0xf8)._s_0.ccarecycle);
  if (((!bVar2) && (bVar2 = IsAlive(&(this->field18_0xf8)._s_0.ccamuf), !bVar2)) &&
     ((this->field16_0x40)._s_0.base_dead == false)) {
    if ((this->field16_0x40)._s_0.cerb_found == false) {
      InfoDisplay::ClearObjectives(&infoDisplay);
      InfoDisplay::AddObjective(&infoDisplay,"misn0801.otf",DisplayInterface::colorGreen,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn0802.otf",DisplayInterface::colorWhite,8.0);
      AudioMessage("misn0820.wav");
      SetObjectiveOn(*piVar1);
      SetObjectiveName(*piVar1,"Relic Site");
    }
    else {
      AudioMessage("misn0818.wav");
      AudioMessage("misn0826.wav");
      pcVar7 = "misn08w1.des";
      fVar6 = Get_Time();
      SucceedMission(fVar6 + 30.0,pcVar7);
    }
    (this->field16_0x40)._s_0.base_dead = true;
  }
  bVar2 = IsAlive(&(this->field18_0xf8)._s_0.nsdfrecycle);
  if ((!bVar2) && ((this->field16_0x40)._s_0.game_over == false)) {
    AudioMessage("misn0421.wav");
    pcVar7 = "misn08f1.des";
    fVar6 = Get_Time();
    FailMission(fVar6 + 15.0,pcVar7);
    (this->field16_0x40)._s_0.game_over = true;
  }
  return;
}
