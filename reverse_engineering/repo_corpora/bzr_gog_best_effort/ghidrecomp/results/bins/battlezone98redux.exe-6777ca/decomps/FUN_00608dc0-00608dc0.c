
void __fastcall FUN_00608dc0(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084d208;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = UserProcess::vftable;
  local_8 = 0;
  iVar2 = FUN_00417ca0(uVar1);
  if (iVar2 != 0) {
    FUN_004d9880(0);
  }
  local_8 = 0xffffffff;
  FUN_00461630();
  ExceptionList = local_10;
  return;
}

