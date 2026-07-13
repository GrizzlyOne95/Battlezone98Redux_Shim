/*
 * Entry: 00518447
 * Name: std::allocator<ObjectClassInfo_*>::allocate
 * Namespace: std::allocator<ObjectClassInfo_*>
 * Signature: ObjectClassInfo * * allocate(allocator<ObjectClassInfo_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ObjectClassInfo ** __thiscall
std::allocator<ObjectClassInfo_*>::allocate(allocator<ObjectClassInfo_*> *this,uint param_1)

{
  ObjectClassInfo **ppOVar1;
  
  ppOVar1 = _Allocate<ObjectClassInfo_*>(param_1,(ObjectClassInfo **)0x0);
  return ppOVar1;
}
