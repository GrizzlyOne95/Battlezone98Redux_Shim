/*
 * Entry: 004d4e79
 * Name: PathDisplay::DrawRegion
 * Namespace: PathDisplay
 * Signature: void DrawRegion(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::DrawRegion(PathDisplay *this)

{
  long lVar1;
  byte bVar2;
  int *piVar3;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int iVar4;
  float local_68 [2];
  float local_60;
  float local_5c [2];
  float local_54;
  VECTOR_3D local_50;
  float local_44;
  float local_3c;
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
  
  WireFrameColors[0] = DisplayInterface::colorBlack;
  WireFrameColors[1] = DisplayInterface::colorGrey;
  WireFrameColors[2] = DisplayInterface::colorBlue;
  WireFrameColors[3] = DisplayInterface::colorCyan;
  WireFrameColors[4] = DisplayInterface::colorGreen;
  WireFrameColors[5] = DisplayInterface::colorYellow;
  WireFrameColors[6] = DisplayInterface::colorRed;
  piVar3 = WireFrameColors + 7;
  do {
    iVar4 = 6;
    do {
      *piVar3 = piVar3[-6] + 1;
      piVar3 = piVar3 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  } while ((int)piVar3 < 0xcaef5c);
  GetTerrainExtents(&local_50);
  (**(code **)(this->_padding_ + 0x24))(0,0,local_68,&local_54);
  (**(code **)(this->_padding_ + 0x24))
            ((DisplayInterface::currentBuffer->Pane).x1 - (DisplayInterface::currentBuffer->Pane).x0
             ,(DisplayInterface::currentBuffer->Pane).y1 -
              (DisplayInterface::currentBuffer->Pane).y0,local_5c,&local_60);
  if (local_50.x < local_68[0]) {
    local_50.x = local_68[0];
  }
  if (local_50.z < local_60) {
    local_50.z = local_60;
  }
  if (local_5c[0] < local_44) {
    local_44 = local_5c[0];
  }
  if (local_54 < local_3c) {
    local_3c = local_54;
  }
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
          bVar2 = CellRegion(local_c,local_8);
          lVar1 = WireFrameColors[bVar2];
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
