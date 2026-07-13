/*
 * Entry: 0048f370
 * Name: stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>::_Reinsert
 * Namespace: stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>
 * Signature: void _Reinsert(_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
stdext::
_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>
::_Reinsert(_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>
            *this)

{
  _Iterator<1> _Var1;
  int iVar2;
  bool bVar3;
  pair<unsigned_long_const_,float> *ppVar4;
  _List_position *p_Var5;
  pair<std::list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::_Iterator<1>,bool>
  local_28;
  _Const_iterator<1> local_1c;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  while( true ) {
    std::
    list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
    ::_Const_iterator<1>::_Const_iterator<1>(&local_c,((this->_List)._Myhead)->_Next,&this->_List);
    iVar2 = local_c._padding_;
    local_14._padding_ = local_c._padding_;
    local_14._Ptr = local_c._Ptr;
    p_Var5 = std::
             vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>::_List_position>_>
             ::operator[](&this->_Vec,0);
    std::
    list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
    ::_Const_iterator<1>::_Const_iterator<1>
              (&local_1c,*(_Node **)&(p_Var5->_Mypos).field_0x4,&this->_List);
    bVar3 = std::
            list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
            ::_Const_iterator<1>::operator==(&local_14,&local_1c);
    if (bVar3) break;
    ppVar4 = std::
             list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
             ::_Const_iterator<1>::operator*(&local_14);
    _Var1._4_4_ = local_c._Ptr;
    _Var1._0_4_ = iVar2;
    _Insert(this,&local_28,ppVar4,_Var1);
  }
  return;
}
