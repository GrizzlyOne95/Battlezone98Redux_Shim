/*
 * Entry: 0051ea2e
 * Name: Terrain_FindFloor
 * Namespace: Global
 * Signature: float Terrain_FindFloor(double param_1, double param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Terrain_FindFloor(double param_1,double param_2)

{
  long lVar1;
  long lVar2;
  long lVar3;
  int iVar4;
  long unaff_ESI;
  int iVar5;
  int unaff_EDI;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float10 fVar6;
  float10 extraout_ST1;
  float10 extraout_ST1_00;
  float10 extraout_ST1_01;
  float10 fVar7;
  
  Set_Rounding(unaff_EDI);
  Set_Rounding(unaff_EDI);
  lVar1 = Terrain_Get_Height(unaff_EDI,unaff_ESI);
  lVar2 = Terrain_Get_Height(unaff_EDI,unaff_ESI);
  if (extraout_ST0 <= extraout_ST1) {
    lVar3 = Terrain_Get_Height(unaff_EDI,unaff_ESI);
    iVar4 = lVar1 - lVar3;
    iVar5 = lVar3 - lVar2;
    fVar6 = extraout_ST0_01;
    fVar7 = extraout_ST1_01;
  }
  else {
    lVar3 = Terrain_Get_Height(unaff_EDI,unaff_ESI);
    iVar4 = lVar3 - lVar2;
    iVar5 = lVar1 - lVar3;
    fVar6 = extraout_ST0_00;
    fVar7 = extraout_ST1_00;
  }
  return (float)(((float10)lVar1 - ((float10)iVar5 * fVar6 + (float10)iVar4 * fVar7)) * (float10)0.1
                );
}
