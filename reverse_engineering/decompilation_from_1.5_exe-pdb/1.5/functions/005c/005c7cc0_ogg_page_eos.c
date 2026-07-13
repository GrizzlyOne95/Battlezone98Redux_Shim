/*
 * Entry: 005c7cc0
 * Name: ogg_page_eos
 * Namespace: Global
 * Signature: undefined ogg_page_eos()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* ogg_page_eos */

byte __cdecl ogg_page_eos(int *param_1)

{
  return *(byte *)(*param_1 + 5) & 4;
}
