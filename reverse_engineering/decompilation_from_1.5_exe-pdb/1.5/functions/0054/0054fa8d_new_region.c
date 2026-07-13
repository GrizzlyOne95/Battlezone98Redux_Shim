/*
 * Entry: 0054fa8d
 * Name: new_region
 * Namespace: Global
 * Signature: SCROLL_REGION * new_region(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SCROLL_REGION * __cdecl new_region(void)

{
  SCROLL_REGION *pSVar1;
  
  pSVar1 = malloc(100);
  return pSVar1;
}
