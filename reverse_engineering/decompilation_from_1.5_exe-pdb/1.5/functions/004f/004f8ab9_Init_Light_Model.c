/*
 * Entry: 004f8ab9
 * Name: Init_Light_Model
 * Namespace: Global
 * Signature: void Init_Light_Model(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Init_Light_Model(long param_1)

{
  memset(&Lights_Struct,0,0xd884);
  Depth_Att0 = -1.0;
  Depth_Att1 = 0.01;
  Lights_Struct.Light_Counter = 0;
  Lights_Struct.TOD_entry = ((param_1 + 2) % 0x18 << 3) / 0x18;
  __Sun_Texture__ = UseItem(TOD_tbl[Lights_Struct.TOD_entry].Bitmap);
  Rotate_Sunlight();
  return;
}
