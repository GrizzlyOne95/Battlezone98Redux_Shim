/*
 * Entry: 004a4332
 * Name: stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_Insert
 * Namespace: stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>
 * Signature: pair<std::list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>::_Iterator<1>,bool> * _Insert(_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_> * this, pair<std::list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>::_Iterator<1>,bool> * __return_storage_ptr__, pair<unsigned_int_const_,char_const_*> * param_1, _Iterator<1> param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Variable defined which should be unmapped: __return_storage_ptr__ */

pair<std::list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>::_Iterator<1>,bool>
* __thiscall
stdext::
_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>
::_Insert(_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>
          *this,pair<std::list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>::_Iterator<1>,bool>
                *__return_storage_ptr__,pair<unsigned_int_const_,char_const_*> *param_1,
         _Iterator<1> param_2)

{
  list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
  *this_00;
  _Const_iterator<1> _Var1;
  _Const_iterator<1> _Var2;
  _Const_iterator<1> _Var3;
  _Const_iterator<1> _Var4;
  bool bVar5;
  uint uVar6;
  _List_position *p_Var7;
  pair<unsigned_int_const_,char_const_*> *ppVar8;
  int iVar9;
  _Iterator<1> _Var10;
  float fVar11;
  _Const_iterator<1> local_1c;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  uVar6 = _Hashval(this,&param_1->first);
  p_Var7 = std::
           vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>_>
           ::operator[](&this->_Vec,uVar6 + 1);
  this_00 = &this->_List;
  std::
  list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
  ::_Const_iterator<1>::_Const_iterator<1>(&local_c,*(_Node **)&(p_Var7->_Mypos).field_0x4,this_00);
  do {
    p_Var7 = std::
             vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>_>
             ::operator[](&this->_Vec,uVar6);
    std::
    list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
    ::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,*(_Node **)&(p_Var7->_Mypos).field_0x4,this_00);
    bVar5 = std::
            list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
            ::_Const_iterator<1>::operator==(&local_c,&local_14);
    if (bVar5) goto LAB_004a43a2;
    std::
    list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
    ::_Const_iterator<1>::operator--(&local_c);
    ppVar8 = std::
             list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
             ::_Const_iterator<1>::operator*(&local_c);
  } while (param_1->first < ppVar8->first);
  ppVar8 = std::
           list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
           ::_Const_iterator<1>::operator*(&local_c);
  if (ppVar8->first < param_1->first) {
    std::
    list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
    ::_Const_iterator<1>::operator++(&local_c);
LAB_004a43a2:
    std::
    list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
    ::_Const_iterator<1>::_Const_iterator<1>(&local_1c,(this->_List)._Myhead,this_00);
    bVar5 = std::
            list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
            ::_Const_iterator<1>::operator==((_Const_iterator<1> *)&param_2,&local_1c);
    if (bVar5) {
      _Var2._Ptr = (_Node *)local_c._padding_;
      _Var2._padding_ = (int)&local_1c;
      _Var10 = std::
               list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
               ::insert(this_00,_Var2,(pair<unsigned_int_const_,char_const_*> *)local_c._Ptr);
      param_2._0_4_ = *_Var10._0_4_;
      param_2._4_4_ = _Var10._0_4_[1];
    }
    else {
      _Var1._Ptr = local_c._Ptr;
      _Var1._padding_ = local_c._padding_;
      _Var4._Ptr = (_Node *)param_2._4_4_;
      _Var4._padding_ = param_2._0_4_;
      std::
      list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
      ::splice(this_00,_Var1,this_00,_Var4);
    }
    while( true ) {
      p_Var7 = std::
               vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>_>
               ::operator[](&this->_Vec,uVar6);
      std::
      list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
      ::_Const_iterator<1>::_Const_iterator<1>
                (&local_14,*(_Node **)&(p_Var7->_Mypos).field_0x4,this_00);
      bVar5 = std::
              list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
              ::_Const_iterator<1>::operator==(&local_c,&local_14);
      if (!bVar5) break;
      _Var10._4_4_ = param_2._4_4_;
      _Var10._0_4_ = param_2._0_4_;
      _List_position::_List_position((_List_position *)&local_1c,_Var10);
      p_Var7 = std::
               vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>_>
               ::operator[](&this->_Vec,uVar6);
      *(int *)&p_Var7->_Mypos = local_1c._padding_;
      *(_Node **)&(p_Var7->_Mypos).field_0x4 = local_1c._Ptr;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
    }
    fVar11 = load_factor(this);
    if (this->_Max_bucket_size < fVar11) {
      uVar6 = this->_Maxidx;
      iVar9 = 0;
      do {
        if (0xffffffe < uVar6) break;
        uVar6 = uVar6 * 2;
        iVar9 = iVar9 + 1;
      } while (iVar9 < 3);
      _Init(this,uVar6);
      _Reinsert(this);
    }
    *(undefined4 *)&__return_storage_ptr__->first = param_2._0_4_;
    __return_storage_ptr__->second = true;
  }
  else {
    std::
    list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
    ::_Const_iterator<1>::_Const_iterator<1>(&local_1c,(this->_List)._Myhead,this_00);
    bVar5 = std::
            list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
            ::_Const_iterator<1>::operator==((_Const_iterator<1> *)&param_2,&local_1c);
    if (!bVar5) {
      _Var3._Ptr = (_Node *)param_2._0_4_;
      _Var3._padding_ = (int)&local_1c;
      std::
      list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
      ::erase(this_00,_Var3);
    }
    *(int *)&__return_storage_ptr__->first = local_c._padding_;
    __return_storage_ptr__->second = false;
    param_2._4_4_ = local_c._Ptr;
  }
  *(undefined4 *)&(__return_storage_ptr__->first).field_0x4 = param_2._4_4_;
  return __return_storage_ptr__;
}
