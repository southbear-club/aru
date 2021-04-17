#include "aru/sdk/event/nlog.hpp"
#include "aru/sdk/macros/defs.hpp"
#include "aru/sdk/ds/list.hpp"
#include "aru/sdk/net/sock.hpp"
#include "aru/sdk/lock/lock.hpp"
#include "aru/sdk/memory/mem.hpp"

namespace aru {

namespace sdk {

typedef struct network_logger_s {
    hloop_t*            loop;
    hio_t*              listenio;
    struct list_head    clients;
} network_logger_t;

typedef struct nlog_client {
    hio_t*              io;
    struct list_node    node;
} nlog_client;

static network_logger_t s_logger;
static mutex_lock_t         s_mutex;

static void on_close(hio_t* io) {
    printd("on_close fd=%d error=%d\n", hio_fd(io), hio_error(io));

    nlog_client* client = (nlog_client*)hevent_userdata(io);
    if (client) {
        hevent_set_userdata(io, NULL);

        mutex_lock(&s_mutex);
        list_del(&client->node);
        mutex_unlock(&s_mutex);

        ARU_FREE(client);
    }
}

static void on_read(hio_t* io, void* buf, int readbytes) {
    printd("on_read fd=%d readbytes=%d\n", hio_fd(io), readbytes);
    printd("< %s\n", (char*)buf);
    // nothing to do
}

static void on_accept(hio_t* io) {
    /*
    printd("on_accept connfd=%d\n", hio_fd(io));
    char localaddrstr[SOCKADDR_STRLEN] = {0};
    char peeraddrstr[SOCKADDR_STRLEN] = {0};
    printd("accept connfd=%d [%s] <= [%s]\n", hio_fd(io),
            SOCKADDR_STR(hio_localaddr(io), localaddrstr),
            SOCKADDR_STR(hio_peeraddr(io), peeraddrstr));
    */

    hio_setcb_read(io, on_read);
    hio_setcb_close(io, on_close);
    hio_read(io);

    // free on_close
    nlog_client* client;
    ARU_ALLOC_SIZEOF(client);
    client->io = io;
    hevent_set_userdata(io, client);

    mutex_lock(&s_mutex);
    list_add(&client->node, &s_logger.clients);
    mutex_unlock(&s_mutex);
}

void network_logger(int loglevel, const char* buf, int len) {
    struct list_node* node;
    nlog_client* client;

    mutex_lock(&s_mutex);
    list_for_each (node, &s_logger.clients) {
        client = list_entry(node, nlog_client, node);
        hio_write(client->io, buf, len);
    }
    mutex_unlock(&s_mutex);
}

hio_t* nlog_listen(hloop_t* loop, int port) {
    s_logger.loop = loop;
    s_logger.listenio = hloop_create_tcp_server(loop, "0.0.0.0", port, on_accept);
    list_init(&s_logger.clients);
    mutex_init(&s_mutex);
    return s_logger.listenio;
}

}
}