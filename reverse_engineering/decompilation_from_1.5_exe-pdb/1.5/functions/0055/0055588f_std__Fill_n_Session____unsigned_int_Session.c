/*
 * Entry: 0055588f
 * Name: std::_Fill_n<Session_*_*,unsigned_int,Session_*>
 * Namespace: std
 * Signature: void _Fill_n<Session_*_*,unsigned_int,Session_*>(Session * * param_1, uint param_2, Session * * param_3, _Range_checked_iterator_tag param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Fill_n<Session_*_*,unsigned_int,Session_*>
          (Session **param_1,uint param_2,Session **param_3,_Range_checked_iterator_tag param_4)

{
  for (; param_2 != 0; param_2 = param_2 - 1) {
    *param_1 = *param_3;
    param_1 = param_1 + 1;
  }
  return;
}
