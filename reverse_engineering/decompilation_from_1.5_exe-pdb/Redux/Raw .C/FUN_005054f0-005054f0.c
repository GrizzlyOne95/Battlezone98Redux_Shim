
bool FUN_005054f0(int *param_1,uint param_2,undefined1 param_3)

{
  bool bVar1;
  
  bVar1 = *param_1 + 1U < param_2;
  if (bVar1) {
    *(char *)(*param_1 + -1) = *(char *)(*param_1 + -1) + '\x01';
    *(undefined1 *)*param_1 = param_3;
    *param_1 = *param_1 + 1;
  }
  return bVar1;
}

