
void __thiscall FUN_0083d680(int param_1,undefined4 *param_2)

{
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = *(undefined4 *)(param_1 + 0x44);
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + -1;
    *(undefined4 **)(param_1 + 0x44) = param_2;
  }
  return;
}

