/*
 * Entry: 00498351
 * Name: std::vector<GameObject_*,std::allocator<GameObject_*>_>::_Umove<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>_>
 * Namespace: std::vector<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: GameObject * * _Umove<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>_>(vector<GameObject_*,std::allocator<GameObject_*>_> * this, _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> param_1, _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> param_2, GameObject * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject ** __thiscall
std::vector<GameObject_*,std::allocator<GameObject_*>_>::
_Umove<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>_>
          (vector<GameObject_*,std::allocator<GameObject_*>_> *this,
          _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> param_1,
          _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> param_2,GameObject **param_3)

{
  GameObject **ppGVar1;
  
  ppGVar1 = stdext::
            _Unchecked_uninitialized_move<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,GameObject_*_*,std::allocator<GameObject_*>_>
                      (param_1,param_2,param_3,(allocator<GameObject_*> *)&this->_padding_);
  return ppGVar1;
}
