/*
 * Entry: 004b2b2e
 * Name: LoadSelection
 * Namespace: Global
 * Signature: void LoadSelection(TEX_INFO * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl LoadSelection(TEX_INFO *param_1)

{
  TEXTURE *pTVar1;
  int unaff_EBX;
  undefined4 *puVar2;
  long local_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  uint uStack_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  puVar2 = (undefined4 *)
           (*(int *)(*(int *)(unaff_EBX + 0x10) + 0x2c) +
           (*(uint *)(unaff_EBX + 0x14) & 0xffff) * 0x10);
  local_18 = *puVar2;
  uStack_14 = puVar2[1];
  uStack_10 = puVar2[2];
  uStack_c = puVar2[3] & 0xffffff;
  SplitPrjFile((char *)&local_18,(long64 *)(unaff_EBX + 0x18),&local_1c);
  pTVar1 = TexCache_UseTexture((char *)&local_18);
  *(TEXTURE **)(unaff_EBX + 0x20) = pTVar1;
  return;
}
