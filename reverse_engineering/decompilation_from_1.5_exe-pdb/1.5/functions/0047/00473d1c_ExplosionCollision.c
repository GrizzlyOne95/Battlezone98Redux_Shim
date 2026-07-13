/*
 * Entry: 00473d1c
 * Name: ExplosionCollision
 * Namespace: Global
 * Signature: _OBJ76 * ExplosionCollision(float param_1, _OBJ76 * param_2, _OBJ76 * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __cdecl ExplosionCollision(float param_1,_OBJ76 *param_2,_OBJ76 *param_3)

{
  VECTOR_3D VVar1;
  VECTOR_3D VVar2;
  tagENTITY *ptVar3;
  int iVar4;
  SPHERE *pSVar5;
  VECTOR_3D *pVVar6;
  _OBJ76 *p_Var7;
  double dVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  SPHERE local_cc;
  VECTOR_3D local_bc;
  VECTOR_3D local_b0;
  VECTOR_3D local_a4 [2];
  float local_8c;
  VECTOR_3D local_88;
  VECTOR_3D local_7c;
  BBOX local_70;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  VECTOR_3D local_4c;
  VECTOR_3D local_40;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  _OBJ76 *local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_20 = (_OBJ76 *)0x0;
  p_Var7 = (_OBJ76 *)0x0;
  if (param_2 != (_OBJ76 *)0x0) {
    local_10 = (float)(param_2->transform).posit_x;
    local_c = (float)(param_2->transform).posit_y;
    local_8 = (float)(param_2->transform).posit_z;
    local_8c = param_1 * param_1;
    local_70.min.x = local_10 - param_1;
    local_70.min.y = local_c - param_1;
    local_70.min.z = local_8 - param_1;
    local_70.max.x = local_10 + param_1;
    local_70.max.y = local_c + param_1;
    local_70.max.z = param_1 + local_8;
    ptVar3 = FirstCollidable();
    while (p_Var7 = local_20, ptVar3 != (tagENTITY *)0x0) {
      if ((ptVar3->obj76 != param_3) && (iVar4 = CheckBoxes(&local_70,ptVar3), iVar4 != 0)) {
        pSVar5 = Entity_WorldSphere(&local_cc,ptVar3);
        local_34 = (pSVar5->origin).x;
        local_30 = (pSVar5->origin).y;
        local_2c = (pSVar5->origin).z;
        local_28 = pSVar5->radius * pSVar5->radius * 0.5;
        local_40.x = local_34 - local_10;
        local_40.y = local_30 - local_c;
        local_40.z = local_2c - local_8;
        local_24 = local_40.x * local_40.x + local_40.y * local_40.y + local_40.z * local_40.z;
        local_1c = local_40.x;
        local_18 = local_40.y;
        local_14 = local_40.z;
        if (local_24 < local_28 + local_8c) {
          p_Var7 = ptVar3->obj76;
          VVar1.y = local_40.y;
          VVar1.x = local_40.x;
          VVar1.z = local_40.z;
          local_20 = p_Var7;
          iVar4 = ZeroVector(VVar1);
          if (iVar4 == 0) {
            fVar9 = local_1c;
            fVar10 = local_18;
            fVar11 = local_14;
            dVar8 = rsqrt((double)local_24);
            VVar2.y = fVar10;
            VVar2.x = fVar9;
            VVar2.z = fVar11;
            pVVar6 = ScaleVector(&local_b0,-(float)dVar8,VVar2);
          }
          else {
            pVVar6 = &local_4c;
            local_4c.x = 0.0;
            local_4c.y = 0.0;
            local_4c.z = 1.0;
          }
          local_58 = 0;
          local_40.x = pVVar6->x;
          local_54 = 0;
          local_50 = 0;
          local_40.y = pVVar6->y;
          local_40.z = pVVar6->z;
          local_88.x = 0.0;
          local_88.y = 0.0;
          local_88.z = 0.0;
          pVVar6 = NegVector(&local_bc,*pVVar6);
          local_7c.x = pVVar6->x;
          local_7c.y = pVVar6->y;
          local_7c.z = pVVar6->z;
          pVVar6 = ScaleVector(local_a4,local_28,*pVVar6);
          local_7c.x = pVVar6->x;
          local_7c.y = pVVar6->y;
          local_7c.z = pVVar6->z;
          Damage_Resolve(p_Var7,param_2,&local_88,&local_40,&local_7c);
        }
      }
      ptVar3 = NextCollidable();
    }
  }
  return p_Var7;
}
