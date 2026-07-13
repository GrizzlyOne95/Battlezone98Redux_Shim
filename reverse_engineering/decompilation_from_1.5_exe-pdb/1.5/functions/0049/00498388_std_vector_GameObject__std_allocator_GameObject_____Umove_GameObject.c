/*
 * Entry: 00498388
 * Name: std::vector<GameObject_*,std::allocator<GameObject_*>_>::_Umove<GameObject_*_*>
 * Namespace: std::vector<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: GameObject * * _Umove<GameObject_*_*>(vector<GameObject_*,std::allocator<GameObject_*>_> * this, GameObject * * param_1, GameObject * * param_2, GameObject * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject ** __thiscall
std::vector<GameObject_*,std::allocator<GameObject_*>_>::_Umove<GameObject_*_*>
          (vector<GameObject_*,std::allocator<GameObject_*>_> *this,GameObject **param_1,
          GameObject **param_2,GameObject **param_3)

{
  GameObject **ppGVar1;
  
  ppGVar1 = stdext::
            unchecked_uninitialized_copy<GameObject_*_*,GameObject_*_*,std::allocator<GameObject_*>_>
                      (param_1,param_2,param_3,(allocator<GameObject_*> *)&this->_padding_);
  return ppGVar1;
}
