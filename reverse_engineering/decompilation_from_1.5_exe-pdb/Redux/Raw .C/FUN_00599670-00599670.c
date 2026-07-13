
void __thiscall FUN_00599670(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0xa8) != 0) {
    FUN_00460fa0();
  }
  *(undefined4 *)(param_1 + 0xa8) = param_2;
  if (*(int *)(param_1 + 0xa8) != 0) {
    uVar1 = *(undefined4 *)(*(int *)(param_1 + 0xa8) + 4);
    FUN_00460e90(200);
    *(undefined4 *)(*(int *)(param_1 + 0xa8) + 4) = uVar1;
  }
  return;
}

