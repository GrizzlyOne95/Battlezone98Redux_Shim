/*
 * Entry: 004b20f4
 * Name: MakeSelectNum
 * Namespace: Global
 * Signature: long MakeSelectNum(long param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl MakeSelectNum(long param_1,long param_2)

{
  return param_1 * 0x10000 - 0x10000U | param_2;
}
