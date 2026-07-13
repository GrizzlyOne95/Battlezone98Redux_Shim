/*
 * Entry: 0047d9ce
 * Name: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::push_back
 * Namespace: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>
 * Signature: void push_back(vector<AnimSprite_*,std::allocator<AnimSprite_*>_> * this, AnimSprite * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::push_back
          (vector<AnimSprite_*,std::allocator<AnimSprite_*>_> *this,AnimSprite **param_1)

{
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> _Var1;
  uint uVar2;
  AnimSprite **ppAVar3;
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> local_c;
  
  ppAVar3 = this->_Mylast;
  local_c._padding_ = (int)this;
  local_c._Myptr = (AnimSprite **)this;
  uVar2 = capacity(this);
  if ((uint)((int)ppAVar3 - (int)this->_Myfirst >> 2) < uVar2) {
    ppAVar3 = _Ufill(this,ppAVar3,1,param_1);
    this->_Mylast = ppAVar3;
  }
  else {
    _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::
    _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>
              (&local_c,ppAVar3,(_Container_base_aux *)this);
    _Var1._Myptr = (AnimSprite **)local_c._padding_;
    _Var1._padding_ = (int)&local_c;
    insert(this,_Var1,local_c._Myptr);
  }
  return;
}
