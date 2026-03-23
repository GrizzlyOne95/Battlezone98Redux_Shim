
undefined2 * __thiscall FUN_0083f930(undefined2 *param_1,short *param_2)

{
  short sVar1;
  short *psVar2;
  
  *(undefined4 *)(param_1 + 10) = 7;
  *(undefined4 *)(param_1 + 8) = 0;
  *param_1 = 0;
  if (*param_2 == 0) {
    FUN_0083fdc0(param_2,0);
    return param_1;
  }
  psVar2 = param_2;
  do {
    sVar1 = *psVar2;
    psVar2 = psVar2 + 1;
  } while (sVar1 != 0);
  FUN_0083fdc0(param_2,(int)psVar2 - (int)(param_2 + 1) >> 1);
  return param_1;
}

