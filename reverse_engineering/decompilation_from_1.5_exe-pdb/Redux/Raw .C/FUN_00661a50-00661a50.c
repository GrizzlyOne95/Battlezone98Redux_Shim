
void __fastcall FUN_00661a50(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0084da36;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = EntityTransparencyMaterial::vftable;
  local_8 = 1;
  FUN_006621b0(uVar1);
  local_8 = local_8 & 0xffffff00;
  FUN_004499a0();
  local_8 = 0xffffffff;
  FUN_004499a0();
  ExceptionList = local_10;
  return;
}

