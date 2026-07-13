/*
 * Entry: 004d752c
 * Name: PathDisplay::DrawColorLayer
 * Namespace: PathDisplay
 * Signature: void DrawColorLayer(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::DrawColorLayer(PathDisplay *this)

{
  uint uVar1;
  float fVar2;
  
  fVar2 = spriteZ;
  spriteZ = 100.0;
  uVar1 = this->colorMode;
  if ((uVar1 & 1) == 0) {
    if ((uVar1 & 0x10) == 0) {
      if ((uVar1 & 0x20) == 0) {
        if ((uVar1 & 0x40) == 0) {
          if ((char)uVar1 < '\0') {
            DrawCell(this);
          }
          else if ((uVar1 & 0x100) != 0) {
            DrawRegion(this);
          }
        }
        else {
          DrawSlope(this);
        }
      }
      else {
        DrawHeight(this);
      }
    }
    else {
      DrawSurface(this);
    }
  }
  else {
    DrawSlabs(this);
  }
  if ((this->colorMode & 2) != 0) {
    DrawGoals(this);
  }
  if ((this->colorMode & 4) != 0) {
    DrawPriorities(this);
  }
  if ((this->colorMode & 8) != 0) {
    DrawPaths(this,true);
  }
  spriteZ = fVar2;
  return;
}
