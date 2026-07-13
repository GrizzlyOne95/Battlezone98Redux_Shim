
void __fastcall FUN_006a2950(undefined4 *param_1)

{
  char cVar1;
  uint uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084d208;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = FindSendPoints::vftable;
  local_8 = 0;
  if (DAT_009310a8 != 0) {
    operator_delete__((void *)DAT_009310a8);
  }
  DAT_009310a8 = 0;
  while( true ) {
    cVar1 = FUN_0041fc90(uVar2);
    if (cVar1 != '\0') break;
    FUN_006a6400();
  }
  local_8 = 0xffffffff;
  FUN_00461630();
  ExceptionList = local_10;
  return;
}

