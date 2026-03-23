
int __fastcall FUN_006b3fa0(int param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008507de;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_006ac9a0(FUN_006b45c0);
  local_8 = 0;
  FUN_006ac110(uVar1);
  local_8._0_1_ = 1;
  *(undefined1 *)(param_1 + 0x38) = 0;
  FUN_006c8f00();
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_006c8f00();
  ExceptionList = local_10;
  return param_1;
}

