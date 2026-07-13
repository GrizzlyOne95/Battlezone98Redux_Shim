/*
 * Entry: 0053eb51
 * Name: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::empty
 * Namespace: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Signature: bool empty(vector<WeaponClass_*,std::allocator<WeaponClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::empty
          (vector<WeaponClass_*,std::allocator<WeaponClass_*>_> *this)

{
  return (bool)('\x01' - (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0));
}
