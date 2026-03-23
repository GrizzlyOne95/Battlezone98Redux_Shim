
void FUN_0044b030(float param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_98 [24];
  undefined1 local_80 [28];
  float local_64;
  int local_60;
  float local_5c [2];
  float local_54;
  float *local_4c;
  int local_48;
  float local_44;
  float local_40;
  float local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00451250();
  FUN_00447e20();
  while( true ) {
    iVar1 = FUN_00447e70();
    FUN_00447e50();
    iVar2 = FUN_00447e70();
    if (iVar1 == iVar2) break;
    local_60 = FUN_00447e70();
    FUN_00447e90();
    local_48 = local_60 + 0x10;
    local_4c = (float *)(local_60 + 0x50);
    puVar3 = (undefined4 *)FUN_00447f60(local_80,local_48);
    local_38 = *puVar3;
    local_34 = puVar3[1];
    local_30 = puVar3[2];
    local_2c = puVar3[3];
    local_28 = puVar3[4];
    local_24 = puVar3[5];
    FUN_004451d0(local_38,local_34,local_30,local_2c,local_28,local_24,local_5c,&local_44);
    fVar4 = (float10)FUN_004428b0(local_4c,&local_44);
    local_64 = (float)fVar4;
    local_54 = -local_64;
    *local_4c = local_54 * local_44 + *local_4c;
    local_4c[1] = local_54 * local_40 + local_4c[1];
    local_4c[2] = local_54 * local_3c + local_4c[2];
    *(double *)(local_48 + 0x28) = (double)(param_1 * *local_4c) + *(double *)(local_48 + 0x28);
    *(double *)(local_48 + 0x30) = (double)(param_1 * local_4c[1]) + *(double *)(local_48 + 0x30);
    *(double *)(local_48 + 0x38) = (double)(param_1 * local_4c[2]) + *(double *)(local_48 + 0x38);
    fVar4 = (float10)FUN_0044b310(*(undefined8 *)(local_48 + 0x28),(double)DAT_02cd912c,
                                  (double)DAT_02cd9124);
    *(double *)(local_48 + 0x28) = (double)fVar4;
    fVar4 = (float10)FUN_0044b310(*(undefined8 *)(local_48 + 0x38),(double)DAT_02cd9130,
                                  (double)DAT_02cd9128);
    *(double *)(local_48 + 0x38) = (double)fVar4;
    puVar3 = (undefined4 *)FUN_00447f60(local_98);
    local_20 = *puVar3;
    local_1c = puVar3[1];
    local_18 = puVar3[2];
    local_14 = puVar3[3];
    local_10 = puVar3[4];
    local_c = puVar3[5];
    FUN_004451d0(local_20,local_1c,local_18,local_14,local_10,local_c,local_5c);
    *(double *)(local_48 + 0x30) = (double)local_5c[0];
  }
  FUN_0083e885();
  return;
}

