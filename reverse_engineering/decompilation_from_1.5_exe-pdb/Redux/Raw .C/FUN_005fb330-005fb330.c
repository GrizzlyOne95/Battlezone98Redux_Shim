
void __fastcall FUN_005fb330(int param_1)

{
  int iVar1;
  void *pvVar2;
  float10 fVar3;
  undefined4 local_24;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008477f8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (*(int *)(*(int *)(param_1 + 0x34) + 0xac) == 2) {
    FUN_004dbc00(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  }
  fVar3 = (float10)FUN_00822d80();
  *(float *)(param_1 + 0x4c) = (float)fVar3;
  iVar1 = FUN_004624b0();
  if (*(float *)(iVar1 + 4) <= 10.0) {
    pvVar2 = operator_new(0x134);
    local_8 = 1;
    if (pvVar2 == (void *)0x0) {
      local_24 = 0;
    }
    else {
      local_24 = FUN_00608580(*(undefined4 *)(param_1 + 0x34));
    }
    *(undefined4 *)(param_1 + 0x38) = local_24;
  }
  else {
    pvVar2 = operator_new(0x134);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_00608990(*(undefined4 *)(param_1 + 0x34));
    }
    *(undefined4 *)(param_1 + 0x38) = local_1c;
  }
  ExceptionList = local_10;
  return;
}

