/*
 * Entry: 0052ec50
 * Name: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::_Buy
 * Namespace: std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Signature: bool _Buy(vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::_Buy
          (vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *this,uint param_1)

{
  bool bVar1;
  ExplosionClass **ppEVar2;
  
  this->_Myfirst = (ExplosionClass **)0x0;
  this->_Mylast = (ExplosionClass **)0x0;
  this->_Myend = (ExplosionClass **)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x40000000) {
      ppEVar2 = _Allocate<ExplosionClass_*>(param_1,(ExplosionClass **)0x0);
      this->_Myfirst = ppEVar2;
      this->_Mylast = ppEVar2;
      this->_Myend = ppEVar2 + param_1;
    }
    else {
      _Xlen();
    }
    bVar1 = true;
  }
  return bVar1;
}
