
void FUN_006073a0(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  float10 fVar3;
  undefined1 local_38 [12];
  float local_2c;
  undefined4 local_28;
  float local_24;
  float local_20;
  float *local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_28 = FUN_0045c4d0();
  local_1c = (float *)(*(int *)(*(int *)(local_18 + 0x10) + 0x230) + 0xc4);
  puVar1 = (undefined4 *)FUN_00440210(local_38,param_1,local_28);
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  *(undefined4 *)(local_18 + 0x58) = local_14;
  *(undefined4 *)(local_18 + 0x5c) = local_10;
  *(undefined4 *)(local_18 + 0x60) = local_c;
  fVar3 = (float10)FUN_0046e0a0(*param_1,param_1[2]);
  local_20 = (float)fVar3;
  iVar2 = FUN_0045c490(0xbf800000,0x3f800000);
  fVar3 = (float10)FUN_00447ed0((-*(float *)(iVar2 + 0x28) * *(float *)(local_18 + 0x70) - local_20)
                                * *(float *)(local_18 + 0x6c));
  *local_1c = (float)fVar3;
  local_2c = (float)param_1[1] * 4.0;
  fVar3 = (float10)FUN_00822d60(0xbf800000,0x3f800000);
  local_24 = (float)fVar3;
  fVar3 = (float10)FUN_00447ed0(local_2c * local_24 + *(float *)(local_18 + 0xb0));
  *(float *)(local_18 + 0xb0) = (float)fVar3;
  local_1c[1] = *(float *)(local_18 + 0xb0);
  FUN_0083e885();
  return;
}

