/*
 * Entry: 004ce165
 * Name: FireballEffect::Simulate
 * Namespace: FireballEffect
 * Signature: void Simulate(FireballEffect * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FireballEffect::Simulate(FireballEffect *this,float param_1)

{
  VECTOR_3D *pVVar1;
  Fireball *pFVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  VECTOR_3D_LONG VVar6;
  FireballEffect *pFVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  ushort uVar11;
  VECTOR_3D local_58;
  VECTOR_3D local_4c;
  float local_40;
  float local_3c;
  float local_38;
  VECTOR_3D local_34;
  VECTOR_3D local_28;
  VECTOR_3D local_1c;
  uint local_10;
  float local_c;
  FireballEffect *local_8;
  
  local_10 = this->indexFirst;
  local_8 = this;
  while (local_10 != this->indexLast) {
    uVar8 = local_10 + 1;
    pFVar2 = this->fireballList + local_10;
    local_10 = uVar8;
    if (0x1f < uVar8) {
      local_10 = 0;
    }
    pFVar2->radius = param_1 * this->fireballScale + pFVar2->radius;
    fVar3 = param_1 * this->fireballRate + pFVar2->frame;
    pFVar2->frame = fVar3;
    fVar4 = (float)(this->fireballTexture + this->fireballFrames);
    if (fVar4 < fVar3 == (fVar4 == fVar3)) {
      local_40 = (pFVar2->pos).x;
      local_3c = (pFVar2->pos).y;
      (pFVar2->vel).y = (pFVar2->vel).y - param_1 * 9.8;
      local_c = param_1;
      local_38 = (pFVar2->pos).z;
      VVar6.y = (double)local_3c;
      VVar6.x = (double)local_40;
      VVar6.z = (double)local_38;
      iVar9 = Terrain_GetIntersection(VVar6,pFVar2->vel,&local_c,&local_34);
      if (iVar9 == 0) {
        (pFVar2->pos).x = param_1 * (pFVar2->vel).x + (pFVar2->pos).x;
        (pFVar2->pos).y = (pFVar2->vel).y * param_1 + (pFVar2->pos).y;
        (pFVar2->pos).z = (pFVar2->vel).z * param_1 + (pFVar2->pos).z;
        fVar3 = pFVar2->emit + local_c;
        pFVar2->emit = fVar3;
        this = local_8;
        while (pFVar7 = local_8, local_8 = pFVar7, 0.0 < fVar3) {
          local_58.x = (pFVar2->pos).x - pFVar2->emit * (pFVar2->vel).x;
          local_58.y = (pFVar2->pos).y - (pFVar2->vel).y * pFVar2->emit;
          local_58.z = (pFVar2->pos).z - pFVar2->emit * (pFVar2->vel).z;
          uVar8 = (Rand_Counter + 1U & 0xff) + 1;
          uVar10 = (uVar8 & 0xff) + 1;
          local_4c.x = pFVar7->smokeInherit * (pFVar2->vel).x +
                       *(float *)(&DAT_00c9021c + uVar8 * 4) * pFVar7->smokeVariance;
          Rand_Counter = uVar10 & 0xff;
          local_4c.y = (pFVar2->vel).y * pFVar7->smokeInherit +
                       *(float *)(&DAT_00c9021c + uVar10 * 4) * pFVar7->smokeVariance;
          local_4c.z = (pFVar2->vel).z * pFVar7->smokeInherit +
                       Pseudo_Rand_Number[Rand_Counter] * pFVar7->smokeVariance;
          SmokeEffect::AddSmoke(&smokeEffect,pFVar7->smokeEmitter,&local_58,&local_4c,pFVar2->emit);
          pFVar2->emit = pFVar2->emit - pFVar7->smokePause;
          this = pFVar7;
          fVar3 = pFVar2->emit;
        }
      }
      else {
        pVVar1 = &pFVar2->vel;
        (pFVar2->pos).x = local_c * pVVar1->x + (pFVar2->pos).x;
        (pFVar2->pos).y = (pFVar2->vel).y * local_c + (pFVar2->pos).y;
        (pFVar2->pos).z = (pFVar2->vel).z * local_c + (pFVar2->pos).z;
        fVar3 = local_c + pFVar2->emit;
        pFVar2->emit = fVar3;
        uVar11 = (ushort)(0.0 < fVar3) << 8 | (ushort)NAN(fVar3) << 10;
        while (pFVar7 = local_8, (POPCOUNT((char)(uVar11 >> 8)) & 1U) != 0) {
          local_28.x = (pFVar2->pos).x - pFVar2->emit * pVVar1->x;
          local_28.y = (pFVar2->pos).y - (pFVar2->vel).y * pFVar2->emit;
          local_28.z = (pFVar2->pos).z - pFVar2->emit * (pFVar2->vel).z;
          uVar8 = (Rand_Counter + 1U & 0xff) + 1;
          uVar10 = (uVar8 & 0xff) + 1;
          local_1c.x = local_8->smokeInherit * pVVar1->x +
                       *(float *)(&DAT_00c9021c + uVar8 * 4) * local_8->smokeVariance;
          Rand_Counter = uVar10 & 0xff;
          local_1c.y = (pFVar2->vel).y * local_8->smokeInherit +
                       *(float *)(&DAT_00c9021c + uVar10 * 4) * local_8->smokeVariance;
          local_1c.z = (pFVar2->vel).z * local_8->smokeInherit +
                       Pseudo_Rand_Number[Rand_Counter] * local_8->smokeVariance;
          SmokeEffect::AddSmoke(&smokeEffect,local_8->smokeEmitter,&local_28,&local_1c,pFVar2->emit)
          ;
          pFVar2->emit = pFVar2->emit - pFVar7->smokePause;
          uVar11 = (ushort)(0.0 < pFVar2->emit) << 8 | (ushort)NAN(pFVar2->emit) << 10;
        }
        fVar3 = local_34.x * pVVar1->x + (pFVar2->vel).z * local_34.z + (pFVar2->vel).y * local_34.y
        ;
        fVar5 = pVVar1->x * 0.5 - local_34.x * fVar3;
        pVVar1->x = fVar5;
        fVar4 = (pFVar2->vel).y * 0.5 - local_34.y * fVar3;
        (pFVar2->vel).y = fVar4;
        fVar3 = (pFVar2->vel).z * 0.5 - local_34.z * fVar3;
        (pFVar2->vel).z = fVar3;
        local_c = param_1 - local_c;
        (pFVar2->pos).x = fVar5 * local_c + (pFVar2->pos).x;
        (pFVar2->pos).y = fVar4 * local_c + (pFVar2->pos).y;
        (pFVar2->pos).z = fVar3 * local_c + (pFVar2->pos).z;
        fVar3 = local_c + pFVar2->emit;
        pFVar2->emit = fVar3;
        this = local_8;
        while (pFVar7 = local_8, local_8 = pFVar7, 0.0 < fVar3) {
          local_28.x = (pFVar2->pos).x - pFVar2->emit * pVVar1->x;
          local_28.y = (pFVar2->pos).y - (pFVar2->vel).y * pFVar2->emit;
          local_28.z = (pFVar2->pos).z - pFVar2->emit * (pFVar2->vel).z;
          uVar8 = (Rand_Counter + 1U & 0xff) + 1;
          uVar10 = (uVar8 & 0xff) + 1;
          local_1c.x = pFVar7->smokeInherit * pVVar1->x +
                       *(float *)(&DAT_00c9021c + uVar8 * 4) * pFVar7->smokeVariance;
          Rand_Counter = uVar10 & 0xff;
          local_1c.y = (pFVar2->vel).y * pFVar7->smokeInherit +
                       *(float *)(&DAT_00c9021c + uVar10 * 4) * pFVar7->smokeVariance;
          local_1c.z = (pFVar2->vel).z * pFVar7->smokeInherit +
                       Pseudo_Rand_Number[Rand_Counter] * pFVar7->smokeVariance;
          SmokeEffect::AddSmoke(&smokeEffect,pFVar7->smokeEmitter,&local_28,&local_1c,pFVar2->emit);
          pFVar2->emit = pFVar2->emit - pFVar7->smokePause;
          this = pFVar7;
          fVar3 = pFVar2->emit;
        }
      }
    }
    else {
      this->indexFirst = this->indexFirst + 1;
      if (0x1f < (uint)this->indexFirst) {
        this->indexFirst = 0;
      }
    }
  }
  return;
}
