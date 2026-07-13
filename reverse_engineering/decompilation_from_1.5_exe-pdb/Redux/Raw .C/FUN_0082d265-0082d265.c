
int FUN_0082d265(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 *local_8;
  
  piVar3 = (int *)FUN_0082c4a6(param_1,param_2);
  iVar4 = FUN_0082c405(piVar3,param_3,&local_8);
  if (iVar4 != 0) {
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -0x10;
    puVar1 = *(undefined4 **)(param_1 + 8);
    *local_8 = *puVar1;
    local_8[1] = puVar1[1];
    local_8[2] = puVar1[2];
    if (((3 < (*(int **)(param_1 + 8))[2]) &&
        (iVar2 = **(int **)(param_1 + 8), (*(byte *)(iVar2 + 5) & 3) != 0)) &&
       ((*(byte *)(*piVar3 + 5) & 4) != 0)) {
      FUN_0083001b(param_1,*piVar3,iVar2);
    }
  }
  return iVar4;
}

