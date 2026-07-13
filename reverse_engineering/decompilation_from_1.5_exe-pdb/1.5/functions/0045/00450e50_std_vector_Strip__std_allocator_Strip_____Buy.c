/*
 * Entry: 00450e50
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::_Buy
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: bool _Buy(vector<Strip_*,std::allocator<Strip_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::_Buy
          (vector<Strip_*,std::allocator<Strip_*>_> *this,uint param_1)

{
  Strip **ppSVar1;
  
  this->_Myfirst = (Strip **)0x0;
  this->_Mylast = (Strip **)0x0;
  this->_Myend = (Strip **)0x0;
  if (param_1 == 0) {
    return false;
  }
  if (0x3fffffff < param_1) {
    _Xlen();
    return true;
  }
  ppSVar1 = _Allocate<Strip_*>(param_1,(Strip **)0x0);
  this->_Myfirst = ppSVar1;
  this->_Mylast = ppSVar1;
  this->_Myend = ppSVar1 + param_1;
  return true;
}
