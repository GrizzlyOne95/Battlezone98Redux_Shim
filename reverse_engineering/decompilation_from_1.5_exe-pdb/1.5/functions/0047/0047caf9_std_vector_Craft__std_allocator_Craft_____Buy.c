/*
 * Entry: 0047caf9
 * Name: std::vector<Craft_*,std::allocator<Craft_*>_>::_Buy
 * Namespace: std::vector<Craft_*,std::allocator<Craft_*>_>
 * Signature: bool _Buy(vector<Craft_*,std::allocator<Craft_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<Craft_*,std::allocator<Craft_*>_>::_Buy
          (vector<Craft_*,std::allocator<Craft_*>_> *this,uint param_1)

{
  bool bVar1;
  Craft **ppCVar2;
  
  this->_Myfirst = (Craft **)0x0;
  this->_Mylast = (Craft **)0x0;
  this->_Myend = (Craft **)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x40000000) {
      ppCVar2 = _Allocate<Craft_*>(param_1,(Craft **)0x0);
      this->_Myfirst = ppCVar2;
      this->_Mylast = ppCVar2;
      this->_Myend = ppCVar2 + param_1;
    }
    else {
      _Xlen();
    }
    bVar1 = true;
  }
  return bVar1;
}
