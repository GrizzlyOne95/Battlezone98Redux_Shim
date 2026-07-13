
void __fastcall FUN_005a4620(int param_1)

{
  undefined4 uVar1;
  void *pvVar2;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008477bc;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = FUN_005a3b40(*(undefined4 *)(param_1 + 0x34),DAT_008e7000 ^ (uint)&stack0xfffffffc);
  *(undefined4 *)(param_1 + 0x80) = uVar1;
  pvVar2 = operator_new(0x14c);
  local_8 = 0;
  if (pvVar2 == (void *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = FUN_005a5630(*(undefined4 *)(param_1 + 0x34),*(undefined4 *)(param_1 + 0x80));
  }
  *(undefined4 *)(param_1 + 0x38) = local_1c;
  *(undefined1 *)(param_1 + 0x7c) = 0;
  ExceptionList = local_10;
  return;
}

