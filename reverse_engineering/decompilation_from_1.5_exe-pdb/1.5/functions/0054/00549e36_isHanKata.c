/*
 * Entry: 00549e36
 * Name: isHanKata
 * Namespace: Global
 * Signature: int isHanKata(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isHanKata(char *param_1)

{
  if (param_1 == (char *)0x0) {
    return -1;
  }
  if ((0xa0 < (byte)*param_1) && ((byte)*param_1 < 0xe0)) {
    return 1;
  }
  return 0;
}
