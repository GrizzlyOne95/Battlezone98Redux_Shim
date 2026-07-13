/*
 * Entry: 00547515
 * Name: DEBUG_setWindowHandle
 * Namespace: Global
 * Signature: void DEBUG_setWindowHandle(HWND__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DEBUG_setWindowHandle(HWND__ *param_1)

{
  DebugWindowHandle = param_1;
  return;
}
