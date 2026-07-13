/*
 * Entry: 0048acf8
 * Name: std::_Construct<std::pair<unsigned_long_const_,float>,std::pair<unsigned_long_const_,float>_>
 * Namespace: std
 * Signature: void _Construct<std::pair<unsigned_long_const_,float>,std::pair<unsigned_long_const_,float>_>(pair<unsigned_long_const_,float> * param_1, pair<unsigned_long_const_,float> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Construct<std::pair<unsigned_long_const_,float>,std::pair<unsigned_long_const_,float>_>
          (pair<unsigned_long_const_,float> *param_1,pair<unsigned_long_const_,float> *param_2)

{
  if (param_1 != (pair<unsigned_long_const_,float> *)0x0) {
    param_1->first = param_2->first;
    param_1->second = param_2->second;
  }
  return;
}
