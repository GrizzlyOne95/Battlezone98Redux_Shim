/*
 * Entry: 004532b0
 * Name: MakeLinkedNode
 * Namespace: Global
 * Signature: Strip * MakeLinkedNode(float param_1, float param_2, Strip * param_3, Strip * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

Strip * __cdecl MakeLinkedNode(float param_1,float param_2,Strip *param_3,Strip *param_4)

{
  float fVar1;
  Strip *pSVar2;
  Strip *unaff_ESI;
  Strip *unaff_EDI;
  
  pSVar2 = param_4;
  if (param_4->visited == false) {
    fVar1 = materialCost[param_4->material & 0xff];
    if ((ushort)((ushort)((uint)param_4->material >> 0x10) & (ushort)_curPathingEnemies) != 0) {
      fVar1 = fVar1 + 2.0;
    }
    if (fVar1 == 99999.0) {
      return (Strip *)0x0;
    }
    std::vector<Strip_*,std::allocator<Strip_*>_>::push_back(usedStrips,&param_4);
    pSVar2->x = param_1;
    pSVar2->z = param_2;
    if (param_3 != (Strip *)0x0) {
      pSVar2->backward = param_3->backward;
    }
  }
  else if (param_4->backward == param_3->backward) {
    pSVar2 = MakeBetterNode(param_1,param_2,unaff_EDI,unaff_ESI);
  }
  else {
    pSVar2 = MakeLinkNode(param_1,param_2,unaff_EDI,unaff_ESI);
  }
  if (pSVar2 != (Strip *)0x0) {
    NodeNeighbor::Link(param_3,pSVar2);
  }
  return pSVar2;
}
