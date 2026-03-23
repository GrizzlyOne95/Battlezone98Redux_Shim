
int __thiscall
FUN_0072c620(int param_1,undefined1 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 *param_5,undefined4 param_6)

{
  undefined4 uVar1;
  uint uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085881b;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_006ac9a0(FUN_0072cec0);
  local_8._0_1_ = 1;
  *(undefined1 *)(param_1 + 0x20) = param_2;
  shared_ptr<>(&param_3);
  local_8 = CONCAT31(local_8._1_3_,2);
  uVar1 = param_5[1];
  *(undefined4 *)(param_1 + 0x2c) = *param_5;
  *(undefined4 *)(param_1 + 0x30) = uVar1;
  FUN_007270d0(param_6);
  local_8 = 0xffffffff;
  FUN_006c9420(uVar2);
  ExceptionList = local_10;
  return param_1;
}

