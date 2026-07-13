/*
 * Entry: 0059c0d0
 * Name: ov_streams
 * Namespace: Global
 * Signature: long ov_streams(OggVorbis_File * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl ov_streams(OggVorbis_File *param_1)

{
  return param_1->links;
}
