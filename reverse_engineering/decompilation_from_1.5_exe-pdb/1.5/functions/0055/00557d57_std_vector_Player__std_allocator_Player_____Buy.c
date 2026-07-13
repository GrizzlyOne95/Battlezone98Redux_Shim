/*
 * Entry: 00557d57
 * Name: std::vector<Player_*,std::allocator<Player_*>_>::_Buy
 * Namespace: std::vector<Player_*,std::allocator<Player_*>_>
 * Signature: bool _Buy(vector<Player_*,std::allocator<Player_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<Player_*,std::allocator<Player_*>_>::_Buy
          (vector<Player_*,std::allocator<Player_*>_> *this,uint param_1)

{
  bool bVar1;
  Player **ppPVar2;
  
  this->_Myfirst = (Player **)0x0;
  this->_Mylast = (Player **)0x0;
  this->_Myend = (Player **)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x40000000) {
      ppPVar2 = _Allocate<Player_*>(param_1,(Player **)0x0);
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
