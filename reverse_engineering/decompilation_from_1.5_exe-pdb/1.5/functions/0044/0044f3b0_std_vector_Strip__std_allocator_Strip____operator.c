/*
 * Entry: 0044f3b0
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::operator[]
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: Strip * * operator[](vector<Strip_*,std::allocator<Strip_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Strip ** __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::operator[]
          (vector<Strip_*,std::allocator<Strip_*>_> *this,uint param_1)

{
  if ((uint)((int)this->_Mylast - (int)this->_Myfirst >> 2) <= param_1) {
    _invalid_parameter_noinfo();
  }
  return this->_Myfirst + param_1;
}
