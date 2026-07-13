/*
 * Entry: 004cef3d
 * Name: IncString
 * Namespace: Global
 * Signature: void IncString(char * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl IncString(char **param_1)

{
  char *pcVar1;
  long lVar2;
  
  if (isMBCS != 0) {
    pcVar1 = *param_1;
    lVar2 = isMBC(*pcVar1);
    if (lVar2 != 0) {
      *param_1 = pcVar1 + 2;
      return;
    }
  }
  *param_1 = *param_1 + 1;
  return;
}
