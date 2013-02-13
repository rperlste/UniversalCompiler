#ifndef _action
#define _action

namespace Action{

	static enum Action{
		Error,
		MoveAppend,
		MoveNoAppend,
		HaltAppend,
		HaltNoAppend,
		HaltReuse
	};

}

#endif