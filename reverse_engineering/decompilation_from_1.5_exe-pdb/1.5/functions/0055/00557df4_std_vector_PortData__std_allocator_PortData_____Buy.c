/*
 * Entry: 00557df4
 * Name: std::vector<PortData_*,std::allocator<PortData_*>_>::_Buy
 * Namespace: std::vector<PortData_*,std::allocator<PortData_*>_>
 * Signature: bool _Buy(vector<PortData_*,std::allocator<PortData_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<PortData_*,std::allocator<PortData_*>_>::_Buy
          (vector<PortData_*,std::allocator<PortData_*>_> *this,uint param_1)

{
  bool bVar1;
  PortData **ppPVar2;
  
  this->_Myfirst = (PortData **)0x0;
  this->_Mylast = (PortData **)0x0;
  this->_Myend = (PortData **)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x40000000) {
      ppPVar2 = _Allocate<PortData_*>(param_1,(PortData **)0x0);
      this->_Myfirst = ppPVar2;
      this->_Mylast = ppPVar2;
      this->_Myend = ppPVar2 + param_1;
    }
    else {
      _Xlen();
    }
    bVar1 = true;
  }
  return bVar1;
}
