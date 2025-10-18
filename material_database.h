#pragma once

#include "Bait.h"
#include "material_plus.h"

class material_database
{
private:
	std::vector<material_plus> material_vector{};
public:
	void database_re_init();
	void database_init();
};

