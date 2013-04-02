

namespace nginx {

/*
Event: 'close'
response.writeContinue()
response.writeHead(statusCode, [reasonPhrase], [headers])
response.setTimeout(msecs, callback)
response.statusCode
response.setHeader(name, value)
response.headersSent
response.sendDate
response.getHeader(name)
response.removeHeader(name)
response.write(chunk, [encoding])
response.addTrailers(headers)
response.end([data], [encoding])
*/

/* nginx.ServerResponse inherits EventEmiter */
class ServerResponse : ObjectWrap {
public:
	static void Init(Handle<Object> exports);
	static Handle<Value> New(const Arguments& args);
	
	/* Events */
	static void EmitClose(ngx_http_request_t *r);

	/* Methods */
	static Handle<Value> WriteContinue(const Arguments& args);
	static Handle<Value> WriteHead(const Arguments& args);
	static Handle<Value> SetTimeout(const Arguments& args);
	static Handle<Value> SetHeader(const Arguments& args);
	static Handle<Value> GetHeader(const Arguments& args);
	static Handle<Value> RemoveHeader(const Arguments& args);
	static Handle<Value> Write(const Arguments& args);
    static Handle<Value> AddTrailers(const Arguments& args);
	static Handle<Value> End(const Arguments& args);

	/* TODO: Members */
	
private:
	ngx_http_request_t *request;
	/*  */
};

}


