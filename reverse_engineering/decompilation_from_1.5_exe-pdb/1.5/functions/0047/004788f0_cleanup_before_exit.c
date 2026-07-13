/*
 * Entry: 004788f0
 * Name: cleanup_before_exit
 * Namespace: Global
 * Signature: void cleanup_before_exit(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl cleanup_before_exit(void)

{
  LastInputs();
  LastGAS();
  if (Device.VideoMode.close != (_func___cdecl_void_void_ptr *)0x0) {
    Device_Graphic_Close(&Device);
    if (Device.hwndApp != (HWND__ *)0x0) {
      DestroyWindow((HWND)Device.hwndApp);
    }
    reset_cursor();
    SetCDVolume(nSaveVolume);
  }
  return;
}
