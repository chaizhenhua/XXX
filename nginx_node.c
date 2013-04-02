

#include <ngx_core.h>
#include <ngx_http.h>

#include <node.h>

typedef struct {    
    ngx_str_t     *file;
    ngx_uint_t     line;
} ngx_http_nodejs_conf_t;

typedef struct {
    ngx_uint_t     script;
} ngx_http_nodejs_main_conf_t;

/*
 * One v8::Context and uv_loop per Thread.
 * Because there is no Context in uv_callback.
 */

typedef struct {
    v8::Context   *context;
    nginx::Server *server;
    uv_async_t     notifer;
} ngx_node_script_t;

static ngx_command_t ngx_http_nodejs_commands[] = {

    { ngx_string("nodejs"),
      NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_HTTP_LIF_CONF
                        |NGX_CONF_TAKE1,
      ngx_http_nodejs,
      NGX_HTTP_LOC_CONF_OFFSET,
      0,
      NULL },

      ngx_null_command
};


static ngx_http_module_t  ngx_http_nodejs_module_ctx = {
    ngx_http_nodejs_preconfig,               /* preconfiguration */
    ngx_http_nodejs_init,                    /* postconfiguration */

    ngx_http_nodejs_create_main_conf,        /* create main configuration */
    NULL,                                    /* init main configuration */

    NULL,                                    /* create server configuration */
    NULL,                                    /* merge server configuration */

    ngx_http_nodejs_create_conf,             /* create location configuration */
    ngx_http_nodejs_merge_conf               /* merge location configuration */
};


ngx_module_t  ngx_http_nodejs_module = {
    NGX_MODULE_V1,
    &ngx_http_nodejs_module_ctx,           /* module context */
    ngx_http_nodejs_commands,              /* module directives */
    NGX_HTTP_MODULE,                       /* module type */
    NULL,                                  /* init master */
    NULL,                                  /* init module */
    ngx_http_nodejs_process_init,          /* init process */
    ngx_http_nodejs_process_exit,          /* init thread */
    NULL,                                  /* exit thread */
    NULL,                                  /* exit process */
    NULL,                                  /* exit master */
    NGX_MODULE_V1_PADDING
};

static char *ngx_http_nodejs(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_nodejs_conf_t *njcf = conf;
    ngx_str_t              *value;

    if (mscf->config != NGX_CONF_UNSET_PTR) {
        return "is duplicate";
    }

    value = cf->args->elts;

    if (ngx_conf_full_name(cf->cycle, &value[1], 1) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

}

static ngx_int_t initialized;

static void *
ngx_http_nodejs_preconfig(ngx_conf_t *cf)
{
    if (!initialized) {
        V8::Initialize();
    }
}



/* read event for output */
static ngx_event_t ** ngx_nodejs_connections;
/* write event for input */
static ngx_event_t ** ngx_nodejs_connections;

static ngx_socket_t ngx_nodejs_fd[2];


static ngx_int_t
ngx_http_nodejs_process_init(ngx_cycle_t *cycle)
{
    int uvfd;

    /* TODO: can we use uv_backend_fd */



    if (ngx_add_channel_event(cycle, ngx_nodejs_fd[0], NGX_READ_EVENT,
                              ngx_http_nodejs_read_handler)
        == NGX_ERROR)
    {
        /* fatal */
        exit(2);
    }
}

static void
ngx_http_nodejs_process_exit(ngx_cycle_t *cycle)
{
    // TODO: call shutdowns.
}

static ngx_int_t
ngx_http_nodejs_emit_request(ngx_http_request_t *r)
{
    ngx_http_nodejs_conf_t *conf = ngx_http_get_module_loc_conf(r, ngx_http_nodejs_module);

    nginx::Server *server = conf->server;
    server->EmitRequest(r);

    /* TODO: */
    return NGX_DONE;
}


