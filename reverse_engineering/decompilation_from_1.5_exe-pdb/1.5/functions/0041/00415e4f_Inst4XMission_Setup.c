/*
 * Entry: 00415e4f
 * Name: Inst4XMission::Setup
 * Namespace: Inst4XMission
 * Signature: void Setup(Inst4XMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Inst4XMission::Setup(Inst4XMission *this)

{
  PathSpawn *pPVar1;
  
  pPVar1 = operator_new(0x114c);
  if (pPVar1 == (PathSpawn *)0x0) {
    pPVar1 = (PathSpawn *)0x0;
  }
  else {
    pPVar1 = PathSpawn::PathSpawn(pPVar1,(AiMission *)this);
  }
  this->pathSpawn = pPVar1;
  (this->field20_0x50)._s_0.timeLeft = 0.0;
  (this->field19_0x4c)._s_0.firstFrame = true;
  (this->field19_0x4c)._s_0.gameOver = false;
  (this->field19_0x4c)._s_0.timerRunning = false;
  return;
}
