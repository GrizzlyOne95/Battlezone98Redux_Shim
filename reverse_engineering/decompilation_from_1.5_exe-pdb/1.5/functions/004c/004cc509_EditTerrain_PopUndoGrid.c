/*
 * Entry: 004cc509
 * Name: EditTerrain::PopUndoGrid
 * Namespace: EditTerrain
 * Signature: void PopUndoGrid(EditTerrain * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::PopUndoGrid(EditTerrain *this)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  ushort *puVar4;
  <unnamed_type_undoTile> *p<Var5;
  
  while ((uVar2 = this->undoGEnd - 1U & 0x3fff, this->undoGCount != 0 &&
         (p<Var5 = this->undoGrid + uVar2, (p<Var5->undoX & 0x8000U) == 0))) {
    this->undoGCount = this->undoGCount + -1;
    this->undoGEnd = uVar2;
    uVar1 = this->undoGrid[uVar2].undoZ;
    if ((uVar1 & 0x8000) == 0) {
      puVar4 = GetZonePtr((int)p<Var5->undoX & 0x7fff,uVar1 & 0x7fff);
    }
    else {
      puVar4 = GetTilePtr((int)p<Var5->undoX & 0x7fff,uVar1 & 0x7fff);
    }
    *puVar4 = this->undoGrid[uVar2].undoData;
  }
  if (this->undoGCount != 0) {
    this->undoGEnd = uVar2;
    this->undoGCount = this->undoGCount + -1;
    uVar1 = this->undoGrid[uVar2].undoZ;
    uVar3 = (int)this->undoGrid[uVar2].undoX & 0x7fff;
    if ((uVar1 & 0x8000) == 0) {
      puVar4 = GetZonePtr(uVar3,uVar1 & 0x7fff);
    }
    else {
      puVar4 = GetTilePtr(uVar3,uVar1 & 0x7fff);
    }
    *puVar4 = this->undoGrid[uVar2].undoData;
  }
  return;
}
