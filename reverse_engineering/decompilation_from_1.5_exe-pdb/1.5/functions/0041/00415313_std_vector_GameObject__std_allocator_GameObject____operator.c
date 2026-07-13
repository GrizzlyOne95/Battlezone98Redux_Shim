/*
 * Entry: 00415313
 * Name: std::vector<GameObject_*,std::allocator<GameObject_*>_>::operator[]
 * Namespace: std::vector<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: GameObject * * operator[](vector<GameObject_*,std::allocator<GameObject_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject ** __thiscall
std::vector<GameObject_*,std::allocator<GameObject_*>_>::operator[]
          (vector<GameObject_*,std::allocator<GameObject_*>_> *this,uint param_1)

{
  if ((uint)((int)this->_Mylast - (int)this->_Myfirst >> 2) <= param_1) {
    _invalid_parameter_noinfo();
  }
  return this->_Myfirst + param_1;
}
