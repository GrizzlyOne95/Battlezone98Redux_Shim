/*
 * Entry: 005352f1
 * Name: std::_Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::_Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
 * Namespace: std::_Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
 * Signature: _Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * _Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>(_Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * this, OrdnanceClass * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * __thiscall
std::_Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::
_Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
          (_Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *this,
          OrdnanceClass **param_1,_Container_base_aux *param_2)

{
  _Vector_const_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::
  _Vector_const_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
            ((_Vector_const_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *)this,
             param_1,param_2);
  return this;
}
