
undefined4 * FUN_00497660(int param_1,int param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  while (param_1 != param_2) {
    param_2 = param_2 + -8;
    puVar2 = (undefined4 *)FUN_00417780(param_2);
    uVar1 = puVar2[1];
    param_3[-2] = *puVar2;
    param_3[-1] = uVar1;
    param_3 = param_3 + -2;
  }
  return param_3;
}

