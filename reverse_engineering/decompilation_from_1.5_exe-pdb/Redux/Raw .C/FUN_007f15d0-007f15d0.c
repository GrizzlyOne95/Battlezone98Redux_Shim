
undefined1 __thiscall FUN_007f15d0(undefined4 param_1,undefined4 param_2,long *param_3)

{
  undefined1 uVar1;
  char cVar2;
  long lVar3;
  
  uVar1 = FUN_007f2170(*param_3,0,0,param_1);
  uVar1 = FUN_007f2150(*param_3,uVar1);
  cVar2 = FUN_007f2190(param_2,uVar1);
  if (cVar2 != '\0') {
    lVar3 = abs(*param_3);
    cVar2 = FUN_007f2210(param_2,lVar3);
    if (cVar2 != '\0') {
      return 1;
    }
  }
  return 0;
}

