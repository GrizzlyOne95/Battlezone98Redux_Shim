/*
 * Entry: 004d5dd0
 * Name: PathDisplay::DrawSurface
 * Namespace: PathDisplay
 * Signature: void DrawSurface(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::DrawSurface(PathDisplay *this)

{
  long lVar1;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  ushort *puVar2;
  VECTOR_3D local_50 [2];
  long local_38;
  long local_34;
  long local_30;
  long local_2c;
  float local_28;
  float local_24;
  float local_20;
  int local_1c;
  int local_18;
  float local_14;
  float local_10;
  int local_c;
  int local_8;
  
  GetTerrainExtents(local_50);
  _ftol2_sse();
  local_1c = extraout_EAX;
  _ftol2_sse();
  local_18 = extraout_EAX_00;
  _ftol2_sse();
  _ftol2_sse();
  local_c = extraout_EAX_02;
  if (extraout_EAX_02 < local_18) {
    do {
      local_8 = local_1c;
      if (local_1c < extraout_EAX_01) {
        local_20 = (float)local_c;
        do {
          local_14 = local_20 * Terrain.Grid_Size;
          local_28 = local_14 + Terrain.Grid_Size;
          local_10 = (float)local_8 * Terrain.Grid_Size;
          local_24 = Terrain.Grid_Size + local_10;
          puVar2 = GetTilePtr(local_c,local_8);
          lVar1 = MaterialColors[*puVar2 >> 0xc];
          (**(code **)(this->_padding_ + 0x20))(local_14,local_10,&local_38,&local_2c);
          (**(code **)(this->_padding_ + 0x20))(local_28,local_24,&local_30,&local_34);
          Graphic_Rect_Filled(DisplayInterface::currentBuffer,local_38,local_34,local_30,local_2c,
                              lVar1,SOLID_PIXELS);
          local_8 = local_8 + 1;
        } while (local_8 < extraout_EAX_01);
      }
      local_c = local_c + 1;
    } while (local_c < local_18);
  }
  return;
}
