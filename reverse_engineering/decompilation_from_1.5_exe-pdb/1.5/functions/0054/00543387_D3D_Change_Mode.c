/*
 * Entry: 00543387
 * Name: D3D_Change_Mode
 * Namespace: Global
 * Signature: int D3D_Change_Mode(VIDEO_DEVICE * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl D3D_Change_Mode(VIDEO_DEVICE *param_1,long param_2)

{
  int iVar1;
  VIDEO_DEVICE *unaff_EBX;
  tagD3DAppInfo *unaff_retaddr;
  
  iVar1 = D3D_Change_Mode_Ex(unaff_EBX,(long)unaff_retaddr);
  if ((iVar1 == 0) && (LastErrorString[0] != '\0')) {
    D3D_Flush_Texture_Cache();
    D3DAppDestroy(unaff_retaddr);
    DEBUG_systemError(LastErrorString);
    return 0;
  }
  SynchCamera();
  return 1;
}
