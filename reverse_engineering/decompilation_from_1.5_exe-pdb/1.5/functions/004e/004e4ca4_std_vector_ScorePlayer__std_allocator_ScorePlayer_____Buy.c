/*
 * Entry: 004e4ca4
 * Name: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::_Buy
 * Namespace: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Signature: bool _Buy(vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::_Buy
          (vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *this,uint param_1)

{
  bool bVar1;
  ScorePlayer **ppSVar2;
  
  this->_Myfirst = (ScorePlayer **)0x0;
  this->_Mylast = (ScorePlayer **)0x0;
  this->_Myend = (ScorePlayer **)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x40000000) {
      ppSVar2 = _Allocate<ScorePlayer_*>(param_1,(ScorePlayer **)0x0);
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
