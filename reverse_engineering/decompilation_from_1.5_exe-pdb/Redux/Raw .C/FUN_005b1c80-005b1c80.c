
void __fastcall FUN_005b1c80(undefined4 *param_1)

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
  *param_1 = RadarDamper::vftable;
  local_8 = 0;
  cVar1 = FUN_005b1cf0(uVar2);
  if (cVar1 != '\0') {
    FUN_005b1d60();
  }
  local_8 = 0xffffffff;
  FUN_005d9780();
  ExceptionList = local_10;
  return;
}

