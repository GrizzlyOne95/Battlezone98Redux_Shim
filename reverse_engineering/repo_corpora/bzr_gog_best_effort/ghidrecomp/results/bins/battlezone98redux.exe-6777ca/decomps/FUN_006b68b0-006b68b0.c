
undefined4 FUN_006b68b0(undefined4 param_1,int param_2)

{
  if (param_2 < 0x12d) {
    if (param_2 == 300) {
      basic_string<>("Multiple Choices");
      return param_1;
    }
    switch(param_2) {
    case 0:
      basic_string<>("Uninitialized");
      break;
    default:
switchD_006b68f0_caseD_1:
      basic_string<>("Unknown");
      break;
    case 100:
      basic_string<>("Continue");
      break;
    case 0x65:
      basic_string<>("Switching Protocols");
      break;
    case 200:
      basic_string<>(&DAT_00896f00);
      break;
    case 0xc9:
      basic_string<>("Created");
      break;
    case 0xca:
      basic_string<>("Accepted");
      break;
    case 0xcb:
      basic_string<>("Non Authoritative Information");
      break;
    case 0xcc:
      basic_string<>("No Content");
      break;
    case 0xcd:
      basic_string<>("Reset Content");
      break;
    case 0xce:
      basic_string<>("Partial Content");
    }
  }
  else {
    switch(param_2) {
    case 0x12d:
      basic_string<>("Moved Permanently");
      break;
    case 0x12e:
      basic_string<>("Found");
      break;
    case 0x12f:
      basic_string<>("See Other");
      break;
    case 0x130:
      basic_string<>("Not Modified");
      break;
    case 0x131:
      basic_string<>("Use Proxy");
      break;
    default:
      goto switchD_006b68f0_caseD_1;
    case 0x133:
      basic_string<>("Temporary Redirect");
      break;
    case 400:
      basic_string<>("Bad Request");
      break;
    case 0x191:
      basic_string<>("Unauthorized");
      break;
    case 0x192:
      basic_string<>("Payment Required");
      break;
    case 0x193:
      basic_string<>("Forbidden");
      break;
    case 0x194:
      basic_string<>("Not Found");
      break;
    case 0x195:
      basic_string<>("Method Not Allowed");
      break;
    case 0x196:
      basic_string<>("Not Acceptable");
      break;
    case 0x197:
      basic_string<>("Proxy Authentication Required");
      break;
    case 0x198:
      basic_string<>("Request Timeout");
      break;
    case 0x199:
      basic_string<>("Conflict");
      break;
    case 0x19a:
      basic_string<>(&DAT_00897290);
      break;
    case 0x19b:
      basic_string<>("Length Required");
      break;
    case 0x19c:
      basic_string<>("Precondition Failed");
      break;
    case 0x19d:
      basic_string<>("Request Entity Too Large");
      break;
    case 0x19e:
      basic_string<>("Request-URI Too Long");
      break;
    case 0x19f:
      basic_string<>("Unsupported Media Type");
      break;
    case 0x1a0:
      basic_string<>("Requested Range Not Satisfiable");
      break;
    case 0x1a1:
      basic_string<>("Expectation Failed");
      break;
    case 0x1a2:
      basic_string<>("I\'m a teapot");
      break;
    case 0x1aa:
      basic_string<>("Upgrade Required");
      break;
    case 0x1ac:
      basic_string<>("Precondition Required");
      break;
    case 0x1ad:
      basic_string<>("Too Many Requests");
      break;
    case 0x1af:
      basic_string<>("Request Header Fields Too Large");
      break;
    case 500:
      basic_string<>("Internal Server Error");
      break;
    case 0x1f5:
      basic_string<>("Not Implemented");
      break;
    case 0x1f6:
      basic_string<>("Bad Gateway");
      break;
    case 0x1f7:
      basic_string<>("Service Unavailable");
      break;
    case 0x1f8:
      basic_string<>("Gateway Timeout");
      break;
    case 0x1f9:
      basic_string<>("HTTP Version Not Supported");
      break;
    case 0x1fe:
      basic_string<>("Not Extended");
      break;
    case 0x1ff:
      basic_string<>("Network Authentication Required");
    }
  }
  return param_1;
}

