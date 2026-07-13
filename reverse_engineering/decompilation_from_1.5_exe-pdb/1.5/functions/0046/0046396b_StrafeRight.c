/*
 * Entry: 0046396b
 * Name: StrafeRight
 * Namespace: Global
 * Signature: void StrafeRight(ActionInfo * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl StrafeRight(ActionInfo *param_1)

{
  VEHICLE *pVVar1;
  
  pVVar1 = get_obj_vhcl(param_1->me);
  (pVVar1->control).braccel = 0.0;
  (pVVar1->control).steer = 0.0;
  (pVVar1->control).strafe = 1.0;
  return;
}
