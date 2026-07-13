/*
 * Entry: 0054a35b
 * Name: jGetNextCharacter
 * Namespace: Global
 * Signature: char * jGetNextCharacter(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl jGetNextCharacter(char *param_1)

{
  long lVar1;
  
  if (param_1 == (char *)0x0) {
    return (char *)0x0;
  }
  lVar1 = isMBC(*param_1);
  if (lVar1 != 0) {
    param_1 = param_1 + 1;
  }
  return param_1 + 1;
}
