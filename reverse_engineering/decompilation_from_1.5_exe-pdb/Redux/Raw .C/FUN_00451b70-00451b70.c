
void FUN_00451b70(float param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_64 [24];
  undefined1 local_4c [4];
  float local_48;
  int local_44;
  float local_40;
  undefined1 local_38 [4];
  int local_34;
  float *local_30;
  float local_2c;
  float local_28;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00451250(param_1);
  FUN_00447e20(local_38);
  while( true ) {
    iVar1 = FUN_00447e70();
    FUN_00447e50(local_4c);
    iVar2 = FUN_00447e70();
    if (iVar1 == iVar2) break;
    local_44 = FUN_00447e70();
    FUN_00447e90();
    local_34 = local_44 + 0x10;
    local_30 = (float *)(local_44 + 0x50);
    *(float *)(local_44 + 0x54) = *(float *)(local_44 + 0x54) - param_1 * 9.8;
    *(double *)(local_44 + 0x38) = (double)(param_1 * *local_30) + *(double *)(local_44 + 0x38);
    *(double *)(local_44 + 0x40) =
         (double)(param_1 * *(float *)(local_44 + 0x54)) + *(double *)(local_44 + 0x40);
    *(double *)(local_44 + 0x48) =
         (double)(param_1 * *(float *)(local_44 + 0x58)) + *(double *)(local_44 + 0x48);
    puVar3 = (undefined4 *)FUN_00447f60(local_64,local_34);
    local_20 = *puVar3;
    local_1c = puVar3[1];
    local_18 = puVar3[2];
    local_14 = puVar3[3];
    local_10 = puVar3[4];
    local_c = puVar3[5];
    FUN_004451d0(local_20,local_1c,local_18,local_14,local_10,local_c,&local_48,&local_2c);
    if ((*(double *)(local_34 + 0x30) <= (double)local_48 &&
         (double)local_48 != *(double *)(local_34 + 0x30)) &&
       (local_30[1] <= 0.0 && local_30[1] != 0.0)) {
      fVar4 = (float10)FUN_004428b0(local_30,&local_2c);
      local_40 = (float)fVar4;
      *local_30 = *local_30 * 0.5 - local_40 * local_2c;
      local_30[1] = local_30[1] * 0.5 - local_40 * local_28;
      local_30[2] = local_30[2] * 0.5 - local_40 * local_24;
      *(double *)(local_34 + 0x30) = (double)local_48;
    }
  }
  FUN_0083e885();
  return;
}

