/*
 * Entry: 004e4c73
 * Name: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::pop_back
 * Namespace: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Signature: void pop_back(vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::pop_back
          (vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *this)

{
  if (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0) {
    this->_Mylast = this->_Mylast + -1;
  }
  return;
}
