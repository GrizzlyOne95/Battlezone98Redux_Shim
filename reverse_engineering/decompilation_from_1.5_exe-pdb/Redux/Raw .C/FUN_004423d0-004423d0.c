
void FUN_004423d0(int param_1,int param_2,float param_3,undefined4 param_4,undefined4 param_5,
                 undefined4 *param_6,undefined4 *param_7)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_1f0 [72];
  undefined1 local_1a8 [72];
  undefined1 local_160 [64];
  undefined1 local_120 [64];
  undefined1 local_e0 [12];
  undefined1 local_d4 [12];
  undefined1 local_c8 [12];
  undefined1 local_bc [12];
  undefined1 local_b0 [12];
  undefined1 local_a4 [12];
  undefined1 local_98 [12];
  undefined1 local_8c [12];
  undefined4 local_80;
  float local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_6c = *(undefined4 *)(param_1 + 0xc);
  local_68 = *(undefined4 *)(param_1 + 0x10);
  local_64 = *(undefined4 *)(param_1 + 0x14);
  puVar1 = (undefined4 *)FUN_008203f0(local_120,param_1 + 0x38);
  puVar3 = local_48;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar1 = (undefined4 *)FUN_0081fe60(local_160,param_4,local_48);
  puVar3 = local_48;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  FUN_00820180(&local_60,param_2 + 0xa0,1,local_48);
  puVar1 = (undefined4 *)FUN_00440000(local_c8,0,0,0,param_2);
  puVar1 = (undefined4 *)FUN_00444ba0(local_98,*puVar1,puVar1[1],puVar1[2]);
  local_54 = *puVar1;
  local_50 = puVar1[1];
  local_4c = puVar1[2];
  puVar1 = (undefined4 *)
           FUN_004401a0(local_b0,local_54,local_50,local_4c,*(undefined4 *)(param_1 + 0xc),
                        *(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x14));
  local_54 = *puVar1;
  local_50 = puVar1[1];
  local_4c = puVar1[2];
  puVar1 = (undefined4 *)FUN_00440300(local_a4,&local_54,param_1 + 0x38);
  local_54 = *puVar1;
  local_50 = puVar1[1];
  local_4c = puVar1[2];
  local_7c = param_3 * *(float *)(param_2 + 0xac);
  *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x20) - local_7c;
  *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) - local_7c;
  *(float *)(param_1 + 0x28) = *(float *)(param_1 + 0x28) - local_7c;
  *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) + local_7c;
  *(float *)(param_1 + 0x30) = *(float *)(param_1 + 0x30) + local_7c;
  *(float *)(param_1 + 0x34) = *(float *)(param_1 + 0x34) + local_7c;
  iVar2 = FUN_00445d90(local_60,local_5c,local_58,local_54,local_50,local_4c,
                       *(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x24),
                       *(undefined4 *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x2c),
                       *(undefined4 *)(param_1 + 0x30),*(undefined4 *)(param_1 + 0x34),param_5,
                       &local_80,&local_78,0);
  if (iVar2 != 0) {
    param_6[0x15] = local_78;
    param_6[0x16] = local_74;
    param_6[0x17] = local_70;
    puVar1 = (undefined4 *)FUN_00440060(local_8c,local_78,local_74,local_70);
    param_7[0x15] = *puVar1;
    param_7[0x16] = puVar1[1];
    param_7[0x17] = puVar1[2];
    puVar1 = (undefined4 *)FUN_00440060(local_bc,local_6c,local_68,local_64);
    param_6[0x18] = *puVar1;
    param_6[0x19] = puVar1[1];
    param_6[0x1a] = puVar1[2];
    param_7[0x18] = local_6c;
    param_7[0x19] = local_68;
    param_7[0x1a] = local_64;
    param_7[0x14] = local_80;
    param_6[0x14] = local_80;
    *param_7 = 1;
    *param_6 = 1;
    param_6[1] = param_2;
    param_7[1] = *(undefined4 *)(param_1 + 0x1c);
    puVar1 = (undefined4 *)FUN_0062bf70(local_1a8,param_2);
    puVar3 = param_6 + 2;
    for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = (undefined4 *)FUN_0062bf70(local_1f0,*(undefined4 *)(param_1 + 0x1c));
    puVar3 = param_7 + 2;
    for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = (undefined4 *)FUN_00440210(local_e0,&local_78,param_1 + 0x38);
    param_7[0x1b] = *puVar1;
    param_7[0x1c] = puVar1[1];
    param_7[0x1d] = puVar1[2];
    puVar1 = (undefined4 *)FUN_00440060(local_d4,param_7[0x1b],param_7[0x1c],param_7[0x1d]);
    param_6[0x1b] = *puVar1;
    param_6[0x1c] = puVar1[1];
    param_6[0x1d] = puVar1[2];
  }
  FUN_0083e885();
  return;
}

