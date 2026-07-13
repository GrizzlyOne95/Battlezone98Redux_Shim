/*
 * Entry: 0052fde6
 * Name: Grenade::Hit
 * Namespace: Grenade
 * Signature: void Hit(Grenade * this, GameObject * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Grenade::Hit(Grenade *this,GameObject *param_1,VECTOR_3D *param_2)

{
  double dVar1;
  double dVar2;
  int iVar3;
  VECTOR_3D VVar4;
  float fVar5;
  int local_8;
  
  iVar3 = *(int *)&this->field_0x18;
  fVar5 = Terrain_FindFloor(*(double *)(iVar3 + 0x48),*(double *)(iVar3 + 0x58));
  if ((float)*(double *)(iVar3 + 0x50) < fVar5 + 0.5) {
    *(double *)(iVar3 + 0x50) = (double)fVar5;
    local_8 = 0x14;
    dVar1 = *(double *)(iVar3 + 0x48);
    dVar2 = *(double *)(iVar3 + 0x58);
    do {
      VVar4.y = fVar5;
      VVar4.x = (float)dVar1;
      VVar4.z = (float)dVar2;
      ChunkEffect::CreateChunklet(&chunkEffect,VVar4,(VECTOR_3D)ZEXT812(0x4170000000000000),false);
      local_8 = local_8 + -1;
    } while (local_8 != 0);
    MakeCrater((float)*(double *)(iVar3 + 0x48),(float)*(double *)(iVar3 + 0x58),3.0);
  }
  Bullet::Hit((Bullet *)this,param_1,param_2);
  return;
}
