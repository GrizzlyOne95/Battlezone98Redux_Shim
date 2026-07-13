
void FUN_00437500(int param_1)

{
  if (param_1 != 0) {
    if (*(int *)(param_1 + 0x80) != 0) {
      (**(code **)(param_1 + 0x80))(param_1);
    }
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
  return;
}

