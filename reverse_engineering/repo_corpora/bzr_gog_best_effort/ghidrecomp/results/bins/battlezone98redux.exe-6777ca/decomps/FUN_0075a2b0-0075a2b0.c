
undefined4 * __fastcall FUN_0075a2b0(undefined4 *param_1)

{
  int iVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085c927;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_00758b90(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8._0_1_ = 1;
  *param_1 = BZRNetP2P::vftable;
  FUN_0073a6b0();
  FUN_0073a6b0();
  vector<>();
  local_8._0_1_ = 2;
  vector<>();
  local_8._0_1_ = 3;
  FUN_0048a380();
  local_8._0_1_ = 4;
  FUN_00422260();
  local_8._0_1_ = 5;
  <>(&stack0x00000004);
  local_8 = CONCAT31(local_8._1_3_,6);
  iVar1 = get();
  *(undefined4 **)(iVar1 + 0xc3c) = param_1;
  local_8 = 0xffffffff;
  FUN_006676c0();
  ExceptionList = local_10;
  return param_1;
}

