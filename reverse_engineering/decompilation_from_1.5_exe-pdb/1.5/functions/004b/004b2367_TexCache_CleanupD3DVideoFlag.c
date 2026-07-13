/*
 * Entry: 004b2367
 * Name: TexCache_CleanupD3DVideoFlag
 * Namespace: Global
 * Signature: void TexCache_CleanupD3DVideoFlag(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl TexCache_CleanupD3DVideoFlag(void)

{
  _texcache *p_Var1;
  
  for (p_Var1 = purge_head; p_Var1 != (_texcache *)0x0; p_Var1 = p_Var1->next_purge) {
    p_Var1->flags = p_Var1->flags & 0xfffd;
  }
  return;
}
