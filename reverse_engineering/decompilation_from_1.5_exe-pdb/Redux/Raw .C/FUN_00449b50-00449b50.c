
/* WARNING: Removing unreachable block (ram,0x00449b96) */
/* WARNING: Removing unreachable block (ram,0x00449b92) */
/* WARNING: Removing unreachable block (ram,0x00449baa) */
/* WARNING: Removing unreachable block (ram,0x00449b5d) */

int __fastcall FUN_00449b50(int param_1)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = (int *)(param_1 + 0x10);
  LOCK();
  iVar1 = *piVar2;
  *piVar2 = *piVar2 + 1;
  UNLOCK();
  return iVar1 + 1;
}

