
/* WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */
/* WARNING: Type propagation algorithm not settling */

void FUN_00441ef0(int param_1,undefined4 param_2,int param_3,int param_4,int *param_5,
                 undefined4 *param_6)

{
  uint uVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  undefined4 *puVar6;
  uint auStack_258 [13];
  uint auStack_224 [4];
  undefined1 local_20c [72];
  undefined1 local_1c4 [72];
  undefined1 local_17c [64];
  undefined1 local_13c [64];
  undefined1 local_fc [12];
  undefined1 local_f0 [12];
  undefined1 local_e4 [12];
  undefined1 local_d8 [12];
  undefined1 local_cc [12];
  undefined1 local_c0 [12];
  undefined1 local_b4 [12];
  undefined1 *local_a8;
  int local_a4;
  undefined1 *local_a0;
  uint local_9c;
  uint *local_98;
  uint local_94;
  undefined4 local_90;
  int local_8c;
  int local_88;
  int local_84;
  uint local_80;
  uint local_7c;
  int local_78;
  int local_74;
  int local_70;
  undefined4 local_6c [16];
  int local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  int local_1c;
  int local_18;
  int local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_98 = *(uint **)(param_1 + 0x9c);
  local_9c = local_98[1];
  uVar1 = *local_98;
  auStack_224[3] = 0x441f31;
  local_a8 = local_20c + uVar1 * -0xc + -8;
  local_a0 = local_20c + uVar1 * -0xc + -8;
  auStack_224[uVar1 * -3 + 3] = param_3 + 0x38;
  auStack_224[uVar1 * -3 + 2] = (uint)local_13c;
  auStack_224[uVar1 * 0xfffffffd + 1] = 0x441f56;
  puVar2 = (undefined4 *)FUN_008203f0();
  puVar6 = local_6c;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar6 = puVar6 + 1;
  }
  auStack_224[uVar1 * -3 + 3] = (uint)local_6c;
  auStack_224[uVar1 * -3 + 2] = param_2;
  auStack_224[uVar1 * 0xfffffffd + 1] = (uint)local_17c;
  auStack_224[uVar1 * -3] = 0x441f79;
  puVar2 = (undefined4 *)FUN_0081fe60();
  puVar6 = local_6c;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar6 = puVar6 + 1;
  }
  auStack_224[uVar1 * -3 + 3] = (uint)local_6c;
  auStack_224[uVar1 * -3 + 2] = *local_98;
  auStack_224[uVar1 * 0xfffffffd + 1] = local_9c;
  auStack_224[uVar1 * -3] = (uint)local_a0;
  auStack_258[uVar1 * -3 + 0xc] = 0x441fa8;
  FUN_00820180();
  *param_5 = 0;
  param_5[0x14] = param_4;
  for (local_94 = 0; local_94 < *local_98; local_94 = local_94 + 1) {
    auStack_224[uVar1 * -3 + 3] = param_1;
    puVar2 = (undefined4 *)(local_94 * 0xc + local_9c);
    auStack_224[uVar1 * -3] = *puVar2;
    auStack_224[uVar1 * 0xfffffffd + 1] = puVar2[1];
    auStack_224[uVar1 * -3 + 2] = puVar2[2];
    auStack_258[uVar1 * -3 + 0xc] = (uint)local_c0;
    auStack_258[uVar1 * -3 + 0xb] = 0x442022;
    piVar3 = (int *)FUN_00444ba0();
    local_78 = *piVar3;
    local_74 = piVar3[1];
    local_70 = piVar3[2];
    auStack_224[uVar1 * 0xfffffffd + 1] = *(undefined4 *)(param_3 + 0xc);
    auStack_224[uVar1 * -3 + 2] = *(uint *)(param_3 + 0x10);
    auStack_224[uVar1 * -3 + 3] = *(uint *)(param_3 + 0x14);
    auStack_258[uVar1 * -3 + 0xb] = local_78;
    auStack_258[uVar1 * -3 + 0xc] = local_74;
    auStack_224[uVar1 * -3] = local_70;
    auStack_258[uVar1 * -3 + 10] = (uint)local_f0;
    auStack_258[uVar1 * -3 + 9] = 0x442073;
    piVar3 = (int *)FUN_004401a0();
    local_78 = *piVar3;
    local_74 = piVar3[1];
    local_70 = piVar3[2];
    auStack_224[uVar1 * -3 + 3] = param_3 + 0x38;
    auStack_224[uVar1 * -3 + 2] = (uint)&local_78;
    auStack_224[uVar1 * 0xfffffffd + 1] = (uint)local_b4;
    auStack_224[uVar1 * -3] = 0x44209e;
    piVar3 = (int *)FUN_00440300();
    local_14 = *piVar3;
    local_10 = piVar3[1];
    local_c = piVar3[2];
    puVar2 = (undefined4 *)(local_a0 + local_94 * 0xc);
    local_20 = *puVar2;
    local_1c = puVar2[1];
    local_18 = puVar2[2];
    auStack_224[uVar1 * -3 + 3] = local_18;
    auStack_224[uVar1 * -3 + 3] = 0;
    auStack_224[uVar1 * -3 + 2] = (uint)&local_2c;
    auStack_224[uVar1 * 0xfffffffd + 1] = (uint)&local_a4;
    auStack_224[uVar1 * -3] = (uint)param_5;
    auStack_224[uVar1 * -3] = param_5[0x14];
    auStack_258[uVar1 * -3 + 7] = *(undefined4 *)(param_3 + 0x20);
    auStack_258[uVar1 * -3 + 8] = *(int *)(param_3 + 0x24);
    auStack_258[uVar1 * -3 + 9] = *(int *)(param_3 + 0x28);
    auStack_258[uVar1 * -3 + 10] = *(int *)(param_3 + 0x2c);
    auStack_258[uVar1 * -3 + 0xb] = *(int *)(param_3 + 0x30);
    auStack_258[uVar1 * -3 + 0xc] = *(int *)(param_3 + 0x34);
    auStack_258[uVar1 * -3 + 1] = local_20;
    auStack_258[uVar1 * -3 + 2] = local_1c;
    auStack_258[uVar1 * -3 + 3] = local_18;
    auStack_258[uVar1 * -3 + 4] = local_14;
    auStack_258[uVar1 * -3 + 5] = local_10;
    auStack_258[uVar1 * -3 + 6] = local_c;
    auStack_258[uVar1 * -3] = 0x442151;
    iVar4 = FUN_00445d90();
    if (iVar4 != 0) {
      *param_5 = 1;
      piVar3 = (int *)(local_94 * 0xc + local_9c);
      param_5[0x15] = *piVar3;
      param_5[0x16] = piVar3[1];
      param_5[0x17] = piVar3[2];
      param_5[0x18] = local_78;
      param_5[0x19] = local_74;
      param_5[0x1a] = local_70;
      param_5[0x14] = local_a4;
      param_5[0x1b] = local_2c;
      param_5[0x1c] = local_28;
      param_5[0x1d] = local_24;
      local_90 = local_20;
      local_8c = local_1c;
      local_88 = local_18;
      local_84 = local_14;
      local_80 = local_10;
      local_7c = local_c;
    }
  }
  if (*param_5 != 0) {
    param_5[1] = *(int *)(param_3 + 0x1c);
    auStack_224[uVar1 * -3 + 3] = *(undefined4 *)(param_3 + 0x1c);
    auStack_224[uVar1 * -3 + 2] = (uint)local_1c4;
    auStack_224[uVar1 * 0xfffffffd + 1] = 0x442223;
    piVar3 = (int *)FUN_0062bf70();
    piVar5 = param_5 + 2;
    for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1) {
      *piVar5 = *piVar3;
      piVar3 = piVar3 + 1;
      piVar5 = piVar5 + 1;
    }
    *param_6 = 1;
    param_6[1] = param_1;
    auStack_224[uVar1 * -3 + 3] = param_1;
    auStack_224[uVar1 * -3 + 2] = (uint)local_20c;
    auStack_224[uVar1 * 0xfffffffd + 1] = 0x442257;
    puVar2 = (undefined4 *)FUN_0062bf70();
    puVar6 = param_6 + 2;
    for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar6 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar6 = puVar6 + 1;
    }
    param_6[0x14] = param_5[0x14];
    auStack_224[uVar1 * 0xfffffffd + 1] = local_84;
    auStack_224[uVar1 * -3 + 2] = local_80;
    auStack_224[uVar1 * -3 + 3] = local_7c;
    auStack_224[uVar1 * -3] = (uint)(auStack_224 + uVar1 * 0xfffffffd + 1);
    auStack_224[uVar1 * -3] = param_6[0x14];
    auStack_258[uVar1 * -3 + 10] = local_90;
    auStack_258[uVar1 * -3 + 0xb] = local_8c;
    auStack_258[uVar1 * -3 + 0xc] = local_88;
    auStack_258[uVar1 * -3 + 9] = (uint)local_cc;
    auStack_258[uVar1 * -3 + 8] = 0x4422c4;
    puVar2 = (undefined4 *)FUN_00439d00();
    param_6[0x15] = *puVar2;
    param_6[0x16] = puVar2[1];
    param_6[0x17] = puVar2[2];
    param_6[0x18] = param_5[0x18];
    param_6[0x19] = param_5[0x19];
    param_6[0x1a] = param_5[0x1a];
    auStack_224[uVar1 * 0xfffffffd + 1] = param_5[0x18];
    auStack_224[uVar1 * -3 + 2] = param_5[0x19];
    auStack_224[uVar1 * -3 + 3] = param_5[0x1a];
    auStack_224[uVar1 * -3] = (uint)local_e4;
    auStack_258[uVar1 * -3 + 0xc] = 0x442320;
    piVar3 = (int *)FUN_00440060();
    param_5[0x18] = *piVar3;
    param_5[0x19] = piVar3[1];
    param_5[0x1a] = piVar3[2];
    auStack_224[uVar1 * -3 + 3] = param_3 + 0x38;
    auStack_224[uVar1 * -3 + 2] = (uint)(param_5 + 0x1b);
    auStack_224[uVar1 * 0xfffffffd + 1] = (uint)local_d8;
    auStack_224[uVar1 * -3] = 0x442353;
    piVar3 = (int *)FUN_00440210();
    param_5[0x1b] = *piVar3;
    param_5[0x1c] = piVar3[1];
    param_5[0x1d] = piVar3[2];
    auStack_224[uVar1 * 0xfffffffd + 1] = param_5[0x1b];
    auStack_224[uVar1 * -3 + 2] = param_5[0x1c];
    auStack_224[uVar1 * -3 + 3] = param_5[0x1d];
    auStack_224[uVar1 * -3] = (uint)local_fc;
    auStack_258[uVar1 * -3 + 0xc] = 0x442393;
    puVar2 = (undefined4 *)FUN_00440060();
    param_6[0x1b] = *puVar2;
    param_6[0x1c] = puVar2[1];
    param_6[0x1d] = puVar2[2];
  }
  FUN_0083e885();
  return;
}

