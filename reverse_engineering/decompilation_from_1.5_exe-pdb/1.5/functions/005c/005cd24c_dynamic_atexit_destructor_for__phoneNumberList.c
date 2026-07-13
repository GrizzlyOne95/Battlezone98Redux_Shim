/*
 * Entry: 005cd24c
 * Name: `dynamic_atexit_destructor_for_'phoneNumberList''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'phoneNumberList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__phoneNumberList__(void)

{
  phoneNumberList.hwnd = (HWND__ *)0x0;
  PhoneNumberList::Init(&phoneNumberList);
  return;
}
