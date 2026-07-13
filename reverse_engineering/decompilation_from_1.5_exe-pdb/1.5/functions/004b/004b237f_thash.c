/*
 * Entry: 004b237f
 * Name: thash
 * Namespace: Global
 * Signature: ulong thash(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl thash(char *param_1)

{
  uint uVar1;
  char *in_EDX;
  
  uVar1 = 0;
  for (; *in_EDX != '\0'; in_EDX = in_EDX + 1) {
    uVar1 = uVar1 * 2 ^ (int)*in_EDX & 0xdfU;
  }
  return (uVar1 * 0x6cd + 0xaab) % 0x6d;
}
