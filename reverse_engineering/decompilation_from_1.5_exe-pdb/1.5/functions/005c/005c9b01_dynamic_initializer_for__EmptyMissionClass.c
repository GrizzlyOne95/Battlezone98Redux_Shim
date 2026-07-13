/*
 * Entry: 005c9b01
 * Name: `dynamic_initializer_for_'EmptyMissionClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'EmptyMissionClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__EmptyMissionClass__(void)

{
  AiMissionClass::AiMissionClass((AiMissionClass *)&EmptyMissionClass,"empty");
  EmptyMissionClass._0_4_ = &EmptyMissionClass::_vftable_;
  return;
}
