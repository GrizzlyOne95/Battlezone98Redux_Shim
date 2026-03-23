
void __fastcall FUN_004cc040(int param_1)

{
  int iVar1;
  void *pvVar2;
  undefined4 local_24;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008477f8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00475000(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  iVar1 = FUN_004624b0();
  if (*(float *)(iVar1 + 4) <= 10.0) {
    pvVar2 = operator_new(0x134);
    local_8 = 1;
    if (pvVar2 == (void *)0x0) {
      local_24 = 0;
    }
    else {
      local_24 = FUN_00608580(*(undefined4 *)(param_1 + 0x20));
    }
    *(undefined4 *)(param_1 + 0x2c) = local_24;
  }
  else {
    pvVar2 = operator_new(0x134);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_00608990(*(undefined4 *)(param_1 + 0x20));
    }
    *(undefined4 *)(param_1 + 0x2c) = local_1c;
  }
  ExceptionList = local_10;
  return;
}

