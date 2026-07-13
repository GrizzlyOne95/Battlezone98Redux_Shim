/*
 * Entry: 0054a0d7
 * Name: isRank1Closing
 * Namespace: Global
 * Signature: int isRank1Closing(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isRank1Closing(char *param_1)

{
  if (param_1 == (char *)0x0) {
    return -1;
  }
  if (*param_1 == -0x7f) {
    switch(param_1[1]) {
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'f':
    case 'h':
    case 'j':
    case 'l':
    case 'n':
    case 'p':
    case 'r':
    case 't':
    case 'v':
    case 'x':
    case 'z':
      return 1;
    default:
    }
  }
  return 0;
}
