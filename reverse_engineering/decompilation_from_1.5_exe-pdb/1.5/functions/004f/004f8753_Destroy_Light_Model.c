/*
 * Entry: 004f8753
 * Name: Destroy_Light_Model
 * Namespace: Global
 * Signature: void Destroy_Light_Model(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Destroy_Light_Model(void)

{
  UnlockItem(TOD_tbl[Lights_Struct.TOD_entry].Bitmap);
  __Sun_Texture__ = (TEXTURE *)0x0;
  memset(&Lights_Struct,0,0xd884);
  return;
}
