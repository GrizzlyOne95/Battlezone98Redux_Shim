/*
 * Entry: 004cf7c7
 * Name: MapJObjective
 * Namespace: Global
 * Signature: void MapJObjective(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl MapJObjective(char *param_1)

{
  long lVar1;
  char *pcVar2;
  char *unaff_ESI;
  
  lVar1 = GetItemSize(unaff_ESI);
  if (0 < lVar1) {
    pcVar2 = UseItem(unaff_ESI);
    MapJChars(pcVar2);
    UnlockItem(unaff_ESI);
  }
  return;
}
