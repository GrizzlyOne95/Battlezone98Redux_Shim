/*
 * Entry: 004e5cc6
 * Name: ScorePlayer::Sort
 * Namespace: ScorePlayer
 * Signature: void Sort(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ScorePlayer::Sort(void)

{
  _Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> _Var1;
  _Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> _Var2;
  _Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> _Var3;
  _Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> _Var4;
  _Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> _Var5;
  _Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> _Var6;
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> local_18;
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> local_10;
  uint local_8;
  
  local_8 = local_8 & 0xffffff00;
  if (king_of_the_hill_game == 0) {
    if (stratgy_game == 0) {
      std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::
      _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
                (&local_18,playerV._Mylast,(_Container_base_aux *)&playerV);
      std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::
      _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
                (&local_10,playerV._Myfirst,(_Container_base_aux *)&playerV);
      _Var3._4_4_ = local_10._Myptr;
      _Var3._0_4_ = local_10._padding_;
      _Var6._4_4_ = local_18._Myptr;
      _Var6._0_4_ = local_18._padding_;
      std::sort<std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>,comp>
                (_Var3,_Var6,SUB41(local_8,0));
    }
    else {
      std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::
      _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
                (&local_18,playerV._Mylast,(_Container_base_aux *)&playerV);
      std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::
      _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
                (&local_10,playerV._Myfirst,(_Container_base_aux *)&playerV);
      _Var2._4_4_ = local_10._Myptr;
      _Var2._0_4_ = local_10._padding_;
      _Var5._4_4_ = local_18._Myptr;
      _Var5._0_4_ = local_18._padding_;
      std::sort<std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>,lives_comp>
                (_Var2,_Var5,SUB41(local_8,0));
    }
  }
  else {
    std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::
    _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
              (&local_10,playerV._Mylast,(_Container_base_aux *)&playerV);
    std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::
    _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
              (&local_18,playerV._Myfirst,(_Container_base_aux *)&playerV);
    _Var1._4_4_ = local_18._Myptr;
    _Var1._0_4_ = local_18._padding_;
    _Var4._4_4_ = local_10._Myptr;
    _Var4._0_4_ = local_10._padding_;
    std::sort<std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>,king_comp>
              (_Var1,_Var4,SUB41(local_8,0));
  }
  return;
}
