/*
 * Entry: 00461414
 * Name: std::vector<Scrap_*,std::allocator<Scrap_*>_>::_Umove<std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>_>
 * Namespace: std::vector<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: Scrap * * _Umove<std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>_>(vector<Scrap_*,std::allocator<Scrap_*>_> * this, _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> param_1, _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> param_2, Scrap * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scrap ** __thiscall
std::vector<Scrap_*,std::allocator<Scrap_*>_>::
_Umove<std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>_>
          (vector<Scrap_*,std::allocator<Scrap_*>_> *this,
          _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> param_1,
          _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> param_2,Scrap **param_3)

{
  Scrap **ppSVar1;
  
  ppSVar1 = stdext::
            _Unchecked_uninitialized_move<std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>,Scrap_*_*,std::allocator<Scrap_*>_>
                      (param_1,param_2,param_3,(allocator<Scrap_*> *)&this->_padding_);
  return ppSVar1;
}
