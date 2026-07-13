/*
 * Entry: 004ee11f
 * Name: Spinner_New
 * Namespace: Global
 * Signature: SPINNER * Spinner_New(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SPINNER * __cdecl Spinner_New(void)

{
  SPINNER *pSVar1;
  
  pSVar1 = obj_class_alloc(0x14);
  if (pSVar1 == (SPINNER *)0x0) {
    return (SPINNER *)0x0;
  }
  pSVar1->current_DDR = 400;
  (pSVar1->omega).x = 0.0;
  (pSVar1->omega).y = 0.7853982;
  (pSVar1->omega).z = 0.0;
  pSVar1->max_DDR = 400;
  return pSVar1;
}
