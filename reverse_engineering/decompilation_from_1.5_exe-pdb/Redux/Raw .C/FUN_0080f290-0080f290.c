
void FUN_0080f290(undefined4 param_1,byte *param_2)

{
  allocator<char> *this;
  uint uVar1;
  undefined1 local_3c [8];
  uint local_34;
  uint local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a048;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_30 = 0;
  basic_string<>(local_14);
  local_8 = 0;
  FUN_0042d300(local_2c);
  _Callable_base<>(local_3c);
  for (; *param_2 != 0; param_2 = param_2 + 1) {
    uVar1 = (uint)*param_2;
    local_34 = uVar1;
    this = (allocator<char> *)allocator<>(0);
    std::allocator<char>::allocator<char>(this);
    FUN_007fc800(uVar1);
  }
  basic_string<>(local_2c);
  local_30 = local_30 | 1;
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

