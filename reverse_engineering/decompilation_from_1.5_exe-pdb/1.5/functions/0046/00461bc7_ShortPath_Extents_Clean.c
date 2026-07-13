/*
 * Entry: 00461bc7
 * Name: ShortPath::Extents::Clean
 * Namespace: ShortPath::Extents
 * Signature: void Clean(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ShortPath::Extents::Clean(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = dz * dx;
  iVar2 = 0;
  if (0 < iVar1) {
    do {
      if (cellNodes[iVar2] != (Node *)0x0) {
        operator_delete(cellNodes[iVar2]);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < iVar1);
  }
  operator_delete__(cellNodes);
  return;
}
