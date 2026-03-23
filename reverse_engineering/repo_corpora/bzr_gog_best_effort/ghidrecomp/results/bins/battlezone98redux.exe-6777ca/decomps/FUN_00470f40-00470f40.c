
void __thiscall FUN_00470f40(int param_1,undefined1 *param_2,int *param_3)

{
  *param_3 = *param_3 + 1;
  if (*(int *)(param_1 + 0x210) == 0) {
    *param_2 = 0;
  }
  else if (*(int *)(param_1 + 0x210) == 1) {
    *param_2 = 1;
  }
  else if (*(int *)(param_1 + 0x210) == 2) {
    *param_2 = 2;
  }
  else if (*(int *)(param_1 + 0x210) == 3) {
    *param_2 = 3;
  }
  FUN_004ef640(param_2 + 1,param_3);
  return;
}

