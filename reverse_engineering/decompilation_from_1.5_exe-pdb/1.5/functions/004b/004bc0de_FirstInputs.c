/*
 * Entry: 004bc0de
 * Name: FirstInputs
 * Namespace: Global
 * Signature: void FirstInputs(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FirstInputs(void)

{
  read_mapping_table();
  read_gamekey_table();
  kbd_num = get_device_num_from_name("keyboard");
  (*input_funcs[kbd_num]->flush_key)();
  inputFound = 0;
  inputCalled = 0;
  return;
}
