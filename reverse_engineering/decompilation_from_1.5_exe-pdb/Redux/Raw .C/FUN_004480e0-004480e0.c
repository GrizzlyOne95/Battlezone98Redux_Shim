
void FUN_004480e0(float param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_e8 [64];
  undefined1 local_a8 [24];
  undefined1 local_90 [4];
  undefined4 *local_8c;
  undefined1 local_88 [8];
  int local_80;
  float local_7c;
  float local_78;
  float *local_74;
  undefined4 *local_70;
  undefined4 local_6c [16];
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
  FUN_00447e20(local_88);
  while( true ) {
    iVar1 = FUN_00447e70();
    FUN_00447e50(local_90);
    iVar2 = FUN_00447e70();
    if (iVar1 == iVar2) break;
    local_80 = FUN_00447e70();
    FUN_00447e90();
    local_70 = (undefined4 *)(local_80 + 0x10);
    local_74 = (float *)(local_80 + 0x50);
    local_8c = (undefined4 *)(local_80 + 0x5c);
    *(float *)(local_80 + 0x54) = *(float *)(local_80 + 0x54) - param_1 * 9.8;
    local_78 = param_1;
    puVar3 = (undefined4 *)FUN_00447f60(local_a8,local_70);
    local_20 = *puVar3;
    local_1c = puVar3[1];
    local_18 = puVar3[2];
    local_14 = puVar3[3];
    local_10 = puVar3[4];
    local_c = puVar3[5];
    iVar1 = FUN_00784620(local_20,local_1c,local_18,local_14,local_10,local_c,*local_74,local_74[1],
                         local_74[2],&local_78,&local_2c);
    if (iVar1 == 0) {
      *(double *)(local_70 + 10) = (double)(param_1 * *local_74) + *(double *)(local_70 + 10);
      *(double *)(local_70 + 0xc) = (double)(param_1 * local_74[1]) + *(double *)(local_70 + 0xc);
      *(double *)(local_70 + 0xe) = (double)(param_1 * local_74[2]) + *(double *)(local_70 + 0xe);
    }
    else {
      *(double *)(local_70 + 10) = (double)(local_78 * *local_74) + *(double *)(local_70 + 10);
      *(double *)(local_70 + 0xc) = (double)(local_78 * local_74[1]) + *(double *)(local_70 + 0xc);
      *(double *)(local_70 + 0xe) = (double)(local_78 * local_74[2]) + *(double *)(local_70 + 0xe);
      fVar5 = (float10)FUN_004428b0(local_74,&local_2c);
      local_7c = (float)fVar5;
      *local_74 = *local_74 * 0.5 - local_7c * local_2c;
      local_74[1] = local_74[1] * 0.5 - local_7c * local_28;
      local_74[2] = local_74[2] * 0.5 - local_7c * local_24;
      *(double *)(local_70 + 10) =
           (double)((param_1 - local_78) * *local_74) + *(double *)(local_70 + 10);
      *(double *)(local_70 + 0xc) =
           (double)((param_1 - local_78) * local_74[1]) + *(double *)(local_70 + 0xc);
      *(double *)(local_70 + 0xe) =
           (double)((param_1 - local_78) * local_74[2]) + *(double *)(local_70 + 0xe);
    }
    puVar3 = (undefined4 *)FUN_00444d50(local_e8,local_70,*local_8c,local_8c[1],local_8c[2],param_1)
    ;
    puVar4 = local_6c;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar3 = local_6c;
    puVar4 = local_70;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
  }
  FUN_0083e885();
  return;
}

