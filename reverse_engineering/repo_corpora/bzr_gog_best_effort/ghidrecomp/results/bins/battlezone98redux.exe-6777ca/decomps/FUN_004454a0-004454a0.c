
void FUN_004454a0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,int *param_7,undefined4 param_8,
                 undefined4 param_9,undefined4 *param_10,undefined4 param_11)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_d0 [64];
  undefined1 local_90 [24];
  undefined1 local_78 [12];
  undefined1 local_6c [12];
  undefined4 local_60 [16];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = (undefined4 *)FUN_004415f0(local_90,param_7);
  local_20 = *puVar1;
  local_1c = puVar1[1];
  local_18 = puVar1[2];
  local_14 = puVar1[3];
  local_10 = puVar1[4];
  local_c = puVar1[5];
  puVar1 = (undefined4 *)FUN_008203f0(local_d0,*param_7 + 0x20);
  puVar3 = local_60;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  FUN_00820180(&param_1,&param_1,1,local_60);
  puVar1 = (undefined4 *)FUN_00440300(local_6c,&param_4,*param_7 + 0x20);
  param_4 = *puVar1;
  param_5 = puVar1[1];
  param_6 = puVar1[2];
  iVar2 = FUN_00445d90(param_1,param_2,param_3,param_4,param_5,param_6,local_20,local_1c,local_18,
                       local_14,local_10,local_c,param_8,param_9,param_10,param_11);
  if (iVar2 != 0) {
    puVar1 = (undefined4 *)FUN_00440210(local_78,param_10,*param_7 + 0x20);
    *param_10 = *puVar1;
    param_10[1] = puVar1[1];
    param_10[2] = puVar1[2];
  }
  FUN_0083e885();
  return;
}

