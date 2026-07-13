/*
 * Entry: 004152e3
 * Name: std::vector<Scrap_*,std::allocator<Scrap_*>_>::operator[]
 * Namespace: std::vector<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: Scrap * * operator[](vector<Scrap_*,std::allocator<Scrap_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scrap ** __thiscall
std::vector<Scrap_*,std::allocator<Scrap_*>_>::operator[]
          (vector<Scrap_*,std::allocator<Scrap_*>_> *this,uint param_1)

{
  if ((uint)((int)this->_Mylast - (int)this->_Myfirst >> 2) <= param_1) {
    _invalid_parameter_noinfo();
  }
  return this->_Myfirst + param_1;
}
