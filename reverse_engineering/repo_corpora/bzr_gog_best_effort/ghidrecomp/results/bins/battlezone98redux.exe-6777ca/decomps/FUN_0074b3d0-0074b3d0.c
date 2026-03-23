
undefined4 * __fastcall FUN_0074b3d0(undefined4 *param_1)

{
  int iVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085bbde;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_0073d690(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8._0_1_ = 1;
  *param_1 = BZRNetLobby::vftable;
  FUN_0066ae30();
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_0074d430(&stack0x00000004);
  iVar1 = get();
  *(undefined4 **)(iVar1 + 0xc38) = param_1;
  local_8 = 0xffffffff;
  FUN_006676c0();
  ExceptionList = local_10;
  return param_1;
}

