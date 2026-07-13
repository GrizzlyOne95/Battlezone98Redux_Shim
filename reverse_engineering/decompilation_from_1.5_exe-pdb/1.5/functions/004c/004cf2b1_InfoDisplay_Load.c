/*
 * Entry: 004cf2b1
 * Name: InfoDisplay::Load
 * Namespace: InfoDisplay
 * Signature: bool Load(InfoDisplay * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

bool __thiscall InfoDisplay::Load(InfoDisplay *this,_iobuf *param_1)

{
  bool bVar1;
  long local_24;
  int local_20;
  int local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  ClearObjectives(this);
  local_1c = 0;
  bVar1 = ::in(param_1,&local_1c,4);
  local_20 = 0;
  if (0 < local_1c) {
    do {
      if (((bVar1 == false) || (bVar1 = ::in(param_1,local_18,0xe), !bVar1)) ||
         (bVar1 = ::in(param_1,&local_24,4), !bVar1)) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
      AddObjective(this,local_18,local_24,0.0);
      local_20 = local_20 + 1;
    } while (local_20 < local_1c);
  }
  if ((bVar1 != false) && (bVar1 = ::in(param_1,&this->objectiveLast,4), bVar1)) {
    return true;
  }
  return false;
}
