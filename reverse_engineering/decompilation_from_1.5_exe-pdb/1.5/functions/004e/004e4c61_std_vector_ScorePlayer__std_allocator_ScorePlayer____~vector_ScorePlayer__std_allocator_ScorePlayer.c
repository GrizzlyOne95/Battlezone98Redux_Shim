/*
 * Entry: 004e4c61
 * Name: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::~vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Namespace: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Signature: void ~vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>(vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::
~vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
          (vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
