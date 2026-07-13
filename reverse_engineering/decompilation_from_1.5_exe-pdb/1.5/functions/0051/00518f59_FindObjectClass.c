/*
 * Entry: 00518f59
 * Name: FindObjectClass
 * Namespace: Global
 * Signature: bool FindObjectClass(GameObjectClass * param_1, GameObjectClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl FindObjectClass(GameObjectClass *param_1,GameObjectClass *param_2)

{
  ObjectClassInfo *pOVar1;
  bool bVar2;
  ObjectClassInfo **ppOVar3;
  vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *pvVar4;
  GameObjectClass *unaff_EDI;
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> local_14;
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> local_c;
  
  bVar2 = IsBuilding(unaff_EDI);
  pvVar4 = &buildingClassList;
  if (!bVar2) {
    pvVar4 = &vehicleClassList;
  }
  std::_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
            (&local_14,pvVar4->_Myfirst,(_Container_base_aux *)pvVar4);
  local_c._padding_ = local_14._padding_;
  local_c._Myptr = local_14._Myptr;
  while( true ) {
    std::_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
    _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
              (&local_14,pvVar4->_Mylast,(_Container_base_aux *)pvVar4);
    bVar2 = std::_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
            operator==(&local_c,&local_14);
    if (bVar2) {
      return false;
    }
    ppOVar3 = std::_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
              operator*(&local_c);
    pOVar1 = *ppOVar3;
    if (pOVar1->objClass == unaff_EDI) break;
    std::_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator++
              (&local_c);
  }
  if (pOVar1->buildClass == (GameObjectClass *)0x0) {
    pOVar1->buildClass = param_1;
  }
  return true;
}
