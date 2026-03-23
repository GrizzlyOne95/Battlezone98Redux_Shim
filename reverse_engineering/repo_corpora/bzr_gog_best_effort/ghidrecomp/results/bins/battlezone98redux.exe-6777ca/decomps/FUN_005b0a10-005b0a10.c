
undefined4 * FUN_005b0a10(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int local_20;
  int local_1c;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a020;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00511720(param_1,param_2,param_3);
  local_8 = 0;
  *local_14 = ProximityMineClass::vftable;
  FUN_00589430(local_14 + 0xe);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00589800(0xecd6fb3,0xe3635ff7,local_14 + 0x5a,*(undefined4 *)(param_1 + 0x168));
  FUN_00589800(0xecd6fb3,0x73a2de0,local_14 + 0x5b,*(undefined4 *)(param_1 + 0x16c));
  FUN_00589c20(0xecd6fb3,0xd61bc22b,&local_20,0,0);
  if (local_20 == 0 && local_1c == 0) {
    local_14[0x5c] = *(undefined4 *)(param_1 + 0x170);
  }
  else {
    uVar1 = FUN_004cb870(local_20,local_1c);
    local_14[0x5c] = uVar1;
  }
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  ExceptionList = local_10;
  return local_14;
}

