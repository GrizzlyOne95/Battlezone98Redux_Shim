
float10 __fastcall FUN_00461110(int param_1)

{
  float10 fVar1;
  undefined8 uVar2;
  float local_10;
  int local_8;
  
  local_10 = 0.0;
  for (local_8 = 1; local_8 < *(int *)(param_1 + 4); local_8 = local_8 + 1) {
    uVar2 = FUN_00444e40(*(undefined4 *)(*(int *)(param_1 + 8) + -8 + local_8 * 8),
                         *(undefined4 *)(*(int *)(param_1 + 8) + -4 + local_8 * 8),
                         *(undefined4 *)(*(int *)(param_1 + 8) + local_8 * 8),
                         *(undefined4 *)(*(int *)(param_1 + 8) + 4 + local_8 * 8));
    fVar1 = (float10)FUN_00460300(uVar2);
    local_10 = (float)fVar1 + local_10;
  }
  return (float10)local_10;
}

