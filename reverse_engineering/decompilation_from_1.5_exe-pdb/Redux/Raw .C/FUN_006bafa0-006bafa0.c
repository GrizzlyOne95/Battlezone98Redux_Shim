
undefined4 FUN_006bafa0(undefined4 param_1,undefined4 param_2)

{
  switch(param_2) {
  case 1:
    basic_string<>("Security policy error");
    break;
  case 2:
    basic_string<>("Socket component error");
    break;
  case 3:
    basic_string<>("Invalid state");
    break;
  case 4:
    basic_string<>("Invalid or empty TLS context supplied");
    break;
  case 5:
    basic_string<>("TLS handshake timed out");
    break;
  case 6:
    basic_string<>("Pass through from socket policy");
    break;
  case 7:
    basic_string<>("Required tls_init handler not present.");
    break;
  case 8:
    basic_string<>("TLS handshake failed");
    break;
  case 9:
    basic_string<>("Failed to set TLS SNI hostname");
    break;
  default:
    basic_string<>("Unknown");
  }
  return param_1;
}

