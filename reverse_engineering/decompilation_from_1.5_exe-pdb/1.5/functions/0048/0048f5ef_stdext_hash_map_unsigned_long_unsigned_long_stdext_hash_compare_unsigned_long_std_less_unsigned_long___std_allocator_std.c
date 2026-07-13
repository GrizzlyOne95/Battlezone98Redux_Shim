/*
 * Entry: 0048f5ef
 * Name: stdext::hash_map<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::operator[]
 * Namespace: stdext::hash_map<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
 * Signature: ulong * operator[](hash_map<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_> * this, ulong * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong * __thiscall
stdext::
hash_map<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
::operator[](hash_map<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
             *this,ulong *param_1)

{
  bool bVar1;
  pair<std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>,bool>
  *ppVar2;
  pair<unsigned_long_const_,unsigned_long> *ppVar3;
  pair<std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>,bool>
  local_20;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  _Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
  ::lower_bound((_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
                 *)this,(ulong *)&local_c);
  std::
  list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
  ::_Const_iterator<1>::_Const_iterator<1>
            (&local_14,*(_Node **)&this->field_0x1c,
             (list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
              *)&this->field_0x8);
  bVar1 = std::
          list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
          ::_Const_iterator<1>::operator==(&local_c,&local_14);
  if (bVar1) {
    local_14._padding_ = *param_1;
    local_14._Ptr = (_Node *)0x0;
    ppVar2 = _Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
             ::insert((_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
                       *)this,&local_20,(pair<unsigned_long_const_,unsigned_long> *)&local_14);
    local_c._padding_ = *(int *)&ppVar2->first;
    local_c._Ptr = *(_Node **)&(ppVar2->first).field_0x4;
  }
  ppVar3 = std::
           list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
           ::_Const_iterator<1>::operator*(&local_c);
  return &ppVar3->second;
}
