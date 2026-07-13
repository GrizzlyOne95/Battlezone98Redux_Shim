/*
 * Entry: 004e4736
 * Name: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::_Tidy
 * Namespace: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Signature: void _Tidy(vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::_Tidy
          (vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *this)

{
  if (this->_Myfirst != (ScorePlayer **)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (ScorePlayer **)0x0;
  this->_Mylast = (ScorePlayer **)0x0;
  this->_Myend = (ScorePlayer **)0x0;
  return;
}
