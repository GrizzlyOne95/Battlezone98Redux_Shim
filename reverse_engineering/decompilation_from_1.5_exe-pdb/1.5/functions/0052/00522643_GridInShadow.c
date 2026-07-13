/*
 * Entry: 00522643
 * Name: GridInShadow
 * Namespace: Global
 * Signature: int GridInShadow(int param_1, float param_2, int param_3, double param_4, double param_5, int param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
GridInShadow(int param_1,float param_2,int param_3,double param_4,double param_5,int param_6)

{
  int iVar1;
  int iVar2;
  float fVar3;
  undefined4 in_stack_00000010;
  int local_10;
  int local_8;
  
  if (param_5._4_4_ == 0.0) {
    local_10 = SUB84((double)((41.0 - param_2) *
                              (float)(double)CONCAT44(param_5._0_4_,param_4._4_4_) + (float)param_1
                             + (float)Float2Int),0);
    local_8 = local_10;
    if (GridMaxX < local_10) {
      local_8 = GridMaxX;
    }
    iVar2 = 1;
    iVar1 = param_1 + 1;
    while (iVar1 <= local_8) {
      local_10 = SUB84((double)iVar2 * (double)CONCAT44(param_4._0_4_,in_stack_00000010) + Float2Int
                       ,0);
      iVar1 = local_10 + param_3;
      if (GridMaxZ < iVar1) {
        return 0;
      }
      param_5._4_4_ = GetTerrainHeight(iVar2 + param_1,iVar1);
      fVar3 = GetTerrainHeight(iVar2 + param_1,iVar1 + 1);
      if (param_5._4_4_ < fVar3) {
        param_5._4_4_ = fVar3;
      }
      if ((0.0 < param_5._4_4_ - param_2) &&
         (SQRT((float)(local_10 * local_10 + iVar2 * iVar2)) *
          (float)(double)CONCAT44(param_5._0_4_,param_4._4_4_) < param_5._4_4_ - param_2)) {
        return 1;
      }
      iVar2 = iVar2 + 1;
      iVar1 = iVar2 + param_1;
    }
  }
  return 0;
}
