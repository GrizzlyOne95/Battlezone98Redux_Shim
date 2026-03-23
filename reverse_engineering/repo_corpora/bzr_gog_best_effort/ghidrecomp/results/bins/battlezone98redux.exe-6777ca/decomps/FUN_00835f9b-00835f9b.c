
int FUN_00835f9b(int param_1,undefined1 *param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  
  iVar2 = 0;
  puVar3 = param_2;
  if (param_2 < *(undefined1 **)(param_1 + 4)) {
    do {
      iVar1 = FUN_0083619b(*puVar3,param_3,param_4);
      if (iVar1 == 0) break;
      iVar2 = iVar2 + 1;
      puVar3 = puVar3 + 1;
    } while (puVar3 < *(undefined1 **)(param_1 + 4));
    if (iVar2 < 0) {
      return 0;
    }
  }
  do {
    iVar1 = FUN_00835b72(param_1,param_2 + iVar2,param_4 + 1);
    if (iVar1 != 0) {
      return iVar1;
    }
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);
  return 0;
}

