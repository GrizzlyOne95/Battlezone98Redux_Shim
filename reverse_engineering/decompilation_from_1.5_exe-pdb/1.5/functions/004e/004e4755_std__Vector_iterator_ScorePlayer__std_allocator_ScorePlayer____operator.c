/*
 * Entry: 004e4755
 * Name: std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator++
 * Namespace: std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Signature: _Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * operator++(_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * __thiscall
std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator++
          (_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *this)

{
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator++
            ((_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *)this);
  return this;
}
