/*
 * Entry: 004d47d4
 * Name: CenterRect
 * Namespace: Global
 * Signature: void CenterRect(long param_1, long param_2, long param_3, long * param_4, long * param_5, long * param_6, long * param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
CenterRect(long param_1,long param_2,long param_3,long *param_4,long *param_5,long *param_6,
          long *param_7)

{
  *param_4 = param_1 - param_3;
  *param_5 = param_2 - param_3;
  *param_6 = param_1 + param_3;
  *param_7 = param_2 + param_3;
  return;
}
