/*
 * Entry: 0059a3f4
 * Name: _GetRawInputData@20
 * Namespace: Global
 * Signature: UINT _GetRawInputData@20(HRAWINPUT hRawInput, UINT uiCommand, LPVOID pData, PUINT pcbSize, UINT cbSizeHeader)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UINT _GetRawInputData_20(HRAWINPUT hRawInput,UINT uiCommand,LPVOID pData,PUINT pcbSize,
                        UINT cbSizeHeader)

{
  UINT UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a3f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = GetRawInputData(hRawInput,uiCommand,pData,pcbSize,cbSizeHeader);
  return UVar1;
}
