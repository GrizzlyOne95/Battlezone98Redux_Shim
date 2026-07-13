
exception * __thiscall FUN_006b5120(exception *param_1,undefined4 param_2,undefined4 param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850989;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  std::exception::exception(param_1);
  local_8 = 0;
  *(undefined ***)param_1 = websocketpp::exception::vftable;
  FUN_006ab780(param_1 + 0xc);
  *(undefined4 *)(param_1 + 0x24) = param_2;
  *(undefined4 *)(param_1 + 0x28) = param_3;
  ExceptionList = local_10;
  return param_1;
}

