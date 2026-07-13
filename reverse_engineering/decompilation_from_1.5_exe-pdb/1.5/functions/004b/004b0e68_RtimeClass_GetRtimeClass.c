/*
 * Entry: 004b0e68
 * Name: RtimeClass::GetRtimeClass
 * Namespace: RtimeClass
 * Signature: RtimeClass * GetRtimeClass(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RtimeClass * __cdecl RtimeClass::GetRtimeClass(char *param_1)

{
  byte bVar1;
  bool bVar2;
  RtimeClass **ppRVar3;
  byte *pbVar4;
  int iVar5;
  byte *pbVar6;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_c,rTimeClasses->_Myhead->_Next,rTimeClasses);
  do {
    std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,rTimeClasses->_Myhead,rTimeClasses);
    bVar2 = std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
    if (bVar2) {
      return (RtimeClass *)0x0;
    }
    ppRVar3 = std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Const_iterator<1>::operator*
                        (&local_c);
    pbVar4 = (byte *)(*ppRVar3)->classname;
    pbVar6 = (byte *)param_1;
    do {
      bVar1 = *pbVar6;
      bVar2 = bVar1 < *pbVar4;
      if (bVar1 != *pbVar4) {
LAB_004b0eb0:
        iVar5 = (1 - (uint)bVar2) - (uint)(bVar2 != 0);
        goto LAB_004b0eb5;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar6[1];
      bVar2 = bVar1 < pbVar4[1];
      if (bVar1 != pbVar4[1]) goto LAB_004b0eb0;
      pbVar6 = pbVar6 + 2;
      pbVar4 = pbVar4 + 2;
    } while (bVar1 != 0);
    iVar5 = 0;
LAB_004b0eb5:
    if (iVar5 == 0) {
      ppRVar3 = std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Const_iterator<1>::operator*
                          (&local_c);
      return *ppRVar3;
    }
    std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Const_iterator<1>::operator++(&local_c);
  } while( true );
}
