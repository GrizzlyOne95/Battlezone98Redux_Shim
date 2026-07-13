
void __fastcall FUN_00613c10(int param_1)

{
  undefined4 uVar1;
  void *pvVar2;
  undefined4 local_28;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084d308;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = FUN_00462630(*(undefined4 *)(param_1 + 0x3c),DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (*(int *)(param_1 + 0x24) == 8) {
    pvVar2 = operator_new(0x134);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_006143d0(*(undefined4 *)(param_1 + 0x34),uVar1);
    }
    *(undefined4 *)(param_1 + 0x38) = local_1c;
  }
  else {
    pvVar2 = operator_new(0x140);
    local_8 = 1;
    if (pvVar2 == (void *)0x0) {
      local_28 = 0;
    }
    else {
      local_28 = FUN_00477e60(*(undefined4 *)(param_1 + 0x34),uVar1);
    }
    *(undefined4 *)(param_1 + 0x38) = local_28;
  }
  ExceptionList = local_10;
  return;
}

