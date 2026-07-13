/*
 * Entry: 00450b90
 * Name: std::_Fill_n<Strip_*_*,unsigned_int,Strip_*>
 * Namespace: std
 * Signature: void _Fill_n<Strip_*_*,unsigned_int,Strip_*>(Strip * * param_1, uint param_2, Strip * * param_3, random_access_iterator_tag param_4, _Range_checked_iterator_tag param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Fill_n<Strip_*_*,unsigned_int,Strip_*>
          (Strip **param_1,uint param_2,Strip **param_3,random_access_iterator_tag param_4,
          _Range_checked_iterator_tag param_5)

{
  for (; param_2 != 0; param_2 = param_2 - 1) {
    *param_1 = *param_3;
    param_1 = param_1 + 1;
  }
  return;
}
