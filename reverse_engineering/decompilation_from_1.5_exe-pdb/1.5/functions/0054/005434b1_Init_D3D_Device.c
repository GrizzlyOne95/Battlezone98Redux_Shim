/*
 * Entry: 005434b1
 * Name: Init_D3D_Device
 * Namespace: Global
 * Signature: int Init_D3D_Device(VIDEO_DEVICE * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Init_D3D_Device(VIDEO_DEVICE *param_1,char *param_2)

{
  tagRECT *lpRect;
  long *plVar1;
  long lVar2;
  DWORD dwStyle;
  uint uVar3;
  uint uVar4;
  UINT UVar5;
  UINT UVar6;
  UINT UVar7;
  UINT UVar8;
  UINT UVar9;
  UINT UVar10;
  UINT UVar11;
  UINT UVar12;
  UINT UVar13;
  UINT UVar14;
  UINT UVar15;
  UINT UVar16;
  UINT UVar17;
  UINT UVar18;
  UINT UVar19;
  UINT UVar20;
  UINT UVar21;
  UINT UVar22;
  HWND hWnd;
  HDC hdc;
  uchar *puVar23;
  undefined4 *puVar24;
  int iVar25;
  int nHeight;
  VIDEO_MODE_CLASS *pVVar26;
  tagPALETTEENTRY *ptVar27;
  uchar *puVar28;
  uint *puVar29;
  int unaff_EDI;
  VIDEO_MODE_CLASS *pVVar30;
  tagPALETTEENTRY *ptVar31;
  int local_5c;
  int local_58;
  
  D3DAppISetDefaults();
  ResolutionMode = 0;
  D3IniFlags = 0x14412b;
  D3VertexBufferSize = 0x40000;
  D3VertexBufferSize = GetPrivateProfileIntA("D3D","ExecBufSize",0x40000,&cfgFileName);
  D3IndexBufferSize = (int)(D3VertexBufferSize * 6 + (D3VertexBufferSize * 6 >> 0x1f & 0x1fU)) >> 5;
  UVar5 = GetPrivateProfileIntA("D3D","RadarType",-1,&cfgFileName);
  UVar6 = GetPrivateProfileIntA("D3D","ZBuffer",-1,&cfgFileName);
  UVar7 = GetPrivateProfileIntA("D3D","Alpha",-1,&cfgFileName);
  UVar8 = GetPrivateProfileIntA("D3D","Texture16",-1,&cfgFileName);
  UVar9 = GetPrivateProfileIntA("D3D","NoCaps",-1,&cfgFileName);
  UVar10 = GetPrivateProfileIntA("D3D","HalfTexel",-1,&cfgFileName);
  UVar11 = GetPrivateProfileIntA("D3D","TripleBuffer",-1,&cfgFileName);
  UVar12 = GetPrivateProfileIntA("D3D","AGPRadar",-1,&cfgFileName);
  UVar13 = GetPrivateProfileIntA("D3D","SplitZBuffer",-1,&cfgFileName);
  UVar14 = GetPrivateProfileIntA("D3D","MipMaps",-1,&cfgFileName);
  UVar15 = GetPrivateProfileIntA("D3D","PreLoad",-1,&cfgFileName);
  UVar16 = GetPrivateProfileIntA("D3D","LargeAssets",-1,&cfgFileName);
  UVar17 = GetPrivateProfileIntA("D3D","DrawInTexture",-1,&cfgFileName);
  UVar18 = GetPrivateProfileIntA("D3D","LoadSprites",-1,&cfgFileName);
  UVar19 = GetPrivateProfileIntA("D3D","Buffer32",-1,&cfgFileName);
  UVar20 = GetPrivateProfileIntA("D3D","Texture32",-1,&cfgFileName);
  UVar21 = GetPrivateProfileIntA("D3D","Vsync",-1,&cfgFileName);
  UVar22 = GetPrivateProfileIntA("D3D","HardwareClip",-1,&cfgFileName);
  d3dappi.MaxAnisotropy = GetPrivateProfileIntA("D3D","MaxAnisotropy",0x10,&cfgFileName);
  d3dappi.MultiSampleType = GetPrivateProfileIntA("D3D","MultiSampleType",0,&cfgFileName);
  d3dappi.MultiSampleQuality = GetPrivateProfileIntA("D3D","MultiSampleQuality",0,&cfgFileName);
  iVar25 = useD3D;
  if (UVar7 == 1) {
    D3IniFlags = D3IniFlags | 2;
  }
  if (UVar8 == 1) {
    D3IniFlags = D3IniFlags | 8;
  }
  if (UVar9 == 1) {
    D3IniFlags = D3IniFlags | 0x10;
  }
  if (UVar10 == 1) {
    D3IniFlags = D3IniFlags | 0x20;
  }
  if (UVar11 == 1) {
    D3IniFlags = D3IniFlags | 0x100;
  }
  if (UVar12 == 1) {
    D3IniFlags = D3IniFlags | 0x200;
  }
  if (UVar13 == 1) {
    D3IniFlags = D3IniFlags | 0x2000;
  }
  if (UVar14 == 1) {
    D3IniFlags = D3IniFlags | 0x4000;
  }
  if (UVar15 == 1) {
    D3IniFlags = D3IniFlags | 0x8000;
  }
  if (UVar17 == 1) {
    D3IniFlags = D3IniFlags | 0x10000;
  }
  if (UVar18 == 1) {
    D3IniFlags = D3IniFlags | 0x20000;
  }
  if (UVar19 == 1) {
    D3IniFlags = D3IniFlags | 0x40000;
  }
  if (UVar20 == 1) {
    D3IniFlags = D3IniFlags | 0x80000;
  }
  if (UVar21 == 1) {
    D3IniFlags = D3IniFlags | 0x100000;
  }
  if (UVar22 == 1) {
    D3IniFlags = D3IniFlags | 0x200000;
  }
  if (UVar7 == 0) {
    D3IniFlags = D3IniFlags & 0xfffffffd;
  }
  if (UVar8 == 0) {
    D3IniFlags = D3IniFlags & 0xfffffff7;
  }
  if (UVar9 == 0) {
    D3IniFlags = D3IniFlags & 0xffffffef;
  }
  if (UVar10 == 0) {
    D3IniFlags = D3IniFlags & 0xffffffdf;
  }
  if (UVar11 == 0) {
    D3IniFlags = D3IniFlags & 0xfffffeff;
  }
  if (UVar12 == 0) {
    D3IniFlags = D3IniFlags & 0xfffffdff;
  }
  if (UVar13 == 0) {
    D3IniFlags = D3IniFlags & 0xffffdfff;
  }
  if (UVar14 == 0) {
    D3IniFlags = D3IniFlags & 0xffffbfff;
  }
  if (UVar15 == 0) {
    D3IniFlags = D3IniFlags & 0xffff7fff;
  }
  if (UVar17 == 0) {
    D3IniFlags = D3IniFlags & 0xfffeffff;
  }
  if (UVar18 == 0) {
    D3IniFlags = D3IniFlags & 0xfffdffff;
  }
  if (UVar19 == 0) {
    D3IniFlags = D3IniFlags & 0xfff3ffff;
  }
  if (UVar20 == 0) {
    D3IniFlags = D3IniFlags & 0xfff7ffff;
  }
  if (UVar21 == 0) {
    D3IniFlags = D3IniFlags & 0xffefffff;
  }
  if (UVar22 == 0) {
    D3IniFlags = D3IniFlags & 0xffdfffff;
  }
  D3RadarType = 2;
  if (UVar5 != 0xffffffff) {
    D3RadarType = UVar5;
  }
  if (((D3IniFlags & 8U) != 0) && (useD3D = useD3D | 2, 0 < (int)UVar16)) {
    useD3D = iVar25 | 6;
  }
  if (-1 < (int)UVar16) {
    useD3D = useD3D | UVar16 << 3;
  }
  d3dappi.CfgZBuffer = UVar6;
  d3dappi.CfgTripleBuf = UVar11;
  (param_1->Viewport).Width = *(long *)(&DAT_0062da78 + ResolutionMode * 0x20);
  lVar2 = *(long *)(&DAT_0062da7c + ResolutionMode * 0x20);
  (param_1->Refresh).id = d3dRefreshMode.id;
  (param_1->Refresh).Blit = d3dRefreshMode.Blit;
  (param_1->Refresh).BlitFill = d3dRefreshMode.BlitFill;
  (param_1->Refresh).CopyBackBuffer = d3dRefreshMode.CopyBackBuffer;
  (param_1->Viewport).Height = lVar2;
  pVVar26 = &d3dVideoMode;
  pVVar30 = &param_1->VideoMode;
  for (iVar25 = 0xd; iVar25 != 0; iVar25 = iVar25 + -1) {
    pVVar30->id = pVVar26->id;
    pVVar26 = (VIDEO_MODE_CLASS *)&pVVar26->windowMode;
    pVVar30 = (VIDEO_MODE_CLASS *)&pVVar30->windowMode;
  }
  (param_1->winRect).top = 0;
  lpRect = &param_1->winRect;
  lpRect->left = 0;
  (param_1->winRect).right = *(long *)(&DAT_0062da78 + ResolutionMode * 0x20);
  (param_1->winRect).bottom = *(long *)(&DAT_0062da7c + ResolutionMode * 0x20);
  param_1->Client_Width = *(long *)(&DAT_0062da78 + ResolutionMode * 0x20);
  dwStyle = (param_1->VideoMode).windowStyle;
  param_1->Client_Height = *(long *)(&DAT_0062da7c + ResolutionMode * 0x20);
  AdjustWindowRect((LPRECT)lpRect,dwStyle,0);
  if (UseDDraw == 0) {
    plVar1 = &(param_1->winRect).bottom;
    *plVar1 = *plVar1 - (param_1->winRect).top;
    plVar1 = &(param_1->winRect).right;
    *plVar1 = *plVar1 - lpRect->left;
    lpRect->left = param_1->Screen_Width - (param_1->winRect).right >> 1;
    (param_1->winRect).top = 0;
  }
  hWnd = (HWND)param_1->hwndApp;
  if (hWnd == (HWND)0x0) {
    if (UseDDraw == 0) {
      local_5c = lpRect->left;
      local_58 = (param_1->winRect).top;
      iVar25 = (param_1->winRect).right;
      nHeight = (param_1->winRect).bottom;
      (param_1->VideoMode).windowStyle = 0xce0000;
    }
    else {
      iVar25 = param_1->Screen_Width;
      nHeight = param_1->Screen_Height;
      (param_1->VideoMode).windowStyle = -0x80000000;
      local_5c = 0;
      local_58 = 0;
    }
    hWnd = CreateWindowExA(0x40000,param_1->AppName,param_1->AppName,
                           (param_1->VideoMode).windowStyle,local_5c,local_58,iVar25,nHeight,
                           (HWND)0x0,(HMENU)0x0,(HINSTANCE)param_1->hInstance,(LPVOID)0x0);
    if (hWnd == (HWND)0x0) {
      return 0;
    }
  }
  param_1->hwndApp = (HWND__ *)hWnd;
  ShowWindow(hWnd,1);
  UpdateWindow(hWnd);
  hdc = GetDC((HWND)0x0);
  GetSystemPaletteEntries(hdc,0,0x100,(LPPALETTEENTRY)Originalppe);
  ptVar27 = Originalppe;
  ptVar31 = ppe;
  for (iVar25 = 0x100; iVar25 != 0; iVar25 = iVar25 + -1) {
    *ptVar31 = *ptVar27;
    ptVar27 = ptVar27 + 1;
    ptVar31 = ptVar31 + 1;
  }
  ReleaseDC((HWND)0x0,hdc);
  puVar28 = &DAT_00cd5841;
  puVar23 = &Originalppe[0].peGreen;
  do {
    puVar28[-1] = ((tagPALETTEENTRY *)(puVar23 + -1))->peRed;
    *puVar28 = *puVar23;
    puVar28[1] = puVar23[1];
    puVar23 = puVar23 + 4;
    puVar28 = puVar28 + 3;
  } while ((int)puVar23 < 0xc920e1);
  iVar25 = Create_D3D_App_Ex((VIDEO_DEVICE *)0x1,(uint)(UseDDraw == 0),unaff_EDI);
  if (iVar25 != 0) {
    Print_D3D_Log(&d3dappi);
    Square_Texture_Only_Flag = 1;
    CanDoWindow = 1;
    Reset_Texture_Struct();
    d3dappi.TextureTotalMem = GetTextureMemSize();
    if ((UVar10 == 0xffffffff) && (useHalfTexel != 0)) {
      D3IniFlags = D3IniFlags | 0x20;
    }
    iVar25 = D3DAppISetRenderState();
    if (iVar25 != 0) {
      if (0 < d3dappi.NumModes) {
        puVar29 = &d3dappi.Mode[0].Height;
        puVar24 = &DAT_0062db6c;
        param_1 = (VIDEO_DEVICE *)d3dappi.NumModes;
        do {
          uVar3 = ((_D3DDISPLAYMODE *)(puVar29 + -1))->Width;
          uVar4 = *puVar29;
          *puVar24 = 0;
          puVar24[-1] = 1;
          puVar24[1] = 1;
          puVar24[2] = 0x10;
          puVar24[3] = uVar3;
          puVar24[4] = uVar4;
          puVar24[5] = uVar3;
          puVar24[6] = uVar4;
          puVar24 = puVar24 + 8;
          puVar29 = puVar29 + 4;
          param_1 = (VIDEO_DEVICE *)((int)&param_1[-1].Refresh.CopyBackBuffer + 3);
        } while (param_1 != (VIDEO_DEVICE *)0x0);
      }
      d3dappi.D3IniFlags = D3IniFlags;
      SOMEONE_KILLED_ResolutionMode = ResolutionMode;
      return 1;
    }
  }
  return 0;
}
