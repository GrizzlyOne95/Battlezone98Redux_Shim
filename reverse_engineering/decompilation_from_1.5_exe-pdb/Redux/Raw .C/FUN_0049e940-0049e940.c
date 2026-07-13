
void __fastcall FUN_0049e940(int param_1)

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
  FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0x13,0,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  pvVar1 = operator_new(0x158);
  local_8 = 0;
  if (pvVar1 == (void *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = FUN_0049dfa0(*(undefined4 *)(param_1 + 0x34),*(undefined4 *)(param_1 + 0x10),
                            *(undefined4 *)(param_1 + 0x44));
  }
  *(undefined4 *)(param_1 + 0x38) = local_1c;
  ExceptionList = local_10;
  return;
}

