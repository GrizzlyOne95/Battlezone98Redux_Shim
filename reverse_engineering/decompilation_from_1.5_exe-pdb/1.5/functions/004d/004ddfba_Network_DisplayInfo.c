/*
 * Entry: 004ddfba
 * Name: Network_DisplayInfo
 * Namespace: Global
 * Signature: void Network_DisplayInfo(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Network_DisplayInfo(CAMERA *param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float10 fVar9;
  float local_11c;
  int local_118;
  long local_114;
  long local_110;
  float local_100;
  int local_fc;
  float local_f8;
  long local_f4;
  float local_f0;
  float local_ec;
  long local_e8;
  long local_e4;
  long local_e0;
  float local_dc;
  _GRAPHIC_BUFFER *local_d8;
  float local_d4;
  char local_d0 [88];
  undefined1 local_78 [112];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_78;
  if ((net_display != 0) && (Net::dp != (dp_s *)0x0)) {
    local_d8 = param_1->Buffer;
    iVar3 = (Default_Font->char_height * 0x1e0) / Device.Viewport.Height;
    iVar7 = iVar3 + 4;
    local_dc = Get_Time();
    dpGetStats(Net::dp,3,&local_118,0x18);
    iVar6 = local_118;
    local_fc = local_118;
    dpGetStats(Net::dp,1,&local_118,0x18);
    local_e0 = local_118;
    dpGetStats(Net::dp,2,&local_118,0x18);
    total_bytes_received = local_118;
    dpGetStats(Net::dp,0,&local_118,0x18);
    local_e4 = local_118;
    dpGetStats(Net::dp,7,&local_118,0x18);
    total_msg_sent = local_114;
    dropped_packets = local_110;
    dpGetStats(Net::dp,5,&local_118,0x18);
    local_e8 = local_114;
    dpGetStats(Net::dp,6,&local_118,0x18);
    total_bytes_sent = local_114;
    dpGetStats(Net::dp,4,&local_118,0x18);
    iVar8 = total_frames + 1;
    local_f4 = local_114;
    total_frames = iVar8;
    fVar9 = (float10)floor((double)local_dc);
    local_d4 = (float)fVar9;
    fVar9 = (float10)floor((double)last_time);
    if ((float10)local_d4 != fVar9) {
      fVar1 = local_dc - last_time_saved_time;
      iVar4 = total_bytes_received - old_total_bytes_received;
      old_total_bytes_received = total_bytes_received;
      iVar5 = local_e4 - old_total_bytes_received_rel;
      bps_recv = (float)(iVar4 * 8) / fVar1;
      old_total_bytes_received_rel = local_e4;
      iVar4 = iVar6 - old_total_msg_received;
      old_total_msg_received = iVar6;
      bps_recv_rel = (float)(iVar5 * 8) / fVar1;
      iVar6 = local_e0 - old_total_msg_received_rel;
      old_total_msg_received_rel = local_e0;
      iVar5 = total_bytes_sent - old_total_bytes_sent;
      mps_received = (float)iVar4 / fVar1;
      old_total_bytes_sent = total_bytes_sent;
      iVar4 = local_114 - old_total_bytes_sent_rel;
      mps_received_rel = (float)iVar6 / fVar1;
      old_total_bytes_sent_rel = local_114;
      iVar6 = total_msg_sent - old_total_msg_sent;
      bps_sent = (float)(iVar5 * 8) / fVar1;
      old_total_msg_sent = total_msg_sent;
      iVar5 = local_e8 - old_total_msg_sent_rel;
      bps_sent_rel = (float)(iVar4 * 8) / fVar1;
      old_total_msg_sent_rel = local_e8;
      local_d4 = (float)(iVar8 - old_total_frames);
      mps_sent = (float)iVar6 / fVar1;
      mps_sent_rel = (float)iVar5 / fVar1;
      fps = (float)(int)local_d4 / fVar1;
      last_time_saved_time = local_dc;
      old_total_frames = iVar8;
    }
    last_time = local_dc;
    Font_Set_Background(Default_Font,-1);
    Font_Set_Foreground(Default_Font,DisplayInterface::colorWhite);
    sprintf(local_d0,"Time: %.1f | %.1f fps",SUB84((double)local_dc,0),
            (int)((ulonglong)(double)local_dc >> 0x20),SUB84((double)fps,0),
            (int)((ulonglong)(double)fps >> 0x20));
    Font_Print_String_Normalized(Default_Font,local_d8,400,0xfa,local_d0);
    local_11c = 0.0;
    local_f0 = local_11c;
    local_f8 = local_11c;
    local_100 = local_11c;
    fVar2 = local_11c;
    local_ec = local_11c;
    fVar1 = local_11c;
    if (0.0 < local_dc) {
      fVar1 = (float)(total_bytes_received << 3) / local_dc;
      local_ec = (float)(local_e4 << 3) / local_dc;
      fVar2 = (float)local_fc / local_dc;
      local_100 = (float)local_e0 / local_dc;
      local_f8 = (float)(total_bytes_sent << 3) / local_dc;
      local_f0 = (float)(local_f4 << 3) / local_dc;
      local_11c = (float)total_msg_sent / local_dc;
    }
    local_d4 = 0.0;
    if (0.0 < local_dc) {
      local_d4 = (float)local_e8 / local_dc;
    }
    local_dc = fVar2;
    sprintf(local_d0,"BW: %ld bytes | %ld bits",Net::dwBandwidth,Net::dwBandwidth << 3);
    Font_Print_String_Normalized(Default_Font,local_d8,400,iVar3 + 0xfe,local_d0);
    sprintf(local_d0,"RX(U): total %ld | bps %.0f | avg %.0f",total_bytes_received,
            SUB84((double)bps_recv,0),(int)((ulonglong)(double)bps_recv >> 0x20),
            SUB84((double)fVar1,0),(int)((ulonglong)(double)fVar1 >> 0x20));
    Font_Print_String_Normalized(Default_Font,local_d8,400,iVar3 + 0xfe + iVar7,local_d0);
    sprintf(local_d0,"        msgs %ld | mps %.0f | avg %.0f",local_fc,SUB84((double)mps_received,0)
            ,(int)((ulonglong)(double)mps_received >> 0x20),SUB84((double)local_dc,0),
            (int)((ulonglong)(double)local_dc >> 0x20));
    Font_Print_String_Normalized(Default_Font,local_d8,400,iVar7 * 3 + 0xfa,local_d0);
    sprintf(local_d0,"RX(R): total %ld | bps %.0f | avg %.0f",local_e4,SUB84((double)bps_recv_rel,0)
            ,(int)((ulonglong)(double)bps_recv_rel >> 0x20),SUB84((double)local_ec,0),
            (int)((ulonglong)(double)local_ec >> 0x20));
    Font_Print_String_Normalized(Default_Font,local_d8,400,iVar7 * 4 + 0xfa,local_d0);
    sprintf(local_d0,"        msgs %ld | mps %.0f | avg %.0f",local_e0,
            SUB84((double)mps_received_rel,0),(int)((ulonglong)(double)mps_received_rel >> 0x20),
            SUB84((double)local_100,0),(int)((ulonglong)(double)local_100 >> 0x20));
    Font_Print_String_Normalized(Default_Font,local_d8,400,(iVar3 + 0x36) * 5,local_d0);
    sprintf(local_d0,"TX(U): total %ld | bps %.0f | avg %.0f",total_bytes_sent,
            SUB84((double)bps_sent,0),(int)((ulonglong)(double)bps_sent >> 0x20),
            SUB84((double)local_f8,0),(int)((ulonglong)(double)local_f8 >> 0x20));
    Font_Print_String_Normalized(Default_Font,local_d8,400,iVar7 * 6 + 0xfa,local_d0);
    sprintf(local_d0,"        msgs %ld | mps %.0f | avg %.0f | drop %ld",total_msg_sent,
            SUB84((double)mps_sent,0),(int)((ulonglong)(double)mps_sent >> 0x20),
            SUB84((double)local_11c,0),(int)((ulonglong)(double)local_11c >> 0x20),dropped_packets);
    Font_Print_String_Normalized(Default_Font,local_d8,400,iVar7 * 7 + 0xfa,local_d0);
    sprintf(local_d0,"TX(R): total %ld | bps %.0f | avg %.0f",local_f4,SUB84((double)bps_sent_rel,0)
            ,(int)((ulonglong)(double)bps_sent_rel >> 0x20),SUB84((double)local_f0,0),
            (int)((ulonglong)(double)local_f0 >> 0x20));
    Font_Print_String_Normalized(Default_Font,local_d8,400,iVar7 * 8 + 0xfa,local_d0);
    sprintf(local_d0,"        msgs %ld | mps %.0f | avg %.0f",local_e8,SUB84((double)mps_sent_rel,0)
            ,(int)((ulonglong)(double)mps_sent_rel >> 0x20),SUB84((double)local_d4,0),
            (int)((ulonglong)(double)local_d4 >> 0x20));
    Font_Print_String_Normalized(Default_Font,local_d8,400,iVar7 * 9 + 0xfa,local_d0);
    sprintf(local_d0,"DObj: pkts %d | objs %d | comp %d | orig %d",tempstate_packets,
            tempstate_objects,tempstate_compressed,tempstate_uncompressed);
    Font_Print_String_Normalized(Default_Font,local_d8,400,(iVar3 + 0x1d) * 10,local_d0);
  }
  return;
}
