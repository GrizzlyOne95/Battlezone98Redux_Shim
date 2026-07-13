/*
 * Entry: 004dc5ab
 * Name: Chat_InputMessage
 * Namespace: Global
 * Signature: void Chat_InputMessage(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Chat_InputMessage(ushort param_1)

{
  int iVar1;
  ushort uVar2;
  char *local_4;
  
  destinations[0].dpid = 0;
  dest_count = 1;
  sprintf(destinations[0].d,"%s: ",ToAllBuf);
  iVar1 = dest_count;
  dest_count = dest_count + 1;
  destinations[iVar1].dpid = 1;
  sprintf(destinations[iVar1].d,"%s: ",ToAlliesBuf);
  uVar2 = NetPlayer_GetFirstPlayer(&local_4,(ulong *)0x0,(ulong *)0x0,(ulong *)0x0);
  for (; (uVar2 != 0xfa01 && ((uint)dest_count < 0x1e)); dest_count = dest_count + 1) {
    sprintf(destinations[dest_count].d,"%s %s (#%d): ",ToBuf,local_4,
            (int)((uVar2 - 0x28) + ((int)(uVar2 - 0x28) >> 0x1f & 3U)) >> 2);
    destinations[dest_count].dpid = uVar2;
    uVar2 = NetPlayer_GetNextPlayer(&local_4,(ulong *)0x0,(ulong *)0x0,(ulong *)0x0);
  }
  if (dest_count <= cur_dest) {
    cur_dest = 0;
  }
  TextInput_SetPrompt(chat_entry,destinations[cur_dest].d);
  TextInput_SetString(chat_entry,"");
  TextInput_ShowRegion(chat_entry,1);
  TextInput_AllowInput(chat_entry,1);
  Scroll_SetFlags(chat_display,1,0);
  return;
}
