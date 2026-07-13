/*
 * Entry: 004021b7
 * Name: std::allocator<AiMissionClass_*>::construct
 * Namespace: std::allocator<AiMissionClass_*>
 * Signature: void construct(allocator<AiMissionClass_*> * this, AiMissionClass * * param_1, AiMissionClass * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<AiMissionClass_*>::construct
          (allocator<AiMissionClass_*> *this,AiMissionClass **param_1,AiMissionClass **param_2)

{
  if (param_1 != (AiMissionClass **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
