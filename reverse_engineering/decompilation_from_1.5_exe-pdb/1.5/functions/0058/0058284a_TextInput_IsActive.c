/*
 * Entry: 0058284a
 * Name: TextInput_IsActive
 * Namespace: Global
 * Signature: void * TextInput_IsActive(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl TextInput_IsActive(void)

{
  wrap_struct *pwVar1;
  
  pwVar1 = region_list;
  while ((pwVar1 != (wrap_struct *)0x0 && ((*(uint *)((int)pwVar1->ptr + 0x124) & 0x100) == 0))) {
    pwVar1 = pwVar1->next;
  }
  return pwVar1;
}
