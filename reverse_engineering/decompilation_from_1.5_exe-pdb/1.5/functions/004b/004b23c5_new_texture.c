/*
 * Entry: 004b23c5
 * Name: new_texture
 * Namespace: Global
 * Signature: TEXTURE * new_texture(ulong param_1, ulong param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TEXTURE * __cdecl new_texture(ulong param_1,ulong param_2)

{
  int in_EAX;
  TEXTURE *pTVar1;
  
  pTVar1 = malloc(in_EAX * param_1 + 8);
  return pTVar1;
}
