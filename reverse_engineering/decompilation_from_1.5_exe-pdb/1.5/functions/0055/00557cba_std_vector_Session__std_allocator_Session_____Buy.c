/*
 * Entry: 00557cba
 * Name: std::vector<Session_*,std::allocator<Session_*>_>::_Buy
 * Namespace: std::vector<Session_*,std::allocator<Session_*>_>
 * Signature: bool _Buy(vector<Session_*,std::allocator<Session_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<Session_*,std::allocator<Session_*>_>::_Buy
          (vector<Session_*,std::allocator<Session_*>_> *this,uint param_1)

{
  bool bVar1;
  Session **ppSVar2;
  
  this->_Myfirst = (Session **)0x0;
  this->_Mylast = (Session **)0x0;
  this->_Myend = (Session **)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x40000000) {
      ppSVar2 = _Allocate<Session_*>(param_1,(Session **)0x0);
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
