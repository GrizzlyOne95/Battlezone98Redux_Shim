
void FUN_006a0430(short *param_1)

{
  for (; *param_1 != 0; param_1 = param_1 + 1) {
    *param_1 = param_1[1];
  }
  return;
}

