
undefined4 __fastcall FUN_006accc0(int param_1)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = (int *)(param_1 + 0x1c);
  LOCK();
  iVar1 = *piVar2;
  *piVar2 = *piVar2;
  UNLOCK();
  return CONCAT31((int3)((uint)iVar1 >> 8),iVar1 != 0);
}

