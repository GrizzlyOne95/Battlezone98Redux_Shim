/*
 * Entry: 004d0ad3
 * Name: LightningFeature::GenerateBoltBranch
 * Namespace: LightningFeature
 * Signature: void GenerateBoltBranch(LightningFeature * this, BoltEmitter * param_1, int param_2, int param_3, int param_4, int param_5, int param_6, float param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
LightningFeature::GenerateBoltBranch
          (LightningFeature *this,BoltEmitter *param_1,int param_2,int param_3,int param_4,
          int param_5,int param_6,float param_7)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  BoltEmitter *pBVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  VECTOR_3D *pVVar10;
  int iVar11;
  BoltSeg *local_c;
  
  pBVar5 = param_1;
  if ((((0 < param_6) && (param_1->segments < 0x100)) && (param_1->vertices < 0x100)) &&
     ((param_1->segments + param_3 < 0x100 && (param_1->vertices + param_3 < 0xff)))) {
    iVar6 = rand();
    rand();
    fVar1 = param_1->nx;
    fVar2 = param_1->nz;
    pVVar10 = param_1->vertex + param_1->vertices;
    local_c = param_1->segment + param_1->segments;
    param_1 = (BoltEmitter *)0x1;
    iVar7 = rand();
    uVar8 = iVar7 + iVar6 * 0x10000;
    rand();
    pVVar10->x = pBVar5->vertex[param_2].x;
    pVVar10->y = pBVar5->vertex[param_2].y;
    pVVar10->z = pBVar5->vertex[param_2].z;
    iVar6 = pBVar5->vertices;
    pBVar5->vertices = iVar6 + 1;
    if (1 < param_3) {
      param_2 = param_3 + -1;
      do {
        fVar3 = fVar2;
        fVar4 = fVar1;
        if ((param_4 < 1) && (fVar3 = 0.0, fVar4 = 0.0, param_4 < 0)) {
          fVar3 = -fVar2;
          fVar4 = -fVar1;
        }
        if ((param_4 < 1) || (((uint)param_1 & uVar8) == 0)) {
          if ((-1 < param_4) || (((uint)param_1 & uVar8) == 0)) {
            if (param_4 != 0) goto LAB_004d0c16;
            if (((uint)param_1 & uVar8) != 0) goto LAB_004d0c04;
          }
          fVar4 = fVar4 - fVar1;
          fVar3 = fVar3 - fVar2;
        }
        else {
LAB_004d0c04:
          fVar4 = fVar4 + fVar1;
          fVar3 = fVar3 + fVar2;
        }
LAB_004d0c16:
        param_1 = (BoltEmitter *)((int)param_1 << 1);
        pVVar10[1].x = pVVar10->x + fVar4;
        pVVar10[1].y = pVVar10->y - param_7;
        pVVar10[1].z = fVar3 + pVVar10->z;
        local_c->start = (char)pBVar5->vertices + 0xff;
        local_c->stop = (uchar)pBVar5->vertices;
        local_c->width = '2';
        local_c->color = (uchar)BoltSet.color;
        pBVar5->segments = pBVar5->segments + 1;
        pBVar5->vertices = pBVar5->vertices + 1;
        local_c = local_c + 1;
        param_2 = param_2 + -1;
        pVVar10 = pVVar10 + 1;
      } while (param_2 != 0);
    }
    if ((1 < param_6) && (0 < param_5)) {
      iVar7 = param_6 + -1;
      param_6 = param_3;
      param_1 = (BoltEmitter *)param_5;
      do {
        uVar8 = rand();
        iVar11 = param_6 / (param_5 + 1) + iVar6;
        iVar9 = (iVar6 - iVar11) + param_3;
        GenerateBoltBranch(this,pBVar5,iVar11,
                           ((int)(iVar9 + (iVar9 >> 0x1f & 3U)) >> 2) +
                           ((int)(uVar8 * param_3) >> 0x10),
                           ~-(uint)(param_4 != 0) & (uint)((uVar8 & 1) == 0) * 2 - 1,(uVar8 & 3) + 2
                           ,iVar7,param_7);
        param_6 = param_6 + param_3;
        param_1 = (BoltEmitter *)((int)&param_1[-1].target + 3);
      } while (param_1 != (BoltEmitter *)0x0);
    }
  }
  return;
}
