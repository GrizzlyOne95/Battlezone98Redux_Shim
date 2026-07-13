
void __thiscall FUN_0047df00(int param_1,float param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_120 [64];
  undefined1 local_e0 [24];
  undefined1 local_c8 [12];
  undefined1 local_bc [12];
  float local_b0;
  int local_ac;
  undefined4 local_a8 [16];
  undefined1 local_68 [12];
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 uStack_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (*(float *)(param_1 + 0x78) <= param_2 && param_2 != *(float *)(param_1 + 0x78)) {
    param_2 = *(float *)(param_1 + 0x78);
  }
  local_ac = param_1;
  if ((*(uint *)(*(int *)(param_1 + 0x14) + 0x14) & 8) == 0) {
    puVar1 = (undefined4 *)FUN_00440000(local_bc,0,0,0);
    local_2c = *puVar1;
    local_28 = puVar1[1];
    local_24 = puVar1[2];
    *(undefined4 *)(local_ac + 0x30) = local_2c;
    *(undefined4 *)(local_ac + 0x34) = local_28;
    *(undefined4 *)(local_ac + 0x38) = local_24;
    *(undefined4 *)(local_ac + 0x20) = 0;
    *(undefined4 *)(local_ac + 0x24) = 0x7149f2ca;
    puVar1 = (undefined4 *)FUN_00447f60(local_e0,*(int *)(local_ac + 0x14) + 0x20);
    local_50 = *puVar1;
    local_4c = puVar1[1];
    local_48 = puVar1[2];
    local_44 = puVar1[3];
    local_40 = puVar1[4];
    local_3c = puVar1[5];
    local_20 = local_50;
    uStack_1c = local_4c;
    local_18 = local_48;
    local_14 = local_44;
    local_10 = local_40;
    uStack_c = local_3c;
    FUN_004451d0(local_50,local_4c,local_48,local_44,local_40,local_3c,&local_b0,local_68);
    puVar1 = (undefined4 *)FUN_004560b0(local_c8,*(int *)(local_ac + 0x14) + 0x20);
    local_5c = *puVar1;
    local_58 = puVar1[1];
    local_54 = puVar1[2];
    local_38 = local_5c;
    local_34 = local_58;
    local_30 = local_54;
    puVar1 = (undefined4 *)FUN_0081f920(local_120,local_68,&local_5c);
    puVar3 = local_a8;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = local_a8;
    puVar3 = (undefined4 *)(*(int *)(local_ac + 0x14) + 0x20);
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    *(ulonglong *)(*(int *)(local_ac + 0x14) + 0x48) = CONCAT44(uStack_1c,local_20);
    *(double *)(*(int *)(local_ac + 0x14) + 0x50) = (double)local_b0;
    *(ulonglong *)(*(int *)(local_ac + 0x14) + 0x58) = CONCAT44(uStack_c,local_10);
    *(float *)(local_ac + 0x78) = *(float *)(local_ac + 0x78) - param_2;
    if (*(int *)(local_ac + 0xdc) != 0) {
      iVar2 = FUN_00439cd0(*(undefined4 *)(local_ac + 0xdc),*(undefined4 *)(local_ac + 0xd8));
      if (iVar2 == 0) {
        *(undefined4 *)(local_ac + 0x78) = 0;
      }
    }
  }
  else {
    FUN_004e7d30(param_2);
  }
  if (*(float *)(local_ac + 0x78) <= 0.0) {
    if ((((*(uint *)(*(int *)(local_ac + 0x14) + 0x14) & 0x200) == 0) ||
        (*(int *)(*(int *)(local_ac + 0xc) + 0x48) == 0)) &&
       (*(int *)(*(int *)(local_ac + 0xc) + 0x3c) != 0)) {
      FUN_004cb7b0(*(int *)(local_ac + 0x14) + 0x20,*(undefined4 *)(local_ac + 0xd8));
    }
    *(uint *)(*(int *)(local_ac + 0x14) + 0x14) =
         *(uint *)(*(int *)(local_ac + 0x14) + 0x14) | 0x200;
  }
  FUN_0083e885();
  return;
}

