/*
 * Entry: 0053ecd6
 * Name: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::_Tidy
 * Namespace: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Signature: void _Tidy(vector<WeaponClass_*,std::allocator<WeaponClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::_Tidy
          (vector<WeaponClass_*,std::allocator<WeaponClass_*>_> *this)

{
  if (this->_Myfirst != (WeaponClass **)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (WeaponClass **)0x0;
  this->_Mylast = (WeaponClass **)0x0;
  this->_Myend = (WeaponClass **)0x0;
  return;
}
