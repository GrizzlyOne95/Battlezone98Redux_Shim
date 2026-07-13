/*
 * Entry: 0046f8df
 * Name: UserProcess::DrawStateA
 * Namespace: UserProcess
 * Signature: void DrawStateA(UserProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall UserProcess::DrawStateA(UserProcess *this)

{
  int iVar1;
  int iVar2;
  UserProcess *pUVar3;
  char *pcVar4;
  char *local_70 [4];
  int local_60;
  UserProcess *local_5c;
  char local_58 [80];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar1 = this->_padding_;
  local_5c = this;
  local_60 = (**(code **)(*(int *)(iVar1 + 0x20) + 0x30))();
  iVar2 = *(int *)(iVar1 + 0x228);
  sprintf(local_58," UserProcess:");
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," ID (%s) Seqno (%d)",local_60 + 8,*(undefined4 *)(iVar1 + 0x150));
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  local_70[0] = " undeployed";
  local_70[1] = " deploying";
  local_70[2] = " deployed";
  local_70[3] = " undeploying";
  sprintf(local_58,local_70[*(int *)(iVar1 + 0x220)]);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," Steer (%+.2f)",(double)*(float *)(iVar2 + 0xc4));
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," Braccel (%+.2f)",(double)*(float *)(iVar2 + 0xd0));
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," Pitch (%+.2f) Strafe (%+.2f)",(double)*(float *)(iVar2 + 200),
          (double)*(float *)(iVar2 + 0xcc));
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  pcVar4 = "off";
  if (*(int *)(iVar2 + 0xd4) != 0) {
    pcVar4 = "on";
  }
  sprintf(local_58," Turbo (%s) Jump (%s)",pcVar4);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  pUVar3 = local_5c;
  (**(code **)(*(int *)(local_5c->_padding_ + 0x20) + 4))();
  sprintf(local_58," Team (%d)");
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," Perceived Team (%d)",*(undefined4 *)(pUVar3->_padding_ + 0x174));
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  return;
}
