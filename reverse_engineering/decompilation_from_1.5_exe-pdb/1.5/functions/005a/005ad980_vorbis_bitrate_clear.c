/*
 * Entry: 005ad980
 * Name: vorbis_bitrate_clear
 * Namespace: Global
 * Signature: void vorbis_bitrate_clear(bitrate_manager_state * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl vorbis_bitrate_clear(bitrate_manager_state *param_1)

{
  memset(param_1,0,0x30);
  return;
}
