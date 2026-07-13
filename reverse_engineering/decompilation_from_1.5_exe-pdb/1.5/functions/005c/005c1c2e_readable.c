/*
 * Entry: 005c1c2e
 * Name: readable
 * Namespace: Global
 * Signature: int readable(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl readable(char *param_1)

{
  FILE *_File;
  
  _File = fopen(param_1,"r");
  if (_File == (FILE *)0x0) {
    return 0;
  }
  fclose(_File);
  return 1;
}
