
undefined4 * __thiscall
FUN_004822f0(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847500;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_005ab360(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = CameraPodClass::vftable;
  FUN_00589430(param_1 + 0xe);
  local_8._0_1_ = 1;
  FUN_00589800(0x6df5d19b,0x73accd30,param_1 + 0x5c,*(undefined4 *)(param_2 + 0x170));
  FUN_00589800(0x6df5d19b,0x487f8e17,param_1 + 0x5d,*(undefined4 *)(param_2 + 0x174));
  FUN_00589800(0x6df5d19b,0xde687e15,param_1 + 0x5e,*(undefined4 *)(param_2 + 0x178));
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00589530();
  ExceptionList = local_10;
  return param_1;
}

