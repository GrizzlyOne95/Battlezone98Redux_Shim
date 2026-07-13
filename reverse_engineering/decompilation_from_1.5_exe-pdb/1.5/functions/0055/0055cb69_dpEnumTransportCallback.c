/*
 * Entry: 0055cb69
 * Name: dpEnumTransportCallback
 * Namespace: Global
 * Signature: void dpEnumTransportCallback(dp_transport_t * param_1, comm_driverInfo_t * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl
dpEnumTransportCallback(dp_transport_t *param_1,comm_driverInfo_t *param_2,void *param_3)

{
  WPARAM wParam;
  LRESULT LVar1;
  int iVar2;
  PortData *pPVar3;
  int iVar4;
  comm_driverInfo_t *pcVar5;
  int *piVar6;
  sTransport *psVar7;
  comm_driverInfo_t *pcVar8;
  dp_transport_t *local_2b8;
  PortData *local_2b4;
  int local_2b0 [30];
  undefined1 local_238 [560];
  uint local_8;
  
  iVar2 = iTransportCount;
  local_8 = __security_cookie ^ (uint)local_238;
  local_2b8 = param_1;
  local_2b4 = param_3;
  if ((param_2->capabilities & 1) != 0) {
    psVar7 = Transport + iTransportCount;
    for (iVar4 = 0x20; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(undefined4 *)(psVar7->dp_transport).fname = *(undefined4 *)param_1;
      param_1 = (dp_transport_t *)((int)param_1 + 4);
      psVar7 = (sTransport *)((psVar7->dp_transport).fname + 4);
    }
    pcVar5 = param_2;
    pcVar8 = &Transport[iVar2].comm_driverInfo;
    for (iVar4 = 0xc; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(undefined4 *)pcVar8->signature = *(undefined4 *)pcVar5->signature;
      pcVar5 = (comm_driverInfo_t *)(pcVar5->signature + 4);
      pcVar8 = (comm_driverInfo_t *)(pcVar8->signature + 4);
    }
    *(undefined2 *)pcVar8->signature = *(undefined2 *)pcVar5->signature;
    wParam = SendMessageA(param_3,0x180,0,(LPARAM)param_2->name);
    if (((wParam != 0xffffffff) && (wParam != 0xfffffffe)) &&
       (LVar1 = SendMessageA((HWND)local_2b4,0x19a,wParam,iTransportCount), LVar1 != -1)) {
      iTransportCount = iTransportCount + 1;
    }
  }
  if (((param_2->needs & 4) != 0) &&
     (iVar2 = dpEnumPorts(local_2b8,local_2b0,10,&local_2b8), iVar2 == 0)) {
    if ((param_2->needs & 0x80) == 0) {
      iVar2 = 0;
      if (0 < (int)local_2b8) {
        piVar6 = local_2b0;
        do {
          pPVar3 = operator_new(8);
          if (pPVar3 == (PortData *)0x0) {
            local_2b4 = (PortData *)0x0;
          }
          else {
            local_2b4 = PortData::PortData(pPVar3,*piVar6,(char *)(piVar6 + 1));
          }
          std::vector<PortData_*,std::allocator<PortData_*>_>::push_back
                    (&nullmodem_portlist,&local_2b4);
          iVar2 = iVar2 + 1;
          piVar6 = piVar6 + 0x11;
        } while (iVar2 < (int)local_2b8);
      }
    }
    else {
      iVar2 = 0;
      if (0 < (int)local_2b8) {
        piVar6 = local_2b0;
        do {
          pPVar3 = operator_new(8);
          if (pPVar3 == (PortData *)0x0) {
            local_2b4 = (PortData *)0x0;
          }
          else {
            local_2b4 = PortData::PortData(pPVar3,*piVar6,(char *)(piVar6 + 1));
          }
          std::vector<PortData_*,std::allocator<PortData_*>_>::push_back(&modem_portlist,&local_2b4)
          ;
          iVar2 = iVar2 + 1;
          piVar6 = piVar6 + 0x11;
        } while (iVar2 < (int)local_2b8);
      }
    }
  }
  return;
}
