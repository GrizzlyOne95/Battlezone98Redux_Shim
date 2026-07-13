/*
 * Entry: 0054427e
 * Name: D3D_Load_Texture
 * Namespace: Global
 * Signature: int D3D_Load_Texture(D3DCACHEENTRY * param_1, TEXTURE * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Exceeded maximum restarts with more pending */

int __cdecl D3D_Load_Texture(D3DCACHEENTRY *param_1,TEXTURE **param_2)

{
  int *piVar1;
  int in_EAX;
  uint uVar2;
  uint uVar3;
  D3DCACHEENTRY *unaff_EBX;
  _D3DSURFACE_DESC *unaff_ESI;
  D3DCACHEENTRY *unaff_EDI;
  IDirect3DTexture9 *pIVar4;
  IDirect3DDevice9 *pIVar5;
  IDirect3DTexture9 *pIVar6;
  undefined1 local_38 [32];
  undefined1 local_18 [4];
  uint local_14;
  _D3DFORMAT local_10;
  uint local_c;
  IDirect3DTexture9 *local_8;
  
  local_8 = (IDirect3DTexture9 *)0x0;
  uVar2 = *(uint *)(in_EAX + 4) >> 0xc & 0xfff;
  piVar1 = *(int **)(in_EAX + 0xc);
  pIVar4 = (IDirect3DTexture9 *)(*(uint *)(in_EAX + 4) & 0xfff);
  local_14 = uVar2;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
    *(undefined4 *)(in_EAX + 0xc) = 0;
  }
  local_10 = GetTextureFormat(unaff_EDI);
  uVar3 = local_14;
  if (local_10 != D3DFMT_UNKNOWN) {
    if (((D3IniFlags & 0x4000U) == 0) || (local_c = 4, param_1 == (D3DCACHEENTRY *)0x0)) {
      local_c = 1;
    }
    pIVar5 = d3dappi.lpD3DDevice;
    pIVar6 = pIVar4;
    (*(d3dappi.lpD3DDevice)->lpVtbl->CreateTexture)
              (d3dappi.lpD3DDevice,(uint)pIVar4,uVar2,local_c,0,local_10,D3DPOOL_MANAGED,&local_8,
               (void **)0x0);
    if (param_1 == (D3DCACHEENTRY *)0x0) {
      uVar3 = (*local_8->lpVtbl->GetLevelDesc)(local_8,0,local_38);
      if (((uVar3 == 0) &&
          (uVar3 = (*local_8->lpVtbl->LockRect)(local_8,0,local_18,0,0), uVar3 == 0)) &&
         (uVar3 = Copy_Texture_To_D3D((_D3DLOCKED_RECT *)unaff_EDI,unaff_ESI,unaff_EBX), uVar3 == 0)
         ) {
        (*local_8->lpVtbl->UnlockRect)(local_8,0);
        local_14 = uVar2;
        goto LAB_00544365;
      }
    }
    else {
      uVar3 = Copy_MIPMAPs_To_D3D(param_1,(TEXTURE **)pIVar5,pIVar6);
      if (uVar3 == 0) {
LAB_00544365:
        D3DTextLoads = D3DTextLoads + 1;
        D3DTextMem = D3DTextMem + local_14 * (int)pIVar4 * 2;
        *(IDirect3DTexture9 **)(in_EAX + 0xc) = local_8;
        return 1;
      }
    }
  }
  D3DAppErrorToString(uVar3);
  D3D_DEBUG_systemWarning("%s");
  if (local_8 != (IDirect3DTexture9 *)0x0) {
    (*local_8->lpVtbl->Release)(local_8);
  }
  return 0;
}
