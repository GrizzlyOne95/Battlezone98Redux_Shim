/*
 * Entry: 0054fbf6
 * Name: Graphic_Buffer_Save
 * Namespace: Global
 * Signature: void Graphic_Buffer_Save(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Graphic_Buffer_Save(VIDEO_DEVICE *param_1)

{
  int iVar1;
  char local_108 [256];
  uint local_8;
  
  iVar1 = picnum;
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  picnum = picnum + 1;
  sprintf(local_108,"SCR%04d.pcx",iVar1);
  Save_pcx_GraphicBuffer(local_108,&param_1->Viewport,param_1->Palette);
  return;
}
