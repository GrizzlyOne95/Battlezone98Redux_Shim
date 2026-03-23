
undefined4 FUN_006b4ac0(undefined4 param_1,undefined4 param_2)

{
  switch(param_2) {
  case 1:
    basic_string<>("Generic error");
    break;
  case 2:
    basic_string<>("send queue full");
    break;
  case 3:
    basic_string<>("payload violation");
    break;
  case 4:
    basic_string<>("endpoint not secure");
    break;
  case 5:
    basic_string<>("endpoint not available");
    break;
  case 6:
    basic_string<>("invalid uri");
    break;
  case 7:
    basic_string<>("no outgoing message buffers");
    break;
  case 8:
    basic_string<>("no incoming message buffers");
    break;
  case 9:
    basic_string<>("invalid state");
    break;
  case 10:
    basic_string<>("Unable to extract close code");
    break;
  case 0xb:
    basic_string<>("Extracted close code is in a reserved range");
    break;
  case 0xc:
    basic_string<>("Extracted close code is in an invalid range");
    break;
  case 0xd:
    basic_string<>("Invalid UTF-8");
    break;
  case 0xe:
    basic_string<>("Invalid subprotocol");
    break;
  case 0xf:
    basic_string<>("Bad Connection");
    break;
  case 0x10:
    basic_string<>("Test Error");
    break;
  case 0x11:
    basic_string<>("Connection creation attempt failed");
    break;
  case 0x12:
    basic_string<>("Selected subprotocol was not requested by the client");
    break;
  case 0x13:
    basic_string<>("Feature not available on server endpoints");
    break;
  case 0x14:
    basic_string<>("Feature not available on client endpoints");
    break;
  case 0x15:
    basic_string<>("HTTP connection ended");
    break;
  case 0x16:
    basic_string<>("The opening handshake timed out");
    break;
  case 0x17:
    basic_string<>("The closing handshake timed out");
    break;
  case 0x18:
    basic_string<>("Invalid URI port");
    break;
  case 0x19:
    basic_string<>("Async Accept not listening");
    break;
  case 0x1a:
    basic_string<>("Operation canceled");
    break;
  case 0x1b:
    basic_string<>("Connection rejected");
    break;
  case 0x1c:
    basic_string<>("Upgrade required");
    break;
  case 0x1d:
    basic_string<>("Invalid version");
    break;
  case 0x1e:
    basic_string<>("Unsupported version");
    break;
  case 0x1f:
    basic_string<>("HTTP parse error");
    break;
  case 0x20:
    basic_string<>("Extension negotiation failed");
    break;
  default:
    basic_string<>("Unknown");
  }
  return param_1;
}

