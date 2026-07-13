/*
 * Entry: 0051938d
 * Name: GetWorldExtents
 * Namespace: Global
 * Signature: void GetWorldExtents(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GetWorldExtents(void)

{
  AOI *pAVar1;
  AiPath *pAVar2;
  VECTOR_2D *pVVar3;
  bool bVar4;
  AOI **ppAVar5;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  VECTOR_2D *pVVar6;
  int iVar7;
  _Const_iterator<1> local_1c;
  _Const_iterator<1> local_14;
  _Node *local_c;
  _Node *local_8;
  
  aiGridX0 = GridMinX;
  aiGridZ0 = GridMinZ;
  aiGridX1 = GridMaxX;
  aiGridZ1 = GridMaxZ;
  std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_1c,(AOI::areas._Myhead)->_Next,&AOI::areas);
  while( true ) {
    std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,AOI::areas._Myhead,&AOI::areas);
    bVar4 = std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator==
                      (&local_1c,&local_14);
    if (bVar4) {
      return;
    }
    ppAVar5 = std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator*(&local_1c);
    pAVar1 = *ppAVar5;
    if ((pAVar1->interesting == false) && (pAVar1->inside == false)) break;
    std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator++(&local_1c);
  }
  pAVar2 = pAVar1->path;
  if (pAVar2 == (AiPath *)0x0) {
    return;
  }
  local_14._Ptr = (_Node *)pAVar2->points->x;
  local_1c._Ptr = (_Node *)pAVar2->points->z;
  local_c = local_1c._Ptr;
  local_8 = local_14._Ptr;
  if (1 < pAVar2->pointCount) {
    iVar7 = pAVar2->pointCount + -1;
    pVVar3 = pAVar2->points;
    do {
      pVVar6 = pVVar3 + 1;
      local_8 = (_Node *)Min((float)local_8,pVVar6->x);
      local_c = (_Node *)Min((float)local_c,pVVar3[1].z);
      local_14._Ptr = (_Node *)Max((float)local_14._Ptr,pVVar6->x);
      local_1c._Ptr = (_Node *)Max((float)local_1c._Ptr,pVVar3[1].z);
      iVar7 = iVar7 + -1;
      pVVar3 = pVVar6;
    } while (iVar7 != 0);
  }
  floor((double)((float)local_8 * 0.1));
  _ftol2_sse();
  if (aiGridX0 < extraout_EAX) {
    aiGridX0 = extraout_EAX;
  }
  floor((double)((float)local_c * 0.1));
  _ftol2_sse();
  if (aiGridZ0 < extraout_EAX_00) {
    aiGridZ0 = extraout_EAX_00;
  }
  ceil((double)((float)local_14._Ptr * 0.1));
  _ftol2_sse();
  if (extraout_EAX_01 < aiGridX1) {
    aiGridX1 = extraout_EAX_01;
  }
  ceil((double)((float)local_1c._Ptr * 0.1));
  _ftol2_sse();
  if (extraout_EAX_02 < aiGridZ1) {
    aiGridZ1 = extraout_EAX_02;
  }
  aiGridZ1 = ((int)(aiGridZ1 + 7 + (aiGridZ1 + 7 >> 0x1f & 7U)) >> 3) << 3;
  aiGridX1 = ((int)(aiGridX1 + 7 + (aiGridX1 + 7 >> 0x1f & 7U)) >> 3) << 3;
  aiGridZ0 = ((int)(aiGridZ0 + (aiGridZ0 >> 0x1f & 7U)) >> 3) << 3;
  aiGridX0 = ((int)(aiGridX0 + (aiGridX0 >> 0x1f & 7U)) >> 3) << 3;
  return;
}
