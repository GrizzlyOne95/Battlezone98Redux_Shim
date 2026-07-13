/*
 * Entry: 0049876a
 * Name: GameObject::operator_new
 * Namespace: GameObject
 * Signature: void * operator_new(uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl GameObject::operator_new(uint param_1)

{
  Scrap **ppSVar1;
  _func_int_uint *p_Var2;
  char (*pacVar3) [1024];
  
  if (freeObject < 0) {
    if (((int)Scrap::scrapList._Mylast - (int)Scrap::scrapList._Myfirst & 0xfffffffcU) != 0) {
      ppSVar1 = std::vector<Scrap_*,std::allocator<Scrap_*>_>::front(&Scrap::scrapList);
      (**(code **)((*ppSVar1)->_padding_ + 0x10))();
    }
    if (freeObject < 0) {
      p_Var2 = _query_new_handler();
      if (p_Var2 != (_func_int_uint *)0x0) {
        (*p_Var2)(param_1);
      }
      return (void *)0x0;
    }
  }
  pacVar3 = gameObjectBuffer + freeObject;
  freeObjectCount = freeObjectCount + -1;
  freeObject = *(int *)(gameObjectBuffer[freeObject] + 0x178);
  return pacVar3;
}
