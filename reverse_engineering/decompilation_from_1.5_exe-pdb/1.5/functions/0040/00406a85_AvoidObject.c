/*
 * Entry: 00406a85
 * Name: AvoidObject
 * Namespace: Global
 * Signature: GameObject * AvoidObject(GameObject * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl AvoidObject(GameObject *param_1,GameObject *param_2)

{
  int *piVar1;
  VECTOR_3D VVar2;
  bool bVar3;
  float *pfVar4;
  GameObject *pGVar5;
  int iVar6;
  int iVar7;
  VECTOR_3D *pVVar8;
  float fVar9;
  Range_Search_Results local_48;
  float local_1c;
  float fStack_18;
  float local_14;
  GameObject *local_10;
  int *local_c;
  float local_8;
  
  pfVar4 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  local_8 = 2500.0;
  local_10 = (GameObject *)0x0;
  local_1c = *pfVar4;
  fStack_18 = pfVar4[1];
  local_14 = pfVar4[2];
  Range::Search(collision_range_search,(double)local_1c,(double)local_14,50.0,&local_48);
  while (bVar3 = Range_Search_Results::Get_Next_Object(&local_48,&local_c), bVar3) {
    pGVar5 = GameObjectHandle::GetObj(*local_c);
    if ((((pGVar5 != (GameObject *)0x0) && (param_1 != pGVar5)) && (param_2 != pGVar5)) &&
       (pGVar5->isCargo == false)) {
      piVar1 = &pGVar5->_padding_;
      iVar6 = (**(code **)*piVar1)();
      iVar6 = *(int *)(iVar6 + 0x20);
      if (((iVar6 != 0x54554700) ||
          (iVar7 = (**(code **)param_1->_padding_)(), *(int *)(iVar7 + 0x20) != 0x52435943)) &&
         (iVar6 != 0x4745495a)) {
        iVar7 = (**(code **)*piVar1)();
        iVar7 = *(int *)(iVar7 + 0x28);
        if (((iVar7 != 7) && ((iVar7 != 3 || (iVar6 == 0x544f5250)))) &&
           ((iVar7 != 4 || (bVar3 = GameObject::EnemyP(param_1,pGVar5), !bVar3)))) {
          pVVar8 = (VECTOR_3D *)(**(code **)(*piVar1 + 0xc))();
          VVar2.y = fStack_18;
          VVar2.x = local_1c;
          VVar2.z = local_14;
          fVar9 = Dist3D_Squared(*pVVar8,VVar2);
          if (fVar9 < local_8) {
            local_10 = pGVar5;
            local_8 = fVar9;
          }
        }
      }
    }
  }
  return local_10;
}
