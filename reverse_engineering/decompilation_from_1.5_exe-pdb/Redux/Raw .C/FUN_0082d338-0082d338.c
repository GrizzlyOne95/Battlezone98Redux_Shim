
int FUN_0082d338(undefined4 param_1,undefined4 param_2)

{
  double *pdVar1;
  undefined1 local_20 [28];
  
  pdVar1 = (double *)FUN_0082c4a6(param_1,param_2);
  if ((*(int *)(pdVar1 + 1) != 3) &&
     (pdVar1 = (double *)FUN_0083332e(pdVar1,local_20), pdVar1 == (double *)0x0)) {
    return 0;
  }
  return (int)ROUND(*pdVar1);
}

