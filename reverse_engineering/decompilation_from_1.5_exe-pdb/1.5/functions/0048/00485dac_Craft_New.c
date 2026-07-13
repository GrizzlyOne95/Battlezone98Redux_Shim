/*
 * Entry: 00485dac
 * Name: Craft_New
 * Namespace: Global
 * Signature: VEHICLE * Craft_New(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VEHICLE * __cdecl Craft_New(void)

{
  VEHICLE *pVVar1;
  
  pVVar1 = obj_class_alloc(0x11c);
  memset(pVVar1,0,0x11c);
  ClearCollision(&pVVar1->clsn_info);
  InitEuler(&pVVar1->euler);
  Euler_SetMass(&pVVar1->euler,1500.0,1500.0);
  (pVVar1->control).turbo = 0;
  (pVVar1->control).steer = 0.0;
  (pVVar1->control).jump = 0;
  (pVVar1->control).braccel = 0.0;
  (pVVar1->control).eject = 0;
  (pVVar1->control).deploy = 0;
  (pVVar1->control).abandon = 0;
  pVVar1->timer = 0.0;
  (pVVar1->center_of_mass).x = 0.0;
  (pVVar1->center_of_mass).y = 0.0;
  (pVVar1->center_of_mass).z = 0.0;
  pVVar1->eyepoint = (_OBJ76 *)0x0;
  pVVar1->shadow = (_OBJ76 *)0x0;
  pVVar1->flags = 0;
  pVVar1->subclass = (void *)0x0;
  pVVar1->net_player = 0;
  pVVar1->killed_by_player = 0;
  return pVVar1;
}
