/*
 * Entry: 00544e9d
 * Name: Get_Texture_Handle
 * Namespace: Global
 * Signature: IDirect3DTexture9 * Get_Texture_Handle(TEXTURE * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

IDirect3DTexture9 * __cdecl Get_Texture_Handle(TEXTURE *param_1,int param_2)

{
  TEXTURE *in_EAX;
  
  if (lastTextPtr == in_EAX) {
    return lastTextHandle;
  }
  lastTextPtr = in_EAX;
  lastTextHandle = Get_D3D_Texture_Handle(in_EAX,(int)param_1);
  return lastTextHandle;
}
