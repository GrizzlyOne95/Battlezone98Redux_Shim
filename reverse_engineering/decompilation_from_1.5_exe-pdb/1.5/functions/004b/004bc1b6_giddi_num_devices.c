/*
 * Entry: 004bc1b6
 * Name: giddi_num_devices
 * Namespace: Global
 * Signature: UINT giddi_num_devices(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UINT giddi_num_devices(void)

{
  UINT UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004bc1b6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = joyGetNumDevs();
  return UVar1;
}
