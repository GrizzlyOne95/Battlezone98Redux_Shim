
void FUN_0082ced4(int param_1,undefined4 param_2)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  piVar2 = (int *)FUN_0082c4a6(param_1,param_2);
  iVar1 = *(int *)(param_1 + 8);
  puVar3 = (undefined4 *)FUN_008310b4(param_1,*piVar2,iVar1 + -0x20);
  *puVar3 = *(undefined4 *)(iVar1 + -0x10);
  puVar3[1] = *(undefined4 *)(iVar1 + -0xc);
  puVar3[2] = *(undefined4 *)(iVar1 + -8);
  if (((3 < *(int *)(*(int *)(param_1 + 8) + -8)) &&
      ((*(byte *)(*(int *)(*(int *)(param_1 + 8) + -0x10) + 5) & 3) != 0)) &&
     ((*(byte *)(*piVar2 + 5) & 4) != 0)) {
    FUN_00830000(param_1,*piVar2);
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -0x20;
  return;
}

