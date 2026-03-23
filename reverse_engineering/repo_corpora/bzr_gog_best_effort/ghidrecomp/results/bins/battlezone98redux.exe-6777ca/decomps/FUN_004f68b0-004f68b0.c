
void __fastcall FUN_004f68b0(int param_1)

{
  void *pvVar1;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008477bc;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0050a970(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (*(int *)(param_1 + 0x60) == 0) {
    pvVar1 = operator_new(0x1150);
    local_8 = 0;
    if (pvVar1 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_0059c1f0(param_1);
    }
    *(undefined4 *)(param_1 + 0x60) = local_1c;
  }
  ExceptionList = local_10;
  return;
}

