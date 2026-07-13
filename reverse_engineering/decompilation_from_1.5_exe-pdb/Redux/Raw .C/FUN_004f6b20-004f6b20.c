
void __fastcall FUN_004f6b20(int param_1)

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
  pvVar1 = operator_new(0x1150);
  local_8 = 0;
  if (pvVar1 == (void *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = FUN_0059c1f0(param_1);
  }
  *(undefined4 *)(param_1 + 0x60) = local_1c;
  *(undefined1 *)(param_1 + 100) = 1;
  *(undefined1 *)(param_1 + 0x65) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined1 *)(param_1 + 0x66) = 0;
  *(undefined1 **)(param_1 + 0x84) = &DAT_008a1ad8;
  *(undefined1 **)(param_1 + 0x88) = &DAT_008a1ad8;
  *(undefined1 **)(param_1 + 0x8c) = &DAT_008a1ad8;
  *(undefined1 **)(param_1 + 0x90) = &DAT_008a1ad8;
  *(undefined4 *)(param_1 + 0x94) = 0;
  *(undefined4 *)(param_1 + 0x98) = 0;
  *(undefined4 *)(param_1 + 0x9c) = 0;
  *(undefined1 *)(param_1 + 0xa0) = 1;
  ExceptionList = local_10;
  return;
}

