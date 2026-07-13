
void __fastcall FUN_00417cc0(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844a49;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  basic_string<>(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  basic_string<>();
  local_8._0_1_ = 1;
  basic_string<>();
  local_8._0_1_ = 2;
  basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,3);
  vector<>();
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined1 *)(param_1 + 100) = 0;
  *(undefined4 *)(param_1 + 0x80) = 0;
  *(undefined4 *)(param_1 + 0x84) = 0;
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

