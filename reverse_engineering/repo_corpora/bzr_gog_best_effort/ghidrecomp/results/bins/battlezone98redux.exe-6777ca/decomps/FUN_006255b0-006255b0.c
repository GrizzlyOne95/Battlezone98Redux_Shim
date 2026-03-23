
void FUN_006255b0(undefined4 *param_1)

{
  uint *puVar1;
  double in_stack_00000030;
  double in_stack_00000038;
  double in_stack_00000040;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 local_50 [16];
  double local_40;
  double local_38;
  double local_30;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined2 local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = (uint *)FUN_0081f1e0(local_50,&stack0x00000008);
  local_18 = *puVar1;
  local_14 = puVar1[1];
  local_10 = puVar1[2];
  local_c = (float)puVar1[3];
  FUN_004dead0(&local_18);
  if (local_c < 0.0) {
    local_c = -local_c;
    local_18 = local_18 ^ 0x80000000;
    local_14 = local_14 ^ 0x80000000;
    local_10 = local_10 ^ 0x80000000;
  }
  FUN_00625310();
  FUN_00625310();
  FUN_00625310();
  in_stack_00000030 = in_stack_00000030 - (double)(DAT_02cd912c + DAT_02cd9124) * 0.5;
  in_stack_00000038 = in_stack_00000038 - (double)DAT_02ce99cc;
  in_stack_00000040 = in_stack_00000040 - (double)(DAT_02cd9130 + DAT_02cd9128) * 0.5;
  uVar4 = 0x18;
  uVar3 = 0x2d;
  puVar2 = &local_28;
  local_38 = in_stack_00000030 * 1024.0 + 0.5;
  floor(local_38);
  FUN_0083f040(puVar2,uVar3,uVar4);
  FUN_00625310();
  uVar4 = 0x13;
  uVar3 = 0x45;
  puVar2 = &local_28;
  local_40 = in_stack_00000038 * 1024.0 + 0.5;
  floor(local_40);
  FUN_0083f040(puVar2,uVar3,uVar4);
  FUN_00625370();
  uVar4 = 0x18;
  uVar3 = 0x58;
  puVar2 = &local_28;
  local_30 = in_stack_00000040 * 1024.0 + 0.5;
  floor(local_30);
  FUN_0083f040(puVar2,uVar3,uVar4);
  FUN_00625310();
  *param_1 = local_28;
  param_1[1] = local_24;
  param_1[2] = local_20;
  *(undefined2 *)(param_1 + 3) = local_1c;
  FUN_0083e885();
  return;
}

