/*
 * Entry: 00460c09
 * Name: std::vector<Scrap_*,std::allocator<Scrap_*>_>::_Buy
 * Namespace: std::vector<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: bool _Buy(vector<Scrap_*,std::allocator<Scrap_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<Scrap_*,std::allocator<Scrap_*>_>::_Buy
          (vector<Scrap_*,std::allocator<Scrap_*>_> *this,uint param_1)

{
  bool bVar1;
  Scrap **ppSVar2;
  
  this->_Myfirst = (Scrap **)0x0;
  this->_Mylast = (Scrap **)0x0;
  this->_Myend = (Scrap **)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x40000000) {
      ppSVar2 = _Allocate<Scrap_*>(param_1,(Scrap **)0x0);
      this->_Myfirst = ppSVar2;
      this->_Mylast = ppSVar2;
      this->_Myend = ppSVar2 + param_1;
    }
    else {
      _Xlen();
    }
    bVar1 = true;
  }
  return bVar1;
}
