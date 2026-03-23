
void __fastcall FUN_006c8d50(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00849b78;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  if (*(char *)(param_1 + 4) != '\0') {
    FUN_006ac0f0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  }
  local_8 = 0xffffffff;
  FUN_00417c60();
  ExceptionList = local_10;
  return;
}

