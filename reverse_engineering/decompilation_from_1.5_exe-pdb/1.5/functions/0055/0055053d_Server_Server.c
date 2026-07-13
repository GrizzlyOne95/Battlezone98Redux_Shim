/*
 * Entry: 0055053d
 * Name: Server::Server
 * Namespace: Server
 * Signature: Server * Server(Server * this, char * param_1, long param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Server * __thiscall Server::Server(Server *this,char *param_1,long param_2,long param_3)

{
  strncpy(this->caName,param_1,0x7f);
  this->avg_ms = param_2;
  this->nr_pl = param_3;
  this->caName[0x7f] = '\0';
  this->mark = 0x14;
  return this;
}
