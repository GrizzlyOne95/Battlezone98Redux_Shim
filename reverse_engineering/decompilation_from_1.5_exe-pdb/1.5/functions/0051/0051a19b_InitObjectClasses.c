/*
 * Entry: 0051a19b
 * Name: InitObjectClasses
 * Namespace: Global
 * Signature: void InitObjectClasses(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InitObjectClasses(void)

{
  char *pcVar1;
  bool bVar2;
  Craft **ppCVar3;
  GameObjectClass *pGVar4;
  char *pcVar5;
  uint uVar6;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_18;
  int local_10;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_c;
  
  local_10 = D3IniFlags;
  D3IniFlags = D3IniFlags & 0xffff7fff;
  uVar6 = 0;
  do {
    RecurseBuildItem(*(long64 *)((int)builders + uVar6));
    uVar6 = uVar6 + 8;
  } while (uVar6 < 0x10);
  std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
            (&local_c,Craft::craftList._Myfirst,(_Container_base_aux *)&Craft::craftList);
  local_18._padding_ = local_c._padding_;
  local_18._Myptr = local_c._Myptr;
  while( true ) {
    std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
    _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
              (&local_c,Craft::craftList._Mylast,(_Container_base_aux *)&Craft::craftList);
    bVar2 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator==
                      (&local_18,&local_c);
    if (bVar2) break;
    ppCVar3 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator*(&local_18);
    pGVar4 = (GameObjectClass *)(**(code **)(*ppCVar3)->_padding_)();
    if ((pGVar4->class_id == CLASS_ID_HELICOPTER) || (pGVar4->class_id == CLASS_ID_VEHICLE)) {
      AddObjectClass(pGVar4,(GameObjectClass *)0x0);
    }
    std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator++(&local_18);
  }
  defaultObjClass = GameObjectClass::Find(0x726d61637061);
  AddObjectClass(defaultObjClass,(GameObjectClass *)0x0);
  pcVar5 = strrchr(&msn_filename,0x2e);
  if (pcVar5 == (char *)0x0) {
    pcVar1 = &msn_filename;
    do {
      pcVar5 = pcVar1;
      pcVar1 = pcVar5 + 1;
    } while (*pcVar5 != '\0');
  }
  local_c._Myptr = (Craft **)(pcVar5 + -0xd42330);
  local_18._Myptr = (Craft **)0x0;
  local_18._padding_ = 0x5f62;
  ppCVar3 = (Craft **)0x6;
  if ((int)local_c._Myptr < 7) {
    ppCVar3 = local_c._Myptr;
  }
  strncpy((char *)((int)&local_18._padding_ + 2),&msn_filename,(size_t)ppCVar3);
  RecurseBuildItem(CONCAT44(local_18._Myptr,local_18._padding_));
  local_18._padding_ = 0;
  local_18._Myptr = (Craft **)0x0;
  ppCVar3 = local_c._Myptr;
  if (8 < (int)local_c._Myptr) {
    ppCVar3 = (Craft **)0x8;
  }
  strncpy((char *)&local_18,&msn_filename,(size_t)ppCVar3);
  RecurseBuildItem(CONCAT44(local_18._Myptr,local_18._padding_));
  D3IniFlags = local_10;
  return;
}
