
undefined4 FUN_006bbd50(undefined4 param_1,undefined4 param_2)

{
  switch(param_2) {
  case 1:
    basic_string<>("Generic processor error");
    break;
  case 2:
    basic_string<>("invalid user input");
    break;
  case 3:
    basic_string<>("Generic protocol violation");
    break;
  case 4:
    basic_string<>("A message was too large");
    break;
  case 5:
    basic_string<>("A payload contained invalid data");
    break;
  case 6:
    basic_string<>("invalid function arguments");
    break;
  case 7:
    basic_string<>("invalid opcode");
    break;
  case 8:
    basic_string<>("Control messages are limited to fewer than 125 characters");
    break;
  case 9:
    basic_string<>("Invalid use of reserved bits");
    break;
  case 10:
    basic_string<>("Control messages cannot be fragmented");
    break;
  case 0xb:
    basic_string<>("Invalid message continuation");
    break;
  case 0xc:
    basic_string<>("Clients may not send unmasked frames");
    break;
  case 0xd:
    basic_string<>("Servers may not send masked frames");
    break;
  case 0xe:
    basic_string<>("Payload length was not minimally encoded");
    break;
  case 0xf:
    basic_string<>("64 bit frames are not supported on 32 bit systems");
    break;
  case 0x10:
    basic_string<>("Invalid UTF8 encoding");
    break;
  case 0x11:
    basic_string<>("Operation required not implemented functionality");
    break;
  case 0x12:
    basic_string<>("Invalid HTTP method.");
    break;
  case 0x13:
    basic_string<>("Invalid HTTP version.");
    break;
  case 0x14:
    basic_string<>("Invalid HTTP status.");
    break;
  case 0x15:
    basic_string<>("A required HTTP header is missing");
    break;
  case 0x16:
    basic_string<>("SHA-1 library error");
    break;
  case 0x17:
    basic_string<>("The WebSocket protocol version in use does not support this feature");
    break;
  case 0x18:
    basic_string<>("Reserved close code used");
    break;
  case 0x19:
    basic_string<>("Invalid close code used");
    break;
  case 0x1a:
    basic_string<>("Using a close reason requires a valid close code");
    break;
  case 0x1b:
    basic_string<>("Error parsing subprotocol header");
    break;
  case 0x1c:
    basic_string<>("Error parsing extension header");
    break;
  case 0x1d:
    basic_string<>("Extensions are disabled");
    break;
  case 0x1e:
    basic_string<>("Short Hybi00 Key 3 read");
    break;
  default:
    basic_string<>("Unknown");
  }
  return param_1;
}

