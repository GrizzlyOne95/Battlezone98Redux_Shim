/*
 * Entry: 0041cc6f
 * Name: std::vector<GameObject_*,std::allocator<GameObject_*>_>::at
 * Namespace: std::vector<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: GameObject * * at(vector<GameObject_*,std::allocator<GameObject_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject ** __thiscall
std::vector<GameObject_*,std::allocator<GameObject_*>_>::at
          (vector<GameObject_*,std::allocator<GameObject_*>_> *this,uint param_1)

{
  GameObject **ppGVar1;
  _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> _Var2;
  undefined1 local_14 [8];
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_c;
  
  if ((uint)((int)this->_Mylast - (int)this->_Myfirst >> 2) <= param_1) {
    _Xran();
  }
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_c,this->_Myfirst,(_Container_base_aux *)this);
  _Var2 = _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator+
                    ((_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> *)&local_c,
                     (int)local_14);
  ppGVar1 = _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                      (_Var2._0_4_);
  return ppGVar1;
}
