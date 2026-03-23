
undefined4 * __thiscall
FUN_006cce50(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00852c71;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = param_2;
  basic_string<>(param_3);
  local_8 = 0;
  basic_string<>(param_4);
  local_8._0_1_ = 1;
  basic_string<>(param_5);
  local_8 = CONCAT31(local_8._1_3_,2);
  basic_string<>(param_6);
  ExceptionList = local_10;
  return param_1;
}

