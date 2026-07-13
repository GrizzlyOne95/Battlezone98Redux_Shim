/*
 * Entry: 005c7ca0
 * Name: ogg_page_continued
 * Namespace: Global
 * Signature: undefined ogg_page_continued()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* ogg_page_continued */

byte __cdecl ogg_page_continued(int *param_1)

{
  return *(byte *)(*param_1 + 5) & 1;
}
