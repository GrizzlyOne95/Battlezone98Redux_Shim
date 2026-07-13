
int __thiscall FUN_006cfbe0(int param_1,undefined1 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00852e9a;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006d3790(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  FUN_006d4430(0xfffffbff,1);
  local_8._0_1_ = 1;
  FUN_006d4430(0xfffffffe,2);
  local_8._0_1_ = 2;
  basic_string<>("WebSocket++/0.7.0");
  local_8._0_1_ = 3;
  FUN_006caaf0();
  local_8._0_1_ = 4;
  FUN_006caaf0();
  local_8._0_1_ = 5;
  FUN_006caaf0();
  local_8._0_1_ = 6;
  FUN_006caaf0();
  local_8._0_1_ = 7;
  FUN_006caaf0();
  local_8._0_1_ = 8;
  FUN_006caaf0();
  local_8._0_1_ = 9;
  FUN_006caaf0();
  local_8._0_1_ = 10;
  FUN_006caaf0();
  local_8._0_1_ = 0xb;
  FUN_006caaf0();
  local_8._0_1_ = 0xc;
  FUN_006caaf0();
  local_8._0_1_ = 0xd;
  *(undefined4 *)(param_1 + 0x1a8) = 5000;
  *(undefined4 *)(param_1 + 0x1ac) = 5000;
  *(undefined4 *)(param_1 + 0x1b0) = 5000;
  *(undefined **)(param_1 + 0x1b4) = &DAT_01e84800;
  *(undefined **)(param_1 + 0x1b8) = &DAT_01e84800;
  FUN_006d48c0();
  local_8._0_1_ = 0xe;
  *(undefined1 *)(param_1 + 0x1cc) = param_2;
  FUN_006b4800();
  local_8 = CONCAT31(local_8._1_3_,0xf);
  FUN_006d0820(0xfffffbff);
  FUN_006d0820(0xfffffffe);
  FUN_006d08b0(0x400,"endpoint constructor");
  FUN_006d3830(param_1 + 0x80,param_1 + 0x90);
  ExceptionList = local_10;
  return param_1;
}

