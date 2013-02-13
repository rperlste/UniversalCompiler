#ifndef _scannerAction
#define _scannerAction

namespace ScannerAction{

	enum ScannerAction{
		Error,
		MoveAppend,
		MoveNoAppend,
		HaltAppend,
		HaltNoAppend,
		HaltReuse
	};

}

#endif