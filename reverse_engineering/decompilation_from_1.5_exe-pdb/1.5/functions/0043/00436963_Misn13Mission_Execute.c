/*
 * Entry: 00436963
 * Name: Misn13Mission::Execute
 * Namespace: Misn13Mission
 * Signature: void Execute(Misn13Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn13Mission::Execute(Misn13Mission *this)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  float fVar7;
  char *pcVar8;
  
  iVar3 = GetPlayerHandle();
  bVar2 = (this->field16_0x40)._s_0.bomber_attack;
  (this->field18_0xac)._s_0.user = iVar3;
  if (bVar2 != false) {
    bVar2 = IsAlive(&(this->field18_0xac)._s_0.sv1);
    if (!bVar2) {
      (this->field16_0x40)._s_0.sv1_wait = false;
    }
    piVar6 = &(this->field18_0xac)._s_0.sv4;
    bVar2 = IsAlive(piVar6);
    if (!bVar2) {
      (this->field16_0x40)._s_0.sv4_wait = false;
    }
    piVar5 = &(this->field18_0xac)._s_0.sv3;
    bVar2 = IsAlive(piVar5);
    if (!bVar2) {
      (this->field16_0x40)._s_0.sv3_wait = false;
    }
    bVar2 = IsAlive(piVar5);
    if ((!bVar2) && (bVar2 = IsAlive(piVar6), !bVar2)) {
      (this->field16_0x40)._s_0.make_bomber = false;
      (this->field17_0x7c)._s_0.bomber_retreat_time = 99999.0;
      (this->field16_0x40)._s_0.bomber_attack = false;
      (this->field16_0x40)._s_0.new_target = false;
      (this->field16_0x40)._s_0.bomber_retreat = false;
      (this->field16_0x40)._s_0.bomber_reload = false;
    }
  }
  bVar2 = IsAlive(&(this->field18_0xac)._s_0.tank1);
  if (!bVar2) {
    (this->field16_0x40)._s_0.assign_tank1 = false;
  }
  bVar2 = IsAlive(&(this->field18_0xac)._s_0.tank2);
  if (!bVar2) {
    (this->field16_0x40)._s_0.assign_tank2 = false;
  }
  bVar2 = IsAlive(&(this->field18_0xac)._s_0.tank3);
  if (!bVar2) {
    (this->field16_0x40)._s_0.assign_tank3 = false;
  }
  bVar2 = IsAlive(&(this->field18_0xac)._s_0.tank4);
  if (!bVar2) {
    (this->field16_0x40)._s_0.assign_tank4 = false;
  }
  if ((this->field16_0x40)._s_0.start_done == false) {
    AudioMessage("misn1300.wav");
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misn1300.otf",DisplayInterface::colorWhite,8.0);
    SetPilot(1,10);
    SetPilot(2,0x28);
    SetScrap(1,0x28);
    SetScrap(2,200);
    Defend((this->field18_0xac)._s_0.tank1,1);
    Defend((this->field18_0xac)._s_0.tank2,1);
    Defend((this->field18_0xac)._s_0.artil1,1);
    Defend((this->field18_0xac)._s_0.artil2,1);
    Defend((this->field18_0xac)._s_0.artil3,1);
    Defend((this->field18_0xac)._s_0.artil4,1);
    iVar3 = BuildObject("svtank",2,(this->field18_0xac)._s_0.artil1);
    (this->field18_0xac)._s_0.escort_tank = iVar3;
    SetObjectiveName((this->field18_0xac)._s_0.nav1,"Drop Zone");
    Defend((this->field18_0xac)._s_0.escort_tank,1);
    fVar7 = Get_Time();
    (this->field17_0x7c)._s_0.first_wave_time = fVar7 + 5.0;
    fVar7 = Get_Time();
    (this->field17_0x7c)._s_0.next_wave_time = fVar7 + 300.0;
    fVar7 = Get_Time();
    (this->field16_0x40)._s_0.start_done = true;
    (this->field17_0x7c)._s_0.artil_move_time = fVar7 + 900.0;
  }
  bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo1);
  if (((!bVar2) && (iVar3 = GetScrap(2), 0x96 < iVar3)) &&
     ((this->field16_0x40)._s_0.silo1_lost == false)) {
    SetScrap(2,0x96);
    (this->field16_0x40)._s_0.silo1_lost = true;
  }
  bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo2);
  if (((!bVar2) && (iVar3 = GetScrap(2), 0x96 < iVar3)) &&
     ((this->field16_0x40)._s_0.silo1_lost == false)) {
    SetScrap(2,0x96);
    (this->field16_0x40)._s_0.silo1_lost = true;
  }
  bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo3);
  if (((!bVar2) && (iVar3 = GetScrap(2), 0x96 < iVar3)) &&
     ((this->field16_0x40)._s_0.silo1_lost == false)) {
    SetScrap(2,0x96);
    (this->field16_0x40)._s_0.silo1_lost = true;
  }
  bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo4);
  if (((!bVar2) && (iVar3 = GetScrap(2), 0x96 < iVar3)) &&
     ((this->field16_0x40)._s_0.silo1_lost == false)) {
    SetScrap(2,0x96);
    (this->field16_0x40)._s_0.silo1_lost = true;
  }
  bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo1);
  if (((!bVar2) && (bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo2), !bVar2)) &&
     ((iVar3 = GetScrap(2), 100 < iVar3 && ((this->field16_0x40)._s_0.silo2_lost == false)))) {
    SetScrap(2,100);
    (this->field16_0x40)._s_0.silo2_lost = true;
  }
  bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo1);
  if (((!bVar2) && (bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo3), !bVar2)) &&
     ((iVar3 = GetScrap(2), 100 < iVar3 && ((this->field16_0x40)._s_0.silo2_lost == false)))) {
    SetScrap(2,100);
    (this->field16_0x40)._s_0.silo2_lost = true;
  }
  bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo1);
  if ((((!bVar2) && (bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo4), !bVar2)) &&
      (iVar3 = GetScrap(2), 100 < iVar3)) && ((this->field16_0x40)._s_0.silo2_lost == false)) {
    SetScrap(2,100);
    (this->field16_0x40)._s_0.silo2_lost = true;
  }
  bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo2);
  if (((!bVar2) && (bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo3), !bVar2)) &&
     ((iVar3 = GetScrap(2), 100 < iVar3 && ((this->field16_0x40)._s_0.silo2_lost == false)))) {
    SetScrap(2,100);
    (this->field16_0x40)._s_0.silo2_lost = true;
  }
  bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo2);
  if (((!bVar2) && (bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo4), !bVar2)) &&
     ((iVar3 = GetScrap(2), 100 < iVar3 && ((this->field16_0x40)._s_0.silo2_lost == false)))) {
    SetScrap(2,100);
    (this->field16_0x40)._s_0.silo2_lost = true;
  }
  bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo3);
  if ((((!bVar2) && (bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo4), !bVar2)) &&
      (iVar3 = GetScrap(2), 100 < iVar3)) && ((this->field16_0x40)._s_0.silo2_lost == false)) {
    SetScrap(2,100);
    (this->field16_0x40)._s_0.silo2_lost = true;
  }
  bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo1);
  if (((!bVar2) && (bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo2), !bVar2)) &&
     ((bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo3), !bVar2 &&
      ((iVar3 = GetScrap(2), 0x32 < iVar3 && ((this->field16_0x40)._s_0.silo3_lost == false)))))) {
    SetScrap(2,0x32);
    (this->field16_0x40)._s_0.silo3_lost = true;
  }
  bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo1);
  if ((((!bVar2) && (bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo2), !bVar2)) &&
      (bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo4), !bVar2)) &&
     ((iVar3 = GetScrap(2), 0x32 < iVar3 && ((this->field16_0x40)._s_0.silo3_lost == false)))) {
    SetScrap(2,0x32);
    (this->field16_0x40)._s_0.silo3_lost = true;
  }
  bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo1);
  if (((!bVar2) && (bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo3), !bVar2)) &&
     ((bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo4), !bVar2 &&
      ((iVar3 = GetScrap(2), 0x32 < iVar3 && ((this->field16_0x40)._s_0.silo3_lost == false)))))) {
    SetScrap(2,0x32);
    (this->field16_0x40)._s_0.silo3_lost = true;
  }
  bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo2);
  if ((((!bVar2) && (bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo3), !bVar2)) &&
      (bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo4), !bVar2)) &&
     ((iVar3 = GetScrap(2), 0x32 < iVar3 && ((this->field16_0x40)._s_0.silo3_lost == false)))) {
    SetScrap(2,0x32);
    (this->field16_0x40)._s_0.silo3_lost = true;
  }
  bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo1);
  if (((!bVar2) && (bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo2), !bVar2)) &&
     ((bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo3), !bVar2 &&
      (((bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccasilo4), !bVar2 &&
        (iVar3 = GetScrap(2), 0 < iVar3)) && ((this->field16_0x40)._s_0.silos_gone == false)))))) {
    (this->field16_0x40)._s_0.silos_gone = true;
    SetScrap(2,0);
  }
  if ((this->field16_0x40)._s_0.start_done == false) {
LAB_00436fd7:
    if ((this->field16_0x40)._s_0.turret_move != false) goto LAB_00436fe1;
  }
  else {
    if ((this->field16_0x40)._s_0.turret_move == false) {
      Retreat((this->field18_0xac)._s_0.turret1,"turret_path1",1);
      Retreat((this->field18_0xac)._s_0.turret2,"turret_path1",1);
      Defend((this->field18_0xac)._s_0.turret3,1);
      Defend((this->field18_0xac)._s_0.turret4,1);
      Retreat((this->field18_0xac)._s_0.turret5,"turret_path2",1);
      Retreat((this->field18_0xac)._s_0.turret6,"turret_path2",1);
      Goto((this->field18_0xac)._s_0.ccaslf,"slf_path",1);
      fVar7 = Get_Time();
      (this->field16_0x40)._s_0.turret_move = true;
      (this->field17_0x7c)._s_0.turret_move_time = fVar7 + 120.0;
      goto LAB_00436fd7;
    }
LAB_00436fe1:
    fVar7 = Get_Time();
    if (((this->field17_0x7c)._s_0.turret_move_time < fVar7) &&
       ((this->field16_0x40)._s_0.silo_defend == false)) {
      fVar7 = Get_Time();
      piVar6 = &(this->field18_0xac)._s_0.ccasilo1;
      iVar3 = *piVar6;
      (this->field17_0x7c)._s_0.turret_move_time = fVar7 + 3.0;
      fVar7 = GetDistance((this->field18_0xac)._s_0.turret5,iVar3);
      if ((fVar7 < 60.0) &&
         (fVar7 = GetDistance((this->field18_0xac)._s_0.turret6,*piVar6), fVar7 < 60.0)) {
        Defend((this->field18_0xac)._s_0.turret5,1);
        Defend((this->field18_0xac)._s_0.turret6,1);
        (this->field16_0x40)._s_0.silo_defend = true;
      }
    }
    if ((this->field16_0x40)._s_0.turret_move != false) {
      fVar7 = Get_Time();
      if ((((this->field17_0x7c)._s_0.turret_move_time < fVar7) &&
          ((this->field16_0x40)._s_0.turret1_set == false)) &&
         (fVar7 = GetDistance((this->field18_0xac)._s_0.turret1,
                              (this->field18_0xac)._s_0.key_geyser1), fVar7 < 100.0)) {
        Goto((this->field18_0xac)._s_0.turret1,(this->field18_0xac)._s_0.key_geyser1,1);
        (this->field16_0x40)._s_0.turret1_set = true;
      }
      if (((((this->field16_0x40)._s_0.turret_move != false) &&
           (fVar7 = Get_Time(), (this->field17_0x7c)._s_0.turret_move_time < fVar7)) &&
          ((this->field16_0x40)._s_0.turret2_set == false)) &&
         (fVar7 = GetDistance((this->field18_0xac)._s_0.turret2,
                              (this->field18_0xac)._s_0.key_geyser1), fVar7 < 100.0)) {
        Goto((this->field18_0xac)._s_0.turret2,(this->field18_0xac)._s_0.key_geyser2,1);
        (this->field16_0x40)._s_0.turret2_set = true;
      }
    }
  }
  if (((this->field16_0x40)._s_0.start_done == false) ||
     (fVar7 = Get_Time(), fVar7 <= (this->field17_0x7c)._s_0.first_wave_time)) {
LAB_00437194:
    if ((this->field16_0x40)._s_0.first_wave != false) goto LAB_0043719a;
  }
  else {
    if ((this->field16_0x40)._s_0.first_wave == false) {
      Attack((this->field18_0xac)._s_0.tank3,(this->field18_0xac)._s_0.nsdfrecycle,1);
      Attack((this->field18_0xac)._s_0.tank4,(this->field18_0xac)._s_0.nsdfrecycle,1);
      Attack((this->field18_0xac)._s_0.fighter5,(this->field18_0xac)._s_0.nsdfrecycle,1);
      Attack((this->field18_0xac)._s_0.fighter6,(this->field18_0xac)._s_0.nsdfrecycle,1);
      fVar7 = Get_Time();
      (this->field16_0x40)._s_0.first_wave = true;
      (this->field17_0x7c)._s_0.second_wave_time = fVar7 + 5.0;
      goto LAB_00437194;
    }
LAB_0043719a:
    fVar7 = Get_Time();
    if (((this->field17_0x7c)._s_0.second_wave_time < fVar7) &&
       ((this->field16_0x40)._s_0.second_wave == false)) {
      Goto((this->field18_0xac)._s_0.fighter1,"choke_point1",1);
      Goto((this->field18_0xac)._s_0.fighter2,"choke_point1",1);
      Goto((this->field18_0xac)._s_0.fighter3,(this->field18_0xac)._s_0.key_geyser1,1);
      Goto((this->field18_0xac)._s_0.fighter4,(this->field18_0xac)._s_0.key_geyser2,1);
      fVar7 = Get_Time();
      (this->field16_0x40)._s_0.second_wave = true;
      (this->field17_0x7c)._s_0.set_aip_time = fVar7 + 60.0;
    }
  }
  if (((((this->field16_0x40)._s_0.set_aip == false) &&
       (fVar7 = Get_Time(), (this->field17_0x7c)._s_0.set_aip_time < fVar7)) &&
      ((this->field16_0x40)._s_0.hold_aip == false)) &&
     ((this->field16_0x40)._s_0.muf_attacked == false)) {
    fVar7 = Get_Time();
    (this->field17_0x7c)._s_0.set_aip_time = fVar7 + 240.0;
    SetAIP("misn13.aip",2);
  }
  piVar6 = &(this->field18_0xac)._s_0.tank1;
  bVar2 = IsAlive(piVar6);
  if ((bVar2) && ((this->field16_0x40)._s_0.assign_tank1 == false)) {
    Follow(*piVar6,(this->field18_0xac)._s_0.ccamuf,1);
    (this->field16_0x40)._s_0.assign_tank1 = true;
  }
  piVar6 = &(this->field18_0xac)._s_0.tank2;
  bVar2 = IsAlive(piVar6);
  if ((bVar2) && ((this->field16_0x40)._s_0.assign_tank2 == false)) {
    Follow(*piVar6,(this->field18_0xac)._s_0.ccamuf,1);
    (this->field16_0x40)._s_0.assign_tank2 = true;
  }
  piVar6 = &(this->field18_0xac)._s_0.tank3;
  bVar2 = IsAlive(piVar6);
  if ((bVar2) && ((this->field16_0x40)._s_0.assign_tank3 == false)) {
    Follow(*piVar6,(this->field18_0xac)._s_0.center,1);
    (this->field16_0x40)._s_0.assign_tank3 = true;
  }
  piVar6 = &(this->field18_0xac)._s_0.tank4;
  bVar2 = IsAlive(piVar6);
  if ((bVar2) && ((this->field16_0x40)._s_0.assign_tank4 == false)) {
    Follow(*piVar6,(this->field18_0xac)._s_0.center,1);
    (this->field16_0x40)._s_0.assign_tank4 = true;
  }
  piVar6 = &(this->field18_0xac)._s_0.guntower1;
  bVar2 = IsAlive(piVar6);
  if ((bVar2) || (bVar2 = IsAlive(&(this->field18_0xac)._s_0.controltower), bVar2)) {
    if ((this->field16_0x40)._s_0.make_bomber == false) {
      if ((this->field16_0x40)._s_0.muf_attacked == false) {
        SetAIP("misn13a.aip",2);
        (this->field16_0x40)._s_0.hold_aip = true;
        (this->field16_0x40)._s_0.make_bomber = true;
      }
      goto LAB_00437343;
    }
LAB_0043734d:
    if ((this->field16_0x40)._s_0.bomber_attack == false) {
      piVar5 = &(this->field18_0xac)._s_0.sv4;
      bVar2 = IsAlive(piVar5);
      if ((bVar2) && ((this->field16_0x40)._s_0.sv4_wait == false)) {
        bVar2 = IsAlive(piVar6);
        if (bVar2) {
          Attack(*piVar5,*piVar6,1);
        }
        else {
          piVar4 = &(this->field18_0xac)._s_0.nsdfmuf;
          bVar2 = IsAlive(piVar4);
          if (bVar2) {
LAB_004373a8:
            Attack(*piVar5,*piVar4,1);
          }
          else {
            piVar4 = &(this->field18_0xac)._s_0.controltower;
            bVar2 = IsAlive(piVar4);
            if (bVar2) goto LAB_004373a8;
          }
          piVar4 = &(this->field18_0xac)._s_0.tank5;
          bVar2 = IsAlive(piVar4);
          if (bVar2) {
            Follow(*piVar4,*piVar5,1);
          }
        }
        (this->field16_0x40)._s_0.sv4_wait = true;
      }
      piVar5 = &(this->field18_0xac)._s_0.sv1;
      bVar2 = IsAlive(piVar5);
      if ((bVar2) && ((this->field16_0x40)._s_0.sv1_wait == false)) {
        piVar4 = &(this->field18_0xac)._s_0.controltower;
        bVar2 = IsAlive(piVar4);
        if (bVar2) {
LAB_00437425:
          iVar3 = *piVar4;
LAB_0043742a:
          Attack(*piVar5,iVar3,1);
        }
        else {
          bVar2 = IsAlive(piVar6);
          if (bVar2) {
            iVar3 = *piVar6;
            goto LAB_0043742a;
          }
          piVar4 = &(this->field18_0xac)._s_0.nsdfmuf;
          bVar2 = IsAlive(piVar4);
          if (bVar2) goto LAB_00437425;
        }
        piVar4 = &(this->field18_0xac)._s_0.tank6;
        bVar2 = IsAlive(piVar4);
        if (bVar2) {
          Follow(*piVar4,*piVar5,1);
        }
        (this->field16_0x40)._s_0.sv1_wait = true;
      }
      piVar5 = &(this->field18_0xac)._s_0.sv3;
      bVar2 = IsAlive(piVar5);
      if ((bVar2) && ((this->field16_0x40)._s_0.sv3_wait == false)) {
        bVar2 = IsAlive(piVar6);
        if (bVar2) {
          Attack(*piVar5,*piVar6,1);
        }
        else {
          piVar4 = &(this->field18_0xac)._s_0.nsdfmuf;
          bVar2 = IsAlive(piVar4);
          if (bVar2) {
LAB_004374a9:
            Attack(*piVar5,*piVar4,1);
          }
          else {
            piVar4 = &(this->field18_0xac)._s_0.controltower;
            bVar2 = IsAlive(piVar4);
            if (bVar2) goto LAB_004374a9;
          }
          piVar4 = &(this->field18_0xac)._s_0.tank7;
          bVar2 = IsAlive(piVar4);
          if (bVar2) {
            Follow(*piVar4,*piVar5,1);
          }
        }
        (this->field16_0x40)._s_0.sv3_wait = true;
      }
    }
  }
  else {
LAB_00437343:
    if ((this->field16_0x40)._s_0.make_bomber != false) goto LAB_0043734d;
  }
  if ((((this->field16_0x40)._s_0.sv1_wait == false) ||
      ((this->field16_0x40)._s_0.sv3_wait == false)) ||
     ((this->field16_0x40)._s_0.sv4_wait == false)) {
LAB_004374fc:
    if ((this->field16_0x40)._s_0.bomber_attack != false) goto LAB_00437506;
  }
  else {
    if ((this->field16_0x40)._s_0.bomber_attack == false) {
      (this->field16_0x40)._s_0.hold_aip = false;
      (this->field16_0x40)._s_0.bomber_attack = true;
      goto LAB_004374fc;
    }
LAB_00437506:
    bVar2 = IsAlive(piVar6);
    if ((!bVar2) && ((this->field16_0x40)._s_0.new_target == false)) {
      piVar6 = &(this->field18_0xac)._s_0.controltower;
      bVar2 = IsAlive(piVar6);
      if (!bVar2) {
        piVar6 = &(this->field18_0xac)._s_0.nsdfmuf;
        bVar2 = IsAlive(piVar6);
        if (!bVar2) goto LAB_004375a4;
      }
      piVar5 = &(this->field18_0xac)._s_0.sv1;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        Attack(*piVar5,*piVar6,1);
      }
      piVar5 = &(this->field18_0xac)._s_0.sv3;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        Attack(*piVar5,*piVar6,1);
      }
      piVar5 = &(this->field18_0xac)._s_0.sv4;
      bVar2 = IsAlive(piVar5);
      if (bVar2) {
        Attack(*piVar5,*piVar6,1);
      }
      (this->field16_0x40)._s_0.new_target = true;
    }
  }
LAB_004375a4:
  piVar6 = &(this->field18_0xac)._s_0.ccasilo1;
  bVar2 = IsAlive(piVar6);
  if (((bVar2) && ((this->field16_0x40)._s_0.silos_attacked == false)) &&
     (fVar7 = GetHealth(*piVar6), fVar7 < 0.95)) {
    fVar7 = Get_Time();
    (this->field16_0x40)._s_0.silos_attacked = true;
    (this->field17_0x7c)._s_0.new_orders_time = fVar7 + 2.0;
  }
  piVar6 = &(this->field18_0xac)._s_0.ccasilo2;
  bVar2 = IsAlive(piVar6);
  if (((bVar2) && ((this->field16_0x40)._s_0.silos_attacked == false)) &&
     (fVar7 = GetHealth(*piVar6), fVar7 < 0.95)) {
    fVar7 = Get_Time();
    (this->field16_0x40)._s_0.silos_attacked = true;
    (this->field17_0x7c)._s_0.new_orders_time = fVar7 + 2.0;
  }
  piVar6 = &(this->field18_0xac)._s_0.ccasilo3;
  bVar2 = IsAlive(piVar6);
  if (((bVar2) && ((this->field16_0x40)._s_0.silos_attacked == false)) &&
     (fVar7 = GetHealth(*piVar6), fVar7 < 0.95)) {
    fVar7 = Get_Time();
    (this->field16_0x40)._s_0.silos_attacked = true;
    (this->field17_0x7c)._s_0.new_orders_time = fVar7 + 2.0;
  }
  piVar6 = &(this->field18_0xac)._s_0.ccasilo4;
  bVar2 = IsAlive(piVar6);
  if (bVar2) {
    if ((this->field16_0x40)._s_0.silos_attacked == false) {
      fVar7 = GetHealth(*piVar6);
      if (fVar7 < 0.95) {
        fVar7 = Get_Time();
        (this->field16_0x40)._s_0.silos_attacked = true;
        (this->field17_0x7c)._s_0.new_orders_time = fVar7 + 2.0;
      }
      goto LAB_004376a8;
    }
LAB_004376b2:
    fVar7 = Get_Time();
    if ((this->field17_0x7c)._s_0.new_orders_time < fVar7) {
      fVar7 = Get_Time();
      piVar6 = &(this->field18_0xac)._s_0.tank1;
      (this->field17_0x7c)._s_0.new_orders_time = fVar7 + 120.0;
      bVar2 = IsAlive(piVar6);
      if (bVar2) {
        Goto(*piVar6,"silo_spot",1);
      }
      piVar6 = &(this->field18_0xac)._s_0.tank2;
      bVar2 = IsAlive(piVar6);
      if (bVar2) {
        Goto(*piVar6,"silo_spot",1);
      }
      piVar6 = &(this->field18_0xac)._s_0.tank3;
      bVar2 = IsAlive(piVar6);
      if (bVar2) {
        Goto(*piVar6,"silo_spot",1);
      }
      piVar6 = &(this->field18_0xac)._s_0.tank4;
      bVar2 = IsAlive(piVar6);
      if (bVar2) {
        Goto(*piVar6,"silo_spot",1);
      }
      piVar6 = &(this->field18_0xac)._s_0.turret1;
      bVar2 = IsAlive(piVar6);
      if (bVar2) {
        Goto(*piVar6,"silo_spot",1);
      }
      piVar6 = &(this->field18_0xac)._s_0.turret2;
      bVar2 = IsAlive(piVar6);
      if (bVar2) {
        Goto(*piVar6,"silo_spot",1);
      }
      piVar6 = &(this->field18_0xac)._s_0.turret5;
      bVar2 = IsAlive(piVar6);
      if (bVar2) {
        Goto(*piVar6,"silo_spot",1);
      }
      piVar6 = &(this->field18_0xac)._s_0.turret6;
      bVar2 = IsAlive(piVar6);
      if (bVar2) {
        Goto(*piVar6,"silo_spot",1);
      }
      piVar6 = &(this->field18_0xac)._s_0.tank4;
      bVar2 = IsAlive(piVar6);
      if (bVar2) {
        Goto(*piVar6,"silo_spot",1);
      }
      if (((this->field16_0x40)._s_0.bomber_reload != false) ||
         ((this->field16_0x40)._s_0.bomber_attack != false)) {
        piVar6 = &(this->field18_0xac)._s_0.sv1;
        bVar2 = IsAlive(piVar6);
        if (bVar2) {
          Goto(*piVar6,"silo_spot",1);
        }
        piVar6 = &(this->field18_0xac)._s_0.sv3;
        bVar2 = IsAlive(piVar6);
        if (bVar2) {
          Goto(*piVar6,"silo_spot",1);
        }
        piVar6 = &(this->field18_0xac)._s_0.sv4;
        bVar2 = IsAlive(piVar6);
        if (bVar2) {
          Goto(*piVar6,"silo_spot",1);
        }
      }
    }
  }
  else {
LAB_004376a8:
    if ((this->field16_0x40)._s_0.silos_attacked != false) goto LAB_004376b2;
  }
  piVar6 = &(this->field18_0xac)._s_0.ccamuf;
  bVar2 = IsAlive(piVar6);
  if ((((bVar2) && ((this->field16_0x40)._s_0.muf_attacked == false)) &&
      (fVar7 = GetHealth(*piVar6), fVar7 < 0.9)) && ((this->field16_0x40)._s_0.muf_safe == false)) {
    piVar5 = &(this->field18_0xac)._s_0.turret1;
    bVar2 = IsAlive(piVar5);
    if (bVar2) {
      Goto(*piVar5,*piVar6,1);
    }
    piVar5 = &(this->field18_0xac)._s_0.turret2;
    bVar2 = IsAlive(piVar5);
    if (bVar2) {
      Goto(*piVar5,*piVar6,1);
    }
    piVar5 = &(this->field18_0xac)._s_0.turret5;
    bVar2 = IsAlive(piVar5);
    if (bVar2) {
      Goto(*piVar5,*piVar6,1);
    }
    piVar5 = &(this->field18_0xac)._s_0.turret6;
    bVar2 = IsAlive(piVar5);
    if (bVar2) {
      Goto(*piVar5,*piVar6,1);
    }
    AddScrap(2,0x28);
    fVar7 = Get_Time();
    (this->field17_0x7c)._s_0.safe_time_check = fVar7 + 120.0;
    SetAIP("misn13c.aip",2);
    (this->field16_0x40)._s_0.muf_attacked = true;
  }
  if ((this->field16_0x40)._s_0.muf_attacked != false) {
    piVar5 = &(this->field18_0xac)._s_0.turret1;
    bVar2 = IsAlive(piVar5);
    if (((bVar2) && ((this->field16_0x40)._s_0.turret1_muf == false)) &&
       (fVar7 = GetDistance(*piVar5,*piVar6), fVar7 < 60.0)) {
      Defend(*piVar5,1);
      (this->field16_0x40)._s_0.turret1_muf = true;
    }
    if ((this->field16_0x40)._s_0.muf_attacked != false) {
      piVar5 = &(this->field18_0xac)._s_0.turret2;
      bVar2 = IsAlive(piVar5);
      if (((bVar2) && ((this->field16_0x40)._s_0.turret2_muf == false)) &&
         (fVar7 = GetDistance(*piVar5,*piVar6), fVar7 < 60.0)) {
        Defend(*piVar5,1);
        (this->field16_0x40)._s_0.turret2_muf = true;
      }
      if ((this->field16_0x40)._s_0.muf_attacked != false) {
        piVar5 = &(this->field18_0xac)._s_0.turret5;
        bVar2 = IsAlive(piVar5);
        if (((bVar2) && ((this->field16_0x40)._s_0.turret5_muf == false)) &&
           (fVar7 = GetDistance(*piVar5,*piVar6), fVar7 < 60.0)) {
          Defend(*piVar5,1);
          (this->field16_0x40)._s_0.turret5_muf = true;
        }
        if ((this->field16_0x40)._s_0.muf_attacked != false) {
          piVar5 = &(this->field18_0xac)._s_0.turret6;
          bVar2 = IsAlive(piVar5);
          if (((bVar2) && ((this->field16_0x40)._s_0.turret6_muf == false)) &&
             (fVar7 = GetDistance(*piVar5,*piVar6), fVar7 < 60.0)) {
            Defend(*piVar5,1);
            (this->field16_0x40)._s_0.turret6_muf = true;
          }
        }
      }
    }
  }
  if ((((this->field16_0x40)._s_0.game_over == false) &&
      ((this->field16_0x40)._s_0.muf_attacked != false)) &&
     ((fVar7 = Get_Time(), (this->field17_0x7c)._s_0.safe_time_check < fVar7 &&
      ((this->field16_0x40)._s_0.muf_safe == false)))) {
    Get_Time();
    iVar3 = CountUnitsNearObject(*piVar6,400.0,1,(char *)0x0);
    (this->field19_0x1e0)._s_0.check = iVar3;
    if ((float)iVar3 < 2.0) {
      (this->field16_0x40)._s_0.muf_safe = true;
      (this->field16_0x40)._s_0.muf_attacked = false;
    }
  }
  if ((((this->field18_0xac)._s_0.choke_bridged == 0) &&
      (bVar2 = IsAlive(&(this->field18_0xac)._s_0.turret3), !bVar2)) &&
     (bVar2 = IsAlive(&(this->field18_0xac)._s_0.turret4), !bVar2)) {
    (this->field18_0xac)._s_0.choke_bridged = 1;
  }
  fVar7 = Get_Time();
  if (fVar7 <= (this->field17_0x7c)._s_0.artil_move_time) {
LAB_00437bcc:
    if ((this->field16_0x40)._s_0.artil_move != false) goto LAB_00437bd6;
  }
  else {
    if ((this->field16_0x40)._s_0.artil_move == false) {
      fVar7 = Get_Time();
      piVar6 = &(this->field18_0xac)._s_0.artil1;
      (this->field17_0x7c)._s_0.artil_move_time = fVar7 + 10.0;
      bVar2 = IsAlive(piVar6);
      if (bVar2) {
        Retreat(*piVar6,"artil_path1",1);
      }
      piVar6 = &(this->field18_0xac)._s_0.artil2;
      bVar2 = IsAlive(piVar6);
      if (bVar2) {
        Retreat(*piVar6,"artil_path1",1);
      }
      piVar6 = &(this->field18_0xac)._s_0.artil3;
      bVar2 = IsAlive(piVar6);
      if (bVar2) {
        Retreat(*piVar6,"artil_path1",1);
      }
      piVar6 = &(this->field18_0xac)._s_0.artil4;
      bVar2 = IsAlive(piVar6);
      if (bVar2) {
        Retreat(*piVar6,"artil_path1",1);
      }
      piVar6 = &(this->field18_0xac)._s_0.escort_tank;
      bVar2 = IsAlive(piVar6);
      if (bVar2) {
        Retreat(*piVar6,"artil_path1",1);
      }
      (this->field16_0x40)._s_0.artil_move = true;
      goto LAB_00437bcc;
    }
LAB_00437bd6:
    fVar7 = Get_Time();
    if (((this->field17_0x7c)._s_0.artil_move_time < fVar7) &&
       ((this->field16_0x40)._s_0.artil_move2 == false)) {
      fVar7 = Get_Time();
      iVar3 = (this->field18_0xac)._s_0.split_geyser;
      piVar6 = &(this->field18_0xac)._s_0.artil4;
      iVar1 = *piVar6;
      (this->field17_0x7c)._s_0.artil_move_time = fVar7 + 5.0;
      fVar7 = GetDistance(iVar1,iVar3);
      if (fVar7 < 20.0) {
        piVar5 = &(this->field18_0xac)._s_0.artil1;
        bVar2 = IsAlive(piVar5);
        if (bVar2) {
          Goto(*piVar5,"artil_point1",1);
          SetIndependence(*piVar5,1);
        }
        piVar4 = &(this->field18_0xac)._s_0.artil2;
        bVar2 = IsAlive(piVar4);
        if (bVar2) {
          Goto(*piVar4,"artil_point2",1);
          SetIndependence(*piVar4,1);
        }
        piVar4 = &(this->field18_0xac)._s_0.artil3;
        bVar2 = IsAlive(piVar4);
        if (bVar2) {
          Goto(*piVar4,"artil_point3",1);
          SetIndependence(*piVar4,1);
        }
        bVar2 = IsAlive(piVar6);
        if (bVar2) {
          Goto(*piVar6,"artil_point4",1);
          SetIndependence(*piVar6,1);
        }
        piVar6 = &(this->field18_0xac)._s_0.escort_tank;
        bVar2 = IsAlive(piVar6);
        if (bVar2) {
          Follow(*piVar6,*piVar5,1);
        }
        fVar7 = Get_Time();
        (this->field16_0x40)._s_0.artil_move2 = true;
        (this->field17_0x7c)._s_0.artil_set_time = fVar7 + 120.0;
      }
    }
  }
  fVar7 = Get_Time();
  if ((fVar7 <= (this->field17_0x7c)._s_0.artil_set_time) ||
     ((this->field16_0x40)._s_0.artil_set != false)) goto LAB_00437dd4;
  piVar6 = &(this->field18_0xac)._s_0.artil1;
  bVar2 = IsAlive(piVar6);
  if (bVar2) {
    piVar5 = &(this->field18_0xac)._s_0.avscav1;
    bVar2 = IsAlive(piVar5);
    if (!bVar2) {
      piVar5 = &(this->field18_0xac)._s_0.avscav2;
      bVar2 = IsAlive(piVar5);
      if (!bVar2) {
        piVar5 = &(this->field18_0xac)._s_0.avscav3;
        bVar2 = IsAlive(piVar5);
        if (!bVar2) goto LAB_00437d7d;
      }
    }
    Attack(*piVar6,*piVar5,1);
  }
LAB_00437d7d:
  piVar6 = &(this->field18_0xac)._s_0.artil2;
  bVar2 = IsAlive(piVar6);
  if (bVar2) {
    piVar5 = &(this->field18_0xac)._s_0.avscav3;
    bVar2 = IsAlive(piVar5);
    if (!bVar2) {
      piVar5 = &(this->field18_0xac)._s_0.avscav2;
      bVar2 = IsAlive(piVar5);
      if (!bVar2) {
        piVar5 = &(this->field18_0xac)._s_0.avscav1;
        bVar2 = IsAlive(piVar5);
        if (!bVar2) goto LAB_00437dd0;
      }
    }
    Attack(*piVar6,*piVar5,1);
  }
LAB_00437dd0:
  (this->field16_0x40)._s_0.artil_set = true;
LAB_00437dd4:
  piVar6 = &(this->field18_0xac)._s_0.artil1;
  bVar2 = IsAlive(piVar6);
  if ((((!bVar2) && (bVar2 = IsAlive(&(this->field18_0xac)._s_0.artil2), !bVar2)) &&
      (bVar2 = IsAlive(&(this->field18_0xac)._s_0.artil3), !bVar2)) &&
     (bVar2 = IsAlive(&(this->field18_0xac)._s_0.artil4), !bVar2)) {
    (this->field16_0x40)._s_0.artil_lost = true;
  }
  if (((this->field16_0x40)._s_0.artil_move2 != false) &&
     ((this->field16_0x40)._s_0.artil_message == false)) {
    piVar5 = &(this->field18_0xac)._s_0.nsdfrecycle;
    bVar2 = IsAlive(piVar5);
    if (bVar2) {
      iVar3 = GetWhoShotMe(*piVar5);
      (this->field19_0x1e0)._s_0.shot_by = iVar3;
      if ((iVar3 != 0) &&
         (((*piVar6 == iVar3 || ((this->field18_0xac)._s_0.artil2 == iVar3)) ||
          (((this->field18_0xac)._s_0.artil3 == iVar3 || ((this->field18_0xac)._s_0.artil4 == iVar3)
           ))))) {
        AudioMessage("misn1302.wav");
        (this->field16_0x40)._s_0.artil_message = true;
      }
    }
    piVar5 = &(this->field18_0xac)._s_0.nsdfmuf;
    bVar2 = IsAlive(piVar5);
    if ((bVar2) && ((this->field16_0x40)._s_0.artil_message == false)) {
      iVar3 = GetWhoShotMe(*piVar5);
      (this->field19_0x1e0)._s_0.shot_by = iVar3;
      if ((iVar3 != 0) &&
         ((((*piVar6 == iVar3 || ((this->field18_0xac)._s_0.artil2 == iVar3)) ||
           ((this->field18_0xac)._s_0.artil3 == iVar3)) ||
          ((this->field18_0xac)._s_0.artil4 == iVar3)))) {
        AudioMessage("misn1302.wav");
        (this->field16_0x40)._s_0.artil_message = true;
      }
    }
    piVar5 = &(this->field18_0xac)._s_0.avscav1;
    bVar2 = IsAlive(piVar5);
    if ((bVar2) && ((this->field16_0x40)._s_0.artil_message == false)) {
      iVar3 = GetWhoShotMe(*piVar5);
      (this->field19_0x1e0)._s_0.shot_by = iVar3;
      if ((iVar3 != 0) &&
         (((*piVar6 == iVar3 || ((this->field18_0xac)._s_0.artil2 == iVar3)) ||
          (((this->field18_0xac)._s_0.artil3 == iVar3 || ((this->field18_0xac)._s_0.artil4 == iVar3)
           ))))) {
        AudioMessage("misn1302.wav");
        (this->field16_0x40)._s_0.artil_message = true;
      }
    }
    piVar5 = &(this->field18_0xac)._s_0.avscav2;
    bVar2 = IsAlive(piVar5);
    if ((bVar2) && ((this->field16_0x40)._s_0.artil_message == false)) {
      iVar3 = GetWhoShotMe(*piVar5);
      (this->field19_0x1e0)._s_0.shot_by = iVar3;
      if ((iVar3 != 0) &&
         ((((*piVar6 == iVar3 || ((this->field18_0xac)._s_0.artil2 == iVar3)) ||
           ((this->field18_0xac)._s_0.artil3 == iVar3)) ||
          ((this->field18_0xac)._s_0.artil4 == iVar3)))) {
        AudioMessage("misn1302.wav");
        (this->field16_0x40)._s_0.artil_message = true;
      }
    }
    piVar5 = &(this->field18_0xac)._s_0.avscav3;
    bVar2 = IsAlive(piVar5);
    if ((bVar2) && ((this->field16_0x40)._s_0.artil_message == false)) {
      iVar3 = GetWhoShotMe(*piVar5);
      (this->field19_0x1e0)._s_0.shot_by = iVar3;
      if ((iVar3 != 0) &&
         (((*piVar6 == iVar3 || ((this->field18_0xac)._s_0.artil2 == iVar3)) ||
          (((this->field18_0xac)._s_0.artil3 == iVar3 || ((this->field18_0xac)._s_0.artil4 == iVar3)
           ))))) {
        AudioMessage("misn1302.wav");
        (this->field16_0x40)._s_0.artil_message = true;
      }
    }
  }
  fVar7 = Get_Time();
  if (((this->field17_0x7c)._s_0.scrap_check < fVar7) &&
     ((this->field16_0x40)._s_0.scav_swap == false)) {
    fVar7 = Get_Time();
    (this->field17_0x7c)._s_0.scrap_check = fVar7 + 60.0;
    iVar3 = GetScrap(2);
    (this->field19_0x1e0)._s_0.scrap = iVar3;
    if (iVar3 < 0x28) {
      iVar3 = (this->field18_0xac)._s_0.svscav1;
      if (iVar3 != 0) {
        iVar3 = BuildObject("svscav",2,iVar3);
        (this->field18_0xac)._s_0.svscav5 = iVar3;
        RemoveObject((this->field18_0xac)._s_0.svscav1);
        Goto((this->field18_0xac)._s_0.svscav5,(this->field18_0xac)._s_0.center_geyser,1);
      }
      iVar3 = (this->field18_0xac)._s_0.svscav2;
      if (iVar3 != 0) {
        iVar3 = BuildObject("svscav",2,iVar3);
        (this->field18_0xac)._s_0.svscav6 = iVar3;
        RemoveObject((this->field18_0xac)._s_0.svscav2);
        Goto((this->field18_0xac)._s_0.svscav6,(this->field18_0xac)._s_0.center_geyser,1);
      }
      iVar3 = (this->field18_0xac)._s_0.svscav3;
      if (iVar3 != 0) {
        iVar3 = BuildObject("svscav",2,iVar3);
        (this->field18_0xac)._s_0.svscav7 = iVar3;
        RemoveObject((this->field18_0xac)._s_0.svscav3);
        Goto((this->field18_0xac)._s_0.svscav7,(this->field18_0xac)._s_0.center_geyser,1);
      }
      iVar3 = (this->field18_0xac)._s_0.svscav4;
      if (iVar3 != 0) {
        iVar3 = BuildObject("svscav",2,iVar3);
        (this->field18_0xac)._s_0.svscav8 = iVar3;
        RemoveObject((this->field18_0xac)._s_0.svscav4);
        Goto((this->field18_0xac)._s_0.svscav8,(this->field18_0xac)._s_0.center_geyser,1);
      }
      (this->field16_0x40)._s_0.scav_swap = true;
    }
  }
  bVar2 = IsAlive(&(this->field18_0xac)._s_0.nsdfrecycle);
  if ((!bVar2) && ((this->field16_0x40)._s_0.game_over == false)) {
    AudioMessage("misn1304.wav");
    pcVar8 = "misn13f1.des";
    fVar7 = Get_Time();
    FailMission(fVar7 + 15.0,pcVar8);
    (this->field16_0x40)._s_0.game_over = true;
  }
  bVar2 = IsAlive(&(this->field18_0xac)._s_0.ccamuf);
  if ((!bVar2) && ((this->field16_0x40)._s_0.game_over == false)) {
    AudioMessage("misn1303.wav");
    pcVar8 = "misn13w1.des";
    fVar7 = Get_Time();
    SucceedMission(fVar7 + 15.0,pcVar8);
    (this->field16_0x40)._s_0.game_over = true;
  }
  return;
}
