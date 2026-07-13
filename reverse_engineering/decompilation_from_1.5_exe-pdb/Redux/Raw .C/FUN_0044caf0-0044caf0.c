
void __fastcall FUN_0044caf0(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00846648;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = LightRender::vftable;
  local_8 = 0;
  iVar2 = FUN_0044d2a0(uVar1);
  (**(code **)(**(int **)(iVar2 + 8) + 0x138))(param_1[0x1c]);
  local_8 = 0xffffffff;
  FUN_00448f70();
  ExceptionList = local_10;
  return;
}

