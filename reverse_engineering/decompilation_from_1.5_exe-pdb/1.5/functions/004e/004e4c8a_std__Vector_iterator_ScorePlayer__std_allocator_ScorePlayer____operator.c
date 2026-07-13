/*
 * Entry: 004e4c8a
 * Name: std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator++
 * Namespace: std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Signature: _Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> operator++(_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> __thiscall
std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator++
          (_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *this,int param_1)

{
  undefined4 extraout_EDX;
  _Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> _Var1;
  
  *(undefined4 *)param_1 = *(undefined4 *)this;
  *(undefined4 *)(param_1 + 4) = *(undefined4 *)&this->field_0x4;
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator++
            ((_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = param_1;
  return _Var1;
}
