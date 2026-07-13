/*
 * Entry: 005474ae
 * Name: DEBUG_fileLine
 * Namespace: Global
 * Signature: void DEBUG_fileLine(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DEBUG_fileLine(char *param_1)

{
  if ((DebugLogFile == (_iobuf *)0x0) &&
     (DebugLogFile = (_iobuf *)fopen(DebugLogFileName,"at"), DebugLogFile == (_iobuf *)0x0)) {
    return;
  }
  fputs(param_1,(FILE *)DebugLogFile);
  fflush((FILE *)DebugLogFile);
  fclose((FILE *)DebugLogFile);
  DebugLogFile = (_iobuf *)0x0;
  return;
}
