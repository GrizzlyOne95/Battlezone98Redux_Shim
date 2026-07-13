/*
 * Entry: 0054f526
 * Name: Scroll_Init
 * Namespace: Global
 * Signature: void Scroll_Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Scroll_Init(void)

{
  MILES_FONT_INFO *pMVar1;
  FONT *pFVar2;
  CHARACTER *pCVar3;
  
  region_list = (wrap_struct *)0x0;
  hRegionHeap = (void *)0x1;
  pMVar1 = LocaleNetworkFont(NETWORK_FONT_HIGHRES_INDEX,"base6x76.fnt");
  pFVar2 = Font_Read(pMVar1);
  pCVar3 = GetCharacterAddress(pFVar2,0x57);
  fWidth = pCVar3->Width;
  fHeight = pFVar2->char_height;
  Font_Free(pFVar2);
  resWidth = 0;
  resHeight = 0;
  return;
}
