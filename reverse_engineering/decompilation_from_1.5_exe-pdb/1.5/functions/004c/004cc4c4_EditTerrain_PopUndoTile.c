/*
 * Entry: 004cc4c4
 * Name: EditTerrain::PopUndoTile
 * Namespace: EditTerrain
 * Signature: void PopUndoTile(EditTerrain * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::PopUndoTile(EditTerrain *this)

{
  uint uVar1;
  ushort *puVar2;
  
  uVar1 = this->undoEnd - 1U & 0x7f;
  this->undoCount = this->undoCount + -1;
  this->undoEnd = uVar1;
  puVar2 = GetTilePtr((int)this->undoTile[uVar1].undoX,(int)this->undoTile[uVar1].undoZ);
  *puVar2 = this->undoTile[uVar1].undoData;
  return;
}
