/*
 * Entry: 0048d683
 * Name: stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>::lower_bound
 * Namespace: stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>
 * Signature: _Iterator<1> lower_bound(_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_> * this, ulong * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> __thiscall
stdext::
_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>
::lower_bound(_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>
              *this,ulong *param_1)

{
  vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>::_List_position>_>
  *this_00;
  _Node *p_Var1;
  _List_position *p_Var2;
  pair<unsigned_long_const_,float> *ppVar3;
  _Const_iterator<1> *p_Var4;
  ulong uVar5;
  _Iterator<1> _Var6;
  _Iterator<1> _Var7;
  ulong *in_stack_00000008;
  _Const_iterator<1> local_1c;
  _Const_iterator<1> local_14;
  list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
  *local_c;
  uint local_8;
  
  local_8 = _Hashval(this,in_stack_00000008);
  this_00 = &this->_Vec;
  p_Var2 = std::
           vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>::_List_position>_>
           ::operator[](this_00,local_8);
  local_c = &this->_List;
  std::
  list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
  ::_Const_iterator<1>::_Const_iterator<1>(&local_1c,*(_Node **)&(p_Var2->_Mypos).field_0x4,local_c)
  ;
  local_14._padding_ = local_1c._padding_;
  local_8 = local_8 + 1;
  local_14._Ptr = local_1c._Ptr;
  p_Var2 = std::
           vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>::_List_position>_>
           ::operator[](this_00,local_8);
  if (*(_Node **)&(p_Var2->_Mypos).field_0x4 != local_1c._Ptr) {
    do {
      ppVar3 = std::
               list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
               ::_Const_iterator<1>::operator*(&local_14);
      if (*in_stack_00000008 <= ppVar3->first) {
        ppVar3 = std::
                 list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
                 ::_Const_iterator<1>::operator*(&local_14);
        if (*in_stack_00000008 < ppVar3->first) {
          std::
          list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
          ::_Const_iterator<1>::_Const_iterator<1>(&local_1c,local_c->_Myhead,local_c);
          p_Var4 = &local_1c;
        }
        else {
          p_Var4 = &local_14;
        }
        uVar5 = p_Var4->_padding_;
        p_Var1 = p_Var4->_Ptr;
        *param_1 = uVar5;
        param_1[1] = (ulong)p_Var1;
        goto LAB_0048d70e;
      }
      std::
      list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
      ::_Const_iterator<1>::operator++(&local_14);
      p_Var2 = std::
               vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>::_List_position>_>
               ::operator[](this_00,local_8);
    } while (*(_Node **)&(p_Var2->_Mypos).field_0x4 != local_14._Ptr);
  }
  _Var6 = end(this);
  uVar5 = _Var6._4_4_;
LAB_0048d70e:
  _Var7._4_4_ = uVar5;
  _Var7._0_4_ = param_1;
  return _Var7;
}
