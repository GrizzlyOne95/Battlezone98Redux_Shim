/*
 * Entry: 00507196
 * Name: AI_Close
 * Namespace: Global
 * Signature: void AI_Close(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Close(void)

{
  tlog_gdm("AI::AI_Close Begins");
  if (ai_game_initialised == 0) {
    tlog_gdm("AI::AI_Close CALLED WITHOUT MATCHING OPEN !!!");
  }
  else {
    ai_game_initialised = 0;
    if (AI_map != (tag_strategy_map *)0x0) {
      Strategy_Map_Delete(AI_map);
      AI_map = (tag_strategy_map *)0x0;
      AIBuild_Close();
      AI_Match_Close();
    }
  }
  Squad_Dump();
  Grassfire_Trash();
  tlog_gdm("AI::AI_Close Ends");
  return;
}
