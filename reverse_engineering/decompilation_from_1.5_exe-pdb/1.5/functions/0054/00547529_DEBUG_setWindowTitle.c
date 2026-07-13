/*
 * Entry: 00547529
 * Name: DEBUG_setWindowTitle
 * Namespace: Global
 * Signature: void DEBUG_setWindowTitle(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DEBUG_setWindowTitle(char *param_1)

{
  _vsnprintf(DebugWindowTitle,0x50,param_1,&stack0x00000008);
  return;
}
