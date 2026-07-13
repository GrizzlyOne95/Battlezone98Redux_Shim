/*
 * Entry: 0040859d
 * Name: UpdateCells
 * Namespace: Global
 * Signature: void UpdateCells(float param_1, float param_2, float param_3, float param_4, _func___cdecl_void_int_int_int * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
UpdateCells(float param_1,float param_2,float param_3,float param_4,
           _func___cdecl_void_int_int_int *param_5)

{
  float fVar1;
  float fVar2;
  int extraout_EAX;
  int iVar3;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int iVar4;
  int extraout_EAX_02;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  fVar2 = param_2;
  fVar1 = param_1;
  iVar6 = GridMinX;
  if (cellType != (uchar *)0x0) {
    if (param_3 < param_1) {
      param_1 = param_3;
      param_3 = fVar1;
    }
    if (param_4 < param_2) {
      param_2 = param_4;
      param_4 = fVar2;
    }
    iVar7 = GridMaxX - GridMinX;
    iVar4 = iVar7 + -1;
    iVar8 = 0;
    iVar3 = iVar4;
    floor((double)(Terrain.Grid_Scale * param_1));
    _ftol2_sse();
    iVar3 = Clamp(extraout_EAX - iVar6,iVar8,iVar3);
    iVar8 = 0;
    floor((double)(Terrain.Grid_Scale * param_3));
    _ftol2_sse();
    iVar8 = Clamp(extraout_EAX_00 - iVar6,iVar8,iVar4);
    iVar5 = (GridMaxZ - GridMinZ) + -1;
    iVar9 = 0;
    iVar4 = iVar5;
    floor((double)(Terrain.Grid_Scale * param_2));
    _ftol2_sse();
    iVar4 = Clamp(extraout_EAX_01 - GridMinZ,iVar9,iVar4);
    iVar9 = 0;
    floor((double)(Terrain.Grid_Scale * param_4));
    _ftol2_sse();
    iVar5 = Clamp(extraout_EAX_02 - GridMinZ,iVar9,iVar5);
    iVar7 = iVar7 * iVar4;
    for (; iVar9 = iVar3, iVar4 <= iVar5; iVar4 = iVar4 + 1) {
      for (; iVar9 <= iVar8; iVar9 = iVar9 + 1) {
        (*param_5)(iVar7 + iVar9,iVar6 + iVar9,GridMinZ + iVar4);
        iVar6 = GridMinX;
      }
      iVar7 = iVar7 + (GridMaxX - iVar6);
    }
    InvalidateStrips(param_1,param_2,param_3,param_4);
  }
  return;
}
