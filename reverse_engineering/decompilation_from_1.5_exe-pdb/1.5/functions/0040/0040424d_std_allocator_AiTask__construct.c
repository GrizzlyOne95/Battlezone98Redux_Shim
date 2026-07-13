/*
 * Entry: 0040424d
 * Name: std::allocator<AiTask_*>::construct
 * Namespace: std::allocator<AiTask_*>
 * Signature: void construct(allocator<AiTask_*> * this, AiTask * * param_1, AiTask * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<AiTask_*>::construct(allocator<AiTask_*> *this,AiTask **param_1,AiTask **param_2)

{
  if (param_1 != (AiTask **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
