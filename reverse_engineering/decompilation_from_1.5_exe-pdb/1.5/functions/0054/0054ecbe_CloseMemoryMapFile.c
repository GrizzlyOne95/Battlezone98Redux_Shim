/*
 * Entry: 0054ecbe
 * Name: CloseMemoryMapFile
 * Namespace: Global
 * Signature: void CloseMemoryMapFile(MM_HANDLE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CloseMemoryMapFile(MM_HANDLE *param_1)

{
  if (param_1->Buffer != (char *)0x0) {
    UnmapViewOfFile(param_1->Buffer);
  }
  if (param_1->Map != (void *)0x0) {
    CloseHandle(param_1->Map);
  }
  if (param_1->File != (void *)0xffffffff) {
    CloseHandle(param_1->File);
  }
  return;
}
