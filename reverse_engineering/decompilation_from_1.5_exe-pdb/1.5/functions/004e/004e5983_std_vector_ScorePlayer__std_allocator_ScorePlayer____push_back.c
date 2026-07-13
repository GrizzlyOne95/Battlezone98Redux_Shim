/*
 * Entry: 004e5983
 * Name: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::push_back
 * Namespace: std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Signature: void push_back(vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * this, ScorePlayer * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::push_back
          (vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *this,ScorePlayer **param_1)

{
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> _Var1;
  uint uVar2;
  ScorePlayer **ppSVar3;
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> local_c;
  
  ppSVar3 = this->_Mylast;
  local_c._padding_ = (int)this;
  local_c._Myptr = (ScorePlayer **)this;
  uVar2 = capacity(this);
  if ((uint)((int)ppSVar3 - (int)this->_Myfirst >> 2) < uVar2) {
    ppSVar3 = _Ufill(this,ppSVar3,1,param_1);
    this->_Mylast = ppSVar3;
  }
  else {
    _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::
    _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
              (&local_c,ppSVar3,(_Container_base_aux *)this);
    _Var1._Myptr = (ScorePlayer **)local_c._padding_;
    _Var1._padding_ = (int)&local_c;
    insert(this,_Var1,local_c._Myptr);
  }
  return;
}
