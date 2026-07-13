/*
 * Entry: 004aebfc
 * Name: BestScrap
 * Namespace: Global
 * Signature: Scrap * BestScrap(Scavenger * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scrap * __cdecl BestScrap(Scavenger *param_1)

{
  float fVar1;
  bool bVar2;
  Scrap *pSVar3;
  float *pfVar4;
  Scrap *pSVar5;
  int iVar6;
  GameObject *in_ECX;
  Range_Search_Results local_44;
  float local_18;
  float local_10;
  int *local_c;
  float local_8;
  
  local_18 = (float)(in_ECX->obj->transform).posit_x;
  local_10 = (float)(in_ECX->obj->transform).posit_z;
  if (in_ECX == GameObject::userObject) {
    local_8 = 25.0;
    pSVar3 = (Scrap *)0x0;
    Range::Search(Scrap::scrapRange,(double)local_18,(double)local_10,20.0,&local_44);
    bVar2 = Range_Search_Results::Get_Next_Object(&local_44,&local_c);
    if (bVar2) {
      do {
        pSVar5 = (Scrap *)GameObject::GetObj(*local_c);
        if (pSVar5 != (Scrap *)0x0) {
          iVar6 = (**(code **)(pSVar5->_padding_ + 0x30))();
          if ((*(uint *)(iVar6 + 0x14) & 0x200) == 0) {
            pfVar4 = (float *)(**(code **)(pSVar5->_padding_ + 0xc))();
            fVar1 = (local_10 - pfVar4[2]) * (local_10 - pfVar4[2]) +
                    (local_18 - *pfVar4) * (local_18 - *pfVar4);
            if (fVar1 < local_8) {
              pSVar3 = pSVar5;
              local_8 = fVar1;
            }
          }
        }
        bVar2 = Range_Search_Results::Get_Next_Object(&local_44,&local_c);
      } while (bVar2);
    }
  }
  else {
    pSVar3 = (Scrap *)GameObject::GetObj(in_ECX->targetHandle);
    if ((pSVar3 == (Scrap *)0x0) ||
       (pfVar4 = (float *)(**(code **)(pSVar3->_padding_ + 0xc))(),
       25.0 <= (local_10 - pfVar4[2]) * (local_10 - pfVar4[2]) +
               (local_18 - *pfVar4) * (local_18 - *pfVar4))) {
      pSVar3 = (Scrap *)0x0;
    }
  }
  return pSVar3;
}
