/*
 * Entry: 00496900
 * Name: out_of_memory
 * Namespace: Global
 * Signature: int out_of_memory(uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl out_of_memory(uint param_1)

{
  LPCSTR lpText;
  char *lpCaption;
  UINT uType;
  
  LastGAS();
  LastInputs();
  Device_Graphic_Close(&Device);
  reset_cursor();
  if (nSaveVolumeFlag != 0) {
    SetCDVolume(nSaveVolume);
  }
  uType = 0x10;
  lpCaption = "Battlezone";
  lpText = (LPCSTR)_StrLookupFind(_DAT_00224566,"Out of Memory");
  MessageBoxA((HWND)Device.hwndApp,lpText,lpCaption,uType);
  SetLastSessionFlag();
                    /* WARNING: Subroutine does not return */
  exit(0x98);
}
