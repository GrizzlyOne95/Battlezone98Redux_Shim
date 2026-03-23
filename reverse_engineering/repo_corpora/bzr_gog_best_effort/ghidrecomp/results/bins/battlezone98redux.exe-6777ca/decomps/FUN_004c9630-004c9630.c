
void __thiscall FUN_004c9630(int param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_124 [64];
  undefined1 local_e4 [12];
  undefined1 local_d8 [12];
  undefined4 local_cc;
  float local_c8;
  int local_c4;
  uint local_c0;
  int local_bc;
  undefined4 local_b8 [16];
  undefined4 local_78 [16];
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_bc = param_1;
  for (local_c0 = param_1 + 0x28; local_c0 < *(uint *)(local_bc + 0x1228);
      local_c0 = local_c0 + 0x48) {
    puVar1 = (undefined4 *)FUN_0081fe60(local_124,local_c0,param_2 + 0x40);
    puVar3 = local_78;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = local_78;
    puVar3 = local_b8;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = (undefined4 *)FUN_00439de0(local_d8,local_b8);
    local_2c = *puVar1;
    local_28 = puVar1[1];
    local_24 = (float)puVar1[2];
    local_20 = local_2c;
    local_1c = local_28;
    local_18 = local_24;
    iVar2 = FUN_006895d0(param_2,&local_2c,*(undefined4 *)(local_bc + 0x123c));
    if (iVar2 < 1) {
      fVar4 = (float10)FUN_0049bf10((float)*(int *)(local_bc + 0x1234) * *(float *)(local_c0 + 0x40)
                                   );
      local_c8 = (float)fVar4;
      local_c4 = *(int *)(local_bc + 0x122c) + (int)fVar4 + *(int *)(local_bc + 0x1230);
      local_cc = DAT_00920ef4;
      DAT_00920ef4 = local_24 - *(float *)(local_bc + 0x123c);
      puVar1 = (undefined4 *)FUN_00439de0(local_e4,local_c0);
      local_38 = *puVar1;
      local_34 = puVar1[1];
      local_30 = puVar1[2];
      local_14 = local_38;
      local_10 = local_34;
      local_c = local_30;
      FUN_0068e600(param_2,&local_38,*(undefined4 *)(local_bc + 0x123c),local_c4,4);
      DAT_00920ef4 = (float)local_cc;
    }
  }
  FUN_0083e885();
  return;
}

