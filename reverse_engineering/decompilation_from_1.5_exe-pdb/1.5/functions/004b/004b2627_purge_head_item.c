/*
 * Entry: 004b2627
 * Name: purge_head_item
 * Namespace: Global
 * Signature: int purge_head_item(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl purge_head_item(void)

{
  _texcache *p_Var1;
  _texcache *_Memory;
  ulong uVar2;
  _texcache *p_Var3;
  _texcache *unaff_ESI;
  
  p_Var1 = purge_head;
  if (purge_head == (_texcache *)0x0) {
    return 0;
  }
  _Memory = purge_head;
  if (useD3D != 0) {
    do {
      if ((_Memory->flags & 2) == 0) break;
      _Memory = _Memory->next_purge;
    } while (_Memory != (_texcache *)0x0);
    if (_Memory == (_texcache *)0x0) {
      D3D_Flush_Texture_Cache();
      _Memory = p_Var1;
    }
  }
  remove_from_purge(unaff_ESI);
  uVar2 = thash(unaff_ESI->name);
  p_Var1 = texcache[uVar2];
  if (p_Var1 == _Memory) {
    texcache[uVar2] = _Memory->next;
  }
  else {
    do {
      p_Var3 = p_Var1;
      p_Var1 = p_Var3->next;
      if (p_Var1 == (_texcache *)0x0) {
        DEBUG_systemError("Error: texture %s from purge list not found in hash table!");
        goto LAB_004b2694;
      }
    } while (p_Var1 != _Memory);
    p_Var3->next = p_Var1->next;
  }
LAB_004b2694:
  free(_Memory->umap);
  free(_Memory);
  nTexPurges = nTexPurges + 1;
  num_purges_temp = num_purges_temp + 1;
  return 1;
}
