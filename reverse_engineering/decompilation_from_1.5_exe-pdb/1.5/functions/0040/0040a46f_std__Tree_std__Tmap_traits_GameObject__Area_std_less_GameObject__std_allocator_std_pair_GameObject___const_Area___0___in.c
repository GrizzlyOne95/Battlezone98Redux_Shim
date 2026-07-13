/*
 * Entry: 0040a46f
 * Name: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::insert
 * Namespace: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
 * Signature: iterator insert(_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_> * this, const_iterator param_1, pair<GameObject_*_const,Area> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

iterator __thiscall
std::
_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
::insert(_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
         *this,const_iterator param_1,pair<GameObject_*_const,Area> *param_2)

{
  char cVar1;
  GameObject *pGVar2;
  bool bVar3;
  pair<std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::iterator,bool>
  *ppVar4;
  iterator iVar6;
  pair<GameObject_*_const,Area> *in_stack_00000010;
  _Node *p_Var7;
  _Node *p_Var8;
  pair<std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::iterator,bool>
  local_18;
  const_iterator local_c;
  undefined4 uVar5;
  
  if (this->_Mysize == 0) {
    iVar6 = _Insert(this,param_1._padding_._0_1_,(_Node *)0x1,
                    (pair<GameObject_*_const,Area> *)this->_Myhead);
    uVar5 = iVar6._4_4_;
    goto LAB_0040a5b8;
  }
  const_iterator::const_iterator(&local_c,this->_Myhead->_Left,this);
  bVar3 = const_iterator::operator==((const_iterator *)&param_1._Ptr,&local_c);
  if (bVar3) {
    if ((GameObject *)(param_2->second).x1 <= in_stack_00000010->first) goto LAB_0040a59c;
LAB_0040a58b:
    p_Var7 = (_Node *)0x1;
    p_Var8 = (_Node *)param_2;
  }
  else {
    const_iterator::const_iterator(&local_c,this->_Myhead,this);
    bVar3 = const_iterator::operator==((const_iterator *)&param_1._Ptr,&local_c);
    if (bVar3) {
      p_Var8 = this->_Myhead->_Right;
      if (in_stack_00000010->first <= (p_Var8->_Myval).first) goto LAB_0040a59c;
    }
    else {
      pGVar2 = (GameObject *)(param_2->second).x1;
      bVar3 = pGVar2 < in_stack_00000010->first;
      if (pGVar2 <= in_stack_00000010->first) {
LAB_0040a541:
        if (bVar3) {
          local_c._Ptr = (_Node *)param_2;
          local_c._padding_ = (int)param_1._Ptr;
          const_iterator::const_iterator
                    ((const_iterator *)&local_18.first.field_0x4,this->_Myhead,this);
          const_iterator::_Inc(&local_c);
          bVar3 = const_iterator::operator==(&local_c,(const_iterator *)&local_18.first.field_0x4);
          if ((bVar3) || (in_stack_00000010->first < ((local_c._Ptr)->_Myval).first)) {
            cVar1 = *(char *)((int)(param_2->second).z0 + 0x21);
            p_Var7 = local_c._Ptr;
            p_Var8 = (_Node *)param_2;
            goto joined_r0x0040a531;
          }
        }
LAB_0040a59c:
        ppVar4 = insert(this,&local_18,in_stack_00000010);
        uVar5 = *(undefined4 *)&ppVar4->first;
        *(undefined4 *)param_1._padding_ = uVar5;
        *(undefined4 *)(param_1._padding_ + 4) = *(undefined4 *)&(ppVar4->first).field_0x4;
        goto LAB_0040a5b8;
      }
      local_c._Ptr = (_Node *)param_2;
      local_c._padding_ = (int)param_1._Ptr;
      const_iterator::_Dec(&local_c);
      if (in_stack_00000010->first <= ((local_c._Ptr)->_Myval).first) {
        bVar3 = (GameObject *)(param_2->second).x1 < in_stack_00000010->first;
        goto LAB_0040a541;
      }
      cVar1 = (local_c._Ptr)->_Right->_Isnil;
      p_Var7 = (_Node *)param_2;
      p_Var8 = local_c._Ptr;
joined_r0x0040a531:
      param_2 = (pair<GameObject_*_const,Area> *)p_Var7;
      if (cVar1 == '\0') goto LAB_0040a58b;
    }
    p_Var7 = (_Node *)0x0;
  }
  iVar6 = _Insert(this,SUB41(param_1._padding_,0),p_Var7,(pair<GameObject_*_const,Area> *)p_Var8);
  uVar5 = iVar6._4_4_;
LAB_0040a5b8:
  iVar6._4_4_ = uVar5;
  iVar6._0_4_ = param_1._padding_;
  return iVar6;
}
