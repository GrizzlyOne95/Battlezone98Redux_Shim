/*
 * Entry: 00543085
 * Name: D3D_Change_Mode_Ex
 * Namespace: Global
 * Signature: int D3D_Change_Mode_Ex(VIDEO_DEVICE * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl D3D_Change_Mode_Ex(VIDEO_DEVICE *param_1,long param_2)

{
  tagRECT *lpRect;
  long *plVar1;
  int iVar2;
  int in_EAX;
  int iVar3;
  VIDEO_DEVICE *unaff_EBX;
  tagRECT *ptVar4;
  undefined4 *puVar5;
  tagRECT *ptVar6;
  RGB *pRVar7;
  RGB local_318 [256];
  tagRECT local_18;
  int local_8;
  
  Trace("Mode: %d\n");
  iVar3 = d3dappi.bWindowed;
  if ((in_EAX == ResolutionMode) && (d3dappi.bWindowed != UseDDraw)) {
    local_8 = 0;
  }
  else {
    local_8 = 1;
  }
  if ((in_EAX == 0) || (*(int *)(&VideoMode + in_EAX * 0x20) != 0)) {
    d3dappi.bWindowed = (int)(UseDDraw == 0);
    SOMEONE_KILLED_ResolutionMode = in_EAX;
    ResolutionMode = in_EAX;
    D3DAppISelectDisplayMode();
    if (local_8 != 0) {
      if (ResolutionMode != 0) {
        (*(d3dappi.lpD3DDevice)->lpVtbl->SetDialogBoxMode)(d3dappi.lpD3DDevice,0);
      }
      if (iVar3 == 0) {
        ptVar4 = (tagRECT *)&d3dappi.SavedWindowRect;
        ptVar6 = &local_18;
      }
      else {
        GetWindowRect((HWND)unaff_EBX->hwndApp,&local_18);
        ptVar4 = &local_18;
        ptVar6 = (tagRECT *)&d3dappi.SavedWindowRect;
      }
      ptVar6->left = ptVar4->left;
      ptVar6->top = ptVar4->top;
      ptVar6->right = ptVar4->right;
      ptVar6->bottom = ptVar4->bottom;
      iVar3 = D3DAppIResetDevice();
      if (iVar3 == 0) goto LAB_005430d7;
      bIgnoreWM_SIZE = 1;
      (unaff_EBX->winRect).top = 0;
      lpRect = &unaff_EBX->winRect;
      lpRect->left = 0;
      (unaff_EBX->winRect).right = *(long *)(&DAT_0062da78 + ResolutionMode * 0x20);
      (unaff_EBX->winRect).bottom = *(long *)(&DAT_0062da7c + ResolutionMode * 0x20);
      unaff_EBX->Client_Width = *(long *)(&DAT_0062da78 + ResolutionMode * 0x20);
      iVar3 = *(int *)(&DAT_0062da7c + ResolutionMode * 0x20);
      unaff_EBX->Client_Height = iVar3;
      if (((iVar3 < unaff_EBX->Screen_Height) && (unaff_EBX->Client_Width < unaff_EBX->Screen_Width)
          ) && (d3dappi.bWindowed != 0)) {
        (unaff_EBX->VideoMode).windowStyle = 0xce0000;
      }
      else {
        (unaff_EBX->VideoMode).windowStyle = -0x80000000;
      }
      AdjustWindowRect((LPRECT)lpRect,(unaff_EBX->VideoMode).windowStyle,0);
      plVar1 = &(unaff_EBX->winRect).right;
      *plVar1 = *plVar1 - lpRect->left;
      plVar1 = &(unaff_EBX->winRect).bottom;
      *plVar1 = *plVar1 - (unaff_EBX->winRect).top;
      iVar3 = (unaff_EBX->winRect).right;
      if (UseDDraw == 0) {
        iVar2 = unaff_EBX->Screen_Width;
        if ((local_18.right - local_18.left < iVar2) && (iVar3 < iVar2)) {
          iVar3 = ((iVar2 - iVar3) * local_18.left) / ((iVar2 - local_18.right) + local_18.left);
        }
        else {
          iVar3 = iVar2 - iVar3 >> 1;
        }
        lpRect->left = iVar3;
        iVar3 = unaff_EBX->Screen_Height;
        if ((local_18.bottom - local_18.top < iVar3) &&
           (iVar2 = (unaff_EBX->winRect).bottom, iVar2 < iVar3)) {
          iVar3 = ((iVar3 - iVar2) * local_18.top) / ((iVar3 - local_18.bottom) + local_18.top);
        }
        else {
          iVar3 = iVar3 - (unaff_EBX->winRect).bottom >> 1;
        }
        (unaff_EBX->winRect).top = iVar3;
      }
      else {
        lpRect->left = 0;
        (unaff_EBX->winRect).top = 0;
      }
      SetWindowLongA((HWND)unaff_EBX->hwndApp,-0x10,(unaff_EBX->VideoMode).windowStyle | 0x10000000)
      ;
      SetWindowPos((HWND)unaff_EBX->hwndApp,(HWND)((-(uint)(UseDDraw != 0) & 2) - 2),lpRect->left,
                   (unaff_EBX->winRect).top,(unaff_EBX->winRect).right,(unaff_EBX->winRect).bottom,
                   0x160);
      bIgnoreWM_SIZE = 0;
      (*(unaff_EBX->Refresh).BlitFill)(unaff_EBX,0);
      (*(unaff_EBX->Refresh).Blit)(unaff_EBX);
    }
    if (ResolutionMode == 0) {
      (*(d3dappi.lpD3DDevice)->lpVtbl->SetDialogBoxMode)(d3dappi.lpD3DDevice,1);
    }
    else {
      if (local_8 != 0) {
        if (((byte)D3IniFlags & 1) == 0) {
          LODInfo.mergeBSP = 7;
          TerrainSeparateDraw = 0;
        }
        else {
          LODInfo.mergeBSP = 0;
          TerrainSeparateDraw = 1;
        }
      }
      puVar5 = (undefined4 *)&Default_Palette;
      pRVar7 = local_318;
      for (iVar3 = 0xc0; iVar3 != 0; iVar3 = iVar3 + -1) {
        *(undefined4 *)pRVar7 = *puVar5;
        puVar5 = puVar5 + 1;
        pRVar7 = (RGB *)&pRVar7[1].g;
      }
      ApplyGammaToPalette(local_318,0,0x100,0);
      D3D_OverlayPalette(unaff_EBX,local_318);
      iVar3 = D3DAppISetRenderState();
      if (iVar3 == 0) goto LAB_005430d7;
      (*(unaff_EBX->VideoMode).LockBuffer)(unaff_EBX);
      (*(unaff_EBX->VideoMode).UnlockBuffer)(unaff_EBX);
    }
    iVar3 = 1;
  }
  else {
LAB_005430d7:
    iVar3 = 0;
  }
  return iVar3;
}
