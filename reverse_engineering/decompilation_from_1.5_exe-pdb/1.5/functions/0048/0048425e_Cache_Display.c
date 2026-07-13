/*
 * Entry: 0048425e
 * Name: Cache_Display
 * Namespace: Global
 * Signature: void Cache_Display(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Cache_Display(void)

{
  float fVar1;
  int iVar2;
  float fVar3;
  char local_5c [84];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  fVar3 = Get_TimeLocal();
  if (hMono == 0) {
    hMono = Mono_Register(refresh_callback);
  }
  iVar2 = Mono_IsActive(hMono);
  if ((iVar2 != 0) && (1.0 < fVar3 - interval_start)) {
    fVar3 = 1.0 / (fVar3 - interval_start);
    fVar1 = (float)(int)nUseItems;
    if ((int)nUseItems < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    sprintf(local_5c,"%7.3f",(double)(fVar1 * fVar3));
    Mono_Display(hMono,local_5c,0x23,1,7);
    fVar1 = (float)(int)nUnlockItems;
    if ((int)nUnlockItems < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    sprintf(local_5c,"%7.3f",(double)(fVar1 * fVar3));
    Mono_Display(hMono,local_5c,0x23,2,7);
    fVar1 = (float)(int)nGetItemSize;
    if ((int)nGetItemSize < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    sprintf(local_5c,"%7.3f",(double)(fVar1 * fVar3));
    Mono_Display(hMono,local_5c,0x23,3,7);
    fVar1 = (float)(int)nFindItems;
    if ((int)nFindItems < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    sprintf(local_5c,"%7.3f",(double)(fVar1 * fVar3));
    Mono_Display(hMono,local_5c,0x23,4,7);
    fVar1 = (float)(int)nItemExists;
    if ((int)nItemExists < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    sprintf(local_5c,"%7.3f",(double)(fVar1 * fVar3));
    Mono_Display(hMono,local_5c,0x23,5,7);
    fVar1 = (float)(int)nTexAccesses;
    if ((int)nTexAccesses < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    sprintf(local_5c,"%7.3f",(double)(fVar1 * fVar3));
    Mono_Display(hMono,local_5c,0x23,7,7);
    fVar1 = (float)(int)nTexHits;
    if ((int)nTexHits < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    sprintf(local_5c,"%7.3f",(double)(fVar1 * fVar3));
    Mono_Display(hMono,local_5c,0x23,8,7);
    fVar1 = (float)(int)nTexMisses;
    if ((int)nTexMisses < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    sprintf(local_5c,"%7.3f",(double)(fVar1 * fVar3));
    Mono_Display(hMono,local_5c,0x23,9,7);
    fVar1 = (float)(int)nTexNotComp;
    if ((int)nTexNotComp < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    sprintf(local_5c,"%7.3f",(double)(fVar1 * fVar3));
    Mono_Display(hMono,local_5c,0x23,10,7);
    fVar1 = (float)(int)nPackAccesses;
    if ((int)nPackAccesses < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    sprintf(local_5c,"%7.3f",(double)(fVar1 * fVar3));
    Mono_Display(hMono,local_5c,0x23,0xb,7);
    fVar1 = (float)(int)nPackHits;
    if ((int)nPackHits < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    sprintf(local_5c,"%7.3f",(double)(fVar1 * fVar3));
    Mono_Display(hMono,local_5c,0x23,0xc,7);
    fVar1 = (float)(int)nPackMisses;
    if ((int)nPackMisses < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    sprintf(local_5c,"%7.3f",(double)(fVar1 * fVar3));
    Mono_Display(hMono,local_5c,0x23,0xd,7);
    fVar1 = (float)(int)nPackNotPack;
    if ((int)nPackNotPack < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    sprintf(local_5c,"%7.3f",(double)(fVar1 * fVar3));
    Mono_Display(hMono,local_5c,0x23,0xe,7);
    fVar1 = (float)(int)nCacheAccesses;
    if ((int)nCacheAccesses < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    sprintf(local_5c,"%7.3f",(double)(fVar1 * fVar3));
    Mono_Display(hMono,local_5c,0x23,0xf,7);
    fVar1 = (float)(int)nCacheHits;
    if ((int)nCacheHits < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    sprintf(local_5c,"%7.3f",(double)(fVar1 * fVar3));
    Mono_Display(hMono,local_5c,0x23,0x10,7);
    fVar1 = (float)(int)nCacheMisses;
    if ((int)nCacheMisses < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    sprintf(local_5c,"%7.3f",(double)(fVar1 * fVar3));
    Mono_Display(hMono,local_5c,0x23,0x11,7);
    fVar1 = (float)(int)nCachePurges;
    if ((int)nCachePurges < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    sprintf(local_5c,"%7.3f",(double)(fVar1 * fVar3));
    Mono_Display(hMono,local_5c,0x23,0x13,7);
    sprintf(local_5c,"%7.3f",(double)nCachePurgesPerAlloc);
    Mono_Display(hMono,local_5c,0x23,0x14,7);
    fVar1 = (float)(int)nTexPurges;
    if ((int)nTexPurges < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    sprintf(local_5c,"%7.3f",(double)(fVar1 * fVar3));
    Mono_Display(hMono,local_5c,0x23,0x15,7);
    sprintf(local_5c,"%7.3f",(double)nTexPurgesPerAlloc);
    Mono_Display(hMono,local_5c,0x23,0x16,7);
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
    nTexAccesses = 0;
    nCachePurges = 0;
    nTexPurges = 0;
  }
  return;
}
