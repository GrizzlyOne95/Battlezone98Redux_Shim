/*
 * Entry: 004b2105
 * Name: SplitSelectNum
 * Namespace: Global
 * Signature: void SplitSelectNum(long param_1, long * param_2, long * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SplitSelectNum(long param_1,long *param_2,long *param_3)

{
  *param_2 = (param_1 >> 0x10 & 0xffffU) + 1;
  *param_3 = param_1 & 0xffff;
  return;
}
