/*
 * Entry: 004ca83f
 * Name: EditTerrain::CreateWorldMap
 * Namespace: EditTerrain
 * Signature: void CreateWorldMap(EditTerrain * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::CreateWorldMap(EditTerrain *this)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uchar *puVar4;
  int iVar5;
  float fVar6;
  uchar uVar7;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int iVar8;
  int extraout_EAX_02;
  ushort *puVar9;
  uint extraout_EAX_03;
  float local_48;
  float local_44;
  float local_40;
  int local_20;
  int local_14;
  long lVar10;
  
  puVar4 = (this->gbMap).Buffer;
  GetTerrainExtents(this->worldExtents);
  piVar1 = &this->mapDX;
  this->worldDX = this->worldExtents[1].x - this->worldExtents[0].x;
  local_14 = 0;
  this->worldDY = this->worldExtents[1].y - this->worldExtents[0].y;
  this->worldDZ = this->worldExtents[1].z - this->worldExtents[0].z;
  if (0 < this->mapDY) {
    do {
      local_20 = 0;
      if (0 < *piVar1) {
        _ftol2_sse();
        _ftol2_sse();
        do {
          _ftol2_sse();
          iVar8 = local_20 + 1;
          _ftol2_sse();
          iVar3 = extraout_EAX;
          if (this->mapMaterials == 0) {
            for (; iVar2 = extraout_EAX_01, iVar3 < extraout_EAX_00; iVar3 = iVar3 + 1) {
              for (; iVar2 < extraout_EAX_02; iVar2 = iVar2 + 1) {
                GetZonePtr(iVar2,iVar3);
              }
            }
            _ftol2_sse();
            uVar7 = (uchar)WireFrameColors[extraout_EAX_03 & 0xff];
          }
          else {
            local_48 = 0.0;
            local_44 = 0.0;
            local_40 = 0.0;
            for (; iVar2 = extraout_EAX_01, iVar3 < extraout_EAX_00; iVar3 = iVar3 + 1) {
              for (; iVar2 < extraout_EAX_02; iVar2 = iVar2 + 1) {
                puVar9 = GetTilePtr(iVar2,iVar3);
                iVar5 = MaterialColors[*puVar9 >> 0xc];
                local_48 = Float_Pal[iVar5][0] + local_48;
                local_44 = Float_Pal[iVar5][1] + local_44;
                local_40 = Float_Pal[iVar5][2] + local_40;
              }
            }
            fVar6 = 1.0 / (float)((extraout_EAX_00 - extraout_EAX) *
                                 (extraout_EAX_02 - extraout_EAX_01));
            lVar10 = Get_Closest_RGB_Entry(local_48 * fVar6,fVar6 * local_44,fVar6 * local_40);
            uVar7 = (uchar)lVar10;
          }
          puVar4[((this->mapDY - local_14) + -1) * *piVar1 + local_20] = uVar7;
          local_20 = iVar8;
        } while (iVar8 < *piVar1);
      }
      local_14 = local_14 + 1;
    } while (local_14 < this->mapDY);
  }
  if (useD3D != 0) {
    D3D_Video_Memory_Is_Dirty = 1;
  }
  return;
}
