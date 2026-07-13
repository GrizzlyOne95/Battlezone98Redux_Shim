/*
 * Entry: 0051912e
 * Name: Units_Init
 * Namespace: Global
 * Signature: void Units_Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Units_Init(void)

{
  bool bVar1;
  tagUNITTYPE *ptVar2;
  ObjectClassInfo **ppOVar3;
  int unaff_ESI;
  uint uVar4;
  GameObjectClass *unaff_EDI;
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> local_14;
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> local_c;
  
  NRUNITTYPES = (int)vehicleClassList._Mylast - (int)vehicleClassList._Myfirst >> 2;
  uVar4 = 0;
  if (0 < NRUNITTYPES) {
    do {
      std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator[]
                (&vehicleClassList,uVar4);
      ptVar2 = Class2UnitType(unaff_EDI);
      ptVar2->unittypeid = uVar4;
      uVar4 = uVar4 + 1;
    } while ((int)uVar4 < NRUNITTYPES);
  }
  ptVar2 = Class2UnitType(unaff_EDI);
  defaultPrereqType = (int)(ptVar2->prereq).prereqtype;
  std::_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
            (&local_14,vehicleClassList._Myfirst,(_Container_base_aux *)&vehicleClassList);
  local_c._padding_ = local_14._padding_;
  local_c._Myptr = local_14._Myptr;
  while( true ) {
    std::_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
    _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
              (&local_14,vehicleClassList._Mylast,(_Container_base_aux *)&vehicleClassList);
    bVar1 = std::_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
            operator==(&local_c,&local_14);
    if (bVar1) break;
    ppOVar3 = std::_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
              operator*(&local_c);
    if ((*ppOVar3)->buildClass != (GameObjectClass *)0x0) {
      GetPrereq(unaff_EDI);
      SetMaker(unaff_EDI,unaff_ESI);
    }
    std::_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator++
              (&local_c);
  }
  std::_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
            (&local_14,buildingClassList._Myfirst,(_Container_base_aux *)&buildingClassList);
  local_c._padding_ = local_14._padding_;
  local_c._Myptr = local_14._Myptr;
  while( true ) {
    std::_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
    _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
              (&local_14,buildingClassList._Mylast,(_Container_base_aux *)&buildingClassList);
    bVar1 = std::_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
            operator==(&local_c,&local_14);
    if (bVar1) break;
    ppOVar3 = std::_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
              operator*(&local_c);
    if ((*ppOVar3)->buildClass != (GameObjectClass *)0x0) {
      GetPrereq(unaff_EDI);
      SetMaker(unaff_EDI,unaff_ESI);
    }
    std::_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator++
              (&local_c);
  }
  return;
}
