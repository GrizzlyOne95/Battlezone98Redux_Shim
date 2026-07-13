/*
 * Entry: 004cc95b
 * Name: EditTerrain::Paste
 * Namespace: EditTerrain
 * Signature: void Paste(EditTerrain * this, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::Paste(EditTerrain *this,VECTOR_3D *param_1)

{
  ushort *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  VECTOR_3D *pVVar5;
  int iVar6;
  int iVar7;
  FLOAT2INT local_24;
  FLOAT2INT local_1c;
  short (*local_14) [64];
  short (*local_10) [64];
  int local_c;
  int local_8;
  
  if (((-1 < this->copyWidth) && (-1 < this->copyDepth)) && (TerrainWireFrame != 0)) {
    WorldToGrid(this,&local_24,&local_1c,param_1);
    pVVar5 = (VECTOR_3D *)(local_24.i - this->brushWidth / 2);
    local_c = (int)&pVVar5->x + this->brushWidth;
    iVar7 = 0;
    iVar4 = local_1c.i - this->brushDepth / 2;
    iVar6 = 1;
    local_24._4_4_ = this->brushDepth + iVar4;
    puVar1 = GetZonePtr((int)pVVar5,iVar4);
    PushUndoGrid(this,(int)pVVar5,iVar4,(uint)*puVar1,iVar6,iVar7);
    if (iVar4 <= (int)local_24._4_4_) {
      local_14 = this->copyGrid;
      local_8 = iVar4;
      do {
        if ((int)pVVar5 <= local_c) {
          local_10 = local_14;
          param_1 = pVVar5;
          do {
            local_1c._4_4_ = GetZonePtr((int)param_1,local_8);
            uVar2 = *(ushort *)local_1c._4_4_ & 0xfff;
            uVar3 = (int)(*local_10)[0] + uVar2;
            if ((int)uVar3 < 0) {
              uVar3 = 0;
            }
            if (0xfff < (int)uVar3) {
              uVar3 = 0xfff;
            }
            if (uVar2 != uVar3) {
              PushUndoGrid(this,(int)param_1,local_8,(uint)*(ushort *)local_1c._4_4_,0,0);
              *(ushort *)local_1c._4_4_ = (ushort)uVar3;
            }
            param_1 = (VECTOR_3D *)((int)&param_1->x + 1);
            local_10 = (short (*) [64])(*local_10 + 1);
          } while ((int)param_1 <= local_c);
        }
        local_8 = local_8 + 1;
        local_14 = local_14 + 1;
      } while (local_8 <= (int)local_24._4_4_);
    }
    local_8 = iVar4;
    if (iVar4 <= (int)local_24._4_4_) {
      local_14 = this->copyTile;
      do {
        if ((int)pVVar5 <= local_c) {
          local_10 = local_14;
          param_1 = pVVar5;
          do {
            local_1c._4_4_ = GetTilePtr((int)param_1,local_8);
            if ((*(ushort *)local_1c._4_4_ & 0xfff) != (*local_10)[0]) {
              PushUndoGrid(this,(int)param_1,local_8,(uint)*(ushort *)local_1c._4_4_,0,1);
              *(short *)local_1c._4_4_ = (*local_10)[0];
            }
            param_1 = (VECTOR_3D *)((int)&param_1->x + 1);
            local_10 = (short (*) [64])(*local_10 + 1);
          } while ((int)param_1 <= local_c);
        }
        local_8 = local_8 + 1;
        local_14 = local_14 + 1;
      } while (local_8 <= (int)local_24._4_4_);
    }
    RecomputeTerrainValues((int)((int)&pVVar5[-1].z + 2),iVar4 + -2,local_c + 2,local_24._4_4_ + 2);
  }
  return;
}
