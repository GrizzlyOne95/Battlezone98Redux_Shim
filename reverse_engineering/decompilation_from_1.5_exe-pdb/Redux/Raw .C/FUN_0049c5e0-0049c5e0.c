
void FUN_0049c5e0(float *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  float10 fVar2;
  undefined1 local_88 [12];
  undefined1 local_7c [12];
  undefined1 local_70 [12];
  undefined1 local_64 [12];
  undefined1 local_58 [12];
  float local_4c;
  int local_48;
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
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = (undefined4 *)FUN_00440000(local_64,*param_1,0x3f000000,param_1[2]);
  local_44 = *puVar1;
  local_40 = puVar1[1];
  local_3c = puVar1[2];
  *(undefined4 *)(local_48 + 0x28) = local_44;
  *(undefined4 *)(local_48 + 0x2c) = local_40;
  *(undefined4 *)(local_48 + 0x30) = local_3c;
  puVar1 = (undefined4 *)FUN_00440000(local_7c,*param_1,0x3f000000,param_1[5]);
  local_2c = *puVar1;
  local_28 = puVar1[1];
  local_24 = puVar1[2];
  *(undefined4 *)(local_48 + 0x34) = local_2c;
  *(undefined4 *)(local_48 + 0x38) = local_28;
  *(undefined4 *)(local_48 + 0x3c) = local_24;
  puVar1 = (undefined4 *)FUN_00440000(local_58,param_1[3],0x3f000000,param_1[5]);
  local_38 = *puVar1;
  local_34 = puVar1[1];
  local_30 = puVar1[2];
  *(undefined4 *)(local_48 + 0x40) = local_38;
  *(undefined4 *)(local_48 + 0x44) = local_34;
  *(undefined4 *)(local_48 + 0x48) = local_30;
  puVar1 = (undefined4 *)FUN_00440000(local_70,param_1[3],0x3f000000,param_1[2]);
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  *(undefined4 *)(local_48 + 0x4c) = local_14;
  *(undefined4 *)(local_48 + 0x50) = local_10;
  *(undefined4 *)(local_48 + 0x54) = local_c;
  puVar1 = (undefined4 *)
           FUN_00440000(local_88,(*param_1 + param_1[3]) * 0.5,0,(param_1[2] + param_1[5]) * 0.5);
  local_20 = *puVar1;
  local_1c = puVar1[1];
  local_18 = puVar1[2];
  *(undefined4 *)(local_48 + 0x58) = local_20;
  *(undefined4 *)(local_48 + 0x5c) = local_1c;
  *(undefined4 *)(local_48 + 0x60) = local_18;
  fVar2 = (float10)FUN_0044fb20(param_1[3] - *param_1,param_1[5] - param_1[2]);
  local_4c = (float)fVar2;
  *(float *)(local_48 + 100) = local_4c * 0.5;
  FUN_00820180(local_48 + 0x28,local_48 + 0x28,5,param_2);
  FUN_0083e885();
  return;
}

