/*
 * Entry: 005ba417
 * Name: kname
 * Namespace: Global
 * Signature: char * kname(Proto * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl kname(Proto *param_1,int param_2)

{
  uint in_EAX;
  int *piVar1;
  int in_ECX;
  
  if (((in_EAX & 0x100) != 0) &&
     (piVar1 = (int *)((in_EAX & 0xfffffeff) * 0x10 + *(int *)(in_ECX + 8)), piVar1[2] == 4)) {
    return (char *)(*piVar1 + 0x10);
  }
  return "?";
}
