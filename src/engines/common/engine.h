#ifndef _IENGINE_H
#define _IENGINE_H

/**
 * The engine interface -- each engine must provide
 *	1) an ignition sequence
 *	2) what each cycle is to do
 *	3) the shutdown sequence
 */

enum status_codes { UNINITIALIZED, INITIALIZED, RUNNING, STOPPED };

class Engine {
	public:
		virtual void ignite();
		virtual void cycle();
		virtual void shutdown();

		virtual int get_status();
	protected:
		int status;
		/**
		 * initialize signal to 1 -- if signal == 0 while in .cycle(), call .shutdown()
		 */
		int signal;
};

#endif
