/*
 * Entry: 00401aee
 * Name: AiMission::SaveMission
 * Namespace: AiMission
 * Signature: bool SaveMission(_iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl AiMission::SaveMission(_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = RtimeClass::Save(param_1,(SObject *)current);
  return bVar1;
}
