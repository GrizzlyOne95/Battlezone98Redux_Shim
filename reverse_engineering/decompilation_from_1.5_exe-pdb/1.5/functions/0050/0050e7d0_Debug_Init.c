/*
 * Entry: 0050e7d0
 * Name: Debug_Init
 * Namespace: Global
 * Signature: void Debug_Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Debug_Init(void)

{
  atexit(Debug_Done);
  return;
}
