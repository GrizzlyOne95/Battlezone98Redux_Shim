/*
 * Entry: 0059a41e
 * Name: _MapVirtualKeyA@8
 * Namespace: Global
 * Signature: UINT _MapVirtualKeyA@8(UINT uCode, UINT uMapType)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UINT _MapVirtualKeyA_8(UINT uCode,UINT uMapType)

{
  UINT UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a41e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = MapVirtualKeyA(uCode,uMapType);
  return UVar1;
}
