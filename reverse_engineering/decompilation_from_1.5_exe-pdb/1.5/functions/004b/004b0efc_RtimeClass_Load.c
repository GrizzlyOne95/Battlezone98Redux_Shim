/*
 * Entry: 004b0efc
 * Name: RtimeClass::Load
 * Namespace: RtimeClass
 * Signature: SObject * Load(_iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

SObject * __cdecl RtimeClass::Load(_iobuf *param_1)

{
  byte bVar1;
  bool bVar2;
  char cVar3;
  RtimeClass **ppRVar4;
  byte *pbVar5;
  int iVar6;
  SObject *pSVar7;
  OldNew *this;
  byte *pbVar8;
  _Const_iterator<1> local_44;
  void *local_3c;
  _Const_iterator<1> local_38;
  byte local_30 [40];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  ::in(param_1,(char *)local_30,0x28);
  if (version < 0x3ea) {
    ::in(param_1,&local_3c,4);
  }
  else {
    in_sptr(param_1,&local_3c,4);
  }
  std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_38,rTimeClasses->_Myhead->_Next,rTimeClasses);
  do {
    std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_44,rTimeClasses->_Myhead,rTimeClasses);
    bVar2 = std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Const_iterator<1>::operator==
                      (&local_38,&local_44);
    if (bVar2) {
LAB_004b0fc8:
      TraceError("No mission class matches \"%s\"\nUsing LuaMission as a substitute\n");
      pSVar7 = LuaMission::CreateObject();
LAB_004b0fdf:
      this = operator_new(8);
      if (this != (OldNew *)0x0) {
        OldNew::OldNew(this,local_3c,pSVar7);
      }
      cVar3 = (**(code **)(pSVar7->_padding_ + 4))(param_1);
      return (SObject *)(-(uint)(cVar3 != '\0') & (uint)pSVar7);
    }
    ppRVar4 = std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Const_iterator<1>::operator*
                        (&local_38);
    pbVar8 = (byte *)(*ppRVar4)->classname;
    pbVar5 = local_30;
    do {
      bVar1 = *pbVar5;
      bVar2 = bVar1 < *pbVar8;
      if (bVar1 != *pbVar8) {
LAB_004b0f84:
        iVar6 = (1 - (uint)bVar2) - (uint)(bVar2 != 0);
        goto LAB_004b0f89;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar5[1];
      bVar2 = bVar1 < pbVar8[1];
      if (bVar1 != pbVar8[1]) goto LAB_004b0f84;
      pbVar5 = pbVar5 + 2;
      pbVar8 = pbVar8 + 2;
    } while (bVar1 != 0);
    iVar6 = 0;
LAB_004b0f89:
    if (iVar6 == 0) {
      ppRVar4 = std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Const_iterator<1>::operator*
                          (&local_38);
      pSVar7 = (*(*ppRVar4)->m_pfnCreateObject)();
      if (pSVar7 != (SObject *)0x0) goto LAB_004b0fdf;
      goto LAB_004b0fc8;
    }
    std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Const_iterator<1>::operator++(&local_38)
    ;
  } while( true );
}
