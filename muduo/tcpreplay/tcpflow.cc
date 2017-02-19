#include "tcpflow.h"

void TcpFlow::Init()
{
    regcomp(&reg_tcpflow,tcpflow_header,REG_EXTENDED);
}
