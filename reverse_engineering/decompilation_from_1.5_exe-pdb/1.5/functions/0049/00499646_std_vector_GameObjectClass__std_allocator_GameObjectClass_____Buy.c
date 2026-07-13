/*
 * Entry: 00499646
 * Name: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::_Buy
 * Namespace: std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Signature: bool _Buy(vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::_Buy
          (vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *this,uint param_1)

{
  bool bVar1;
  GameObjectClass **ppGVar2;
  
  this->_Myfirst = (GameObjectClass **)0x0;
  this->_Mylast = (GameObjectClass **)0x0;
  this->_Myend = (GameObjectClass **)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x40000000) {
      ppGVar2 = _Allocate<GameObjectClass_*>(param_1,(GameObjectClass **)0x0);
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
