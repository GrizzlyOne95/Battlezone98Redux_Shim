/*
 * Entry: 004e5494
 * Name: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::back
 * Namespace: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Signature: ScorePlayer * * back(vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScorePlayer ** __thiscall
std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::back
          (vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *this)

{
  ScorePlayer **ppSVar1;
  _Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> _Var2;
  undefined1 local_14 [8];
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> local_c;
  
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
            (&local_c,this->_Mylast,(_Container_base_aux *)this);
  _Var2 = _Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator-
                    ((_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *)&local_c,
                     (int)local_14);
  ppSVar1 = _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator*
                      (_Var2._0_4_);
  return ppSVar1;
}
