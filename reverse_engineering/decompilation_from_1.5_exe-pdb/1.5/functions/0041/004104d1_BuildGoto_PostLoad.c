/*
 * Entry: 004104d1
 * Name: BuildGoto::PostLoad
 * Namespace: BuildGoto
 * Signature: bool PostLoad(BuildGoto * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall BuildGoto::PostLoad(BuildGoto *this)

{
  bool bVar1;
  
  bVar1 = GotoTask::PostLoad((GotoTask *)this);
  if (this->buildClass != (GameObjectClass *)0x0) {
    Producer::StartBuild((Producer *)this->_padding_,this->buildClass);
  }
  return bVar1;
}
