
void __fastcall FUN_00461630(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00847398;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = AiProcess::vftable;
  local_8 = 0;
  if (param_1[3] != 0) {
    FUN_004db910(0);
    FUN_004dbc00();
    FUN_004dbce0(0);
  }
  FUN_0045cce0(param_1);
  local_8 = 0xffffffff;
  FUN_005d7350(uVar1);
  ExceptionList = local_10;
  return;
}

