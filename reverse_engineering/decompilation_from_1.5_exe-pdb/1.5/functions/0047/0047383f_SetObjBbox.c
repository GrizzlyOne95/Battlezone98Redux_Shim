/*
 * Entry: 0047383f
 * Name: SetObjBbox
 * Namespace: Global
 * Signature: void SetObjBbox(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetObjBbox(_OBJ76 *param_1)

{
  _GEOMETRY *p_Var1;
  float fVar2;
  float fVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  int iVar6;
  VECTOR_3D *pVVar7;
  VECTOR_3D *pVVar8;
  VECTOR_3D local_64;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  for (; param_1 != (_OBJ76 *)0x0; param_1 = param_1->sibling) {
    if (((param_1->flags & 1) == 0) && (iVar6 = GeoCache_SelectLOD(param_1,0), iVar6 == 1)) {
      iVar6 = param_1->geom->vertex_count;
      local_28 = 0x7149f2ca;
      local_24 = 0x7149f2ca;
      local_20 = 0x7149f2ca;
      local_1c = 1e+30;
      local_34 = 0xf149f2ca;
      local_18 = 1e+30;
      local_30 = 0xf149f2ca;
      local_2c = 0xf149f2ca;
      local_14 = 1e+30;
      local_10 = -1e+30;
      local_c = -1e+30;
      local_8 = -1e+30;
      if (0 < iVar6) {
        pVVar7 = param_1->geom->vertex_table;
        do {
          local_40 = pVVar7->x;
          local_3c = pVVar7->y;
          local_38 = pVVar7->z;
          if (local_40 < local_1c) {
            local_1c = local_40;
          }
          if (local_3c < local_18) {
            local_18 = local_3c;
          }
          if (local_38 < local_14) {
            local_14 = local_38;
          }
          if (local_10 < local_40) {
            local_10 = local_40;
          }
          if (local_c < local_3c) {
            local_c = local_3c;
          }
          if (local_8 < local_38) {
            local_8 = local_38;
          }
          pVVar7 = pVVar7 + 1;
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
      }
      (param_1->bBox).min.x = local_1c;
      (param_1->bBox).min.y = local_18;
      (param_1->bBox).min.z = local_14;
      (param_1->bBox).max.x = local_10;
      (param_1->bBox).max.y = local_c;
      (param_1->bBox).max.z = local_8;
      VVar4.y = local_18;
      VVar4.x = local_1c;
      VVar4.z = local_14;
      VVar5.y = local_c;
      VVar5.x = local_10;
      VVar5.z = local_8;
      pVVar7 = CombineVectors(&local_64,0.5,VVar4,0.5,VVar5);
      p_Var1 = param_1->geom;
      fVar2 = -1e+30;
      (param_1->bSphere).origin.x = pVVar7->x;
      (param_1->bSphere).origin.y = pVVar7->y;
      (param_1->bSphere).origin.z = pVVar7->z;
      iVar6 = p_Var1->vertex_count;
      if (0 < iVar6) {
        pVVar8 = p_Var1->vertex_table;
        local_58 = pVVar7->x;
        local_54 = pVVar7->y;
        local_50 = pVVar7->z;
        do {
          local_4c = pVVar8->x;
          local_48 = pVVar8->y;
          local_44 = pVVar8->z;
          fVar3 = (local_44 - local_50) * (local_44 - local_50) +
                  (local_48 - local_54) * (local_48 - local_54) +
                  (local_4c - local_58) * (local_4c - local_58);
          if (fVar2 < fVar3) {
            fVar2 = fVar3;
          }
          pVVar8 = pVVar8 + 1;
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
      }
      (param_1->bSphere).radius = SQRT(fVar2);
    }
    if (param_1->child != (_OBJ76 *)0x0) {
      SetObjBbox(param_1->child);
    }
  }
  return;
}
