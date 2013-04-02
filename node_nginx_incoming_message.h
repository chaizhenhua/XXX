

namespace nginx {
using namespace v8;
using namespace node;
/*
Event: 'data'
Event: 'end'
Event: 'close'
message.httpVersion
message.headers
message.trailers
message.setTimeout(msecs, callback)
message.setEncoding([encoding])
message.pause()
message.resume()
message.method
message.url
message.statusCode
message.socket
*/

/* nginx.IncomingMessage inherits StreamWrap, EventEmiter */
class IncomingMessage : ObjectWrap {
public:
	static void Init(Handle<Object> exports);

    static Handle<Value> New(ngx_http_request_t *r, Server *s);

    
	// static Handle<Value> New(const Arguments& args);
    
	/* Events */

	/* Methods */


	/* EmitEvents */

	/* Methods */

    /* Members */

    static HANDLE<Value> GetHttpVersion(Local<String> property, const AccessorInfo& info);
    static HANDLE<Value> GetHeaders(Local<String> property, const AccessorInfo& info);
    static HANDLE<Value> GetTrailers(Local<String> property, const AccessorInfo& info);
private:
	ngx_http_request_t *request;
    Server             *s;
};
}

static HANDLE<Value> nginx::IncomingMessage::GetHeaders(Local<String> property, const AccessorInfo& info)
{
	  HandleScope scope;

      Local<Object>   headers;
      IncomingMessage *message = ObjectWrap::Unwrap<IncomingMessage>(info.Holder());
      ngx_http_request_t *r = message->request;
        /* TODO: */

      headers->Set(String, String);
        
      return scope.close(headers);
}


