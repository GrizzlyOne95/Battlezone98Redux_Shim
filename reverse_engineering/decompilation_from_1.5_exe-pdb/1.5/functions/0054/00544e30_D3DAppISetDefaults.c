/*
 * Entry: 00544e30
 * Name: D3DAppISetDefaults
 * Namespace: Global
 * Signature: void D3DAppISetDefaults(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl D3DAppISetDefaults(void)

{
  memset(&d3dappi,0,0x9b8);
  bPrimaryPalettized = 0;
  bPaletteActivate = 0;
  bIgnoreWM_SIZE = 0;
  memset(ppe,0,0x400);
  memset(Originalppe,0,0x400);
  LastError = 0;
  memset(LastErrorString,0,0x100);
  return;
}
