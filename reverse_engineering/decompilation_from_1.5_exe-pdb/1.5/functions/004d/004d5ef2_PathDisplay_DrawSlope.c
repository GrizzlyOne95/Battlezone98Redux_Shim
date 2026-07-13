/*
 * Entry: 004d5ef2
 * Name: PathDisplay::DrawSlope
 * Namespace: PathDisplay
 * Signature: void DrawSlope(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::DrawSlope(PathDisplay *this)

{
  float fVar1;
  PathDisplay *pPVar2;
  long lVar3;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  VECTOR_3D local_5c [2];
  long local_44;
  long local_40;
  long local_3c;
  long local_38;
  float local_34;
  float local_30;
  PathDisplay *local_2c;
  float local_28;
  int local_24;
  int local_20;
  int local_1c;
  float local_18;
  float local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_2c = this;
  do {
    fVar1 = (float)local_8 * 0.0029411765 + 0.25;
    lVar3 = Get_Closest_RGB_Entry(fVar1,fVar1,fVar1);
    iVar8 = local_8 + 1;
    WireFrameColors[local_8] = lVar3;
    local_8 = iVar8;
  } while (iVar8 < 0x100);
  GetTerrainExtents(local_5c);
  _ftol2_sse();
  local_24 = extraout_EAX;
  _ftol2_sse();
  local_20 = extraout_EAX_00;
  _ftol2_sse();
  local_1c = extraout_EAX_01;
  _ftol2_sse();
  local_8 = extraout_EAX_02;
  if (extraout_EAX_02 < local_20) {
    do {
      if (local_24 < local_1c) {
        local_28 = (float)local_8;
        iVar8 = local_24;
        do {
          iVar6 = local_8;
          local_18 = local_28 * Terrain.Grid_Size;
          local_34 = local_18 + Terrain.Grid_Size;
          local_14 = (float)iVar8 * Terrain.Grid_Size;
          local_30 = Terrain.Grid_Size + local_14;
          iVar4 = GetTerY(local_8,iVar8);
          local_10 = GetTerY(iVar6 + 1,iVar8);
          iVar8 = iVar8 + 1;
          iVar5 = GetTerY(iVar6,iVar8);
          local_c = GetTerY(local_8 + 1,iVar8);
          pPVar2 = local_2c;
          uVar7 = iVar5 - iVar4 >> 0x1f;
          iVar6 = (iVar5 - iVar4 ^ uVar7) - uVar7;
          uVar7 = local_c - iVar5 >> 0x1f;
          iVar5 = (local_c - iVar5 ^ uVar7) - uVar7;
          if (iVar6 <= iVar5) {
            iVar6 = iVar5;
          }
          uVar7 = local_10 - local_c >> 0x1f;
          iVar5 = (local_10 - local_c ^ uVar7) - uVar7;
          uVar7 = iVar4 - local_10 >> 0x1f;
          iVar4 = (iVar4 - local_10 ^ uVar7) - uVar7;
          if (iVar4 < iVar5) {
            iVar4 = iVar5;
          }
          if (iVar6 <= iVar4) {
            iVar6 = iVar4;
          }
          iVar4 = 0xff;
          if (iVar6 < 0x100) {
            iVar4 = iVar6;
          }
          lVar3 = WireFrameColors[iVar4];
          (**(code **)(local_2c->_padding_ + 0x20))(local_18,local_14,&local_44,&local_38);
          (**(code **)(pPVar2->_padding_ + 0x20))(local_34,local_30,&local_3c,&local_40);
          Graphic_Rect_Filled(DisplayInterface::currentBuffer,local_44,local_40,local_3c,local_38,
                              lVar3,SOLID_PIXELS);
        } while (iVar8 < local_1c);
      }
      local_8 = local_8 + 1;
    } while (local_8 < local_20);
  }
  return;
}
