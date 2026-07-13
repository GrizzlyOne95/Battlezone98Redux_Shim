/*
 * Entry: 0044e890
 * Name: `vector_constructor_iterator'
 * Namespace: Global
 * Signature: void `vector_constructor_iterator'(void * param_1, uint param_2, int param_3, _func___thiscall_void_ptr_void_ptr * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
_vector_constructor_iterator_
          (void *param_1,uint param_2,int param_3,_func___thiscall_void_ptr_void_ptr *param_4)

{
  while (param_3 = param_3 + -1, -1 < param_3) {
    (*param_4)(param_1);
    param_1 = (void *)((int)param_1 + param_2);
  }
  return;
}
