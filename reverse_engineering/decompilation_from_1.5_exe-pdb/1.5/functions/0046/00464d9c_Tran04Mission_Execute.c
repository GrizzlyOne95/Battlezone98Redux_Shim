/*
 * Entry: 00464d9c
 * Name: Tran04Mission::Execute
 * Namespace: Tran04Mission
 * Signature: void Execute(Tran04Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tran04Mission::Execute(Tran04Mission *this)

{
  int *piVar1;
  int *piVar2;
  bool bVar3;
  int iVar4;
  GameObject *pGVar5;
  float fVar6;
  char *pcVar7;
  
  if ((this->field16_0x40)._s_0.start_done == false) {
    iVar4 = GetHandle("avturr12_turrettank");
    (this->field18_0x64)._s_0.target1 = iVar4;
    iVar4 = GetHandle("avturr-1_turrettank");
    (this->field18_0x64)._s_0.target2 = iVar4;
    iVar4 = GetHandle("avrecy-1_recycler");
    (this->field18_0x64)._s_0.recycler = iVar4;
    iVar4 = GetHandle("apcamr-1_camerapod");
    (this->field18_0x64)._s_0.camera = iVar4;
    iVar4 = GetHandle("player-1_hover");
    (this->field18_0x64)._s_0.player = iVar4;
    GameObjectHandle::GetObj((this->field18_0x64)._s_0.recycler);
    SetScrap(1,0x1e);
    AudioMessage("tran0401.wav");
    AudioMessage("tran0402.wav");
    AudioMessage("tran0424.wav");
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"tran0401.otf",DisplayInterface::colorWhite,8.0);
    (this->field16_0x40)._s_0.start_done = true;
  }
  if ((this->field16_0x40)._s_0.message1 == false) {
    piVar1 = &(this->field18_0x64)._s_0.recycler;
    bVar3 = IsAlive(piVar1);
    if ((bVar3) && (pGVar5 = GameObjectHandle::GetObj(*piVar1), pGVar5->isSelected != false)) {
      AudioMessage("tran0425.wav");
      (this->field16_0x40)._s_0.message1 = true;
    }
    if ((this->field16_0x40)._s_0.message1 != false) goto LAB_00464e8c;
LAB_00464eb6:
    if ((this->field16_0x40)._s_0.message2 != false) goto LAB_00464ebb;
  }
  else {
LAB_00464e8c:
    if ((this->field16_0x40)._s_0.message2 == false) {
      piVar1 = &(this->field18_0x64)._s_0.recycler;
      bVar3 = IsAlive(piVar1);
      if ((bVar3) && (bVar3 = IsDeployed(*piVar1), bVar3)) {
        AudioMessage("tran0424.wav");
        (this->field16_0x40)._s_0.message2 = true;
      }
      goto LAB_00464eb6;
    }
LAB_00464ebb:
    piVar1 = &(this->field18_0x64)._s_0.recycler;
    bVar3 = IsAlive(piVar1);
    if (((bVar3) && (pGVar5 = GameObjectHandle::GetObj(*piVar1), pGVar5->isSelected != false)) &&
       ((this->field16_0x40)._s_0.press7 == false)) {
      AudioMessage("tran0406.wav");
      (this->field16_0x40)._s_0.press7 = true;
      (this->field16_0x40)._s_0.message6 = true;
    }
  }
  if ((this->field16_0x40)._s_0.message6 == false) {
LAB_00464f36:
    if ((this->field16_0x40)._s_0.message7 != false) goto LAB_00464f3b;
LAB_00464f94:
    if ((this->field16_0x40)._s_0.message8 != false) goto LAB_00464f99;
  }
  else {
    if ((this->field16_0x40)._s_0.message7 == false) {
      piVar1 = &(this->field18_0x64)._s_0.recycler;
      bVar3 = IsAlive(piVar1);
      if ((bVar3) && (pGVar5 = GameObjectHandle::GetObj(*piVar1), pGVar5->isSelected == false)) {
        AudioMessage("tran0407.wav");
        fVar6 = Get_Time();
        (this->field16_0x40)._s_0.message7 = true;
        (this->field17_0x58)._s_0.camera_delay = fVar6 + 5.0;
      }
      goto LAB_00464f36;
    }
LAB_00464f3b:
    if (((this->field16_0x40)._s_0.message8 == false) &&
       (fVar6 = Get_Time(), (this->field17_0x58)._s_0.camera_delay < fVar6)) {
      AudioMessage("tran0408.wav");
      (this->field17_0x58)._s_0.camera_delay = 99999.0;
    }
    if ((this->field16_0x40)._s_0.message7 == false) goto LAB_00464f94;
    if ((this->field16_0x40)._s_0.message8 == false) {
      iVar4 = GetUserTarget();
      if (iVar4 == (this->field18_0x64)._s_0.camera) {
        AudioMessage("tran0409.wav");
        (this->field16_0x40)._s_0.message8 = true;
        fVar6 = Get_Time();
        (this->field17_0x58)._s_0.camera_delay = fVar6 + 3.0;
      }
      goto LAB_00464f94;
    }
LAB_00464f99:
    if ((((this->field16_0x40)._s_0.message9 == false) &&
        (fVar6 = Get_Time(), (this->field17_0x58)._s_0.camera_delay < fVar6)) &&
       ((this->field16_0x40)._s_0.found2 != false)) {
      AudioMessage("tran0410.wav");
      (this->field17_0x58)._s_0.camera_delay = 99999.0;
      (this->field16_0x40)._s_0.message9 = true;
    }
    if ((((this->field16_0x40)._s_0.message8 != false) &&
        (bVar3 = IsAlive(&(this->field18_0x64)._s_0.wing), !bVar3)) &&
       ((this->field16_0x40)._s_0.message16 == false)) {
      pcVar7 = "tran04l1.des";
      fVar6 = Get_Time();
      FailMission(fVar6 + 5.0,pcVar7);
      (this->field16_0x40)._s_0.message16 = true;
    }
  }
  if ((this->field16_0x40)._s_0.message9 == false) {
LAB_00465038:
    if ((this->field16_0x40)._s_0.message10 != false) goto LAB_00465041;
  }
  else {
    if ((this->field16_0x40)._s_0.message10 == false) {
      piVar1 = &(this->field18_0x64)._s_0.wing;
      bVar3 = IsAlive(piVar1);
      if ((bVar3) && (pGVar5 = GameObjectHandle::GetObj(*piVar1), pGVar5->isSelected != false)) {
        AudioMessage("tran0411.wav");
        (this->field16_0x40)._s_0.message10 = true;
      }
      goto LAB_00465038;
    }
LAB_00465041:
    if ((this->field16_0x40)._s_0.message11 == false) {
      piVar1 = &(this->field18_0x64)._s_0.wing;
      bVar3 = IsAlive(piVar1);
      if (((bVar3) && (pGVar5 = GameObjectHandle::GetObj(*piVar1), pGVar5->isSelected == false)) &&
         ((this->field17_0x58)._s_0.camera_delay == 99999.0)) {
        fVar6 = Get_Time();
        (this->field17_0x58)._s_0.camera_delay = fVar6 + 10.0;
      }
    }
    if ((this->field16_0x40)._s_0.message10 != false) {
      if (((this->field16_0x40)._s_0.message11 == false) &&
         (fVar6 = Get_Time(), (this->field17_0x58)._s_0.camera_delay < fVar6)) {
        AudioMessage("tran0412.wav");
        (this->field17_0x58)._s_0.camera_delay = 99999.0;
        (this->field16_0x40)._s_0.message11 = true;
      }
      if (((this->field16_0x40)._s_0.message10 != false) &&
         ((this->field16_0x40)._s_0.attacked == false)) {
        piVar1 = &(this->field18_0x64)._s_0.wing;
        bVar3 = IsAlive(piVar1);
        if ((bVar3) && (pGVar5 = GameObjectHandle::GetObj(*piVar1), 0.0 < pGVar5->enemyShot)) {
          AudioMessage("tran0413.wav");
          (this->field16_0x40)._s_0.attacked = true;
        }
      }
    }
  }
  piVar1 = &(this->field18_0x64)._s_0.target1;
  bVar3 = IsAlive(piVar1);
  if ((!bVar3) && ((this->field16_0x40)._s_0.message12 == false)) {
    AudioMessage("tran0415.wav");
    piVar2 = &(this->field18_0x64)._s_0.target2;
    bVar3 = IsAlive(piVar2);
    if (bVar3) {
      SetObjectiveOn(*piVar2);
      SetObjectiveName(*piVar2,"Drone 2");
    }
    (this->field16_0x40)._s_0.message12 = true;
  }
  pGVar5 = GameObjectHandle::GetObj((this->field18_0x64)._s_0.player);
  if ((((pGVar5 == (GameObject *)0x0) ||
       (pGVar5 = GameObjectHandle::GetObj((this->field18_0x64)._s_0.target2),
       pGVar5 == (GameObject *)0x0)) || ((this->field16_0x40)._s_0.message12 == false)) ||
     (fVar6 = GetDistance((this->field18_0x64)._s_0.player,(this->field18_0x64)._s_0.target2),
     300.0 <= fVar6)) {
LAB_00465195:
    if ((this->field16_0x40)._s_0.message13 != false) goto LAB_0046519a;
LAB_004651b8:
    if ((this->field16_0x40)._s_0.message14 == false) goto LAB_004651e2;
  }
  else {
    if ((this->field16_0x40)._s_0.message13 == false) {
      AudioMessage("tran0416.wav");
      (this->field16_0x40)._s_0.message13 = true;
      AudioMessage("tran0418.wav");
      (this->field16_0x40)._s_0.message13 = true;
      goto LAB_00465195;
    }
LAB_0046519a:
    iVar4 = GetUserTarget();
    if (iVar4 != (this->field18_0x64)._s_0.target2) goto LAB_004651b8;
    if ((this->field16_0x40)._s_0.message14 == false) {
      AudioMessage("tran0410.wav");
      (this->field16_0x40)._s_0.message14 = true;
      goto LAB_004651b8;
    }
  }
  if (((this->field16_0x40)._s_0.message15 == false) &&
     (pGVar5 = GameObjectHandle::GetObj((this->field18_0x64)._s_0.wing), pGVar5->isSelected != false
     )) {
    AudioMessage("tran0420.wav");
    (this->field16_0x40)._s_0.message15 = true;
  }
LAB_004651e2:
  if ((this->field16_0x40)._s_0.message6 != false) {
    bVar3 = IsAlive(piVar1);
    if (((!bVar3) && (bVar3 = IsAlive(&(this->field18_0x64)._s_0.target2), !bVar3)) &&
       ((this->field16_0x40)._s_0.message16 == false)) {
      AudioMessage("tran0421.wav");
      pcVar7 = "tran04w1.des";
      fVar6 = Get_Time();
      SucceedMission(fVar6 + 10.0,pcVar7);
      (this->field16_0x40)._s_0.message16 = true;
    }
    if ((this->field16_0x40)._s_0.message6 != false) {
      return;
    }
  }
  bVar3 = IsAlive(piVar1);
  if ((bVar3) && (bVar3 = IsAlive(&(this->field18_0x64)._s_0.target2), bVar3)) {
    return;
  }
  if ((this->field16_0x40)._s_0.message16 == false) {
    pcVar7 = "tran04l1.des";
    (this->field16_0x40)._s_0.message16 = true;
    fVar6 = Get_Time();
    FailMission(fVar6 + 5.0,pcVar7);
  }
  return;
}
