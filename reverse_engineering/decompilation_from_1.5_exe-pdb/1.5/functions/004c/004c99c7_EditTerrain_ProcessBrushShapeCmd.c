/*
 * Entry: 004c99c7
 * Name: EditTerrain::ProcessBrushShapeCmd
 * Namespace: EditTerrain
 * Signature: void ProcessBrushShapeCmd(EditTerrain * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::ProcessBrushShapeCmd(EditTerrain *this,int param_1)

{
  float fVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint local_8;
  
  iVar5 = 1;
  local_8 = (uint)(edit_controls.edit_lmouse != '\0');
  uVar3 = (uint)(edit_controls.edit_lmouse != '\0');
  if (edit_controls.edit_rmouse != '\0') {
    uVar3 = 0xffffffff;
    local_8 = 0xffffffff;
  }
  if (param_1 == 0xd) {
    piVar2 = &this->brushWidth;
  }
  else {
    if (param_1 == 0xe) {
      if (edit_controls.edit_shift != '\0') {
        local_8 = uVar3 * 10;
      }
      this->brushY = (float)(int)local_8 + this->brushY;
      if (this->brushY < 0.0) {
        this->brushY = 0.0;
      }
      if (this->brushY <= 409.5) {
        return;
      }
      this->brushY = 409.5;
      return;
    }
    iVar4 = iVar5;
    if (param_1 == 0xf) {
      do {
        if (this->brushInc <= brushIncValues[iVar4]) {
          iVar5 = iVar4 + uVar3;
          break;
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < 7);
      this->brushInc = brushIncValues[iVar5];
      return;
    }
    if (param_1 != 0x13) {
      if (param_1 != 0x14) {
        return;
      }
      fVar1 = (float)(int)local_8 * 0.05 + this->brushSD;
      this->brushSD = fVar1;
      if (fVar1 < 0.05) {
        this->brushSD = 0.05;
      }
      if (this->brushSD <= 1.0) {
        return;
      }
      this->brushSD = 1.0;
      return;
    }
    piVar2 = &this->brushDepth;
  }
  *piVar2 = *piVar2 + uVar3;
  if (*piVar2 < 0) {
    *piVar2 = 0;
  }
  if (0x3f < *piVar2) {
    *piVar2 = 0x3f;
  }
  return;
}
