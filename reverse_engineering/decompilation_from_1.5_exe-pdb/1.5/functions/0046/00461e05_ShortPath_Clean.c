/*
 * Entry: 00461e05
 * Name: ShortPath::Clean
 * Namespace: ShortPath
 * Signature: void Clean(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ShortPath::Clean(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = Extents::dz * Extents::dx;
  iVar2 = 0;
  if (0 < iVar1) {
    do {
      if (Extents::cellNodes[iVar2] != (Node *)0x0) {
        operator_delete(Extents::cellNodes[iVar2]);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < iVar1);
  }
  operator_delete__(Extents::cellNodes);
  return;
}
