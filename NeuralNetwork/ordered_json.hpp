#pragma once
#include "fifo_map.hpp"

namespace nlohmann {

	// A workaround to give to use fifo_map as map, we are just ignoring the 'less' compare
	template<class K, class V, class dummy_compare, class A>
	using workaround_fifo_map = fifo_map<K, V, fifo_map_compare<K>, A>;
	using ordered_json = basic_json<workaround_fifo_map>;

}
