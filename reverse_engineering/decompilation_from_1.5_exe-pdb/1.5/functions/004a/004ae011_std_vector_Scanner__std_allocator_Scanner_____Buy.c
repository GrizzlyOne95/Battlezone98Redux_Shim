/*
 * Entry: 004ae011
 * Name: std::vector<Scanner_*,std::allocator<Scanner_*>_>::_Buy
 * Namespace: std::vector<Scanner_*,std::allocator<Scanner_*>_>
 * Signature: bool _Buy(vector<Scanner_*,std::allocator<Scanner_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<Scanner_*,std::allocator<Scanner_*>_>::_Buy
          (vector<Scanner_*,std::allocator<Scanner_*>_> *this,uint param_1)

{
  bool bVar1;
  Scanner **ppSVar2;
  
  this->_Myfirst = (Scanner **)0x0;
  this->_Mylast = (Scanner **)0x0;
  this->_Myend = (Scanner **)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x40000000) {
      ppSVar2 = _Allocate<Scanner_*>(param_1,(Scanner **)0x0);
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
