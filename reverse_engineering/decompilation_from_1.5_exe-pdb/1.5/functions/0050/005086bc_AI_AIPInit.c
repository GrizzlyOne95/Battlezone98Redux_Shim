/*
 * Entry: 005086bc
 * Name: AI_AIPInit
 * Namespace: Global
 * Signature: void AI_AIPInit(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_AIPInit(void)

{
  if (aip_initialised != 0) {
    tlog(1,"AI_AIPInit called twice without matching Close\n");
  }
  C_Linked_List_Init(&aip_list);
  aip_initialised = 1;
  AI_FSMInit();
  return;
}
