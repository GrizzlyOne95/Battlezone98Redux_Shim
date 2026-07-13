/*
 * Entry: 004d9898
 * Name: Reticle::FindGroundPos
 * Namespace: Reticle
 * Signature: VECTOR_3D * FindGroundPos(Reticle * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __thiscall Reticle::FindGroundPos(Reticle *this)

{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  VECTOR_3D_LONG VVar7;
  VECTOR_3D VVar8;
  int iVar9;
  float local_8;
  
  local_8 = 200.0;
  dVar4 = (this->sightMat).posit_x;
  dVar5 = (this->sightMat).posit_y;
  dVar6 = (this->sightMat).posit_z;
  VVar7.x = (this->sightMat).posit_x;
  VVar7.y = (this->sightMat).posit_y;
  VVar7.z = (this->sightMat).posit_z;
  fVar1 = (this->sightMat).front_x;
  fVar2 = (this->sightMat).front_y;
  fVar3 = (this->sightMat).front_z;
  VVar8.x = (this->sightMat).front_x;
  VVar8.y = (this->sightMat).front_y;
  VVar8.z = (this->sightMat).front_z;
  iVar9 = Terrain_GetIntersection(VVar7,VVar8,&local_8,(VECTOR_3D *)0x0);
  if (iVar9 != 0) {
    fVar1 = fVar1 * local_8 + (float)dVar4;
    (this->gPos).x = fVar1;
    (this->gPos).y = fVar2 * local_8 + (float)dVar5;
    fVar2 = fVar3 * local_8 + (float)dVar6;
    (this->gPos).z = fVar2;
    if ((((edgeMinX < fVar1) && (fVar1 < edgeMaxX)) && (edgeMinZ < fVar2)) && (fVar2 < edgeMaxZ)) {
      return &this->gPos;
    }
  }
  return (VECTOR_3D *)0x0;
}
