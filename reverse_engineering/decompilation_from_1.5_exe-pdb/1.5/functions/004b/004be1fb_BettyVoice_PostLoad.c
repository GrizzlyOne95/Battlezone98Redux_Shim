/*
 * Entry: 004be1fb
 * Name: BettyVoice::PostLoad
 * Namespace: BettyVoice
 * Signature: void PostLoad(BettyVoice * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BettyVoice::PostLoad(BettyVoice *this)

{
  char cVar1;
  GameObjectClass *pGVar2;
  int iVar3;
  int iVar4;
  char (*_Dest) [16];
  char local_9;
  int iStack_8;
  
  cVar1 = 'a';
  if (GameObject::userObject != (GameObject *)0x0) {
    pGVar2 = GameObject::userObject->curPilot;
    if (pGVar2 == (GameObjectClass *)0x0) {
      pGVar2 = (GameObjectClass *)(**(code **)GameObject::userObject->_padding_)();
    }
    cVar1 = pGVar2->nation;
    if (cVar1 == 'c') {
      local_9 = 's';
      goto LAB_004be237;
    }
  }
  local_9 = 'a';
LAB_004be237:
  iVar4 = 1;
  _Dest = this->VoiceSound;
  iStack_8 = 0xe;
  do {
    sprintf(*_Dest,"%cbetty%d.wav",(int)cVar1,iVar4);
    iVar3 = ItemExists(*_Dest);
    if (iVar3 == 0) {
      sprintf(*_Dest,"%cbetty%d.wav",(int)local_9,iVar4);
    }
    _Dest = _Dest + 1;
    iVar4 = iVar4 + 1;
    iStack_8 = iStack_8 + -1;
  } while (iStack_8 != 0);
  this->messageFirst = this->messageQueue;
  this->messageLast = this->messageQueue;
  voiceReady = true;
  this->nextAttack = -1e+30;
  return;
}
