
void FUN_00440690(int *param_1,int *param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
                 )

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_158 [24];
  undefined1 local_140 [24];
  undefined1 local_128 [24];
  undefined1 local_110 [24];
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  int local_e0;
  int local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0 [16];
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  int local_68;
  int local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = (undefined4 *)FUN_00444b00(local_158,param_1);
  local_f8 = *puVar1;
  local_f4 = puVar1[1];
  local_f0 = puVar1[2];
  local_ec = puVar1[3];
  local_e8 = puVar1[4];
  local_e4 = puVar1[5];
  local_e0 = param_1[5];
  local_dc = *param_1;
  puVar1 = (undefined4 *)FUN_004415f0(local_128,param_1);
  local_d8 = *puVar1;
  local_d4 = puVar1[1];
  local_d0 = puVar1[2];
  local_cc = puVar1[3];
  local_c8 = puVar1[4];
  local_c4 = puVar1[5];
  puVar1 = (undefined4 *)(*param_1 + 0x20);
  puVar3 = local_c0;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar1 = (undefined4 *)FUN_00444b00(local_110,param_2);
  local_80 = *puVar1;
  local_7c = puVar1[1];
  local_78 = puVar1[2];
  local_74 = puVar1[3];
  local_70 = puVar1[4];
  local_6c = puVar1[5];
  local_68 = param_2[5];
  local_64 = *param_2;
  puVar1 = (undefined4 *)FUN_004415f0(local_140,param_2);
  local_60 = *puVar1;
  local_5c = puVar1[1];
  local_58 = puVar1[2];
  local_54 = puVar1[3];
  local_50 = puVar1[4];
  local_4c = puVar1[5];
  puVar1 = (undefined4 *)(*param_2 + 0x20);
  puVar3 = local_48;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  iVar2 = FUN_00440e60(&local_f8,&local_80,param_3,param_4,param_5);
  if (iVar2 == 0) {
    FUN_00440e60(&local_80,&local_f8,param_3,param_5,param_4);
  }
  FUN_0083e885();
  return;
}

