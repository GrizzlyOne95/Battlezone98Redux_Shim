/*
 * Entry: 005451ea
 * Name: Set_Render_State_Flags
 * Namespace: Global
 * Signature: void Set_Render_State_Flags(IDirect3DTexture9 * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Set_Render_State_Flags(IDirect3DTexture9 *param_1,long param_2)

{
  IDirect3DTexture9 *in_EAX;
  IDirect3DDevice9Vtbl *pIVar1;
  uint unaff_EBX;
  uint uVar2;
  _D3DRENDERSTATETYPE in_stack_ffffffd0;
  ulong in_stack_ffffffd4;
  
  Flush_Vertex_Buffer();
  if (in_EAX != lastEBHandle) {
    (*(d3dappi.lpD3DDevice)->lpVtbl->SetTexture)
              (d3dappi.lpD3DDevice,0,(IDirect3DBaseTexture9 *)in_EAX);
  }
  if (unaff_EBX == lastEBFlags) {
    lastEBFlags = unaff_EBX;
    lastEBHandle = in_EAX;
    return;
  }
  lastEBHandle = in_EAX;
  if (((lastEBFlags ^ unaff_EBX) & 0x10) != 0) {
    uVar2 = ~(unaff_EBX >> 3) & 2 | 1;
    (*(d3dappi.lpD3DDevice)->lpVtbl->SetSamplerState)(d3dappi.lpD3DDevice,0,D3DSAMP_ADDRESSU,uVar2);
    in_stack_ffffffd4 = 2;
    in_stack_ffffffd0 = 0;
    (*(d3dappi.lpD3DDevice)->lpVtbl->SetSamplerState)(d3dappi.lpD3DDevice,0,D3DSAMP_ADDRESSV,uVar2);
  }
  if (((lastEBFlags ^ unaff_EBX) & 0x20) != 0) {
    (*(d3dappi.lpD3DDevice)->lpVtbl->SetRenderState)
              (d3dappi.lpD3DDevice,D3DRS_FOGENABLE,unaff_EBX >> 5 & 1);
  }
  if (((lastEBFlags ^ unaff_EBX) & 0x40) != 0) {
    (*(d3dappi.lpD3DDevice)->lpVtbl->SetRenderState)
              (d3dappi.lpD3DDevice,D3DRS_ZWRITEENABLE,~(unaff_EBX >> 6) & 1);
  }
  if (((lastEBFlags ^ unaff_EBX) & 0xc) == 0) goto LAB_00545324;
  if (((unaff_EBX & 4) == 0) && ((D3IniFlags & 0x400U) == 0)) {
    pIVar1 = (d3dappi.lpD3DDevice)->lpVtbl;
    if ((unaff_EBX & 8) != 0) {
      (*pIVar1->SetRenderState)(d3dappi.lpD3DDevice,D3DRS_ALPHABLENDENABLE,1);
      (*(d3dappi.lpD3DDevice)->lpVtbl->SetRenderState)(d3dappi.lpD3DDevice,D3DRS_SRCBLEND,2);
      goto LAB_00545314;
    }
  }
  else {
    (*(d3dappi.lpD3DDevice)->lpVtbl->SetRenderState)(d3dappi.lpD3DDevice,D3DRS_ALPHABLENDENABLE,1);
    (*(d3dappi.lpD3DDevice)->lpVtbl->SetRenderState)(d3dappi.lpD3DDevice,D3DRS_SRCBLEND,5);
LAB_00545314:
    pIVar1 = (d3dappi.lpD3DDevice)->lpVtbl;
  }
  (*pIVar1->SetRenderState)(d3dappi.lpD3DDevice,in_stack_ffffffd0,in_stack_ffffffd4);
LAB_00545324:
  if ((unaff_EBX & 0x80) != (lastEBFlags & 0x80U)) {
    (*(d3dappi.lpD3DDevice)->lpVtbl->SetRenderState)
              (d3dappi.lpD3DDevice,D3DRS_MULTISAMPLEANTIALIAS,(uint)((unaff_EBX & 0x80) == 0));
  }
  lastEBFlags = unaff_EBX;
  return;
}
