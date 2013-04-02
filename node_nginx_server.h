

namespace nginx {
/* HTTP Server Event: 
 * Event: 'request'
 * Event: 'connection'
 * Event: 'close'
 * Event: 'checkContinue'
 * Event: 'connect'
 * Event: 'upgrade'
 * Event: 'clientError'
 */

/* nginx.Server inherits EventEmiter */
class Server: ObjectWrap {
public:
  static Handle<Value> New(const Arguments& args);
  
  void Init(Handle<Object> exports) {
  	
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("Server"));
	tpl->InstanceTemplate()->SetInternalFieldCount(0);
  
	Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
	exports->Set(String::NewSymbol("Server"), constructor);
  }

  /* EmitEvents called from nginx */
  void EmitRequest(ngx_http_request_t *r);
  void EmitClose();
  
  /* No Methods */
private:
  Context *context;
  /* TODO: nginx context */
};


/* TODO: */
Handle<Value> Server::New(const Arguments& args) {
  HandleScope scope;

  assert(args.IsConstructCall());
  Server* self = new Server();
  self->Wrap(args.This());

  return scope.Close(args.This());
}

void Server::EmitRequest(ngx_http_request_t *r) {
    
  Context::Scope context(this->context);
  
  HandleScope scope;

  IncomingMessage *req = (r, this);
  ServerResponse *res = (r, this);

  Handle<Value> argv[3] = {
    String::New("request"), // event name
         // request
       // response
  };

  MakeCallback(args.This(), "emit", 3, argv);
  
}
}


