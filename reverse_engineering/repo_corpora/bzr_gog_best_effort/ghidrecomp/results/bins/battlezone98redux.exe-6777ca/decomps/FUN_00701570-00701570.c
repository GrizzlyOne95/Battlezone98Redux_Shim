
void FUN_00701570(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 extraout_var;
  _RunAllParam<unsigned_char> local_d0 [116];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856743;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_007048c0(param_2);
  local_8 = 0;
  uVar2 = extraout_var;
  basic_string<>("Sec-WebSocket-Key3");
  local_8._0_1_ = 1;
  FUN_006b7840(local_2c);
  local_8._0_1_ = 0;
  ~basic_string<>(uVar1,uVar2);
  basic_string<>("Sec-WebSocket-Key3");
  local_8._0_1_ = 2;
  uVar2 = FUN_006b9760(local_5c);
  local_8._0_1_ = 3;
  uVar3 = FUN_006b7490(local_44);
  FUN_00426a20(param_1,uVar2,uVar3);
  local_8._0_1_ = 2;
  ~basic_string<>();
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  Concurrency::details::_RunAllParam<unsigned_char>::~_RunAllParam<unsigned_char>(local_d0);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

