/*
 * Entry: 0040b9be
 * Name: AOI::~AOI
 * Namespace: AOI
 * Signature: void ~AOI(AOI * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AOI::~AOI(AOI *this)

{
  int iVar1;
  _Node *p_Var2;
  bool bVar3;
  AOI **ppAVar4;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  iVar1 = this->team;
  local_c._Ptr = (_Node *)this;
  std::list<AOI_*,std::allocator<AOI_*>_>::remove(&areas,(AOI **)&local_c._Ptr);
  p_Var2 = areas._Myhead;
  hasArea[iVar1] = false;
  std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_c,p_Var2->_Next,&areas);
  while( true ) {
    std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,areas._Myhead,&areas);
    bVar3 = std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
    if (bVar3) {
      return;
    }
    ppAVar4 = std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator*(&local_c);
    if ((*ppAVar4)->team == iVar1) break;
    std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator++(&local_c);
  }
  hasArea[iVar1] = true;
  return;
}
