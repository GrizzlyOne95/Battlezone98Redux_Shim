
void FUN_008388c1(int param_1,char param_2,undefined1 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar2 = (*(int **)(param_1 + 0x3c))[1];
  iVar1 = **(int **)(param_1 + 0x3c);
  while (iVar2 != 0) {
    iVar2 = iVar2 + -1;
    if (*(char *)(iVar1 + iVar2) == param_2) {
      *(undefined1 *)(iVar1 + iVar2) = param_3;
    }
  }
  return;
}

