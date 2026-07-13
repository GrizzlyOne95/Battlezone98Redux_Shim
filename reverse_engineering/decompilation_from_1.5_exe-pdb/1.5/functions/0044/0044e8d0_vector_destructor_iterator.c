/*
 * Entry: 0044e8d0
 * Name: `vector_destructor_iterator'
 * Namespace: Global
 * Signature: void `vector_destructor_iterator'(void * param_1, uint param_2, int param_3, _func___thiscall_void_void_ptr * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
_vector_destructor_iterator_
          (void *param_1,uint param_2,int param_3,_func___thiscall_void_void_ptr *param_4)

{
  void *pvVar1;
  
  pvVar1 = (void *)((int)param_1 + param_2 * param_3);
  while (param_3 = param_3 + -1, -1 < param_3) {
    pvVar1 = (void *)((int)pvVar1 - param_2);
    (*param_4)(pvVar1);
  }
  return;
}
