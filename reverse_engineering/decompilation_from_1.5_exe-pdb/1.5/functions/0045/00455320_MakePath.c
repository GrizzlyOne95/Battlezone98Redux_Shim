/*
 * Entry: 00455320
 * Name: MakePath
 * Namespace: Global
 * Signature: void MakePath(Strip * param_1, PathPlan * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl MakePath(Strip *param_1,PathPlan *param_2)

{
  float fVar1;
  float fVar2;
  _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> _Var3;
  _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> _Var4;
  Strip *pSVar5;
  float fVar6;
  Strip *pSVar7;
  Strip *pSVar8;
  float *pfVar9;
  PathPoint *pPVar10;
  Strip *pSVar11;
  int iVar12;
  Strip *pSVar13;
  vector<PathPoint,std::allocator<PathPoint>_> *this;
  uint uVar14;
  PathPoint *local_10 [4];
  
  param_2->flags = param_2->flags | 8;
  pSVar7 = goalNode;
  if (param_1->backward == false) {
    pSVar11 = param_1->next;
    pSVar8 = param_1->prev;
    while (pSVar13 = pSVar11, pSVar13 != pSVar7) {
      pSVar11 = pSVar13->prev;
      pSVar13->prev = pSVar8;
      fVar1 = pSVar8->x;
      fVar2 = pSVar13->x1 - 0.01;
      fVar6 = pSVar13->x0;
      if ((fVar1 < pSVar13->x0) || (fVar6 = fVar1, fVar1 <= fVar2)) {
        fVar2 = fVar6;
      }
      pSVar13->x = fVar2;
      fVar1 = pSVar8->z;
      fVar2 = pSVar13->z1 - 0.01;
      fVar6 = pSVar13->z0;
      if ((fVar1 < pSVar13->z0) || (fVar6 = fVar1, fVar1 <= fVar2)) {
        fVar2 = fVar6;
      }
      pSVar13->z = fVar2;
      pSVar8 = pSVar13;
    }
    Strip::operator=(param_1,pSVar13);
    param_1->link = true;
    param_1->seqNo = -1;
    fVar1 = pSVar8->x;
    fVar2 = pSVar13->x0;
    fVar6 = pSVar13->x1 - 0.01;
    if ((fVar1 < fVar2) || (fVar2 = fVar1, fVar1 <= fVar6)) {
      fVar6 = fVar2;
    }
    param_1->x = fVar6;
    fVar1 = pSVar8->z;
    fVar2 = pSVar13->z1;
    fVar6 = pSVar13->z0;
    if (pSVar13->z0 <= fVar1) {
LAB_0045554a:
      fVar2 = fVar2 - 0.01;
      fVar6 = fVar1;
      if (fVar2 < fVar1) goto LAB_004553fb;
    }
  }
  else {
    pSVar11 = param_1->prev;
    pSVar8 = param_1->next;
    while (pSVar13 = pSVar11, pSVar13 != pSVar7) {
      pSVar11 = pSVar13->prev;
      pSVar13->prev = pSVar8;
      fVar1 = pSVar8->x;
      fVar2 = pSVar13->x1 - 0.01;
      fVar6 = pSVar13->x0;
      if ((fVar1 < pSVar13->x0) || (fVar6 = fVar1, fVar1 <= fVar2)) {
        fVar2 = fVar6;
      }
      pSVar13->x = fVar2;
      fVar1 = pSVar8->z;
      fVar2 = pSVar13->z1 - 0.01;
      fVar6 = pSVar13->z0;
      if ((fVar1 < pSVar13->z0) || (fVar6 = fVar1, fVar1 <= fVar2)) {
        fVar2 = fVar6;
      }
      pSVar13->z = fVar2;
      pSVar8 = pSVar13;
    }
    Strip::operator=(param_1,pSVar13);
    param_1->link = true;
    param_1->seqNo = -1;
    fVar1 = pSVar8->x;
    fVar2 = pSVar13->x1 - 0.01;
    fVar6 = pSVar13->x0;
    if ((fVar1 < pSVar13->x0) || (fVar6 = fVar1, fVar1 <= fVar2)) {
      fVar2 = fVar6;
    }
    param_1->x = fVar2;
    fVar1 = pSVar8->z;
    fVar2 = pSVar13->z1;
    fVar6 = pSVar13->z0;
    if (pSVar13->z0 <= fVar1) goto LAB_0045554a;
  }
  fVar2 = fVar6;
LAB_004553fb:
  param_1->z = fVar2;
  pSVar13->prev = param_1;
  pSVar11 = startNode;
  param_1->prev = pSVar8;
  lastIntNode = (Strip *)0x0;
  while (pSVar8 = pSVar7->prev, pSVar8 != pSVar11) {
    pSVar13 = pSVar8->prev;
    curNode = pSVar8;
    MoveAwayFromCorner(pSVar13,pSVar8,pSVar7);
    pSVar5 = pSVar7;
    if (pSVar13 != pSVar11) {
      pSVar8 = MoveAwayFromEdge(pSVar13,pSVar8);
      pSVar11 = startNode;
    }
    for (; pSVar7 = pSVar8, pSVar5 != pSVar7; pSVar5 = pSVar5->prev) {
      pSVar8 = pSVar7;
    }
  }
  uVar14 = 1;
  for (curNode = goalNode; curNode != pSVar11; curNode = curNode->prev) {
    uVar14 = uVar14 + 1;
  }
  this = &param_2->points;
  if ((param_2->points)._Mylast < (param_2->points)._Myfirst) {
    _invalid_parameter_noinfo();
  }
  pPVar10 = (param_2->points)._Myfirst;
  local_10[0] = (PathPoint *)this->_padding_;
  if ((param_2->points)._Mylast < pPVar10) {
    _invalid_parameter_noinfo();
  }
  _Var3._Myptr = (PathPoint *)this->_padding_;
  _Var3._padding_ = (int)local_10;
  _Var4._Myptr = local_10[0];
  _Var4._padding_ = (int)pPVar10;
  std::vector<PathPoint,std::allocator<PathPoint>_>::erase(this,_Var3,_Var4);
  local_10[0] = (PathPoint *)0x0;
  std::vector<PathPoint,std::allocator<PathPoint>_>::resize(this,uVar14,(PathPoint)ZEXT816(0));
  curNode = goalNode;
  if (uVar14 != 0) {
    iVar12 = uVar14 << 4;
    do {
      uVar14 = uVar14 - 1;
      if ((uint)((int)(param_2->points)._Mylast - (int)(param_2->points)._Myfirst >> 4) <= uVar14) {
        _invalid_parameter_noinfo();
      }
      pfVar9 = (float *)((int)&(param_2->points)._Myfirst[-1].point.x + iVar12);
      *pfVar9 = curNode->x * Terrain.Grid_Size;
      pfVar9[1] = curNode->z * Terrain.Grid_Size;
      if (curNode->seqNo == -1) {
        pfVar9[2] = 0.0;
        pfVar9[3] = 0.0;
      }
      else {
        pfVar9[2] = (float)curNode;
        pfVar9[3] = (float)curNode->seqNo;
      }
      curNode = curNode->prev;
      iVar12 = iVar12 + -0x10;
    } while (uVar14 != 0);
  }
  param_1->neighbor = 0;
  param_1->edge = '\0';
  param_1->link = false;
  param_1->open = false;
  param_1->backward = false;
  pPVar10 = std::vector<PathPoint,std::allocator<PathPoint>_>::back(this);
  *(float *)&param_1->detour = (pPVar10->point).x;
  param_1->x = (pPVar10->point).z;
  return;
}
