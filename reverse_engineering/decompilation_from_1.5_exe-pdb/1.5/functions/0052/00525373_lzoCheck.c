/*
 * Entry: 00525373
 * Name: lzoCheck
 * Namespace: Global
 * Signature: int lzoCheck(int param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lzoCheck(int param_1,char *param_2)

{
  if (param_1 != 0) {
    sprintf(&zfserr,"Error %d during compression library operation: %s");
    return 0;
  }
  return 1;
}
