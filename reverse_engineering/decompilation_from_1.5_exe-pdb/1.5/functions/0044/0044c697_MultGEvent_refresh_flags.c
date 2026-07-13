/*
 * Entry: 0044c697
 * Name: MultGEvent::refresh_flags
 * Namespace: MultGEvent
 * Signature: void refresh_flags(MultGEvent * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MultGEvent::refresh_flags(MultGEvent *this)

{
  bool bVar1;
  int iVar2;
  
  this->goal1amessage = 1;
  this->goal1bmessage = 1;
  this->goal2amessage = 1;
  this->goal2bmessage = 1;
  bVar1 = IsAlive(&this->goal1a);
  if (!bVar1) {
    iVar2 = BuildObject("abstor",1,"goal1a",0);
    this->goal1a = iVar2;
  }
  bVar1 = IsAlive(&this->goal1b);
  if (!bVar1) {
    iVar2 = BuildObject("abstor",1,"goal1b",0);
    this->goal1b = iVar2;
  }
  bVar1 = IsAlive(&this->goal2a);
  if (!bVar1) {
    iVar2 = BuildObject("abstor",2,"goal2a",0);
    this->goal2a = iVar2;
  }
  bVar1 = IsAlive(&this->goal2b);
  if (!bVar1) {
    iVar2 = BuildObject("abstor",2,"goal2b",0);
    this->goal2b = iVar2;
  }
  return;
}
