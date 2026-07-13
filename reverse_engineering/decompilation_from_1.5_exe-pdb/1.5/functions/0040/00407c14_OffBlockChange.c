/*
 * Entry: 00407c14
 * Name: OffBlockChange
 * Namespace: Global
 * Signature: int OffBlockChange(long param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl OffBlockChange(long param_1,long param_2)

{
  byte bVar1;
  int iVar2;
  
  bVar1 = CellType(param_1,param_2);
  iVar2 = Material((uint)bVar1);
  if ((iVar2 != 6) && (iVar2 != 5)) {
    return 1;
  }
  return 0;
}
