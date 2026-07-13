/*
 * Entry: 00549e19
 * Name: isVoicingMark
 * Namespace: Global
 * Signature: int isVoicingMark(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isVoicingMark(char *param_1)

{
  if (param_1 == (char *)0x0) {
    return -1;
  }
  if ((*param_1 != -0x22) && (*param_1 != -0x21)) {
    return 0;
  }
  return 1;
}
