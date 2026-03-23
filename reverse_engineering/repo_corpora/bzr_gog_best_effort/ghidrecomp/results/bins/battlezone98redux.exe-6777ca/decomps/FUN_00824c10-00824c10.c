
void FUN_00824c10(int param_1,int *param_2,int param_3,int param_4)

{
  while( true ) {
    if (param_3 == 0) break;
    *param_2 = param_1;
    param_1 = param_4 * 100 + param_1;
    param_2 = param_2 + 1;
    param_3 = param_3 + -1;
  }
  return;
}

