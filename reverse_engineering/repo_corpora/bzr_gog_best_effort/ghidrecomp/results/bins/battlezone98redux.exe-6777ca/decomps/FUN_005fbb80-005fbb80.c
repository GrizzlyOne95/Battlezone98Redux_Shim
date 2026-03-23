
void __fastcall FUN_005fbb80(int param_1)

{
  void *pvVar1;
  undefined4 uVar2;
  undefined4 local_24;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084d148;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (*(int *)(param_1 + 0x3c) == 0) {
    pvVar1 = operator_new(0x134);
    local_8 = 0;
    if (pvVar1 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_00608580(*(undefined4 *)(param_1 + 0x34));
    }
    *(undefined4 *)(param_1 + 0x38) = local_1c;
  }
  else {
    uVar2 = FUN_00462630(*(undefined4 *)(param_1 + 0x3c),DAT_008e7000 ^ (uint)&stack0xfffffffc);
    pvVar1 = operator_new(0x134);
    local_8 = 1;
    if (pvVar1 == (void *)0x0) {
      local_24 = 0;
    }
    else {
      local_24 = FUN_004b0f40(*(undefined4 *)(param_1 + 0x34),uVar2);
    }
    *(undefined4 *)(param_1 + 0x38) = local_24;
  }
  ExceptionList = local_10;
  return;
}

