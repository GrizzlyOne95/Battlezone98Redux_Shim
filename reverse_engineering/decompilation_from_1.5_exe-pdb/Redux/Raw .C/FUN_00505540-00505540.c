
bool FUN_00505540(int *param_1,uint param_2,undefined2 param_3)

{
  bool bVar1;
  
  bVar1 = *param_1 + 2U < param_2;
  if (bVar1) {
    *(char *)(*param_1 + -1) = *(char *)(*param_1 + -1) + '\x02';
    *(undefined2 *)*param_1 = param_3;
    *param_1 = *param_1 + 2;
  }
  return bVar1;
}

