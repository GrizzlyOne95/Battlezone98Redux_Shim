/*
 * Entry: 00451b30
 * Name: DrawPath
 * Namespace: Global
 * Signature: void DrawPath(PathPlan * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DrawPath(PathPlan *param_1)

{
  uint uVar1;
  Strip *pSVar2;
  PathPoint *pPVar3;
  PathPoint *pPVar4;
  PathPoint *pPVar5;
  vector<Strip_*,std::allocator<Strip_*>_> *pvVar6;
  Strip **ppSVar7;
  NodeNeighbor *pNVar8;
  Strip *pSVar9;
  int iVar10;
  uint uVar11;
  _Vector_iterator<Strip_*,std::allocator<Strip_*>_> _Var12;
  uint *puVar13;
  uint local_10;
  undefined8 local_c;
  
  pvVar6 = usedStrips;
  if ((param_1 != (PathPlan *)0x0) &&
     (1 < (uint)((int)(param_1->points)._Mylast - (int)(param_1->points)._Myfirst >> 4))) {
    uVar11 = param_1->flags;
    if ((uVar11 & 0x10) != 0) {
      DrawShortPath(param_1);
      return;
    }
    if ((uVar11 & 4) == 0) {
      local_c._4_4_ =
           (Strip **)(((int)(param_1->points)._Mylast - (int)(param_1->points)._Myfirst >> 4) + -1);
      if (0 < (int)local_c._4_4_) {
        iVar10 = 0;
        uVar11 = 0;
        do {
          uVar1 = uVar11 + 1;
          local_10 = uVar1;
          if ((uint)((int)(param_1->points)._Mylast - (int)(param_1->points)._Myfirst >> 4) <= uVar1
             ) {
            _invalid_parameter_noinfo();
          }
          pPVar3 = (param_1->points)._Myfirst;
          if ((uint)((int)(param_1->points)._Mylast - (int)pPVar3 >> 4) <= uVar1) {
            _invalid_parameter_noinfo();
          }
          pPVar4 = (param_1->points)._Myfirst;
          if ((uint)((int)(param_1->points)._Mylast - (int)pPVar4 >> 4) <= uVar11) {
            _invalid_parameter_noinfo();
          }
          pPVar5 = (param_1->points)._Myfirst;
          if ((uint)((int)(param_1->points)._Mylast - (int)pPVar5 >> 4) <= uVar11) {
            _invalid_parameter_noinfo();
          }
          WorldLine(*(float *)((int)&(((param_1->points)._Myfirst)->point).x + iVar10),
                    *(float *)((int)&(pPVar5->point).z + iVar10),
                    *(float *)((int)&pPVar4[1].point.x + iVar10),
                    *(float *)((int)&pPVar3[1].point.z + iVar10),0xffffff);
          iVar10 = iVar10 + 0x10;
          uVar11 = local_10;
        } while ((int)local_10 < (int)local_c._4_4_);
      }
    }
    else if ((uVar11 & 8) == 0) {
      puVar13 = &local_10;
      _Var12 = std::vector<Strip_*,std::allocator<Strip_*>_>::begin(usedStrips);
      local_c._0_4_ = *_Var12._0_4_;
      local_c._4_4_ = (Strip **)_Var12._0_4_[1];
      while( true ) {
        iVar10 = (int)local_c;
        ppSVar7 = pvVar6->_Mylast;
        if (ppSVar7 < pvVar6->_Myfirst) {
          _invalid_parameter_noinfo();
        }
        if ((iVar10 == 0) || (iVar10 != pvVar6->_padding_)) {
          _invalid_parameter_noinfo();
        }
        if (local_c._4_4_ == ppSVar7) break;
        ppSVar7 = std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>::operator*
                            ((_Vector_iterator<Strip_*,std::allocator<Strip_*>_> *)&local_c);
        pSVar9 = *ppSVar7;
        if (pSVar9->prev != (Strip *)0x0) {
          DrawLine(pSVar9->x,pSVar9->z,pSVar9->prev->x,pSVar9->prev->z,(long)puVar13);
        }
        if (pSVar9->next != (Strip *)0x0) {
          DrawLine(pSVar9->x,pSVar9->z,pSVar9->next->x,pSVar9->next->z,(long)puVar13);
        }
        iVar10 = (0 < NodeNeighbor::count) - 1;
        do {
          if (iVar10 < 0) break;
          pNVar8 = ExpandingArray<NodeNeighbor>::operator[](&NodeNeighbor::neighbors,iVar10);
          pSVar2 = pNVar8->node;
          if (pSVar2->prev == (Strip *)0x0) {
            WorldLine(Terrain.Grid_Size * pSVar9->x,pSVar9->z * Terrain.Grid_Size,
                      pSVar2->x * Terrain.Grid_Size,pSVar2->z * Terrain.Grid_Size,0xffff00);
          }
          iVar10 = iVar10 + 1;
        } while (iVar10 < NodeNeighbor::count);
        std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>::operator++
                  ((_Vector_iterator<Strip_*,std::allocator<Strip_*>_> *)&local_c);
      }
    }
    else {
      ppSVar7 = &goalNode->prev;
      pSVar9 = goalNode;
      if (goalNode->prev != (Strip *)0x0) {
        do {
          WorldLine(Terrain.Grid_Size * pSVar9->x,pSVar9->z * Terrain.Grid_Size,
                    (*ppSVar7)->x * Terrain.Grid_Size,(*ppSVar7)->z * Terrain.Grid_Size,0xffffff);
          pSVar9 = *ppSVar7;
          ppSVar7 = &pSVar9->prev;
        } while (*ppSVar7 != (Strip *)0x0);
        return;
      }
    }
  }
  return;
}
