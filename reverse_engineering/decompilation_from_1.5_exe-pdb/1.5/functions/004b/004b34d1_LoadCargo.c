/*
 * Entry: 004b34d1
 * Name: LoadCargo
 * Namespace: Global
 * Signature: void LoadCargo(Tug * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl LoadCargo(Tug *param_1)

{
  float fVar1;
  bool bVar2;
  float *pfVar3;
  Tug *pTVar4;
  Tug *pTVar5;
  int iVar6;
  float *pfVar7;
  Range_Search_Results local_48;
  float local_1c;
  float fStack_18;
  float local_14;
  int *local_10;
  float local_c;
  Tug *local_8;
  
  pfVar3 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  local_1c = *pfVar3;
  fStack_18 = pfVar3[1];
  local_14 = pfVar3[2];
  Range::Search(GameObject::objectRange,(double)local_1c,(double)local_14,30.0,&local_48);
  local_8 = (Tug *)0x0;
  local_c = 900.0;
  bVar2 = Range_Search_Results::Get_Next_Object(&local_48,&local_10);
  if (bVar2) {
    do {
      pTVar4 = (Tug *)GameObjectHandle::GetObj(*local_10);
      pTVar5 = param_1;
      if (pTVar4 != (Tug *)0x0) {
        do {
          if (pTVar4 == pTVar5) break;
          pTVar5 = (Tug *)pTVar5->_padding_;
        } while (pTVar5 != (Tug *)0x0);
        if ((((pTVar5 == (Tug *)0x0) &&
             (iVar6 = (**(code **)(pTVar4->_padding_ + 0x28))(), iVar6 != 0)) &&
            (*(bool *)&pTVar4->_padding_ == false)) &&
           ((AiProcess *)pTVar4->_padding_ == (AiProcess *)0x0)) {
          pfVar3 = (float *)(**(code **)(pTVar4->_padding_ + 0xc))();
          pfVar7 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
          fVar1 = (pfVar7[2] - pfVar3[2]) * (pfVar7[2] - pfVar3[2]) +
                  (*pfVar7 - *pfVar3) * (*pfVar7 - *pfVar3);
          if (fVar1 <= local_c) {
            local_c = fVar1;
            local_8 = pTVar4;
          }
        }
      }
      bVar2 = Range_Search_Results::Get_Next_Object(&local_48,&local_10);
    } while (bVar2);
    if (local_8 != (Tug *)0x0) {
      Tug::SetCargo(param_1,(GameObject *)local_8);
    }
  }
  return;
}
