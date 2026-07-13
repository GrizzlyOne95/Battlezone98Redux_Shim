/*
 * Entry: 0052eb14
 * Name: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::empty
 * Namespace: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Signature: bool empty(vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::empty
          (vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *this)

{
  return (bool)('\x01' - (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0));
}
