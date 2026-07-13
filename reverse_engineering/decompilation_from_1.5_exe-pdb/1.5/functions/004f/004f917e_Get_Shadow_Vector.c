/*
 * Entry: 004f917e
 * Name: Get_Shadow_Vector
 * Namespace: Global
 * Signature: VECTOR_3D * Get_Shadow_Vector(VECTOR_3D * __return_storage_ptr__, tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl Get_Shadow_Vector(VECTOR_3D *__return_storage_ptr__,tagENTITY *param_1)

{
  _OBJ76 *p_Var1;
  DYNAMIC_LIGHT *pDVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  DYNAMIC_LIGHT *pDVar8;
  VECTOR_3D *pVVar9;
  float fVar10;
  VECTOR_3D local_3c;
  VECTOR_3D local_30;
  VECTOR_3D local_24;
  float local_18;
  float local_14;
  float local_10;
  int local_c;
  float local_8;
  
  if (TOD_tbl[Lights_Struct.TOD_entry].Day_Time == 1) {
    pVVar9 = &Sun_Light;
    goto LAB_004f9330;
  }
  p_Var1 = param_1->obj76;
  local_8 = 0.0;
  local_10 = 0.0;
  pDVar8 = (DYNAMIC_LIGHT *)0x0;
  Vector_Transform(&local_24,&(param_1->bSphere).origin,1,&p_Var1->transform);
  local_c = 0;
  local_18 = TOD_tbl[Lights_Struct.TOD_entry].Att * 1.5;
  if (Lights_Struct.Visibles_Light_Counter < 1) {
LAB_004f9321:
    pVVar9 = &Sun_Light;
  }
  else {
    do {
      pDVar2 = Lights_Struct.Visibles_Lights[local_c];
      if ((pDVar2->Light_Owner != (_OBJ76 *)0x0) && (pDVar2->Light_Owner != p_Var1)) {
        fVar3 = (pDVar2->Shadow_Pos).x - local_24.x;
        fVar6 = (pDVar2->Shadow_Pos).y - local_24.y;
        fVar7 = (pDVar2->Shadow_Pos).z - local_24.z;
        fVar5 = fVar3 * fVar3 + fVar6 * fVar6 + fVar7 * fVar7;
        fVar4 = 1.0 / (pDVar2->Att_Dist * fVar5 + 1.0);
        local_14 = fVar4;
        fVar10 = 1.0;
        if ((pDVar2->flags & 1) != 0) {
          fVar10 = Pow((double)((((pDVar2->World_Direction).z * fVar7 +
                                  (pDVar2->World_Direction).y *
                                  (pDVar2->Real_Shadow_Pos_Offset + fVar6) +
                                 (pDVar2->World_Direction).x * fVar3) /
                                 SQRT((fVar6 + fVar6 + pDVar2->Real_Shadow_Pos_Offset) *
                                      pDVar2->Real_Shadow_Pos_Offset + fVar5) + 1.0) * 0.5),
                       (double)(pDVar2->Cone * 0.25));
          fVar4 = local_14 * fVar10;
        }
        if (local_8 < fVar4) {
          local_8 = fVar4;
          local_10 = fVar10;
          pDVar8 = pDVar2;
        }
      }
      local_c = local_c + 1;
    } while (local_c < Lights_Struct.Visibles_Light_Counter);
    if ((pDVar8 == (DYNAMIC_LIGHT *)0x0) || (local_8 <= local_18)) goto LAB_004f9321;
    local_30.x = (pDVar8->Shadow_Pos).x - local_24.x;
    local_30.y = ((pDVar8->Shadow_Pos).y - local_10 * 15.0) - local_24.y;
    local_30.z = (pDVar8->Shadow_Pos).z - local_24.z;
    pVVar9 = Normalize_Vector(&local_3c,&local_30);
  }
  local_30.x = pVVar9->x;
  local_30.y = pVVar9->y;
  local_30.z = pVVar9->z;
  pVVar9 = &local_30;
LAB_004f9330:
  __return_storage_ptr__->x = pVVar9->x;
  __return_storage_ptr__->y = pVVar9->y;
  __return_storage_ptr__->z = pVVar9->z;
  return __return_storage_ptr__;
}
