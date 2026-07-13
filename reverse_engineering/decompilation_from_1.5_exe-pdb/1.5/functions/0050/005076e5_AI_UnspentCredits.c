/*
 * Entry: 005076e5
 * Name: AI_UnspentCredits
 * Namespace: Global
 * Signature: int AI_UnspentCredits(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AI_UnspentCredits(int param_1)

{
  if (AI_map->team[param_1] == (tag_team *)0x0) {
    return teamdata[param_1].credits;
  }
  return (AI_map->team[param_1]->aibuild).credit[0];
}
