
void FUN_00686830(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  short sVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *local_30;
  int local_2c;
  int local_28;
  short *local_24;
  
  iVar3 = (param_3 + -2) * 3;
  FUN_0067a110(param_3,iVar3);
  sVar1 = FUN_00684c10();
  local_30 = (undefined4 *)FUN_0067a150(param_3);
  for (local_28 = 0; local_28 < param_3; local_28 = local_28 + 1) {
    puVar2 = (undefined4 *)
             FUN_00446360(*(undefined4 *)(param_2 + local_28 * 0x18),
                          *(undefined4 *)(param_2 + 4 + local_28 * 0x18),
                          *(uint *)(param_2 + 8 + local_28 * 0x18) ^ 0x80000000,param_4,
                          *(undefined4 *)(param_2 + 0xc + local_28 * 0x18),
                          *(undefined4 *)(param_2 + 0x10 + local_28 * 0x18));
    *local_30 = *puVar2;
    local_30[1] = puVar2[1];
    local_30[2] = puVar2[2];
    local_30[3] = puVar2[3];
    local_30[4] = puVar2[4];
    local_30[5] = puVar2[5];
    local_30 = local_30 + 6;
  }
  local_24 = (short *)FUN_0067a1e0(iVar3);
  for (local_2c = 2; local_2c < param_3; local_2c = local_2c + 1) {
    *local_24 = sVar1;
    local_24[1] = sVar1 + (short)local_2c;
    local_24[2] = sVar1 + -1 + (short)local_2c;
    local_24 = local_24 + 3;
  }
  FUN_0083e885();
  return;
}

