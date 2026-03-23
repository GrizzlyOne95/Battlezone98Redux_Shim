
undefined4 * __thiscall FUN_006e5cd0(undefined4 *param_1,undefined4 *param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853e16;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = *param_2;
  FUN_006d4f40(param_2 + 1);
  local_8 = 0;
  FUN_006d4f40(param_2 + 4);
  local_8 = CONCAT31(local_8._1_3_,1);
  param_1[7] = param_2[7];
  FUN_006e69f0(param_2 + 8);
  ExceptionList = local_10;
  return param_1;
}

