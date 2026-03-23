
undefined4 * FUN_005a6ba0(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int local_20;
  int local_1c;
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
  *local_14 = PopperClass::vftable;
  FUN_00589430(local_14 + 8);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00589800(0x25bbee79,0x6a1b2cdd,local_14 + 0x34,*(undefined4 *)(param_1 + 0xd0));
  FUN_00589c20(0x25bbee79,0x43506756,&local_20,0,0);
  if (local_20 == 0 && local_1c == 0) {
    local_14[0x35] = *(undefined4 *)(param_1 + 0xd4);
  }
  else {
    uVar2 = FUN_004cb870(local_20,local_1c,uVar1);
    local_14[0x35] = uVar2;
  }
  FUN_00589c20(0x25bbee79,0x5eaf51ed,&local_20,0,0);
  if (local_20 == 0 && local_1c == 0) {
    local_14[0x36] = *(undefined4 *)(param_1 + 0xd8);
  }
  else {
    uVar2 = FUN_00586c60(local_20,local_1c);
    local_14[0x36] = uVar2;
  }
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  ExceptionList = local_10;
  return local_14;
}

