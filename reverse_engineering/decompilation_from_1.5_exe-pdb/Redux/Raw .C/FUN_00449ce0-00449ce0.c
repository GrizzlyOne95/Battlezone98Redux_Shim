
/* WARNING: Removing unreachable block (ram,0x00449d24) */
/* WARNING: Removing unreachable block (ram,0x00449d20) */
/* WARNING: Removing unreachable block (ram,0x00449d38) */
/* WARNING: Removing unreachable block (ram,0x00449ced) */

int __fastcall FUN_00449ce0(int param_1)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = (int *)(param_1 + 0x10);
  LOCK();
  iVar1 = *piVar2;
  *piVar2 = *piVar2 + -1;
  UNLOCK();
  return iVar1 + -1;
}

