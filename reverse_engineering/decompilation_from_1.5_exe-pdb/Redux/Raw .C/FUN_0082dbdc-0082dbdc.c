
undefined4 FUN_0082dbdc(undefined4 param_1,int param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  
  if (((((*(int **)(param_2 + 4))[2] != 6) || (*(char *)(**(int **)(param_2 + 4) + 6) != '\0')) ||
      (*(int *)(param_2 + 0x14) < 1)) &&
     (((*(int **)(param_2 + -0x14))[2] == 6 && (*(char *)(**(int **)(param_2 + -0x14) + 6) == '\0'))
     )) {
    iVar2 = FUN_0082dad3(param_1,param_2 + -0x18);
    uVar1 = *(uint *)(*(int *)(*(int *)(**(int **)(param_2 + -0x14) + 0x10) + 0xc) + iVar2 * 4);
    uVar4 = uVar1 & 0x3f;
    if ((uVar4 == 0x1c) || ((uVar4 == 0x1d || (uVar4 == 0x21)))) {
      uVar3 = FUN_0082dc7a(param_1,param_2 + -0x18,uVar1 >> 6 & 0xff,param_3);
      return uVar3;
    }
  }
  return 0;
}

