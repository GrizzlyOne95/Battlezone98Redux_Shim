
allocator<char> * __thiscall
FUN_006d8b00(allocator<char> *param_1,undefined4 param_2,undefined4 param_3)

{
  void *pvVar1;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853634;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  std::allocator<char>::allocator<char>(param_1);
  local_8 = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  pvVar1 = operator_new(0x10);
  local_8._0_1_ = 1;
  if (pvVar1 == (void *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = FUN_006e2c00(param_2);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006ac680(local_1c,param_3);
  ExceptionList = local_10;
  return param_1;
}

