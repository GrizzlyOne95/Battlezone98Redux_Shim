/*
 * Entry: 00547a4f
 * Name: out
 * Namespace: Global
 * Signature: bool out(_iobuf * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl out(_iobuf *param_1,char *param_2)

{
  int iVar1;
  
  if (binarySave) {
    return true;
  }
  iVar1 = fprintf((FILE *)param_1,"%s\r\n",param_2);
  return 0 < iVar1;
}
