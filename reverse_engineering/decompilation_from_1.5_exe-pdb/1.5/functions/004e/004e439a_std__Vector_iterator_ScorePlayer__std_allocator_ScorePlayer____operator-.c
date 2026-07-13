/*
 * Entry: 004e439a
 * Name: std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator-
 * Namespace: std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Signature: int operator-(_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * this, _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall
std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator-
          (_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *this,
          _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *param_1)

{
  if ((*(int *)this == 0) || (*(int *)this != param_1->_padding_)) {
    _invalid_parameter_noinfo();
  }
  return *(int *)&this->field_0x4 - (int)param_1->_Myptr >> 2;
}
