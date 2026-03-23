
void __thiscall FUN_00472420(int param_1,int param_2,int param_3)

{
  *(int *)(param_1 + 4 + param_2 * 4) = param_3;
  if ((param_3 != 0) && (*(int *)(param_3 + 0x84) == 0x4a)) {
    *(int *)(param_1 + 0x38) = param_2;
  }
  return;
}

