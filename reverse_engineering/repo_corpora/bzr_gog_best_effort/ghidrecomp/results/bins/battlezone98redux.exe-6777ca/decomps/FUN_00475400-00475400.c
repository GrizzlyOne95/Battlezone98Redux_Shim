
void __fastcall FUN_00475400(int param_1)

{
  char cVar1;
  int iVar2;
  void *pvVar3;
  undefined4 local_28;
  undefined4 local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847838;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  cVar1 = FUN_00475000(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  iVar2 = FUN_004624b0();
  if (*(float *)(iVar2 + 4) <= 10.0) {
    pvVar3 = operator_new(0x134);
    local_8 = 1;
    if (pvVar3 == (void *)0x0) {
      local_28 = 0;
    }
    else {
      local_28 = FUN_00608580(*(undefined4 *)(param_1 + 0x20));
    }
    *(undefined4 *)(param_1 + 0x28) = local_28;
  }
  else {
    pvVar3 = operator_new(0x134);
    local_8 = 0;
    if (pvVar3 == (void *)0x0) {
      local_20 = 0;
    }
    else {
      local_20 = FUN_00608990(*(undefined4 *)(param_1 + 0x20));
    }
    *(undefined4 *)(param_1 + 0x28) = local_20;
  }
  if (cVar1 == '\0') {
    *(undefined4 *)(param_1 + 0x1c) = 8;
  }
  ExceptionList = local_10;
  return;
}

