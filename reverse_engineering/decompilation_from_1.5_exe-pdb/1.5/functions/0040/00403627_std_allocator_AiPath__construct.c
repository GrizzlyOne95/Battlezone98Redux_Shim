/*
 * Entry: 00403627
 * Name: std::allocator<AiPath_*>::construct
 * Namespace: std::allocator<AiPath_*>
 * Signature: void construct(allocator<AiPath_*> * this, AiPath * * param_1, AiPath * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<AiPath_*>::construct(allocator<AiPath_*> *this,AiPath **param_1,AiPath **param_2)

{
  if (param_1 != (AiPath **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
