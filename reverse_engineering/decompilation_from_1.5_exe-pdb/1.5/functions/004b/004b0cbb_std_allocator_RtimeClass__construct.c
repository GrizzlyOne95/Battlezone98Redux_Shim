/*
 * Entry: 004b0cbb
 * Name: std::allocator<RtimeClass_*>::construct
 * Namespace: std::allocator<RtimeClass_*>
 * Signature: void construct(allocator<RtimeClass_*> * this, RtimeClass * * param_1, RtimeClass * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<RtimeClass_*>::construct
          (allocator<RtimeClass_*> *this,RtimeClass **param_1,RtimeClass **param_2)

{
  if (param_1 != (RtimeClass **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
