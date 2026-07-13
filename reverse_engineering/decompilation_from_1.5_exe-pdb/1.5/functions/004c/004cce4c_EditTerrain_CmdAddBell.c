/*
 * Entry: 004cce4c
 * Name: EditTerrain::CmdAddBell
 * Namespace: EditTerrain
 * Signature: void CmdAddBell(EditTerrain * this, ushort * param_1, int param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
EditTerrain::CmdAddBell
          (EditTerrain *this,ushort *param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  ushort *puVar3;
  int extraout_EAX;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  if ((this->brushWidth < 1) && (this->brushDepth < 1)) {
    CmdAddFlat(this,param_1,param_2,param_3,param_4,0);
  }
  if (((this->brushSD != this->bellSD) || (this->bellWidth != this->brushWidth)) ||
     (this->bellDepth != this->brushDepth)) {
    CreateBell(this);
  }
  iVar7 = param_2 - this->brushWidth / 2;
  iVar4 = this->brushWidth + iVar7;
  iVar6 = param_3 - this->brushDepth / 2;
  iVar5 = this->brushDepth + iVar6;
  iVar1 = iVar6;
  if (param_5 != 0) {
    PushUndoGrid(this,param_2,param_3,(uint)*param_1,1,0);
  }
  for (; iVar2 = iVar7, iVar1 <= iVar5; iVar1 = iVar1 + 1) {
    for (; iVar2 <= iVar4; iVar2 = iVar2 + 1) {
      puVar3 = GetZonePtr(iVar2,iVar1);
      _ftol2_sse();
      param_5 = extraout_EAX;
      if (extraout_EAX < 0) {
        param_5 = 0;
      }
      if (0xfff < param_5) {
        param_5 = 0xfff;
      }
      if ((*puVar3 & 0xfff) != param_5) {
        PushUndoGrid(this,iVar2,iVar1,(uint)*puVar3,0,0);
        *puVar3 = (ushort)param_5;
      }
    }
  }
  RecomputeTerrainValues(iVar7 + -2,iVar6 + -2,iVar4 + 2,iVar5 + 2);
  return;
}
