/*
 * Entry: 0052ef00
 * Name: ExplosionClass::Find
 * Namespace: ExplosionClass
 * Signature: ExplosionClass * Find(long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ExplosionClass * __cdecl ExplosionClass::Find(long64 param_1)

{
  undefined4 *puVar1;
  bool bVar2;
  int iVar3;
  ExplosionClass *pEVar4;
  vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *pvVar5;
  ExplosionClass **ppEVar6;
  undefined4 *puVar7;
  ParameterDB local_3c;
  _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> local_38;
  _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> local_30;
  char local_28 [15];
  undefined4 uStack_19;
  undefined1 auStack_14 [4];
  undefined1 local_10;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  param_1 = param_1 & 0x7f7f7f7f7f7f7f7f;
  pEVar4 = (ExplosionClass *)0x0;
  if (param_1 != 0) {
    std::_Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::
    _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
              (&local_30,classList._Myfirst,(_Container_base_aux *)&classList);
    local_38._padding_ = local_30._padding_;
    local_38._Myptr = local_30._Myptr;
    while( true ) {
      std::_Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::
      _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
                (&local_30,classList._Mylast,(_Container_base_aux *)&classList);
      bVar2 = std::_Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::
              operator==(&local_38,&local_30);
      if (bVar2) break;
      ppEVar6 = std::_Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::
                operator*(&local_38);
      if (((int)(*ppEVar6)->cfg == (int)param_1) &&
         (*(int *)((int)&(*ppEVar6)->cfg + 4) == param_1._4_4_)) {
        ppEVar6 = std::_Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::
                  operator*(&local_38);
        return *ppEVar6;
      }
      std::_Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::operator++
                (&local_38);
    }
    strncpy((char *)((int)&uStack_19 + 1),(char *)&param_1,8);
    local_10 = 0;
    puVar1 = &uStack_19;
    do {
      puVar7 = puVar1;
      puVar1 = (undefined4 *)((int)puVar7 + 1);
    } while (*(char *)((int)puVar7 + 1) != '\0');
    *(undefined4 *)((int)puVar7 + 1) = 0x66646f2e;
    *(undefined1 *)((int)puVar7 + 5) = 0;
    iVar3 = ItemExists((char *)((int)&uStack_19 + 1));
    if (iVar3 == 0) {
      TraceError("Explosion \"%s\" not found\n");
      pEVar4 = (ExplosionClass *)0x0;
    }
    else {
      ParameterDB::ParameterDB(&local_3c,(char *)((int)&uStack_19 + 1));
      ParameterDB::Get(&local_3c,0x2bb1fe0,0x92d04727,local_28,0x10,(char *)0x0);
      pvVar5 = GetProtoList();
      std::_Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::
      _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
                (&local_30,pvVar5->_Myfirst,(_Container_base_aux *)pvVar5);
      local_38._padding_ = local_30._padding_;
      local_38._Myptr = local_30._Myptr;
      while( true ) {
        pvVar5 = GetProtoList();
        std::_Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::
        _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
                  (&local_30,pvVar5->_Mylast,(_Container_base_aux *)pvVar5);
        bVar2 = std::_Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::
                operator==(&local_38,&local_30);
        if (bVar2) break;
        ppEVar6 = std::_Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::
                  operator*(&local_38);
        pEVar4 = *ppEVar6;
        iVar3 = _stricmp(pEVar4->label,local_28);
        if (iVar3 == 0) {
          pEVar4 = (ExplosionClass *)(**(code **)(pEVar4->_padding_ + 4))(param_1);
          goto LAB_0052f0a5;
        }
        std::_Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::operator++
                  (&local_38);
      }
      TraceError("Explosion \"%s\" uses unknown class label \"%s\"\n");
      pEVar4 = (ExplosionClass *)0x0;
LAB_0052f0a5:
      ParameterDB::~ParameterDB(&local_3c);
    }
  }
  return pEVar4;
}
