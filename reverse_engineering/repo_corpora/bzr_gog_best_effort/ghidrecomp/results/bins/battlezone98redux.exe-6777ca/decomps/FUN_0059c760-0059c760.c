
undefined4 FUN_0059c760(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  void *pvVar1;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084711c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  pvVar1 = operator_new(0x158);
  local_8 = 0;
  if (pvVar1 == (void *)0x0) {
    local_18 = 0;
  }
  else {
    local_18 = FUN_0059c8e0(param_1,param_2,param_3);
  }
  ExceptionList = local_10;
  return local_18;
}

