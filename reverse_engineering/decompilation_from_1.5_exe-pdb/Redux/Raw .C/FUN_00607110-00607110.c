
void FUN_00607110(float *param_1,float *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  float10 fVar3;
  undefined1 local_64 [12];
  undefined1 local_58 [12];
  float local_4c;
  float local_48;
  undefined4 local_44;
  float local_40;
  float local_3c;
  float local_38;
  float *local_34;
  int local_30;
  undefined4 local_2c;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  float local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_44 = FUN_0045c4d0();
  local_34 = (float *)(*(int *)(*(int *)(local_30 + 0x10) + 0x230) + 0xc4);
  puVar1 = (undefined4 *)FUN_004621a0(local_58,param_1);
  local_2c = *puVar1;
  local_28 = (float)puVar1[1];
  local_24 = puVar1[2];
  local_14 = local_2c;
  local_10 = local_28;
  local_c = local_24;
  puVar1 = (undefined4 *)FUN_00440210(local_64,&local_2c,local_44);
  local_20 = *puVar1;
  local_1c = puVar1[1];
  local_18 = puVar1[2];
  *(undefined4 *)(local_30 + 0x58) = local_20;
  *(undefined4 *)(local_30 + 0x5c) = local_1c;
  *(undefined4 *)(local_30 + 0x60) = local_18;
  fVar3 = (float10)FUN_0046e0a0(*param_1,param_1[2]);
  local_48 = (float)fVar3;
  local_38 = (param_2[2] * *param_1 - *param_2 * param_1[2]) /
             (*param_1 * *param_1 + param_1[2] * param_1[2]);
  local_40 = local_38 * *(float *)(local_30 + 0x74);
  iVar2 = FUN_0045c490(0xbf800000,0x3f800000);
  fVar3 = (float10)FUN_00447ed0(local_40 +
                                ((local_38 - *(float *)(iVar2 + 0x28)) * *(float *)(local_30 + 0x70)
                                - local_48) * *(float *)(local_30 + 0x6c));
  *local_34 = (float)fVar3;
  local_3c = local_28 * 4.0;
  fVar3 = (float10)FUN_00822d60(0xbf800000,0x3f800000);
  local_4c = (float)fVar3;
  fVar3 = (float10)FUN_00447ed0(local_3c * local_4c + *(float *)(local_30 + 0xb0));
  *(float *)(local_30 + 0xb0) = (float)fVar3;
  local_34[1] = *(float *)(local_30 + 0xb0);
  FUN_0083e885();
  return;
}

