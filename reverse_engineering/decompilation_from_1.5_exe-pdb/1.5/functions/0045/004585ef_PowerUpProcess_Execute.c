/*
 * Entry: 004585ef
 * Name: PowerUpProcess::Execute
 * Namespace: PowerUpProcess
 * Signature: void Execute(PowerUpProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PowerUpProcess::Execute(PowerUpProcess *this)

{
  float fVar1;
  double dVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  float fVar7;
  int iVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  double dVar12;
  float local_20;
  float local_8;
  
  iVar3 = *(int *)&this->field_0xc;
  if (*(int *)(iVar3 + 0xb0) == 0) {
    *(undefined4 *)&this->field_0x10 = 1;
  }
  else {
    uVar4 = *(uint *)(*(int *)(iVar3 + 0x220) + 0x10c);
    if ((uVar4 & 1) == 0) {
      if ((uVar4 & 4) == 0) {
        *(undefined4 *)&this->field_0x10 = 1;
        iVar3 = *(int *)(iVar3 + 0x220);
        *(undefined4 *)(iVar3 + 0xd0) = 0;
        *(undefined4 *)(iVar3 + 0xcc) = 0;
        *(undefined4 *)(iVar3 + 0xc4) = 0;
        *(undefined4 *)(iVar3 + 200) = 0;
      }
    }
    else {
      iVar5 = *(int *)(iVar3 + 0x220);
      iVar6 = *(int *)(iVar3 + 0xe8);
      dVar12 = ((VECTOR_3D_LONG *)(iVar6 + 0x48))->x;
      iVar8 = *(int *)(*(int *)(iVar3 + 0xb8) + 8);
      dVar2 = *(double *)(iVar6 + 0x58);
      local_20 = *(float *)(iVar8 + 8);
      fVar11 = *(float *)(iVar8 + 0xc);
      local_8 = 10.0;
      iVar8 = Terrain_GetIntersection
                        (*(VECTOR_3D_LONG *)(iVar6 + 0x48),*(VECTOR_3D *)(iVar3 + 0x120),&local_8,
                         (VECTOR_3D *)0x0);
      if (iVar8 == 0) {
        fVar10 = (float)dVar12;
        fVar1 = (float)dVar2;
      }
      else {
        fVar10 = ((VECTOR_3D *)(iVar3 + 0x120))->x * local_8 + (float)dVar12;
        fVar1 = *(float *)(iVar3 + 0x128) * local_8 + (float)dVar2;
      }
      local_20 = local_20 - fVar10;
      fVar11 = fVar11 - fVar1;
      fVar7 = *(float *)(iVar6 + 0x20) * local_20 + *(float *)(iVar6 + 0x28) * fVar11;
      fVar10 = *(float *)(iVar6 + 0x40);
      fVar1 = *(float *)(iVar6 + 0x38);
      fVar9 = Clamp(fVar7 * 0.2,-1.0,1.0);
      *(float *)(iVar5 + 0xcc) = fVar9;
      fVar10 = Clamp((fVar1 * local_20 + fVar10 * fVar11) * 0.2,-1.0,1.0);
      *(float *)(iVar5 + 0xd0) = fVar10;
      dVar12 = rsqrt((double)(local_20 * local_20 + fVar11 * fVar11 + 0.0001));
      fVar11 = Clamp((float)dVar12 * fVar7 * 5.0 - *(float *)(*(int *)&this->field_0xc + 0x130),-1.0
                     ,1.0);
      *(float *)(iVar5 + 0xc4) = fVar11;
    }
  }
  return;
}
