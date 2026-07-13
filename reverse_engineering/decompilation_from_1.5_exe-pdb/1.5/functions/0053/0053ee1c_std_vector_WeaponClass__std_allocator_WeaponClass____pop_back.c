/*
 * Entry: 0053ee1c
 * Name: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::pop_back
 * Namespace: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Signature: void pop_back(vector<WeaponClass_*,std::allocator<WeaponClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::pop_back
          (vector<WeaponClass_*,std::allocator<WeaponClass_*>_> *this)

{
  if (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0) {
    this->_Mylast = this->_Mylast + -1;
  }
  return;
}
