/*
 * Entry: 0048cf16
 * Name: stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::erase
 * Namespace: stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
 * Signature: _Iterator<1> erase(_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_> * this, _Const_iterator<1> param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> __thiscall
stdext::
_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
::erase(_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
        *this,_Const_iterator<1> param_1)

{
  vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position>_>
  *this_00;
  _Const_iterator<1> _Var1;
  pair<unsigned_long_const_,unsigned_long> *ppVar2;
  uint uVar3;
  _List_position *p_Var4;
  _Iterator<1> _Var5;
  _Iterator<1> _Var6;
  int in_stack_0000000c;
  _List_position local_14;
  _Const_iterator<1> local_c;
  
  ppVar2 = std::
           list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
           ::_Const_iterator<1>::operator*((_Const_iterator<1> *)&param_1._Ptr);
  uVar3 = _Hashval(this,&ppVar2->first);
  this_00 = &this->_Vec;
  while( true ) {
    p_Var4 = std::
             vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position>_>
             ::operator[](this_00,uVar3);
    if (*(int *)&(p_Var4->_Mypos).field_0x4 != in_stack_0000000c) break;
    p_Var4 = std::
             vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position>_>
             ::operator[](this_00,uVar3);
    std::
    list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
    ::_Const_iterator<1>::_Const_iterator<1>
              (&local_c,*(_Node **)&(p_Var4->_Mypos).field_0x4,&this->_List);
    std::
    list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
    ::_Const_iterator<1>::operator++(&local_c);
    _Var5._4_4_ = local_c._Ptr;
    _Var5._0_4_ = local_c._padding_;
    _List_position::_List_position(&local_14,_Var5);
    p_Var4 = std::
             vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position>_>
             ::operator[](this_00,uVar3);
    *(undefined4 *)&p_Var4->_Mypos = local_14._Mypos._0_4_;
    *(undefined4 *)&(p_Var4->_Mypos).field_0x4 = local_14._Mypos._4_4_;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
  }
  _Var1._Ptr = param_1._Ptr;
  _Var1._padding_ = param_1._padding_;
  _Var5 = std::
          list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
          ::erase(&this->_List,_Var1);
  _Var6._4_4_ = _Var5._4_4_;
  _Var6._0_4_ = param_1._padding_;
  return _Var6;
}
