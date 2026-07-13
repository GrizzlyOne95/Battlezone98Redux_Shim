/*
 * Entry: 004cf7a2
 * Name: MapJChars
 * Namespace: Global
 * Signature: void MapJChars(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl MapJChars(char *param_1)

{
  while (*param_1 != '\0') {
    MapJChar(*(ushort *)param_1);
    IncString(&param_1);
  }
  return;
}
