
void FUN_00839a51(int param_1)

{
  byte *pbVar1;
  int iVar2;
  undefined4 uVar3;
  byte bVar4;
  int *piVar5;
  
  iVar2 = *(int *)(param_1 + 0x30);
  bVar4 = 0;
  piVar5 = *(int **)(iVar2 + 0x14);
  if (piVar5 != (int *)0x0) {
    do {
      if (*(char *)((int)piVar5 + 10) != '\0') break;
      pbVar1 = (byte *)((int)piVar5 + 9);
      piVar5 = (int *)*piVar5;
      bVar4 = bVar4 | *pbVar1;
    } while (piVar5 != (int *)0x0);
    if (piVar5 != (int *)0x0) goto LAB_00839a89;
  }
  FUN_008390b7(param_1,"no loop to break");
LAB_00839a89:
  if (bVar4 != 0) {
    FUN_0083c5d2(iVar2,0x23,(char)piVar5[2],0,0);
  }
  uVar3 = FUN_0083c9bd(iVar2);
  FUN_0083c626(iVar2,piVar5 + 1,uVar3);
  return;
}

