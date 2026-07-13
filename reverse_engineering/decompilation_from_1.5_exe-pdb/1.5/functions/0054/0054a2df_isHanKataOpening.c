/*
 * Entry: 0054a2df
 * Name: isHanKataOpening
 * Namespace: Global
 * Signature: int isHanKataOpening(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isHanKataOpening(char *param_1)

{
  if (param_1 == (char *)0x0) {
    return -1;
  }
  return (uint)(*param_1 == -0x5e);
}
