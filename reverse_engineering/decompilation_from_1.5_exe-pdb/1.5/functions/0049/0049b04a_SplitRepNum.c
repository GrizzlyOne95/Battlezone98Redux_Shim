/*
 * Entry: 0049b04a
 * Name: SplitRepNum
 * Namespace: Global
 * Signature: void SplitRepNum(int param_1, long * param_2, long * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SplitRepNum(int param_1,long *param_2,long *param_3)

{
  *param_3 = param_1 & 0xffff;
  *param_2 = param_1 >> 0x10 & 0xffff;
  return;
}
