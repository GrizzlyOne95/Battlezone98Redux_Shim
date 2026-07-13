
void __thiscall FUN_00461890(int param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 8) = param_2;
  FUN_0045ccc0(param_1);
  *(undefined4 *)(param_1 + 0xc) = param_3;
  *(undefined4 *)(param_1 + 0x14) = 0;
  if (*(int *)(param_1 + 0xc) != 0) {
    FUN_004db910(param_1);
  }
  return;
}

