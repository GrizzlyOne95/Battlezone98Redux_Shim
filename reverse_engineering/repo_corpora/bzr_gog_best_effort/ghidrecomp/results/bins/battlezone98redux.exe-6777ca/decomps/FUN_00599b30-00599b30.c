
void FUN_00599b30(int param_1)

{
  undefined1 uVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  float10 fVar6;
  int local_5c;
  char local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar3 = (**(code **)(*(int *)(param_1 + 0x18) + 0x30))();
  sprintf(local_58," EmptyDrawState");
  FUN_004b70f0(local_58,DAT_0091755c,DAT_00917584);
  uVar4 = FUN_00462450();
  sprintf(local_58," ID (%s) Seqno (%d)",iVar3 + 8,uVar4);
  FUN_004b70f0(local_58,DAT_0091755c,DAT_00917584);
  fVar6 = (float10)FUN_00822d80();
  sprintf(local_58," Time (%f)",(double)fVar6);
  FUN_004b70f0(local_58,DAT_0091755c);
  (**(code **)(*(int *)(param_1 + 0x18) + 4))();
  sprintf(local_58," Team (%d)");
  FUN_004b70f0(local_58,DAT_0091755c);
  FUN_004625b0();
  sprintf(local_58," Perceived Team (%d)");
  FUN_004b70f0(local_58,DAT_0091755c);
  sprintf(local_58," Flags (0x%x)");
  FUN_004b70f0(local_58,DAT_0091755c,DAT_00917584);
  fVar6 = (float10)FUN_0046fbd0();
  sprintf(local_58," Current Health (%f)",(double)fVar6);
  FUN_004b70f0(local_58,DAT_0091755c);
  local_5c = 0;
  switch(*(undefined4 *)(iVar3 + 0x84)) {
  case 1:
  case 4:
  case 6:
    local_5c = *(int *)(param_1 + 0x230);
    break;
  case 3:
    local_5c = *(int *)(param_1 + 0x228);
  }
  if (local_5c != 0) {
    sprintf(local_58," Vhcl Flags (0x%x)");
    FUN_004b70f0(local_58,DAT_0091755c,DAT_00917584);
    sprintf(local_58," Timer (%f)",(double)*(float *)(local_5c + 0x110));
    FUN_004b70f0(local_58,DAT_0091755c,DAT_00917584);
    sprintf(local_58," Braccel: (%f)",(double)*(float *)(local_5c + 0xd0));
    FUN_004b70f0(local_58,DAT_0091755c,DAT_00917584);
    sprintf(local_58," Steer: (%f)",(double)*(float *)(local_5c + 0xc4));
    FUN_004b70f0(local_58,DAT_0091755c,DAT_00917584);
    sprintf(local_58," Strafe: (%f)",(double)*(float *)(local_5c + 0xcc));
    FUN_004b70f0(local_58,DAT_0091755c,DAT_00917584);
    sprintf(local_58," Pitch: (%f)",(double)*(float *)(local_5c + 200));
    FUN_004b70f0(local_58,DAT_0091755c);
    sprintf(local_58," Turbo: (%lu)");
    FUN_004b70f0(local_58,DAT_0091755c,DAT_00917584);
  }
  iVar3 = FUN_00572a70();
  if (iVar3 != 0) {
    fVar6 = (float10)FUN_00581830();
    sprintf(local_58," Received (%f)",(double)fVar6);
    FUN_004b70f0(local_58,DAT_0091755c,DAT_00917584);
    fVar6 = (float10)FUN_00581780();
    sprintf(local_58," Sent (%f)",(double)fVar6);
    FUN_004b70f0(local_58,DAT_0091755c,DAT_00917584);
    FUN_00581870();
    uVar1 = FUN_00581850();
    uVar2 = FUN_004b9800(uVar1);
    uVar4 = FUN_005779d0(uVar2);
    sprintf(local_58," %s User (%d) Type (%c)",uVar4);
    FUN_004b70f0(local_58,DAT_0091755c,DAT_00917584);
    FUN_004b9a90();
    uVar5 = FUN_004b9800();
    sprintf(local_58," PlayerID (%lu) ID (%lu)",uVar5 & 0xffff);
    FUN_004b70f0(local_58,DAT_0091755c,DAT_00917584);
  }
  FUN_0083e885();
  return;
}

