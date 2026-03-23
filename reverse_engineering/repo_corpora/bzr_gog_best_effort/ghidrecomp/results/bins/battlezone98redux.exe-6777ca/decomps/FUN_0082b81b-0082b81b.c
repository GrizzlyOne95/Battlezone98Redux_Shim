
void FUN_0082b81b(int *param_1,undefined1 *param_2,int param_3)

{
  while (param_3 != 0) {
    param_3 = param_3 + -1;
    if (param_1 + 0x83 <= (int *)*param_1) {
      FUN_0082c2ac(param_1);
    }
    *(undefined1 *)*param_1 = *param_2;
    *param_1 = *param_1 + 1;
    param_2 = param_2 + 1;
  }
  return;
}

