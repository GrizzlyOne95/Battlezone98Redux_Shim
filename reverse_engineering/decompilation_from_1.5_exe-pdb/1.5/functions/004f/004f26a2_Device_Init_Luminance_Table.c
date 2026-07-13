/*
 * Entry: 004f26a2
 * Name: Device_Init_Luminance_Table
 * Namespace: Global
 * Signature: void Device_Init_Luminance_Table(VIDEO_DEVICE * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Device_Init_Luminance_Table(VIDEO_DEVICE *param_1,char *param_2)

{
  uchar *puVar1;
  uint uVar2;
  uint uVar3;
  float unaff_ESI;
  uint uVar4;
  float unaff_EDI;
  
  uVar4 = 0;
  puVar1 = &param_1->Palette[0].g;
  uVar2 = 0;
  do {
    uVar3 = uVar2 + 0xc;
    *(float *)((int)Float_Pal[0] + uVar2) = (float)((RGB *)(puVar1 + -1))->r * 0.003921569;
    *(float *)((int)Float_Pal[0] + uVar2 + 4) = (float)*puVar1 * 0.003921569;
    *(float *)((int)Float_Pal[0] + uVar2 + 8) = (float)puVar1[1] * 0.003921569;
    puVar1 = puVar1 + 3;
    uVar2 = uVar3;
  } while (uVar3 < 0xc00);
  if (param_2 == (char *)0x0) {
    do {
      Device_Build_ColorRamp_Entry
                ((VIDEO_DEVICE *)0x3c23d70a,0x3c23d70a,0.01,0.8,unaff_EDI,unaff_ESI);
      uVar4 = uVar4 + 1;
    } while (uVar4 < 0x100);
  }
  else {
    memcpy(Luminance_Table,param_2,0x10000);
  }
  Fill_Luminance_Extras();
  return;
}
