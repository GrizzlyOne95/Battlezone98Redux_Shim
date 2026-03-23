
undefined4 FUN_006baab0(undefined4 param_1,undefined4 param_2)

{
  switch(param_2) {
  case 1:
    basic_string<>("Generic asio transport policy error");
    break;
  case 2:
    basic_string<>("async_read_at_least call requested more bytes than buffer can store");
    break;
  case 3:
    basic_string<>("Underlying Transport Error");
    break;
  case 4:
    basic_string<>("Proxy connection failed");
    break;
  case 5:
    basic_string<>("Invalid proxy URI");
    break;
  case 6:
    basic_string<>("Invalid host or service");
    break;
  default:
    basic_string<>("Unknown");
  }
  return param_1;
}

