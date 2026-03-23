
int FUN_00830cca(undefined4 param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  
  if (param_3[2] == 0) {
    iVar1 = -1;
  }
  else {
    iVar1 = FUN_00830c5b(param_3);
    if ((iVar1 < 1) || (*(int *)(param_2 + 0x1c) < iVar1)) {
      iVar1 = FUN_00831196(param_2,param_3);
      do {
        iVar2 = FUN_0082eafa(iVar1 + 0x10,param_3);
        if ((iVar2 != 0) ||
           (((*(int *)(iVar1 + 0x18) == 0xb && (3 < param_3[2])) &&
            (*(int *)(iVar1 + 0x10) == *param_3)))) {
          return (iVar1 - *(int *)(param_2 + 0x10) >> 5) + *(int *)(param_2 + 0x1c);
        }
        iVar1 = *(int *)(iVar1 + 0x1c);
      } while (iVar1 != 0);
      FUN_0082df5b(param_1,"invalid key to \'next\'");
      iVar1 = 0;
    }
    else {
      iVar1 = iVar1 + -1;
    }
  }
  return iVar1;
}

