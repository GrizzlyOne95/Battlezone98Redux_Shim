/*
 * Entry: 004e5351
 * Name: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::begin
 * Namespace: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Signature: _Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> begin(vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> __thiscall
std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::begin
          (vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> _Var1;
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *in_stack_00000004;
  
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
            (in_stack_00000004,this->_Myfirst,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
