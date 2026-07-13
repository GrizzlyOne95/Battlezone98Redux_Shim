/*
 * Entry: 0048a480
 * Name: std::pair<unsigned_long_const_,unsigned_long>::pair<unsigned_long_const_,unsigned_long>
 * Namespace: std::pair<unsigned_long_const_,unsigned_long>
 * Signature: pair<unsigned_long_const_,unsigned_long> * pair<unsigned_long_const_,unsigned_long>(pair<unsigned_long_const_,unsigned_long> * this, ulong * param_1, ulong * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<unsigned_long_const_,unsigned_long> * __thiscall
std::pair<unsigned_long_const_,unsigned_long>::pair<unsigned_long_const_,unsigned_long>
          (pair<unsigned_long_const_,unsigned_long> *this,ulong *param_1,ulong *param_2)

{
  this->first = *param_1;
  this->second = *param_2;
  return this;
}
