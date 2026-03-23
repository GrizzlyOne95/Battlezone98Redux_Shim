
void __thiscall FUN_007d36d0(int param_1,undefined4 param_2,undefined4 param_3,char param_4)

{
  *(undefined4 *)(param_1 + 0xc) = param_2;
  *(undefined4 *)(param_1 + 0x10) = param_3;
  if (param_4 == '\0') {
    *(float *)(param_1 + 0x10) = *(float *)(param_1 + 0x10) * *(float *)(param_1 + 0x1c);
    if ((*(uint *)(param_1 + 0x14) & 0x20) == 0) {
      *(float *)(param_1 + 0xc) = *(float *)(param_1 + 0xc) * *(float *)(param_1 + 0x18);
    }
    else {
      *(float *)(param_1 + 0xc) = *(float *)(param_1 + 0xc) * *(float *)(param_1 + 0x1c);
    }
  }
  if (*(int *)(param_1 + 0x120) != 0) {
    (**(code **)(**(int **)(param_1 + 0x120) + 0x118))(0);
    FUN_007d2e20();
    (**(code **)(**(int **)(param_1 + 0x120) + 0x16c))();
  }
  return;
}

