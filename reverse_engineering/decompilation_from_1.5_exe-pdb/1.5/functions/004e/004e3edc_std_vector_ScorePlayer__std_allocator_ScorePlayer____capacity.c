/*
 * Entry: 004e3edc
 * Name: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::capacity
 * Namespace: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Signature: uint capacity(vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::capacity
          (vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *this)

{
  if (this->_Myfirst == (ScorePlayer **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
