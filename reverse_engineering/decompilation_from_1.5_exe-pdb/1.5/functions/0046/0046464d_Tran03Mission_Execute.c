/*
 * Entry: 0046464d
 * Name: Tran03Mission::Execute
 * Namespace: Tran03Mission
 * Signature: void Execute(Tran03Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tran03Mission::Execute(Tran03Mission *this)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  GameObject *pGVar4;
  GameObject *pGVar5;
  VECTOR_3D *pVVar6;
  VECTOR_3D *pVVar7;
  long lVar8;
  float fVar9;
  char *pcVar10;
  
  if ((this->field16_0x40)._s_0.start_done == false) {
    AudioMessage("tran0301.wav");
    AudioMessage("tran0302.wav");
    iVar3 = GetHandle("eggeizr111_geyser");
    (this->field18_0x64)._s_0.geyser = iVar3;
    iVar3 = GetHandle("avrecy-1_recycler");
    (this->field18_0x64)._s_0.recycler = iVar3;
    iVar3 = GetHandle("svfigh-1_wingman");
    (this->field18_0x64)._s_0.attacker = iVar3;
    SetObjectiveOn((this->field18_0x64)._s_0.recycler);
    SetObjectiveName((this->field18_0x64)._s_0.recycler,"recycler");
    GameObjectHandle::GetObj((this->field18_0x64)._s_0.recycler);
    SetScrap(1,7);
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"tran0301.otf",DisplayInterface::colorWhite,8.0);
    InfoDisplay::AddObjective(&infoDisplay,"tran0302.otf",DisplayInterface::colorWhite,8.0);
    (this->field16_0x40)._s_0.start_done = true;
    if ((this->field16_0x40)._s_0.start_done != false) goto LAB_00464717;
LAB_00464769:
    if ((this->field16_0x40)._s_0.first_message != false) goto LAB_0046476f;
LAB_0046479e:
    if ((this->field16_0x40)._s_0.second_message != false) goto LAB_004647a4;
LAB_00464815:
    if ((this->field16_0x40)._s_0.third_message != false) goto LAB_0046481f;
LAB_004648d0:
    if ((this->field16_0x40)._s_0.fifth_message != false) goto LAB_004648d6;
  }
  else {
LAB_00464717:
    if ((this->field16_0x40)._s_0.first_message == false) {
      piVar1 = &(this->field18_0x64)._s_0.recycler;
      bVar2 = IsAlive(piVar1);
      if ((bVar2) && (pGVar4 = GameObjectHandle::GetObj(*piVar1), pGVar4->isSelected != false)) {
        AudioMessage("tran0303.wav");
        SetObjectiveOff(*piVar1);
        SetObjectiveOn((this->field18_0x64)._s_0.geyser);
        SetObjectiveName((this->field18_0x64)._s_0.geyser,"Check Point 1");
        (this->field16_0x40)._s_0.first_message = true;
      }
      goto LAB_00464769;
    }
LAB_0046476f:
    if ((this->field16_0x40)._s_0.second_message == false) {
      piVar1 = &(this->field18_0x64)._s_0.recycler;
      bVar2 = IsAlive(piVar1);
      if ((bVar2) && (bVar2 = IsDeployed(*piVar1), !bVar2)) {
        AudioMessage("tran0304.wav");
        (this->field16_0x40)._s_0.second_message = true;
      }
      goto LAB_0046479e;
    }
LAB_004647a4:
    if ((this->field16_0x40)._s_0.third_message == false) {
      piVar1 = &(this->field18_0x64)._s_0.recycler;
      bVar2 = IsAlive(piVar1);
      if (bVar2) {
        pGVar4 = GameObjectHandle::GetObj(*piVar1);
        pGVar5 = GameObjectHandle::GetObj((this->field18_0x64)._s_0.geyser);
        pVVar6 = (VECTOR_3D *)(**(code **)(pGVar4->_padding_ + 0xc))();
        pVVar7 = (VECTOR_3D *)(**(code **)(pGVar5->_padding_ + 0xc))();
        fVar9 = Dist3D_Squared(*pVVar7,*pVVar6);
        if (fVar9 < 40000.0) {
          AudioMessage("tran0305.wav");
          (this->field16_0x40)._s_0.third_message = true;
        }
      }
      goto LAB_00464815;
    }
LAB_0046481f:
    if ((this->field16_0x40)._s_0.fourth_message == false) {
      piVar1 = &(this->field18_0x64)._s_0.recycler;
      bVar2 = IsAlive(piVar1);
      if ((bVar2) && (pGVar4 = GameObjectHandle::GetObj(*piVar1), pGVar4->isSelected != false)) {
        AudioMessage("tran0306.wav");
        (this->field16_0x40)._s_0.fourth_message = true;
      }
    }
    if ((this->field16_0x40)._s_0.third_message == false) goto LAB_004648d0;
    if ((this->field16_0x40)._s_0.fifth_message == false) {
      piVar1 = &(this->field18_0x64)._s_0.recycler;
      bVar2 = IsAlive(piVar1);
      if ((bVar2) && (bVar2 = IsDeployed(*piVar1), bVar2)) {
        SetObjectiveOff((this->field18_0x64)._s_0.geyser);
        InfoDisplay::ClearObjectives(&infoDisplay);
        InfoDisplay::AddObjective(&infoDisplay,"tran0301.otf",DisplayInterface::colorGreen,8.0);
        InfoDisplay::AddObjective(&infoDisplay,"tran0302.otf",DisplayInterface::colorWhite,8.0);
        AudioMessage("tran0307.wav");
        (this->field16_0x40)._s_0.fifth_message = true;
      }
      goto LAB_004648d0;
    }
LAB_004648d6:
    if (((this->field16_0x40)._s_0.fifthb_message == false) &&
       (pGVar4 = GameObjectHandle::GetObj((this->field18_0x64)._s_0.recycler),
       pGVar4->isSelected != false)) {
      AudioMessage("tran0309.wav");
      (this->field16_0x40)._s_0.fifthb_message = true;
    }
  }
  piVar1 = &(this->field18_0x64)._s_0.attacker;
  bVar2 = IsAlive(piVar1);
  if ((bVar2) && ((this->field16_0x40)._s_0.sixth_message == false)) {
    AddHealth(*piVar1,50.0);
  }
  if (((this->field16_0x40)._s_0.fifth_message != false) &&
     ((this->field16_0x40)._s_0.sixth_message == false)) {
    pGVar4 = GameObjectHandle::GetObj((this->field18_0x64)._s_0.recycler);
    lVar8 = Team::GetScrap(pGVar4->teamList);
    if ((lVar8 < 5) && ((this->field16_0x40)._s_0.found != false)) {
      AudioMessage("tran0308.wav");
      (this->field16_0x40)._s_0.sixth_message = true;
      fVar9 = Get_Time();
      (this->field17_0x5c)._s_0.delay_message = fVar9 + 5.0;
      bVar2 = IsAlive(piVar1);
      if (bVar2) {
        Attack(*piVar1,(this->field18_0x64)._s_0.scav,1);
      }
    }
  }
  if (((this->field16_0x40)._s_0.scav_died == false) &&
     ((bVar2 = IsAlive(&(this->field18_0x64)._s_0.recycler), !bVar2 ||
      (((this->field16_0x40)._s_0.sixth_message != false &&
       (bVar2 = IsAlive((this->field18_0x64).h_array), !bVar2)))))) {
    (this->field16_0x40)._s_0.scav_died = true;
    AudioMessage("tran0313.wav");
    pcVar10 = "tran03l1.des";
    fVar9 = Get_Time();
    FailMission(fVar9 + 10.0,pcVar10);
  }
  fVar9 = Get_Time();
  if ((this->field17_0x5c)._s_0.delay_message < fVar9) {
    (this->field17_0x5c)._s_0.delay_message = 99999.0;
  }
  if ((this->field16_0x40)._s_0.sixth_message != false) {
    if ((this->field16_0x40)._s_0.seventh_message != false) goto LAB_00464a1d;
    bVar2 = IsAlive(piVar1);
    if (!bVar2) {
      AudioMessage("tran0314.wav");
      (this->field16_0x40)._s_0.seventh_message = true;
    }
  }
  if ((this->field16_0x40)._s_0.seventh_message == false) {
    return;
  }
LAB_00464a1d:
  if ((this->field16_0x40)._s_0.eighth_message == false) {
    pGVar4 = GameObjectHandle::GetObj((this->field18_0x64)._s_0.recycler);
    lVar8 = Team::GetScrap(pGVar4->teamList);
    if (1 < lVar8) {
      AudioMessage("tran0310.wav");
      AudioMessage("tran0315.wav");
      (this->field16_0x40)._s_0.eighth_message = true;
      pcVar10 = "tran03w1.des";
      fVar9 = Get_Time();
      SucceedMission(fVar9 + 20.0,pcVar10);
    }
  }
  return;
}
