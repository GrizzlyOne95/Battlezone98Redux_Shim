/*
 * Entry: 00535289
 * Name: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::_Buy
 * Namespace: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
 * Signature: bool _Buy(vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::_Buy
          (vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *this,uint param_1)

{
  bool bVar1;
  OrdnanceClass **ppOVar2;
  
  this->_Myfirst = (OrdnanceClass **)0x0;
  this->_Mylast = (OrdnanceClass **)0x0;
  this->_Myend = (OrdnanceClass **)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x40000000) {
      ppOVar2 = _Allocate<OrdnanceClass_*>(param_1,(OrdnanceClass **)0x0);
      this->_Myfirst = ppOVar2;
      this->_Mylast = ppOVar2;
      this->_Myend = ppOVar2 + param_1;
    }
    else {
      _Xlen();
    }
    bVar1 = true;
  }
  return bVar1;
}
