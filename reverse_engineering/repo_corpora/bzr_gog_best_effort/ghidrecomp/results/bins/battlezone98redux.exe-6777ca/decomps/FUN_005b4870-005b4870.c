
void __fastcall FUN_005b4870(int param_1)

{
  char cVar1;
  int iVar2;
  void *pvVar3;
  undefined4 local_24;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008477f8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar2 = FUN_004624b0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (*(float *)(iVar2 + 4) <= 10.0) {
    pvVar3 = operator_new(0x134);
    local_8 = 1;
    if (pvVar3 == (void *)0x0) {
      local_24 = 0;
    }
    else {
      local_24 = FUN_00608580(*(undefined4 *)(param_1 + 0x20));
    }
    *(undefined4 *)(param_1 + 0x2c) = local_24;
  }
  else {
    pvVar3 = operator_new(0x134);
    local_8 = 0;
    if (pvVar3 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_00608990(*(undefined4 *)(param_1 + 0x20));
    }
    *(undefined4 *)(param_1 + 0x2c) = local_1c;
  }
  local_8 = 0xffffffff;
  cVar1 = FUN_00475000();
  if (cVar1 == '\0') {
    *(undefined4 *)(param_1 + 0x1c) = 8;
  }
  ExceptionList = local_10;
  return;
}

