/*
 * Entry: 00547543
 * Name: DEBUG_setLogFileName
 * Namespace: Global
 * Signature: void DEBUG_setLogFileName(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DEBUG_setLogFileName(char *param_1)

{
  strncpy(DebugLogFileName,param_1,0x100);
  return;
}
