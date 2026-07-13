/*
 * Entry: 0040b434
 * Name: std::list<AOI_*,std::allocator<AOI_*>_>::_Iterator<1>::_Iterator<1>
 * Namespace: std::list<AOI_*,std::allocator<AOI_*>_>::_Iterator<1>
 * Signature: _Iterator<1> * _Iterator<1>(_Iterator<1> * this, _Node * param_1, list<AOI_*,std::allocator<AOI_*>_> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<AOI_*,std::allocator<AOI_*>_>::_Iterator<1>::_Iterator<1>
          (_Iterator<1> *this,_Node *param_1,list<AOI_*,std::allocator<AOI_*>_> *param_2)

{
  list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::_Const_iterator<1>
            ((_Const_iterator<1> *)this,param_1,param_2);
  return this;
}
