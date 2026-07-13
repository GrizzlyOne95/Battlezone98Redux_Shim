
void FUN_007fc180(undefined4 param_1,undefined4 param_2)

{
  allocator<char> local_38 [4];
  undefined1 local_34 [4];
  uint local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b778;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_30 = 0;
  basic_string<>(local_14);
  local_8 = 0;
  FUN_0042d300(local_2c);
  _Callable_base<>(local_34);
  std::allocator<char>::allocator<char>(local_38);
  FUN_007fc800(param_2);
  basic_string<>(local_2c);
  local_30 = local_30 | 1;
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

