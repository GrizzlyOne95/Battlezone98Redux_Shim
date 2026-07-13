/*
 * Entry: 0049825c
 * Name: std::vector<GameObject_*,std::allocator<GameObject_*>_>::back
 * Namespace: std::vector<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: GameObject * * back(vector<GameObject_*,std::allocator<GameObject_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject ** __thiscall
std::vector<GameObject_*,std::allocator<GameObject_*>_>::back
          (vector<GameObject_*,std::allocator<GameObject_*>_> *this)

{
  GameObject **ppGVar1;
  _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> _Var2;
  undefined1 local_14 [8];
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_c;
  
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_c,this->_Mylast,(_Container_base_aux *)this);
  _Var2 = _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator-
                    ((_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> *)&local_c,
                     (int)local_14);
  ppGVar1 = _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                      (_Var2._0_4_);
  return ppGVar1;
}
