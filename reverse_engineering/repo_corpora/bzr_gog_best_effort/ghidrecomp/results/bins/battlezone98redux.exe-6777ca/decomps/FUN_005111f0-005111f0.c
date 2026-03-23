
void FUN_005111f0(int param_1,int param_2)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_118 [64];
  undefined1 local_d8 [24];
  undefined1 local_c0 [12];
  float local_b4;
  undefined4 *local_b0;
  undefined4 *local_ac;
  undefined4 local_a8 [16];
  undefined1 local_68 [12];
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  double local_24;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084ac7b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_0047e9c0(param_1,param_2);
  local_8 = 0;
  *local_ac = Mine::vftable;
  local_ac[6] = Mine::vftable;
  FUN_00442d30(local_ac[0x3c],uVar1);
  local_ac[0x8e] = *(undefined4 *)(param_2 + 0x160);
  local_b0 = (undefined4 *)(param_1 + 0x20);
  puVar2 = (undefined4 *)FUN_00447f60(local_d8,local_b0);
  local_50 = *puVar2;
  local_4c = puVar2[1];
  local_48 = puVar2[2];
  local_44 = puVar2[3];
  local_24 = *(double *)(puVar2 + 2);
  local_40 = puVar2[4];
  local_3c = puVar2[5];
  local_2c = local_50;
  local_28 = local_4c;
  local_1c = local_40;
  local_18 = local_3c;
  FUN_00444f70(local_ac[0x3c],local_50,local_4c,local_48,local_44,local_40,local_3c,&local_b4,
               local_68,0);
  local_24 = (double)local_b4;
  puVar2 = (undefined4 *)FUN_004560b0(local_c0,local_b0);
  local_5c = *puVar2;
  local_58 = puVar2[1];
  local_54 = puVar2[2];
  local_38 = local_5c;
  local_34 = local_58;
  local_30 = local_54;
  puVar2 = (undefined4 *)FUN_0081f920(local_118,local_68,&local_5c);
  puVar4 = local_a8;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar2 = local_a8;
  puVar4 = local_b0;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  FUN_0044b7d0(local_b0,&local_2c);
  FUN_004db100();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

