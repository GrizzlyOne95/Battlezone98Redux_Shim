
void FUN_008310b4(undefined4 param_1,int param_2,double *param_3)

{
  undefined *puVar1;
  char *pcVar2;
  
  puVar1 = (undefined *)FUN_00830de6(param_2,param_3);
  *(undefined1 *)(param_2 + 6) = 0;
  if (puVar1 != &DAT_0086ed18) {
    return;
  }
  if (*(int *)(param_3 + 1) == 0) {
    pcVar2 = "table index is nil";
  }
  else {
    if ((*(int *)(param_3 + 1) != 3) || (!NAN(*param_3))) goto LAB_00831103;
    pcVar2 = "table index is NaN";
  }
  FUN_0082df5b(param_1,pcVar2);
LAB_00831103:
  FUN_0083120f(param_1,param_2,param_3);
  return;
}

