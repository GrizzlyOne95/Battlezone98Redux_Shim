/*
 * Entry: 004be9e6
 * Name: ChunkEffect::Simulate
 * Namespace: ChunkEffect
 * Signature: void Simulate(ChunkEffect * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ChunkEffect::Simulate(ChunkEffect *this,float param_1)

{
  float fVar1;
  _OBJ76 *p_Var2;
  VECTOR_3D_LONG VVar3;
  VECTOR_3D VVar4;
  float *pfVar5;
  MAT_3D *pMVar6;
  VECTOR_3D *pVVar7;
  uint uVar8;
  uint uVar9;
  ExplosionClass *this_00;
  int iVar10;
  Chunk *pCVar11;
  Chunk *pCVar12;
  MAT_3D *pMVar13;
  ushort uVar14;
  MAT_3D local_e0;
  VECTOR_3D local_a0;
  double local_94;
  double local_8c;
  double local_84;
  VECTOR_3D local_7c;
  VECTOR_3D local_70;
  VECTOR_3D local_64;
  VECTOR_3D local_58;
  VECTOR_3D local_4c;
  VECTOR_3D local_40;
  VECTOR_3D local_34;
  float local_28;
  int local_24;
  VECTOR_3D *local_20;
  float *local_1c;
  Chunk *local_18;
  _OBJ76 *local_14;
  float *local_10;
  float *local_c;
  VECTOR_3D *local_8;
  
  local_24 = 0;
  if (0 < this->chunkCount) {
    local_1c = &this->chunkList[0].timer;
    local_20 = &this->chunkList[0].omega;
    local_8 = (VECTOR_3D *)this->chunkList;
    local_10 = &this->chunkList[0].veloc.z;
    pCVar12 = this->chunkList;
    local_c = &this->chunkList[0].veloc.y;
    do {
      local_8 = (VECTOR_3D *)&local_8->z;
      p_Var2 = pCVar12->obj;
      local_94 = (p_Var2->transform).posit_x;
      local_8c = (p_Var2->transform).posit_y;
      local_84 = (p_Var2->transform).posit_z;
      local_18 = pCVar12;
      local_14 = p_Var2;
      if ((p_Var2->flags & 0x200) == 0) {
        pMVar6 = Spinner(&local_e0,&p_Var2->transform,*local_20,param_1);
        pMVar13 = &local_14->transform;
        for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
          pMVar13->right_x = pMVar6->right_x;
          pMVar6 = (MAT_3D *)&pMVar6->right_y;
          pMVar13 = (MAT_3D *)&pMVar13->right_y;
        }
        *local_c = *local_c - param_1 * 9.8;
        local_28 = param_1;
        VVar3.y._0_4_ = SUB84(local_8c,0);
        VVar3.x = local_94;
        VVar3.y._4_4_ = (int)((ulonglong)local_8c >> 0x20);
        VVar3.z._0_4_ = SUB84(local_84,0);
        VVar3.z._4_4_ = (int)((ulonglong)local_84 >> 0x20);
        iVar10 = Terrain_GetIntersection(VVar3,*local_8,&local_28,&local_34);
        p_Var2 = local_14;
        pfVar5 = local_1c;
        if (iVar10 == 0) {
          (local_14->transform).posit_x =
               (double)(param_1 * local_8->x + (float)(local_14->transform).posit_x);
          (local_14->transform).posit_y =
               (double)(param_1 * *local_c + (float)(local_14->transform).posit_y);
          (local_14->transform).posit_z =
               (double)(*local_10 * param_1 + (float)(local_14->transform).posit_z);
          if ((local_14->flags & 8) != 0) {
            fVar1 = param_1 + *local_1c;
            *local_1c = fVar1;
            while (0.0 < fVar1) {
              fVar1 = *pfVar5 - this->smokePause;
              *pfVar5 = fVar1;
              local_58.x = (float)(p_Var2->transform).posit_x - fVar1 * local_8->x;
              local_58.y = (float)(p_Var2->transform).posit_y - fVar1 * *local_c;
              local_58.z = (float)(p_Var2->transform).posit_z - fVar1 * *local_10;
              uVar8 = (Rand_Counter + 1U & 0xff) + 1;
              uVar9 = (uVar8 & 0xff) + 1;
              local_40.x = this->smokeInherit * local_8->x +
                           *(float *)(&DAT_00c9021c + uVar8 * 4) * this->smokeVariance;
              Rand_Counter = uVar9 & 0xff;
              local_40.y = *local_c * this->smokeInherit +
                           *(float *)(&DAT_00c9021c + uVar9 * 4) * this->smokeVariance;
              local_40.z = *local_10 * this->smokeInherit +
                           Pseudo_Rand_Number[Rand_Counter] * this->smokeVariance;
              SmokeEffect::AddSmoke(&smokeEffect,this->smokeEmitter,&local_58,&local_40,*pfVar5);
              fVar1 = *pfVar5;
            }
          }
        }
        else {
          (local_14->transform).posit_x =
               (double)(local_28 * local_8->x + (float)(local_14->transform).posit_x);
          (local_14->transform).posit_y =
               (double)(local_28 * *local_c + (float)(local_14->transform).posit_y);
          (local_14->transform).posit_z =
               (double)(*local_10 * local_28 + (float)(local_14->transform).posit_z);
          if ((local_14->flags & 8) != 0) {
            fVar1 = local_28 + *local_1c;
            *local_1c = fVar1;
            uVar14 = (ushort)(0.0 < fVar1) << 8 | (ushort)NAN(fVar1) << 10;
            while ((POPCOUNT((char)(uVar14 >> 8)) & 1U) != 0) {
              fVar1 = *pfVar5 - this->smokePause;
              *pfVar5 = fVar1;
              local_7c.x = (float)(p_Var2->transform).posit_x - fVar1 * local_8->x;
              local_7c.y = (float)(p_Var2->transform).posit_y - fVar1 * *local_c;
              local_7c.z = (float)(p_Var2->transform).posit_z - fVar1 * *local_10;
              uVar8 = (Rand_Counter + 1U & 0xff) + 1;
              uVar9 = (uVar8 & 0xff) + 1;
              local_4c.x = this->smokeInherit * local_8->x +
                           *(float *)(&DAT_00c9021c + uVar8 * 4) * this->smokeVariance;
              Rand_Counter = uVar9 & 0xff;
              local_4c.y = *local_c * this->smokeInherit +
                           *(float *)(&DAT_00c9021c + uVar9 * 4) * this->smokeVariance;
              local_4c.z = *local_10 * this->smokeInherit +
                           Pseudo_Rand_Number[Rand_Counter] * this->smokeVariance;
              SmokeEffect::AddSmoke(&smokeEffect,this->smokeEmitter,&local_7c,&local_4c,*pfVar5);
              uVar14 = (ushort)(0.0 < *pfVar5) << 8 | (ushort)NAN(*pfVar5) << 10;
            }
          }
          VVar4.y = local_34.y;
          VVar4.x = local_34.x;
          VVar4.z = local_34.z;
          pVVar7 = CombineVectors(&local_a0,0.25,*local_8,
                                  (local_8->z * local_34.z +
                                  local_34.x * local_8->x + local_8->y * local_34.y) * -0.5,VVar4);
          p_Var2 = local_14;
          pCVar12 = local_18;
          local_28 = param_1 - local_28;
          local_8->x = pVVar7->x;
          local_8->y = pVVar7->y;
          local_8->z = pVVar7->z;
          (local_14->transform).posit_x =
               (double)(local_28 * local_8->x + (float)(local_14->transform).posit_x);
          (local_14->transform).posit_y =
               (double)(local_8->y * local_28 + (float)(local_14->transform).posit_y);
          (local_14->transform).posit_z =
               (double)(local_8->z * local_28 + (float)(local_14->transform).posit_z);
          if ((local_14->flags & 8) != 0) {
            fVar1 = local_28 + local_18->timer;
            local_18->timer = fVar1;
            while (0.0 < fVar1) {
              fVar1 = pCVar12->timer - this->smokePause;
              pCVar12->timer = fVar1;
              local_70.x = (float)(p_Var2->transform).posit_x - fVar1 * local_8->x;
              local_70.y = (float)(p_Var2->transform).posit_y - fVar1 * local_8->y;
              local_70.z = (float)(p_Var2->transform).posit_z - fVar1 * local_8->z;
              uVar8 = (Rand_Counter + 1U & 0xff) + 1;
              uVar9 = (uVar8 & 0xff) + 1;
              local_64.x = this->smokeInherit * local_8->x +
                           *(float *)(&DAT_00c9021c + uVar8 * 4) * this->smokeVariance;
              Rand_Counter = uVar9 & 0xff;
              local_64.y = local_8->y * this->smokeInherit +
                           *(float *)(&DAT_00c9021c + uVar9 * 4) * this->smokeVariance;
              local_64.z = local_8->z * this->smokeInherit +
                           Pseudo_Rand_Number[Rand_Counter] * this->smokeVariance;
              SmokeEffect::AddSmoke
                        (&smokeEffect,this->smokeEmitter,&local_70,&local_64,pCVar12->timer);
              fVar1 = pCVar12->timer;
            }
          }
          if (ABS(local_8->y) < 0.5) {
            local_14->flags = local_14->flags | 0x200;
          }
        }
      }
      else {
        if ((((10.0 < (p_Var2->bSphere).radius) &&
             (this_00 = xplBuilding, xplBuilding != (ExplosionClass *)0x0)) ||
            ((2.0 < (p_Var2->bSphere).radius &&
             (this_00 = xplVehicle, xplVehicle != (ExplosionClass *)0x0)))) ||
           ((0.5 < (p_Var2->bSphere).radius &&
            (this_00 = xplSecondary, xplSecondary != (ExplosionClass *)0x0)))) {
          ExplosionClass::Build(this_00,&p_Var2->transform,(_OBJ76 *)0x0);
        }
        remove_obj(p_Var2,".\\fun3d\\ChunkEffect.cpp");
        this->chunkCount = this->chunkCount + -1;
        local_24 = local_24 + -1;
        local_18 = local_18 + -1;
        local_8 = (VECTOR_3D *)((int)local_8 + -0x20);
        local_c = local_c + -8;
        local_10 = local_10 + -8;
        local_20 = (VECTOR_3D *)&local_20[-3].y;
        local_1c = local_1c + -8;
        pCVar11 = this->chunkList + this->chunkCount;
        for (iVar10 = 8; iVar10 != 0; iVar10 = iVar10 + -1) {
          pCVar12->obj = pCVar11->obj;
          pCVar11 = (Chunk *)&pCVar11->timer;
          pCVar12 = (Chunk *)&pCVar12->timer;
        }
      }
      local_24 = local_24 + 1;
      pCVar12 = local_18 + 1;
      local_8 = local_8 + 2;
      local_c = local_c + 8;
      local_10 = local_10 + 8;
      local_20 = (VECTOR_3D *)&local_20[2].z;
      local_1c = local_1c + 8;
    } while (local_24 < this->chunkCount);
  }
  return;
}
