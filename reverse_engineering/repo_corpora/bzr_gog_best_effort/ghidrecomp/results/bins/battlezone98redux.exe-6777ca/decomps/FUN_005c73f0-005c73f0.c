
void __thiscall FUN_005c73f0(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x208) = param_2;
  if (0.0 < *(float *)(param_1 + 0x208)) {
    *(float *)(param_1 + 0x200) = *(float *)(param_1 + 0x204) / *(float *)(param_1 + 0x208);
  }
  return;
}

