/*
 * Entry: 00508ba3
 * Name: AI_Parts_ReturnPartsSquad
 * Namespace: Global
 * Signature: tag_squad * AI_Parts_ReturnPartsSquad(tagUNIT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tag_squad * __cdecl AI_Parts_ReturnPartsSquad(tagUNIT *param_1)

{
  return (param_1->ai).the_squad;
}
