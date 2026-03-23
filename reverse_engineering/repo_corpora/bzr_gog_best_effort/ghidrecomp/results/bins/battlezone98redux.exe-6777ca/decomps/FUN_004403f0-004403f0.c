
void FUN_004403f0(int *param_1,int *param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
                 )

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_130 [24];
  undefined1 local_118 [24];
  undefined1 local_100 [12];
  undefined1 local_f4 [12];
  undefined1 local_e8 [12];
  int local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  int local_c0;
  int local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0 [16];
  undefined4 local_60 [16];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = (undefined4 *)FUN_00444b00(local_130,param_1);
  local_d8 = *puVar1;
  local_d4 = puVar1[1];
  local_d0 = puVar1[2];
  local_cc = puVar1[3];
  local_c8 = puVar1[4];
  local_c4 = puVar1[5];
  local_c0 = param_1[5];
  local_bc = *param_1;
  puVar1 = (undefined4 *)FUN_004415f0(local_118,param_1);
  local_b8 = *puVar1;
  local_b4 = puVar1[1];
  local_b0 = puVar1[2];
  local_ac = puVar1[3];
  local_a8 = puVar1[4];
  local_a4 = puVar1[5];
  puVar1 = (undefined4 *)(*param_1 + 0x20);
  puVar3 = local_a0;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  local_dc = *param_2;
  puVar1 = (undefined4 *)(local_dc + 0x20);
  puVar3 = local_60;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar1 = (undefined4 *)FUN_00439de0(local_e8,local_60);
  local_20 = *puVar1;
  local_1c = puVar1[1];
  local_18 = puVar1[2];
  puVar1 = (undefined4 *)FUN_00440000(local_100,0,0,0,local_dc);
  puVar1 = (undefined4 *)FUN_00444ba0(local_f4,*puVar1,puVar1[1],puVar1[2]);
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  FUN_004423d0(&local_d8,local_dc,0x3f800000,local_60,param_3,param_4,param_5);
  FUN_0083e885();
  return;
}

