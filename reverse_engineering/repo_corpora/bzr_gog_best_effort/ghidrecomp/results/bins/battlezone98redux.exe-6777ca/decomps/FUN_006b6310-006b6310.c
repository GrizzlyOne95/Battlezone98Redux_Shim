
char * FUN_006b6310(uint param_1)

{
  char *pcVar1;
  
  if (param_1 < 0x81) {
    if (param_1 == 0x80) {
      return "endpoint";
    }
    switch(param_1) {
    case 1:
      pcVar1 = "connect";
      break;
    case 2:
      pcVar1 = "disconnect";
      break;
    default:
      goto switchD_006b634d_caseD_3;
    case 4:
      pcVar1 = "control";
      break;
    case 8:
      pcVar1 = "frame_header";
      break;
    case 0x10:
      pcVar1 = "frame_payload";
      break;
    case 0x20:
      pcVar1 = "message_header";
      break;
    case 0x40:
      pcVar1 = "message_payload";
    }
  }
  else {
    if (param_1 < 0x801) {
      if (param_1 == 0x800) {
        return "application";
      }
      if (param_1 == 0x100) {
        return "debug_handshake";
      }
      if (param_1 == 0x200) {
        return "debug_close";
      }
      if (param_1 == 0x400) {
        return "devel";
      }
    }
    else {
      if (param_1 == 0x1000) {
        return "http";
      }
      if (param_1 == 0x2000) {
        return "fail";
      }
    }
switchD_006b634d_caseD_3:
    pcVar1 = "unknown";
  }
  return pcVar1;
}

