/*
 * Entry: 0040b159
 * Name: FindRects
 * Namespace: Global
 * Signature: void FindRects(bool param_1, double param_2, double param_3, double param_4, double param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FindRects(bool param_1,double param_2,double param_3,double param_4,double param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int in_stack_00000008;
  undefined4 local_8;
  
  iVar2 = gridRows;
  iVar1 = gridColumns;
  in_stack_00000008 = SUB84((double)CONCAT44(param_2._0_4_,in_stack_00000008) + Float2Int,0);
  local_8 = (in_stack_00000008 - gridLeft) / gridScale;
  in_stack_00000008 = SUB84((double)CONCAT44(param_3._0_4_,param_2._4_4_) + Float2Int,0);
  param_2._4_4_ = SUB84((double)CONCAT44(param_4._0_4_,param_3._4_4_) + Float2Int,0);
  param_3._4_4_ = SUB84(Float2Int + (double)CONCAT44(param_5._0_4_,param_4._4_4_),0);
  param_2._0_4_ = (in_stack_00000008 - gridTop) / gridScale;
  param_3._0_4_ = ((gridScale - gridLeft) + -1 + param_2._4_4_) / gridScale;
  iVar3 = ((gridScale - gridTop) + -1 + param_3._4_4_) / gridScale;
  if (local_8 < 0) {
    local_8 = 0;
  }
  if (param_2._0_4_ < 0) {
    param_2._0_4_ = 0;
  }
  if (gridColumns < param_3._0_4_) {
    param_3._0_4_ = gridColumns;
  }
  if (gridRows < iVar3) {
    iVar3 = gridRows;
  }
  rectCount = 0;
  if (param_1) {
    AddRect(local_8,param_2._0_4_,param_3._0_4_,iVar3);
  }
  else {
    AddRect(0,0,gridColumns,param_2._0_4_);
    AddRect(0,iVar3,iVar1,iVar2);
    AddRect(0,param_2._0_4_,local_8,iVar3);
    AddRect(param_3._0_4_,param_2._0_4_,iVar1,iVar3);
  }
  return;
}
