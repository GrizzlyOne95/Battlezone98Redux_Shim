/*
 * Entry: 004e7af3
 * Name: DelEntCallback
 * Namespace: Global
 * Signature: void DelEntCallback(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DelEntCallback(tagENTITY *param_1)

{
  int iVar1;
  tagANIMOBJ_HEADER *ptVar2;
  tagANIMOBJ_HEADER **pptVar3;
  int iVar4;
  int iVar5;
  tagANIMOBJ_HEADER **extraout_EDX;
  int iVar6;
  tagANIMOBJ_HEADER **pptVar7;
  int local_c;
  tagANIMOBJ_HEADER **local_8;
  
  iVar5 = 0;
  iVar6 = 0;
  pptVar3 = &AnimActiveList[0].animHeader;
  do {
    if (AnimObj_ActiveCount <= iVar5) break;
    if (((tagANIMOBJ_ACTIVE_LIST *)(pptVar3 + -1))->status != 0) {
      iVar5 = iVar5 + 1;
      if ((*pptVar3 != (tagANIMOBJ_HEADER *)0x0) && ((*pptVar3)->entity == param_1)) {
        AnimObj_Stop(iVar6);
        break;
      }
    }
    pptVar3 = pptVar3 + 8;
    iVar6 = iVar6 + 1;
  } while ((int)pptVar3 < 0xbac8ec);
  iVar5 = AnimCount;
  iVar6 = 0;
  if (0 < AnimCount) {
    do {
      if (AnimList[iVar6]->entity == param_1) {
        local_c = 0;
        pptVar3 = AnimList + iVar6;
        ptVar2 = *pptVar3;
        local_8 = &AnimActiveList[0].animHeader;
        do {
          if (*local_8 == ptVar2) {
            AnimObj_Stop(local_c);
            pptVar3 = extraout_EDX;
          }
          local_8 = local_8 + 8;
          local_c = local_c + 1;
        } while ((int)local_8 < 0xbac8ec);
        ptVar2->entity = (void *)0x0;
        (*pptVar3)->obj = (void *)0x0;
        free(*pptVar3);
        iVar1 = iVar6 + 1;
        if (iVar1 < iVar5) {
          pptVar3 = AnimList + iVar1;
          pptVar7 = (tagANIMOBJ_HEADER **)(&AnimActiveList[0x200].status + iVar6);
          for (iVar4 = iVar5 - iVar1; iVar4 != 0; iVar4 = iVar4 + -1) {
            *pptVar7 = *pptVar3;
            pptVar3 = pptVar3 + 1;
            pptVar7 = pptVar7 + 1;
          }
        }
        AnimCount = iVar5 + -1;
        return;
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < AnimCount);
  }
  return;
}
