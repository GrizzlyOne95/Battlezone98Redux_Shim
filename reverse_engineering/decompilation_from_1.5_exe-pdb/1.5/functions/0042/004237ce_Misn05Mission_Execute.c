/*
 * Entry: 004237ce
 * Name: Misn05Mission::Execute
 * Namespace: Misn05Mission
 * Signature: void Execute(Misn05Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn05Mission::Execute(Misn05Mission *this)

{
  int *piVar1;
  int *piVar2;
  Misn05Mission_u_300 *pMVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  tagAIP_struct *ptVar7;
  bool bVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  AiCommand AVar12;
  float *pfVar13;
  float fVar14;
  char *pcVar15;
  int local_4;
  
  if ((this->field16_0x40)._s_0.game_start == false) {
    SetScrap(1,0x14);
    SetScrap(2,0x14);
    iVar9 = GetHandle("oblema110_i76building");
    (this->field18_0x12c)._s_0.lemnos = iVar9;
    iVar9 = GetHandle("svrecy-1_recycler");
    (this->field18_0x12c)._s_0.svrec = iVar9;
    iVar9 = GetHandle("avrecy-1_recycler");
    (this->field18_0x12c)._s_0.avrec = iVar9;
    SetAIP("misn05.aip",2);
    AudioMessage("misn0501.wav");
    (this->field16_0x40)._s_0.game_start = true;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine1 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine2 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine3 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine4 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine5 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine6 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine7 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine8 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine9 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine10 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine11 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine12 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine13 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine14 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine15 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine16 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine17 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine18 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine19 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine20 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine21 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine22 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine23 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.mine24 = fVar14 + 2.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.randomwave = fVar14 + 1.0;
    iVar9 = GetHandle("cam1");
    (this->field18_0x12c)._s_0.cam1 = iVar9;
    SetObjectiveName(iVar9,"Volcano");
    (this->field16_0x40)._s_0.newobjective = true;
  }
  iVar9 = GetPlayerHandle();
  (this->field18_0x12c)._s_0.player = iVar9;
  if (((AI_map != (tag_strategy_map *)0x0) && (AI_map->team[2] != (tag_team *)0x0)) &&
     (ptVar7 = AI_map->team[2]->AIP, ptVar7 != (tagAIP_struct *)0x0)) {
    ptVar7->escort_priority = 0;
    ptVar7->min_escort_force = 100;
    ptVar7->max_escort_force = 100;
    ptVar7->perimeter_priority = 0;
    ptVar7->min_perimeter_force = 100;
    ptVar7->max_perimeter_force = 100;
    ptVar7->defend_buildings_priority = 0;
    ptVar7->min_building_defense_force = 100;
    ptVar7->max_building_defense_force = 100;
  }
  if ((this->field16_0x40)._s_0.newobjective == true) {
    InfoDisplay::ClearObjectives(&infoDisplay);
    if ((this->field16_0x40)._s_0.missionwon == true) {
      InfoDisplay::AddObjective(&infoDisplay,"misn0502.otf",DisplayInterface::colorGreen,8.0);
    }
    if ((this->field16_0x40)._s_0.neworders == true) {
      if ((this->field16_0x40)._s_0.missionwon == false) {
        InfoDisplay::AddObjective(&infoDisplay,"misn0502.otf",DisplayInterface::colorWhite,8.0);
      }
      if ((this->field16_0x40)._s_0.neworders == true) {
        InfoDisplay::AddObjective(&infoDisplay,"misn0503.otf",DisplayInterface::colorGreen,8.0);
      }
    }
    if ((this->field16_0x40)._s_0.reconfactory == true) {
      if ((this->field16_0x40)._s_0.neworders == false) {
        InfoDisplay::AddObjective(&infoDisplay,"misn0503.otf",DisplayInterface::colorWhite,8.0);
      }
      if ((this->field16_0x40)._s_0.reconfactory == true) {
        InfoDisplay::AddObjective(&infoDisplay,"misn0501.otf",DisplayInterface::colorGreen,8.0);
      }
    }
    if ((this->field16_0x40)._s_0.reconfactory == false) {
      InfoDisplay::AddObjective(&infoDisplay,"misn0501.otf",DisplayInterface::colorWhite,8.0);
    }
    (this->field16_0x40)._s_0.newobjective = false;
  }
  if ((this->field16_0x40)._s_0.reconed == false) {
    if (((this->field16_0x40)._s_0.needtospawn == true) &&
       (fVar14 = Get_Time(), (this->field17_0x88)._s_0.randomwave < fVar14)) {
      piVar1 = &(this->field18_0x12c)._s_0.svrec;
      bVar8 = IsAlive(piVar1);
      if (bVar8) {
        iVar9 = BuildObject("svfigh",2,*piVar1);
        (this->field18_0x12c)._s_0.rand1 = iVar9;
        iVar9 = BuildObject("svfigh",2,*piVar1);
        piVar1 = &(this->field18_0x12c)._s_0.avrec;
        (this->field18_0x12c)._s_0.rand2 = iVar9;
        Attack((this->field18_0x12c)._s_0.rand1,*piVar1,1);
        Attack((this->field18_0x12c)._s_0.rand2,*piVar1,1);
        SetIndependence((this->field18_0x12c)._s_0.rand1,1);
        SetIndependence((this->field18_0x12c)._s_0.rand2,1);
        (this->field16_0x40)._s_0.needtospawn = false;
      }
    }
    if ((((this->field16_0x40)._s_0.needtospawn == false) &&
        (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.rand1), !bVar8)) &&
       (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.rand2), !bVar8)) {
      (this->field16_0x40)._s_0.needtospawn = true;
    }
  }
  if ((this->field16_0x40)._s_0.mine1built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine1 < fVar14) {
      iVar9 = GetNearestVehicle("path_1",1);
      fVar14 = GetDistance(iVar9,"path_1",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_1",0);
        (this->field18_0x12c)._s_0.MINE1 = iVar9;
        (this->field16_0x40)._s_0.mine1built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_1",1);
    fVar14 = GetDistance(iVar9,"path_1",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE1;
      (this->field16_0x40)._s_0.mine1built = false;
      (this->field17_0x88)._s_0.mine1 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine2built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine2 < fVar14) {
      iVar9 = GetNearestVehicle("path_2",1);
      fVar14 = GetDistance(iVar9,"path_2",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_2",0);
        (this->field18_0x12c)._s_0.MINE2 = iVar9;
        (this->field16_0x40)._s_0.mine2built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_2",1);
    fVar14 = GetDistance(iVar9,"path_2",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE2;
      (this->field16_0x40)._s_0.mine2built = false;
      (this->field17_0x88)._s_0.mine2 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine3built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine3 < fVar14) {
      iVar9 = GetNearestVehicle("path_3",1);
      fVar14 = GetDistance(iVar9,"path_3",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_3",0);
        (this->field18_0x12c)._s_0.MINE3 = iVar9;
        (this->field16_0x40)._s_0.mine3built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_3",1);
    fVar14 = GetDistance(iVar9,"path_3",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE3;
      (this->field16_0x40)._s_0.mine3built = false;
      (this->field17_0x88)._s_0.mine3 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine4built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine4 < fVar14) {
      iVar9 = GetNearestVehicle("path_4",1);
      fVar14 = GetDistance(iVar9,"path_4",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_4",0);
        (this->field18_0x12c)._s_0.MINE4 = iVar9;
        (this->field16_0x40)._s_0.mine4built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_4",1);
    fVar14 = GetDistance(iVar9,"path_4",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE4;
      (this->field16_0x40)._s_0.mine4built = false;
      (this->field17_0x88)._s_0.mine4 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine5built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine5 < fVar14) {
      iVar9 = GetNearestVehicle("path_5",1);
      fVar14 = GetDistance(iVar9,"path_5",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_5",0);
        (this->field18_0x12c)._s_0.MINE5 = iVar9;
        (this->field16_0x40)._s_0.mine5built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_5",1);
    fVar14 = GetDistance(iVar9,"path_5",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE5;
      (this->field16_0x40)._s_0.mine5built = false;
      (this->field17_0x88)._s_0.mine5 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine6built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine6 < fVar14) {
      iVar9 = GetNearestVehicle("path_6",1);
      fVar14 = GetDistance(iVar9,"path_6",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_6",0);
        (this->field18_0x12c)._s_0.MINE6 = iVar9;
        (this->field16_0x40)._s_0.mine6built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_6",1);
    fVar14 = GetDistance(iVar9,"path_6",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE6;
      (this->field16_0x40)._s_0.mine6built = false;
      (this->field17_0x88)._s_0.mine6 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine7built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine7 < fVar14) {
      iVar9 = GetNearestVehicle("path_7",1);
      fVar14 = GetDistance(iVar9,"path_7",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_7",0);
        (this->field18_0x12c)._s_0.MINE7 = iVar9;
        (this->field16_0x40)._s_0.mine7built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_7",1);
    fVar14 = GetDistance(iVar9,"path_7",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE7;
      (this->field16_0x40)._s_0.mine7built = false;
      (this->field17_0x88)._s_0.mine7 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine8built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine8 < fVar14) {
      iVar9 = GetNearestVehicle("path_8",1);
      fVar14 = GetDistance(iVar9,"path_8",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_8",0);
        (this->field18_0x12c)._s_0.MINE8 = iVar9;
        (this->field16_0x40)._s_0.mine8built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_8",1);
    fVar14 = GetDistance(iVar9,"path_8",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE8;
      (this->field16_0x40)._s_0.mine8built = false;
      (this->field17_0x88)._s_0.mine8 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine9built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine9 < fVar14) {
      iVar9 = GetNearestVehicle("path_9",1);
      fVar14 = GetDistance(iVar9,"path_9",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_9",0);
        (this->field18_0x12c)._s_0.MINE9 = iVar9;
        (this->field16_0x40)._s_0.mine9built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_9",1);
    fVar14 = GetDistance(iVar9,"path_9",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE9;
      (this->field16_0x40)._s_0.mine9built = false;
      (this->field17_0x88)._s_0.mine9 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine10built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine10 < fVar14) {
      iVar9 = GetNearestVehicle("path_10",1);
      fVar14 = GetDistance(iVar9,"path_10",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_10",0);
        (this->field18_0x12c)._s_0.MINE10 = iVar9;
        (this->field16_0x40)._s_0.mine10built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_10",1);
    fVar14 = GetDistance(iVar9,"path_10",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE10;
      (this->field16_0x40)._s_0.mine10built = false;
      (this->field17_0x88)._s_0.mine10 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine11built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine11 < fVar14) {
      iVar9 = GetNearestVehicle("path_11",1);
      fVar14 = GetDistance(iVar9,"path_11",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_11",0);
        (this->field18_0x12c)._s_0.MINE11 = iVar9;
        (this->field16_0x40)._s_0.mine11built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_11",1);
    fVar14 = GetDistance(iVar9,"path_11",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE11;
      (this->field16_0x40)._s_0.mine11built = false;
      (this->field17_0x88)._s_0.mine11 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine12built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine12 < fVar14) {
      iVar9 = GetNearestVehicle("path_12",1);
      fVar14 = GetDistance(iVar9,"path_12",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_12",0);
        (this->field18_0x12c)._s_0.MINE12 = iVar9;
        (this->field16_0x40)._s_0.mine12built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_12",1);
    fVar14 = GetDistance(iVar9,"path_12",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE12;
      (this->field16_0x40)._s_0.mine12built = false;
      (this->field17_0x88)._s_0.mine12 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine13built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine13 < fVar14) {
      iVar9 = GetNearestVehicle("path_13",1);
      fVar14 = GetDistance(iVar9,"path_13",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_13",0);
        (this->field18_0x12c)._s_0.MINE13 = iVar9;
        (this->field16_0x40)._s_0.mine13built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_13",1);
    fVar14 = GetDistance(iVar9,"path_13",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE13;
      (this->field16_0x40)._s_0.mine13built = false;
      (this->field17_0x88)._s_0.mine13 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine14built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine14 < fVar14) {
      iVar9 = GetNearestVehicle("path_14",1);
      fVar14 = GetDistance(iVar9,"path_14",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_14",0);
        (this->field18_0x12c)._s_0.MINE14 = iVar9;
        (this->field16_0x40)._s_0.mine14built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_14",1);
    fVar14 = GetDistance(iVar9,"path_14",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE14;
      (this->field16_0x40)._s_0.mine14built = false;
      (this->field17_0x88)._s_0.mine14 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine15built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine15 < fVar14) {
      iVar9 = GetNearestVehicle("path_15",1);
      fVar14 = GetDistance(iVar9,"path_15",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_15",0);
        (this->field18_0x12c)._s_0.MINE15 = iVar9;
        (this->field16_0x40)._s_0.mine15built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_15",1);
    fVar14 = GetDistance(iVar9,"path_15",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE15;
      (this->field16_0x40)._s_0.mine15built = false;
      (this->field17_0x88)._s_0.mine15 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine16built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine16 < fVar14) {
      iVar9 = GetNearestVehicle("path_16",1);
      fVar14 = GetDistance(iVar9,"path_16",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_16",0);
        (this->field18_0x12c)._s_0.MINE16 = iVar9;
        (this->field16_0x40)._s_0.mine16built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_16",1);
    fVar14 = GetDistance(iVar9,"path_16",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE16;
      (this->field16_0x40)._s_0.mine16built = false;
      (this->field17_0x88)._s_0.mine16 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine17built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine17 < fVar14) {
      iVar9 = GetNearestVehicle("path_17",1);
      fVar14 = GetDistance(iVar9,"path_17",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_17",0);
        (this->field18_0x12c)._s_0.MINE17 = iVar9;
        (this->field16_0x40)._s_0.mine17built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_17",1);
    fVar14 = GetDistance(iVar9,"path_17",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE17;
      (this->field16_0x40)._s_0.mine17built = false;
      (this->field17_0x88)._s_0.mine17 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine18built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine18 < fVar14) {
      iVar9 = GetNearestVehicle("path_18",1);
      fVar14 = GetDistance(iVar9,"path_18",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_18",0);
        (this->field18_0x12c)._s_0.MINE18 = iVar9;
        (this->field16_0x40)._s_0.mine18built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_18",1);
    fVar14 = GetDistance(iVar9,"path_18",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE18;
      (this->field16_0x40)._s_0.mine18built = false;
      (this->field17_0x88)._s_0.mine18 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine19built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine19 < fVar14) {
      iVar9 = GetNearestVehicle("path_19",1);
      fVar14 = GetDistance(iVar9,"path_19",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_19",0);
        (this->field18_0x12c)._s_0.MINE19 = iVar9;
        (this->field16_0x40)._s_0.mine19built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_19",1);
    fVar14 = GetDistance(iVar9,"path_19",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE19;
      (this->field16_0x40)._s_0.mine19built = false;
      (this->field17_0x88)._s_0.mine19 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine20built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine20 < fVar14) {
      iVar9 = GetNearestVehicle("path_20",1);
      fVar14 = GetDistance(iVar9,"path_20",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_20",0);
        (this->field18_0x12c)._s_0.MINE20 = iVar9;
        (this->field16_0x40)._s_0.mine20built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_20",1);
    fVar14 = GetDistance(iVar9,"path_20",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE20;
      (this->field16_0x40)._s_0.mine20built = false;
      (this->field17_0x88)._s_0.mine20 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine21built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine21 < fVar14) {
      iVar9 = GetNearestVehicle("path_21",1);
      fVar14 = GetDistance(iVar9,"path_21",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_21",0);
        (this->field18_0x12c)._s_0.MINE21 = iVar9;
        (this->field16_0x40)._s_0.mine21built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_21",1);
    fVar14 = GetDistance(iVar9,"path_21",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE21;
      (this->field16_0x40)._s_0.mine21built = false;
      (this->field17_0x88)._s_0.mine21 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine22built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine22 < fVar14) {
      iVar9 = GetNearestVehicle("path_22",1);
      fVar14 = GetDistance(iVar9,"path_22",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_22",0);
        (this->field18_0x12c)._s_0.MINE22 = iVar9;
        (this->field16_0x40)._s_0.mine22built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_22",1);
    fVar14 = GetDistance(iVar9,"path_22",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE22;
      (this->field16_0x40)._s_0.mine22built = false;
      (this->field17_0x88)._s_0.mine22 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine23built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine23 < fVar14) {
      iVar9 = GetNearestVehicle("path_23",1);
      fVar14 = GetDistance(iVar9,"path_23",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_23",0);
        (this->field18_0x12c)._s_0.MINE23 = iVar9;
        (this->field16_0x40)._s_0.mine23built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_23",1);
    fVar14 = GetDistance(iVar9,"path_23",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE23;
      (this->field16_0x40)._s_0.mine23built = false;
      (this->field17_0x88)._s_0.mine23 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if ((this->field16_0x40)._s_0.mine24built == false) {
    fVar14 = Get_Time();
    if ((this->field17_0x88)._s_0.mine24 < fVar14) {
      iVar9 = GetNearestVehicle("path_24",1);
      fVar14 = GetDistance(iVar9,"path_24",0);
      if (fVar14 < 400.0) {
        iVar9 = BuildObject("boltmine",2,"path_24",0);
        (this->field18_0x12c)._s_0.MINE24 = iVar9;
        (this->field16_0x40)._s_0.mine24built = true;
      }
    }
  }
  else {
    iVar9 = GetNearestVehicle("path_24",1);
    fVar14 = GetDistance(iVar9,"path_24",0);
    if (400.0 < fVar14) {
      fVar14 = Get_Time();
      iVar9 = (this->field18_0x12c)._s_0.MINE24;
      (this->field16_0x40)._s_0.mine24built = false;
      (this->field17_0x88)._s_0.mine24 = fVar14 + 3.0;
      RemoveObject(iVar9);
    }
  }
  if (((this->field16_0x40)._s_0.notfound == true) && ((this->field16_0x40)._s_0.shuffle == false))
  {
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.sendTime[0] = fVar14 + 10.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.sendTime[1] = fVar14 + 90.0;
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.sendTime[2] = fVar14 + 130.0;
    fVar14 = Get_Time();
    local_4 = 10;
    (this->field17_0x88)._s_0.sendTime[3] = fVar14 + 190.0;
    do {
      uVar10 = rand();
      uVar10 = uVar10 & 0x80000003;
      if ((int)uVar10 < 0) {
        uVar10 = (uVar10 - 1 | 0xfffffffc) + 1;
      }
      uVar11 = rand();
      uVar11 = uVar11 & 0x80000003;
      if ((int)uVar11 < 0) {
        uVar11 = (uVar11 - 1 | 0xfffffffc) + 1;
      }
      local_4 = local_4 + -1;
      puVar4 = (undefined4 *)((int)&this->field17_0x88 + uVar10 * 4 + 4);
      uVar6 = *puVar4;
      puVar5 = (undefined4 *)((int)&this->field17_0x88 + uVar11 * 4 + 4);
      *puVar4 = *puVar5;
      *puVar5 = uVar6;
    } while (local_4 != 0);
    pfVar13 = (this->field17_0x88)._s_0.sendTime;
    iVar9 = 4;
    do {
      printf("%f\n",(double)*pfVar13);
      pfVar13 = pfVar13 + 1;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
    (this->field16_0x40)._s_0.shuffle = true;
  }
  fVar14 = Get_Time();
  if (((this->field17_0x88)._s_0.sendTime[0] < fVar14) &&
     ((this->field16_0x40)._s_0.sent1Done == false)) {
    iVar9 = BuildObject("svfigh",2,(this->field18_0x12c)._s_0.svrec);
    (this->field18_0x12c)._s_0.w1u1 = iVar9;
    iVar9 = BuildObject("svfigh",2,(this->field18_0x12c)._s_0.svrec);
    (this->field18_0x12c)._s_0.w1u2 = iVar9;
    iVar9 = BuildObject("svturr",2,(this->field18_0x12c)._s_0.svrec);
    (this->field18_0x12c)._s_0.w1u3 = iVar9;
    iVar9 = BuildObject("svturr",2,(this->field18_0x12c)._s_0.svrec);
    (this->field18_0x12c)._s_0.w1u4 = iVar9;
    (this->field16_0x40)._s_0.sent1Done = true;
    Follow((this->field18_0x12c)._s_0.w1u1,(this->field18_0x12c)._s_0.w1u3,1);
    Follow((this->field18_0x12c)._s_0.w1u2,(this->field18_0x12c)._s_0.w1u4,1);
    SetIndependence((this->field18_0x12c)._s_0.w1u1,1);
    SetIndependence((this->field18_0x12c)._s_0.w1u2,1);
    Goto((this->field18_0x12c)._s_0.w1u3,"defendrim2",1);
    Goto((this->field18_0x12c)._s_0.w1u4,"defendrim1",1);
    (this->field16_0x40)._s_0.check1 = true;
    (this->field16_0x40)._s_0.check2 = true;
    (this->field16_0x40)._s_0.check3 = true;
    (this->field16_0x40)._s_0.check4 = true;
  }
  piVar1 = &(this->field18_0x12c)._s_0.w1u3;
  bVar8 = IsAlive(piVar1);
  if (((bVar8) && ((this->field16_0x40)._s_0.check1 == false)) &&
     (AVar12 = GetCurrentCommand(*piVar1), AVar12 == CMD_NONE)) {
    Defend(*piVar1,1000);
  }
  if (((this->field16_0x40)._s_0.check1 == true) &&
     ((bVar8 = IsAlive(piVar1), !bVar8 ||
      (fVar14 = GetDistance(*piVar1,"defendrim2",0), fVar14 < 20.0)))) {
    bVar8 = IsAlive(piVar1);
    if (bVar8) {
      Stop(*piVar1,1000);
    }
    Patrol((this->field18_0x12c)._s_0.w1u1,"attackpatrol1",2);
    (this->field16_0x40)._s_0.check1 = false;
  }
  piVar1 = &(this->field18_0x12c)._s_0.w1u4;
  bVar8 = IsAlive(piVar1);
  if (((bVar8) && ((this->field16_0x40)._s_0.check2 == false)) &&
     (AVar12 = GetCurrentCommand(*piVar1), AVar12 == CMD_NONE)) {
    Defend(*piVar1,1000);
  }
  if (((this->field16_0x40)._s_0.check2 == true) &&
     ((bVar8 = IsAlive(piVar1), !bVar8 ||
      (fVar14 = GetDistance(*piVar1,"defendrim1",0), fVar14 < 20.0)))) {
    bVar8 = IsAlive(piVar1);
    if (bVar8) {
      Stop(*piVar1,1000);
    }
    Patrol((this->field18_0x12c)._s_0.w1u2,"attackpatrol1",2);
    (this->field16_0x40)._s_0.check2 = false;
  }
  piVar1 = &(this->field18_0x12c)._s_0.w2u3;
  bVar8 = IsAlive(piVar1);
  if (((bVar8) && ((this->field16_0x40)._s_0.check3 == false)) &&
     (AVar12 = GetCurrentCommand(*piVar1), AVar12 == CMD_NONE)) {
    Defend(*piVar1,1000);
  }
  if (((this->field16_0x40)._s_0.check3 == true) &&
     ((bVar8 = IsAlive(piVar1), !bVar8 ||
      (fVar14 = GetDistance(*piVar1,"defendrim3",0), fVar14 < 20.0)))) {
    bVar8 = IsAlive(piVar1);
    if (bVar8) {
      Stop(*piVar1,1000);
    }
    Patrol((this->field18_0x12c)._s_0.w2u1,"attackpatrol1",2);
    (this->field16_0x40)._s_0.check3 = false;
  }
  piVar1 = &(this->field18_0x12c)._s_0.w2u4;
  bVar8 = IsAlive(piVar1);
  if (((bVar8) && ((this->field16_0x40)._s_0.check4 == false)) &&
     (AVar12 = GetCurrentCommand(*piVar1), AVar12 == CMD_NONE)) {
    Defend(*piVar1,1000);
  }
  if (((this->field16_0x40)._s_0.check4 == true) &&
     ((bVar8 = IsAlive(piVar1), !bVar8 ||
      (fVar14 = GetDistance(*piVar1,"defendrim4",0), fVar14 < 20.0)))) {
    bVar8 = IsAlive(piVar1);
    if (bVar8) {
      Stop(*piVar1,1000);
    }
    Patrol((this->field18_0x12c)._s_0.w2u2,"attackpatrol1",2);
    (this->field16_0x40)._s_0.check4 = false;
  }
  fVar14 = Get_Time();
  if (((this->field17_0x88)._s_0.sendTime[1] < fVar14) &&
     ((this->field16_0x40)._s_0.sent2Done == false)) {
    iVar9 = BuildObject("svtank",2,(this->field18_0x12c)._s_0.svrec);
    (this->field18_0x12c)._s_0.w2u1 = iVar9;
    iVar9 = BuildObject("svtank",2,(this->field18_0x12c)._s_0.svrec);
    (this->field18_0x12c)._s_0.w2u2 = iVar9;
    iVar9 = BuildObject("svturr",2,(this->field18_0x12c)._s_0.svrec);
    piVar2 = &(this->field18_0x12c)._s_0.w2u3;
    *piVar2 = iVar9;
    iVar9 = BuildObject("svturr",2,(this->field18_0x12c)._s_0.svrec);
    *piVar1 = iVar9;
    (this->field16_0x40)._s_0.sent2Done = true;
    Follow((this->field18_0x12c)._s_0.w2u1,*piVar2,1);
    Follow((this->field18_0x12c)._s_0.w2u2,*piVar1,1);
    SetIndependence((this->field18_0x12c)._s_0.w2u1,1);
    SetIndependence((this->field18_0x12c)._s_0.w2u2,1);
    Goto(*piVar2,"defendrim3",1);
    Goto(*piVar1,"defendrim4",1);
  }
  fVar14 = Get_Time();
  if (((this->field17_0x88)._s_0.sendTime[2] < fVar14) &&
     ((this->field16_0x40)._s_0.sent3Done == false)) {
    iVar9 = BuildObject("svfigh",2,(this->field18_0x12c)._s_0.svrec);
    (this->field18_0x12c)._s_0.w3u3 = iVar9;
    iVar9 = BuildObject("svfigh",2,(this->field18_0x12c)._s_0.svrec);
    (this->field18_0x12c)._s_0.w3u4 = iVar9;
    (this->field16_0x40)._s_0.sent3Done = true;
    Patrol((this->field18_0x12c)._s_0.w3u3,"attackpatrol1",2);
    Patrol((this->field18_0x12c)._s_0.w3u4,"attackpatrol1",2);
  }
  fVar14 = Get_Time();
  if (((this->field17_0x88)._s_0.sendTime[3] < fVar14) &&
     ((this->field16_0x40)._s_0.sent4Done == false)) {
    iVar9 = BuildObject("svfigh",2,(this->field18_0x12c)._s_0.svrec);
    (this->field18_0x12c)._s_0.w4u3 = iVar9;
    iVar9 = BuildObject("svfigh",2,(this->field18_0x12c)._s_0.svrec);
    (this->field18_0x12c)._s_0.w4u4 = iVar9;
    (this->field16_0x40)._s_0.sent4Done = true;
    Patrol((this->field18_0x12c)._s_0.w4u3,"attackpatrol1",2);
    Patrol((this->field18_0x12c)._s_0.w4u4,"attackpatrol1",2);
  }
  if ((this->field16_0x40)._s_0.reconfactory == false) {
    fVar14 = GetDistance((this->field18_0x12c)._s_0.player,(this->field18_0x12c)._s_0.lemnos);
    if ((fVar14 < 600.0) && ((this->field16_0x40)._s_0.notfound == false)) {
      AudioMessage("misn0502.wav");
      (this->field16_0x40)._s_0.notfound = true;
    }
    if (((this->field16_0x40)._s_0.reconfactory == false) &&
       (fVar14 = GetDistance((this->field18_0x12c)._s_0.player,(this->field18_0x12c)._s_0.lemnos),
       fVar14 < 230.0)) {
      AudioMessage("misn0503.wav");
      AudioMessage("misn0504.wav");
      (this->field16_0x40)._s_0.reconfactory = true;
      (this->field16_0x40)._s_0.newobjective = true;
      fVar14 = Get_Time();
      (this->field17_0x88)._s_0.start = fVar14 + 90.0;
    }
  }
  if ((((this->field16_0x40)._s_0.reconfactory == true) &&
      ((this->field16_0x40)._s_0.reconed == false)) &&
     ((bVar8 = IsInfo("oblema"), bVar8 ||
      (fVar14 = Get_Time(), (this->field17_0x88)._s_0.start < fVar14)))) {
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.readtime = fVar14 + 5.0;
    (this->field16_0x40)._s_0.reconed = true;
  }
  if (((this->field16_0x40)._s_0.neworders == false) &&
     (fVar14 = Get_Time(), (this->field17_0x88)._s_0.readtime < fVar14)) {
    (this->field16_0x40)._s_0.neworders = true;
    AudioMessage("misn0506.wav");
    SetObjectiveOn((this->field18_0x12c)._s_0.lemnos);
    (this->field16_0x40)._s_0.newobjective = true;
  }
  piVar2 = &(this->field18_0x12c)._s_0.svrec;
  bVar8 = IsAlive(piVar2);
  if (((bVar8) && ((this->field16_0x40)._s_0.basewave == false)) &&
     ((this->field16_0x40)._s_0.reconfactory == true)) {
    iVar9 = BuildObject("svtank",2,*piVar2);
    (this->field18_0x12c)._s_0.wBu1 = iVar9;
    iVar9 = BuildObject("svfigh",2,*piVar2);
    (this->field18_0x12c)._s_0.wBu2 = iVar9;
    iVar9 = BuildObject("svfigh",2,*piVar2);
    (this->field18_0x12c)._s_0.wBu3 = iVar9;
    Attack((this->field18_0x12c)._s_0.wBu1,(this->field18_0x12c)._s_0.avrec,1);
    Attack((this->field18_0x12c)._s_0.wBu2,(this->field18_0x12c)._s_0.avrec,1);
    Attack((this->field18_0x12c)._s_0.wBu3,(this->field18_0x12c)._s_0.avrec,1);
    SetIndependence((this->field18_0x12c)._s_0.wBu1,1);
    SetIndependence((this->field18_0x12c)._s_0.wBu2,1);
    SetIndependence((this->field18_0x12c)._s_0.wBu3,1);
    (this->field16_0x40)._s_0.basewave = true;
  }
  if ((this->field16_0x40)._s_0.sent1Done != false) {
    IsAlive(&(this->field18_0x12c)._s_0.w1u1);
    IsAlive(&(this->field18_0x12c)._s_0.w1u2);
    IsAlive(&(this->field18_0x12c)._s_0.w1u3);
    IsAlive(&(this->field18_0x12c)._s_0.w1u4);
  }
  if ((this->field16_0x40)._s_0.sent2Done != false) {
    IsAlive(&(this->field18_0x12c)._s_0.w2u1);
    IsAlive(&(this->field18_0x12c)._s_0.w2u2);
    IsAlive(&(this->field18_0x12c)._s_0.w2u3);
    IsAlive(piVar1);
  }
  if ((this->field16_0x40)._s_0.sent3Done != false) {
    IsAlive(&(this->field18_0x12c)._s_0.w3u1);
    IsAlive(&(this->field18_0x12c)._s_0.w3u2);
    IsAlive(&(this->field18_0x12c)._s_0.w3u3);
    IsAlive(&(this->field18_0x12c)._s_0.w3u4);
  }
  if ((this->field16_0x40)._s_0.sent4Done != false) {
    IsAlive(&(this->field18_0x12c)._s_0.w4u1);
    IsAlive(&(this->field18_0x12c)._s_0.w4u2);
    IsAlive(&(this->field18_0x12c)._s_0.w4u3);
    IsAlive(&(this->field18_0x12c)._s_0.w4u4);
  }
  if ((((((this->field16_0x40)._s_0.sent1Done == true) &&
        ((this->field16_0x40)._s_0.sent2Done == true)) &&
       (((this->field16_0x40)._s_0.sent3Done == true &&
        (((this->field16_0x40)._s_0.sent4Done == true &&
         (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w1u1), !bVar8)))))) &&
      (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w1u2), !bVar8)) &&
     (((((((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w1u3), !bVar8 &&
           (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w1u4), !bVar8)) &&
          (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w2u1), !bVar8)) &&
         ((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w2u2), !bVar8 &&
          (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w2u3), !bVar8)))) &&
        (bVar8 = IsAlive(piVar1), !bVar8)) &&
       ((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w3u1), !bVar8 &&
        (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w3u2), !bVar8)))) &&
      (((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w3u3), !bVar8 &&
        (((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w3u4), !bVar8 &&
          (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w4u1), !bVar8)) &&
         (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w4u2), !bVar8)))) &&
       (((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w4u3), !bVar8 &&
         (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w4u4), !bVar8)) &&
        ((this->field16_0x40)._s_0.attacktimeset == false)))))))) {
    AudioMessage("misn0507.wav");
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.platoonhere = fVar14 + 45.0;
    (this->field16_0x40)._s_0.attacktimeset = true;
    (this->field16_0x40)._s_0.go = true;
  }
  bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw1);
  if ((((bVar8) || (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw2), bVar8)) ||
      ((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw3), bVar8 ||
       (((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw4), bVar8 ||
         (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw5), bVar8)) ||
        (fVar14 = Get_Time(), (this->field17_0x88)._s_0.platoonhere <= fVar14)))))) ||
     (((this->field16_0x40)._s_0.go != true || (bVar8 = IsAlive(piVar2), !bVar8))))
  goto LAB_00425821;
  AudioMessage("misn0508.wav");
  AudioMessage("misn0509.wav");
  uVar10 = rand();
  uVar10 = uVar10 & 0x80000003;
  if ((int)uVar10 < 0) {
    uVar10 = (uVar10 - 1 | 0xfffffffc) + 1;
  }
  (this->field19_0x234)._s_0.attacksent = uVar10;
  (this->field16_0x40)._s_0.attackstatement = false;
  iVar9 = (this->field19_0x234)._s_0.attacksent;
  if (iVar9 == 0) {
    iVar9 = BuildObject("svhraz",2,*piVar2);
    (this->field18_0x12c)._s_0.aw1 = iVar9;
    iVar9 = BuildObject("svhraz",2,*piVar2);
    (this->field18_0x12c)._s_0.aw2 = iVar9;
    iVar9 = BuildObject("svhraz",2,*piVar2);
    (this->field18_0x12c)._s_0.aw3 = iVar9;
    Goto((this->field18_0x12c)._s_0.aw1,"destroy1",1);
    Goto((this->field18_0x12c)._s_0.aw2,"destroy1",1);
    pcVar15 = "destroy1";
LAB_004257be:
    Goto((this->field18_0x12c)._s_0.aw3,pcVar15,1);
  }
  else {
    if (iVar9 == 1) {
      iVar9 = BuildObject("svhraz",2,*piVar2);
      (this->field18_0x12c)._s_0.aw1 = iVar9;
      iVar9 = BuildObject("svhraz",2,*piVar2);
      (this->field18_0x12c)._s_0.aw2 = iVar9;
      iVar9 = BuildObject("svhraz",2,*piVar2);
      (this->field18_0x12c)._s_0.aw3 = iVar9;
      Goto((this->field18_0x12c)._s_0.aw1,"destroy2",1);
      Goto((this->field18_0x12c)._s_0.aw2,"destroy2",1);
      pcVar15 = "destroy2";
      goto LAB_004257be;
    }
    if (iVar9 == 2) {
      iVar9 = BuildObject("svhraz",2,*piVar2);
      (this->field18_0x12c)._s_0.aw1 = iVar9;
      iVar9 = BuildObject("svhraz",2,*piVar2);
      (this->field18_0x12c)._s_0.aw2 = iVar9;
      iVar9 = BuildObject("svhraz",2,*piVar2);
      (this->field18_0x12c)._s_0.aw3 = iVar9;
      Goto((this->field18_0x12c)._s_0.aw1,"destroy3",1);
      Goto((this->field18_0x12c)._s_0.aw2,"destroy3",1);
      pcVar15 = "destroy3";
      goto LAB_004257be;
    }
    if (iVar9 == 3) {
      iVar9 = BuildObject("svhraz",2,*piVar2);
      (this->field18_0x12c)._s_0.aw1 = iVar9;
      iVar9 = BuildObject("svhraz",2,*piVar2);
      (this->field18_0x12c)._s_0.aw2 = iVar9;
      iVar9 = BuildObject("svhraz",2,*piVar2);
      (this->field18_0x12c)._s_0.aw3 = iVar9;
      Goto((this->field18_0x12c)._s_0.aw1,"destroy4",1);
      Goto((this->field18_0x12c)._s_0.aw2,"destroy4",1);
      pcVar15 = "destroy4";
      goto LAB_004257be;
    }
  }
  fVar14 = Get_Time();
  (this->field17_0x88)._s_0.bombtime = fVar14 + 10.0;
  (this->field16_0x40)._s_0.attackcmd = false;
  fVar14 = Get_Time();
  (this->field17_0x88)._s_0.aw1t = fVar14 + 10.0;
  fVar14 = Get_Time();
  (this->field17_0x88)._s_0.aw2t = fVar14 + 50.0;
  fVar14 = Get_Time();
  (this->field17_0x88)._s_0.aw3t = fVar14 + 100.0;
  fVar14 = Get_Time();
  (this->field17_0x88)._s_0.aw4t = fVar14 + 140.0;
LAB_00425821:
  if (((this->field16_0x40)._s_0.attackcmd == false) &&
     (fVar14 = Get_Time(), (this->field17_0x88)._s_0.bombtime < fVar14)) {
    piVar1 = &(this->field18_0x12c)._s_0.aw1;
    fVar14 = GetDistance(*piVar1,"dest1",0);
    if ((fVar14 < 30.0) || (fVar14 = GetDistance(*piVar1,"dest2",0), fVar14 < 30.0)) {
      Attack(*piVar1,(this->field18_0x12c)._s_0.lemnos,1);
      SetIndependence(*piVar1,1);
      (this->field16_0x40)._s_0.attackcmd = true;
    }
    fVar14 = GetDistance((this->field18_0x12c)._s_0.aw2,"dest1",0);
    if ((fVar14 < 30.0) ||
       (fVar14 = GetDistance((this->field18_0x12c)._s_0.aw2,"dest2",0), fVar14 < 30.0)) {
      Attack((this->field18_0x12c)._s_0.aw2,(this->field18_0x12c)._s_0.lemnos,1);
      SetIndependence((this->field18_0x12c)._s_0.aw2,1);
      (this->field16_0x40)._s_0.attackcmd = true;
    }
    fVar14 = GetDistance((this->field18_0x12c)._s_0.aw3,"dest1",0);
    if ((fVar14 < 30.0) ||
       (fVar14 = GetDistance((this->field18_0x12c)._s_0.aw3,"dest2",0), fVar14 < 30.0)) {
      Attack((this->field18_0x12c)._s_0.aw3,(this->field18_0x12c)._s_0.lemnos,1);
      SetIndependence((this->field18_0x12c)._s_0.aw3,1);
      (this->field16_0x40)._s_0.attackcmd = true;
    }
    fVar14 = GetDistance((this->field18_0x12c)._s_0.aw4,"dest1",0);
    if ((fVar14 < 30.0) ||
       (fVar14 = GetDistance((this->field18_0x12c)._s_0.aw4,"dest2",0), fVar14 < 30.0)) {
      Attack((this->field18_0x12c)._s_0.aw4,(this->field18_0x12c)._s_0.lemnos,1);
      SetIndependence((this->field18_0x12c)._s_0.aw4,1);
      (this->field16_0x40)._s_0.attackcmd = true;
    }
    fVar14 = GetDistance((this->field18_0x12c)._s_0.aw5,"dest1",0);
    if ((fVar14 < 30.0) ||
       (fVar14 = GetDistance((this->field18_0x12c)._s_0.aw5,"dest2",0), fVar14 < 30.0)) {
      Attack((this->field18_0x12c)._s_0.aw5,(this->field18_0x12c)._s_0.lemnos,1);
      SetIndependence((this->field18_0x12c)._s_0.aw5,1);
      (this->field16_0x40)._s_0.attackcmd = true;
    }
    fVar14 = Get_Time();
    (this->field17_0x88)._s_0.bombtime = fVar14 + 3.0;
  }
  bVar8 = IsAlive(&(this->field18_0x12c)._s_0.avrec);
  if ((!bVar8) && ((this->field16_0x40)._s_0.missionfail == false)) {
    pcVar15 = "misn05l1.des";
    fVar14 = Get_Time();
    FailMission(fVar14 + 15.0,pcVar15);
    AudioMessage("misn0513.wav");
    (this->field16_0x40)._s_0.missionfail = true;
  }
  pMVar3 = &this->field18_0x12c;
  bVar8 = IsAlive(pMVar3->h_array);
  if ((!bVar8) && ((this->field16_0x40)._s_0.missionfail == false)) {
    pcVar15 = "misn05l2.des";
    fVar14 = Get_Time();
    FailMission(fVar14 + 15.0,pcVar15);
    AudioMessage("misn0514.wav");
    (this->field16_0x40)._s_0.missionfail = true;
  }
  fVar14 = GetDistance((this->field18_0x12c)._s_0.aw1,(pMVar3->_s_0).lemnos);
  if (((((fVar14 < 500.0) ||
        (fVar14 = GetDistance((this->field18_0x12c)._s_0.aw2,(pMVar3->_s_0).lemnos), fVar14 < 500.0)
        ) || (fVar14 = GetDistance((this->field18_0x12c)._s_0.aw3,(pMVar3->_s_0).lemnos),
             fVar14 < 500.0)) ||
      ((fVar14 = GetDistance((this->field18_0x12c)._s_0.aw4,(pMVar3->_s_0).lemnos), fVar14 < 500.0
       || (fVar14 = GetDistance((this->field18_0x12c)._s_0.aw5,(pMVar3->_s_0).lemnos),
          fVar14 < 500.0)))) && ((this->field16_0x40)._s_0.attackstatement == false)) {
    AudioMessage("misn0510.wav");
    (this->field16_0x40)._s_0.attackstatement = true;
  }
  fVar14 = Get_Time();
  if ((((this->field17_0x88)._s_0.aw1t < fVar14) && ((this->field16_0x40)._s_0.aw1sent == false)) &&
     (bVar8 = IsAlive(piVar2), bVar8)) {
    iVar9 = BuildObject("svfigh",2,*piVar2);
    (this->field18_0x12c)._s_0.aw2a = iVar9;
    Attack(iVar9,(pMVar3->_s_0).lemnos,1);
    SetIndependence((this->field18_0x12c)._s_0.aw2a,1);
    (this->field16_0x40)._s_0.aw1sent = true;
  }
  fVar14 = Get_Time();
  if ((((this->field17_0x88)._s_0.aw2t < fVar14) && ((this->field16_0x40)._s_0.aw2sent == false)) &&
     (bVar8 = IsAlive(piVar2), bVar8)) {
    iVar9 = BuildObject("svtank",2,*piVar2);
    (this->field18_0x12c)._s_0.aw4a = iVar9;
    Attack(iVar9,(pMVar3->_s_0).lemnos,1);
    SetIndependence((this->field18_0x12c)._s_0.aw4a,1);
    (this->field16_0x40)._s_0.aw2sent = true;
  }
  fVar14 = Get_Time();
  if ((((this->field17_0x88)._s_0.aw3t < fVar14) && ((this->field16_0x40)._s_0.aw3sent == false)) &&
     (bVar8 = IsAlive(piVar2), bVar8)) {
    iVar9 = BuildObject("svfigh",2,*piVar2);
    (this->field18_0x12c)._s_0.aw5a = iVar9;
    iVar9 = BuildObject("svfigh",2,*piVar2);
    (this->field18_0x12c)._s_0.aw6a = iVar9;
    Attack((this->field18_0x12c)._s_0.aw5a,(pMVar3->_s_0).lemnos,1);
    Attack((this->field18_0x12c)._s_0.aw6a,(pMVar3->_s_0).lemnos,1);
    SetIndependence((this->field18_0x12c)._s_0.aw5a,1);
    SetIndependence((this->field18_0x12c)._s_0.aw6a,1);
    (this->field16_0x40)._s_0.aw3sent = true;
  }
  fVar14 = Get_Time();
  if ((((this->field17_0x88)._s_0.aw4t < fVar14) && ((this->field16_0x40)._s_0.aw4sent == false)) &&
     (bVar8 = IsAlive(piVar2), bVar8)) {
    iVar9 = BuildObject("svfigh",2,*piVar2);
    (this->field18_0x12c)._s_0.aw8a = iVar9;
    iVar9 = BuildObject("svtank",2,*piVar2);
    (this->field18_0x12c)._s_0.aw9a = iVar9;
    Attack((this->field18_0x12c)._s_0.aw8a,(pMVar3->_s_0).lemnos,1);
    Attack((this->field18_0x12c)._s_0.aw9a,(pMVar3->_s_0).lemnos,1);
    SetIndependence((this->field18_0x12c)._s_0.aw8a,1);
    SetIndependence((this->field18_0x12c)._s_0.aw9a,1);
    (this->field16_0x40)._s_0.aw4sent = true;
  }
  if ((this->field16_0x40)._s_0.aw1sent == true) {
    bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw1a);
    if (((bVar8) && ((this->field16_0x40)._s_0.aw1aattack == false)) &&
       (fVar14 = GetDistance((this->field18_0x12c)._s_0.aw1a,(pMVar3->_s_0).lemnos), fVar14 < 300.0)
       ) {
      Attack((this->field18_0x12c)._s_0.aw1a,(pMVar3->_s_0).lemnos,1);
      SetIndependence((this->field18_0x12c)._s_0.aw1a,1);
      (this->field16_0x40)._s_0.aw1aattack = true;
    }
    if ((this->field16_0x40)._s_0.aw1sent == true) {
      bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw2a);
      if (((bVar8) && ((this->field16_0x40)._s_0.aw2aattack == false)) &&
         (fVar14 = GetDistance((this->field18_0x12c)._s_0.aw2a,(pMVar3->_s_0).lemnos),
         fVar14 < 300.0)) {
        Attack((this->field18_0x12c)._s_0.aw2a,(pMVar3->_s_0).lemnos,1);
        SetIndependence((this->field18_0x12c)._s_0.aw2a,1);
        (this->field16_0x40)._s_0.aw2aattack = true;
      }
      if ((this->field16_0x40)._s_0.aw1sent == true) {
        bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw3a);
        if (((bVar8) && ((this->field16_0x40)._s_0.aw3aattack == false)) &&
           (fVar14 = GetDistance((this->field18_0x12c)._s_0.aw3a,(pMVar3->_s_0).lemnos),
           fVar14 < 300.0)) {
          Attack((this->field18_0x12c)._s_0.aw3a,(pMVar3->_s_0).lemnos,1);
          SetIndependence((this->field18_0x12c)._s_0.aw3a,1);
          (this->field16_0x40)._s_0.aw3aattack = true;
        }
        if ((this->field16_0x40)._s_0.aw1sent == true) {
          bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw4a);
          if (((bVar8) && ((this->field16_0x40)._s_0.aw4aattack == false)) &&
             (fVar14 = GetDistance((this->field18_0x12c)._s_0.aw4a,(pMVar3->_s_0).lemnos),
             fVar14 < 300.0)) {
            Attack((this->field18_0x12c)._s_0.aw4a,(pMVar3->_s_0).lemnos,1);
            SetIndependence((this->field18_0x12c)._s_0.aw4a,1);
            (this->field16_0x40)._s_0.aw4aattack = true;
          }
          if ((((this->field16_0x40)._s_0.aw1sent == true) &&
              (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw9a), bVar8)) &&
             (((this->field16_0x40)._s_0.aw9aattack == false &&
              (fVar14 = GetDistance((this->field18_0x12c)._s_0.aw9a,(pMVar3->_s_0).lemnos),
              fVar14 < 300.0)))) {
            Attack((this->field18_0x12c)._s_0.aw9a,(pMVar3->_s_0).lemnos,1);
            SetIndependence((this->field18_0x12c)._s_0.aw9a,1);
            (this->field16_0x40)._s_0.aw9aattack = true;
          }
        }
      }
    }
  }
  bVar8 = IsAlive(piVar2);
  if ((!bVar8) && ((this->field16_0x40)._s_0.possiblewin == false)) {
    (this->field16_0x40)._s_0.possiblewin = true;
    AudioMessage("misn0516.wav");
    (this->field16_0x40)._s_0.aw1aattack = true;
    (this->field16_0x40)._s_0.aw2aattack = true;
    (this->field16_0x40)._s_0.aw3aattack = true;
    (this->field16_0x40)._s_0.aw4aattack = true;
    (this->field16_0x40)._s_0.aw5aattack = true;
    (this->field16_0x40)._s_0.aw6aattack = true;
    (this->field16_0x40)._s_0.aw7aattack = true;
    (this->field16_0x40)._s_0.aw8aattack = true;
    (this->field16_0x40)._s_0.aw9aattack = true;
    (this->field16_0x40)._s_0.sent1Done = true;
    (this->field16_0x40)._s_0.sent2Done = true;
    (this->field16_0x40)._s_0.sent3Done = true;
    (this->field16_0x40)._s_0.sent4Done = true;
    bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw1);
    if ((((bVar8) ||
         ((((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw2), bVar8 ||
            (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw3), bVar8)) ||
           (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw4), bVar8)) ||
          ((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw5), bVar8 ||
           (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw1a), bVar8)))))) ||
        (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw2a), bVar8)) ||
       ((((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw3a), bVar8 ||
          (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw4a), bVar8)) ||
         ((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw5a), bVar8 ||
          (((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw6a), bVar8 ||
            (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw7a), bVar8)) ||
           (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw8a), bVar8)))))) ||
        (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw9a), bVar8)))) {
      AudioMessage("misn0517.wav");
    }
  }
  if ((((((this->field16_0x40)._s_0.aw1sent == true) && ((this->field16_0x40)._s_0.aw2sent == true))
       && (((this->field16_0x40)._s_0.aw3sent == true &&
           (((this->field16_0x40)._s_0.aw4sent == true &&
            ((this->field16_0x40)._s_0.sent1Done == true)))))) &&
      ((((this->field16_0x40)._s_0.sent2Done == true &&
        (((((this->field16_0x40)._s_0.sent3Done == true &&
           ((this->field16_0x40)._s_0.sent4Done == true)) &&
          ((this->field16_0x40)._s_0.missionwon == false)) &&
         (((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw1), !bVar8 &&
           (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw2), !bVar8)) &&
          ((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw3), !bVar8 &&
           ((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw4), !bVar8 &&
            (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw5), !bVar8)))))))))) &&
       (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw1a), !bVar8)))) &&
     ((((((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw2a), !bVar8 &&
          (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw3a), !bVar8)) &&
         (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw4a), !bVar8)) &&
        ((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw5a), !bVar8 &&
         (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw6a), !bVar8)))) &&
       (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw7a), !bVar8)) &&
      (((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw8a), !bVar8 &&
        (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.aw9a), !bVar8)) &&
       ((((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w1u1), !bVar8 &&
          (((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w1u2), !bVar8 &&
            (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w1u3), !bVar8)) &&
           (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w1u4), !bVar8)))) &&
         (((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w2u1), !bVar8 &&
           (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w2u2), !bVar8)) &&
          (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w2u3), !bVar8)))) &&
        (((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w2u4), !bVar8 &&
          (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w3u1), !bVar8)) &&
         ((((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w3u2), !bVar8 &&
            (((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w3u3), !bVar8 &&
              (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w3u4), !bVar8)) &&
             (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w4u1), !bVar8)))) &&
           ((bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w4u2), !bVar8 &&
            (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w4u3), !bVar8)))) &&
          (bVar8 = IsAlive(&(this->field18_0x12c)._s_0.w4u4), !bVar8)))))))))))) {
    (this->field16_0x40)._s_0.missionwon = true;
    (this->field16_0x40)._s_0.newobjective = true;
    AudioMessage("misn0511.wav");
    AudioMessage("misn0512.wav");
    pcVar15 = "misn05w1.des";
    fVar14 = Get_Time();
    SucceedMission(fVar14 + 15.0,pcVar15);
  }
  bVar8 = IsAlive(piVar2);
  if ((!bVar8) && ((this->field16_0x40)._s_0.takeoutfactory == false)) {
    Attack((this->field18_0x12c)._s_0.w1u1,(pMVar3->_s_0).lemnos,1);
    Attack((this->field18_0x12c)._s_0.w1u2,(pMVar3->_s_0).lemnos,1);
    Attack((this->field18_0x12c)._s_0.w1u3,(pMVar3->_s_0).lemnos,1);
    Attack((this->field18_0x12c)._s_0.w1u4,(pMVar3->_s_0).lemnos,1);
    Attack((this->field18_0x12c)._s_0.w2u1,(pMVar3->_s_0).lemnos,1);
    Attack((this->field18_0x12c)._s_0.w2u2,(pMVar3->_s_0).lemnos,1);
    Attack((this->field18_0x12c)._s_0.w2u3,(pMVar3->_s_0).lemnos,1);
    Attack((this->field18_0x12c)._s_0.w2u4,(pMVar3->_s_0).lemnos,1);
    Attack((this->field18_0x12c)._s_0.w3u1,(pMVar3->_s_0).lemnos,1);
    Attack((this->field18_0x12c)._s_0.w3u2,(pMVar3->_s_0).lemnos,1);
    Attack((this->field18_0x12c)._s_0.w3u3,(pMVar3->_s_0).lemnos,1);
    Attack((this->field18_0x12c)._s_0.w3u4,(pMVar3->_s_0).lemnos,1);
    Attack((this->field18_0x12c)._s_0.w4u1,(pMVar3->_s_0).lemnos,1);
    Attack((this->field18_0x12c)._s_0.w4u2,(pMVar3->_s_0).lemnos,1);
    Attack((this->field18_0x12c)._s_0.w4u3,(pMVar3->_s_0).lemnos,1);
    Attack((this->field18_0x12c)._s_0.w4u4,(pMVar3->_s_0).lemnos,1);
    (this->field16_0x40)._s_0.takeoutfactory = true;
  }
  return;
}
