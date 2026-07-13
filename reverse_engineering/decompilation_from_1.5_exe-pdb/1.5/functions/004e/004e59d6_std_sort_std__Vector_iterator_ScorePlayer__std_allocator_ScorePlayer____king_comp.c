/*
 * Entry: 004e59d6
 * Name: std::sort<std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>,king_comp>
 * Namespace: std
 * Signature: void sort<std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>,king_comp>(_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> param_1, _Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> param_2, king_comp param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::sort<std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>,king_comp>
          (_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> param_1,
          _Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> param_2,king_comp param_3)

{
  int iVar1;
  
  iVar1 = _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator-
                    ((_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *)
                     &param_2,(_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
                               *)&param_1);
  _Sort<ScorePlayer_*_*,int,king_comp>
            ((ScorePlayer **)param_1._4_4_,(ScorePlayer **)param_2._4_4_,iVar1,param_3);
  return;
}
