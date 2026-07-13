/*
 * Entry: 00494aa9
 * Name: std::vector<GameFeature_*,std::allocator<GameFeature_*>_>::push_back
 * Namespace: std::vector<GameFeature_*,std::allocator<GameFeature_*>_>
 * Signature: void push_back(vector<GameFeature_*,std::allocator<GameFeature_*>_> * this, GameFeature * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<GameFeature_*,std::allocator<GameFeature_*>_>::push_back
          (vector<GameFeature_*,std::allocator<GameFeature_*>_> *this,GameFeature **param_1)

{
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_> _Var1;
  uint uVar2;
  GameFeature **ppGVar3;
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_> local_c;
  
  ppGVar3 = this->_Mylast;
  local_c._padding_ = (int)this;
  local_c._Myptr = (GameFeature **)this;
  uVar2 = capacity(this);
  if ((uint)((int)ppGVar3 - (int)this->_Myfirst >> 2) < uVar2) {
    ppGVar3 = _Ufill(this,ppGVar3,1,param_1);
    this->_Mylast = ppGVar3;
  }
  else {
    _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::
    _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
              (&local_c,ppGVar3,(_Container_base_aux *)this);
    _Var1._Myptr = (GameFeature **)local_c._padding_;
    _Var1._padding_ = (int)&local_c;
    insert(this,_Var1,local_c._Myptr);
  }
  return;
}
