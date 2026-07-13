/*
 * Entry: 00409b98
 * Name: FindPlan
 * Namespace: Global
 * Signature: AiPath * FindPlan(float param_1, float param_2, float param_3, float param_4, int param_5, int param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiPath * __cdecl
FindPlan(float param_1,float param_2,float param_3,float param_4,int param_5,int param_6)

{
  VECTOR_2D **ppVVar1;
  PathPlan *pPVar2;
  AiPath *pAVar3;
  PathPoint *pPVar4;
  int iVar5;
  float *pfVar6;
  VECTOR_3D local_2c;
  VECTOR_3D local_20;
  _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> local_14;
  _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> local_c;
  
  local_2c.x = param_1;
  local_2c.y = 1000.0;
  local_2c.z = param_2;
  local_20.x = param_3;
  local_20.y = 1000.0;
  local_20.z = param_4;
  SetPathingType(param_5,param_6);
  pPVar2 = FindPath(&local_2c,&local_20);
  if ((pPVar2->flags & 1) == 0) {
    iVar5 = (int)(pPVar2->points)._Mylast - (int)(pPVar2->points)._Myfirst >> 4;
    pAVar3 = operator_new(0x1c);
    if (pAVar3 == (AiPath *)0x0) {
      param_1 = 0.0;
    }
    else {
      param_1 = (float)AiPath::AiPath(pAVar3,(char *)0x0,iVar5);
    }
    std::_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>::
    _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>
              (&local_c,(pPVar2->points)._Myfirst,(_Container_base_aux *)&pPVar2->points);
    pfVar6 = *(float **)((int)param_1 + 8);
    if (0 < iVar5) {
      do {
        local_14._padding_ = local_c._padding_;
        local_14._Myptr = local_c._Myptr;
        std::_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>::operator++(&local_c);
        pPVar4 = std::_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>::operator*
                           (&local_14);
        *pfVar6 = (pPVar4->point).x;
        pfVar6[1] = (pPVar4->point).z;
        pfVar6 = pfVar6 + 2;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    FreePath(pPVar2);
  }
  else {
    (**(code **)pPVar2->_padding_)(1);
    pAVar3 = operator_new(0x1c);
    if (pAVar3 == (AiPath *)0x0) {
      pAVar3 = (AiPath *)0x0;
    }
    else {
      pAVar3 = AiPath::AiPath(pAVar3,(char *)0x0,2);
    }
    ppVVar1 = &pAVar3->points;
    (*ppVVar1)->x = param_1;
    (*ppVVar1)->z = param_2;
    (*ppVVar1)[1].x = param_3;
    (*ppVVar1)[1].z = param_4;
    pAVar3->pathType = BAD_PATH;
    param_1 = (float)pAVar3;
  }
  return (AiPath *)param_1;
}
