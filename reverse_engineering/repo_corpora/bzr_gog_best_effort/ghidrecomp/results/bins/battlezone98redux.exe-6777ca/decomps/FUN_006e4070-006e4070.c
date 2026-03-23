
undefined4 * __thiscall
FUN_006e4070(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853e16;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  allocator<>(param_5);
  *param_1 = param_2;
  FUN_006d4f40(param_3);
  local_8 = 0;
  FUN_006d4f40(param_4);
  local_8 = CONCAT31(local_8._1_3_,1);
  param_1[7] = 0;
  FUN_006e5140(param_6);
  ExceptionList = local_10;
  return param_1;
}

