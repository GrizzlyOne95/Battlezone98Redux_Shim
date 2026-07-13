/*
 * Entry: 004e6181
 * Name: Scores_Toggle
 * Namespace: Global
 * Signature: void Scores_Toggle(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Scores_Toggle(void)

{
  Scores_UpdateScores();
  score_show = (int)(score_show == 0);
  Scores_Show(score_show);
  return;
}
