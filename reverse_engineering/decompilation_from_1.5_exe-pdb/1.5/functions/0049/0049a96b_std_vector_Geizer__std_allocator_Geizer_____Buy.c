/*
 * Entry: 0049a96b
 * Name: std::vector<Geizer_*,std::allocator<Geizer_*>_>::_Buy
 * Namespace: std::vector<Geizer_*,std::allocator<Geizer_*>_>
 * Signature: bool _Buy(vector<Geizer_*,std::allocator<Geizer_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<Geizer_*,std::allocator<Geizer_*>_>::_Buy
          (vector<Geizer_*,std::allocator<Geizer_*>_> *this,uint param_1)

{
  bool bVar1;
  Geizer **ppGVar2;
  
  this->_Myfirst = (Geizer **)0x0;
  this->_Mylast = (Geizer **)0x0;
  this->_Myend = (Geizer **)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x40000000) {
      ppGVar2 = _Allocate<Geizer_*>(param_1,(Geizer **)0x0);
      this->_Myfirst = ppGVar2;
      this->_Mylast = ppGVar2;
      this->_Myend = ppGVar2 + param_1;
    }
    else {
      _Xlen();
    }
    bVar1 = true;
  }
  return bVar1;
}
