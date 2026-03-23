
void FUN_0074eb40(void)

{
  int *piVar1;
  undefined1 auStack_f8 [4];
  undefined4 uStack_f4;
  uint uStack_f0;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085bf6b;
  local_10 = ExceptionList;
  uStack_f0 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  uStack_f4 = 0x74eb7e;
  piVar1 = (int *)FUN_0074db30();
  FUN_0073a9b0(auStack_f8);
  (**(code **)(*piVar1 + 0x1c))();
  FUN_0074ec92();
  return;
}

