
int __thiscall FUN_00704ec0(int param_1,undefined1 param_2,undefined4 param_3,undefined4 param_4)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856e0b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006bb1e0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *(undefined1 *)(param_1 + 0x38) = param_2;
  *(undefined4 *)(param_1 + 0x3c) = param_3;
  *(undefined4 *)(param_1 + 0x40) = param_4;
  basic_string<>();
  local_8._0_1_ = 1;
  FUN_0068b0a0();
  local_8._0_1_ = 2;
  FUN_0068b0a0();
  local_8._0_1_ = 3;
  FUN_0068b0a0();
  local_8._0_1_ = 4;
  vector<>();
  local_8._0_1_ = 5;
  FUN_004fbb60();
  FUN_006caaf0();
  local_8._0_1_ = 6;
  FUN_006caaf0();
  local_8 = CONCAT31(local_8._1_3_,7);
  FUN_006baa00();
  FUN_006baa00();
  FUN_006d08b0(0x400,"asio con transport constructor");
  ExceptionList = local_10;
  return param_1;
}

