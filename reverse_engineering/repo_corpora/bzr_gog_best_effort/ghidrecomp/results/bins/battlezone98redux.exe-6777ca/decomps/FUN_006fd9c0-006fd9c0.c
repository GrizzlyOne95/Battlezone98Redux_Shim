
undefined4 FUN_006fd9c0(undefined4 param_1)

{
  undefined4 in_stack_00000048;
  undefined4 in_stack_0000004c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00855d48;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_00700b70(&stack0x00000008,in_stack_00000048,in_stack_0000004c);
  local_8 = 0xffffffff;
  ATL::_ATL_BASE_MODULE70::~_ATL_BASE_MODULE70((_ATL_BASE_MODULE70 *)&stack0x00000008);
  ExceptionList = local_10;
  return param_1;
}

