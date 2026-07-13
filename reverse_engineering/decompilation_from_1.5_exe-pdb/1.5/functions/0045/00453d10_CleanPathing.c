/*
 * Entry: 00453d10
 * Name: CleanPathing
 * Namespace: Global
 * Signature: void CleanPathing(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CleanPathing(void)

{
  Strip ***pppSVar1;
  Strip ***pppSVar2;
  Strip **ppSVar3;
  void *pvVar4;
  _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> _Var5;
  _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> _Var6;
  _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> _Var7;
  _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> _Var8;
  vector<Strip_*,std::allocator<Strip_*>_> *pvVar9;
  Strip **local_c;
  Strip **local_8 [2];
  
  DeleteAllStrips();
  BlockedCellClean();
  pvVar9 = freeStrips;
  StripCount = 0;
  stripSeqNo = 0;
  sBuiltZoneWidth = 0;
  sBuiltZoneHeight = 0;
  sBuiltZoneMax2D = 0;
  curFindPath = (PathPlan *)0x0;
  startStrip = (Strip *)0x0;
  goalStrip = (Strip *)0x0;
  cellWidth = 0;
  cellHeight = 0;
  zoneWidth = 0;
  zoneHeight = 0;
  zones = (PathZone *)0x0;
  pathMem = 0;
  randomizeCost = false;
  ContainerNeighbor::firstFree = -1;
  ContainerNeighbor::neighbors = (ContainerNeighbor *)0x0;
  ContainerNeighbor::maxNeighbors = 0;
  if (freeStrips != (vector<Strip_*,std::allocator<Strip_*>_> *)0x0) {
    local_c = freeStrips->_Mylast;
    pppSVar1 = &freeStrips->_Mylast;
    pppSVar2 = &freeStrips->_Myfirst;
    if (local_c < *pppSVar2) {
      _invalid_parameter_noinfo();
    }
    ppSVar3 = *pppSVar2;
    local_8[0] = (Strip **)pvVar9->_padding_;
    if (*pppSVar1 < ppSVar3) {
      _invalid_parameter_noinfo();
    }
    _Var6._Myptr = (Strip **)pvVar9->_padding_;
    _Var6._padding_ = (int)local_8;
    _Var8._Myptr = local_8[0];
    _Var8._padding_ = (int)ppSVar3;
    std::vector<Strip_*,std::allocator<Strip_*>_>::erase(pvVar9,_Var6,_Var8);
  }
  pvVar9 = usedStrips;
  if (usedStrips != (vector<Strip_*,std::allocator<Strip_*>_> *)0x0) {
    pppSVar1 = &usedStrips->_Mylast;
    pppSVar2 = &usedStrips->_Myfirst;
    if (usedStrips->_Mylast < *pppSVar2) {
      _invalid_parameter_noinfo();
    }
    ppSVar3 = *pppSVar2;
    local_c = (Strip **)pvVar9->_padding_;
    if (*pppSVar1 < ppSVar3) {
      _invalid_parameter_noinfo();
    }
    _Var5._Myptr = (Strip **)pvVar9->_padding_;
    _Var5._padding_ = (int)&local_c;
    _Var7._Myptr = local_c;
    _Var7._padding_ = (int)ppSVar3;
    std::vector<Strip_*,std::allocator<Strip_*>_>::erase(pvVar9,_Var5,_Var7);
  }
  materialCost[0] = 0.0;
  materialCost[1] = 0.0;
  materialCost[2] = 0.0;
  materialCost[3] = 0.0;
  materialCost[4] = 0.0;
  materialCost[5] = 0.0;
  materialCost[6] = 0.0;
  curPathingType = -1;
  curPathingTeam = -1;
  curPathingEnemies = 0;
  Search::path = (PathPlan *)0x0;
  longSearch = 0;
  startNode = (Strip *)0x0;
  goalNode = (Strip *)0x0;
  curNode = (Strip *)0x0;
  NodeNeighbor::count = 0;
  NodeNeighbor::curNode = (Strip *)0x0;
  if (NodeNeighbor::neighbors.array != (NodeNeighbor *)0x0) {
    operator_delete__(NodeNeighbor::neighbors.array);
  }
  pvVar9 = freeStrips;
  NodeNeighbor::neighbors.array = (NodeNeighbor *)0x0;
  NodeNeighbor::neighbors.size = 0;
  lastIntNode = (Strip *)0x0;
  lastIntNextNode = (Strip *)0x0;
  compareStart.x = 0.0;
  compareStart.z = 0.0;
  maxStrips = 0;
  getStrips = (Strip **)0x0;
  stripList = (tagSTRIP *)0x0;
  stripListSize = 0;
  stripListMax = 0;
  xSlabSize = 0;
  xSlab = (int *)0x0;
  xSlabMax = 0;
  rClip = false;
  bClip = false;
  if (freeStrips != (vector<Strip_*,std::allocator<Strip_*>_> *)0x0) {
    pppSVar1 = &freeStrips->_Myfirst;
    if (freeStrips->_Myfirst != (Strip **)0x0) {
      operator_delete(freeStrips->_Myfirst);
    }
    pvVar4 = (void *)pvVar9->_padding_;
    *pppSVar1 = (Strip **)0x0;
    pvVar9->_Mylast = (Strip **)0x0;
    pvVar9->_Myend = (Strip **)0x0;
    operator_delete(pvVar4);
    operator_delete(pvVar9);
  }
  pvVar9 = usedStrips;
  freeStrips = (vector<Strip_*,std::allocator<Strip_*>_> *)0x0;
  if (usedStrips != (vector<Strip_*,std::allocator<Strip_*>_> *)0x0) {
    pppSVar1 = &usedStrips->_Myfirst;
    if (usedStrips->_Myfirst != (Strip **)0x0) {
      operator_delete(usedStrips->_Myfirst);
    }
    pvVar4 = (void *)pvVar9->_padding_;
    *pppSVar1 = (Strip **)0x0;
    pvVar9->_Mylast = (Strip **)0x0;
    pvVar9->_Myend = (Strip **)0x0;
    operator_delete(pvVar4);
    operator_delete(pvVar9);
  }
  usedStrips = (vector<Strip_*,std::allocator<Strip_*>_> *)0x0;
  return;
}
