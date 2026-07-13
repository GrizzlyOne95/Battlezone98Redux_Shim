/*
 * Entry: 0055c4cb
 * Name: std::vector<Server_*,std::allocator<Server_*>_>::push_back
 * Namespace: std::vector<Server_*,std::allocator<Server_*>_>
 * Signature: void push_back(vector<Server_*,std::allocator<Server_*>_> * this, Server * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Server_*,std::allocator<Server_*>_>::push_back
          (vector<Server_*,std::allocator<Server_*>_> *this,Server **param_1)

{
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_> _Var1;
  uint uVar2;
  Server **ppSVar3;
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_> local_c;
  
  ppSVar3 = this->_Mylast;
  local_c._padding_ = (int)this;
  local_c._Myptr = (Server **)this;
  uVar2 = capacity(this);
  if ((uint)((int)ppSVar3 - (int)this->_Myfirst >> 2) < uVar2) {
    ppSVar3 = _Ufill(this,ppSVar3,1,param_1);
    this->_Mylast = ppSVar3;
  }
  else {
    _Vector_const_iterator<Server_*,std::allocator<Server_*>_>::
    _Vector_const_iterator<Server_*,std::allocator<Server_*>_>
              (&local_c,ppSVar3,(_Container_base_aux *)this);
    _Var1._Myptr = (Server **)local_c._padding_;
    _Var1._padding_ = (int)&local_c;
    insert(this,_Var1,local_c._Myptr);
  }
  return;
}
