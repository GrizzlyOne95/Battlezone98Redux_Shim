
int __fastcall FUN_00700600(int param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00856466;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  shared_ptr<>(&stack0x00000004);
  local_8._0_1_ = 1;
  basic_string<>(uVar1);
  local_8._0_1_ = 2;
  basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,3);
  basic_string<>();
  *(undefined1 *)(param_1 + 0x54) = 0;
  *(undefined1 *)(param_1 + 0x55) = 1;
  *(undefined1 *)(param_1 + 0x56) = 0;
  *(undefined1 *)(param_1 + 0x57) = 0;
  local_8 = 0xffffffff;
  FUN_006ca8c0();
  ExceptionList = local_10;
  return param_1;
}

