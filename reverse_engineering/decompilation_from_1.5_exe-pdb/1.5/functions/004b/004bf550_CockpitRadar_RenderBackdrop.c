/*
 * Entry: 004bf550
 * Name: CockpitRadar::RenderBackdrop
 * Namespace: CockpitRadar
 * Signature: void RenderBackdrop(CockpitRadar * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CockpitRadar::RenderBackdrop(CockpitRadar *this)

{
  float fVar1;
  
  fVar1 = spriteZ;
  if (this->simulated != false) {
    if (useD3D != 0) {
      D3IniFlags = D3IniFlags | 0x800;
      spriteZ = spriteZ + 0.015;
      DrawSprite(DisplayInterface::currentBuffer,RADAR_BACKGROUND[2].index,RADAR_CENTER.x,
                 RADAR_CENTER.y + 10,0x60001);
      DrawSprite(DisplayInterface::currentBuffer,RADAR_BACKGROUND[3].index,RADAR_CENTER.x + -1,
                 RADAR_CENTER.y + 10,0x140001);
      spriteZ = fVar1;
      D3IniFlags = D3IniFlags & 0xfffff7ff;
      return;
    }
    if (400 < Device.Viewport.Width) {
      DrawSprite(DisplayInterface::currentBuffer,
                 RADAR_BACKGROUND[Device.Viewport.Width < 0x201].index,
                 RADAR_BACKGROUND_POS.x + RADAR_CENTER.x,RADAR_BACKGROUND_POS.y + RADAR_CENTER.y,1);
    }
  }
  return;
}
