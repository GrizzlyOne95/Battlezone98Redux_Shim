/*
 * Entry: 0054026a
 * Name: D3DAppISetRenderState
 * Namespace: Global
 * Signature: int D3DAppISetRenderState(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl D3DAppISetRenderState(void)

{
  uint uVar1;
  
  uVar1 = D3IniFlags & 1;
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetRenderState)(d3dappi.lpD3DDevice,D3DRS_SHADEMODE,2);
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetRenderState)(d3dappi.lpD3DDevice,D3DRS_ZENABLE,uVar1);
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetRenderState)(d3dappi.lpD3DDevice,D3DRS_ZWRITEENABLE,uVar1);
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetRenderState)(d3dappi.lpD3DDevice,D3DRS_ZFUNC,4);
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetRenderState)(d3dappi.lpD3DDevice,D3DRS_FILLMODE,3);
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetRenderState)(d3dappi.lpD3DDevice,D3DRS_DITHERENABLE,1);
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetRenderState)(d3dappi.lpD3DDevice,D3DRS_SPECULARENABLE,0);
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetRenderState)(d3dappi.lpD3DDevice,D3DRS_FOGENABLE,0);
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetRenderState)
            (d3dappi.lpD3DDevice,D3DRS_FOGCOLOR,d3dappi.fogColor);
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetRenderState)(d3dappi.lpD3DDevice,D3DRS_CULLMODE,1);
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetRenderState)(d3dappi.lpD3DDevice,D3DRS_ALPHABLENDENABLE,0);
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetRenderState)(d3dappi.lpD3DDevice,D3DRS_MULTISAMPLEANTIALIAS,1)
  ;
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetSamplerState)(d3dappi.lpD3DDevice,0,D3DSAMP_MAGFILTER,2);
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetSamplerState)(d3dappi.lpD3DDevice,0,D3DSAMP_MINFILTER,3);
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetSamplerState)(d3dappi.lpD3DDevice,0,D3DSAMP_MIPFILTER,2);
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetSamplerState)(d3dappi.lpD3DDevice,0,D3DSAMP_ADDRESSU,3);
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetSamplerState)(d3dappi.lpD3DDevice,0,D3DSAMP_ADDRESSV,3);
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetSamplerState)
            (d3dappi.lpD3DDevice,0,D3DSAMP_MAXANISOTROPY,d3dappi.MaxAnisotropy);
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetTextureStageState)(d3dappi.lpD3DDevice,0,D3DTSS_COLOROP,4);
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetTextureStageState)(d3dappi.lpD3DDevice,0,D3DTSS_COLORARG1,2);
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetTextureStageState)(d3dappi.lpD3DDevice,0,D3DTSS_COLORARG2,0);
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetTextureStageState)(d3dappi.lpD3DDevice,0,D3DTSS_ALPHAOP,4);
  return 1;
}
