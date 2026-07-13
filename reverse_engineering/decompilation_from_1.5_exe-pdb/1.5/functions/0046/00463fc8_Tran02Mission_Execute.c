/*
 * Entry: 00463fc8
 * Name: Tran02Mission::Execute
 * Namespace: Tran02Mission
 * Signature: void Execute(Tran02Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tran02Mission::Execute(Tran02Mission *this)

{
  Tran02Mission_u_100 *pTVar1;
  int *piVar2;
  bool bVar3;
  GameObject *pGVar4;
  GameObject *pGVar5;
  VECTOR_3D *pVVar6;
  VECTOR_3D *pVVar7;
  AiCommand AVar8;
  float fVar9;
  char *pcVar10;
  
  pTVar1 = &this->field18_0x64;
  bVar3 = IsAlive(pTVar1->h_array);
  if (!bVar3) {
    if ((this->field16_0x40)._s_0.lost != false) {
      return;
    }
    pcVar10 = "tran02l1.des";
    (this->field16_0x40)._s_0.lost = true;
    fVar9 = Get_Time();
    FailMission(fVar9 + 5.0,pcVar10);
    return;
  }
  fVar9 = PlayReminder((this->field17_0x58)._s_0.repeat_time,(this->field20_0x8c)._s_0.message);
  bVar3 = (this->field16_0x40)._s_0.start_done;
  (this->field17_0x58)._s_0.repeat_time = fVar9;
  if (bVar3 == false) {
    SetObjectiveOn((pTVar1->_s_0).turret);
    SetObjectiveName((pTVar1->_s_0).turret,"Turret");
    AudioMessage("tran0201.wav");
    fVar9 = Get_Time();
    (this->field17_0x58)._s_0.hint_delay = fVar9 + 1.0;
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"tran0201.otf",DisplayInterface::colorGreen,8.0);
    (this->field16_0x40)._s_0.start_done = true;
  }
  fVar9 = Get_Time();
  if ((this->field17_0x58)._s_0.hint_delay < fVar9) {
    AudioMessage("tran0204.wav");
    (this->field17_0x58)._s_0.hint_delay = 99999.0;
    fVar9 = Get_Time();
    (this->field20_0x8c)._s_0.message = 3;
    (this->field16_0x40)._s_0.second_selection = true;
    (this->field17_0x58)._s_0.repeat_time = fVar9 + 30.0;
  }
  if ((((this->field16_0x40)._s_0.thirda_selection == false) &&
      ((this->field16_0x40)._s_0.second_selection != false)) && (controlPanel.currentItem == 1)) {
    AudioMessage("tran0205.wav");
    (this->field16_0x40)._s_0.thirda_selection = true;
    fVar9 = Get_Time();
    (this->field20_0x8c)._s_0.message = 4;
    (this->field17_0x58)._s_0.repeat_time = fVar9 + 30.0;
  }
  if ((this->field16_0x40)._s_0.third_selection == false) {
    if (((this->field16_0x40)._s_0.second_selection != false) &&
       (pGVar4 = GameObjectHandle::GetObj((pTVar1->_s_0).turret), pGVar4->isSelected != false)) {
      AudioMessage("tran0206.wav");
      SetObjectiveOff((pTVar1->_s_0).turret);
      SetObjectiveOn((this->field18_0x64)._s_0.pointer);
      SetObjectiveName((this->field18_0x64)._s_0.pointer,"Target Range");
      (this->field16_0x40)._s_0.third_selection = true;
      fVar9 = Get_Time();
      (this->field20_0x8c)._s_0.message = 5;
      (this->field17_0x58)._s_0.repeat_time = fVar9 + 30.0;
    }
    if ((this->field16_0x40)._s_0.third_selection != false) goto LAB_00464142;
LAB_00464215:
    if ((this->field16_0x40)._s_0.hint1 != false) goto LAB_0046421b;
LAB_00464297:
    if ((this->field16_0x40)._s_0.fourth_selection != false) goto LAB_0046429d;
  }
  else {
LAB_00464142:
    if (((this->field16_0x40)._s_0.go_reminder == false) &&
       (pGVar4 = GameObjectHandle::GetObj((pTVar1->_s_0).turret), pGVar4->isSelected == false)) {
      AudioMessage("misn0109.wav");
      (this->field16_0x40)._s_0.go_reminder = true;
      fVar9 = Get_Time();
      (this->field20_0x8c)._s_0.message = 6;
      (this->field17_0x58)._s_0.repeat_time = fVar9 + 30.0;
    }
    if ((this->field16_0x40)._s_0.third_selection == false) goto LAB_00464215;
    if ((this->field16_0x40)._s_0.hint1 == false) {
      pGVar4 = GameObjectHandle::GetObj((pTVar1->_s_0).turret);
      pGVar5 = GameObjectHandle::GetObj((this->field18_0x64)._s_0.pointer);
      pVVar6 = (VECTOR_3D *)(**(code **)(pGVar4->_padding_ + 0xc))();
      pVVar7 = (VECTOR_3D *)(**(code **)(pGVar5->_padding_ + 0xc))();
      fVar9 = Dist3D_Squared(*pVVar7,*pVVar6);
      if (fVar9 < 10000.0) {
        AudioMessage("tran0207.wav");
        AudioMessage("tran0212.wav");
        (this->field16_0x40)._s_0.hint1 = true;
        fVar9 = Get_Time();
        (this->field20_0x8c)._s_0.message = 7;
        (this->field17_0x58)._s_0.repeat_time = fVar9 + 30.0;
      }
      goto LAB_00464215;
    }
LAB_0046421b:
    if (((this->field16_0x40)._s_0.hint2 == false) && (controlPanel.currentItem == 1)) {
      (this->field16_0x40)._s_0.hint2 = true;
      AudioMessage("tran0211.wav");
      fVar9 = Get_Time();
      (this->field20_0x8c)._s_0.message = 4;
      (this->field17_0x58)._s_0.repeat_time = fVar9 + 20.0;
    }
    if ((this->field16_0x40)._s_0.hint1 == false) goto LAB_00464297;
    if ((this->field16_0x40)._s_0.fourth_selection == false) {
      pGVar4 = GameObjectHandle::GetObj((pTVar1->_s_0).turret);
      if (pGVar4->isSelected != false) {
        AudioMessage("tran0208.wav");
        (this->field16_0x40)._s_0.fourth_selection = true;
        fVar9 = Get_Time();
        (this->field20_0x8c)._s_0.message = 8;
        (this->field17_0x58)._s_0.repeat_time = fVar9 + 30.0;
      }
      goto LAB_00464297;
    }
LAB_0046429d:
    if ((this->field16_0x40)._s_0.fifth_selection != false) goto LAB_00464322;
    AVar8 = GetCurrentCommand((pTVar1->_s_0).turret);
    if (AVar8 == CMD_GO) {
      (this->field17_0x58)._s_0.repeat_time = 99999.0;
      AudioMessage("tran0209.wav");
      piVar2 = &(this->field18_0x64)._s_0.haul1;
      bVar3 = IsAlive(piVar2);
      if (bVar3) {
        SetObjectiveOff((this->field18_0x64)._s_0.pointer);
        Goto(*piVar2,(pTVar1->_s_0).turret,1);
        SetObjectiveOn(*piVar2);
        SetObjectiveName(*piVar2,"Target Drone");
      }
      else {
        pcVar10 = "tran02l1.des";
        fVar9 = Get_Time();
        FailMission(fVar9 + 2.0,pcVar10);
      }
      (this->field16_0x40)._s_0.fifth_selection = true;
    }
  }
  if ((this->field16_0x40)._s_0.fifth_selection == false) {
    return;
  }
LAB_00464322:
  if (((this->field16_0x40)._s_0.end_message == false) &&
     (pGVar4 = GameObjectHandle::GetObj((this->field18_0x64)._s_0.haul1),
     pGVar4 == (GameObject *)0x0)) {
    AudioMessage("tran0210.wav");
    (this->field16_0x40)._s_0.end_message = true;
    pcVar10 = "tran02w1.des";
    fVar9 = Get_Time();
    SucceedMission(fVar9 + 10.0,pcVar10);
  }
  return;
}
