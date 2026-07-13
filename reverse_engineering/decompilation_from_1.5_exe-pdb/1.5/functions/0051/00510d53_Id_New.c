/*
 * Entry: 00510d53
 * Name: Id_New
 * Namespace: Global
 * Signature: int Id_New(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Id_New(void)

{
  int iVar1;
  
  iVar1 = id_nextavail;
  id_nextavail = id_nextavail + 1;
  return iVar1;
}
