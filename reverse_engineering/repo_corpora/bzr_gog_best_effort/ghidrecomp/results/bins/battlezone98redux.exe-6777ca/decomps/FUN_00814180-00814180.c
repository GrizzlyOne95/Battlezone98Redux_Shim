
undefined4 __thiscall FUN_00814180(undefined4 param_1,int *param_2,undefined1 param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*param_2 < 0xccccccd) {
    *param_2 = *param_2 * 10;
    iVar2 = FUN_00814580(param_3,param_1);
    if (0x7fffffff - iVar2 < *param_2) {
      uVar1 = 0;
    }
    else {
      *param_2 = *param_2 + iVar2;
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

