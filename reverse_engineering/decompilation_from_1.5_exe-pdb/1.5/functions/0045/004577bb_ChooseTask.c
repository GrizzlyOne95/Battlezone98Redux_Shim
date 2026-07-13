/*
 * Entry: 004577bb
 * Name: ChooseTask
 * Namespace: Global
 * Signature: AiTask * ChooseTask(Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiTask * __cdecl ChooseTask(Craft *param_1,GameObject *param_2)

{
  VECTOR_3D_LONG VVar1;
  VECTOR_3D VVar2;
  bool bVar3;
  char cVar4;
  float *pfVar5;
  PersonGlide *pPVar6;
  int iVar7;
  Craft *pCVar8;
  _OBJ76 *p_Var9;
  PersonStraight *pPVar10;
  PersonGetIn *pPVar11;
  Craft *unaff_EBX;
  SINCOS SVar12;
  float fVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  Range_Search_Results *pRVar17;
  VECTOR_3D local_9c;
  undefined1 local_90 [20];
  VECTOR_3D_LONG local_7c;
  VECTOR_3D local_64;
  VECTOR_3D local_58;
  SINCOS local_4c;
  float local_44;
  VECTOR_3D local_40;
  VECTOR_3D local_34;
  int *local_28;
  VECTOR_3D local_24;
  int local_18;
  VECTOR_3D local_14;
  int *local_8;
  
  pfVar5 = (float *)(**(code **)(unaff_EBX->_padding_ + 0xc))();
  local_24.x = *pfVar5;
  local_24.y = pfVar5[1];
  local_24.z = pfVar5[2];
  bVar3 = OnBlocked(&local_24);
  if ((bVar3) && ((unaff_EBX->vhcl->flags & 4) != 0)) {
    pPVar6 = operator_new(0x138);
    if (pPVar6 != (PersonGlide *)0x0) {
      pPVar6 = PersonGlide::PersonGlide(pPVar6,unaff_EBX,(GameObject *)param_1);
      return (AiTask *)pPVar6;
    }
  }
  else {
    pfVar5 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
    local_14.x = *pfVar5;
    local_14.y = pfVar5[1];
    local_14.z = pfVar5[2];
    bVar3 = OnBlocked(&local_14);
    if (bVar3) {
      local_18 = 0;
      local_28 = (int *)0x3f800000;
      local_34.x = local_14.x;
      local_34.y = local_14.y;
      local_34.z = local_14.z;
      do {
        SVar12 = SinCos((float)local_18 * 0.7853982);
        local_40.x = local_4c.Sin * Terrain.Grid_Size * 16.0;
        local_40.y = 0.0;
        local_4c.Cos = SVar12.Cos;
        local_40.z = Terrain.Grid_Size * local_4c.Cos * 16.0;
        local_7c.x = (double)local_14.x;
        local_7c.y = (double)local_14.y;
        local_7c.z = (double)local_14.z;
        local_4c = SVar12;
        local_8 = (int *)DistToOffBlocked(&local_7c,&local_40,(float)local_28);
        if ((float)local_8 < (float)local_28) {
          local_28 = local_8;
          dVar14 = rsqrt((double)(local_40.x * local_40.x + local_40.z * local_40.z));
          local_34.x = local_40.x * ((float)dVar14 + (float)local_8) + local_14.x;
          local_34.y = local_14.y;
          local_34.z = ((float)dVar14 + (float)local_8) * local_40.z + local_14.z;
        }
        local_18 = local_18 + 1;
      } while (local_18 < 8);
      local_14.x = local_34.x;
      local_14.y = local_34.y;
      local_14.z = local_34.z;
    }
    local_58.x = local_14.x - local_24.x;
    local_64.x = local_24.x;
    local_64.y = local_24.y;
    local_58.y = local_14.y - local_24.y;
    local_64.z = local_24.z;
    local_58.z = local_14.z - local_24.z;
    local_44 = 1.0;
    VVar1.y._0_4_ = SUB84((double)local_24.y,0);
    VVar1.x = (double)local_24.x;
    VVar1.y._4_4_ = (int)((ulonglong)(double)local_24.y >> 0x20);
    VVar1.z._0_4_ = SUB84((double)local_24.z,0);
    VVar1.z._4_4_ = (int)((ulonglong)(double)local_24.z >> 0x20);
    VVar2.y = local_58.y;
    VVar2.x = local_58.x;
    VVar2.z = local_58.z;
    local_34.x = local_58.x;
    local_34.y = local_58.y;
    local_34.z = local_58.z;
    iVar7 = Terrain_GetIntersection(VVar1,VVar2,&local_44,&local_9c);
    if (iVar7 == 0) {
      pRVar17 = (Range_Search_Results *)local_90;
      fVar13 = Max(local_24.z,local_14.z);
      dVar14 = (double)fVar13;
      fVar13 = Max(local_24.x,local_14.x);
      dVar16 = (double)fVar13;
      fVar13 = Min(local_24.z,local_14.z);
      dVar15 = (double)fVar13;
      fVar13 = Min(local_24.x,local_14.x);
      Range::Search(GameObject::objectRange,(double)fVar13,dVar15,dVar16,dVar14,pRVar17);
      do {
        do {
          bVar3 = Range_Search_Results::Get_Next_Object((Range_Search_Results *)local_90,&local_8);
          if (!bVar3) {
            pPVar10 = operator_new(0x138);
            if (pPVar10 == (PersonStraight *)0x0) {
              return (AiTask *)0x0;
            }
            pPVar10 = PersonStraight::PersonStraight(pPVar10,unaff_EBX,(GameObject *)param_1);
            return (AiTask *)pPVar10;
          }
          pCVar8 = (Craft *)GameObject::GetObj(*local_8);
        } while (((pCVar8 == (Craft *)0x0) || (pCVar8 == unaff_EBX)) || (pCVar8 == param_1));
        p_Var9 = (_OBJ76 *)(**(code **)(pCVar8->_padding_ + 0x30))();
        iVar7 = dynamic_object(p_Var9);
      } while (((iVar7 != 0) &&
               ((iVar7 = IsCraft(p_Var9), iVar7 == 0 ||
                (cVar4 = (**(code **)(pCVar8->_padding_ + 100))(), cVar4 == '\0')))) ||
              (bVar3 = IntersectGameObject(&local_64,&local_58,&local_44,&local_34,
                                           (GameObject *)pCVar8,(float)unaff_EBX->_padding_), !bVar3
              ));
    }
    pPVar11 = operator_new(0x150);
    if (pPVar11 != (PersonGetIn *)0x0) {
      pPVar11 = PersonGetIn::PersonGetIn(pPVar11,unaff_EBX,(GameObject *)param_1,&local_14);
      return (AiTask *)pPVar11;
    }
  }
  return (AiTask *)0x0;
}
