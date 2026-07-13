/*
 * Entry: 0044d7c0
 * Name: NetProcess::DrawStateA
 * Namespace: NetProcess
 * Signature: void DrawStateA(NetProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall NetProcess::DrawStateA(NetProcess *this)

{
  undefined1 *this_00;
  NetGameObject *this_01;
  ushort uVar1;
  int iVar2;
  float fVar3;
  double dVar4;
  char local_58 [80];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  this_01 = *(NetGameObject **)&this->field_0xc;
  this_00 = &this_01->field_0x20;
  iVar2 = (**(code **)(*(int *)this_00 + 0x30))();
  sprintf(local_58," NetProcess:");
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," ID (%s) Seqno (%d)",iVar2 + 8,*(undefined4 *)&this_01->field_0x150);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  (**(code **)(*(int *)this_00 + 4))();
  sprintf(local_58," Team (%d)");
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," Perceived Team (%d)",*(undefined4 *)&this_01->field_0x174);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  fVar3 = Get_TimeLocal();
  dVar4 = (double)fVar3;
  fVar3 = Get_Time();
  sprintf(local_58," Time (%f) Local (%f)",(double)fVar3,dVar4);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  fVar3 = TimeStep();
  sprintf(local_58," Time Step (%f)",(double)fVar3);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," Received (%f)",(double)*(float *)&this_01->field_0x98);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," Sent (%f)",(double)*(float *)&this_01->field_0x8c);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  NetGameObject::o_type(this_01);
  uVar1 = DistributedObject::GetPlayerID((DistributedObject *)this_00);
  NetPlayer_GetPlayerName(uVar1);
  sprintf(local_58," %s User (%d) Type (%c)");
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  DistributedObject::GetID((DistributedObject *)this_00);
  uVar1 = DistributedObject::GetPlayerID((DistributedObject *)this_00);
  sprintf(local_58," PlayerID (%lu) ID (%lu)",(uint)uVar1);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," Flags (0x%x)",*(undefined4 *)(iVar2 + 0x14));
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," Current Health (%d)",(double)*(float *)&this_01->field_0x1fc);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  iVar2 = *(int *)(iVar2 + 0xac);
  if (iVar2 != 1) {
    if (iVar2 == 3) {
      sprintf(local_58," Vhcl Flags (0x%x)");
      DisplayInterface::DrawTextA
                (local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
      return;
    }
    if ((iVar2 != 4) && (iVar2 != 6)) {
      return;
    }
  }
  sprintf(local_58," Vhcl Flags (0x%x) Timer (%f)");
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  return;
}
