/*
 * Entry: 00401ab0
 * Name: AiMission::LoadMission
 * Namespace: AiMission
 * Signature: bool LoadMission(_iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl AiMission::LoadMission(_iobuf *param_1)

{
  current = (AiMission *)RtimeClass::Load(param_1);
  return current != (AiMission *)0x0;
}
