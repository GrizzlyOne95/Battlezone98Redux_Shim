/*
 * Entry: 00557c1d
 * Name: std::vector<Server_*,std::allocator<Server_*>_>::_Buy
 * Namespace: std::vector<Server_*,std::allocator<Server_*>_>
 * Signature: bool _Buy(vector<Server_*,std::allocator<Server_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<Server_*,std::allocator<Server_*>_>::_Buy
          (vector<Server_*,std::allocator<Server_*>_> *this,uint param_1)

{
  bool bVar1;
  Server **ppSVar2;
  
  this->_Myfirst = (Server **)0x0;
  this->_Mylast = (Server **)0x0;
  this->_Myend = (Server **)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x40000000) {
      ppSVar2 = _Allocate<Server_*>(param_1,(Server **)0x0);
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
