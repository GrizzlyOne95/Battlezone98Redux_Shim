/*
 * Entry: 004773b8
 * Name: Close_SkyBackdrop
 * Namespace: Global
 * Signature: void Close_SkyBackdrop(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Close_SkyBackdrop(void)

{
  int iVar1;
  tagSkyBackdrop *ptVar2;
  
  if (SkyBackdrop.name[0] != '\0') {
    TexCache_UnlockTexture(SkyBackdrop.name);
  }
  ptVar2 = &SkyBackdrop;
  for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
    ptVar2->name[0] = '\0';
    ptVar2->name[1] = '\0';
    ptVar2->name[2] = '\0';
    ptVar2->name[3] = '\0';
    ptVar2 = (tagSkyBackdrop *)(ptVar2->name + 4);
  }
  return;
}
