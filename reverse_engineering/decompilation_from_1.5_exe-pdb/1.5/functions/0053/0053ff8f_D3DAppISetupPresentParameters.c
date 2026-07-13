/*
 * Entry: 0053ff8f
 * Name: D3DAppISetupPresentParameters
 * Namespace: Global
 * Signature: void D3DAppISetupPresentParameters(_D3DPRESENT_PARAMETERS_ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl D3DAppISetupPresentParameters(_D3DPRESENT_PARAMETERS_ *param_1)

{
  _D3DFORMAT _Var1;
  uint *unaff_ESI;
  
  memset();
  *unaff_ESI = d3dappi.ThisMode.Width;
  unaff_ESI[1] = d3dappi.ThisMode.Height;
  unaff_ESI[2] = d3dappi.ThisMode.Format;
  unaff_ESI[3] = ((D3IniFlags & 0x100U) != 0) + 1;
  if (ResolutionMode != 0) {
    unaff_ESI[4] = d3dappi.MultiSampleType;
    unaff_ESI[5] = d3dappi.MultiSampleQuality;
  }
  unaff_ESI[6] = 1;
  unaff_ESI[8] = d3dappi.bWindowed;
  if (ResolutionMode == 0) {
    unaff_ESI[0xb] = 1;
  }
  else if ((D3IniFlags & 1U) != 0) {
    unaff_ESI[9] = 1;
    _Var1 = d3dappi.DepthFormat;
    unaff_ESI[0xb] = unaff_ESI[0xb] | 2;
    unaff_ESI[10] = _Var1;
  }
  if (d3dappi.bWindowed == 0) {
    unaff_ESI[0xc] = d3dappi.ThisMode.RefreshRate;
  }
  if ((D3IniFlags & 0x100000U) == 0) {
    unaff_ESI[0xd] = 0x80000000;
  }
  return;
}
