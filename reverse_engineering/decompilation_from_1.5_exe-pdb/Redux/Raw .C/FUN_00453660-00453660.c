
void __fastcall FUN_00453660(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00846218;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = ShockRenderClass::vftable;
  local_8 = 0;
  FUN_004499a0(uVar1);
  local_8 = 0xffffffff;
  FUN_0044e1d0();
  ExceptionList = local_10;
  return;
}

