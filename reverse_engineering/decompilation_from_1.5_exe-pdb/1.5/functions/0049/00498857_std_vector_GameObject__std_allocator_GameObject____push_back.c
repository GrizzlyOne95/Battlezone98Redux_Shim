/*
 * Entry: 00498857
 * Name: std::vector<GameObject_*,std::allocator<GameObject_*>_>::push_back
 * Namespace: std::vector<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: void push_back(vector<GameObject_*,std::allocator<GameObject_*>_> * this, GameObject * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<GameObject_*,std::allocator<GameObject_*>_>::push_back
          (vector<GameObject_*,std::allocator<GameObject_*>_> *this,GameObject **param_1)

{
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> _Var1;
  uint uVar2;
  GameObject **ppGVar3;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_c;
  
  ppGVar3 = this->_Mylast;
  local_c._padding_ = (int)this;
  local_c._Myptr = (GameObject **)this;
  uVar2 = capacity(this);
  if ((uint)((int)ppGVar3 - (int)this->_Myfirst >> 2) < uVar2) {
    ppGVar3 = _Ufill(this,ppGVar3,1,param_1);
    this->_Mylast = ppGVar3;
  }
  else {
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_c,ppGVar3,(_Container_base_aux *)this);
    _Var1._Myptr = (GameObject **)local_c._padding_;
    _Var1._padding_ = (int)&local_c;
    insert(this,_Var1,local_c._Myptr);
  }
  return;
}
