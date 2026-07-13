/*
 * Entry: 005189e5
 * Name: std::_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Namespace: std::_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Signature: _Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * _Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>(_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * this, ObjectClassInfo * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * __thiscall
std::_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
          (_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this,
          ObjectClassInfo **param_1,_Container_base_aux *param_2)

{
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
            ((_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *)this,
             param_1,param_2);
  return this;
}
