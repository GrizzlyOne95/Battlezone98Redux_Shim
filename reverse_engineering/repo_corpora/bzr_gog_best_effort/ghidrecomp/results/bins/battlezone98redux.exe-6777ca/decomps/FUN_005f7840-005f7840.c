
void __fastcall FUN_005f7840(int param_1)

{
  undefined4 uVar1;
  void *pvVar2;
  float10 fVar3;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084d0bc;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  (**(code **)(**(int **)(param_1 + 0x34) + 0x60))(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  uVar1 = FUN_00462630(*(undefined4 *)(param_1 + 0x3c));
  pvVar2 = operator_new(0x134);
  local_8 = 0;
  if (pvVar2 == (void *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = FUN_005f7b90(*(undefined4 *)(param_1 + 0x34),uVar1);
  }
  local_8 = 0xffffffff;
  *(undefined4 *)(param_1 + 0x38) = local_1c;
  fVar3 = (float10)FUN_00822d80();
  *(float *)(param_1 + 0x88) = (float)fVar3 + 3.0;
  ExceptionList = local_10;
  return;
}

