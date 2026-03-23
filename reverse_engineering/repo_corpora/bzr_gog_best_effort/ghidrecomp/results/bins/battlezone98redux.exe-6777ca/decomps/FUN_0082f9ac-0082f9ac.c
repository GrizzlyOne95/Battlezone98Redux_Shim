
int * FUN_0082f9ac(int param_1,uint param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  
  iVar2 = *(int *)(param_1 + 0x10);
  iVar3 = *(int *)(param_1 + 0x68);
  piVar4 = (int *)(param_1 + 0x68);
  while (iVar3 != 0) {
    piVar5 = (int *)*piVar4;
    if ((uint)piVar5[2] < param_2) break;
    if (piVar5[2] == param_2) {
      if ((~*(byte *)(iVar2 + 0x14) & *(byte *)((int)piVar5 + 5) & 3) != 0) {
        *(byte *)((int)piVar5 + 5) = *(byte *)((int)piVar5 + 5) ^ 3;
        return piVar5;
      }
      return piVar5;
    }
    piVar4 = piVar5;
    iVar3 = *piVar5;
  }
  piVar5 = (int *)FUN_00838869(param_1,0,0,0x20);
  *(undefined1 *)(piVar5 + 1) = 10;
  bVar1 = *(byte *)(iVar2 + 0x14);
  piVar5[2] = param_2;
  *(byte *)((int)piVar5 + 5) = bVar1 & 3;
  *piVar5 = *piVar4;
  *piVar4 = (int)piVar5;
  piVar5[4] = iVar2 + 0x78;
  iVar3 = *(int *)(iVar2 + 0x8c);
  piVar5[5] = iVar3;
  *(int **)(iVar3 + 0x10) = piVar5;
  *(int **)(iVar2 + 0x8c) = piVar5;
  return piVar5;
}

