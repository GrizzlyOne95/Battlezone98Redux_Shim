/*
 * Entry: 0054412f
 * Name: Copy_MIPMAPs_To_D3D
 * Namespace: Global
 * Signature: T_HRESULT Copy_MIPMAPs_To_D3D(D3DCACHEENTRY * param_1, TEXTURE * * param_2, IDirect3DTexture9 * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Copy_MIPMAPs_To_D3D(D3DCACHEENTRY *param_1,TEXTURE **param_2,IDirect3DTexture9 *param_3)

{
  TEXTURE *pTVar1;
  int iVar2;
  undefined4 *unaff_EBX;
  _D3DLOCKED_RECT *unaff_ESI;
  _D3DLOCKED_RECT *p_Var3;
  _D3DSURFACE_DESC *p_Var4;
  D3DCACHEENTRY *pDVar5;
  D3DCACHEENTRY local_34;
  uint local_1c;
  int local_18;
  undefined4 local_c;
  int local_8;
  
  local_c = *unaff_EBX;
  pDVar5 = &local_34;
  p_Var4 = (_D3DSURFACE_DESC *)0x0;
  p_Var3 = unaff_ESI;
  iVar2 = (**(code **)(unaff_ESI->Pitch + 0x44))();
  if (((iVar2 == 0) && (iVar2 = (**(code **)(unaff_ESI->Pitch + 0x4c))(), iVar2 == 0)) &&
     (iVar2 = Copy_Texture_To_D3D(p_Var3,p_Var4,pDVar5), iVar2 == 0)) {
    (**(code **)(unaff_ESI->Pitch + 0x50))();
    local_8 = 1;
    while ((iVar2 = (**(code **)(unaff_ESI->Pitch + 0x44))(), iVar2 == 0 &&
           (iVar2 = (**(code **)(unaff_ESI->Pitch + 0x4c))(), iVar2 == 0))) {
      pTVar1 = (&param_1->texture)[local_8];
      *unaff_EBX = pTVar1;
      if (((uint)(int)pTVar1->width >> (2 < pTVar1->type) + (0 < pTVar1->type) == local_1c) &&
         (pTVar1->height == local_18)) {
        iVar2 = Copy_Texture_To_D3D(p_Var3,p_Var4,pDVar5);
        if (iVar2 != 0) break;
        D3DTextLoads = D3DTextLoads + 1;
        D3DTextMem = D3DTextMem + local_18 * local_1c * 2;
      }
      else {
        cacheName(pTVar1);
        Trace("Texture %s is %dx%d instead of %dx%d\n");
      }
      (**(code **)(unaff_ESI->Pitch + 0x50))();
      local_8 = local_8 + 1;
      if (3 < local_8) {
        *unaff_EBX = local_c;
        return 0;
      }
    }
  }
  D3DAppErrorToString(iVar2);
  D3D_DEBUG_systemWarning("%s");
  *unaff_EBX = local_c;
  return iVar2;
}
