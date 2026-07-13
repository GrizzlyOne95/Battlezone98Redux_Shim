/*
 * Entry: 004dda62
 * Name: Net_SetTransport
 * Namespace: Global
 * Signature: void Net_SetTransport(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Net_SetTransport(char *param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = (int)Net::transport - (int)param_1;
  do {
    cVar1 = *param_1;
    param_1[iVar2] = cVar1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  return;
}
