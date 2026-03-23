
undefined4 FUN_0082d08e(int param_1,undefined4 param_2)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  
  uVar3 = 1;
  piVar2 = (int *)FUN_0082c4a6(param_1,param_2);
  iVar1 = piVar2[2];
  if ((iVar1 == 6) || (iVar1 == 7)) {
    *(undefined4 *)(*piVar2 + 0xc) = *(undefined4 *)(*(int *)(param_1 + 8) + -0x10);
  }
  else {
    if (iVar1 != 8) {
      uVar3 = 0;
      goto LAB_0082d0f8;
    }
    iVar1 = *piVar2;
    *(undefined4 *)(iVar1 + 0x48) = *(undefined4 *)(*(int *)(param_1 + 8) + -0x10);
    *(undefined4 *)(iVar1 + 0x50) = 5;
  }
  iVar1 = *(int *)(*(int *)(param_1 + 8) + -0x10);
  if (((*(byte *)(iVar1 + 5) & 3) != 0) && ((*(byte *)(*piVar2 + 5) & 4) != 0)) {
    FUN_0083001b(param_1,*piVar2,iVar1);
  }
LAB_0082d0f8:
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -0x10;
  return uVar3;
}

