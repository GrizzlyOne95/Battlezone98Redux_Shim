/*
 * Entry: 004e472a
 * Name: std::_Vector_val<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::~_Vector_val<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Namespace: std::_Vector_val<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Signature: void ~_Vector_val<ScorePlayer_*,std::allocator<ScorePlayer_*>_>(_Vector_val<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::
~_Vector_val<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
          (_Vector_val<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
