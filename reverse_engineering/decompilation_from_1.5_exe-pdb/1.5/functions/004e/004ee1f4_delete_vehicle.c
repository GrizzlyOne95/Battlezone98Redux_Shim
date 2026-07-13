/*
 * Entry: 004ee1f4
 * Name: delete_vehicle
 * Namespace: Global
 * Signature: void delete_vehicle(VEHICLE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl delete_vehicle(VEHICLE *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x004ec905. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  free(param_1);
  return;
}
