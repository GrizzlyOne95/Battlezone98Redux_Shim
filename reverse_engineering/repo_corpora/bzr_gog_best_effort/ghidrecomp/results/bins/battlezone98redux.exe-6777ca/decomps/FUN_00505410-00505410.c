
undefined4 FUN_00505410(int *param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_004ff750(param_3,param_4);
  iVar2 = FUN_004da060(uVar1);
  if (iVar2 != 0) {
    if (param_2 <= *param_1 + 4U) {
      return 0;
    }
    *(char *)(*param_1 + -1) = *(char *)(*param_1 + -1) + '\x01';
    uVar1 = FUN_004b9a90();
    *(undefined4 *)*param_1 = uVar1;
    *param_1 = *param_1 + 4;
  }
  return 1;
}

