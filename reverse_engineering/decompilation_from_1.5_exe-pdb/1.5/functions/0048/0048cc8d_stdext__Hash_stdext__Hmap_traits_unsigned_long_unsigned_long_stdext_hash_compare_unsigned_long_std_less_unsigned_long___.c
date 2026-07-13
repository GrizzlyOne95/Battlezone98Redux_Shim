/*
 * Entry: 0048cc8d
 * Name: stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::equal_range
 * Namespace: stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
 * Signature: pair<std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>,std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>_> * equal_range(_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_> * this, pair<std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>,std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>_> * __return_storage_ptr__, ulong * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Variable defined which should be unmapped: __return_storage_ptr__ */

pair<std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>,std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>_>
* __thiscall
stdext::
_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
::equal_range(_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
              *this,pair<std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>,std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>_>
                    *__return_storage_ptr__,ulong *param_1)

{
  vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position>_>
  *this_00;
  list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
  *plVar1;
  bool bVar2;
  uint uVar3;
  _List_position *p_Var4;
  pair<unsigned_long_const_,unsigned_long> *ppVar5;
  _Node *p_Var6;
  _Const_iterator<1> local_18;
  _Const_iterator<1> local_10;
  list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
  *local_8;
  
  uVar3 = _Hashval(this,param_1);
  this_00 = &this->_Vec;
  p_Var4 = std::
           vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position>_>
           ::operator[](this_00,uVar3);
  local_8 = &this->_List;
  std::
  list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
  ::_Const_iterator<1>::_Const_iterator<1>(&local_18,*(_Node **)&(p_Var4->_Mypos).field_0x4,local_8)
  ;
  p_Var6 = local_18._Ptr;
  uVar3 = uVar3 + 1;
  local_10._padding_ = local_18._padding_;
  local_10._Ptr = local_18._Ptr;
  p_Var4 = std::
           vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position>_>
           ::operator[](this_00,uVar3);
  if (*(_Node **)&(p_Var4->_Mypos).field_0x4 != p_Var6) {
    do {
      ppVar5 = std::
               list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
               ::_Const_iterator<1>::operator*(&local_10);
      if (*param_1 <= ppVar5->first) {
        local_18._padding_ = local_10._padding_;
        local_18._Ptr = p_Var6;
        p_Var4 = std::
                 vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position>_>
                 ::operator[](this_00,uVar3);
        while ((*(_Node **)&(p_Var4->_Mypos).field_0x4 != p_Var6 &&
               (ppVar5 = std::
                         list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
                         ::_Const_iterator<1>::operator*(&local_10), ppVar5->first <= *param_1))) {
          std::
          list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
          ::_Const_iterator<1>::operator++(&local_10);
          p_Var4 = std::
                   vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position>_>
                   ::operator[](this_00,uVar3);
          p_Var6 = local_10._Ptr;
        }
        bVar2 = std::
                list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
                ::_Const_iterator<1>::operator==(&local_18,&local_10);
        if (!bVar2) {
          *(int *)&__return_storage_ptr__->first = local_18._padding_;
          *(_Node **)&(__return_storage_ptr__->first).field_0x4 = local_18._Ptr;
          *(int *)&__return_storage_ptr__->second = local_10._padding_;
          *(_Node **)&(__return_storage_ptr__->second).field_0x4 = p_Var6;
          return __return_storage_ptr__;
        }
        break;
      }
      std::
      list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
      ::_Const_iterator<1>::operator++(&local_10);
      p_Var4 = std::
               vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position>_>
               ::operator[](this_00,uVar3);
      p_Var6 = local_10._Ptr;
    } while (*(_Node **)&(p_Var4->_Mypos).field_0x4 != local_10._Ptr);
  }
  plVar1 = local_8;
  std::
  list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
  ::_Const_iterator<1>::_Const_iterator<1>(&local_10,local_8->_Myhead,local_8);
  std::
  list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
  ::_Const_iterator<1>::_Const_iterator<1>(&local_18,plVar1->_Myhead,plVar1);
  *(int *)&__return_storage_ptr__->first = local_18._padding_;
  *(_Node **)&(__return_storage_ptr__->first).field_0x4 = local_18._Ptr;
  *(int *)&__return_storage_ptr__->second = local_10._padding_;
  *(_Node **)&(__return_storage_ptr__->second).field_0x4 = local_10._Ptr;
  return __return_storage_ptr__;
}
