/*
 * Entry: 00401575
 * Name: AiMission::Fail
 * Namespace: AiMission
 * Signature: void Fail(AiMission * this, float param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AiMission::Fail(AiMission *this,float param_1,char *param_2)

{
  End(this,param_1,param_2,true);
  return;
}
