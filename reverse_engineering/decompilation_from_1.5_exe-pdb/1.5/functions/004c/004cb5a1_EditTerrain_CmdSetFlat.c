/*
 * Entry: 004cb5a1
 * Name: EditTerrain::CmdSetFlat
 * Namespace: EditTerrain
 * Signature: void CmdSetFlat(EditTerrain * this, ushort * param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
EditTerrain::CmdSetFlat(EditTerrain *this,ushort *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  ushort *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  if ((this->brushWidth < 1) && (this->brushDepth < 1)) {
    if ((*param_1 & 0xfff) == this->eyedropGrid) {
      return;
    }
    PushUndoGrid(this,param_2,param_3,(uint)*param_1,param_4,0);
    *param_1 = (ushort)this->eyedropGrid;
    iVar7 = param_2;
    iVar6 = param_3;
    iVar4 = param_2;
    iVar5 = param_3;
  }
  else {
    iVar7 = param_2 - this->brushWidth / 2;
    iVar4 = this->brushWidth + iVar7;
    iVar6 = param_3 - this->brushDepth / 2;
    iVar5 = this->brushDepth + iVar6;
    iVar1 = iVar6;
    if (param_4 != 0) {
      PushUndoGrid(this,param_2,param_3,(uint)*param_1,1,0);
    }
    for (; iVar2 = iVar7, iVar1 <= iVar5; iVar1 = iVar1 + 1) {
      for (; iVar2 <= iVar4; iVar2 = iVar2 + 1) {
        puVar3 = GetZonePtr(iVar2,iVar1);
        if ((*puVar3 & 0xfff) != this->eyedropGrid) {
          PushUndoGrid(this,iVar2,iVar1,(uint)*puVar3,0,0);
          *puVar3 = (ushort)this->eyedropGrid;
        }
      }
    }
  }
  RecomputeTerrainValues(iVar7 + -2,iVar6 + -2,iVar4 + 2,iVar5 + 2);
  return;
}
