/*
 * Entry: 0052ec99
 * Name: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::_Tidy
 * Namespace: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Signature: void _Tidy(vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::_Tidy
          (vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *this)

{
  if (this->_Myfirst != (ExplosionClass **)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (ExplosionClass **)0x0;
  this->_Mylast = (ExplosionClass **)0x0;
  this->_Myend = (ExplosionClass **)0x0;
  return;
}
