
void FUN_005abab0(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined1 local_424 [64];
  undefined1 local_3e4 [64];
  undefined1 local_3a4 [64];
  undefined1 local_364 [64];
  undefined1 local_324 [64];
  undefined1 local_2e4 [64];
  float local_2a4;
  int local_2a0;
  int local_29c;
  undefined4 *local_298;
  undefined4 local_294 [16];
  undefined4 local_254 [16];
  undefined4 local_214 [16];
  undefined4 local_1d4 [16];
  undefined4 local_194 [16];
  undefined4 local_154 [16];
  undefined4 local_114 [16];
  undefined4 local_d4 [16];
  undefined4 local_94 [10];
  undefined8 local_6c;
  undefined8 local_64;
  undefined8 local_5c;
  undefined4 local_54 [10];
  undefined8 local_2c;
  undefined8 local_24;
  undefined8 local_1c;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c346;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_004e96d0(param_1,param_2);
  local_8 = 0;
  *local_298 = Producer::vftable;
  local_298[6] = Producer::vftable;
  FUN_0083ead2(local_298 + 0xd2,4,8,FUN_00423890,FUN_0044dc30);
  local_8 = CONCAT31(local_8._1_3_,1);
  local_298[0x8a] = 0;
  local_298[0xc5] = 0xffffffff;
  local_298[0xc6] = 0xf149f2ca;
  local_298[0xc3] = 0;
  local_298[0xc4] = 0;
  fVar6 = (float10)FUN_00822da0(uVar1);
  local_2a4 = (float)fVar6;
  local_298[199] = local_2a4 + 10.0;
  local_298[0xc0] = 0;
  *(undefined1 *)(local_298 + 0xc2) = 1;
  *(undefined1 *)((int)local_298 + 0x309) = 1;
  local_298[0xd1] = 0;
  local_298[200] = 0;
  FUN_005aba30(param_1);
  uVar2 = FUN_004d9ca0(local_298[0x3d],&DAT_00886064);
  local_298[0xda] = uVar2;
  if (local_298[0xda] == 0) {
    local_29c = *(int *)(local_298[0x3d] + 0x80);
    puVar3 = (undefined4 *)FUN_0081ed60(local_3e4,0xbf860a92,0xbfc90fda);
    puVar5 = local_214;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar5 = puVar5 + 1;
    }
    puVar3 = local_214;
    puVar5 = local_94;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar5 = puVar5 + 1;
    }
    local_6c = 0;
    local_64 = 0x4014000000000000;
    local_5c = 0;
    puVar3 = (undefined4 *)FUN_008203f0(local_364,local_29c + 0x20);
    puVar5 = local_1d4;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar5 = puVar5 + 1;
    }
    puVar3 = local_1d4;
    puVar5 = local_154;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar5 = puVar5 + 1;
    }
    uVar2 = FUN_0062ccc0(local_29c,"fun3d\\Producer.cpp");
    local_298[0xda] = uVar2;
    *(undefined4 *)(local_298[0xda] + 0x84) = 0x4a;
    puVar3 = (undefined4 *)FUN_0081fe60(local_2e4,local_94,local_154);
    puVar5 = local_d4;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar5 = puVar5 + 1;
    }
    puVar3 = local_d4;
    puVar5 = (undefined4 *)(local_298[0xda] + 0x20);
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar5 = puVar5 + 1;
    }
  }
  uVar2 = FUN_004d9ca0(local_298[0x3d],&DAT_0088604c);
  local_298[0xdb] = uVar2;
  if (local_298[0xdb] == 0) {
    local_2a0 = *(int *)(local_298[0x3d] + 0x80);
    puVar3 = (undefined4 *)FUN_0081ed60(local_324,0xbf860a92,0x3fc90fda);
    puVar5 = local_294;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar5 = puVar5 + 1;
    }
    puVar3 = local_294;
    puVar5 = local_54;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar5 = puVar5 + 1;
    }
    local_2c = 0;
    local_24 = 0x4014000000000000;
    local_1c = 0;
    puVar3 = (undefined4 *)FUN_008203f0(local_3a4,local_2a0 + 0x20);
    puVar5 = local_114;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar5 = puVar5 + 1;
    }
    puVar3 = local_114;
    puVar5 = local_254;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar5 = puVar5 + 1;
    }
    uVar2 = FUN_0062ccc0(local_2a0,"fun3d\\Producer.cpp");
    local_298[0xdb] = uVar2;
    *(undefined4 *)(local_298[0xdb] + 0x84) = 0x4a;
    puVar3 = (undefined4 *)FUN_0081fe60(local_424,local_54,local_254);
    puVar5 = local_194;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar5 = puVar5 + 1;
    }
    puVar3 = local_194;
    puVar5 = (undefined4 *)(local_298[0xdb] + 0x20);
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar5 = puVar5 + 1;
    }
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

