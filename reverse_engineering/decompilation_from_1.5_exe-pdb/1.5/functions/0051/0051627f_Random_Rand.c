/*
 * Entry: 0051627f
 * Name: Random_Rand
 * Namespace: Global
 * Signature: ulong Random_Rand(int * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl Random_Rand(int *param_1,int param_2)

{
  int *in_ECX;
  ulong uVar1;
  
  if ((0x8b < *in_ECX) || (*in_ECX < 0)) {
    *in_ECX = 0;
  }
  if ((int)param_1 < 1) {
    uVar1 = 0;
  }
  else {
    uVar1 = randomtable[*in_ECX] % (uint)param_1;
  }
  *in_ECX = *in_ECX + 1;
  return uVar1;
}
