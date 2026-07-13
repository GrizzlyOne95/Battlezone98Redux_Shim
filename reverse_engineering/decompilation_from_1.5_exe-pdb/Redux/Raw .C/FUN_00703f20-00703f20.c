
int __thiscall
FUN_00703f20(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            ,undefined4 param_6)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00856c14;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_006ac9a0(FUN_007069b0);
  local_8._0_1_ = 1;
  shared_ptr<>(&param_2);
  local_8._0_1_ = 2;
  FUN_007049a0(param_4);
  local_8._0_1_ = 3;
  *(undefined4 *)(param_1 + 0x78) = param_5;
  FUN_006e5080(param_6);
  local_8 = CONCAT31(local_8._1_3_,4);
  FUN_004fbb60(uVar1);
  *(undefined4 *)(param_1 + 200) = 0;
  local_8 = 0xffffffff;
  FUN_006c9420();
  ExceptionList = local_10;
  return param_1;
}

