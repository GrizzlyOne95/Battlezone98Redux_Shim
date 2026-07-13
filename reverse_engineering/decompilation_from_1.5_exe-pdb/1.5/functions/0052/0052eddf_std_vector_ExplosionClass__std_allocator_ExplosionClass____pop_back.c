/*
 * Entry: 0052eddf
 * Name: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::pop_back
 * Namespace: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Signature: void pop_back(vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::pop_back
          (vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *this)

{
  if (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0) {
    this->_Mylast = this->_Mylast + -1;
  }
  return;
}
