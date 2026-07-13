
undefined4 * __fastcall FUN_00750900(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c016;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0073d690(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = CSteamLobby::vftable;
  FUN_00751d60(param_1,FUN_007518a0);
  local_8._0_1_ = 1;
  FUN_00751df0(param_1,FUN_007519d0);
  local_8._0_1_ = 2;
  FUN_00751e80(param_1,FUN_00751a60);
  local_8._0_1_ = 3;
  FUN_00751f10(param_1,FUN_00751b30);
  local_8._0_1_ = 4;
  FUN_00751fa0(param_1,FUN_00751930);
  local_8._0_1_ = 5;
  FUN_00752030(param_1,FUN_00750f90);
  local_8._0_1_ = 6;
  FUN_007520c0(param_1,FUN_00751050);
  local_8._0_1_ = 7;
  FUN_00752150(param_1,FUN_007514b0);
  local_8._0_1_ = 8;
  FUN_007521e0();
  local_8 = CONCAT31(local_8._1_3_,9);
  FUN_00752370();
  ExceptionList = local_10;
  return param_1;
}

