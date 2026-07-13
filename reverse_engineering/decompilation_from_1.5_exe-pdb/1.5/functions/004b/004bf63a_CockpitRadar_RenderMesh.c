/*
 * Entry: 004bf63a
 * Name: CockpitRadar::RenderMesh
 * Namespace: CockpitRadar
 * Signature: void RenderMesh(CockpitRadar * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CockpitRadar::RenderMesh(CockpitRadar *this)

{
  float fVar1;
  
  fVar1 = spriteZ;
  if (this->simulated != false) {
    spriteZ = spriteZ + 0.01;
    Draw_RadarMesh(DisplayInterface::currentBuffer,&this->radarMesh);
    spriteZ = fVar1;
    this->simulated = false;
  }
  return;
}
