
void FUN_0083abfa(int param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = *(int *)(param_1 + 0x34);
  iVar3 = FUN_0082fbf2(iVar1);
  *param_2 = iVar3;
  param_2[2] = *(int *)(param_1 + 0x30);
  param_2[3] = param_1;
  param_2[4] = iVar1;
  *(int **)(param_1 + 0x30) = param_2;
  param_2[7] = -1;
  param_2[8] = -1;
  param_2[6] = 0;
  param_2[9] = 0;
  param_2[10] = 0;
  param_2[0xb] = 0;
  *(undefined2 *)(param_2 + 0xc) = 0;
  *(undefined1 *)((int)param_2 + 0x32) = 0;
  param_2[5] = 0;
  *(undefined4 *)(iVar3 + 0x20) = *(undefined4 *)(param_1 + 0x40);
  *(undefined1 *)(iVar3 + 0x4b) = 2;
  iVar4 = FUN_00830f66(iVar1,0,0);
  param_2[1] = iVar4;
  piVar2 = *(int **)(iVar1 + 8);
  *piVar2 = iVar4;
  piVar2[2] = 5;
  if (*(int *)(iVar1 + 0x1c) - *(int *)(iVar1 + 8) < 0x11) {
    FUN_0082f194(iVar1,1);
  }
  *(int *)(iVar1 + 8) = *(int *)(iVar1 + 8) + 0x10;
  piVar2 = *(int **)(iVar1 + 8);
  *piVar2 = iVar3;
  piVar2[2] = 9;
  if (*(int *)(iVar1 + 0x1c) - *(int *)(iVar1 + 8) < 0x11) {
    FUN_0082f194(iVar1,1);
  }
  *(int *)(iVar1 + 8) = *(int *)(iVar1 + 8) + 0x10;
  return;
}

