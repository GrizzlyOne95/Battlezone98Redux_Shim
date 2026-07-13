/*
 * Entry: 0051cc8d
 * Name: Close_Clouds
 * Namespace: Global
 * Signature: void Close_Clouds(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Close_Clouds(void)

{
  char (*pacVar1) [16];
  
  pacVar1 = CloudSet.name;
  do {
    if ((*pacVar1)[0] != '\0') {
      TexCache_UnlockTexture(*pacVar1);
    }
    pacVar1 = pacVar1 + 1;
  } while ((int)pacVar1 < 0xc407f0);
  memset(&CloudSet,0,0xf0);
  memset(VisibleCloud,0,0x280);
  return;
}
