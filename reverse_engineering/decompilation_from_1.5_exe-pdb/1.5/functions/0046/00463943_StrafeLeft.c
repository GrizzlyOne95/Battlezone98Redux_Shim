/*
 * Entry: 00463943
 * Name: StrafeLeft
 * Namespace: Global
 * Signature: void StrafeLeft(ActionInfo * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl StrafeLeft(ActionInfo *param_1)

{
  VEHICLE *pVVar1;
  
  pVVar1 = get_obj_vhcl(param_1->me);
  (pVVar1->control).braccel = 0.0;
  (pVVar1->control).steer = 0.0;
  (pVVar1->control).strafe = -1.0;
  return;
}
