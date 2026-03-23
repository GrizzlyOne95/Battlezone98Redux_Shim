
undefined4 * __thiscall FUN_00733420(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00849b78;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = param_2[1];
  *param_1 = *param_2;
  param_1[1] = uVar1;
  local_8 = 0;
  FUN_00700b10(param_2 + 2);
  ExceptionList = local_10;
  return param_1;
}

