/*
 * Entry: 0059fba0
 * Name: vorbis_info_init
 * Namespace: Global
 * Signature: void vorbis_info_init(vorbis_info * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl vorbis_info_init(vorbis_info *param_1)

{
  void *pvVar1;
  
  param_1->version = 0;
  param_1->channels = 0;
  param_1->rate = 0;
  param_1->bitrate_upper = 0;
  param_1->bitrate_nominal = 0;
  param_1->bitrate_lower = 0;
  param_1->bitrate_window = 0;
  param_1->codec_setup = (void *)0x0;
  pvVar1 = calloc(1,0xe50);
  param_1->codec_setup = pvVar1;
  return;
}
