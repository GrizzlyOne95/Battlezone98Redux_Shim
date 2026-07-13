/*
 * Entry: 004f2756
 * Name: Fade_Cue_First_Frame
 * Namespace: Global
 * Signature: void Fade_Cue_First_Frame(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Fade_Cue_First_Frame(void)

{
  uchar *puVar1;
  int iVar2;
  RGB local_304 [256];
  
  Fade_First_Frame_Cueing_Flag = 1;
  puVar1 = &local_304[0].g;
  iVar2 = 0x100;
  do {
    ((RGB *)(puVar1 + -1))->r = '\0';
    *puVar1 = '\0';
    puVar1[1] = '\0';
    puVar1 = puVar1 + 3;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  (*Device.VideoMode.OverlayPalette)(&Device,local_304);
  return;
}
