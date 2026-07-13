/*
 * Entry: 0052874d
 * Name: paths_setbit
 * Namespace: Global
 * Signature: int paths_setbit(ulong * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl paths_setbit(ulong *param_1,int param_2)

{
  int in_ECX;
  
  if (0x100 < in_ECX) {
    return 0;
  }
  param_1[(int)(in_ECX + (in_ECX >> 0x1f & 0x1fU)) >> 5] =
       param_1[(int)(in_ECX + (in_ECX >> 0x1f & 0x1fU)) >> 5] | 1 << ((byte)in_ECX & 0x1f);
  return 1;
}
