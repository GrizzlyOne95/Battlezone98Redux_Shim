/*
 * Entry: 0053ee9c
 * Name: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Namespace: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Signature: vector<WeaponClass_*,std::allocator<WeaponClass_*>_> * vector<WeaponClass_*,std::allocator<WeaponClass_*>_>(vector<WeaponClass_*,std::allocator<WeaponClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

vector<WeaponClass_*,std::allocator<WeaponClass_*>_> * __thiscall
std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::
vector<WeaponClass_*,std::allocator<WeaponClass_*>_>
          (vector<WeaponClass_*,std::allocator<WeaponClass_*>_> *this)

{
  _Vector_val<WeaponClass_*,std::allocator<WeaponClass_*>_>::
  _Vector_val<WeaponClass_*,std::allocator<WeaponClass_*>_>
            ((_Vector_val<WeaponClass_*,std::allocator<WeaponClass_*>_> *)this,SUB41(this,0));
  _Buy(this,0);
  return this;
}
