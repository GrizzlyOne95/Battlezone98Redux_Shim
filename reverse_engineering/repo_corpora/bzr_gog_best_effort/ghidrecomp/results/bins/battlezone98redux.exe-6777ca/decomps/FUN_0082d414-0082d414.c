
undefined4 FUN_0082d414(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  
  puVar2 = (undefined4 *)FUN_0082c4a6(param_1,param_2);
  iVar1 = puVar2[2];
  if (iVar1 != 2) {
    if ((iVar1 != 5) && (iVar1 != 6)) {
      if (iVar1 == 7) goto LAB_0082d441;
      if (iVar1 != 8) {
        return 0;
      }
    }
    return *puVar2;
  }
LAB_0082d441:
  uVar3 = FUN_0082d465();
  return uVar3;
}

