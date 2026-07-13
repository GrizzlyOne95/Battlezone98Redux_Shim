/*
 * Entry: 004bf7fc
 * Name: CockpitRadar::PostLoad
 * Namespace: CockpitRadar
 * Signature: void PostLoad(CockpitRadar * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CockpitRadar::PostLoad(CockpitRadar *this)

{
  long lVar1;
  uint uVar2;
  
  UpdateRadarData(Device.Viewport.Height);
  lVar1 = DisplayInterface::colorGreen;
  stateColor[1] = DisplayInterface::colorWhite;
  stateColor[0] = DisplayInterface::colorRed;
  stateColor[4] = DisplayInterface::colorRed;
  stateColor[2] = DisplayInterface::colorYellow;
  stateColor[5] = DisplayInterface::colorGrey;
  stateColor[3] = DisplayInterface::colorGreen;
  uVar2 = 0;
  do {
    *(uint *)((int)&RADAR_PING[0].color + uVar2) =
         (uint)DisplayInterface::colorRamp[*(int *)((int)&RADAR_PING[0].bright + uVar2)][lVar1];
    uVar2 = uVar2 + 0x10;
  } while (uVar2 < 0xe0);
  return;
}
