
void FUN_0044b4c0(float param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_64 [24];
  undefined1 local_4c [4];
  int local_48;
  undefined1 local_40 [4];
  float local_3c;
  float local_38;
  float *local_34;
  int local_30;
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
  FUN_00447e20(local_40);
  while( true ) {
    iVar1 = FUN_00447e70();
    FUN_00447e50(local_4c);
    iVar2 = FUN_00447e70();
    if (iVar1 == iVar2) break;
    local_48 = FUN_00447e70();
    FUN_00447e90();
    local_30 = local_48 + 0x10;
    local_34 = (float *)(local_48 + 0x50);
    *(float *)(local_48 + 0x54) = *(float *)(local_48 + 0x54) - param_1 * 9.8;
    local_38 = param_1;
    puVar3 = (undefined4 *)FUN_00447f60(local_64,local_30);
    local_20 = *puVar3;
    local_1c = puVar3[1];
    local_18 = puVar3[2];
    local_14 = puVar3[3];
    local_10 = puVar3[4];
    local_c = puVar3[5];
    iVar1 = FUN_00784620(local_20,local_1c,local_18,local_14,local_10,local_c,*local_34,local_34[1],
                         local_34[2],&local_38,&local_2c);
    if (iVar1 == 0) {
      *(double *)(local_30 + 0x28) = (double)(param_1 * *local_34) + *(double *)(local_30 + 0x28);
      *(double *)(local_30 + 0x30) = (double)(param_1 * local_34[1]) + *(double *)(local_30 + 0x30);
      *(double *)(local_30 + 0x38) = (double)(param_1 * local_34[2]) + *(double *)(local_30 + 0x38);
    }
    else {
      *(double *)(local_30 + 0x28) = (double)(local_38 * *local_34) + *(double *)(local_30 + 0x28);
      *(double *)(local_30 + 0x30) = (double)(local_38 * local_34[1]) + *(double *)(local_30 + 0x30)
      ;
      *(double *)(local_30 + 0x38) = (double)(local_38 * local_34[2]) + *(double *)(local_30 + 0x38)
      ;
      fVar4 = (float10)FUN_004428b0(local_34,&local_2c);
      local_3c = (float)fVar4;
      *local_34 = *local_34 * 0.5 - local_3c * local_2c;
      local_34[1] = local_34[1] * 0.5 - local_3c * local_28;
      local_34[2] = local_34[2] * 0.5 - local_3c * local_24;
      *(double *)(local_30 + 0x28) =
           (double)((param_1 - local_38) * *local_34) + *(double *)(local_30 + 0x28);
      *(double *)(local_30 + 0x30) =
           (double)((param_1 - local_38) * local_34[1]) + *(double *)(local_30 + 0x30);
      *(double *)(local_30 + 0x38) =
           (double)((param_1 - local_38) * local_34[2]) + *(double *)(local_30 + 0x38);
    }
  }
  FUN_0083e885();
  return;
}

