/*
 * Entry: 005a2ba0
 * Name: vorbis_synthesis_halfrate
 * Namespace: Global
 * Signature: int vorbis_synthesis_halfrate(vorbis_info * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_synthesis_halfrate(vorbis_info *param_1,int param_2)

{
  if ((*(int *)param_1->codec_setup < 0x41) && (param_2 != 0)) {
    return -1;
  }
  *(uint *)((int)param_1->codec_setup + 0xe48) = (uint)(param_2 != 0);
  return 0;
}
