/*
 * Entry: 004977e7
 * Name: std::vector<GameObject_*,std::allocator<GameObject_*>_>::_Buy
 * Namespace: std::vector<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: bool _Buy(vector<GameObject_*,std::allocator<GameObject_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<GameObject_*,std::allocator<GameObject_*>_>::_Buy
          (vector<GameObject_*,std::allocator<GameObject_*>_> *this,uint param_1)

{
  bool bVar1;
  GameObject **ppGVar2;
  
  this->_Myfirst = (GameObject **)0x0;
  this->_Mylast = (GameObject **)0x0;
  this->_Myend = (GameObject **)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x40000000) {
      ppGVar2 = _Allocate<GameObject_*>(param_1,(GameObject **)0x0);
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
