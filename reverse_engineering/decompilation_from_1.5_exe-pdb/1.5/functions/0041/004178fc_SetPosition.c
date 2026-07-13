/*
 * Entry: 004178fc
 * Name: SetPosition
 * Namespace: Global
 * Signature: void SetPosition(MAT_3D * param_1, double param_2, double param_3, double param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetPosition(MAT_3D *param_1,double param_2,double param_3,double param_4)

{
  undefined4 in_stack_00000008;
  
  param_1->posit_x = (double)CONCAT44(param_2._0_4_,in_stack_00000008);
  param_1->posit_y = (double)CONCAT44(param_3._0_4_,param_2._4_4_);
  param_1->posit_z = (double)CONCAT44(param_4._0_4_,param_3._4_4_);
  return;
}
