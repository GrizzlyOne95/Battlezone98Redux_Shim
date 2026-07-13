/*
 * Entry: 004dce65
 * Name: updown_callback
 * Namespace: Global
 * Signature: int updown_callback(void * * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl updown_callback(void **param_1,int param_2)

{
  ushort uVar1;
  
  if (param_2 == 0) {
    cur_dest = cur_dest + 1;
    if (dest_count <= cur_dest) {
      cur_dest = 0;
    }
    uVar1 = Net_GetMyPlayerID();
    if ((destinations[cur_dest].dpid == uVar1) && (cur_dest = cur_dest + 1, dest_count <= cur_dest))
    {
      cur_dest = 0;
    }
  }
  else {
    cur_dest = cur_dest + -1;
    if (cur_dest < 0) {
      cur_dest = dest_count + -1;
    }
    uVar1 = Net_GetMyPlayerID();
    if ((destinations[cur_dest].dpid == uVar1) && (cur_dest = cur_dest + -1, cur_dest < 0)) {
      cur_dest = dest_count + -1;
    }
  }
  TextInput_SetPrompt(chat_entry,destinations[cur_dest].d);
  return 1;
}
