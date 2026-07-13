/*
 * Entry: 004d0d11
 * Name: LightningFeature::GenerateBoltSegs
 * Namespace: LightningFeature
 * Signature: void GenerateBoltSegs(LightningFeature * this, BoltEmitter * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall LightningFeature::GenerateBoltSegs(LightningFeature *this,BoltEmitter *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uchar uVar4;
  BoltSeg *pBVar5;
  BoltEmitter *pBVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  VECTOR_3D *pVVar11;
  uchar *puVar12;
  uint local_c;
  
  pBVar6 = param_1;
  uVar7 = rand();
  uVar8 = rand();
  fVar1 = (param_1->origin).y;
  fVar2 = param_1->ground;
  param_1->vertex[0].x = (param_1->origin).x;
  fVar1 = (fVar1 - fVar2) * 0.03125;
  param_1->vertex[0].y = (param_1->origin).y;
  param_1->vertex[0].z = (param_1->origin).z;
  local_c = 1;
  param_1->vertices = 1;
  param_1->segments = 0;
  if ((param_1->target == (_OBJ76 *)0x0) && (0x3fff < (int)uVar7)) {
    param_1->type = 1;
    GenerateBoltBranch(this,param_1,0,0x20,0,(uVar8 & 3) + 1,(uVar7 & 3) + 2,fVar1);
  }
  else {
    iVar9 = rand();
    iVar10 = rand();
    uVar4 = '\x01';
    param_1 = (BoltEmitter *)0x64;
    puVar12 = &pBVar6->segment[0].stop;
    pVVar11 = pBVar6->vertex;
    do {
      pVVar11 = pVVar11 + 1;
      fVar2 = -1.0;
      if ((local_c & iVar9 + uVar7 * 0x10000) != 0) {
        fVar2 = 1.0;
      }
      fVar3 = 1.0;
      if ((local_c & iVar10 + uVar8 * 0x10000) == 0) {
        fVar3 = -1.0;
      }
      local_c = local_c << 1;
      pVVar11->x = pVVar11[-1].x + fVar2;
      pVVar11->y = pVVar11[-1].y - fVar1;
      pVVar11->z = fVar3 + pVVar11[-1].z;
      *puVar12 = uVar4;
      pBVar5 = param_1->segment;
      ((BoltSeg *)(puVar12 + -1))->start = uVar4 + 0xff;
      puVar12[1] = 0x96 - (char)((int)((int)&((BoltEmitter *)(param_1->segment + -0xc))->type +
                                      ((int)param_1 >> 0x1f & 0x1fU)) >> 5);
      puVar12[2] = (uchar)BoltSet.color;
      pBVar6->segments = pBVar6->segments + 1;
      pBVar6->vertices = pBVar6->vertices + 1;
      uVar4 = uVar4 + '\x01';
      puVar12 = puVar12 + 4;
      param_1 = (BoltEmitter *)(pBVar5 + 0xd);
    } while ((int)(pBVar5 + 0xd) < 0xc80);
    pBVar6->type = 0;
  }
  return;
}
