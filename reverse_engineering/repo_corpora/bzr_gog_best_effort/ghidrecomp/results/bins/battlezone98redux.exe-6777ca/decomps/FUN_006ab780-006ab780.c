
undefined4 FUN_006ab780(undefined4 param_1)

{
  int *piVar1;
  undefined4 uVar2;
  undefined4 extraout_var;
  
  uVar2 = 0;
  piVar1 = (int *)FUN_00416410(0);
  uVar2 = get(uVar2,piVar1,extraout_var);
  (**(code **)(*piVar1 + 8))(param_1,uVar2);
  return param_1;
}

