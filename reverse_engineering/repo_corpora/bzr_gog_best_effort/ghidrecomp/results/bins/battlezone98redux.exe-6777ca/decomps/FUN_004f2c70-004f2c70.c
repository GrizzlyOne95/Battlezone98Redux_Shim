
void __fastcall FUN_004f2c70(undefined4 *param_1)

{
  char cVar1;
  uint uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084a638;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = ImageRefract::vftable;
  local_8 = 0;
  cVar1 = FUN_004f2ce0(uVar2);
  if (cVar1 != '\0') {
    FUN_004f2d70();
  }
  local_8 = 0xffffffff;
  FUN_005d9780();
  ExceptionList = local_10;
  return;
}

