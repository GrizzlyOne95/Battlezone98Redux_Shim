/*
 * Entry: 0053e8b2
 * Name: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::size
 * Namespace: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Signature: uint size(vector<WeaponClass_*,std::allocator<WeaponClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::size
          (vector<WeaponClass_*,std::allocator<WeaponClass_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
