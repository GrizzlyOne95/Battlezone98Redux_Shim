/*
 * Entry: 0053e89f
 * Name: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::capacity
 * Namespace: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Signature: uint capacity(vector<WeaponClass_*,std::allocator<WeaponClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::capacity
          (vector<WeaponClass_*,std::allocator<WeaponClass_*>_> *this)

{
  if (this->_Myfirst == (WeaponClass **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
