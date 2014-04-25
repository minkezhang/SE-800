#ifndef _IENGINE_H
#define _IENGINE_H

/**
 * The engine interface -- each engine must provide
 *	1) an ignition sequence
 *	2) what each cycle is to do
 *	3) the shutdown sequence
 */

class Engine {
	public:
		virtual void ignite();
		virtual void cycle();
		virtual void shutdown();
};

#endif
