/*
 * Entry: 004cfd9c
 * Name: PostLoadJChar
 * Namespace: Global
 * Signature: void PostLoadJChar(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl PostLoadJChar(void)

{
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar1;
  undefined4 *puVar2;
  bool bVar3;
  int iVar4;
  GameObject **ppGVar5;
  char *pcVar6;
  long lVar7;
  char *pcVar8;
  undefined4 *puVar9;
  int local_2c;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_28;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_20;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar4 = IsJapanese();
  pvVar1 = GameObject::objectList;
  if ((iVar4 != 0) &&
     (GameObject::objectList != (vector<GameObject_*,std::allocator<GameObject_*>_> *)0x0)) {
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_20,GameObject::objectList->_Myfirst,
               (_Container_base_aux *)GameObject::objectList);
    local_28._padding_ = local_20._padding_;
    local_28._Myptr = local_20._Myptr;
    while( true ) {
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
      _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                (&local_20,pvVar1->_Mylast,(_Container_base_aux *)pvVar1);
      bVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                        (&local_28,&local_20);
      if (bVar3) break;
      ppGVar5 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                          (&local_28);
      iVar4 = (**(code **)(*ppGVar5)->_padding_)();
      MapJChars(*(char **)(iVar4 + 0x14c));
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_28)
      ;
    }
    strncpy(local_18,&msn_filename,6);
    puVar2 = (undefined4 *)((int)&local_20._Myptr + 3);
    do {
      puVar9 = puVar2;
      puVar2 = (undefined4 *)((int)puVar9 + 1);
    } while (*(char *)((int)puVar9 + 1) != '\0');
    local_2c = 0;
    *(undefined4 *)((int)puVar9 + 1) = 0x746f2e2a;
    *(undefined2 *)((int)puVar9 + 5) = 0x66;
    pcVar6 = zixMatchWild(local_18,&local_2c);
    while (pcVar6 != (char *)0x0) {
      lVar7 = GetItemSize(pcVar6);
      if (0 < lVar7) {
        pcVar8 = UseItem(pcVar6);
        MapJChars(pcVar8);
        UnlockItem(pcVar6);
      }
      pcVar6 = zixMatchWild(local_18,&local_2c);
    }
  }
  return;
}
