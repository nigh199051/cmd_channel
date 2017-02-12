#include"mux.h"
#include"handler.h"

mux::mux(std::string,int port)
{
	this->ip=ip;
	this->port=port;
	emgr=new event_mgr();
	cs=new conn_status();
}


void mux::sock_init()
{
	listen_s.Bind("0.0.0.0",9699);
	listen_s.set_nonblock();
	listen_s.set_reuse();
	listen_s.Listen();

	if(worker_s.Connect("/tmp/worker.so")<0)
	{
		return;
	}
	worker_s.set_nonblock();
}

void mux::do_it()
{
	sock_init();

	Event e;
	e.fd=listen_s.get_fd();
	e.type0=EV_READ|EV_PERSIST;
	e.handler=handler::listenfd_handler;
	e.arg=(void*)this;
	emgr->add_event(e);

	Event we;
	we.fd=worker_s.get_fd();
	we.type0=EV_READ|EV_PERSIST;
	we.handler=handler::worker_handler;
	we.arg=(void*)this;
	emgr->add_event(we);

	{
		signal(SIGPIPE,SIG_IGN);
		signal(SIGHUP,SIG_IGN);
	}

	Event sig_e;
	sig_e.fd=2;
	sig_e.type0=EV_SIGNAL|EV_PERSIST;
	sig_e.handler=handler::sig_handler;
	sig_e.arg=(void*)this;
	
	emgr->add_sig_event(sig_e);
	emgr->run();
}
