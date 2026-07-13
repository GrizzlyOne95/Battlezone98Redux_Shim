/*
 * Entry: 00544c94
 * Name: D3DAppISelectDisplayMode
 * Namespace: Global
 * Signature: int D3DAppISelectDisplayMode(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl D3DAppISelectDisplayMode(void)

{
  _D3DDISPLAYMODE *p_Var1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  _D3DDISPLAYMODE local_28;
  uint local_18;
  uint local_14;
  int local_10;
  uint local_c;
  uint local_8;
  
  local_14 = *(uint *)(&DAT_0062da78 + ResolutionMode * 0x20);
  local_18 = *(uint *)(&DAT_0062da7c + ResolutionMode * 0x20);
  d3dappi.PixelFormat = GetBestPixelFormat();
  if (d3dappi.PixelFormat == D3DFMT_UNKNOWN) {
    D3DAppISetErrorString("No supported pixel format found.\n");
    iVar2 = 0;
  }
  else {
    d3dappi.DepthFormat = GetBestDepthFormat();
    if (d3dappi.DepthFormat == D3DFMT_UNKNOWN) {
      Trace("Create: z-buffer disabled\n");
      D3IniFlags = D3IniFlags & 0xfffffffe;
    }
    local_c = (*(d3dappi.lpD3D)->lpVtbl->GetAdapterModeCount)(d3dappi.lpD3D,0,d3dappi.PixelFormat);
    (*(d3dappi.lpD3D)->lpVtbl->GetAdapterDisplayMode)(d3dappi.lpD3D,0,&d3dappi.WindowsDisplay);
    d3dappi.CurrMode = 0;
    d3dappi.NumModes = 0;
    memset(0xc92654,0,0x800);
    local_8 = 0;
    if (0 < (int)local_c) {
      do {
        (*(d3dappi.lpD3D)->lpVtbl->EnumAdapterModes)
                  (d3dappi.lpD3D,0,d3dappi.PixelFormat,local_8,&local_28);
        if ((0x27f < local_28.Width) && (0x1df < local_28.Height)) {
          if ((0 < d3dappi.NumModes) &&
             ((d3dappi.Mode[d3dappi.NumModes + -1].Width == local_28.Width &&
              (d3dappi.Mode[d3dappi.NumModes + -1].Height == local_28.Height)))) {
            uVar3 = d3dappi.Mode[d3dappi.NumModes + -1].RefreshRate -
                    d3dappi.WindowsDisplay.RefreshRate;
            uVar4 = (int)uVar3 >> 0x1f;
            local_10 = (uVar3 ^ uVar4) - uVar4;
            uVar3 = (int)(local_28.RefreshRate - d3dappi.WindowsDisplay.RefreshRate) >> 0x1f;
            if (local_10 <=
                (int)((local_28.RefreshRate - d3dappi.WindowsDisplay.RefreshRate ^ uVar3) - uVar3))
            goto LAB_00544e05;
            d3dappi.NumModes = d3dappi.NumModes + -1;
          }
          iVar2 = d3dappi.NumModes;
          if (0x7f < d3dappi.NumModes) break;
          p_Var1 = d3dappi.Mode + d3dappi.NumModes;
          d3dappi.Mode[d3dappi.NumModes].Width = local_28.Width;
          p_Var1->Height = local_28.Height;
          d3dappi.Mode[iVar2].RefreshRate = local_28.RefreshRate;
          d3dappi.Mode[iVar2].Format = local_28.Format;
          if ((local_28.Width == local_14) && (local_28.Height == local_18)) {
            d3dappi.CurrMode = d3dappi.NumModes;
          }
          d3dappi.NumModes = d3dappi.NumModes + 1;
        }
LAB_00544e05:
        local_8 = local_8 + 1;
      } while ((int)local_8 < (int)local_c);
    }
    d3dappi.ThisMode.Width = d3dappi.Mode[d3dappi.CurrMode].Width;
    d3dappi.ThisMode.Height = d3dappi.Mode[d3dappi.CurrMode].Height;
    d3dappi.ThisMode.RefreshRate = d3dappi.Mode[d3dappi.CurrMode].RefreshRate;
    d3dappi.ThisMode.Format = d3dappi.Mode[d3dappi.CurrMode].Format;
    iVar2 = 1;
  }
  return iVar2;
}
