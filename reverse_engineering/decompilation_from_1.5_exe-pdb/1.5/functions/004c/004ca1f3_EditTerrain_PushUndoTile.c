/*
 * Entry: 004ca1f3
 * Name: EditTerrain::PushUndoTile
 * Namespace: EditTerrain
 * Signature: void PushUndoTile(EditTerrain * this, int param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::PushUndoTile(EditTerrain *this,int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  zoneDataChanged = 1;
  this->undoTile[this->undoEnd].undoX = (short)param_1;
  this->undoTile[this->undoEnd].undoZ = (short)param_2;
  this->undoTile[this->undoEnd].undoData = (short)param_3;
  this->undoCount = this->undoCount + 1;
  uVar1 = this->undoEnd + 1U & 0x7f;
  this->undoEnd = uVar1;
  if (0x7f < this->undoCount) {
    this->undoCount = 0x7f;
    this->undoStart = uVar1 + 1 & 0x7f;
  }
  return;
}
