#pragma once

#include "GameFramework/Actor.h"

class JWUtils
{
public:
	template<typename ComponentClass, typename OwnerClass>
	static ComponentClass* GetComponent(OwnerClass* Actor)
	{
		if (!Actor)
			return nullptr;

		const auto Component = Actor->GetComponentByClass(ComponentClass::StaticClass());

		return Cast<ComponentClass>(Component);
	}
};