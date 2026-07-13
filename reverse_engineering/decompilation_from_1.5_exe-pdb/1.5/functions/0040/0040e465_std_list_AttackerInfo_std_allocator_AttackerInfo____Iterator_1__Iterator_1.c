/*
 * Entry: 0040e465
 * Name: std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Iterator<1>::_Iterator<1>
 * Namespace: std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Iterator<1>
 * Signature: _Iterator<1> * _Iterator<1>(_Iterator<1> * this, _Node * param_1, list<AttackerInfo,std::allocator<AttackerInfo>_> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Iterator<1>::_Iterator<1>
          (_Iterator<1> *this,_Node *param_1,
          list<AttackerInfo,std::allocator<AttackerInfo>_> *param_2)

{
  list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
            ((_Const_iterator<1> *)this,param_1,param_2);
  return this;
}
