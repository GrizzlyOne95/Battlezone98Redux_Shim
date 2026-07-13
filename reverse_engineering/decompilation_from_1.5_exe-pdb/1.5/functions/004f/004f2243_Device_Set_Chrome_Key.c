/*
 * Entry: 004f2243
 * Name: Device_Set_Chrome_Key
 * Namespace: Global
 * Signature: void Device_Set_Chrome_Key(VIDEO_DEVICE * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Device_Set_Chrome_Key(VIDEO_DEVICE *param_1,long param_2)

{
  uchar *puVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = param_2 & 0xff;
  memmove(Chrome_Key_Table + uVar3,&Reset_Chroma,0x100);
  memset(&DAT_00d3fda0,uVar3,0x100);
  memmove(Translucency_Table + uVar3,&Reset_Chroma,0x100);
  iVar2 = 0;
  puVar1 = Translucency_Table[0] + uVar3;
  do {
    *puVar1 = (&Reset_Chroma)[iVar2];
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 0x100;
  } while (iVar2 < 0xff);
  return;
}
