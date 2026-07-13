/*
 * Entry: 00415e8c
 * Name: Inst4XMission::Execute
 * Namespace: Inst4XMission
 * Signature: void Execute(Inst4XMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Inst4XMission::Execute(Inst4XMission *this)

{
  Team *pTVar1;
  int iVar2;
  float fVar3;
  char *pcVar4;
  
  pTVar1 = Team::GetTeam(2);
  if (((((this->field19_0x4c)._s_0.gameOver == false) &&
       (iVar2 = Team::FirstFilledSlot(pTVar1,1,4), iVar2 == -1)) &&
      (iVar2 = Team::FirstFilledSlot(pTVar1,5,0xe), iVar2 == -1)) &&
     (iVar2 = Team::FirstFilledSlot(pTVar1,0xf,0x18), iVar2 == -1)) {
    (this->field19_0x4c)._s_0.gameOver = true;
    InfoDisplay::ClearObjectives(&infoDisplay);
    AddObjective(missionObjective,DisplayInterface::colorGreen,8.0);
    pcVar4 = shellSuccess;
    fVar3 = Get_Time();
    SucceedMission(fVar3 + 5.0,pcVar4);
  }
  if (((successCondition == 1) && ((this->field19_0x4c)._s_0.gameOver == false)) &&
     (iVar2 = Team::FirstFilledSlot(pTVar1,1,4), iVar2 == -1)) {
    (this->field19_0x4c)._s_0.gameOver = true;
    InfoDisplay::ClearObjectives(&infoDisplay);
    AddObjective(missionObjective,DisplayInterface::colorGreen,8.0);
    pcVar4 = shellSuccess;
    fVar3 = Get_Time();
    SucceedMission(fVar3 + 5.0,pcVar4);
  }
  pTVar1 = Team::GetTeam(1);
  if (failCondition == 1) {
    if ((this->field19_0x4c)._s_0.gameOver != false) {
      return;
    }
    iVar2 = Team::FirstFilledSlot(pTVar1,1,4);
    if (iVar2 == -1) {
      (this->field19_0x4c)._s_0.gameOver = true;
      InfoDisplay::ClearObjectives(&infoDisplay);
      AddObjective(missionObjective,DisplayInterface::colorRed,8.0);
      pcVar4 = shellFail;
      fVar3 = Get_Time();
      FailMission(fVar3 + 5.0,pcVar4);
    }
  }
  if ((this->field19_0x4c)._s_0.gameOver == false) {
    if (((cockpitTimer.timer < 1) && ((this->field19_0x4c)._s_0.timerRunning == true)) &&
       (shellOutOfTime == 0)) {
      (this->field19_0x4c)._s_0.gameOver = true;
      InfoDisplay::ClearObjectives(&infoDisplay);
      AddObjective(missionObjective,DisplayInterface::colorRed,8.0);
      pcVar4 = shellFail;
      fVar3 = Get_Time();
      FailMission(fVar3 + 5.0,pcVar4);
    }
    if (((((this->field19_0x4c)._s_0.gameOver == false) && (cockpitTimer.timer < 1)) &&
        ((this->field19_0x4c)._s_0.timerRunning == true)) && (shellOutOfTime == 1)) {
      (this->field19_0x4c)._s_0.gameOver = true;
      InfoDisplay::ClearObjectives(&infoDisplay);
      AddObjective(missionObjective,DisplayInterface::colorGreen,8.0);
      pcVar4 = shellSuccess;
      fVar3 = Get_Time();
      SucceedMission(fVar3 + 5.0,pcVar4);
    }
  }
  return;
}
