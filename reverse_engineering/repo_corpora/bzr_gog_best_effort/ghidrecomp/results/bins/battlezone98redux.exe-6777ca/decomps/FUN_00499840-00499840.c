
void __thiscall FUN_00499840(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_158 [64];
  undefined4 *local_118;
  undefined4 *local_114;
  int local_110;
  undefined4 local_10c;
  undefined4 local_108 [16];
  undefined4 local_c8 [16];
  undefined4 local_88 [16];
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_10c = param_1;
  for (; param_2 != 0; param_2 = *(int *)(param_2 + 0x7c)) {
    if (param_3 == 0) {
      puVar1 = (undefined4 *)(param_2 + 0x20);
      puVar3 = local_c8;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      local_114 = local_c8;
    }
    else {
      puVar1 = (undefined4 *)FUN_0081fe60(local_158,param_2 + 0x20,param_3);
      puVar3 = local_88;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar1 = local_88;
      puVar3 = local_108;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      local_114 = local_108;
    }
    local_118 = local_114;
    puVar1 = local_114;
    puVar3 = local_48;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    local_110 = FUN_0043fff0(param_2);
    if (local_110 < 0x4001) {
      if (local_110 == 0x4000) {
        FUN_00499ab0(param_2 + 0xa0,*(undefined4 *)(param_2 + 0xac),local_48,param_4);
      }
      else if (local_110 == 0x2000) {
        FUN_00499b80(param_2 + 0xb0,param_2 + 0xbc,local_48,param_4);
      }
      else if (local_110 == 0x3000) {
        FUN_00499b80(param_2 + 0xb0,param_2 + 0xbc,local_48,DAT_00917588);
        FUN_00499ab0(param_2 + 0xa0,*(undefined4 *)(param_2 + 0xac),local_48,DAT_00917570);
        FUN_00499e40(*(undefined4 *)(param_2 + 0x9c),local_48,param_4);
      }
    }
    else if (local_110 == 0x5000) {
      FUN_00499ab0(param_2 + 0xa0,*(float *)(param_2 + 0xac) * 0.75,local_48,param_4);
    }
    if (*(int *)(param_2 + 0x80) != 0) {
      FUN_00499840(*(undefined4 *)(param_2 + 0x80),local_48,param_4);
    }
  }
  FUN_0083e885();
  return;
}

