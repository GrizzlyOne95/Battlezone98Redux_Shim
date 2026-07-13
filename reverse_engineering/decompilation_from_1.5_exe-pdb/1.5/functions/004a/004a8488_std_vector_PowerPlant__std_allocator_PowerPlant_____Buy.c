/*
 * Entry: 004a8488
 * Name: std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::_Buy
 * Namespace: std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>
 * Signature: bool _Buy(vector<PowerPlant_*,std::allocator<PowerPlant_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<PowerPlant_*,std::allocator<PowerPlant_*>_>::_Buy
          (vector<PowerPlant_*,std::allocator<PowerPlant_*>_> *this,uint param_1)

{
  bool bVar1;
  PowerPlant **ppPVar2;
  
  this->_Myfirst = (PowerPlant **)0x0;
  this->_Mylast = (PowerPlant **)0x0;
  this->_Myend = (PowerPlant **)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x40000000) {
      ppPVar2 = _Allocate<PowerPlant_*>(param_1,(PowerPlant **)0x0);
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
