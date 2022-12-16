export module new_baseclass;

import <memory>;

//new/delete operators with malloc/free to remove need for libstdc++
export class class_metamod_new
{
public:
	// Construction
	class_metamod_new(void) noexcept = default;

	// Operators
	inline void *operator new(size_t size) noexcept
	{
		if (size == 0)
			return(calloc(1, 1));
		return(calloc(1, size));
	}

	inline void *operator new[](size_t size) noexcept 
	{
		if (size == 0)
			return(calloc(1, 1));
		return(calloc(1, size));
	}

	inline void operator delete(void *ptr) noexcept 
	{
		if (ptr)
			free(ptr);
	}

	inline void operator delete[](void *ptr) noexcept 
	{
		if (ptr)
			free(ptr);
	}
};
