/*
 * Entry: 00583221
 * Name: NewWrapper
 * Namespace: Global
 * Signature: wrap_struct * NewWrapper(wrap_struct * param_1, wrap_struct * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

wrap_struct * __cdecl NewWrapper(wrap_struct *param_1,wrap_struct *param_2,void *param_3)

{
  wrap_struct *pwVar1;
  
  pwVar1 = malloc(0xc);
  if (pwVar1 != (wrap_struct *)0x0) {
    pwVar1->ptr = param_3;
    pwVar1->next = param_1;
    pwVar1->prev = param_2;
    if (param_1 != (wrap_struct *)0x0) {
      param_1->prev = pwVar1;
    }
    if (param_2 != (wrap_struct *)0x0) {
      param_2->next = pwVar1;
    }
  }
  return pwVar1;
}
