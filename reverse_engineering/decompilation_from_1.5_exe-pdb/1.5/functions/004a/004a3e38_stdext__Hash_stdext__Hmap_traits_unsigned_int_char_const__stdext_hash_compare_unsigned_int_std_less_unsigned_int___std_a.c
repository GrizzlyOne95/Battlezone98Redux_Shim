/*
 * Entry: 004a3e38
 * Name: stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_Copy
 * Namespace: stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>
 * Signature: void _Copy(_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_> * this, _Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
stdext::
_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>
::_Copy(_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>
        *this,_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>
              *param_1)

{
  list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
  *this_00;
  list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
  *plVar1;
  _List_position *p_Var2;
  _Const_iterator<1> _Var3;
  _Iterator<1> _Var4;
  _Const_iterator<1> _Var5;
  _List_position _Var6;
  _Const_iterator<1> _Var7;
  _Iterator<1> _Var8;
  _List_position *p_Var9;
  uint uVar10;
  vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>_>
  *pvVar11;
  vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>_>
  *pvVar12;
  _Const_iterator<1> local_24;
  _Const_iterator<1> local_1c;
  _Const_iterator<1> local_14;
  vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>_>
  *local_c;
  vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>_>
  *local_8;
  
  this_00 = &this->_List;
  std::
  list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
  ::_Const_iterator<1>::_Const_iterator<1>(&local_14,(this->_List)._Myhead,this_00);
  pvVar11 = &param_1->_Vec;
  p_Var9 = (param_1->_Vec)._Mylast;
  p_Var2 = (param_1->_Vec)._Myfirst;
  local_8 = &this->_Vec;
  _Var4._4_4_ = local_14._Ptr;
  _Var4._0_4_ = local_14._padding_;
  pvVar12 = pvVar11;
  local_c = pvVar11;
  _List_position::_List_position((_List_position *)&stack0xffffffc8,_Var4);
  _Var6._Mypos._4_4_ = pvVar12;
  _Var6._Mypos._0_4_ = pvVar11;
  std::
  vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>_>
  ::resize(local_8,(int)p_Var9 - (int)p_Var2 >> 3,_Var6);
  this->_Mask = param_1->_Mask;
  this->_Maxidx = param_1->_Maxidx;
  this->_Max_bucket_size = param_1->_Max_bucket_size;
  std::
  list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
  ::clear(this_00);
  std::
  list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
  ::_Const_iterator<1>::_Const_iterator<1>(&local_24,(this->_List)._Myhead,this_00);
  plVar1 = &param_1->_List;
  std::
  list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
  ::_Const_iterator<1>::_Const_iterator<1>(&local_14,(param_1->_List)._Myhead,plVar1);
  std::
  list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
  ::_Const_iterator<1>::_Const_iterator<1>(&local_1c,((param_1->_List)._Myhead)->_Next,plVar1);
  _Var3._Ptr = local_24._Ptr;
  _Var3._padding_ = local_24._padding_;
  _Var5._Ptr = local_1c._Ptr;
  _Var5._padding_ = local_1c._padding_;
  _Var7._Ptr = local_14._Ptr;
  _Var7._padding_ = local_14._padding_;
  std::
  list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
  ::
  insert<std::list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>::_Const_iterator<1>_>
            (this_00,_Var3,_Var5,_Var7);
  *(char *)&this->_padding_ = (char)param_1->_padding_;
  std::
  list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
  ::_Const_iterator<1>::_Const_iterator<1>(&local_14,((this->_List)._Myhead)->_Next,this_00);
  std::
  list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
  ::_Const_iterator<1>::_Const_iterator<1>(&local_1c,((param_1->_List)._Myhead)->_Next,plVar1);
  pvVar11 = local_8;
  uVar10 = 0;
  if ((int)local_8->_Mylast - (int)local_8->_Myfirst >> 3 != 0) {
    do {
      p_Var9 = std::
               vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>_>
               ::operator[](local_c,uVar10);
      if (*(_Node **)&(p_Var9->_Mypos).field_0x4 == local_1c._Ptr) {
        _Var8._4_4_ = local_14._Ptr;
        _Var8._0_4_ = local_14._padding_;
        _List_position::_List_position((_List_position *)&local_24,_Var8);
        p_Var9 = std::
                 vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>_>
                 ::operator[](pvVar11,uVar10);
        *(int *)&p_Var9->_Mypos = local_24._padding_;
        *(_Node **)&(p_Var9->_Mypos).field_0x4 = local_24._Ptr;
        uVar10 = uVar10 + 1;
      }
      else {
        std::
        list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
        ::_Const_iterator<1>::operator++(&local_14);
        std::
        list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
        ::_Const_iterator<1>::operator++(&local_1c);
      }
    } while (uVar10 < (uint)((int)pvVar11->_Mylast - (int)pvVar11->_Myfirst >> 3));
  }
  return;
}
