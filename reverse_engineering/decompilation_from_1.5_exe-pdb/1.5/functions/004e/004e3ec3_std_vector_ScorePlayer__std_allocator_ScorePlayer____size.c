/*
 * Entry: 004e3ec3
 * Name: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::size
 * Namespace: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Signature: uint size(vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::size
          (vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
