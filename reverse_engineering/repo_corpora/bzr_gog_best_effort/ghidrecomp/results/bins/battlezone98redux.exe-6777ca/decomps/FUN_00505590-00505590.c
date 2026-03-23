
bool FUN_00505590(int *param_1,uint param_2,undefined4 param_3)

{
  bool bVar1;
  
  bVar1 = *param_1 + 4U < param_2;
  if (bVar1) {
    *(char *)(*param_1 + -1) = *(char *)(*param_1 + -1) + '\x04';
    *(undefined4 *)*param_1 = param_3;
    *param_1 = *param_1 + 4;
  }
  return bVar1;
}

