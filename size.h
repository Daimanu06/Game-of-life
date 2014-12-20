#ifndef _SIZE_H_
#define _SIZE_H_

#include <cstdint>

namespace gameoflife {

	struct Size {
			typedef std::uint16_t size_t;
			size_t width;
			size_t height;
	};

}

#endif // GRIDSIZE_H
