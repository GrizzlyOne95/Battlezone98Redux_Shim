/*
 * Entry: 0059b090
 * Name: _lookup_serialno
 * Namespace: Global
 * Signature: int _lookup_serialno(long param_1, long * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl _lookup_serialno(long param_1,long *param_2,int param_3)

{
  if (param_2 != (long *)0x0) {
    while (param_3 != 0) {
      if (*param_2 == param_1) {
        return 1;
      }
      param_2 = param_2 + 1;
      param_3 = param_3 + -1;
    }
  }
  return 0;
}
