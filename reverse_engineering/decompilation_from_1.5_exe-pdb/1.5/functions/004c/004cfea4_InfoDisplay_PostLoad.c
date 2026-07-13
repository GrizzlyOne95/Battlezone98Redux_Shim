/*
 * Entry: 004cfea4
 * Name: InfoDisplay::PostLoad
 * Namespace: InfoDisplay
 * Signature: void PostLoad(InfoDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall InfoDisplay::PostLoad(InfoDisplay *this)

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
  int iStack_2c;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> _Stack_28;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> _Stack_20;
  char acStack_18 [16];
  uint uStack_8;
  
  uStack_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar4 = IsJapanese();
  pvVar1 = GameObject::objectList;
  if ((iVar4 != 0) &&
     (GameObject::objectList != (vector<GameObject_*,std::allocator<GameObject_*>_> *)0x0)) {
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&_Stack_20,GameObject::objectList->_Myfirst,
               (_Container_base_aux *)GameObject::objectList);
    _Stack_28._padding_ = _Stack_20._padding_;
    _Stack_28._Myptr = _Stack_20._Myptr;
    while( true ) {
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
      _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                (&_Stack_20,pvVar1->_Mylast,(_Container_base_aux *)pvVar1);
      bVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                        (&_Stack_28,&_Stack_20);
      if (bVar3) break;
      ppGVar5 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                          (&_Stack_28);
      iVar4 = (**(code **)(*ppGVar5)->_padding_)();
      MapJChars(*(char **)(iVar4 + 0x14c));
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++
                (&_Stack_28);
    }
    strncpy(acStack_18,&msn_filename,6);
    puVar2 = (undefined4 *)((int)&_Stack_20._Myptr + 3);
    do {
      puVar9 = puVar2;
      puVar2 = (undefined4 *)((int)puVar9 + 1);
    } while (*(char *)((int)puVar9 + 1) != '\0');
    iStack_2c = 0;
    *(undefined4 *)((int)puVar9 + 1) = 0x746f2e2a;
    *(undefined2 *)((int)puVar9 + 5) = 0x66;
    pcVar6 = zixMatchWild(acStack_18,&iStack_2c);
    while (pcVar6 != (char *)0x0) {
      lVar7 = GetItemSize(pcVar6);
      if (0 < lVar7) {
        pcVar8 = UseItem(pcVar6);
        MapJChars(pcVar8);
        UnlockItem(pcVar6);
      }
      pcVar6 = zixMatchWild(acStack_18,&iStack_2c);
    }
  }
  return;
}
