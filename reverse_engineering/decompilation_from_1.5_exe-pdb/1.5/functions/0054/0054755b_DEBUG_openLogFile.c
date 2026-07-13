/*
 * Entry: 0054755b
 * Name: DEBUG_openLogFile
 * Namespace: Global
 * Signature: void DEBUG_openLogFile(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DEBUG_openLogFile(void)

{
  DebugLogFile = (_iobuf *)fopen(DebugLogFileName,"wt");
  return;
}
