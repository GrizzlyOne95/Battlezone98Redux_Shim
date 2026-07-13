/*
 * Entry: 0054a0b4
 * Name: isNobashi
 * Namespace: Global
 * Signature: int isNobashi(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isNobashi(char *param_1)

{
  if (param_1 == (char *)0x0) {
    return -1;
  }
  if ((*param_1 == -0x7f) && ((param_1[1] == '[' || (param_1[1] == '\\')))) {
    return 1;
  }
  return 0;
}
