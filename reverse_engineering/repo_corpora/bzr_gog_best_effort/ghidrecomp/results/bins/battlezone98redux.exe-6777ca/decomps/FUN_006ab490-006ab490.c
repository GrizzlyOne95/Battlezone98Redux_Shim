
uint __fastcall FUN_006ab490(uint param_1)

{
  int iVar1;
  int iVar2;
  
  do {
    iVar1 = *(int *)(param_1 + 4);
    if (iVar1 == 0) {
      return param_1 & 0xffffff00;
    }
    LOCK();
    iVar2 = *(int *)(param_1 + 4);
    if (iVar1 == iVar2) {
      *(int *)(param_1 + 4) = iVar1 + 1;
      iVar2 = iVar1;
    }
    UNLOCK();
  } while (iVar2 != iVar1);
  return CONCAT31((int3)((uint)iVar2 >> 8),1);
}

