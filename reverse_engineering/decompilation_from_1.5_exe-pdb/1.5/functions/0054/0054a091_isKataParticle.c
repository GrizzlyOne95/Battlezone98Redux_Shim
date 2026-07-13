/*
 * Entry: 0054a091
 * Name: isKataParticle
 * Namespace: Global
 * Signature: int isKataParticle(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isKataParticle(char *param_1)

{
  if (param_1 == (char *)0x0) {
    return -1;
  }
  if ((*param_1 == -0x7d) && ((param_1[1] == -0x6b || (param_1[1] == -0x6a)))) {
    return 1;
  }
  return 0;
}
