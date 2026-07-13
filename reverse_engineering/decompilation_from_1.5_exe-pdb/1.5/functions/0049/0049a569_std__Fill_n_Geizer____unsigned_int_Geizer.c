/*
 * Entry: 0049a569
 * Name: std::_Fill_n<Geizer_*_*,unsigned_int,Geizer_*>
 * Namespace: std
 * Signature: void _Fill_n<Geizer_*_*,unsigned_int,Geizer_*>(Geizer * * param_1, uint param_2, Geizer * * param_3, _Range_checked_iterator_tag param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Fill_n<Geizer_*_*,unsigned_int,Geizer_*>
          (Geizer **param_1,uint param_2,Geizer **param_3,_Range_checked_iterator_tag param_4)

{
  for (; param_2 != 0; param_2 = param_2 - 1) {
    *param_1 = *param_3;
    param_1 = param_1 + 1;
  }
  return;
}
