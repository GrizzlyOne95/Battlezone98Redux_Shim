/*
 * Entry: 0048acdc
 * Name: std::_Construct<std::pair<unsigned_long_const_,unsigned_long>,std::pair<unsigned_long_const_,unsigned_long>_>
 * Namespace: std
 * Signature: void _Construct<std::pair<unsigned_long_const_,unsigned_long>,std::pair<unsigned_long_const_,unsigned_long>_>(pair<unsigned_long_const_,unsigned_long> * param_1, pair<unsigned_long_const_,unsigned_long> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
_Construct<std::pair<unsigned_long_const_,unsigned_long>,std::pair<unsigned_long_const_,unsigned_long>_>
          (pair<unsigned_long_const_,unsigned_long> *param_1,
          pair<unsigned_long_const_,unsigned_long> *param_2)

{
  if (param_1 != (pair<unsigned_long_const_,unsigned_long> *)0x0) {
    param_1->first = param_2->first;
    param_1->second = param_2->second;
  }
  return;
}
