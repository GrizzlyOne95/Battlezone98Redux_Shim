/*
 * Entry: 004e3ecd
 * Name: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::empty
 * Namespace: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Signature: bool empty(vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::empty
          (vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *this)

{
  return (bool)('\x01' - (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0));
}
