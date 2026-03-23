
undefined4 __thiscall
FUN_007268c0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008587d6;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_006ac9a0(FUN_00727360);
  local_8._0_1_ = 1;
  shared_ptr<>(&param_2);
  local_8._0_1_ = 2;
  FUN_00713b90(param_4);
  local_8 = CONCAT31(local_8._1_3_,3);
  FUN_0071e950(param_5);
  local_8 = 0xffffffff;
  FUN_006c9420(uVar1);
  ExceptionList = local_10;
  return param_1;
}

