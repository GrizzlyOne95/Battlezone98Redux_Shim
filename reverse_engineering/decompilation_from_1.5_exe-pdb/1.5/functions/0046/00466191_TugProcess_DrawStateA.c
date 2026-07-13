/*
 * Entry: 00466191
 * Name: TugProcess::DrawStateA
 * Namespace: TugProcess
 * Signature: void DrawStateA(TugProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall TugProcess::DrawStateA(TugProcess *this)

{
  VEHICLE *pVVar1;
  Craft *pCVar2;
  int iVar3;
  char *pcVar4;
  char local_58 [80];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar3 = (**(code **)(this->craft->_padding_ + 0x30))();
  sprintf(local_58," TugProcess:");
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," ID (%s) Seqno (%d)",iVar3 + 8,this->craft->_padding_);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," State (%s)",stateText[this->curState]);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  iVar3 = (**(code **)this->craft->_padding_)();
  if ((*(int *)(iVar3 + 0x28) == 1) ||
     (iVar3 = (**(code **)this->craft->_padding_)(), *(int *)(iVar3 + 0x28) == 6)) {
    pVVar1 = this->craft->vhcl;
    sprintf(local_58," Craft (0x%p)");
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    sprintf(local_58," Cargo (0x%p)",this->craft[1]._padding_);
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    if (this->craft[1]._padding_ != 0) {
      sprintf(local_58," Cargo (%s)");
      DisplayInterface::DrawTextA
                (local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    }
    sprintf(local_58," Steer (%+.2f)",(double)(pVVar1->control).steer);
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    sprintf(local_58," Braccel (%+.2f)",(double)(pVVar1->control).braccel);
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    sprintf(local_58," Pitch (%+.2f) Strafe (%+.2f)",(double)(pVVar1->control).pitch,
            (double)(pVVar1->control).strafe);
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    pcVar4 = "off";
    if ((pVVar1->control).turbo != 0) {
      pcVar4 = "on";
    }
    sprintf(local_58," Turbo (%s) Jump (%s)",pcVar4);
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    iVar3 = (**(code **)(this->craft->_padding_ + 0x30))();
    sprintf(local_58," Transform Position:");
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    sprintf(local_58," X (%.2f)",*(undefined8 *)(iVar3 + 0x48));
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    sprintf(local_58," Y (%.2f)",*(undefined8 *)(iVar3 + 0x50));
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    sprintf(local_58," Z (%.2f)",*(undefined8 *)(iVar3 + 0x58));
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    pCVar2 = this->craft;
    sprintf(local_58," Velocity:");
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    sprintf(local_58," X(%+.2f) Y(%+.2f) Z(%+.2f)",(double)(float)pCVar2->_padding_,
            (double)(float)pCVar2->_padding_,(double)(float)pCVar2->_padding_);
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    sprintf(local_58," Accel:");
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    sprintf(local_58," X(%+.2f) Y(%+.2f) Z(%+.2f)",(double)(float)pCVar2->_padding_,
            (double)(float)pCVar2->_padding_,(double)(float)pCVar2->_padding_);
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    sprintf(local_58," Omega:");
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    sprintf(local_58," X(%+.2f) Y(%+.2f) Z(%+.2f)",(double)(float)pCVar2->_padding_,
            (double)(float)pCVar2->_padding_,(double)(float)pCVar2->_padding_);
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  }
  if (this->task != (AiTask *)0x0) {
    (**(code **)(this->task->_padding_ + 0x20))();
  }
  return;
}
