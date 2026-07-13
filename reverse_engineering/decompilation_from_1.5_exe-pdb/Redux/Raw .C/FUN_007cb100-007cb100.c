
undefined * __fastcall FUN_007cb100(int param_1)

{
  undefined *puVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0086254e;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if ((DAT_02cc39d0 & 1) == 0) {
    DAT_02cc39d0 = DAT_02cc39d0 | 1;
    local_8 = 0;
    basic_string<>(DAT_008e7000 ^ (uint)&stack0xfffffffc);
    FUN_0083e979(FUN_008680b0);
  }
  local_8 = 0xffffffff;
  if (*(int *)(param_1 + 0x14c) < 0) {
    puVar1 = &DAT_02cc39b8;
  }
  else {
    puVar1 = (undefined *)FUN_0066b170(*(undefined4 *)(param_1 + 0x14c));
  }
  ExceptionList = local_10;
  return puVar1;
}

