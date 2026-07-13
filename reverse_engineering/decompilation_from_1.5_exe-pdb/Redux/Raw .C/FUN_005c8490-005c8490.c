
undefined4 __thiscall FUN_005c8490(undefined4 param_1,int *param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*param_2 == 0) {
    uVar1 = 0;
  }
  else {
    iVar2 = FUN_00462630(*param_2,param_1);
    if (iVar2 == 0) {
      *param_2 = 0;
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  return uVar1;
}

