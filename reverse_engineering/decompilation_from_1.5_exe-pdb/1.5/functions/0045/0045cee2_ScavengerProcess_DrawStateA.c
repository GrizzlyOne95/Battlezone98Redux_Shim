/*
 * Entry: 0045cee2
 * Name: ScavengerProcess::DrawStateA
 * Namespace: ScavengerProcess
 * Signature: void DrawStateA(ScavengerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall ScavengerProcess::DrawStateA(ScavengerProcess *this)

{
  int iVar1;
  WorldInterface *pWVar2;
  char *pcVar3;
  float *pfVar4;
  char *pcVar5;
  float fVar6;
  undefined1 local_78 [4];
  float local_74;
  float fStack_70;
  float local_6c;
  int local_68;
  WorldInterface *local_64;
  long local_60;
  int local_5c;
  char local_58 [80];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_5c = (**(code **)(this->craft->_padding_ + 0x30))();
  iVar1 = this->craft->_padding_;
  sprintf(local_58," ScavengerProcess:");
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," ID (%s) Seqno (%d)",local_5c + 8,this->craft->_padding_);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," State (%s)",stateText[this->curState]);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," Steer (%+.2f)",(double)*(float *)(iVar1 + 0xc4));
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," Braccel (%+.2f)",(double)*(float *)(iVar1 + 0xd0));
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," Pitch (%+.2f) Strafe (%+.2f)",(double)*(float *)(iVar1 + 200),
          (double)*(float *)(iVar1 + 0xcc));
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  pcVar3 = "off";
  pcVar5 = "on";
  if (*(int *)(iVar1 + 0xd8) == 0) {
    pcVar5 = "off";
  }
  if (*(int *)(iVar1 + 0xd4) != 0) {
    pcVar3 = "on";
  }
  sprintf(local_58," Turbo (%s) Jump (%s)",pcVar3,pcVar5);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  if (this->curState == WAIT) {
    sprintf(local_58," Wait Time (%.2f)",(double)this->wait_time);
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    fVar6 = Get_Time();
    sprintf(local_58," Get Time (%.2f)",(double)fVar6);
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  }
  local_64 = WorldInterface::currentDisplay;
  pfVar4 = (float *)(**(code **)(this->craft->_padding_ + 0xc))();
  pWVar2 = local_64;
  local_74 = *pfVar4;
  fStack_70 = pfVar4[1];
  local_6c = pfVar4[2];
  (**(code **)(*(int *)local_64 + 0x20))(local_74,local_6c,&local_5c,&local_60);
  (**(code **)(*(int *)pWVar2 + 0x20))
            (*(float *)this->craft->_padding_ + local_74,local_6c,&local_68,local_78);
  Graphic_Circle(DisplayInterface::currentBuffer,local_5c,local_60,local_68 - local_5c,0x18,
                 DisplayInterface::colorGreen,SOLID_PIXELS);
  if (this->task != (AiTask *)0x0) {
    (**(code **)(this->task->_padding_ + 0x20))();
  }
  return;
}
