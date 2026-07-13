/*
 * Entry: 004693cf
 * Name: UnitProcess::DrawStateA
 * Namespace: UnitProcess
 * Signature: void DrawStateA(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall UnitProcess::DrawStateA(UnitProcess *this)

{
  VEHICLE *pVVar1;
  WorldInterface *pWVar2;
  char *pcVar3;
  GameObject *pGVar4;
  undefined4 *puVar5;
  float fVar6;
  char *local_80 [4];
  UnitProcess *local_70;
  long local_6c;
  WorldInterface *local_68;
  long local_64;
  long local_60;
  long local_5c;
  char local_58 [80];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_70 = this;
  local_68 = (WorldInterface *)(**(code **)(this->me->_padding_ + 0x30))();
  pVVar1 = this->me->vhcl;
  sprintf(local_58," UnitProcess:");
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," ID (%s) Seqno (%d)",local_68 + 1,this->me->_padding_);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  fVar6 = Get_Time();
  sprintf(local_58," Time (%.2f)",(double)fVar6);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," State (%s)",stateText[this->curState]);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," SaveState (%s)",stateText[this->saveState]);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," Priority (%d)",this->me->_padding_);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  local_80[0] = " undeployed";
  local_80[1] = " deploying";
  local_80[2] = " deployed";
  local_80[3] = " undeploying";
  sprintf(local_58,local_80[this->me->state]);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," Steer (%+.2f)",(double)(pVVar1->control).steer);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," Braccel (%+.2f)",(double)(pVVar1->control).braccel);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," Pitch (%+.2f) Strafe (%+.2f)",(double)(pVVar1->control).pitch,
          (double)(pVVar1->control).strafe);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  pcVar3 = "off";
  if ((pVVar1->control).turbo != 0) {
    pcVar3 = "on";
  }
  sprintf(local_58," Turbo (%s) Jump (%s)",pcVar3);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  (**(code **)(this->me->_padding_ + 4))();
  sprintf(local_58," Team (%d)");
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," Perceived Team (%d)",this->me->_padding_);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  pGVar4 = GameObjectHandle::GetObj(this->whoHandle);
  if (pGVar4 != (GameObject *)0x0) {
    if (pGVar4->label != (char *)0x0) {
      sprintf(local_58," Who (%s)");
      DisplayInterface::DrawTextA
                (local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    }
    local_68 = WorldInterface::currentDisplay;
    local_64 = DisplayInterface::textLeft;
    local_60 = DisplayInterface::textTop;
    puVar5 = (undefined4 *)(**(code **)(pGVar4->_padding_ + 0xc))();
    local_80[1] = (char *)*puVar5;
    local_80[2] = (char *)puVar5[1];
    local_80[3] = (char *)puVar5[2];
    (**(code **)(*(int *)local_68 + 0x20))(local_80[1],local_80[3],&local_5c);
    Graphic_Line(DisplayInterface::currentBuffer,local_64,local_60,local_5c,local_6c,
                 DisplayInterface::colorWhite,SOLID_PIXELS);
    this = local_70;
  }
  pGVar4 = GameObjectHandle::GetObj(this->saveWho);
  if (pGVar4 != (GameObject *)0x0) {
    if (pGVar4->label != (char *)0x0) {
      sprintf(local_58," Save Who (%s)");
      DisplayInterface::DrawTextA
                (local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    }
    pWVar2 = WorldInterface::currentDisplay;
    local_6c = DisplayInterface::textLeft;
    local_5c = DisplayInterface::textTop;
    puVar5 = (undefined4 *)(**(code **)(pGVar4->_padding_ + 0xc))();
    local_80[1] = (char *)*puVar5;
    local_80[2] = (char *)puVar5[1];
    local_80[3] = (char *)puVar5[2];
    (**(code **)(*(int *)pWVar2 + 0x20))(local_80[1],local_80[3],&local_60);
    Graphic_Line(DisplayInterface::currentBuffer,local_6c,local_5c,local_60,local_64,
                 DisplayInterface::colorWhite,SOLID_PIXELS);
    this = local_70;
  }
  if (this->task != (AiTask *)0x0) {
    (**(code **)(this->task->_padding_ + 0x20))();
  }
  return;
}
