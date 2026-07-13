
int FUN_0083b012(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  
  piVar1 = *(int **)(param_1 + 0x30);
  iVar2 = *piVar1;
  iVar5 = *(int *)(iVar2 + 0x38);
  if (iVar5 < (short)piVar1[0xc] + 1) {
    uVar3 = FUN_008387f7(*(undefined4 *)(param_1 + 0x34),*(undefined4 *)(iVar2 + 0x18),
                         (int *)(iVar2 + 0x38),0xc,0x7fff,"too many local variables");
    *(undefined4 *)(iVar2 + 0x18) = uVar3;
  }
  if (iVar5 < *(int *)(iVar2 + 0x38)) {
    iVar4 = iVar5 * 0xc;
    do {
      *(undefined4 *)(iVar4 + *(int *)(iVar2 + 0x18)) = 0;
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + 0xc;
    } while (iVar5 < *(int *)(iVar2 + 0x38));
  }
  *(int *)((short)piVar1[0xc] * 0xc + *(int *)(iVar2 + 0x18)) = param_2;
  if (((*(byte *)(param_2 + 5) & 3) != 0) && ((*(byte *)(iVar2 + 5) & 4) != 0)) {
    FUN_0083001b(*(undefined4 *)(param_1 + 0x34),iVar2,param_2);
  }
  iVar2 = piVar1[0xc];
  *(short *)(piVar1 + 0xc) = (short)iVar2 + 1;
  return (int)(short)iVar2;
}

