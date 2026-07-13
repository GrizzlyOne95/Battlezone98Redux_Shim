/*
 * Entry: 004757b1
 * Name: Floor_GetFloor
 * Namespace: Global
 * Signature: void Floor_GetFloor(VECTOR_3D_LONG param_1, float * param_2, VECTOR_3D * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Floor_GetFloor(VECTOR_3D_LONG param_1,float *param_2,VECTOR_3D *param_3)

{
  float fVar1;
  float fVar2;
  CIRCLE *pCVar3;
  int iVar4;
  wrap_struct *pwVar5;
  VECTOR_3D *unaff_EDI;
  VECTOR_2D VVar6;
  VECTOR_2D VVar7;
  CIRCLE local_50;
  float local_44;
  float fStack_40;
  float fStack_3c;
  VECTOR_3D local_38;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  VECTOR_2D local_18;
  tagENTITY *local_10;
  _OBJ76 *local_c;
  _OBJ76 *local_8;
  
  local_20 = (float)param_1.x;
  local_1c = (float)param_1.z;
  Terrain_GetHeightAndNormal(param_1.x,param_1.z,(float *)&local_c,&local_38);
  for (pwVar5 = FloorList; pwVar5 != (wrap_struct *)0x0; pwVar5 = pwVar5->next) {
    local_10 = pwVar5->ptr;
    pCVar3 = Entity_WorldCircle(&local_50,local_10);
    local_2c = (pCVar3->origin).x;
    local_28 = (pCVar3->origin).z;
    local_24 = pCVar3->radius;
    VVar6.z = local_1c;
    VVar6.x = local_20;
    VVar6 = Vec2D_Subtract(VVar6,pCVar3->origin);
    fVar1 = local_18.x * local_18.x;
    local_18.z = VVar6.z;
    fVar2 = local_18.z * local_18.z;
    local_18 = VVar6;
    if (fVar2 + fVar1 <= local_24 * local_24) {
      VVar7.z = local_1c;
      VVar7.x = local_20;
      iVar4 = PointOnFloor(VVar7,(tagENTITY *)&local_8,&local_44,unaff_EDI);
      if (((iVar4 != 0) && ((double)(float)local_8 < param_1.y + 1.0)) &&
         ((float)local_c < (float)local_8)) {
        local_c = local_8;
        local_38.x = local_44;
        local_38.y = fStack_40;
        local_38.z = fStack_3c;
      }
    }
  }
  if (param_2 != (float *)0x0) {
    *param_2 = (float)local_c;
  }
  if (param_3 != (VECTOR_3D *)0x0) {
    param_3->x = local_38.x;
    param_3->y = local_38.y;
    param_3->z = local_38.z;
  }
  return;
}
