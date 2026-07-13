
undefined4 __thiscall FUN_006b3340(int *param_1,undefined4 param_2)

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
  if (*param_1 != 1) {
    std::bad_cast::bad_cast(local_20,"bad cast");
    local_8 = 0;
    FUN_006d95c0(local_20);
    local_8 = 0xffffffff;
    std::bad_cast::~bad_cast(local_20);
  }
  FUN_006b2f70(local_14 + 2);
  ExceptionList = local_10;
  return param_2;
}

