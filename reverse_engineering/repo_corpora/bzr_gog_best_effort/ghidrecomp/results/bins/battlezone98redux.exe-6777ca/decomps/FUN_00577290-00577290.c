
void FUN_00577290(int param_1,int param_2)

{
  int iVar1;
  char cVar2;
  short sVar3;
  
  sVar3 = FUN_00572d90();
  if ((0 < param_1) && (iVar1 = *(int *)(&DAT_009180e8 + param_1 * 4), iVar1 != 0)) {
    if (sVar3 == *(short *)(iVar1 + 0x28)) {
      FUN_00626000(1);
    }
    *(int *)(iVar1 + 0x6c) = *(int *)(iVar1 + 0x6c) + 1;
  }
  if (0 < param_2) {
    FUN_005e0bc0(param_2,param_1);
    cVar2 = FUN_005e1310(param_1);
    if ((cVar2 == '\0') && (iVar1 = *(int *)(&DAT_009180e8 + param_2 * 4), iVar1 != 0)) {
      if (sVar3 == *(short *)(iVar1 + 0x28)) {
        FUN_00625f90();
      }
      else {
        FUN_00573090(sVar3,*(undefined2 *)(iVar1 + 0x28),param_2);
      }
      *(int *)(iVar1 + 0x70) = *(int *)(iVar1 + 0x70) + 1;
    }
  }
  return;
}

