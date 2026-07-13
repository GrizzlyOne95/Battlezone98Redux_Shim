/*
 * Entry: 00521b59
 * Name: ComputeCoplanarFlags
 * Namespace: Global
 * Signature: void ComputeCoplanarFlags(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ComputeCoplanarFlags(int param_1,int param_2)

{
  uint uVar1;
  float fVar2;
  PLANE *pPVar3;
  ushort *puVar4;
  int iVar5;
  PLANE local_8c;
  PLANE local_7c;
  float local_6c;
  float local_68;
  float local_64;
  float fStack_60;
  float local_5c;
  float local_58;
  float local_54;
  float fStack_50;
  VECTOR_3D local_4c;
  VECTOR_3D local_40;
  VECTOR_3D local_34;
  VECTOR_3D local_28;
  int local_1c;
  undefined4 local_18;
  float local_14;
  float local_10;
  uint local_c;
  float local_8;
  
  local_18 = 0;
  local_4c.y = GetTerrainHeight(param_1,param_2);
  local_4c.x = (float)param_1;
  uVar1 = param_1 + 1;
  fVar2 = (float)param_2;
  local_4c.z = fVar2;
  local_c = uVar1;
  local_8 = local_4c.x;
  local_40.y = GetTerrainHeight(uVar1,param_2);
  iVar5 = param_2 + 1;
  local_40.x = (float)(int)local_c;
  local_40.z = fVar2;
  local_1c = iVar5;
  local_14 = local_40.x;
  local_34.y = GetTerrainHeight(uVar1,iVar5);
  local_34.x = local_14;
  local_34.z = (float)local_1c;
  local_10 = local_34.z;
  local_28.y = GetTerrainHeight(param_1,iVar5);
  local_28.x = local_8;
  local_28.z = local_10;
  pPVar3 = Plane_Equation(&local_7c,&local_4c,&local_40,&local_34);
  local_6c = (pPVar3->surf_normal).x;
  local_68 = (pPVar3->surf_normal).y;
  local_64 = (pPVar3->surf_normal).z;
  fStack_60 = pPVar3->dist;
  pPVar3 = Plane_Equation(&local_7c,&local_4c,&local_34,&local_28);
  local_5c = (pPVar3->surf_normal).x;
  local_58 = (pPVar3->surf_normal).y;
  local_54 = (pPVar3->surf_normal).z;
  fStack_50 = pPVar3->dist;
  if ((0.995 < local_64 * local_54 + local_5c * local_6c + local_68 * local_58) &&
     (local_18 = 0x8000, ((local_c ^ param_1) & 0xfffffffe) == 0)) {
    local_4c.y = GetTerrainHeight(local_c,param_2);
    local_4c.x = local_14;
    iVar5 = param_1 + 2;
    local_4c.z = fVar2;
    local_8 = (float)iVar5;
    local_40.y = GetTerrainHeight(iVar5,param_2);
    local_40.x = (float)(int)local_8;
    local_40.z = fVar2;
    local_8 = local_40.x;
    local_34.y = GetTerrainHeight(iVar5,local_1c);
    local_34.x = local_8;
    local_34.z = local_10;
    local_28.y = GetTerrainHeight(local_c,local_1c);
    local_28.x = local_14;
    local_28.z = local_10;
    pPVar3 = Plane_Equation(&local_7c,&local_4c,&local_40,&local_34);
    local_5c = (pPVar3->surf_normal).x;
    local_58 = (pPVar3->surf_normal).y;
    local_54 = (pPVar3->surf_normal).z;
    fStack_50 = pPVar3->dist;
    pPVar3 = Plane_Equation(&local_8c,&local_4c,&local_34,&local_28);
    local_7c.surf_normal.x = (pPVar3->surf_normal).x;
    local_7c.surf_normal.y = (pPVar3->surf_normal).y;
    local_7c.surf_normal.z = (pPVar3->surf_normal).z;
    local_7c.dist = pPVar3->dist;
    fVar2 = local_7c.surf_normal.z * local_54 +
            local_7c.surf_normal.x * local_5c + local_7c.surf_normal.y * local_58;
    if ((!NAN(fVar2) && 1.0 < fVar2 != (fVar2 == 1.0)) &&
       ((1.0 <= local_64 * local_54 + local_5c * local_6c + local_68 * local_58 &&
        (1.0 <= local_7c.surf_normal.x * local_6c +
                local_7c.surf_normal.z * local_64 + local_7c.surf_normal.y * local_68)))) {
      local_18 = 0xc000;
    }
  }
  puVar4 = GetZonePtr(param_1,param_2);
  *puVar4 = *puVar4 & 0x3fff | (ushort)local_18;
  return;
}
