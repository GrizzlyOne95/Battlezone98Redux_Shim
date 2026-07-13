
void FUN_005f02f0(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_114 [64];
  undefined1 local_d4 [24];
  undefined1 local_bc [12];
  float local_b0;
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
  undefined4 uStack_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 uStack_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084d01b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_004a7a20(param_1,param_2);
  local_8 = 0;
  *local_ac = TurretCraft::vftable;
  local_ac[6] = TurretCraft::vftable;
  puVar2 = (undefined4 *)FUN_00447f60(local_d4,local_ac[0x3d] + 0x20,uVar1);
  local_50 = *puVar2;
  local_4c = puVar2[1];
  local_48 = puVar2[2];
  local_44 = puVar2[3];
  local_40 = puVar2[4];
  local_3c = puVar2[5];
  local_2c = local_50;
  uStack_28 = local_4c;
  local_24 = local_48;
  local_20 = local_44;
  local_1c = local_40;
  uStack_18 = local_3c;
  FUN_00444f70(local_ac[0x3c],local_50,local_4c,local_48,local_44,local_40,local_3c,&local_b0,
               local_68,0);
  puVar2 = (undefined4 *)FUN_004560b0(local_bc,local_ac[0x3d] + 0x20);
  local_5c = *puVar2;
  local_58 = puVar2[1];
  local_54 = puVar2[2];
  local_38 = local_5c;
  local_34 = local_58;
  local_30 = local_54;
  puVar2 = (undefined4 *)FUN_0081f920(local_114,local_68,&local_5c);
  puVar4 = local_a8;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar2 = local_a8;
  puVar4 = (undefined4 *)(local_ac[0x3d] + 0x20);
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  *(ulonglong *)(local_ac[0x3d] + 0x48) = CONCAT44(uStack_28,local_2c);
  *(double *)(local_ac[0x3d] + 0x50) = (double)local_b0;
  *(ulonglong *)(local_ac[0x3d] + 0x58) = CONCAT44(uStack_18,local_1c);
  local_ac[0xaa] = 0;
  local_ac[0xaf] = 0;
  FUN_005f01d0(local_ac[0x3d]);
  if ((local_ac[0x9f] == 0) && (local_ac[0xaa] != 0)) {
    local_ac[local_ac[0x9f] + 0x97] = local_ac[0xaa];
    local_ac[0x9f] = local_ac[0x9f] + 1;
  }
  local_ac[0xb0] = 0;
  FUN_005ca980(local_ac[0x3d]);
  local_ac[0xb1] = 0;
  local_ac[0x2a] = 1;
  local_ac[0x2b] = 0xf;
  local_ac[0x2c] = 0;
  local_ac[0x2d] = 0;
  local_ac[0x30] = 0;
  local_ac[0x31] = 0;
  local_ac[0x8a] = 2;
  local_ac[0xb2] = 0;
  FUN_00444ef0(local_ac[0x3c]);
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

