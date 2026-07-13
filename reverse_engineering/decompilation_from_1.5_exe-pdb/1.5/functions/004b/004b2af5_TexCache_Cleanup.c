/*
 * Entry: 004b2af5
 * Name: TexCache_Cleanup
 * Namespace: Global
 * Signature: void TexCache_Cleanup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl TexCache_Cleanup(void)

{
  _texcache *p_Var1;
  int iVar2;
  _texcache **pp_Var3;
  _texcache *unaff_EDI;
  
  D3D_Flush_Texture_Cache();
  pp_Var3 = texcache;
  do {
    p_Var1 = *pp_Var3;
    while (p_Var1 != (_texcache *)0x0) {
      p_Var1 = p_Var1->next;
      add_to_purge(unaff_EDI);
    }
    pp_Var3 = pp_Var3 + 1;
  } while ((int)pp_Var3 < 0xb0d04c);
  do {
    iVar2 = purge_head_item();
  } while (iVar2 != 0);
  return;
}
