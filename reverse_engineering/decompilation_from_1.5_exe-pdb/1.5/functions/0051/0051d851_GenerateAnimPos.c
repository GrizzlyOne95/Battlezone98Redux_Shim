/*
 * Entry: 0051d851
 * Name: GenerateAnimPos
 * Namespace: Global
 * Signature: int GenerateAnimPos(tagActiveAnim * param_1, CAMERA * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GenerateAnimPos(tagActiveAnim *param_1,CAMERA *param_2)

{
  int extraout_EAX;
  int extraout_EAX_00;
  ushort *puVar1;
  uint uVar2;
  float fVar3;
  int local_c;
  
  local_c = 0;
  while( true ) {
    rand();
    rand();
    _ftol2_sse();
    _ftol2_sse();
    puVar1 = GetTilePtr(extraout_EAX,extraout_EAX_00);
    uVar2 = (int)(uint)*puVar1 >> 0xc;
    if ((uVar2 == ((int)(uint)*puVar1 >> 8 & 0xfU)) && (0 < AnimSet[uVar2].anims)) break;
    local_c = local_c + 1;
    if (0xf < local_c) {
      return -1;
    }
  }
  param_1->x = ((float)extraout_EAX + 0.5) * Terrain.Grid_Size;
  fVar3 = ((float)extraout_EAX_00 + 0.5) * Terrain.Grid_Size;
  param_1->z = fVar3;
  fVar3 = Terrain_FindFloor((double)param_1->x,(double)fVar3);
  param_1->y = fVar3;
  return uVar2;
}
