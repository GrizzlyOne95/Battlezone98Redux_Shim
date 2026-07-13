/*
 * Entry: 005149ec
 * Name: NR_Error
 * Namespace: Global
 * Signature: void NR_Error(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl NR_Error(char *param_1)

{
  DEBUG_systemWarning("NR Util RunTime Error : [%s]");
  return;
}
