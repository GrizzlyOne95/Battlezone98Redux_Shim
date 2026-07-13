
void __fastcall FUN_005c3a50(int param_1)

{
  float *pfVar1;
  float10 fVar2;
  undefined1 local_94 [4];
  int local_90;
  undefined4 local_8c;
  int local_88;
  undefined4 local_84;
  int local_80;
  int local_7c;
  undefined *local_78;
  undefined *local_74;
  int *local_70;
  float *local_6c;
  int local_68;
  float local_64;
  float local_60;
  float local_5c;
  char local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_68 = param_1;
  local_80 = (**(code **)(*(int *)(*(int *)(param_1 + 0x28) + 0x18) + 0x30))();
  local_6c = (float *)(*(int *)(*(int *)(local_68 + 0x28) + 0x230) + 0xc4);
  sprintf(local_58," ScavengerProcess:");
  FUN_004b70f0();
  FUN_00462450();
  sprintf(local_58," ID (%s) Seqno (%d)",local_80 + 8);
  FUN_004b70f0();
  sprintf(local_58," State (%s)");
  FUN_004b70f0();
  sprintf(local_58," Steer (%+.2f)",(double)*local_6c);
  FUN_004b70f0();
  sprintf(local_58," Braccel (%+.2f)",(double)local_6c[3]);
  FUN_004b70f0();
  sprintf(local_58," Pitch (%+.2f) Strafe (%+.2f)",(double)local_6c[1],(double)local_6c[2]);
  FUN_004b70f0();
  if (local_6c[5] == 0.0) {
    local_74 = &DAT_008865a8;
  }
  else {
    local_74 = &DAT_00886520;
  }
  if (local_6c[4] == 0.0) {
    local_78 = &DAT_008865a8;
  }
  else {
    local_78 = &DAT_00886520;
  }
  sprintf(local_58," Turbo (%s) Jump (%s)",local_78,local_74);
  FUN_004b70f0();
  if (*(int *)(local_68 + 0x1c) == 1) {
    sprintf(local_58," Wait Time (%.2f)",(double)*(float *)(local_68 + 0x44));
    FUN_004b70f0();
    fVar2 = (float10)FUN_00822d80();
    sprintf(local_58," Get Time (%.2f)",(double)fVar2);
    FUN_004b70f0();
  }
  local_70 = DAT_00917554;
  local_8c = 0x18;
  pfVar1 = (float *)(**(code **)(*(int *)(*(int *)(local_68 + 0x28) + 0x18) + 0xc))();
  local_64 = *pfVar1;
  local_60 = pfVar1[1];
  local_5c = pfVar1[2];
  (**(code **)(*local_70 + 0x24))(local_64,local_5c,&local_7c,&local_84);
  pfVar1 = (float *)FUN_00492d40();
  local_64 = local_64 + *pfVar1;
  (**(code **)(*local_70 + 0x24))(local_64,local_5c,&local_90,local_94);
  local_88 = local_90 - local_7c;
  FUN_0068ad00(DAT_00917580,local_7c,local_84,local_88,local_8c,DAT_009175b0,0);
  if (*(int *)(local_68 + 0x58) != 0) {
    (**(code **)(**(int **)(local_68 + 0x58) + 0x20))();
  }
  FUN_0083e885();
  return;
}

