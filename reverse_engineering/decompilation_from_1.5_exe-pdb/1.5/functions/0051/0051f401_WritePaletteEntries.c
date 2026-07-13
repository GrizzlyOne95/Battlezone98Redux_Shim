/*
 * Entry: 0051f401
 * Name: WritePaletteEntries
 * Namespace: Global
 * Signature: void WritePaletteEntries(RGB * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl WritePaletteEntries(RGB *param_1,char *param_2)

{
  if (useD3D != 0) {
    (*Device.VideoMode.writePaletteEntries)(&Device,0,0x100,param_1,param_2);
    return;
  }
  if (Device.ActiveVideo != 0) {
    memmove(Device.Palette,param_1,0x300);
    Device.Palette[0].r = '\0';
    Device.Palette[0].g = '\0';
    Device.Palette[0].b = '\0';
    UpdateFloatPalette(Device.Palette);
    ApplyGammaToPalette(Device.Palette,0,0x100,0);
    Device_Init_Luminance_Table(&Device,param_2);
  }
  return;
}
