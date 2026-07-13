
void __thiscall FUN_005aef60(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  float *pfVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined1 local_1d4 [64];
  undefined1 local_194 [64];
  undefined1 local_154 [12];
  undefined1 local_148 [12];
  int local_13c;
  undefined4 local_138 [16];
  undefined4 local_f8 [16];
  undefined4 local_b8 [10];
  double local_90;
  double local_88;
  double local_80;
  undefined4 local_78 [10];
  double local_50;
  double local_48;
  double local_40;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_13c = param_1;
  if (*(int *)(*(int *)(param_1 + 0x300) + 0x1c) == 3) {
    puVar1 = (undefined4 *)FUN_0062e070(local_194,*(undefined4 *)(param_1 + 0x36c),0);
    puVar5 = local_138;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar5 = puVar5 + 1;
    }
    puVar1 = local_138;
    puVar5 = local_b8;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar5 = puVar5 + 1;
    }
    uVar2 = FUN_0049c590(local_b8);
    pfVar3 = (float *)FUN_00440210(local_154,uVar2);
    local_2c = *pfVar3;
    local_28 = pfVar3[1];
    local_24 = pfVar3[2];
    local_38 = local_2c;
    local_34 = local_28;
    local_30 = local_24;
    local_90 = local_90 - (double)local_2c;
    local_88 = local_88 - (double)local_28;
    local_80 = local_80 - (double)local_24;
    puVar1 = local_b8;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *param_2 = *puVar1;
      puVar1 = puVar1 + 1;
      param_2 = param_2 + 1;
    }
  }
  else {
    puVar1 = (undefined4 *)FUN_0062e070(local_1d4,*(undefined4 *)(param_1 + 0x368),0);
    puVar5 = local_f8;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar5 = puVar5 + 1;
    }
    puVar1 = local_f8;
    puVar5 = local_78;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar5 = puVar5 + 1;
    }
    uVar2 = FUN_0049c590(local_78);
    pfVar3 = (float *)FUN_00440210(local_148,uVar2);
    local_20 = *pfVar3;
    local_1c = pfVar3[1];
    local_18 = pfVar3[2];
    local_14 = local_20;
    local_10 = local_1c;
    local_c = local_18;
    local_50 = local_50 - (double)local_20;
    local_48 = local_48 - (double)local_1c;
    local_40 = local_40 - (double)local_18;
    puVar1 = local_78;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *param_2 = *puVar1;
      puVar1 = puVar1 + 1;
      param_2 = param_2 + 1;
    }
  }
  FUN_0083e885();
  return;
}

