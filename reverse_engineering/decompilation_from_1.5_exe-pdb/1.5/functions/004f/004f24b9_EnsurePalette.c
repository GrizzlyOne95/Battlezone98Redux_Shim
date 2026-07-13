/*
 * Entry: 004f24b9
 * Name: EnsurePalette
 * Namespace: Global
 * Signature: void EnsurePalette(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl EnsurePalette(void)

{
  Graphic_Buffer_Clear(&Device.Viewport,Black_Color);
  if (Device.VideoMode.OverlayPalette != (_func___cdecl_int_void_ptr_RGB_ptr *)0x0) {
    (*Device.VideoMode.OverlayPalette)(&Device,(RGB *)&WindowsPalette);
  }
  WindowsPaletteLoaded = 1;
  if (Device.Refresh.Blit != (_func___cdecl_int_void_ptr *)0x0) {
    (*Device.Refresh.Blit)(&Device);
  }
  return;
}
