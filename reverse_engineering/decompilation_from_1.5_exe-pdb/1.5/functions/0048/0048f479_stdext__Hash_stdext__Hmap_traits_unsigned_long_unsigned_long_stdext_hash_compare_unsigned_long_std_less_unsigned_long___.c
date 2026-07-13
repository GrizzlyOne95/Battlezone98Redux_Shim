/*
 * Entry: 0048f479
 * Name: stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::erase
 * Namespace: stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
 * Signature: _Iterator<1> erase(_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_> * this, _Const_iterator<1> param_1, _Const_iterator<1> param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> __thiscall
stdext::
_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
::erase(_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
        *this,_Const_iterator<1> param_1,_Const_iterator<1> param_2)

{
  list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
  *this_00;
  _Const_iterator<1> _Var1;
  _Node *p_Var2;
  bool bVar3;
  undefined4 uVar4;
  undefined4 extraout_EDX;
  _Iterator<1> _Var5;
  _Iterator<1> _Var6;
  undefined1 local_14 [8];
  _Const_iterator<1> local_c;
  
  this_00 = &this->_List;
  std::
  list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
  ::_Const_iterator<1>::_Const_iterator<1>(&local_c,((this->_List)._Myhead)->_Next,this_00);
  bVar3 = std::
          list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
          ::_Const_iterator<1>::operator==((_Const_iterator<1> *)&param_1._Ptr,&local_c);
  if (bVar3) {
    std::
    list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
    ::_Const_iterator<1>::_Const_iterator<1>(&local_c,(this->_List)._Myhead,this_00);
    bVar3 = std::
            list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
            ::_Const_iterator<1>::operator==((_Const_iterator<1> *)&param_2._Ptr,&local_c);
    if (bVar3) {
      clear(this);
      _Var5 = std::
              list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
              ::begin(this_00);
      uVar4 = _Var5._4_4_;
      goto LAB_0048f521;
    }
  }
  bVar3 = std::
          list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
          ::_Const_iterator<1>::operator==
                    ((_Const_iterator<1> *)&param_1._Ptr,(_Const_iterator<1> *)&param_2._Ptr);
  p_Var2 = param_1._Ptr;
  while (param_1._Ptr = p_Var2, !bVar3) {
    local_c._Ptr = (_Node *)param_2._padding_;
    std::
    list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
    ::_Const_iterator<1>::operator++((_Const_iterator<1> *)&param_1._Ptr);
    _Var1._Ptr = p_Var2;
    _Var1._padding_ = (int)local_14;
    erase(this,_Var1);
    bVar3 = std::
            list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
            ::_Const_iterator<1>::operator==
                      ((_Const_iterator<1> *)&param_1._Ptr,(_Const_iterator<1> *)&param_2._Ptr);
    p_Var2 = param_1._Ptr;
  }
  std::
  list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
  ::_Const_iterator<1>::_Const_iterator<1>
            ((_Const_iterator<1> *)param_1._padding_,(_Node *)param_2._padding_,this_00);
  uVar4 = extraout_EDX;
LAB_0048f521:
  _Var6._4_4_ = uVar4;
  _Var6._0_4_ = param_1._padding_;
  return _Var6;
}
