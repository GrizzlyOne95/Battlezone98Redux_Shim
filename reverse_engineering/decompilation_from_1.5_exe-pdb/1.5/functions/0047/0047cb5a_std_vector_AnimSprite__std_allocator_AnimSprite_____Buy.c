/*
 * Entry: 0047cb5a
 * Name: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::_Buy
 * Namespace: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>
 * Signature: bool _Buy(vector<AnimSprite_*,std::allocator<AnimSprite_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::_Buy
          (vector<AnimSprite_*,std::allocator<AnimSprite_*>_> *this,uint param_1)

{
  bool bVar1;
  AnimSprite **ppAVar2;
  
  this->_Myfirst = (AnimSprite **)0x0;
  this->_Mylast = (AnimSprite **)0x0;
  this->_Myend = (AnimSprite **)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x40000000) {
      ppAVar2 = _Allocate<AnimSprite_*>(param_1,(AnimSprite **)0x0);
      this->_Myfirst = ppAVar2;
      this->_Mylast = ppAVar2;
      this->_Myend = ppAVar2 + param_1;
    }
    else {
      _Xlen();
    }
    bVar1 = true;
  }
  return bVar1;
}
