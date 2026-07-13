/*
 * Entry: 00549ec8
 * Name: isGreek
 * Namespace: Global
 * Signature: int isGreek(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isGreek(char *param_1)

{
  byte bVar1;
  
  if (param_1 == (char *)0x0) {
    return -1;
  }
  if ((*param_1 == -0x7d) &&
     (((bVar1 = param_1[1], 0x9e < bVar1 && (bVar1 < 0xb7)) || ((0xbe < bVar1 && (bVar1 < 0xd7))))))
  {
    return 1;
  }
  return 0;
}
