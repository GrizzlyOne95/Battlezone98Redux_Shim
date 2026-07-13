
undefined4 * __thiscall FUN_0071e810(undefined4 *param_1,undefined1 param_2,undefined1 param_3)

{
  *param_1 = websocketpp::processor::processor<struct_websocketpp::config::asio_client>::vftable;
  *(undefined1 *)(param_1 + 1) = param_2;
  *(undefined1 *)((int)param_1 + 5) = param_3;
  param_1[2] = &DAT_01e84800;
  return param_1;
}

