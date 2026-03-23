
undefined4 * FUN_004b59a0(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  int local_24;
  int local_20;
  int local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008499e0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00611aa0(param_1,param_2,param_3);
  local_8 = 0;
  *local_14 = DispenserClass::vftable;
  FUN_00589430(local_14 + 8);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00589c20(0xd60ea600,0xfab4528a,&local_24,0,0);
  if (local_24 != 0 || local_20 != 0) {
    local_18 = FUN_004e0f70(local_24,local_20,uVar1);
    if (local_18 != 0) {
      local_14[0xc] = local_18;
      local_14[0xd] = *(undefined4 *)(local_18 + 0x5c);
    }
  }
  FUN_00589800(0xd60ea600,0xd9356908,local_14 + 0x20,*(undefined4 *)(param_1 + 0x80));
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  ExceptionList = local_10;
  return local_14;
}

