/*
 * Entry: 005463ef
 * Name: CalibrateOcclusionQuery
 * Namespace: Global
 * Signature: void CalibrateOcclusionQuery(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CalibrateOcclusionQuery(void)

{
  VECTOR_3D local_34;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_34.x = 0.0;
  local_34.y = 0.0;
  local_34.z = 1.0;
  local_28 = 0x3f800000;
  local_20 = 0x3f800000;
  local_1c = 0x3f800000;
  local_18 = 0x3f800000;
  local_14 = 0x3f800000;
  local_c = 0x3f800000;
  local_8 = 0x3f800000;
  local_24 = 0;
  local_10 = 0;
  if ((ResolutionMode != 0) && (((byte)D3IniFlags & 1) != 0)) {
    (*(d3dappi.lpD3DDevice)->lpVtbl->Clear)(d3dappi.lpD3DDevice,0,(_D3DRECT *)0x0,2,0,1.0,0);
  }
  (*(d3dappi.lpD3DDevice)->lpVtbl->BeginScene)(d3dappi.lpD3DDevice);
  gD3DEB.nQueryScale = 1;
  gD3DEB.nQueryScale = D3D_Occlusion_Query(&local_34,4);
  (*(d3dappi.lpD3DDevice)->lpVtbl->EndScene)(d3dappi.lpD3DDevice);
  return;
}
