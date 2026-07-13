/*
 * Entry: 0054535e
 * Name: Set_Render_State
 * Namespace: Global
 * Signature: void Set_Render_State(IDirect3DTexture9 * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Set_Render_State(IDirect3DTexture9 *param_1,long param_2)

{
  IDirect3DTexture9 *in_EAX;
  uint in_ECX;
  IDirect3DTexture9 *unaff_EBX;
  long unaff_retaddr;
  
  if ((in_EAX != lastEBHandle) || ((in_ECX | 2) != lastEBFlags)) {
    Set_Render_State_Flags(unaff_EBX,unaff_retaddr);
  }
  return;
}
