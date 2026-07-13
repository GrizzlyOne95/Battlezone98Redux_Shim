/*
 * Entry: 0054a259
 * Name: isRank1Opening
 * Namespace: Global
 * Signature: int isRank1Opening(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isRank1Opening(char *param_1)

{
  if (param_1 == (char *)0x0) {
    return -1;
  }
  if (*param_1 == -0x7f) {
    switch(param_1[1]) {
    case 'e':
    case 'h':
    case 'i':
    case 'k':
    case 'm':
    case 'o':
    case 'q':
    case 's':
    case 'u':
    case 'w':
    case 'y':
      return 1;
    default:
    }
  }
  return 0;
}
