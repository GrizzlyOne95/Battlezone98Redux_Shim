/*
 * Entry: 0040b5cc
 * Name: AOI::DoRecalc
 * Namespace: AOI
 * Signature: void DoRecalc(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AOI::DoRecalc(void)

{
  AOI *pAVar1;
  bool bVar2;
  AOI **ppAVar3;
  double *unaff_EBX;
  int iVar4;
  double *unaff_ESI;
  int **unaff_EDI;
  undefined8 local_7c;
  undefined1 local_74 [32];
  undefined1 local_54 [24];
  _Const_iterator<1> local_3c;
  _Const_iterator<1> local_34;
  _Const_iterator<1> local_2c;
  _Const_iterator<1> local_24;
  _Const_iterator<1> local_1c;
  int **local_14;
  int **local_10;
  int **local_c;
  int local_8;
  
  local_8 = 0;
  do {
    iVar4 = local_8;
    if (hasArea[local_8] != false) {
      local_14 = values[1] + local_8;
      local_10 = values[0] + local_8;
      local_c = forces + local_8;
      InitGrid(unaff_EDI);
      InitGrid(unaff_EDI);
      InitGrid(unaff_EDI);
      std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::_Const_iterator<1>
                (&local_34,(areas._Myhead)->_Next,&areas);
      local_1c._padding_ = local_34._padding_;
      local_1c._Ptr = local_34._Ptr;
      while( true ) {
        std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::_Const_iterator<1>
                  (&local_24,areas._Myhead,&areas);
        bVar2 = std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator==
                          (&local_1c,&local_24);
        if (bVar2) break;
        ppAVar3 = std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator*(&local_1c);
        pAVar1 = *ppAVar3;
        if ((pAVar1->team == iVar4) && (pAVar1->interesting != false)) {
          Extents((AiPath *)local_54,(double *)(local_54 + 8),(double *)unaff_EDI,unaff_ESI,
                  unaff_EBX);
          FindRects(pAVar1->inside,(double)CONCAT44((char *)local_54._0_8_,SUB84(local_74._24_8_,4))
                    ,(double)CONCAT44((VECTOR_2D *)local_54._8_8_,SUB84(local_54._0_8_,4)),
                    (double)CONCAT44((PathType)local_54._16_8_,SUB84(local_54._8_8_,4)),
                    (double)CONCAT44(unaff_EDI,SUB84(local_54._16_8_,4)));
          FillRects(*local_10,pAVar1->value);
          FillRects(*local_c,pAVar1->force);
          iVar4 = local_8;
        }
        std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator++(&local_1c);
      }
      std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::_Const_iterator<1>
                (&local_3c,(areas._Myhead)->_Next,&areas);
      local_1c._padding_ = local_3c._padding_;
      local_1c._Ptr = local_3c._Ptr;
      while( true ) {
        std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::_Const_iterator<1>
                  (&local_2c,areas._Myhead,&areas);
        bVar2 = std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator==
                          (&local_1c,&local_2c);
        if (bVar2) break;
        ppAVar3 = std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator*(&local_1c);
        pAVar1 = *ppAVar3;
        if ((pAVar1->team == iVar4) && (pAVar1->interesting == false)) {
          Extents((AiPath *)local_74,(double *)(local_74 + 8),(double *)unaff_EDI,unaff_ESI,
                  unaff_EBX);
          FindRects(pAVar1->inside,
                    (double)CONCAT44((char *)local_74._0_8_,(int)((ulonglong)local_7c >> 0x20)),
                    (double)CONCAT44((VECTOR_2D *)local_74._8_8_,SUB84(local_74._0_8_,4)),
                    (double)CONCAT44((PathType)local_74._16_8_,SUB84(local_74._8_8_,4)),
                    (double)CONCAT44(unaff_EDI,SUB84(local_74._16_8_,4)));
          FillRects(*local_14,pAVar1->value);
          iVar4 = local_8;
        }
        std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator++(&local_1c);
      }
    }
    local_8 = iVar4 + 1;
  } while (local_8 < 0x10);
  recalc = false;
  return;
}
