
/*

librabbitmq

APIs

*/

#include <windows.h>
#include <string.h>
#include <time.h>

#include "hbapi.h"
#include "hbapierr.h"
#include "hbapilng.h"
#include "hbapiitm.h"
#include "hbwinuni.h"

#include <amqp_tcp_socket.h>
#include <amqp.h>
#include <amqp_framing.h>

typedef struct _MQ_CONN
{
   amqp_connection_state_t conn;
} MQ_CONN, * PMQ_CONN;

typedef amqp_envelope_t* PENVELOPE;

HB_FUNC( AMQP_NEW_CONNECTION );
HB_FUNC( AMQP_CONNECTION_CLOSE );
HB_FUNC( AMQP_DESTROY_CONNECTION );
HB_FUNC( AMQP_TCP_SOCKET_NEW );
HB_FUNC( AMQP_SOCKET_OPEN );
HB_FUNC( AMQP_LOGIN );
HB_FUNC( AMQP_CHANNEL_OPEN );
HB_FUNC( AMQP_CHANNEL_CLOSE );
HB_FUNC( AMQP_EXCHANGE_DECLARE );
HB_FUNC( AMQP_BASIC_PUBLISH );
HB_FUNC( AMQP_BASIC_CONSUME );
HB_FUNC( AMQP_BASIC_ACK);
HB_FUNC( AMQP_CONSUME_MESSAGE);
HB_FUNC( AMQP_DESTROY_ENVELOPE );
HB_FUNC( AMQP_ENVELOPE_NEW );
HB_FUNC( AMQP_ENVELOPE_GETMESSAGEBODY );
HB_FUNC( AMQP_ENVELOPE_GETDELIVERYTAG );
HB_FUNC( AMQP_ENVELOPE_GETROUTINGKEY);
HB_FUNC( AMQP_ENVELOPE_GETEXCHANGE);

HB_FUNC( AMQP_MAYBE_RELEASE_BUFFERS);

static amqp_response_type_enum decode_reply( amqp_rpc_reply_t x, char const * context );
static int decode_status( int status, char const * context );
