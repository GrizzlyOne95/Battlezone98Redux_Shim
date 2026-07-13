/*
 * Entry: 00461730
 * Name: std::vector<Scrap_*,std::allocator<Scrap_*>_>::push_back
 * Namespace: std::vector<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: void push_back(vector<Scrap_*,std::allocator<Scrap_*>_> * this, Scrap * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Scrap_*,std::allocator<Scrap_*>_>::push_back
          (vector<Scrap_*,std::allocator<Scrap_*>_> *this,Scrap **param_1)

{
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> _Var1;
  uint uVar2;
  Scrap **ppSVar3;
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> local_c;
  
  ppSVar3 = this->_Mylast;
  local_c._padding_ = (int)this;
  local_c._Myptr = (Scrap **)this;
  uVar2 = capacity(this);
  if ((uint)((int)ppSVar3 - (int)this->_Myfirst >> 2) < uVar2) {
    ppSVar3 = _Ufill(this,ppSVar3,1,param_1);
    this->_Mylast = ppSVar3;
  }
  else {
    _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::
    _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>
              (&local_c,ppSVar3,(_Container_base_aux *)this);
    _Var1._Myptr = (Scrap **)local_c._padding_;
    _Var1._padding_ = (int)&local_c;
    insert(this,_Var1,local_c._Myptr);
  }
  return;
}
