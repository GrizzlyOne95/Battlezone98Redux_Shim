/*
 * Entry: 004d1453
 * Name: MapRadar::Cleanup
 * Namespace: MapRadar
 * Signature: void Cleanup(MapRadar * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MapRadar::Cleanup(MapRadar *this)

{
  if (this->mapTexture != (TEXTURE *)0x0) {
    free(this->mapTexture);
  }
  this->mapTexture = (TEXTURE *)0x0;
  this->mapIndex = 0;
  return;
}
