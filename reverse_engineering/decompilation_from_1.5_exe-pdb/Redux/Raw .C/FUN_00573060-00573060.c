
undefined1 __thiscall FUN_00573060(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int *piVar2;
  
  piVar2 = (int *)FUN_0045ca50(param_1);
  if (piVar2 == (int *)0x0) {
    uVar1 = 0;
  }
  else {
    uVar1 = (**(code **)(*piVar2 + 0x44))(param_2);
  }
  return uVar1;
}

