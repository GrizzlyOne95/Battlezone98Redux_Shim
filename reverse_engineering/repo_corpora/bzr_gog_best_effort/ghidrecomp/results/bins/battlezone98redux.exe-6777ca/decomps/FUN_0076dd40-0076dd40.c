
void FUN_0076dd40(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_1c [8];
  undefined1 local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085db78;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_0048a850(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  FID_conflict_begin(local_14);
  while( true ) {
    uVar2 = FID_conflict_end(local_1c);
    cVar1 = FID_conflict_operator__(uVar2);
    if (cVar1 == '\0') break;
    uVar2 = FUN_00421ec0();
    FUN_006cae50(uVar2);
    FUN_0076fa50();
  }
  FUN_0076e4a0();
  local_8 = 0xffffffff;
  FUN_0048a040();
  ExceptionList = local_10;
  return;
}

