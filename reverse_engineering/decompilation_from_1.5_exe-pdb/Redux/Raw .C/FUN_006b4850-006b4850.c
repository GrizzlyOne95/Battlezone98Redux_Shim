
undefined4 FUN_006b4850(undefined4 param_1,undefined4 param_2)

{
  switch(param_2) {
  case 1:
    basic_string<>("Generic transport policy error");
    break;
  case 2:
    basic_string<>("Underlying Transport Error");
    break;
  case 3:
    basic_string<>("async_read_at_least call requested more bytes than buffer can store");
    break;
  default:
    basic_string<>("Unknown");
    break;
  case 5:
    basic_string<>("The operation was aborted");
    break;
  case 6:
    basic_string<>("The operation is not supported by this transport");
    break;
  case 7:
    basic_string<>("End of File");
    break;
  case 8:
    basic_string<>("TLS Short Read");
    break;
  case 9:
    basic_string<>("Timer Expired");
    break;
  case 10:
    basic_string<>("A transport action was requested after shutdown");
    break;
  case 0xb:
    basic_string<>("Generic TLS related error");
  }
  return param_1;
}

