/*
 * Entry: 004ca27b
 * Name: EditTerrain::PushUndoGrid
 * Namespace: EditTerrain
 * Signature: void PushUndoGrid(EditTerrain * this, int param_1, int param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
EditTerrain::PushUndoGrid
          (EditTerrain *this,int param_1,int param_2,int param_3,int param_4,int param_5)

{
  uint uVar1;
  
  zoneDataChanged = 1;
  if (param_4 != 0) {
    param_1._0_2_ = (ushort)param_1 | 0x8000;
  }
  if (param_5 != 0) {
    param_2._0_2_ = (ushort)param_2 | 0x8000;
  }
  this->undoGrid[this->undoGEnd].undoX = (ushort)param_1;
  this->undoGrid[this->undoGEnd].undoZ = (ushort)param_2;
  this->undoGrid[this->undoGEnd].undoData = (short)param_3;
  this->undoGCount = this->undoGCount + 1;
  uVar1 = this->undoGEnd + 1U & 0x3fff;
  this->undoGEnd = uVar1;
  if (0x3fff < this->undoGCount) {
    this->undoGCount = 0x3fff;
    this->undoGStart = uVar1 + 1 & 0x3fff;
  }
  return;
}
