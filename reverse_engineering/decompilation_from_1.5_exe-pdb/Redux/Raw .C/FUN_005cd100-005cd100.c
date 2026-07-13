
void __thiscall FUN_005cd100(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_00462630(param_2,param_1);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x18))(param_3);
  }
  return;
}

