/*
 * Entry: 00493118
 * Name: std::vector<GameFeature_*,std::allocator<GameFeature_*>_>::_Buy
 * Namespace: std::vector<GameFeature_*,std::allocator<GameFeature_*>_>
 * Signature: bool _Buy(vector<GameFeature_*,std::allocator<GameFeature_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<GameFeature_*,std::allocator<GameFeature_*>_>::_Buy
          (vector<GameFeature_*,std::allocator<GameFeature_*>_> *this,uint param_1)

{
  bool bVar1;
  GameFeature **ppGVar2;
  
  this->_Myfirst = (GameFeature **)0x0;
  this->_Mylast = (GameFeature **)0x0;
  this->_Myend = (GameFeature **)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x40000000) {
      ppGVar2 = _Allocate<GameFeature_*>(param_1,(GameFeature **)0x0);
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
