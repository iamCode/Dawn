#include "elements.h"

#include "debug.h"

namespace ElementType
{
	std::string getElementName( ElementType::ElementType elementType )
	{
		switch( elementType ) {
			case Fire:
				return "Fire";
			break;
			case Water:
				return "Water";
			break;
			case Air:
				return "Air";
			break;
			case Earth:
				return "Earth";
			break;
			case Light:
				return "Light";
			break;
			case Dark:
				return "Dark";
			break;
			default:
				dawn_debug_warn( "unsupported element type in getElementName: %d. Aborting", static_cast<size_t>(elementType) );
				abort();
			break;
		}
	}
	
	std::string getElementNameLowercase( ElementType::ElementType elementType )
	{
		switch( elementType ) {
			case Fire:
				return "fire";
			break;
			case Water:
				return "water";
			break;
			case Air:
				return "air";
			break;
			case Earth:
				return "earth";
			break;
			case Light:
				return "light";
			break;
			case Dark:
				return "dark";
			break;
			default:
				dawn_debug_warn( "unsupported element type in getElementNameLowercase: %d. Aborting", static_cast<size_t>(elementType) );
				abort();
			break;
		}
	}
}

