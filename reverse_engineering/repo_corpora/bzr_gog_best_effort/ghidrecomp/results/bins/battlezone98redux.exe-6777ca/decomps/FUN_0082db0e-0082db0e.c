
char * FUN_0082db0e(int param_1,int *param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  char *pcVar3;
  
  iVar1 = FUN_0082dc5a(param_2);
  if (iVar1 != 0) {
    uVar2 = FUN_0082dad3(param_1,param_2);
    pcVar3 = (char *)FUN_0082fb1b(iVar1,param_3,uVar2);
    if (pcVar3 != (char *)0x0) {
      return pcVar3;
    }
  }
  if (param_2 == *(int **)(param_1 + 0x14)) {
    iVar1 = *(int *)(param_1 + 8);
  }
  else {
    iVar1 = param_2[7];
  }
  if ((iVar1 - *param_2 >> 4 < param_3) || (param_3 < 1)) {
    pcVar3 = (char *)0x0;
  }
  else {
    pcVar3 = "(*temporary)";
  }
  return pcVar3;
}

