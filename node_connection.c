

/*
 * send_conn_to_nginx()
 * send_conn_to_node
 * recv_conn_from_nginx
 * recv_conn_from_node
 */

static void ngx_http_nodejs_read_handler(ngx_event_t *ev) 
{
    ngx_connection_t *c = ev->data;
    ngx_int_t         rc;
    uint64_t          sig;

    while (1) {

        rc = read(c->fd, &sig, sizeof(sig));
        if (rc == -1) {
            err = ngx_errno;
        
            switch (err) {
            case NGX_EAGAIN:
                break;
        
            case NGX_EINTR:
                continue;
        
            default:
                ev->error = 1;
                /* TODO */
            }
        }
    }

    /* TODO: deque, set handler, adjuest request struct,  */

    if (ngx_add_conn) {
        ngx_add_conn(c);
    } else {
        ngx_add_event(c->read, NGX_READ_EVENT, 0);
        ngx_add_event(c->write, NGX_WRITE_EVENT, 0);
    }
    
}


/* send connection to nginx */
static void send_conn_to_nginx(ngx_connection_t *c)
{
    /* TODO: inqueue */
    ngx_http_nodejs_send_event.handler = ngx_http_nodejs_write_handler;
    ngx_http_nodejs_write_handler(&ngx_http_nodejs_send_event);
}

static ngx_event_t ngx_http_nodejs_send_event;

static void
ngx_http_nodejs_empty_handler(ngx_event_t *wev)
{
    ngx_log_debug0(NGX_LOG_DEBUG_EVENT, wev->log, 0, "http nodejs empty handler");

    return;
}


/* send connection to nginx */
static void 
ngx_http_nodejs_write_handler(ngx_event_t *ev)
{
    /* TODO: send connections to node */
    ngx_connection_t *c = ev->data;
    ngx_int_t         rc;
    uint64_t          sig = 1ULL;

    while (1) {

        rc = write(c->fd, &sig, sizeof(sig));
        if (rc == -1) {
            err = ngx_errno;
        
            switch (err) {
            case NGX_EAGAIN:
                return;
        
            case NGX_EINTR:
                continue;
        
            default:
                ev->error = 1;
                /* TODO */
            }
        }

        /* OK */
        ev->handler = ngx_http_nodejs_empty_handler;
        return;
    }

}

/* used to send message to node */
static uv_async_t uv_async;


void uv_cb(uv_async_t* handle, int status)
{
    /* TODO: transfer request to Node and call onRequest callback */;

    
}


static ngx_inline void send_conn_to_node(ngx_connection_t *c)
{
    if (ngx_del_conn) {
        ngx_del_conn(c);
    } else {
        ngx_del_event(c->read);
        ngx_del_event(c->write);
    }
    
    /* TODO: inqueue */

    
    uv_async_send(&uv_async);
}

ngx_int_t xxx () {
    return uv_async_init(uv_default_loop(), &uv_async, uv_cb);
}


