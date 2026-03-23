
undefined4 FUN_006fc980(undefined4 param_1)

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
  pvVar1 = operator_new(0x38);
  local_8 = 0;
  if (pvVar1 == (void *)0x0) {
    local_18 = 0;
  }
  else {
    local_18 = FUN_006ffae0(param_1);
  }
  ExceptionList = local_10;
  return local_18;
}

