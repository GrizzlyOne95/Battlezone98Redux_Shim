/*
 * Entry: 005ca17e
 * Name: `dynamic_initializer_for_'mpMission''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'mpMission''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__mpMission__(void)

{
  AiMissionClass::AiMissionClass((AiMissionClass *)&mpMission,"MP");
  mpMission._0_4_ = &MPMissionClass::_vftable_;
  return;
}
