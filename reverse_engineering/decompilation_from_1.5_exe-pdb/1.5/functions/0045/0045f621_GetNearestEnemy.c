/*
 * Entry: 0045f621
 * Name: GetNearestEnemy
 * Namespace: Global
 * Signature: int GetNearestEnemy(VECTOR_3D * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetNearestEnemy(VECTOR_3D *param_1,GameObject *param_2)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  VECTOR_3D *pVVar4;
  bool bVar5;
  GameObject *pGVar6;
  int iVar7;
  float *pfVar8;
  Range_Search_Results local_3c;
  _OBJ76 *local_10;
  GameObject *local_c;
  float local_8;
  
  pVVar4 = param_1;
  local_c = (GameObject *)0x0;
  local_8 = 1e+30;
  Range::Search(collision_range_search,(double)param_1->x,(double)param_1->z,450.0,&local_3c);
  bVar5 = Range_Search_Results::Get_Next_Object(&local_3c,(int **)&param_1);
  if (bVar5) {
    do {
      pGVar6 = GameObjectHandle::GetObj((int)param_1->x);
      if ((pGVar6 != (GameObject *)0x0) && (pGVar6 != param_2)) {
        piVar1 = &pGVar6->_padding_;
        iVar7 = (**(code **)(*piVar1 + 4))();
        bVar5 = GameObject::EnemyP(param_2,iVar7);
        if (((bVar5) &&
            ((bVar5 = GameObject::EnemyP(param_2,pGVar6->perceivedTeam), bVar5 &&
             (local_10 = (_OBJ76 *)(**(code **)(*piVar1 + 0x30))(), (local_10->flags & 0x200) == 0))
            )) && ((iVar7 = IsCraft(local_10), iVar7 != 0 || (local_10->class_id == CLASS_ID_PERSON)
                   ))) {
          pfVar8 = (float *)(**(code **)(*piVar1 + 0xc))();
          fVar2 = pVVar4->x - *pfVar8;
          fVar3 = pVVar4->z - pfVar8[2];
          fVar2 = fVar3 * fVar3 + fVar2 * fVar2;
          if (fVar2 < local_8) {
            local_c = pGVar6;
            local_8 = fVar2;
          }
        }
      }
      bVar5 = Range_Search_Results::Get_Next_Object(&local_3c,(int **)&param_1);
    } while (bVar5);
    if (local_c != (GameObject *)0x0) {
      iVar7 = GameObject::GetHandle(local_c);
      return iVar7;
    }
  }
  return 0;
}
