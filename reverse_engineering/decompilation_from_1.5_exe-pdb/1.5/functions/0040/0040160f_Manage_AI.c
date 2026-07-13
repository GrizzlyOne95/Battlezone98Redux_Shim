/*
 * Entry: 0040160f
 * Name: Manage_AI
 * Namespace: Global
 * Signature: void Manage_AI(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Manage_AI(VIDEO_DEVICE *param_1)

{
  int iVar1;
  float fVar2;
  char *pcVar3;
  
  Collision_Fill_In_Range_Search_Structure();
  if (mission == (AiMission *)0x0) {
    mission = AiMission::GetCurrent();
  }
  (**(code **)(mission->_padding_ + 0x2c))();
  (**(code **)(mission->_padding_ + 0x30))();
  iVar1 = Net_IsNetGame();
  if ((iVar1 == 0) &&
     (((GameObject::userObject == (GameObject *)0x0 ||
       (GameObject::userObject->aiProcess == (AiProcess *)0x0)) && (mission->done == false)))) {
    pcVar3 = (char *)0x0;
    fVar2 = Get_Time();
    FailMission(fVar2 + 10.0,pcVar3);
  }
  return;
}
