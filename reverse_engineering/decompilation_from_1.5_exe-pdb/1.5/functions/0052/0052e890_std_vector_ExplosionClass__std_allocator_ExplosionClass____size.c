/*
 * Entry: 0052e890
 * Name: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::size
 * Namespace: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Signature: uint size(vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::size
          (vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
