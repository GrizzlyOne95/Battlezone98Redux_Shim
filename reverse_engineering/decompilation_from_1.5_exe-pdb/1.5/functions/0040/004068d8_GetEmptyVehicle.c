/*
 * Entry: 004068d8
 * Name: GetEmptyVehicle
 * Namespace: Global
 * Signature: GameObject * GetEmptyVehicle(GameObject * param_1, float * param_2, GameObject * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl GetEmptyVehicle(GameObject *param_1,float *param_2,GameObject *param_3)

{
  float fVar1;
  bool bVar2;
  byte bVar3;
  float *pfVar4;
  GameObject *pGVar5;
  _OBJ76 *p_Var6;
  int iVar7;
  Range_Search_Results local_50;
  float local_24;
  float fStack_20;
  float local_1c;
  float local_18;
  float fStack_14;
  float local_10;
  GameObject *local_c;
  int *local_8;
  
  pfVar4 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  local_c = (GameObject *)0x0;
  local_18 = *pfVar4;
  fStack_14 = pfVar4[1];
  local_10 = pfVar4[2];
  Range::Search(collision_range_search,(double)local_18,(double)local_10,(double)SQRT(*param_2),
                &local_50);
  bVar2 = Range_Search_Results::Get_Next_Object(&local_50,&local_8);
  if (bVar2) {
    do {
      pGVar5 = GameObjectHandle::GetObj(*local_8);
      if ((((pGVar5 != (GameObject *)0x0) && (pGVar5 != param_3)) && (pGVar5->isCargo == false)) &&
         (bVar3 = (**(code **)(param_1->_padding_ + 4))(),
         (pGVar5->locked >> (bVar3 & 0x1f) & 1) == 0)) {
        p_Var6 = (_OBJ76 *)(**(code **)(pGVar5->_padding_ + 0x30))();
        iVar7 = IsCraft(p_Var6);
        if (((iVar7 != 0) && (pGVar5->aiProcess == (AiProcess *)0x0)) &&
           ((pGVar5->curPilot == (GameObjectClass *)0x0 &&
            (bVar2 = TeamHasFreeSlot(param_1->teamList,pGVar5), bVar2)))) {
          pfVar4 = (float *)(**(code **)(pGVar5->_padding_ + 0xc))();
          local_24 = *pfVar4;
          fStack_20 = pfVar4[1];
          local_1c = pfVar4[2];
          fVar1 = (local_1c - local_10) * (local_1c - local_10) +
                  (local_24 - local_18) * (local_24 - local_18);
          if (fVar1 < *param_2) {
            *param_2 = fVar1;
            local_c = pGVar5;
          }
        }
      }
      bVar2 = Range_Search_Results::Get_Next_Object(&local_50,&local_8);
    } while (bVar2);
  }
  return local_c;
}
