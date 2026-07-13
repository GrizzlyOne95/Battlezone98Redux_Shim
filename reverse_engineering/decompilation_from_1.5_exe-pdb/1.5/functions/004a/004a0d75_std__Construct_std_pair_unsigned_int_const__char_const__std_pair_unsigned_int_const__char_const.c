/*
 * Entry: 004a0d75
 * Name: std::_Construct<std::pair<unsigned_int_const_,char_const_*>,std::pair<unsigned_int_const_,char_const_*>_>
 * Namespace: std
 * Signature: void _Construct<std::pair<unsigned_int_const_,char_const_*>,std::pair<unsigned_int_const_,char_const_*>_>(pair<unsigned_int_const_,char_const_*> * param_1, pair<unsigned_int_const_,char_const_*> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
_Construct<std::pair<unsigned_int_const_,char_const_*>,std::pair<unsigned_int_const_,char_const_*>_>
          (pair<unsigned_int_const_,char_const_*> *param_1,
          pair<unsigned_int_const_,char_const_*> *param_2)

{
  if (param_1 != (pair<unsigned_int_const_,char_const_*> *)0x0) {
    param_1->first = param_2->first;
    param_1->second = param_2->second;
  }
  return;
}
