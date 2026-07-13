/*
 * Entry: 00528711
 * Name: paths_testbit
 * Namespace: Global
 * Signature: int paths_testbit(ulong * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl paths_testbit(ulong *param_1,int param_2)

{
  int in_ECX;
  
  if ((in_ECX < 0x101) && (param_1[(int)(in_ECX + (in_ECX >> 0x1f & 0x1fU)) >> 5] != 0)) {
    return (uint)((1 << ((byte)in_ECX & 0x1f) &
                  param_1[(int)(in_ECX + (in_ECX >> 0x1f & 0x1fU)) >> 5]) != 0);
  }
  return 0;
}
