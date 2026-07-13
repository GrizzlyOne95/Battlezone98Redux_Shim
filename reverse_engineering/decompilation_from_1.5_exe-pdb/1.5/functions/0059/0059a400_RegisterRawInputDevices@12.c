/*
 * Entry: 0059a400
 * Name: _RegisterRawInputDevices@12
 * Namespace: Global
 * Signature: BOOL _RegisterRawInputDevices@12(PCRAWINPUTDEVICE pRawInputDevices, UINT uiNumDevices, UINT cbSize)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _RegisterRawInputDevices_12(PCRAWINPUTDEVICE pRawInputDevices,UINT uiNumDevices,UINT cbSize)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a400. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = RegisterRawInputDevices(pRawInputDevices,uiNumDevices,cbSize);
  return BVar1;
}
