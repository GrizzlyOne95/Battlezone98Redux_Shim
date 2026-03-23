
undefined4 * FUN_005dad90(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c2a0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004e8010(param_1,param_2,param_3);
  local_8 = 0;
  *local_14 = SprayBombClass::vftable;
  FUN_00589430(local_14 + 8);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00589c20(0x47d244de,0x830b28dd,&local_20,param_2,param_3);
  uVar2 = FUN_004e0f70(local_20,local_1c,uVar1);
  local_14[0x34] = uVar2;
  if (local_14[0x34] == 0) {
    FUN_007d6b70("SprayBombClass \"%s\" has nothing to deploy\n",local_14 + 8);
  }
  FUN_00589800(0x47d244de,0xa7666fac,local_14 + 0x35,*(undefined4 *)(param_1 + 0xd4));
  FUN_0047b6c0(0x47d244de,0x7e5a762c,local_14 + 0x36,param_1 + 0xd8);
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  ExceptionList = local_10;
  return local_14;
}

