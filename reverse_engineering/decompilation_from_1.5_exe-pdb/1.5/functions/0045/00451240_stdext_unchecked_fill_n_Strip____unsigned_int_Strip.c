/*
 * Entry: 00451240
 * Name: stdext::unchecked_fill_n<Strip_*_*,unsigned_int,Strip_*>
 * Namespace: stdext
 * Signature: void unchecked_fill_n<Strip_*_*,unsigned_int,Strip_*>(Strip * * param_1, uint param_2, Strip * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::unchecked_fill_n<Strip_*_*,unsigned_int,Strip_*>
          (Strip **param_1,uint param_2,Strip **param_3)

{
  for (; param_2 != 0; param_2 = param_2 - 1) {
    *param_1 = *param_3;
    param_1 = param_1 + 1;
  }
  return;
}
