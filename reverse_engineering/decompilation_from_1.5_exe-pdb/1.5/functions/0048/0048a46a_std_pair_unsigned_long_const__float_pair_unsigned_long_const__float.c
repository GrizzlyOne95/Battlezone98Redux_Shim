/*
 * Entry: 0048a46a
 * Name: std::pair<unsigned_long_const_,float>::pair<unsigned_long_const_,float>
 * Namespace: std::pair<unsigned_long_const_,float>
 * Signature: pair<unsigned_long_const_,float> * pair<unsigned_long_const_,float>(pair<unsigned_long_const_,float> * this, ulong * param_1, float * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<unsigned_long_const_,float> * __thiscall
std::pair<unsigned_long_const_,float>::pair<unsigned_long_const_,float>
          (pair<unsigned_long_const_,float> *this,ulong *param_1,float *param_2)

{
  this->first = *param_1;
  this->second = *param_2;
  return this;
}
