
uint FUN_0082ec83(int *param_1)

{
  int iVar1;
  
  if (*param_1 == 0) {
    iVar1 = FUN_0082ec27(param_1);
    if (iVar1 == -1) {
      return 0xffffffff;
    }
    *param_1 = *param_1 + 1;
    param_1[1] = param_1[1] + -1;
  }
  return (uint)*(byte *)param_1[1];
}

