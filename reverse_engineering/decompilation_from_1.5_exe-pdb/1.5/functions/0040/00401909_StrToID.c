/*
 * Entry: 00401909
 * Name: StrToID
 * Namespace: Global
 * Signature: void StrToID(char * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl StrToID(char *param_1,long64 param_2)

{
  char *unaff_ESI;
  
  strncpy(unaff_ESI,(char *)&param_1,8);
  unaff_ESI[8] = '\0';
  return;
}
