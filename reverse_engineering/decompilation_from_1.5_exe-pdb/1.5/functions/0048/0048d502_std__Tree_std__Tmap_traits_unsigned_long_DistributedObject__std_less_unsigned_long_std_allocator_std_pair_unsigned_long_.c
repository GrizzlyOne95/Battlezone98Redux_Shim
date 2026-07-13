/*
 * Entry: 0048d502
 * Name: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::insert
 * Namespace: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
 * Signature: iterator insert(_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_> * this, const_iterator param_1, pair<unsigned_long_const_,DistributedObject_*> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

iterator __thiscall
std::
_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
::insert(_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
         *this,const_iterator param_1,pair<unsigned_long_const_,DistributedObject_*> *param_2)

{
  char cVar1;
  bool bVar2;
  pair<std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::iterator,bool>
  *ppVar3;
  iterator iVar5;
  pair<unsigned_long_const_,DistributedObject_*> *in_stack_00000010;
  _Node *p_Var6;
  _Node *p_Var7;
  pair<std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::iterator,bool>
  local_18;
  const_iterator local_c;
  undefined4 uVar4;
  
  if (this->_Mysize == 0) {
    iVar5 = _Insert(this,param_1._padding_._0_1_,(_Node *)0x1,
                    (pair<unsigned_long_const_,DistributedObject_*> *)this->_Myhead);
    uVar4 = iVar5._4_4_;
    goto LAB_0048d64b;
  }
  const_iterator::const_iterator(&local_c,this->_Myhead->_Left,this);
  bVar2 = const_iterator::operator==((const_iterator *)&param_1._Ptr,&local_c);
  if (bVar2) {
    if (param_2[1].second <= (DistributedObject *)in_stack_00000010->first) goto LAB_0048d62f;
LAB_0048d61e:
    p_Var6 = (_Node *)0x1;
    p_Var7 = (_Node *)param_2;
  }
  else {
    const_iterator::const_iterator(&local_c,this->_Myhead,this);
    bVar2 = const_iterator::operator==((const_iterator *)&param_1._Ptr,&local_c);
    if (bVar2) {
      p_Var7 = this->_Myhead->_Right;
      if (in_stack_00000010->first <= (p_Var7->_Myval).first) goto LAB_0048d62f;
    }
    else {
      bVar2 = param_2[1].second < (DistributedObject *)in_stack_00000010->first;
      if (param_2[1].second <= (DistributedObject *)in_stack_00000010->first) {
LAB_0048d5d4:
        if (bVar2) {
          local_c._Ptr = (_Node *)param_2;
          local_c._padding_ = (int)param_1._Ptr;
          const_iterator::const_iterator
                    ((const_iterator *)&local_18.first.field_0x4,this->_Myhead,this);
          const_iterator::_Inc(&local_c);
          bVar2 = const_iterator::operator==(&local_c,(const_iterator *)&local_18.first.field_0x4);
          if ((bVar2) || (in_stack_00000010->first < ((local_c._Ptr)->_Myval).first)) {
            cVar1 = *(char *)(param_2[1].first + 0x15);
            p_Var6 = local_c._Ptr;
            p_Var7 = (_Node *)param_2;
            goto joined_r0x0048d5c4;
          }
        }
LAB_0048d62f:
        ppVar3 = insert(this,&local_18,in_stack_00000010);
        uVar4 = *(undefined4 *)&ppVar3->first;
        *(undefined4 *)param_1._padding_ = uVar4;
        *(undefined4 *)(param_1._padding_ + 4) = *(undefined4 *)&(ppVar3->first).field_0x4;
        goto LAB_0048d64b;
      }
      local_c._Ptr = (_Node *)param_2;
      local_c._padding_ = (int)param_1._Ptr;
      const_iterator::_Dec(&local_c);
      if ((DistributedObject *)in_stack_00000010->first <=
          (DistributedObject *)((local_c._Ptr)->_Myval).first) {
        bVar2 = param_2[1].second < (DistributedObject *)in_stack_00000010->first;
        goto LAB_0048d5d4;
      }
      cVar1 = (local_c._Ptr)->_Right->_Isnil;
      p_Var6 = (_Node *)param_2;
      p_Var7 = local_c._Ptr;
joined_r0x0048d5c4:
      param_2 = (pair<unsigned_long_const_,DistributedObject_*> *)p_Var6;
      if (cVar1 == '\0') goto LAB_0048d61e;
    }
    p_Var6 = (_Node *)0x0;
  }
  iVar5 = _Insert(this,SUB41(param_1._padding_,0),p_Var6,
                  (pair<unsigned_long_const_,DistributedObject_*> *)p_Var7);
  uVar4 = iVar5._4_4_;
LAB_0048d64b:
  iVar5._4_4_ = uVar4;
  iVar5._0_4_ = param_1._padding_;
  return iVar5;
}
