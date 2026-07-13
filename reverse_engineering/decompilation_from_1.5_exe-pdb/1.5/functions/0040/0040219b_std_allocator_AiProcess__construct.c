/*
 * Entry: 0040219b
 * Name: std::allocator<AiProcess_*>::construct
 * Namespace: std::allocator<AiProcess_*>
 * Signature: void construct(allocator<AiProcess_*> * this, AiProcess * * param_1, AiProcess * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<AiProcess_*>::construct
          (allocator<AiProcess_*> *this,AiProcess **param_1,AiProcess **param_2)

{
  if (param_1 != (AiProcess **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
