/*
 * Entry: 00549ea5
 * Name: isHiragana
 * Namespace: Global
 * Signature: int isHiragana(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isHiragana(char *param_1)

{
  if (param_1 == (char *)0x0) {
    return -1;
  }
  if (((*param_1 == -0x7e) && (0x9e < (byte)param_1[1])) && ((byte)param_1[1] < 0xf3)) {
    return 1;
  }
  return 0;
}
