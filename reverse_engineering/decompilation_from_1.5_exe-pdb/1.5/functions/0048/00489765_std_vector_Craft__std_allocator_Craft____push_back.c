/*
 * Entry: 00489765
 * Name: std::vector<Craft_*,std::allocator<Craft_*>_>::push_back
 * Namespace: std::vector<Craft_*,std::allocator<Craft_*>_>
 * Signature: void push_back(vector<Craft_*,std::allocator<Craft_*>_> * this, Craft * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Craft_*,std::allocator<Craft_*>_>::push_back
          (vector<Craft_*,std::allocator<Craft_*>_> *this,Craft **param_1)

{
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> _Var1;
  uint uVar2;
  Craft **ppCVar3;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_c;
  
  ppCVar3 = this->_Mylast;
  local_c._padding_ = (int)this;
  local_c._Myptr = (Craft **)this;
  uVar2 = capacity(this);
  if ((uint)((int)ppCVar3 - (int)this->_Myfirst >> 2) < uVar2) {
    ppCVar3 = _Ufill(this,ppCVar3,1,param_1);
    this->_Mylast = ppCVar3;
  }
  else {
    _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
    _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
              (&local_c,ppCVar3,(_Container_base_aux *)this);
    _Var1._Myptr = (Craft **)local_c._padding_;
    _Var1._padding_ = (int)&local_c;
    insert(this,_Var1,local_c._Myptr);
  }
  return;
}
