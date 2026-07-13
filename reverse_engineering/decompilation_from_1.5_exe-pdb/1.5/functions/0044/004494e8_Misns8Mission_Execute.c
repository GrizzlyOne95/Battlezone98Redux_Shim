/*
 * Entry: 004494e8
 * Name: Misns8Mission::Execute
 * Namespace: Misns8Mission
 * Signature: void Execute(Misns8Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns8Mission::Execute(Misns8Mission *this)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  bool *pbVar4;
  float *pfVar5;
  bool bVar6;
  int iVar7;
  int extraout_EAX;
  int iVar8;
  float fVar9;
  char *pcVar10;
  
  iVar7 = GetPlayerHandle();
  (this->field18_0x130)._s_0.user = iVar7;
  bVar6 = IsAlive(&(this->field18_0x130)._s_0.sav1);
  if (!bVar6) {
    (this->field16_0x40)._s_0.sav1_swap = false;
  }
  bVar6 = IsAlive(&(this->field18_0x130)._s_0.sav2);
  if (!bVar6) {
    (this->field16_0x40)._s_0.sav2_swap = false;
  }
  bVar6 = IsAlive(&(this->field18_0x130)._s_0.sav3);
  if (!bVar6) {
    (this->field16_0x40)._s_0.sav3_swap = false;
  }
  bVar6 = IsAlive(&(this->field18_0x130)._s_0.sav4);
  if (!bVar6) {
    (this->field16_0x40)._s_0.sav4_swap = false;
  }
  bVar6 = IsAlive(&(this->field18_0x130)._s_0.sav5);
  if (!bVar6) {
    (this->field16_0x40)._s_0.sav5_swap = false;
  }
  bVar6 = IsAlive(&(this->field18_0x130)._s_0.sav6);
  if (!bVar6) {
    (this->field16_0x40)._s_0.sav6_swap = false;
  }
  bVar6 = IsAlive(&(this->field18_0x130)._s_0.avbomb1);
  if (!bVar6) {
    (this->field16_0x40)._s_0.bomb_attack = false;
  }
  bVar6 = IsAlive(&(this->field18_0x130)._s_0.avapc1);
  if (!bVar6) {
    (this->field16_0x40)._s_0.apc_attack = false;
  }
  bVar6 = IsAlive(&(this->field18_0x130)._s_0.avwalker);
  if (!bVar6) {
    (this->field16_0x40)._s_0.walker_attack = false;
  }
  piVar1 = &(this->field18_0x130)._s_0.avrecycle;
  bVar6 = IsAlive(piVar1);
  if (((bVar6) && ((this->field16_0x40)._s_0.recycle_move == false)) &&
     (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.next_second < fVar9)) {
    AddHealth(*piVar1,200.0);
    fVar9 = Get_Time();
    (this->field17_0xb4)._s_0.next_second = fVar9 + 1.0;
  }
  if ((this->field16_0x40)._s_0.start_done == false) {
    SetScrap(1,0x19);
    SetScrap(2,0x28);
    SetPilot(1,10);
    SetPilot(2,0x3c);
    AudioMessage("misns800.wav");
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misns800.otf",DisplayInterface::colorWhite,8.0);
    iVar7 = BuildObject("bvsca8",2,"american_spawn",0);
    (this->field18_0x130)._s_0.avscav1 = iVar7;
    iVar7 = BuildObject("bvsca8",2,"american_spawn",0);
    (this->field18_0x130)._s_0.avscav2 = iVar7;
    iVar7 = BuildObject("bvsca8",2,"american_spawn",0);
    (this->field18_0x130)._s_0.avscav3 = iVar7;
    iVar7 = BuildObject("bvra8",2,"american_spawn",0);
    (this->field18_0x130)._s_0.nark = iVar7;
    SetObjectiveName((this->field18_0x130)._s_0.cam1,"Black Dog Base");
    SetObjectiveName((this->field18_0x130)._s_0.cam2,"Drop Zone");
    fVar9 = Get_Time();
    (this->field17_0xb4)._s_0.defense_check = fVar9 + 60.0;
    SetAIP("misns8.aip",2);
    (this->field16_0x40)._s_0.start_done = true;
    (this->field16_0x40)._s_0.plan_a = true;
  }
  piVar1 = &(this->field18_0x130)._s_0.avrig1;
  bVar6 = IsAlive(piVar1);
  if (bVar6) {
    piVar2 = &(this->field18_0x130)._s_0.avrig2;
    bVar6 = IsAlive(piVar2);
    if (!bVar6) goto LAB_00449772;
    if ((this->field16_0x40)._s_0.rig_prep == false) {
      ::Build(*piVar1,"abwpow",1);
      ::Build(*piVar2,"abtowe",1);
      fVar9 = Get_Time();
      (this->field17_0xb4)._s_0.base_build_time = fVar9 + 10.0;
      SetAIP("misns8a.aip",2);
      (this->field16_0x40)._s_0.rig_prep = true;
      goto LAB_00449772;
    }
LAB_00449778:
    if ((this->field16_0x40)._s_0.base_build == false) {
      fVar9 = Get_Time();
      if ((this->field17_0xb4)._s_0.base_build_time < fVar9) {
        AddScrap(2,0x3c);
        bVar6 = IsAlive(piVar1);
        if (bVar6) {
          Dropoff(*piVar1,"rpower1",1);
        }
        piVar2 = &(this->field18_0x130)._s_0.avrig2;
        bVar6 = IsAlive(piVar2);
        if (bVar6) {
          Dropoff(*piVar2,"rtower1",1);
        }
        (this->field16_0x40)._s_0.base_build = true;
      }
      goto LAB_004497de;
    }
LAB_004497e4:
    bVar6 = IsAlive(&(this->field18_0x130)._s_0.avtower1);
    if (((bVar6) && (bVar6 = IsAlive(&(this->field18_0x130)._s_0.avpower1), bVar6)) &&
       ((this->field16_0x40)._s_0.rig_movea == false)) {
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        Goto(*piVar1,"center_path",1);
      }
      piVar2 = &(this->field18_0x130)._s_0.avrig2;
      bVar6 = IsAlive(piVar2);
      if (bVar6) {
        Goto(*piVar2,"center_path",1);
      }
      fVar9 = Get_Time();
      (this->field16_0x40)._s_0.rig_movea = true;
      (this->field17_0xb4)._s_0.rig_check = fVar9 + 90.0;
    }
  }
  else {
LAB_00449772:
    if ((this->field16_0x40)._s_0.rig_prep != false) goto LAB_00449778;
LAB_004497de:
    if ((this->field16_0x40)._s_0.base_build != false) goto LAB_004497e4;
  }
  if (((this->field16_0x40)._s_0.artil_build == false) &&
     ((this->field16_0x40)._s_0.rig_movea != false)) {
    iVar7 = BuildObject("avart8",2,"american_spawn",0);
    (this->field18_0x130)._s_0.popartil = iVar7;
    (this->field16_0x40)._s_0.artil_build = true;
  }
  if ((this->field16_0x40)._s_0.at_geyser == false) {
    piVar2 = &(this->field18_0x130)._s_0.popartil;
    bVar6 = IsAlive(piVar2);
    if (bVar6) {
      Goto(*piVar2,(this->field18_0x130)._s_0.temp_geyser,1);
      (this->field16_0x40)._s_0.at_geyser = true;
    }
  }
  if ((this->field16_0x40)._s_0.silo_center_prep == false) {
    fVar9 = Get_Time();
    if ((this->field17_0xb4)._s_0.rig_check < fVar9) {
      fVar9 = Get_Time();
      (this->field17_0xb4)._s_0.rig_check2 = fVar9 + 5.0;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        ::Build(*piVar1,"absilo",1);
      }
      piVar2 = &(this->field18_0x130)._s_0.avrig2;
      bVar6 = IsAlive(piVar2);
      if (bVar6) {
        ::Build(*piVar2,"absilo",1);
      }
      (this->field16_0x40)._s_0.silo_center_prep = true;
    }
    if ((this->field16_0x40)._s_0.silo_center_prep != false) goto LAB_0044992b;
  }
  else {
LAB_0044992b:
    if (((this->field16_0x40)._s_0.silo1_build == false) &&
       (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.rig_check2 < fVar9)) {
      fVar9 = Get_Time();
      piVar2 = &(this->field19_0x274)._s_0.scrap;
      (this->field17_0xb4)._s_0.rig_check2 = fVar9 + 5.0;
      iVar7 = GetScrap(2);
      *piVar2 = iVar7;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        iVar7 = (this->field18_0x130)._s_0.temp_geyser;
        iVar8 = *piVar1;
LAB_0044999b:
        GetDistance(iVar8,iVar7);
        _ftol2_sse();
        (this->field19_0x274)._s_0.check2 = extraout_EAX;
      }
      else {
        piVar3 = &(this->field18_0x130)._s_0.avrig2;
        bVar6 = IsAlive(piVar3);
        if (bVar6) {
          iVar7 = (this->field18_0x130)._s_0.temp_geyser;
          iVar8 = *piVar3;
          goto LAB_0044999b;
        }
      }
      if ((float)*piVar2 <= 8.0) {
        if (100.0 <= (float)(this->field19_0x274)._s_0.check2) {
          bVar6 = IsAlive(piVar1);
          if (bVar6) {
            Goto(*piVar1,(this->field18_0x130)._s_0.temp_geyser,1);
          }
          piVar2 = &(this->field18_0x130)._s_0.avrig2;
          bVar6 = IsAlive(piVar2);
          if (bVar6) {
            Goto(*piVar2,(this->field18_0x130)._s_0.temp_geyser,1);
          }
        }
        else {
          bVar6 = IsAlive(piVar1);
          if (bVar6) {
            Defend(*piVar1,1);
          }
          piVar2 = &(this->field18_0x130)._s_0.avrig2;
          bVar6 = IsAlive(piVar2);
          if (bVar6) {
            Defend(*piVar2,1);
          }
        }
      }
      else {
        bVar6 = IsAlive(piVar1);
        if (bVar6) {
          Dropoff(*piVar1,"center_silo",1);
          piVar2 = &(this->field18_0x130)._s_0.avrig2;
          bVar6 = IsAlive(piVar2);
          if (bVar6) {
            Goto(*piVar2,"center_silo",1);
          }
          (this->field16_0x40)._s_0.silo1_build = true;
        }
        else {
          piVar2 = &(this->field18_0x130)._s_0.avrig2;
          bVar6 = IsAlive(piVar2);
          if (bVar6) {
            Dropoff(*piVar2,"center_silo",1);
            (this->field16_0x40)._s_0.silo1_build = true;
          }
        }
      }
    }
  }
  if ((this->field16_0x40)._s_0.silo1_build == false) {
LAB_00449b4c:
    if ((this->field16_0x40)._s_0.prep_center_towers != false) goto LAB_00449b56;
  }
  else {
    if ((this->field16_0x40)._s_0.prep_center_towers == false) {
      bVar6 = IsAlive(&(this->field18_0x130)._s_0.avsilo1);
      if (bVar6) {
        bVar6 = IsAlive(piVar1);
        if (bVar6) {
          ::Build(*piVar1,"abwpow",1);
        }
        piVar2 = &(this->field18_0x130)._s_0.avrig2;
        bVar6 = IsAlive(piVar2);
        if (bVar6) {
          ::Build(*piVar2,"abtowe",1);
        }
        SetAIP("misns8b.aip",2);
        fVar9 = Get_Time();
        (this->field17_0xb4)._s_0.rig_check = fVar9 + 10.0;
        fVar9 = Get_Time();
        (this->field16_0x40)._s_0.prep_center_towers = true;
        (this->field17_0xb4)._s_0.muf_timer = fVar9 + 10.0;
      }
      goto LAB_00449b4c;
    }
LAB_00449b56:
    if (((this->field16_0x40)._s_0.rigs_ordered == false) &&
       (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.rig_check < fVar9)) {
      fVar9 = Get_Time();
      (this->field17_0xb4)._s_0.rig_check = fVar9 + 5.0;
      iVar7 = GetScrap(2);
      (this->field19_0x274)._s_0.scrap = iVar7;
      if ((float)iVar7 <= 14.0) {
        bVar6 = IsAlive(piVar1);
        if ((!bVar6) ||
           (fVar9 = GetDistance(*piVar1,(this->field18_0x130)._s_0.temp_geyser), 200.0 <= fVar9)) {
          piVar1 = &(this->field18_0x130)._s_0.avrig2;
          bVar6 = IsAlive(piVar1);
          if ((bVar6) &&
             (fVar9 = GetDistance(*piVar1,(this->field18_0x130)._s_0.temp_geyser), fVar9 < 200.0))
          goto LAB_00449c74;
        }
        else {
          Defend(*piVar1,1);
          bVar6 = IsAlive(&(this->field18_0x130)._s_0.avrig2);
          if (bVar6) {
LAB_00449c74:
            Defend((this->field18_0x130)._s_0.avrig2,1);
          }
        }
        AddScrap(2,2);
      }
      else {
        SetAIP("misns8g.aip",2);
        bVar6 = IsAlive(piVar1);
        if (bVar6) {
          Dropoff(*piVar1,"main_field2",1);
        }
        piVar1 = &(this->field18_0x130)._s_0.avrig2;
        bVar6 = IsAlive(piVar1);
        if (bVar6) {
          Dropoff(*piVar1,"main_field1",1);
        }
        (this->field16_0x40)._s_0.rigs_ordered = true;
      }
    }
  }
  bVar6 = IsAlive(&(this->field18_0x130)._s_0.avtower2);
  if (((bVar6) && (bVar6 = IsAlive(&(this->field18_0x130)._s_0.avpower2), bVar6)) &&
     ((this->field16_0x40)._s_0.welldone_rig == false)) {
    fVar9 = Get_Time();
    (this->field17_0xb4)._s_0.go_to_alt = fVar9 + 20.0;
    SetAIP("misns8b.aip",2);
    fVar9 = Get_Time();
    (this->field17_0xb4)._s_0.center_check = fVar9 + 5.0;
    fVar9 = Get_Time();
    (this->field16_0x40)._s_0.new_turret_orders = true;
    (this->field16_0x40)._s_0.welldone_rig = true;
    (this->field17_0xb4)._s_0.alt_check = fVar9 + 60.0;
  }
  piVar1 = &(this->field18_0x130)._s_0.avtank2;
  bVar6 = IsAlive(piVar1);
  if (bVar6) {
    if ((this->field16_0x40)._s_0.tanks_follow == false) {
      piVar2 = &(this->field18_0x130)._s_0.avmuf;
      bVar6 = IsAlive(piVar2);
      if (bVar6) {
        Follow(*piVar1,*piVar2,1);
        piVar1 = &(this->field18_0x130)._s_0.avtank1;
        bVar6 = IsAlive(piVar1);
        if (bVar6) {
          Follow(*piVar1,*piVar2,1);
        }
        fVar9 = Get_Time();
        (this->field16_0x40)._s_0.tanks_follow = true;
        (this->field17_0xb4)._s_0.tank_check = fVar9 + 30.0;
      }
      goto LAB_00449d62;
    }
LAB_00449d68:
    fVar9 = Get_Time();
    if (fVar9 <= (this->field17_0xb4)._s_0.tank_check) goto LAB_00449da6;
    if ((this->field16_0x40)._s_0.tanks_built == false) {
      fVar9 = Get_Time();
      (this->field17_0xb4)._s_0.tank_check = fVar9 + 30.0;
      bVar6 = IsAlive(&(this->field18_0x130)._s_0.avtank3);
      if (bVar6) {
        (this->field16_0x40)._s_0.tanks_built = true;
      }
      goto LAB_00449da6;
    }
LAB_00449dac:
    if (((this->field16_0x40)._s_0.welldone_rig != false) &&
       ((this->field16_0x40)._s_0.plan_a != false)) {
      (this->field16_0x40)._s_0.plan_a = false;
      (this->field16_0x40)._s_0.plan_b = true;
    }
  }
  else {
LAB_00449d62:
    if ((this->field16_0x40)._s_0.tanks_follow != false) goto LAB_00449d68;
LAB_00449da6:
    if ((this->field16_0x40)._s_0.tanks_built != false) goto LAB_00449dac;
  }
  if ((this->field16_0x40)._s_0.plan_b != false) {
    if (((this->field16_0x40)._s_0.turret4_set != false) &&
       (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.turret4_set_time < fVar9)) {
      piVar1 = &(this->field18_0x130)._s_0.popartil;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        fVar9 = Get_Time();
        (this->field17_0xb4)._s_0.turret4_set_time = fVar9 + 180.0;
        Defend(*piVar1,1);
      }
    }
    if ((this->field16_0x40)._s_0.muf_pack == false) {
      piVar1 = &(this->field18_0x130)._s_0.avmuf;
      bVar6 = IsAlive(piVar1);
      if ((bVar6) && (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.muf_timer < fVar9)) {
        fVar9 = Get_Time();
        (this->field17_0xb4)._s_0.muf_timer = fVar9 + 10.0;
        iVar7 = GetScrap(2);
        (this->field19_0x274)._s_0.scrap = iVar7;
        if (0xb < iVar7) {
          Pickup(*piVar1,0,1);
          fVar9 = Get_Time();
          (this->field16_0x40)._s_0.muf_pack = true;
          (this->field17_0xb4)._s_0.muf_timer = fVar9 + 10.0;
        }
      }
    }
    if (((this->field16_0x40)._s_0.convoy_start == false) &&
       ((this->field16_0x40)._s_0.muf_pack != false)) {
      piVar1 = &(this->field18_0x130)._s_0.avmuf;
      bVar6 = IsAlive(piVar1);
      if ((bVar6) && (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.muf_timer < fVar9)) {
        Goto(*piVar1,"convoy_path",1);
        SetAIP("misns8d.aip",2);
        fVar9 = Get_Time();
        (this->field17_0xb4)._s_0.muf_timer = fVar9 + 60.0;
        fVar9 = Get_Time();
        piVar2 = &(this->field18_0x130)._s_0.avfighter1;
        (this->field17_0xb4)._s_0.muf_warning = fVar9 + 10.0;
        bVar6 = IsAlive(piVar2);
        if (bVar6) {
          Follow(*piVar2,*piVar1,1);
        }
        piVar2 = &(this->field18_0x130)._s_0.avfighter2;
        bVar6 = IsAlive(piVar2);
        if (bVar6) {
          Follow(*piVar2,*piVar1,1);
        }
        (this->field16_0x40)._s_0.convoy_start = true;
      }
    }
    if (((this->field16_0x40)._s_0.warning == false) &&
       ((this->field16_0x40)._s_0.convoy_start != false)) {
      piVar1 = &(this->field18_0x130)._s_0.avmuf;
      bVar6 = IsAlive(piVar1);
      if ((bVar6) && (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.muf_warning < fVar9)) {
        fVar9 = Get_Time();
        iVar7 = *piVar1;
        iVar8 = (this->field18_0x130)._s_0.user;
        (this->field17_0xb4)._s_0.muf_warning = fVar9 + 6.0;
        fVar9 = GetDistance(iVar8,iVar7);
        if (100.0 <= fVar9) {
          fVar9 = GetDistance(*piVar1,(this->field18_0x130)._s_0.dis_geyser1);
          if (100.0 <= fVar9) goto LAB_0044a043;
          AudioMessage("misns801.wav");
          iVar7 = BuildObject("apcamr",1,"cam_spawn",0);
          (this->field18_0x130)._s_0.cam3 = iVar7;
          SetObjectiveName(iVar7,"Choke Point");
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misns800.otf",DisplayInterface::colorWhite,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misns801.otf",DisplayInterface::colorWhite,8.0);
        }
        (this->field16_0x40)._s_0.warning = true;
      }
    }
LAB_0044a043:
    if ((this->field16_0x40)._s_0.convoy_over == false) {
      if ((this->field16_0x40)._s_0.convoy_start != false) {
        piVar1 = &(this->field18_0x130)._s_0.avmuf;
        bVar6 = IsAlive(piVar1);
        if ((bVar6) && (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.muf_timer < fVar9)) {
          fVar9 = Get_Time();
          iVar7 = (this->field18_0x130)._s_0.center_geyser;
          iVar8 = *piVar1;
          (this->field17_0xb4)._s_0.muf_timer = fVar9 + 5.0;
          fVar9 = GetDistance(iVar8,iVar7);
          if (fVar9 < 100.0) {
            Goto(*piVar1,(this->field18_0x130)._s_0.center_geyser,1);
            (this->field16_0x40)._s_0.convoy_over = true;
          }
        }
      }
      if ((this->field16_0x40)._s_0.convoy_over != false) goto LAB_0044a0ba;
    }
    else {
LAB_0044a0ba:
      if ((this->field16_0x40)._s_0.muf_deployed == false) {
        piVar1 = &(this->field18_0x130)._s_0.avmuf;
        bVar6 = IsAlive(piVar1);
        if ((bVar6) && (bVar6 = IsDeployed(*piVar1), bVar6)) {
          (this->field16_0x40)._s_0.muf_deployed = true;
        }
      }
    }
    if ((this->field16_0x40)._s_0.convoy_start != false) {
      piVar1 = &(this->field18_0x130)._s_0.avmuf;
      bVar6 = IsAlive(piVar1);
      if ((!bVar6) && ((this->field16_0x40)._s_0.new_muf == false)) {
        iVar7 = BuildObject("bvtavk",2,"t1post",0);
        (this->field18_0x130)._s_0.screwu1 = iVar7;
        iVar7 = BuildObject("bvtavk",2,"t1post",0);
        piVar2 = &(this->field18_0x130)._s_0.ccarecycle;
        (this->field18_0x130)._s_0.screwu2 = iVar7;
        bVar6 = IsAlive(piVar2);
        if (bVar6) {
          Attack((this->field18_0x130)._s_0.screwu1,*piVar2,1);
          Attack((this->field18_0x130)._s_0.screwu2,*piVar2,1);
        }
        iVar7 = BuildObject("bvmuf",2,"american_spawn",0);
        *piVar1 = iVar7;
        Goto(iVar7,(this->field18_0x130)._s_0.avmuf_geyser,1);
        (this->field16_0x40)._s_0.muf_deployed = false;
        (this->field16_0x40)._s_0.new_muf = true;
      }
    }
    if (((this->field16_0x40)._s_0.start_attack == false) &&
       ((this->field16_0x40)._s_0.muf_deployed != false)) {
      SetAIP("misns8c.aip",2);
      (this->field16_0x40)._s_0.start_attack = true;
    }
    piVar1 = &(this->field18_0x130)._s_0.avbomb1;
    bVar6 = IsAlive(piVar1);
    if ((bVar6) && ((this->field16_0x40)._s_0.bomb_attack == false)) {
      piVar2 = &(this->field18_0x130)._s_0.ccarecycle;
      bVar6 = IsAlive(piVar2);
      if (bVar6) {
        Attack(*piVar1,*piVar2,1);
      }
      (this->field16_0x40)._s_0.bomb_attack = true;
    }
    piVar1 = &(this->field18_0x130)._s_0.avapc1;
    bVar6 = IsAlive(piVar1);
    if ((bVar6) && ((this->field16_0x40)._s_0.apc_attack == false)) {
      piVar2 = &(this->field18_0x130)._s_0.ccarecycle;
      bVar6 = IsAlive(piVar2);
      if (bVar6) {
        Attack(*piVar1,*piVar2,1);
      }
      (this->field16_0x40)._s_0.apc_attack = true;
    }
    piVar1 = &(this->field18_0x130)._s_0.avwalker;
    bVar6 = IsAlive(piVar1);
    if ((bVar6) && ((this->field16_0x40)._s_0.walker_attack == false)) {
      piVar2 = &(this->field18_0x130)._s_0.ccarecycle;
      bVar6 = IsAlive(piVar2);
      if (bVar6) {
        Attack(*piVar1,*piVar2,0);
      }
      (this->field16_0x40)._s_0.walker_attack = true;
    }
  }
  if ((this->field16_0x40)._s_0.plan_c == false) {
    piVar1 = &(this->field18_0x130)._s_0.avrecycle;
    bVar6 = IsAlive(piVar1);
    if ((bVar6) && (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.defense_check < fVar9)) {
      fVar9 = Get_Time();
      (this->field17_0xb4)._s_0.defense_check = fVar9 + 5.0;
      iVar8 = CountUnitsNearObject(*piVar1,200.0,2,"abtowe");
      iVar7 = *piVar1;
      (this->field19_0x274)._s_0.defense1 = iVar8;
      iVar7 = CountUnitsNearObject(iVar7,200.0,2,"abwpow");
      (this->field19_0x274)._s_0.defense2 = iVar7;
      iVar7 = GetScrap(2);
      (this->field19_0x274)._s_0.scrap = iVar7;
      if ((((this->field19_0x274)._s_0.defense1 == 0) || ((this->field19_0x274)._s_0.defense2 == 0))
         && ((float)iVar7 < 10.0)) {
        (this->field16_0x40)._s_0.plan_a = false;
        (this->field16_0x40)._s_0.plan_b = false;
        (this->field16_0x40)._s_0.plan_c = true;
      }
    }
  }
  if ((this->field16_0x40)._s_0.plan_c != false) {
    if ((((this->field16_0x40)._s_0.general_message1 != false) ||
        ((this->field16_0x40)._s_0.sav_payback != false)) &&
       ((this->field16_0x40)._s_0.recycle_pack == false)) {
      piVar1 = &(this->field18_0x130)._s_0.avrecycle;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        AddScrap(2,0x14);
        SetAIP("misns8c.aip",2);
        Pickup(*piVar1,0,1);
        fVar9 = Get_Time();
        (this->field16_0x40)._s_0.recycle_pack = true;
        (this->field17_0xb4)._s_0.recy_time = fVar9 + 10.0;
      }
    }
    if ((this->field16_0x40)._s_0.recycle_move == false) {
      if ((this->field16_0x40)._s_0.recycle_pack != false) {
        piVar1 = &(this->field18_0x130)._s_0.avrecycle;
        bVar6 = IsAlive(piVar1);
        if ((bVar6) && (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.recy_time < fVar9)) {
          Goto(*piVar1,"escape_route",1);
          fVar9 = Get_Time();
          iVar7 = *piVar1;
          (this->field17_0xb4)._s_0.recy_time = fVar9 + 60.0;
          SetPerceivedTeam(iVar7,1);
          piVar1 = &(this->field18_0x130)._s_0.basetower1;
          bVar6 = IsAlive(piVar1);
          if (bVar6) {
            SetPerceivedTeam(*piVar1,1);
          }
          piVar1 = &(this->field18_0x130)._s_0.basetower2;
          bVar6 = IsAlive(piVar1);
          if (bVar6) {
            SetPerceivedTeam(*piVar1,1);
          }
          piVar1 = &(this->field18_0x130)._s_0.avtower1;
          bVar6 = IsAlive(piVar1);
          if (bVar6) {
            SetPerceivedTeam(*piVar1,1);
          }
          piVar1 = &(this->field18_0x130)._s_0.powerplant1;
          bVar6 = IsAlive(piVar1);
          if (bVar6) {
            SetPerceivedTeam(*piVar1,1);
          }
          piVar1 = &(this->field18_0x130)._s_0.powerplant2;
          bVar6 = IsAlive(piVar1);
          if (bVar6) {
            SetPerceivedTeam(*piVar1,1);
          }
          piVar1 = &(this->field18_0x130)._s_0.avpower1;
          bVar6 = IsAlive(piVar1);
          if (bVar6) {
            SetPerceivedTeam(*piVar1,1);
          }
          piVar1 = &(this->field18_0x130)._s_0.avmuf;
          bVar6 = IsAlive(piVar1);
          if (bVar6) {
            SetPerceivedTeam(*piVar1,1);
          }
          (this->field16_0x40)._s_0.recycle_move = true;
        }
      }
      if ((this->field16_0x40)._s_0.recycle_move != false) goto LAB_0044a4d4;
LAB_0044a547:
      if ((this->field16_0x40)._s_0.recy_goto_geyser != false) goto LAB_0044a54d;
LAB_0044a5a4:
      if ((this->field16_0x40)._s_0.recy_deployed == false) goto LAB_0044a5e8;
    }
    else {
LAB_0044a4d4:
      piVar1 = &(this->field18_0x130)._s_0.avrecycle;
      bVar6 = IsAlive(piVar1);
      if ((!bVar6) || (fVar9 = Get_Time(), fVar9 <= (this->field17_0xb4)._s_0.recy_time))
      goto LAB_0044a547;
      fVar9 = Get_Time();
      iVar7 = (this->field18_0x130)._s_0.last_geyser;
      iVar8 = *piVar1;
      (this->field17_0xb4)._s_0.recy_time = fVar9 + 10.0;
      fVar9 = GetDistance(iVar8,iVar7);
      if (100.0 <= fVar9) goto LAB_0044a547;
      if ((this->field16_0x40)._s_0.recy_goto_geyser == false) {
        Goto(*piVar1,(this->field18_0x130)._s_0.last_geyser,1);
        SetPerceivedTeam(*piVar1,2);
        (this->field16_0x40)._s_0.recy_goto_geyser = true;
        goto LAB_0044a547;
      }
LAB_0044a54d:
      if ((this->field16_0x40)._s_0.recy_deployed == false) {
        piVar1 = &(this->field18_0x130)._s_0.avrecycle;
        bVar6 = IsAlive(piVar1);
        if ((bVar6) && (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.recy_time < fVar9)) {
          fVar9 = Get_Time();
          iVar7 = *piVar1;
          (this->field17_0xb4)._s_0.recy_time = fVar9 + 5.0;
          bVar6 = IsDeployed(iVar7);
          if (bVar6) {
            SetAIP("misns8a.aip",2);
            (this->field16_0x40)._s_0.recy_deployed = true;
          }
        }
        goto LAB_0044a5a4;
      }
    }
    if ((((this->field16_0x40)._s_0.back_in_business == false) &&
        (bVar6 = IsAlive(&(this->field18_0x130)._s_0.avturret1), bVar6)) &&
       (bVar6 = IsAlive(&(this->field18_0x130)._s_0.avturret2), bVar6)) {
      SetAIP("misns8f.aip",2);
      (this->field16_0x40)._s_0.back_in_business = true;
    }
  }
LAB_0044a5e8:
  if (((this->field16_0x40)._s_0.welldone_rig == false) ||
     (fVar9 = Get_Time(), fVar9 <= (this->field17_0xb4)._s_0.go_to_alt)) {
LAB_0044a68c:
    if ((this->field16_0x40)._s_0.rigs_reordered != false) goto LAB_0044a699;
  }
  else {
    if ((this->field16_0x40)._s_0.rigs_reordered == false) {
      piVar1 = &(this->field18_0x130)._s_0.avsilo1;
      bVar6 = IsAlive(piVar1);
      piVar2 = &(this->field18_0x130)._s_0.avrig1;
      if (bVar6) {
        bVar6 = IsAlive(piVar2);
        if (bVar6) {
          Follow(*piVar2,*piVar1,1);
        }
      }
      else {
        bVar6 = IsAlive(piVar2);
        if (bVar6) {
          ::Build(*piVar2,"absilo",1);
        }
      }
      piVar1 = &(this->field18_0x130)._s_0.avrig2;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        Goto(*piVar1,"go_path",1);
      }
      (this->field16_0x40)._s_0.rigs_reordered = true;
      goto LAB_0044a68c;
    }
LAB_0044a699:
    piVar1 = &(this->field18_0x130)._s_0.avrig1;
    bVar6 = IsAlive(piVar1);
    if ((bVar6) && (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.center_check < fVar9)) {
      if ((this->field16_0x40)._s_0.rebuild1_prep == false) {
        if (((this->field16_0x40)._s_0.rebuild2_prep == false) &&
           ((this->field16_0x40)._s_0.rebuild3_prep == false)) {
          fVar9 = Get_Time();
          (this->field17_0xb4)._s_0.center_check = fVar9 + 10.0;
          iVar7 = CountUnitsNearObject((this->field18_0x130)._s_0.temp_geyser,900.0,2,"absilo");
          (this->field19_0x274)._s_0.silo1 = iVar7;
          iVar7 = CountUnitsNearObject((this->field18_0x130)._s_0.temp_geyser,900.0,2,"abwpow");
          (this->field19_0x274)._s_0.power1 = iVar7;
          iVar7 = CountUnitsNearObject((this->field18_0x130)._s_0.temp_geyser,900.0,2,"abtowe");
          (this->field19_0x274)._s_0.tower1 = iVar7;
          if ((this->field19_0x274)._s_0.silo1 == 0) {
            ::Build(*piVar1,"absilo",1);
            fVar9 = Get_Time();
            (this->field17_0xb4)._s_0.rebuild_time = fVar9 + 5.0;
            (this->field16_0x40)._s_0.rebuild1_prep = true;
          }
          else if ((this->field19_0x274)._s_0.power1 == 0) {
            ::Build(*piVar1,"abwpow",1);
            fVar9 = Get_Time();
            (this->field17_0xb4)._s_0.rebuild_time = fVar9 + 5.0;
            (this->field16_0x40)._s_0.rebuild2_prep = true;
          }
          else if (iVar7 == 0) {
            ::Build(*piVar1,"abtowe",1);
            fVar9 = Get_Time();
            (this->field17_0xb4)._s_0.rebuild_time = fVar9 + 5.0;
            (this->field16_0x40)._s_0.rebuild3_prep = true;
          }
          else {
            Defend(*piVar1,1);
          }
        }
        if ((this->field16_0x40)._s_0.rebuild1_prep != false) goto LAB_0044a7f7;
      }
      else {
LAB_0044a7f7:
        if (((this->field16_0x40)._s_0.rebuilding1 == false) &&
           (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.rebuild_time < fVar9)) {
          fVar9 = Get_Time();
          (this->field17_0xb4)._s_0.rebuild_time = fVar9 + 5.0;
          iVar7 = GetScrap(2);
          (this->field19_0x274)._s_0.scrap = iVar7;
          if (8 < iVar7) {
            Dropoff(*piVar1,"center_silo",1);
            (this->field16_0x40)._s_0.rebuilding1 = true;
          }
        }
      }
      if ((((this->field16_0x40)._s_0.rebuild2_prep != false) &&
          ((this->field16_0x40)._s_0.rebuilding2 == false)) &&
         (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.rebuild_time < fVar9)) {
        fVar9 = Get_Time();
        (this->field17_0xb4)._s_0.rebuild_time = fVar9 + 5.0;
        iVar7 = GetScrap(2);
        (this->field19_0x274)._s_0.scrap = iVar7;
        if (10 < iVar7) {
          Dropoff(*piVar1,"main_field2",1);
          (this->field16_0x40)._s_0.rebuilding2 = true;
        }
      }
      if ((((this->field16_0x40)._s_0.rebuild3_prep != false) &&
          ((this->field16_0x40)._s_0.rebuilding3 == false)) &&
         (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.rebuild_time < fVar9)) {
        fVar9 = Get_Time();
        (this->field17_0xb4)._s_0.rebuild_time = fVar9 + 5.0;
        iVar7 = GetScrap(2);
        (this->field19_0x274)._s_0.scrap = iVar7;
        if (10 < iVar7) {
          Dropoff(*piVar1,"main_field1",1);
          (this->field16_0x40)._s_0.rebuilding3 = true;
        }
      }
      if (((this->field16_0x40)._s_0.rebuilding1 != false) &&
         (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.center_check < fVar9)) {
        fVar9 = Get_Time();
        (this->field17_0xb4)._s_0.center_check = fVar9 + 10.0;
        iVar7 = CountUnitsNearObject((this->field18_0x130)._s_0.temp_geyser,900.0,2,"absilo");
        (this->field19_0x274)._s_0.silo1 = iVar7;
        if (iVar7 == 1) {
          (this->field16_0x40)._s_0.rebuild1_prep = false;
          (this->field16_0x40)._s_0.rebuilding1 = false;
        }
      }
      if (((this->field16_0x40)._s_0.rebuilding2 != false) &&
         (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.center_check < fVar9)) {
        fVar9 = Get_Time();
        (this->field17_0xb4)._s_0.center_check = fVar9 + 10.0;
        iVar7 = CountUnitsNearObject((this->field18_0x130)._s_0.temp_geyser,900.0,2,"abwpow");
        (this->field19_0x274)._s_0.power1 = iVar7;
        if (iVar7 == 1) {
          (this->field16_0x40)._s_0.rebuild2_prep = false;
          (this->field16_0x40)._s_0.rebuilding2 = false;
        }
      }
      if (((this->field16_0x40)._s_0.rebuilding3 != false) &&
         (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.center_check < fVar9)) {
        fVar9 = Get_Time();
        (this->field17_0xb4)._s_0.center_check = fVar9 + 10.0;
        iVar7 = CountUnitsNearObject((this->field18_0x130)._s_0.temp_geyser,900.0,2,"abtowe");
        (this->field19_0x274)._s_0.tower1 = iVar7;
        if (iVar7 == 1) {
          (this->field16_0x40)._s_0.rebuild3_prep = false;
          (this->field16_0x40)._s_0.rebuilding3 = false;
        }
      }
    }
  }
  if ((this->field16_0x40)._s_0.welldone_rig != false) {
    piVar1 = &(this->field18_0x130)._s_0.avrig2;
    bVar6 = IsAlive(piVar1);
    if (bVar6) {
      pbVar4 = &(this->field16_0x40)._s_0.maintain;
      if (*pbVar4 == false) {
        ::Build(*piVar1,"absilo",1);
        *pbVar4 = true;
      }
      fVar9 = Get_Time();
      if (fVar9 <= (this->field17_0xb4)._s_0.alt_check) {
LAB_0044aa9b:
        if ((this->field16_0x40)._s_0.rig_there == false) goto LAB_0044ae29;
      }
      else if ((this->field16_0x40)._s_0.rig_there == false) {
        fVar9 = Get_Time();
        iVar7 = (this->field18_0x130)._s_0.last_geyser;
        iVar8 = *piVar1;
        (this->field17_0xb4)._s_0.alt_check = fVar9 + 10.0;
        fVar9 = GetDistance(iVar8,iVar7);
        if (fVar9 < 300.0) {
          fVar9 = Get_Time();
          (this->field17_0xb4)._s_0.rebuild_time2 = fVar9 + 5.0;
          (this->field16_0x40)._s_0.rig_there = true;
        }
        goto LAB_0044aa9b;
      }
      fVar9 = Get_Time();
      if ((this->field17_0xb4)._s_0.alt_check < fVar9) {
        if ((this->field16_0x40)._s_0.rebuild4_prep == false) {
          if (((this->field16_0x40)._s_0.rebuild5_prep == false) &&
             ((this->field16_0x40)._s_0.rebuild6_prep == false)) {
            fVar9 = Get_Time();
            (this->field17_0xb4)._s_0.alt_check = fVar9 + 10.0;
            iVar7 = CountUnitsNearObject((this->field18_0x130)._s_0.last_geyser,400.0,2,"absilo");
            (this->field19_0x274)._s_0.silo2 = iVar7;
            iVar7 = CountUnitsNearObject((this->field18_0x130)._s_0.last_geyser,400.0,2,"abwpow");
            (this->field19_0x274)._s_0.power2 = iVar7;
            iVar7 = CountUnitsNearObject((this->field18_0x130)._s_0.last_geyser,400.0,2,"abtowe");
            (this->field19_0x274)._s_0.tower2 = iVar7;
            if ((this->field19_0x274)._s_0.silo2 == 0) {
              ::Build(*piVar1,"absilo",1);
              fVar9 = Get_Time();
              (this->field17_0xb4)._s_0.rebuild_time2 = fVar9 + 5.0;
              (this->field16_0x40)._s_0.rebuild4_prep = true;
            }
            else if ((this->field19_0x274)._s_0.power2 == 0) {
              ::Build(*piVar1,"abwpow",1);
              fVar9 = Get_Time();
              (this->field17_0xb4)._s_0.rebuild_time2 = fVar9 + 5.0;
              (this->field16_0x40)._s_0.rebuild5_prep = true;
            }
            else if (iVar7 == 0) {
              ::Build(*piVar1,"abtowe",1);
              fVar9 = Get_Time();
              (this->field17_0xb4)._s_0.rebuild_time2 = fVar9 + 5.0;
              (this->field16_0x40)._s_0.rebuild6_prep = true;
            }
            else {
              Defend(*piVar1,1);
              if ((this->field16_0x40)._s_0.scav_sent == false) {
                piVar2 = &(this->field18_0x130)._s_0.avscav1;
                bVar6 = IsAlive(piVar2);
                if (bVar6) {
                  Goto(*piVar2,"go_path",1);
                }
                (this->field16_0x40)._s_0.scav_sent = true;
              }
            }
          }
          if ((this->field16_0x40)._s_0.rebuild4_prep != false) goto LAB_0044ac1f;
        }
        else {
LAB_0044ac1f:
          if (((this->field16_0x40)._s_0.rebuilding4 == false) &&
             (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.rebuild_time2 < fVar9)) {
            fVar9 = Get_Time();
            (this->field17_0xb4)._s_0.rebuild_time2 = fVar9 + 5.0;
            iVar7 = GetScrap(2);
            (this->field19_0x274)._s_0.scrap = iVar7;
            if (8 < iVar7) {
              Dropoff(*piVar1,"alt_silo",1);
              (this->field16_0x40)._s_0.rebuilding4 = true;
            }
          }
        }
        if ((((this->field16_0x40)._s_0.rebuild5_prep != false) &&
            ((this->field16_0x40)._s_0.rebuilding5 == false)) &&
           (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.rebuild_time2 < fVar9)) {
          fVar9 = Get_Time();
          (this->field17_0xb4)._s_0.rebuild_time2 = fVar9 + 5.0;
          iVar7 = GetScrap(2);
          (this->field19_0x274)._s_0.scrap = iVar7;
          if (10 < iVar7) {
            Dropoff(*piVar1,"alt_power",1);
            (this->field16_0x40)._s_0.rebuilding5 = true;
          }
        }
        if ((((this->field16_0x40)._s_0.rebuild6_prep != false) &&
            ((this->field16_0x40)._s_0.rebuilding6 == false)) &&
           (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.rebuild_time2 < fVar9)) {
          fVar9 = Get_Time();
          (this->field17_0xb4)._s_0.rebuild_time2 = fVar9 + 5.0;
          iVar7 = GetScrap(2);
          (this->field19_0x274)._s_0.scrap = iVar7;
          if (10 < iVar7) {
            Dropoff(*piVar1,"alt_tower",1);
            (this->field16_0x40)._s_0.rebuilding6 = true;
          }
        }
        if (((this->field16_0x40)._s_0.rebuilding4 != false) &&
           (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.alt_check < fVar9)) {
          fVar9 = Get_Time();
          (this->field17_0xb4)._s_0.alt_check = fVar9 + 10.0;
          iVar7 = CountUnitsNearObject((this->field18_0x130)._s_0.last_geyser,400.0,2,"absilo");
          (this->field19_0x274)._s_0.silo2 = iVar7;
          if (iVar7 == 1) {
            (this->field16_0x40)._s_0.rebuild4_prep = false;
            (this->field16_0x40)._s_0.rebuilding4 = false;
          }
        }
        if (((this->field16_0x40)._s_0.rebuilding5 != false) &&
           (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.alt_check < fVar9)) {
          fVar9 = Get_Time();
          (this->field17_0xb4)._s_0.alt_check = fVar9 + 10.0;
          iVar7 = CountUnitsNearObject((this->field18_0x130)._s_0.last_geyser,400.0,2,"abwpow");
          (this->field19_0x274)._s_0.power2 = iVar7;
          if (iVar7 == 1) {
            (this->field16_0x40)._s_0.rebuild5_prep = false;
            (this->field16_0x40)._s_0.rebuilding5 = false;
          }
        }
        if (((this->field16_0x40)._s_0.rebuilding6 != false) &&
           (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.alt_check < fVar9)) {
          fVar9 = Get_Time();
          (this->field17_0xb4)._s_0.alt_check = fVar9 + 10.0;
          iVar7 = CountUnitsNearObject((this->field18_0x130)._s_0.last_geyser,400.0,2,"abtowe");
          (this->field19_0x274)._s_0.tower2 = iVar7;
          if (iVar7 == 1) {
            (this->field16_0x40)._s_0.rebuild6_prep = false;
            (this->field16_0x40)._s_0.rebuilding6 = false;
          }
        }
      }
    }
  }
LAB_0044ae29:
  if ((this->field16_0x40)._s_0.plan_c != false) {
    if ((this->field16_0x40)._s_0.recycle_message == false) {
      bVar6 = IsAlive(&(this->field18_0x130)._s_0.sav1);
      if (((((bVar6) || (bVar6 = IsAlive(&(this->field18_0x130)._s_0.sav2), bVar6)) ||
           (bVar6 = IsAlive(&(this->field18_0x130)._s_0.sav3), bVar6)) ||
          ((bVar6 = IsAlive(&(this->field18_0x130)._s_0.sav4), bVar6 ||
           (bVar6 = IsAlive(&(this->field18_0x130)._s_0.sav5), bVar6)))) ||
         (bVar6 = IsAlive(&(this->field18_0x130)._s_0.sav6), bVar6)) {
        AudioMessage("misns816.wav");
        (this->field16_0x40)._s_0.savs_alive = true;
      }
      else {
        AudioMessage("misns815.wav");
      }
      (this->field16_0x40)._s_0.recycle_message = true;
    }
    if (((this->field16_0x40)._s_0.plan_c != false) &&
       ((this->field16_0x40)._s_0.general_spawn == false)) {
      iVar7 = BuildObject("svtank",1,"romeski_spawn",0);
      piVar1 = &(this->field18_0x130)._s_0.avrecycle;
      (this->field18_0x130)._s_0.key_tank = iVar7;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        SetPerceivedTeam(*piVar1,1);
        Follow((this->field18_0x130)._s_0.key_tank,(this->field18_0x130)._s_0.sv_geyser,1);
      }
      piVar1 = &(this->field18_0x130)._s_0.basetower1;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        SetPerceivedTeam(*piVar1,1);
      }
      piVar1 = &(this->field18_0x130)._s_0.basetower2;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        SetPerceivedTeam(*piVar1,1);
      }
      piVar1 = &(this->field18_0x130)._s_0.avtower1;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        SetPerceivedTeam(*piVar1,1);
      }
      piVar1 = &(this->field18_0x130)._s_0.powerplant1;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        SetPerceivedTeam(*piVar1,1);
      }
      piVar1 = &(this->field18_0x130)._s_0.powerplant2;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        SetPerceivedTeam(*piVar1,1);
      }
      piVar1 = &(this->field18_0x130)._s_0.avpower1;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        SetPerceivedTeam(*piVar1,1);
      }
      piVar1 = &(this->field18_0x130)._s_0.avmuf;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        SetPerceivedTeam(*piVar1,1);
      }
      fVar9 = Get_Time();
      (this->field17_0xb4)._s_0.pay_off = fVar9 + 5.0;
      fVar9 = Get_Time();
      (this->field17_0xb4)._s_0.sav_check = fVar9 + 10.0;
      (this->field16_0x40)._s_0.general_spawn = true;
    }
  }
  if ((this->field16_0x40)._s_0.general_spawn != false) {
    if (((this->field16_0x40)._s_0.general_message1 == false) &&
       (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.pay_off < fVar9)) {
      fVar9 = Get_Time();
      piVar1 = &(this->field18_0x130)._s_0.key_tank;
      (this->field17_0xb4)._s_0.pay_off = fVar9 + 2.0;
      bVar6 = IsAlive(piVar1);
      if ((bVar6) && (fVar9 = GetDistance((this->field18_0x130)._s_0.user,*piVar1), fVar9 < 150.0))
      {
        SetObjectiveOn(*piVar1);
        SetObjectiveName(*piVar1,"Romeski");
        if ((this->field16_0x40)._s_0.sav_payback == false) {
          Attack(*piVar1,(this->field18_0x130)._s_0.avrecycle,1);
        }
        (this->field16_0x40)._s_0.general_message1 = true;
      }
    }
    if ((this->field16_0x40)._s_0.general_spawn != false) {
      piVar1 = &(this->field18_0x130)._s_0.key_tank;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        if ((this->field16_0x40)._s_0.sav1_togeneral == false) {
          piVar2 = &(this->field18_0x130)._s_0.sav1;
          bVar6 = IsAlive(piVar2);
          if (bVar6) {
            Follow(*piVar2,*piVar1,1);
            pbVar4 = &(this->field16_0x40)._s_0.savs_alive;
            (this->field16_0x40)._s_0.sav1_togeneral = true;
            if ((*pbVar4 == false) && ((this->field16_0x40)._s_0.general_dead == false)) {
              AudioMessage("misns807.wav");
              *pbVar4 = true;
            }
          }
        }
        if ((this->field16_0x40)._s_0.sav2_togeneral == false) {
          piVar2 = &(this->field18_0x130)._s_0.sav2;
          bVar6 = IsAlive(piVar2);
          if (bVar6) {
            Follow(*piVar2,*piVar1,1);
            pbVar4 = &(this->field16_0x40)._s_0.savs_alive;
            (this->field16_0x40)._s_0.sav2_togeneral = true;
            if ((*pbVar4 == false) && ((this->field16_0x40)._s_0.general_dead == false)) {
              AudioMessage("misns807.wav");
              *pbVar4 = true;
            }
          }
        }
        if ((this->field16_0x40)._s_0.sav3_togeneral == false) {
          piVar2 = &(this->field18_0x130)._s_0.sav3;
          bVar6 = IsAlive(piVar2);
          if (bVar6) {
            Follow(*piVar2,*piVar1,1);
            pbVar4 = &(this->field16_0x40)._s_0.savs_alive;
            (this->field16_0x40)._s_0.sav3_togeneral = true;
            if ((*pbVar4 == false) && ((this->field16_0x40)._s_0.general_dead == false)) {
              AudioMessage("misns807.wav");
              *pbVar4 = true;
            }
          }
        }
        if ((this->field16_0x40)._s_0.sav4_togeneral == false) {
          piVar2 = &(this->field18_0x130)._s_0.sav4;
          bVar6 = IsAlive(piVar2);
          if (bVar6) {
            Follow(*piVar2,*piVar1,1);
            pbVar4 = &(this->field16_0x40)._s_0.savs_alive;
            (this->field16_0x40)._s_0.sav4_togeneral = true;
            if ((*pbVar4 == false) && ((this->field16_0x40)._s_0.general_dead == false)) {
              AudioMessage("misns807.wav");
              *pbVar4 = true;
            }
          }
        }
        if ((this->field16_0x40)._s_0.sav5_togeneral == false) {
          piVar2 = &(this->field18_0x130)._s_0.sav5;
          bVar6 = IsAlive(piVar2);
          if (bVar6) {
            Follow(*piVar2,*piVar1,1);
            pbVar4 = &(this->field16_0x40)._s_0.savs_alive;
            (this->field16_0x40)._s_0.sav5_togeneral = true;
            if ((*pbVar4 == false) && ((this->field16_0x40)._s_0.general_dead == false)) {
              AudioMessage("misns807.wav");
              *pbVar4 = true;
            }
          }
        }
        if ((this->field16_0x40)._s_0.sav6_togeneral == false) {
          piVar2 = &(this->field18_0x130)._s_0.sav6;
          bVar6 = IsAlive(piVar2);
          if (bVar6) {
            Follow(*piVar2,*piVar1,1);
            pbVar4 = &(this->field16_0x40)._s_0.savs_alive;
            (this->field16_0x40)._s_0.sav6_togeneral = true;
            if ((*pbVar4 == false) && ((this->field16_0x40)._s_0.general_dead == false)) {
              AudioMessage("misns807.wav");
              *pbVar4 = true;
            }
          }
        }
      }
    }
  }
  fVar9 = Get_Time();
  if ((this->field17_0xb4)._s_0.sav_check < fVar9) {
    fVar9 = Get_Time();
    piVar1 = &(this->field18_0x130)._s_0.sav1;
    (this->field17_0xb4)._s_0.sav_check = fVar9 + 10.0;
    bVar6 = IsAlive(piVar1);
    if (((bVar6) && ((this->field16_0x40)._s_0.sav1_togeneral != false)) &&
       ((this->field16_0x40)._s_0.sav1_attack == false)) {
      piVar2 = &(this->field18_0x130)._s_0.key_tank;
      bVar6 = IsAlive(piVar2);
      if ((bVar6) && (fVar9 = GetDistance(*piVar1,*piVar2), fVar9 < 200.0)) {
        Attack(*piVar1,*piVar2,1);
        (this->field16_0x40)._s_0.sav_attack = true;
        (this->field16_0x40)._s_0.sav1_attack = true;
      }
    }
    piVar1 = &(this->field18_0x130)._s_0.sav2;
    bVar6 = IsAlive(piVar1);
    if (((bVar6) && ((this->field16_0x40)._s_0.sav2_togeneral != false)) &&
       ((this->field16_0x40)._s_0.sav2_attack == false)) {
      piVar2 = &(this->field18_0x130)._s_0.key_tank;
      bVar6 = IsAlive(piVar2);
      if ((bVar6) && (fVar9 = GetDistance(*piVar1,*piVar2), fVar9 < 200.0)) {
        Attack(*piVar1,*piVar2,1);
        (this->field16_0x40)._s_0.sav_attack = true;
        (this->field16_0x40)._s_0.sav2_attack = true;
      }
    }
    piVar1 = &(this->field18_0x130)._s_0.sav3;
    bVar6 = IsAlive(piVar1);
    if (((bVar6) && ((this->field16_0x40)._s_0.sav3_togeneral != false)) &&
       ((this->field16_0x40)._s_0.sav3_attack == false)) {
      piVar2 = &(this->field18_0x130)._s_0.key_tank;
      bVar6 = IsAlive(piVar2);
      if ((bVar6) && (fVar9 = GetDistance(*piVar1,*piVar2), fVar9 < 200.0)) {
        Attack(*piVar1,*piVar2,1);
        (this->field16_0x40)._s_0.sav_attack = true;
        (this->field16_0x40)._s_0.sav3_attack = true;
      }
    }
    piVar1 = &(this->field18_0x130)._s_0.sav4;
    bVar6 = IsAlive(piVar1);
    if (((bVar6) && ((this->field16_0x40)._s_0.sav4_togeneral != false)) &&
       ((this->field16_0x40)._s_0.sav4_attack == false)) {
      piVar2 = &(this->field18_0x130)._s_0.key_tank;
      bVar6 = IsAlive(piVar2);
      if ((bVar6) && (fVar9 = GetDistance(*piVar1,*piVar2), fVar9 < 200.0)) {
        Attack(*piVar1,*piVar2,1);
        (this->field16_0x40)._s_0.sav_attack = true;
        (this->field16_0x40)._s_0.sav4_attack = true;
      }
    }
    piVar1 = &(this->field18_0x130)._s_0.sav5;
    bVar6 = IsAlive(piVar1);
    if (((bVar6) && ((this->field16_0x40)._s_0.sav5_togeneral != false)) &&
       ((this->field16_0x40)._s_0.sav5_attack == false)) {
      piVar2 = &(this->field18_0x130)._s_0.key_tank;
      bVar6 = IsAlive(piVar2);
      if ((bVar6) && (fVar9 = GetDistance(*piVar1,*piVar2), fVar9 < 200.0)) {
        Attack(*piVar1,*piVar2,1);
        (this->field16_0x40)._s_0.sav_attack = true;
        (this->field16_0x40)._s_0.sav5_attack = true;
      }
    }
    piVar1 = &(this->field18_0x130)._s_0.sav6;
    bVar6 = IsAlive(piVar1);
    if (((bVar6) && ((this->field16_0x40)._s_0.sav6_togeneral != false)) &&
       ((this->field16_0x40)._s_0.sav6_attack == false)) {
      piVar2 = &(this->field18_0x130)._s_0.key_tank;
      bVar6 = IsAlive(piVar2);
      if ((bVar6) && (fVar9 = GetDistance(*piVar1,*piVar2), fVar9 < 200.0)) {
        Attack(*piVar1,*piVar2,1);
        (this->field16_0x40)._s_0.sav_attack = true;
        (this->field16_0x40)._s_0.sav6_attack = true;
      }
    }
  }
  if (((((((this->field16_0x40)._s_0.sav1_togeneral != false) ||
         ((this->field16_0x40)._s_0.sav2_togeneral != false)) ||
        ((this->field16_0x40)._s_0.sav3_togeneral != false)) ||
       (((this->field16_0x40)._s_0.sav4_togeneral != false ||
        ((this->field16_0x40)._s_0.sav5_togeneral != false)))) ||
      ((this->field16_0x40)._s_0.sav6_togeneral != false)) &&
     (pbVar4 = &(this->field16_0x40)._s_0.danger_message, *pbVar4 == false)) {
    AudioMessage("misns805.wav");
    AudioMessage("misns818.wav");
    *pbVar4 = true;
  }
  piVar1 = &(this->field18_0x130)._s_0.key_tank;
  bVar6 = IsAlive(piVar1);
  if (((bVar6) && ((this->field16_0x40)._s_0.key_open == false)) &&
     (fVar9 = Get_Time(), (this->field17_0xb4)._s_0.next_second2 < fVar9)) {
    AddHealth(*piVar1,300.0);
    fVar9 = Get_Time();
    (this->field17_0xb4)._s_0.next_second2 = fVar9 + 1.0;
  }
  if ((this->field16_0x40)._s_0.player_payback == false) {
    if ((this->field16_0x40)._s_0.sav_payback == false) {
      bVar6 = IsAlive(piVar1);
      if ((bVar6) && (iVar7 = GetWhoShotMe(*piVar1), iVar7 != 0)) {
        if ((this->field18_0x130)._s_0.user == iVar7) {
          AudioMessage("misns819.wav");
          Attack(*piVar1,(this->field18_0x130)._s_0.user,1);
          (this->field16_0x40)._s_0.key_open = true;
          (this->field16_0x40)._s_0.player_payback = true;
        }
        else if (((((this->field18_0x130)._s_0.badsav1 == iVar7) ||
                  ((this->field18_0x130)._s_0.badsav2 == iVar7)) ||
                 ((this->field18_0x130)._s_0.badsav3 == iVar7)) ||
                ((((this->field18_0x130)._s_0.badsav4 == iVar7 ||
                  ((this->field18_0x130)._s_0.badsav5 == iVar7)) ||
                 ((this->field18_0x130)._s_0.badsav6 == iVar7)))) {
          fVar9 = Get_Time();
          (this->field17_0xb4)._s_0.help_me_check = fVar9 + 5.0;
          (this->field16_0x40)._s_0.key_open = true;
          (this->field16_0x40)._s_0.sav_payback = true;
        }
      }
      goto LAB_0044b6c9;
    }
LAB_0044b6d6:
    if ((((this->field16_0x40)._s_0.general_message3 == false) && (bVar6 = IsAlive(piVar1), bVar6))
       && ((fVar9 = GetHealth(*piVar1), fVar9 < 0.8 &&
           ((this->field16_0x40)._s_0.general_message2 == false)))) {
      AudioMessage("misns817.wav");
      (this->field16_0x40)._s_0.general_message3 = true;
    }
    if (((this->field16_0x40)._s_0.sav_payback != false) &&
       ((this->field16_0x40)._s_0.general_message2 == false)) {
      fVar9 = Get_Time();
      pfVar5 = &(this->field17_0xb4)._s_0.help_me_check;
      if (*pfVar5 < fVar9) {
        fVar9 = Get_Time();
        *pfVar5 = fVar9 + 3.0;
        bVar6 = IsAlive(piVar1);
        if ((bVar6) && (fVar9 = GetDistance(*piVar1,(this->field18_0x130)._s_0.user), fVar9 < 130.0)
           ) {
          Follow(*piVar1,(this->field18_0x130)._s_0.user,1);
          AudioMessage("misns810.wav");
          (this->field16_0x40)._s_0.general_message2 = true;
        }
      }
    }
  }
  else {
LAB_0044b6c9:
    if ((this->field16_0x40)._s_0.sav_payback != false) goto LAB_0044b6d6;
  }
  bVar6 = IsAlive(piVar1);
  if (bVar6) {
    if ((this->field16_0x40)._s_0.general_scream == false) {
      fVar9 = GetHealth(*piVar1);
      if (fVar9 < 0.1) {
        AudioMessage("misns812.wav");
        fVar9 = Get_Time();
        (this->field17_0xb4)._s_0.damage_time = fVar9 + 3.0;
        (this->field16_0x40)._s_0.general_scream = true;
      }
      goto LAB_0044b7e5;
    }
  }
  else {
LAB_0044b7e5:
    if ((this->field16_0x40)._s_0.general_scream == false) goto LAB_0044b829;
  }
  fVar9 = Get_Time();
  if (((this->field17_0xb4)._s_0.damage_time < fVar9) &&
     ((this->field16_0x40)._s_0.general_dead == false)) {
    bVar6 = IsAlive(piVar1);
    if (bVar6) {
      Damage(*piVar1,1000);
    }
    (this->field16_0x40)._s_0.general_dead = true;
  }
LAB_0044b829:
  if (((this->field16_0x40)._s_0.general_spawn != false) &&
     ((bVar6 = IsAlive(piVar1), !bVar6 || ((this->field16_0x40)._s_0.sav_attack != false)))) {
    if ((this->field16_0x40)._s_0.sav1_swap == false) {
      piVar2 = &(this->field18_0x130)._s_0.sav1;
      bVar6 = IsAlive(piVar2);
      if (bVar6) {
        iVar7 = BuildObject("savs8",2,*piVar2);
        (this->field18_0x130)._s_0.badsav1 = iVar7;
        SetIndependence(iVar7,1);
        RemoveObject(*piVar2);
        bVar6 = IsAlive(piVar1);
        if (bVar6) {
          Attack((this->field18_0x130)._s_0.badsav1,*piVar1,1);
        }
        pbVar4 = &(this->field16_0x40)._s_0.danger_message;
        if (*pbVar4 == false) {
          AudioMessage("misns805.wav");
          *pbVar4 = true;
        }
        (this->field16_0x40)._s_0.sav1_swap = true;
      }
    }
    if ((this->field16_0x40)._s_0.sav2_swap == false) {
      piVar2 = &(this->field18_0x130)._s_0.sav2;
      bVar6 = IsAlive(piVar2);
      if (bVar6) {
        iVar7 = BuildObject("savs8",2,*piVar2);
        (this->field18_0x130)._s_0.badsav2 = iVar7;
        SetIndependence(iVar7,1);
        RemoveObject(*piVar2);
        bVar6 = IsAlive(piVar1);
        if (bVar6) {
          Attack((this->field18_0x130)._s_0.badsav2,*piVar1,1);
        }
        pbVar4 = &(this->field16_0x40)._s_0.danger_message;
        if (*pbVar4 == false) {
          AudioMessage("misns805.wav");
          *pbVar4 = true;
        }
        (this->field16_0x40)._s_0.sav2_swap = true;
      }
    }
    if ((this->field16_0x40)._s_0.sav3_swap == false) {
      piVar2 = &(this->field18_0x130)._s_0.sav3;
      bVar6 = IsAlive(piVar2);
      if (bVar6) {
        iVar7 = BuildObject("savs8",2,*piVar2);
        (this->field18_0x130)._s_0.badsav3 = iVar7;
        SetIndependence(iVar7,1);
        RemoveObject(*piVar2);
        bVar6 = IsAlive(piVar1);
        if (bVar6) {
          Attack((this->field18_0x130)._s_0.badsav3,*piVar1,1);
        }
        pbVar4 = &(this->field16_0x40)._s_0.danger_message;
        if (*pbVar4 == false) {
          AudioMessage("misns805.wav");
          *pbVar4 = true;
        }
        (this->field16_0x40)._s_0.sav3_swap = true;
      }
    }
    if ((this->field16_0x40)._s_0.sav4_swap == false) {
      piVar2 = &(this->field18_0x130)._s_0.sav4;
      bVar6 = IsAlive(piVar2);
      if (bVar6) {
        iVar7 = BuildObject("savs8",2,*piVar2);
        (this->field18_0x130)._s_0.badsav4 = iVar7;
        SetIndependence(iVar7,1);
        RemoveObject(*piVar2);
        bVar6 = IsAlive(piVar1);
        if (bVar6) {
          Attack((this->field18_0x130)._s_0.badsav4,*piVar1,1);
        }
        pbVar4 = &(this->field16_0x40)._s_0.danger_message;
        if (*pbVar4 == false) {
          AudioMessage("misns805.wav");
          *pbVar4 = true;
        }
        (this->field16_0x40)._s_0.sav4_swap = true;
      }
    }
    if ((this->field16_0x40)._s_0.sav5_swap == false) {
      piVar2 = &(this->field18_0x130)._s_0.sav5;
      bVar6 = IsAlive(piVar2);
      if (bVar6) {
        iVar7 = BuildObject("savs8",2,*piVar2);
        (this->field18_0x130)._s_0.badsav5 = iVar7;
        SetIndependence(iVar7,1);
        RemoveObject(*piVar2);
        bVar6 = IsAlive(piVar1);
        if (bVar6) {
          Attack((this->field18_0x130)._s_0.badsav5,*piVar1,1);
        }
        pbVar4 = &(this->field16_0x40)._s_0.danger_message;
        if (*pbVar4 == false) {
          AudioMessage("misns805.wav");
          *pbVar4 = true;
        }
        (this->field16_0x40)._s_0.sav5_swap = true;
      }
    }
    if ((this->field16_0x40)._s_0.sav6_swap == false) {
      piVar2 = &(this->field18_0x130)._s_0.sav6;
      bVar6 = IsAlive(piVar2);
      if (bVar6) {
        iVar7 = BuildObject("savs8",2,*piVar2);
        (this->field18_0x130)._s_0.badsav6 = iVar7;
        SetIndependence(iVar7,1);
        RemoveObject(*piVar2);
        bVar6 = IsAlive(piVar1);
        if (bVar6) {
          Attack((this->field18_0x130)._s_0.badsav6,*piVar1,1);
        }
        pbVar4 = &(this->field16_0x40)._s_0.danger_message;
        if (*pbVar4 == false) {
          AudioMessage("misns805.wav");
          *pbVar4 = true;
        }
        (this->field16_0x40)._s_0.sav6_swap = true;
      }
    }
  }
  bVar6 = IsAlive(&(this->field18_0x130)._s_0.avrecycle);
  if ((!bVar6) && ((this->field16_0x40)._s_0.game_over == false)) {
    piVar2 = &(this->field18_0x130)._s_0.badsav1;
    bVar6 = IsAlive(piVar2);
    if (bVar6) {
      Goto(*piVar2,(this->field18_0x130)._s_0.first_geyser,1);
    }
    piVar2 = &(this->field18_0x130)._s_0.badsav2;
    bVar6 = IsAlive(piVar2);
    if (bVar6) {
      Goto(*piVar2,(this->field18_0x130)._s_0.first_geyser,1);
    }
    piVar2 = &(this->field18_0x130)._s_0.badsav3;
    bVar6 = IsAlive(piVar2);
    if (bVar6) {
      Goto(*piVar2,(this->field18_0x130)._s_0.first_geyser,1);
    }
    piVar2 = &(this->field18_0x130)._s_0.badsav4;
    bVar6 = IsAlive(piVar2);
    if (bVar6) {
      Goto(*piVar2,(this->field18_0x130)._s_0.first_geyser,1);
    }
    piVar2 = &(this->field18_0x130)._s_0.badsav5;
    bVar6 = IsAlive(piVar2);
    if (bVar6) {
      Goto(*piVar2,(this->field18_0x130)._s_0.first_geyser,1);
    }
    piVar2 = &(this->field18_0x130)._s_0.badsav6;
    bVar6 = IsAlive(piVar2);
    if (bVar6) {
      Goto(*piVar2,(this->field18_0x130)._s_0.first_geyser,1);
    }
    bVar6 = IsAlive(piVar1);
    if (bVar6) {
      AudioMessage("misns803.wav");
      AudioMessage("misns808.wav");
      pcVar10 = "misns8w1.des";
      fVar9 = Get_Time();
      fVar9 = fVar9 + 35.0;
    }
    else {
      AudioMessage("misns814.wav");
      pcVar10 = "misns8w1.des";
      fVar9 = Get_Time();
      fVar9 = fVar9 + 25.0;
    }
    SucceedMission(fVar9,pcVar10);
    (this->field16_0x40)._s_0.game_over = true;
  }
  return;
}
