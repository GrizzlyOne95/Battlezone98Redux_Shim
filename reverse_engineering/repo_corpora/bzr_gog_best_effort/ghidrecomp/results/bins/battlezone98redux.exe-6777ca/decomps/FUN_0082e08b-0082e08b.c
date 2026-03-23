
undefined4 FUN_0082e08b(int param_1,char *param_2,int param_3)

{
  int *piVar1;
  undefined4 uVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = 0;
  iVar5 = 0;
  if (*param_2 == '>') {
    param_2 = param_2 + 1;
    piVar1 = (int *)(*(int *)(param_1 + 8) + -0x10);
    iVar5 = *piVar1;
    *(int **)(param_1 + 8) = piVar1;
  }
  else if (*(int *)(param_3 + 0x60) != 0) {
    iVar4 = *(int *)(param_3 + 0x60) * 0x18 + *(int *)(param_1 + 0x28);
    iVar5 = **(int **)(iVar4 + 4);
  }
  uVar2 = FUN_0082d8f0(param_1,param_2,param_3,iVar5,iVar4);
  pcVar3 = strchr(param_2,0x66);
  if (pcVar3 != (char *)0x0) {
    piVar1 = *(int **)(param_1 + 8);
    if (iVar5 == 0) {
      piVar1[2] = 0;
    }
    else {
      *piVar1 = iVar5;
      piVar1[2] = 6;
    }
    if (*(int *)(param_1 + 0x1c) - *(int *)(param_1 + 8) < 0x11) {
      FUN_0082f194(param_1,1);
    }
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
  }
  pcVar3 = strchr(param_2,0x4c);
  if (pcVar3 != (char *)0x0) {
    FUN_0082da0c(param_1,iVar5);
  }
  return uVar2;
}

