/*
 * Entry: 004d67cd
 * Name: EmptyDrawState
 * Namespace: Global
 * Signature: void EmptyDrawState(GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl EmptyDrawState(GameObject *param_1)

{
  undefined1 *this;
  byte bVar1;
  char cVar2;
  ushort uVar3;
  int iVar4;
  char *pcVar5;
  NetDisplayObject *unaff_EDI;
  float fVar6;
  undefined8 uVar7;
  char local_58 [80];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  this = &unaff_EDI->field_0x20;
  iVar4 = (**(code **)(*(int *)this + 0x30))();
  sprintf(local_58," EmptyDrawState");
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," ID (%s) Seqno (%d)",iVar4 + 8,*(undefined4 *)&unaff_EDI->field_0x150);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  fVar6 = Get_Time();
  sprintf(local_58," Time (%f)",(double)fVar6);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  (**(code **)(*(int *)this + 4))();
  sprintf(local_58," Team (%d)");
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," Perceived Team (%d)",*(undefined4 *)&unaff_EDI->field_0x174);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," Flags (0x%x)",*(undefined4 *)(iVar4 + 0x14));
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," Current Health (%d)",(double)*(float *)&unaff_EDI->field_0x1fc);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  iVar4 = *(int *)(iVar4 + 0xac);
  if (iVar4 == 1) {
LAB_004d6931:
    iVar4 = *(int *)&unaff_EDI[1].field_0x8;
  }
  else {
    if (iVar4 != 3) {
      if ((iVar4 != 4) && (iVar4 != 6)) goto LAB_004d6a7f;
      goto LAB_004d6931;
    }
    iVar4 = *(int *)(unaff_EDI + 1);
  }
  if (iVar4 != 0) {
    sprintf(local_58," Vhcl Flags (0x%x)");
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    sprintf(local_58," Timer (%f)",(double)*(float *)(iVar4 + 0x108));
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    sprintf(local_58," Braccel: (%f)",(double)*(float *)(iVar4 + 0xd0));
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    sprintf(local_58," Steer: (%f)",(double)*(float *)(iVar4 + 0xc4));
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    sprintf(local_58," Strafe: (%f)",(double)*(float *)(iVar4 + 0xcc));
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    sprintf(local_58," Pitch: (%f)",(double)*(float *)(iVar4 + 200));
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    sprintf(local_58," Turbo: (%f)",*(undefined4 *)(iVar4 + 0xd4));
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  }
LAB_004d6a7f:
  iVar4 = Net_IsNetGame();
  if (iVar4 != 0) {
    sprintf(local_58," Received (%f)",(double)*(float *)&unaff_EDI->field_0x98);
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    sprintf(local_58," Sent (%f)",(double)*(float *)&unaff_EDI->field_0x8c);
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    bVar1 = unaff_EDI->field_0x80;
    cVar2 = NetDisplayObject::o_type(unaff_EDI);
    uVar7 = CONCAT44((int)cVar2,(uint)bVar1);
    uVar3 = DistributedObject::GetPlayerID((DistributedObject *)this);
    pcVar5 = NetPlayer_GetPlayerName(uVar3);
    sprintf(local_58," %s User (%d) Type (%c)",pcVar5,uVar7);
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    DistributedObject::GetID((DistributedObject *)this);
    uVar3 = DistributedObject::GetPlayerID((DistributedObject *)this);
    sprintf(local_58," PlayerID (%lu) ID (%lu)",(uint)uVar3);
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  }
  return;
}
