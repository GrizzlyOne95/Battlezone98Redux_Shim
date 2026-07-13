/*
 * Entry: 004998f6
 * Name: GameObjectClass::Find
 * Namespace: GameObjectClass
 * Signature: GameObjectClass * Find(long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

GameObjectClass * __cdecl GameObjectClass::Find(long64 param_1)

{
  char *_Str1;
  bool bVar1;
  int iVar2;
  GameObjectClass *pGVar3;
  vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *pvVar4;
  GameObjectClass **ppGVar5;
  ParameterDB local_3c;
  _Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> local_38;
  _Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> local_30;
  char local_28 [16];
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  param_1 = param_1 & 0x7f7f7f7f7f7f7f7f;
  pGVar3 = (GameObjectClass *)0x0;
  if (param_1 != 0) {
    std::_Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::
    _Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
              (&local_30,classList._Myfirst,(_Container_base_aux *)&classList);
    local_38._padding_ = local_30._padding_;
    local_38._Myptr = local_30._Myptr;
    while( true ) {
      std::_Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::
      _Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
                (&local_30,classList._Mylast,(_Container_base_aux *)&classList);
      bVar1 = std::_Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::
              operator==(&local_38,&local_30);
      if (bVar1) break;
      ppGVar5 = std::_Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::
                operator*(&local_38);
      pGVar3 = *ppGVar5;
      if (((int)pGVar3->cfg == (int)param_1) && (*(int *)((int)&pGVar3->cfg + 4) == param_1._4_4_))
      {
        return pGVar3;
      }
      std::_Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::operator++
                (&local_38);
    }
    sprintf(local_18,"%.8s.odf",&param_1);
    iVar2 = ItemExists(local_18);
    if (iVar2 == 0) {
      TraceError("GameObject \"%s\" not found\n");
      pGVar3 = (GameObjectClass *)0x0;
    }
    else {
      ParameterDB::ParameterDB(&local_3c,local_18);
      ParameterDB::Get(&local_3c,0xd3dd9cec,0x92d04727,local_28,0x10,(char *)0x0);
      pvVar4 = GetProtoList();
      std::_Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::
      _Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
                (&local_30,pvVar4->_Myfirst,(_Container_base_aux *)pvVar4);
      local_38._padding_ = local_30._padding_;
      local_38._Myptr = local_30._Myptr;
      while( true ) {
        pvVar4 = GetProtoList();
        std::_Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::
        _Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
                  (&local_30,pvVar4->_Mylast,(_Container_base_aux *)pvVar4);
        bVar1 = std::_Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::
                operator==(&local_38,&local_30);
        if (bVar1) break;
        ppGVar5 = std::_Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
                  ::operator*(&local_38);
        pGVar3 = *ppGVar5;
        _Str1 = pGVar3->label;
        if (_Str1 != (char *)0x0) {
          iVar2 = _stricmp(_Str1,local_28);
          if (iVar2 == 0) {
            pGVar3 = (GameObjectClass *)(**(code **)(pGVar3->_padding_ + 8))(param_1);
            goto LAB_00499a79;
          }
        }
        std::_Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::
        operator++(&local_38);
      }
      TraceError("GameObject \"%s\" uses unknown class label \"%s\"\n");
      pGVar3 = (GameObjectClass *)0x0;
LAB_00499a79:
      ParameterDB::~ParameterDB(&local_3c);
    }
  }
  return pGVar3;
}
