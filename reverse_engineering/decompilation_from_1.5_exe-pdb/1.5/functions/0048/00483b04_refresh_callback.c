/*
 * Entry: 00483b04
 * Name: refresh_callback
 * Namespace: Global
 * Signature: void refresh_callback(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl refresh_callback(void)

{
  char local_5c [84];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  Mono_Clear(hMono);
  sprintf(local_5c,"%-80s","Cache Activity");
  Mono_Display(hMono,local_5c,0,0,0x70);
  Mono_Display(hMono,"# UseItems/sec:",0,1,7);
  Mono_Display(hMono,"# UnlockItems/sec:",0,2,7);
  Mono_Display(hMono,"# GetItemSize/sec:",0,3,7);
  Mono_Display(hMono,"# FindItems/sec:",0,4,7);
  Mono_Display(hMono,"# ItemExists/sec:",0,5,7);
  Mono_Display(hMono,"# TexCache Accesses/sec:",0,7,7);
  Mono_Display(hMono,"# TexCache Hits/sec:",0,8,7);
  Mono_Display(hMono,"# TexCache Misses/sec:",0,9,7);
  Mono_Display(hMono,"# TexCache Uncompressed/sec:",0,10,7);
  Mono_Display(hMono,"# Pack Accesses/sec:",0,0xb,7);
  Mono_Display(hMono,"# Pack Hits/sec:",0,0xc,7);
  Mono_Display(hMono,"# Pack Misses/sec:",0,0xd,7);
  Mono_Display(hMono,"# Pack Not Packed/sec:",0,0xe,7);
  Mono_Display(hMono,"# Cache Accesses/sec:",0,0xf,7);
  Mono_Display(hMono,"# Cache Hits/sec:",0,0x10,7);
  Mono_Display(hMono,"# Cache Misses/sec:",0,0x11,7);
  Mono_Display(hMono,"# Cache Purges/sec:",0,0x13,7);
  Mono_Display(hMono,"# Cache Purges per allocation:",0,0x14,7);
  Mono_Display(hMono,"# TexCache Purges/sec:",0,0x15,7);
  Mono_Display(hMono,"# TexCache Purges per allocation:",0,0x16,7);
  interval_start = Get_TimeLocal();
  nItemExists = 0;
  nFindItems = 0;
  nGetItemSize = 0;
  nUnlockItems = 0;
  nUseItems = 0;
  nCacheMisses = 0;
  nCacheHits = 0;
  nCacheAccesses = 0;
  nPackNotPack = 0;
  nPackMisses = 0;
  nPackHits = 0;
  nPackAccesses = 0;
  nTexNotComp = 0;
  nTexMisses = 0;
  nTexHits = 0;
  nCachePurgesPerAlloc = 0.0;
  nTexAccesses = 0;
  nTexPurgesPerAlloc = 0.0;
  nCachePurges = 0;
  nTexPurges = 0;
  return;
}
