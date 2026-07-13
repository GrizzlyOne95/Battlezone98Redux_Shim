/*
 * Entry: 0052e87d
 * Name: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::capacity
 * Namespace: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Signature: uint capacity(vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::capacity
          (vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *this)

{
  if (this->_Myfirst == (ExplosionClass **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
