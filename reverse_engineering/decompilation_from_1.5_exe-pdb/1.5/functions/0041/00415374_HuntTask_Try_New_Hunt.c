/*
 * Entry: 00415374
 * Name: HuntTask::Try_New_Hunt
 * Namespace: HuntTask
 * Signature: int Try_New_Hunt(HuntTask * this, float * param_1, float * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall HuntTask::Try_New_Hunt(HuntTask *this,float *param_1,float *param_2,int param_3)

{
  float fVar1;
  vector<GameObject_*,std::allocator<GameObject_*>_> *this_00;
  uint uVar2;
  Scrap **ppSVar3;
  float *pfVar4;
  uint uVar5;
  
  this_00 = GameObject::objectList;
  uVar5 = (int)Scrap::scrapList._Mylast - (int)Scrap::scrapList._Myfirst >> 2;
  if (uVar5 == 0) {
    uVar5 = (int)GameObject::objectList->_Mylast - (int)GameObject::objectList->_Myfirst >> 2;
    if (uVar5 == 0) {
      return 0;
    }
    uVar2 = rand();
    ppSVar3 = (Scrap **)
              std::vector<GameObject_*,std::allocator<GameObject_*>_>::operator[]
                        (this_00,uVar2 % uVar5);
  }
  else {
    uVar2 = rand();
    ppSVar3 = std::vector<Scrap_*,std::allocator<Scrap_*>_>::operator[]
                        (&Scrap::scrapList,uVar2 % uVar5);
  }
  if (*ppSVar3 == (Scrap *)0x0) {
    return 0;
  }
  pfVar4 = (float *)(**(code **)((*ppSVar3)->_padding_ + 0xc))();
  fVar1 = pfVar4[2];
  *param_1 = *pfVar4;
  *param_2 = fVar1;
  return 1;
}
