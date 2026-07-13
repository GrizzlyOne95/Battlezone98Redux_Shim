/*
 * Entry: 0048211b
 * Name: StopGASEvent
 * Namespace: Global
 * Signature: void StopGASEvent(_gas_object * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl StopGASEvent(_gas_object *param_1)

{
  if (param_1 != (_gas_object *)0x0) {
    DeleteGASObject(param_1);
    return;
  }
  return;
}
