
int __thiscall
FUN_0043aa30(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  int iVar1;
  int iVar2;
  
  if (DAT_00915594 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_0043af00(param_2,param_3,param_4,0,param_1);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar2 = FUN_0043b520(DAT_00915594,iVar1,param_5);
      if (iVar2 == 0) {
        FUN_0043b010(iVar1);
        iVar1 = 0;
      }
    }
  }
  return iVar1;
}

