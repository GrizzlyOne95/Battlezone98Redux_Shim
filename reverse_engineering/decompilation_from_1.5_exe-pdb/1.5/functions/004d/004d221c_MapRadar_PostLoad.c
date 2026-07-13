/*
 * Entry: 004d221c
 * Name: MapRadar::PostLoad
 * Namespace: MapRadar
 * Signature: void PostLoad(MapRadar * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MapRadar::PostLoad(MapRadar *this)

{
  TEXTURE *pTVar1;
  float fVar2;
  
  stateColor[1] = DisplayInterface::colorWhite;
  stateColor[2] = DisplayInterface::colorYellow;
  stateColor[0] = DisplayInterface::colorRed;
  stateColor[4] = DisplayInterface::colorRed;
  stateColor[3] = DisplayInterface::colorGreen;
  stateColor[5] = DisplayInterface::colorGrey;
  fVar2 = max<float>(edgeMaxX - edgeMinX,edgeMaxZ - edgeMinZ);
  this->screenScale = 128.0 / fVar2;
  pTVar1 = malloc(0x4008);
  this->mapTexture = pTVar1;
  if ((pTVar1 == (TEXTURE *)0x0) || (0x7fe < spriteTableSize)) {
    this->mapIndex = 0;
  }
  else {
    pTVar1->type = 0;
    this->mapTexture->width = 0x80;
    this->mapTexture->height = 0x80;
    FillTerrainMap(this,this->mapTexture,((edgeMinX + edgeMaxX) - fVar2) * 0.5,
                   ((edgeMinZ + edgeMaxZ) - fVar2) * 0.5,(edgeMinX + edgeMaxX + fVar2) * 0.5,
                   (edgeMinZ + edgeMaxZ + fVar2) * 0.5);
    this->mapIndex = spriteTableSize;
    spriteTableSize = spriteTableSize + 1;
    spriteTable[this->mapIndex].texPtr = this->mapTexture;
    spriteTable[this->mapIndex].u = 0;
    spriteTable[this->mapIndex].v = 0;
    spriteTable[this->mapIndex].width = 0x80;
    spriteTable[this->mapIndex].height = 0x80;
    spriteTable[this->mapIndex].flags = 0;
  }
  return;
}
