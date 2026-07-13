/*
 * Entry: 004e47ca
 * Name: std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator+=
 * Namespace: std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Signature: _Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * operator+=(_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * __thiscall
std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator+=
          (_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *this,int param_1)

{
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator+=
            ((_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *)this,param_1);
  return this;
}
