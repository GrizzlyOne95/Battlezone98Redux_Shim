/*
 * Entry: 00518878
 * Name: Iterate_BuildNext
 * Namespace: Global
 * Signature: tagBUILDING * Iterate_BuildNext(tagITERATOR * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagBUILDING * __cdecl Iterate_BuildNext(tagITERATOR *param_1)

{
  int *piVar1;
  uint uVar2;
  GameObject *pGVar3;
  vector<GameObject_*,std::allocator<GameObject_*>_> *this;
  bool bVar4;
  GameObject **ppGVar5;
  int iVar6;
  GameObjectClass *pGVar7;
  tagBUILDING *ptVar8;
  
  this = GameObject::objectList;
  do {
    do {
      if ((uint)((int)this->_Mylast - (int)this->_Myfirst >> 2) <= (uint)param_1->junk[0]) {
        return (tagBUILDING *)0x0;
      }
      uVar2 = param_1->junk[0];
      param_1->junk[0] = uVar2 + 1;
      ppGVar5 = std::vector<GameObject_*,std::allocator<GameObject_*>_>::operator[](this,uVar2);
      pGVar3 = *ppGVar5;
      piVar1 = &pGVar3->_padding_;
      iVar6 = (**(code **)(*piVar1 + 0x2c))();
    } while (iVar6 == 0);
    pGVar7 = (GameObjectClass *)(**(code **)*piVar1)();
    bVar4 = IsBuilding(pGVar7);
  } while ((!bVar4) ||
          ((param_1->junk[2] != -1 &&
           (iVar6 = (**(code **)(*piVar1 + 4))(), param_1->junk[2] != iVar6))));
  ptVar8 = Obj2Build(pGVar3);
  return ptVar8;
}
