
void __fastcall FUN_0049e070(undefined4 *param_1)

{
  char cVar1;
  uint uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00849568;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = BuildGoto::vftable;
  local_8 = 0;
  cVar1 = FUN_004723d0(uVar2);
  if (cVar1 != '\0') {
    FUN_005aed80();
  }
  local_8 = 0xffffffff;
  FUN_004e5a70();
  ExceptionList = local_10;
  return;
}

