/*
 * Entry: 00518cc3
 * Name: Iterate_UnitNext
 * Namespace: Global
 * Signature: tagUNIT * Iterate_UnitNext(tagITERATOR * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagUNIT * __cdecl Iterate_UnitNext(tagITERATOR *param_1)

{
  uint uVar1;
  GameObject *pGVar2;
  vector<GameObject_*,std::allocator<GameObject_*>_> *this;
  bool bVar3;
  GameObject **ppGVar4;
  int iVar5;
  tagUNIT *ptVar6;
  
  this = GameObject::objectList;
  do {
    if ((uint)((int)this->_Mylast - (int)this->_Myfirst >> 2) <= (uint)param_1->junk[0]) {
      return (tagUNIT *)0x0;
    }
    uVar1 = param_1->junk[0];
    param_1->junk[0] = uVar1 + 1;
    ppGVar4 = std::vector<GameObject_*,std::allocator<GameObject_*>_>::operator[](this,uVar1);
    pGVar2 = *ppGVar4;
    bVar3 = IsUnit(pGVar2);
  } while ((!bVar3) ||
          ((param_1->junk[2] != -1 &&
           (iVar5 = (**(code **)(pGVar2->_padding_ + 4))(), param_1->junk[2] != iVar5))));
  ptVar6 = Obj2Unit(pGVar2);
  return ptVar6;
}
