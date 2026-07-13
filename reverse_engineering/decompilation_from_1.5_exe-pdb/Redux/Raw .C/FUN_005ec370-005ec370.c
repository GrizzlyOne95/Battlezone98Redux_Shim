
void __fastcall FUN_005ec370(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084c378;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = Tug::vftable;
  param_1[6] = Tug::vftable;
  local_8 = 0;
  FUN_005ed4b0(0);
  local_8 = 0xffffffff;
  FUN_004e9ef0(uVar1);
  ExceptionList = local_10;
  return;
}

