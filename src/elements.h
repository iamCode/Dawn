#ifndef __ELEMENTS_H__
#define __ELEMENTS_H__

#include <string>

namespace ElementType
{
	enum ElementType
	{
		Fire,
		Water,
		Air,
		Earth,
		Light,
		Dark,
		Count
	};
	
	/// \brief Returns a string representation of the elementType.
	/// \example Fire -> "Fire"
	///
	std::string getElementName( ElementType::ElementType elementType );

	/// \brief Returns a string representation of the elementType in lowercase letters.
	/// \example Fire -> "fire"
	///
	std::string getElementNameLowercase( ElementType::ElementType elementType );
}

#endif // __ELEMENTS_H__
