/*
 * Entry: 00477d1b
 * Name: Init_SkyBackdrop
 * Namespace: Global
 * Signature: void Init_SkyBackdrop(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Init_SkyBackdrop(void)

{
  float fVar1;
  int iVar2;
  tagSkyBackdrop *ptVar3;
  float10 fVar4;
  
  ptVar3 = &SkyBackdrop;
  for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1) {
    ptVar3->name[0] = '\0';
    ptVar3->name[1] = '\0';
    ptVar3->name[2] = '\0';
    ptVar3->name[3] = '\0';
    ptVar3 = (tagSkyBackdrop *)(ptVar3->name + 4);
  }
  GetINIString(secStr,"BackdropTexture","",SkyBackdrop.name,0x10,missionName);
  if ((SkyBackdrop.name[0] != '\0') &&
     (SkyBackdrop.bitmap = TexCache_UseTexture(SkyBackdrop.name),
     SkyBackdrop.bitmap != (TEXTURE *)0x0)) {
    iVar2 = GetINIInt(secStr,"BackdropDistance",400,missionName);
    SkyBackdrop.distance = (float)iVar2;
    iVar2 = GetINIInt(secStr,"BackdropHeight",0x32,missionName);
    SkyBackdrop.height = (float)iVar2;
    iVar2 = GetINIInt(secStr,"BackdropBase",0,missionName);
    SkyBackdrop.base = (float)iVar2;
    SkyBackdrop.type = GetINIInt(secStr,"BackdropType",0,missionName);
    fVar1 = SQRT(SkyBackdrop.height * 0.5 * SkyBackdrop.height * 0.5 +
                 SkyBackdrop.distance * SkyBackdrop.distance);
    SkyBackdrop.width = fVar1 + fVar1;
    fVar4 = (float10)__CIacos();
    pi2_inv = (float)((float10)0.5 / fVar4);
    return;
  }
  Close_SkyBackdrop();
  return;
}
