/*
 * Entry: 004556e0
 * Name: A_Star
 * Namespace: Global
 * Signature: void A_Star(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl A_Star(void)

{
  float fVar1;
  bool bVar2;
  PathPoint *pPVar3;
  PathPoint *pPVar4;
  float fVar5;
  float fVar6;
  bool bVar7;
  PathPlan *pPVar8;
  vector<Strip_*,std::allocator<Strip_*>_> *this;
  Strip *pSVar9;
  NodeNeighbor *pNVar10;
  Strip *pSVar11;
  Strip *pSVar12;
  int iVar13;
  PathPoint *pPVar14;
  int iVar15;
  Strip **ppSVar16;
  Strip *local_28;
  float local_24;
  Strip *local_20;
  int local_1c [2];
  Heap_Class<Strip_*,float> local_14;
  
  pPVar8 = Search::path;
  if ((int)(Search::path->points)._Mylast - (int)(Search::path->points)._Myfirst >> 4 == 0) {
    _invalid_parameter_noinfo();
  }
  pPVar3 = (pPVar8->points)._Myfirst;
  if ((uint)((int)(pPVar8->points)._Mylast - (int)pPVar3 >> 4) < 2) {
    _invalid_parameter_noinfo();
  }
  pSVar9 = startStrip;
  local_24 = (pPVar3->point).x;
  pPVar4 = (pPVar8->points)._Myfirst;
  local_20 = (Strip *)(pPVar3->point).z;
  local_28 = startStrip;
  std::vector<Strip_*,std::allocator<Strip_*>_>::push_back(usedStrips,&local_28);
  this = usedStrips;
  pSVar9->x = local_24;
  pSVar9->z = (float)local_20;
  pSVar12 = goalStrip;
  local_24 = pPVar4[1].point.x;
  startNode = pSVar9;
  local_28 = (Strip *)pPVar4[1].point.z;
  local_20 = goalStrip;
  std::vector<Strip_*,std::allocator<Strip_*>_>::push_back(this,&local_20);
  pSVar12->x = local_24;
  pSVar12->z = (float)local_28;
  goalNode = pSVar12;
  pSVar12->backward = true;
  local_14.Allocated = true;
  local_14.Pool = operator_new__(0x10008);
  (local_14.Pool)->Key = 0.0;
  pSVar9 = startNode;
  local_14.Max_Count = 0x2000;
  local_14.Count = 0;
  local_14._padding_ = (int)&StripHeap::_vftable_;
  pSVar12 = startNode;
  if (startNode->backward == false) {
    pSVar12 = goalNode;
  }
  fVar1 = pSVar12->x - startNode->x;
  fVar5 = pSVar12->z - startNode->z;
  startNode->visited = true;
  pSVar9->g = 0.0;
  Heap_Class<Strip_*,float>::Push(&local_14,pSVar9,-(SQRT(fVar1 * fVar1 + fVar5 * fVar5) + 0.0001));
  pSVar11 = goalNode;
  pSVar12 = startNode;
  pSVar9->open = true;
  if (pSVar11->backward == false) {
    pSVar12 = pSVar11;
  }
  fVar1 = pSVar12->x - pSVar11->x;
  fVar5 = pSVar12->z - pSVar11->z;
  pSVar11->visited = true;
  pSVar11->g = 0.0;
  Heap_Class<Strip_*,float>::Push(&local_14,pSVar11,-(SQRT(fVar5 * fVar5 + fVar1 * fVar1) + 0.0001))
  ;
  pSVar11->open = true;
  local_1c[0] = 1;
  local_1c[1] = 1;
  local_28 = (Strip *)0x1;
  while( true ) {
    if (local_14.Count == 0) {
      pSVar9 = (Strip *)0x0;
    }
    else {
      pSVar9 = local_14.Pool[1].Data;
      Heap_Class<Strip_*,float>::Pop(&local_14);
      pSVar9->open = false;
    }
    curNode = pSVar9;
    if (pSVar9 == (Strip *)0x0) goto LAB_00455ba5;
    local_1c[pSVar9->backward] = local_1c[pSVar9->backward] + -1;
    if (pSVar9->link != false) break;
    ExpandNode(pSVar9);
    iVar15 = (0 < NodeNeighbor::count) - 1;
    do {
      if (iVar15 < 0) break;
      pNVar10 = ExpandingArray<NodeNeighbor>::operator[](&NodeNeighbor::neighbors,iVar15);
      pSVar12 = curNode;
      bVar7 = randomizeCost;
      pSVar9 = pNVar10->node;
      fVar1 = materialCost[curNode->material & 0xff];
      if ((ushort)((ushort)((uint)curNode->material >> 0x10) & (ushort)_curPathingEnemies) != 0) {
        fVar1 = fVar1 + 2.0;
      }
      if (pSVar9 == (Strip *)0x0) {
        local_24 = 1e+30;
      }
      else {
        fVar5 = pSVar9->x - curNode->x;
        fVar6 = pSVar9->z - curNode->z;
        local_24 = SQRT(fVar6 * fVar6 + fVar5 * fVar5);
        if (randomizeCost != false) {
          Rand_Counter = Rand_Counter + 1U & 0xff;
          local_24 = Pseudo_Rand_Number[Rand_Counter] * local_24 * 0.2 + local_24;
        }
        local_24 = local_24 * fVar1;
      }
      local_24 = local_24 + curNode->g;
      pSVar9->prev = curNode;
      pSVar9->g = local_24;
      if (pSVar9->visited == false) {
        pSVar9->visited = true;
        if (pSVar9->link == false) {
          pSVar12 = startNode;
          if (pSVar9->backward == false) {
            pSVar12 = goalNode;
          }
          fVar1 = pSVar12->x - pSVar9->x;
          fVar5 = pSVar12->z - pSVar9->z;
          fVar1 = SQRT(fVar5 * fVar5 + fVar1 * fVar1) + 0.0001;
        }
        else {
          bVar2 = pSVar12->backward;
          pSVar12 = pSVar9->next;
          pSVar9->backward = bVar2;
          fVar1 = materialCost[pSVar9->material & 0xff];
          if ((ushort)((ushort)((uint)pSVar9->material >> 0x10) & (ushort)_curPathingEnemies) != 0)
          {
            fVar1 = fVar1 + 2.0;
          }
          if ((uint)((int)usedStrips->_Mylast - (int)usedStrips->_Myfirst >> 2) < longSearch) {
            if (pSVar12 == (Strip *)0x0) {
              fVar1 = fRam00000030 + 1e+30;
            }
            else {
              fVar5 = pSVar12->x - pSVar9->x;
              fVar6 = pSVar12->z - pSVar9->z;
              fVar5 = SQRT(fVar6 * fVar6 + fVar5 * fVar5);
              if (bVar7 != false) {
                Rand_Counter = Rand_Counter + 1U & 0xff;
                fVar5 = Pseudo_Rand_Number[Rand_Counter] * fVar5 * 0.2 + fVar5;
              }
              fVar1 = fVar5 * fVar1 + pSVar12->g;
            }
          }
          else {
            pSVar11 = startNode;
            if (bVar2 == false) {
              pSVar11 = goalNode;
            }
            fVar1 = pSVar11->x - pSVar9->x;
            fVar5 = pSVar11->z - pSVar9->z;
            fVar1 = SQRT(fVar5 * fVar5 + fVar1 * fVar1) + 0.0001 + pSVar12->g;
          }
        }
        local_1c[pSVar9->backward] = local_1c[pSVar9->backward] + 1;
        Heap_Class<Strip_*,float>::Push(&local_14,pSVar9,-(fVar1 + local_24));
LAB_00455b64:
        pSVar9->open = true;
      }
      else {
        pSVar12 = startNode;
        if (pSVar9->backward == false) {
          pSVar12 = goalNode;
        }
        fVar1 = pSVar12->x - pSVar9->x;
        fVar5 = pSVar12->z - pSVar9->z;
        local_20 = (Strip *)(SQRT(fVar5 * fVar5 + fVar1 * fVar1) + 0.0001);
        if (pSVar9->open == false) {
          Heap_Class<Strip_*,float>::Push(&local_14,pSVar9,-((float)local_20 + local_24));
          local_1c[pSVar9->backward] = local_1c[pSVar9->backward] + 1;
          goto LAB_00455b64;
        }
        iVar13 = 0;
        if (0 < local_14.Count) {
          ppSVar16 = &local_14.Pool[1].Data;
          do {
            if (*ppSVar16 == pSVar9) {
              if (-1 < iVar13) {
                Heap_Class<Strip_*,float>::Remove(&local_14,iVar13);
                Heap_Class<Strip_*,float>::Push(&local_14,pSVar9,-((float)local_20 + local_24));
                goto LAB_00455b64;
              }
              break;
            }
            iVar13 = iVar13 + 1;
            ppSVar16 = ppSVar16 + 2;
          } while (iVar13 < local_14.Count);
        }
      }
      iVar15 = iVar15 + 1;
    } while (iVar15 < NodeNeighbor::count);
    if (((local_1c[0] == 0) || (local_1c[1] == 0)) ||
       (local_28 = (Strip *)((int)&local_28->_padding_ + 1), 499999 < (int)local_28)) {
      curNode = (Strip *)0x0;
LAB_00455ba5:
      pPVar8->flags = 1;
      if ((int)(pPVar8->points)._Mylast - (int)(pPVar8->points)._Myfirst >> 4 == 0) {
        _invalid_parameter_noinfo();
      }
      pPVar3 = (pPVar8->points)._Myfirst;
      if ((uint)((int)(pPVar8->points)._Mylast - (int)pPVar3 >> 4) < 2) {
        _invalid_parameter_noinfo();
      }
      pPVar4 = (pPVar8->points)._Myfirst;
      pPVar14 = pPVar4 + 1;
      (pPVar3->point).x = (pPVar3->point).x * Terrain.Grid_Size;
      (pPVar3->point).z = (pPVar3->point).z * Terrain.Grid_Size;
      (pPVar14->point).x = (pPVar14->point).x * Terrain.Grid_Size;
      pPVar4[1].point.z = pPVar4[1].point.z * Terrain.Grid_Size;
      pPVar8->curPoint = 0;
      (pPVar8->goal).x = (pPVar14->point).x;
      (pPVar8->goal).z = pPVar4[1].point.z;
LAB_00455c21:
      if (local_14.Allocated == true) {
        operator_delete__(local_14.Pool);
      }
      return;
    }
  }
  MakePath(pSVar9,pPVar8);
  goto LAB_00455c21;
}
