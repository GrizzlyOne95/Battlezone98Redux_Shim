/*
 * Entry: 0048a295
 * Name: DistributedObject::SendBuf
 * Namespace: DistributedObject
 * Signature: int SendBuf(char * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl DistributedObject::SendBuf(char *param_1,int param_2)

{
  int iVar1;
  DWORD DVar2;
  dp_s *unaff_ESI;
  
  send_it_anyways = 0;
  iVar1 = 3;
  if (dp != (dp_s *)0x0) {
    iVar1 = Net::Send(dp,global_activnet_id,0,0,param_1,param_2);
    if (iVar1 == 0) {
      Ordnance_Sent(1);
      DVar2 = Get_TimeNow();
      if ((DVar2 < Net::dwLastByteSentTime) || (1000 < DVar2 - Net::dwLastByteSentTime)) {
        Net::dwLastByteSentTime = DVar2;
        Net::dwLastByteSentCount = GetTotalBytesSent(unaff_ESI);
      }
      return 0;
    }
  }
  Ordnance_Sent(0);
  return iVar1;
}
