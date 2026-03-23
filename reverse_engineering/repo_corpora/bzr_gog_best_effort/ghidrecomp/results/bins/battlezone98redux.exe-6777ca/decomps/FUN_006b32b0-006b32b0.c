
undefined4 __thiscall FUN_006b32b0(int *param_1,undefined4 param_2)

{
  bad_cast local_20 [12];
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850679;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_14 = param_1;
  if (*param_1 != 0) {
    std::bad_cast::bad_cast(local_20,"bad cast");
    local_8 = 0;
    FUN_006d95c0(local_20);
    local_8 = 0xffffffff;
    std::bad_cast::~bad_cast(local_20);
  }
  _Callable_base<>(local_14 + 1);
  ExceptionList = local_10;
  return param_2;
}

