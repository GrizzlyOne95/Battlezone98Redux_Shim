/*
 * Entry: 005c7cb0
 * Name: ogg_page_bos
 * Namespace: Global
 * Signature: undefined ogg_page_bos()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* ogg_page_bos */

byte __cdecl ogg_page_bos(int *param_1)

{
  return *(byte *)(*param_1 + 5) & 2;
}
