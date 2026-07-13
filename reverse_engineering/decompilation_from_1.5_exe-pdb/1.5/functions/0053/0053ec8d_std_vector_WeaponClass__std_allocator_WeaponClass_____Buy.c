/*
 * Entry: 0053ec8d
 * Name: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::_Buy
 * Namespace: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Signature: bool _Buy(vector<WeaponClass_*,std::allocator<WeaponClass_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::_Buy
          (vector<WeaponClass_*,std::allocator<WeaponClass_*>_> *this,uint param_1)

{
  bool bVar1;
  WeaponClass **ppWVar2;
  
  this->_Myfirst = (WeaponClass **)0x0;
  this->_Mylast = (WeaponClass **)0x0;
  this->_Myend = (WeaponClass **)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x40000000) {
      ppWVar2 = _Allocate<WeaponClass_*>(param_1,(WeaponClass **)0x0);
      this->_Myfirst = ppWVar2;
      this->_Mylast = ppWVar2;
      this->_Myend = ppWVar2 + param_1;
    }
    else {
      _Xlen();
    }
    bVar1 = true;
  }
  return bVar1;
}
