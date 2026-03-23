
void __fastcall FUN_00581940(int param_1)

{
  int iVar1;
  undefined1 uVar2;
  int iVar3;
  uint uVar4;
  float10 fVar5;
  char local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = *(int *)(param_1 + 0xc);
  iVar3 = (**(code **)(*(int *)(iVar1 + 0x18) + 0x30))();
  sprintf(local_58," NetProcess:");
  FUN_004b70f0();
  FUN_00462450();
  sprintf(local_58," ID (%s) Seqno (%d)",iVar3 + 8);
  FUN_004b70f0();
  (**(code **)(*(int *)(iVar1 + 0x18) + 4))();
  sprintf(local_58," Team (%d)");
  FUN_004b70f0();
  FUN_004625b0();
  sprintf(local_58," Perceived Team (%d)");
  FUN_004b70f0();
  fVar5 = (float10)FUN_00822da0();
  fVar5 = (float10)FUN_00822d80((double)fVar5);
  sprintf(local_58," Time (%f) Local (%f)",(double)fVar5);
  FUN_004b70f0();
  fVar5 = (float10)FUN_00822d60();
  sprintf(local_58," Time Step (%f)",(double)fVar5);
  FUN_004b70f0();
  fVar5 = (float10)FUN_00581830();
  sprintf(local_58," Received (%f)",(double)fVar5);
  FUN_004b70f0();
  fVar5 = (float10)FUN_00581780();
  sprintf(local_58," Sent (%f)",(double)fVar5);
  FUN_004b70f0();
  FUN_00581870();
  uVar2 = FUN_00581850();
  FUN_004b9800(uVar2);
  FUN_005779d0();
  sprintf(local_58," %s User (%d) Type (%c)");
  FUN_004b70f0();
  FUN_004b9a90();
  uVar4 = FUN_004b9800();
  sprintf(local_58," PlayerID (%lu) ID (%lu)",uVar4 & 0xffff);
  FUN_004b70f0();
  sprintf(local_58," Flags (0x%x)");
  FUN_004b70f0();
  fVar5 = (float10)FUN_0046fbd0();
  sprintf(local_58," Current Health (%f)",(double)fVar5);
  FUN_004b70f0();
  switch(*(undefined4 *)(iVar3 + 0x84)) {
  case 1:
  case 4:
  case 6:
    sprintf(local_58," Vhcl Flags (0x%x) Timer (%f)");
    FUN_004b70f0();
    break;
  case 3:
    sprintf(local_58," Vhcl Flags (0x%x)");
    FUN_004b70f0();
  }
  FUN_0083e885();
  return;
}

