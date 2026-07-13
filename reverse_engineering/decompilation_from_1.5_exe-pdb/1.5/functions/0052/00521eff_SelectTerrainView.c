/*
 * Entry: 00521eff
 * Name: SelectTerrainView
 * Namespace: Global
 * Signature: void SelectTerrainView(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SelectTerrainView(int param_1)

{
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int iVar1;
  tagTERRAIN_VIEW *ptVar2;
  tagTERRAIN_VIEW *ptVar3;
  
  if (1 < param_1) {
    if (param_1 < 4) {
      ptVar2 = &SateliteView;
      ptVar3 = &TerrainView;
      for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
        ptVar3->Visibility_Range = ptVar2->Visibility_Range;
        ptVar2 = (tagTERRAIN_VIEW *)&ptVar2->Flat_Range;
        ptVar3 = (tagTERRAIN_VIEW *)&ptVar3->Flat_Range;
      }
      iVar1 = SateliteView.Fog_End - SateliteView.Fog_Start;
      goto LAB_00521fa3;
    }
    if (param_1 == 10) {
      ptVar2 = &SateliteView;
      ptVar3 = &TerrainView;
      for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
        ptVar3->Visibility_Range = ptVar2->Visibility_Range;
        ptVar2 = (tagTERRAIN_VIEW *)&ptVar2->Flat_Range;
        ptVar3 = (tagTERRAIN_VIEW *)&ptVar3->Flat_Range;
      }
      TerrainView.Visibility_Range = 1000.0;
      iVar1 = SateliteView.Fog_End - SateliteView.Fog_Start;
      goto LAB_00521fa3;
    }
  }
  ptVar2 = &NormalView;
  ptVar3 = &TerrainView;
  for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
    ptVar3->Visibility_Range = ptVar2->Visibility_Range;
    ptVar2 = (tagTERRAIN_VIEW *)&ptVar2->Flat_Range;
    ptVar3 = (tagTERRAIN_VIEW *)&ptVar3->Flat_Range;
  }
  iVar1 = NormalView.Fog_End - NormalView.Fog_Start;
LAB_00521fa3:
  TerrainView.Fog_InvWidth = 1.0 / (float)iVar1;
  TerrainView.Current_View = param_1;
  TerrainVisibility2 = TerrainView.Visibility_Range * TerrainView.Visibility_Range;
  TerrainIntensity = TerrainView.Intensity;
  TerrainView.Intensity256 = TerrainView.Intensity * 0.00390625;
  FarClip = TerrainView.Visibility_Range;
  TerrainVisibilityRange = TerrainView.Visibility_Range;
  InitFogTable();
  if (TerrainEditMode == 0) {
    _ftol2_sse();
    mipDistance2[0] = extraout_EAX;
    _ftol2_sse();
    mipDistance2[1] = extraout_EAX_00;
    _ftol2_sse();
    mipDistance2[2] = extraout_EAX_01;
  }
  else {
    mipDistance2[0] = 0;
    mipDistance2[1] = 0;
    mipDistance2[2] = 0;
  }
  _ftol2_sse();
  mipDistance2[3] = extraout_EAX_02;
  return;
}
