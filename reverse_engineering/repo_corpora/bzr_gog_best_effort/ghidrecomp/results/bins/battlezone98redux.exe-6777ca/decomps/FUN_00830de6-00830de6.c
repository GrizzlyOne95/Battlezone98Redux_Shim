
undefined * FUN_00830de6(undefined4 param_1,double *param_2)

{
  undefined *puVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_2 + 1);
  if (iVar2 != 0) {
    if (iVar2 == 3) {
      if ((double)(int)ROUND(*param_2) == *param_2) {
        puVar1 = (undefined *)FUN_00830ecf(param_1,(int)ROUND(*param_2));
        return puVar1;
      }
    }
    else if (iVar2 == 4) {
      puVar1 = (undefined *)FUN_00830f2e(param_1,*(undefined4 *)param_2);
      return puVar1;
    }
    puVar1 = (undefined *)FUN_00831196(param_1,param_2);
    do {
      iVar2 = FUN_0082eafa(puVar1 + 0x10,param_2);
      if (iVar2 != 0) {
        return puVar1;
      }
      puVar1 = *(undefined **)(puVar1 + 0x1c);
    } while (puVar1 != (undefined *)0x0);
  }
  return &DAT_0086ed18;
}

