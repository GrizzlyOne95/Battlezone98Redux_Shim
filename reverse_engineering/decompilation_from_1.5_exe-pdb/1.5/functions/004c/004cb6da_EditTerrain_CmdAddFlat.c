/*
 * Entry: 004cb6da
 * Name: EditTerrain::CmdAddFlat
 * Namespace: EditTerrain
 * Signature: void CmdAddFlat(EditTerrain * this, ushort * param_1, int param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
EditTerrain::CmdAddFlat
          (EditTerrain *this,ushort *param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  ushort *puVar5;
  int extraout_EAX;
  int extraout_EAX_00;
  int iVar6;
  
  if ((this->commandMenu->icon[this->commandDown].cmd == 0xc) ||
     ((this->brushWidth < 1 && (this->brushDepth < 1)))) {
    uVar2 = *param_1;
    _ftol2_sse();
    param_4 = extraout_EAX_00;
    if (extraout_EAX_00 < 0) {
      param_4 = 0;
    }
    if (0xfff < param_4) {
      param_4 = 0xfff;
    }
    if ((uVar2 & 0xfff) == param_4) {
      return;
    }
    PushUndoGrid(this,param_2,param_3,(uint)uVar2,param_5,0);
    *param_1 = (ushort)param_4;
    iVar6 = param_2;
    iVar1 = param_3;
  }
  else {
    iVar6 = this->brushWidth;
    param_2 = param_2 - iVar6 / 2;
    iVar6 = iVar6 + param_2;
    param_3 = param_3 - this->brushDepth / 2;
    iVar1 = this->brushDepth + param_3;
    iVar3 = param_3;
    if (param_5 != 0) {
      PushUndoGrid(this,param_2,param_3,(uint)*param_1,1,0);
    }
    for (; iVar4 = param_2, iVar3 <= iVar1; iVar3 = iVar3 + 1) {
      for (; iVar4 <= iVar6; iVar4 = iVar4 + 1) {
        puVar5 = GetZonePtr(iVar4,iVar3);
        _ftol2_sse();
        param_5 = extraout_EAX;
        if (extraout_EAX < 0) {
          param_5 = 0;
        }
        if (0xfff < param_5) {
          param_5 = 0xfff;
        }
        if ((*puVar5 & 0xfff) != param_5) {
          PushUndoGrid(this,iVar4,iVar3,(uint)*puVar5,0,0);
          *puVar5 = (ushort)param_5;
        }
      }
    }
  }
  RecomputeTerrainValues(param_2 + -2,param_3 + -2,iVar6 + 2,iVar1 + 2);
  return;
}
