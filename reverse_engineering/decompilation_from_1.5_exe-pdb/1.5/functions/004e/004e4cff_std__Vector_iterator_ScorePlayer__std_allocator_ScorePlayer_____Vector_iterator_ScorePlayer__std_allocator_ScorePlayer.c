/*
 * Entry: 004e4cff
 * Name: std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Namespace: std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Signature: _Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * _Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>(_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * this, ScorePlayer * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * __thiscall
std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::
_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
          (_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *this,
          ScorePlayer **param_1,_Container_base_aux *param_2)

{
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
            ((_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *)this,param_1,
             param_2);
  return this;
}
