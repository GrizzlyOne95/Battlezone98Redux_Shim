/*
 * Entry: 004ae645
 * Name: std::vector<Scanner_*,std::allocator<Scanner_*>_>::push_back
 * Namespace: std::vector<Scanner_*,std::allocator<Scanner_*>_>
 * Signature: void push_back(vector<Scanner_*,std::allocator<Scanner_*>_> * this, Scanner * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Scanner_*,std::allocator<Scanner_*>_>::push_back
          (vector<Scanner_*,std::allocator<Scanner_*>_> *this,Scanner **param_1)

{
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> _Var1;
  uint uVar2;
  Scanner **ppSVar3;
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> local_c;
  
  ppSVar3 = this->_Mylast;
  local_c._padding_ = (int)this;
  local_c._Myptr = (Scanner **)this;
  uVar2 = capacity(this);
  if ((uint)((int)ppSVar3 - (int)this->_Myfirst >> 2) < uVar2) {
    ppSVar3 = _Ufill(this,ppSVar3,1,param_1);
    this->_Mylast = ppSVar3;
  }
  else {
    _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>::
    _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>
              (&local_c,ppSVar3,(_Container_base_aux *)this);
    _Var1._Myptr = (Scanner **)local_c._padding_;
    _Var1._padding_ = (int)&local_c;
    insert(this,_Var1,local_c._Myptr);
  }
  return;
}
